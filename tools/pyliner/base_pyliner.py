import re
from abc import abstractmethod, ABCMeta
from datetime import datetime
from os.path import join

from builtins import isinstance
from junit_xml import TestCase, TestSuite
from sortedcontainers import SortedDict

from app import App
from communication import Communication
from logging_service import LoggingService
from service import ServiceWrapper
from telemetry import Telemetry


class ScriptingWrapper:
    def __init__(self, vehicle):
        self._vehicle = vehicle

    def __getattr__(self, item):
        apps = self._vehicle.apps
        if item in apps:
            return apps[item]
        raise AttributeError('{} is not a method or module of this '
                             'Pyliner instance.'.format(item))


class BasePyliner(object):
    """
    Contains the bare-minimum required for Pyliner. All additional functionality
    is provided through the Pyliner class.

    Implements context manager (with-statement) functionality. Unhandled
    exceptions in the context manager are passed to `critical_failure` to give
    the user a chance to fail gracefully before exiting the context manager.

    Module management is performed via the `enable_module` and `disable_module`
    methods. Modules are given a name which must be a valid Python identifier.
    The module is then accessible directly by that name (pyliner.module).

    By way of the communications instance given in the constructor, telemetry
    from the vehicle is exposed via the TODO methods.
    """
    __metaclass__ = ABCMeta

    def __init__(self, communications, logging):
        """Constructor for BasePyliner.

        Args:
            communications (Communication): Communications PylinerModule.
                Not exposed as a public module for direct access, but the user
                is given the option to use a custom class if they desire.
            logging (LoggingService):
        """
        self._apps = {}
        self._services = set()
        self._communications = communications
        self._com_priority = SortedDict()

        # Only uses log method. May eventually remove when logging is unified.
        self._communications.attach(self)
        self.attach_service('logging', logging)
        logging.start()

    def __enter__(self):
        return ScriptingWrapper(self)

    def __exit__(self, exc_type, exc_val, exc_tb):
        # If the context manager exits without error, all good. Otherwise...
        if exc_type:
            self.critical_failure(exc_type, exc_val, exc_tb)

    @property
    def apps(self):
        """Mapping of enabled modules."""
        return self._apps.copy()

    def attach_app(self, priority, name, app):
        """Enable a PylinerApp on this vehicle."""
        identifier = re.compile(r"^[^\d\W]\w*\Z")

        if priority in self._com_priority:
            raise ValueError('There is already a module with priority '
                             '{}'.format(priority))
        elif name in self._apps:
            raise ValueError('Attempting to enable a module on top of an '
                             'existing module.')
        elif not re.match(identifier, name):
            raise ValueError('Attempting to enable a module with an illegal '
                             'name. Module names must be valid Python '
                             'identifiers.')
        elif not isinstance(app, App):
            return TypeError('module must implement App.')
        app.attach(self)
        self._apps[name] = app
        self._com_priority[priority] = app

    def attach_service(self, service_name, service):
        sw = ServiceWrapper(self, service_name, service)
        self._services.add(sw)
        service.attach(sw)

    @abstractmethod
    def critical_failure(self, exc_type, exc_val, exc_tb):
        raise NotImplementedError()

    def detach_app(self, name):
        """Disable an app by removing it from the vehicle.

        Note:
            Any apps that attempt to call the disabled app by name will
            produce an error.
        """
        if name not in self._apps:
            raise AttributeError('Cannot disable a module that was never '
                                 'enabled.')
        module = self._apps[name]
        del self._apps[name]
        module.detach()
        for priority, pri_module in self._com_priority.items():
            if module is pri_module:
                self._com_priority.pop(priority)

    def telemetry(self):
        # type: () -> Telemetry
        """Return telemetry to send, or None."""
        # Iterate through every app in priority order to see if any have
        # telemetry to send.
        for app in self._com_priority.values():  # type: App
            if app.telemetry_available:
                return app.telemetry
        return None

    def log(self, text, level=LogLevel.Info):
        """ Wrapper for logging function """
        if level == LogLevel.Debug:
            logging.debug(text)
        elif level == LogLevel.Info:
            logging.info(text)
        elif level == LogLevel.Warn:
            logging.warn(text)
        elif level == LogLevel.Error:
            logging.error(text)
        else:
            logging.debug("Specified log mode unsupported")

    # Testing Code. TODO Figure out where to put this
    def assert_equals(self, a, b, description):
        """ Assert for Pyliner that tracks passes and failures """
        if a == b:
            self.passes += 1
            self.test_description.append(description)
            self.log('Valid assertion made: %s == %s' % (a, b))
        else:
            self.fails += 1
            self.test_description.append(description)
            self.log('Invalid assertion made: %s == %s' % (a, b), LogLevel.Warn)

    def assert_not_equals(self, a, b, description):
        """ Assert for Pyliner that tracks passes and failures """
        if a != b:
            self.passes += 1
            self.test_description.append(description)
            self.log('Valid assertion made: %s != %s' % (a, b))
        else:
            self.fails += 1
            self.test_description.append(description)
            self.log('Invalid assertion made: %s != %s' % (a, b), LogLevel.Warn)

    def assert_true(self, expr, description):
        """ Assert for Pyliner that tracks passes and failures """
        if expr:
            self.passes += 1
            self.test_description.append(description)
            self.log("Valid true assertion made")
        else:
            self.fails += 1
            self.test_description.append(description)
            self.log("Invalid true assertion made", LogLevel.Warn)

    def assert_false(self, expr, description):
        """ Assert for Pyliner that tracks passes and failures """
        if not expr:
            self.passes += 1
            self.test_description.append(description)
            self.log("Valid false assertion made")
        else:
            self.fails += 1
            self.test_description.append(description)
            self.log("Invalid false assertion made", LogLevel.Warn)

    def dump_tlm(self):
        """ Dump all received telemetry to file """
        with open(join(self.log_dir, self.log_name[:-3]) + 'tlm',
                  'w') as tlm_file:
            for tlm in self.all_telemetry:
                tlm_file.write(str(tlm) + '\n')

    def get_test_results(self):
        """ Generates a string with all test results """
        time_diff = datetime.now() - self.start_time
        diff = divmod(time_diff.total_seconds(), 60)
        duration = "%i minutes %i seconds" % (diff[0], diff[1]) if diff[0] > 0 \
            else "%i seconds" % (diff[1])
        self.duration = time_diff.seconds
        result = "PASS" if self.fails == 0 else "FAIL"

        results = "=================================================\n"
        results += "Pyliner test complete\n"
        results += "Test case:  " + self.script_name + "\n"
        results += "Result:     " + result + "\n"
        results += "Passes:     " + str(self.passes) + "\n"
        results += "Fails:      " + str(self.fails) + "\n"
        results += "Duration:   " + str(duration) + "\n"
        results += "================================================="
        return results

    def finish_test(self):
        """ Do all the clean up post test execution """
        self.dump_tlm()
        print(self.get_test_results())
        self.generate_junit()

    def generate_junit(self):
        # Get the test count
        test_count = self.passes + self.fails
        # Add the first test case
        test_cases = [
            TestCase(self.script_name + str(0), '', self.duration / test_count,
                     '', '')]
        # Add the remaining test cases
        for x in range(1, test_count):
            test_cases.append(TestCase(self.script_name + str(x), '',
                                       self.duration / test_count, '', ''))
        # Add any failure info
        for x in range(0, self.fails):
            test_cases[0].add_failure_info(self.test_description[x])
        ts = TestSuite("test suite", test_cases)
        with open(join(self.log_dir, self.script_name + '_results.xml'),
                  'w') as f:
            TestSuite.to_file(f, [ts], prettyprint=False)

    def reset_test(self):
        """ Reset  """
        pass  # Need this?
