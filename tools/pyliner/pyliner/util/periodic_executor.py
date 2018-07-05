import logging
import threading
import time


class PeriodicExecutor(threading.Thread):
    """Executes a callback function every x-seconds.

    Optionally takes callbacks for exception and last-pass handling.

    Exceptions may occur in Python 2.7 during interpreter shutdown, as threads
    are left alive until the process closes, during which time the thread is
    attempting to access garbage collected objects.
    """

    def __init__(self, target, every=1, args=(), kwargs=None, exception=None,
                 finalize=None, name=None, logger=None, daemon=True):
        """
        Args:
            target (Callable): This method will be called with no arguments
                continuously until stopped.
            every (Real): Amount of seconds to sleep between calls.
            args (Optional[list]): If given, these args are passed to target.
            kwargs (Optional[dict]): If given, these kwargs are passed to
                target.
            exception (Callable): If an exception is raised this will
                be called with the exception as an argument.
            finalize (Callable): This method will be called with no arguments
                after the thread is stopped.
            name (str): The name of the thread. Default is autogenerated.
            logger (Logger): Logger to use. Default logging.getLogger(self.name)
            daemon (bool): Whether the thread is a daemon or not.
        """
        super(PeriodicExecutor, self).__init__(
            target=target, name=name, args=args, kwargs=kwargs)
        self.daemon = daemon  # Attribute of Thread

        # Instance Attributes
        self.exception = exception if exception else \
            lambda e: self.logger.exception(
                'Unhandled exception in thread %s', self.name)
        self.every = every
        self.finalize = finalize
        self.logger = logger if logger else logging.getLogger(self.name)
        self.running = False
        # self.target = target

    def run(self):
        """Do not call this directly. Use PeriodicExecutor.start()"""
        self.logger.info('Thread %s starting', self.name)
        self.running = True
        try:
            while self.running:
                self._Thread__target(
                    *self._Thread__args, **self._Thread__kwargs)
                time.sleep(self.every)
        except Exception as e:
            if callable(self.exception):
                self.exception(e)
        finally:
            if callable(self.finalize):
                self.finalize()
            self.stop()

    def stop(self):
        """Stops the thread from continuing to loop.

        Thread will not stop immediately. When the thread wakes up next it will
        see that it has been stopped, will execute the finalize method if it was
        given, and will then complete.
        """
        self.logger.info('Thread %s stopping.', self.name)
        self.running = False
