"""
The Vehicle Access module provides a token-ish interface for a component to
interact with a vehicle, and the other components of the vehicle.

Classes:
    AppAccess  Access controller between a Vehicle and its components.
"""

from pyliner.intent import Intent
from pyliner.intent import IntentFilter
from pyliner.intent import IntentFuture, IntentResponse
from pyliner.pyliner_exceptions import InvalidStateError
from pyliner.util.loggable import Loggable


class AppAccess(Loggable):
    """
    The AppAccess class acts as a boundary between components on a vehicle
    so that they do not interact destructively with each other. Components must
    access the vehicle through the interface provided by their AppAccess.
    """
    def __init__(self, app):
        super(AppAccess, self).__init__()
        self.callback = None
        self.app = app
        self.vehicle = None
        """:type: BaseVehicle"""
        self._filter = {}
        """:type: dict[IntentFilter, Callable[[Intent], Any]"""

    def attach(self, vehicle):
        """Attach the App to a Vehicle."""
        self.vehicle = vehicle
        self.logger = vehicle.logger.getChild(self.app.qualified_name)
        self.app.attach(self)

    def detach(self):
        """Detach the App from the Vehicle."""
        self.app.detach()
        self.vehicle = None
        self.logger = None

    def add_filter(self, intent_filter, callback):
        """Add an intent filter.

        Args:
            intent_filter (IntentFilter): The filter to apply to incoming
                intents.
            callback (Callable[[Intent], Any]: If an incoming intent passes
                through the filter, the callback will be run with the intent
                as an argument.

        Returns:
            IntentFilter: Same object as intent_filter.
        """
        if not isinstance(intent_filter, IntentFilter):
            raise TypeError('intent_filter must be IntentFilter.')
        if not callable(callback):
            raise TypeError('callback must be callable.')
        self._filter[intent_filter] = callback
        self.vehicle.add_filter(intent_filter, self)
        return intent_filter

    def clear_filter(self):
        """Remove all intent filters."""
        self._filter.clear()

    def receive(self, intent, future):
        """Receive an intent and pass it to any callbacks that are listening.

        If self.callback is set, call that before checking intent filters.

        Args:
            intent (Intent): The intent that was broadcast.
            future (IntentFuture): The Future to return results into.
        """
        def handle(cb):
            result = exception = None
            try:
                result = cb(intent)
            except Exception as e:
                exception = e
                self.exception('While handling {}, an Exception was raised:'
                               .format(intent))
            if result is not None or exception is not None:
                future.add(IntentResponse(result=result, exception=exception))

        if callable(self.callback):
            handle(self.callback)
        for intent_filter, callback in self._filter.items():
            if intent in intent_filter:
                handle(callback)

    def broadcast(self, intent):
        # type: (Intent) -> IntentFuture
        """Broadcast an intent to the vehicle."""
        if not self.vehicle:
            raise InvalidStateError('Cannot broadcast while detached.')
        return self.vehicle.broadcast(intent)

    def remove_filter(self, intent_filter):
        """Remove a filter (by the tuple returned by add) from this access."""
        del self._filter[intent_filter]
        self.vehicle.remove_filter(intent_filter, self)
