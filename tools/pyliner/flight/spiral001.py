"""
Fly in a rising spiral.

Requirements Fulfilled:
    PYLINER001
    PYLINER003
    PYLINER004
    PYLINER009
    PYLINER010
    PYLINER011
    PYLINER012
    PYLINER013
    PYLINER014
    PYLINER016
"""
import time
from os.path import basename

from pyliner.app.communication import Communication
from pyliner.app.controller import FlightMode
from pyliner.vehicle import Vehicle
from pyliner.util import read_json, enable_logging
from pyliner.util.scripting_wrapper import ScriptingWrapper

enable_logging(log_dir='logs', script=basename(__file__))

rky = Vehicle(
    vehicle_id='rocky',
    communication=Communication(
        airliner_map=read_json("airliner.json"),
        ci_port=5009,
        to_port=5012)
)

with ScriptingWrapper(rky) as rocky:
    while rocky.nav.altitude == "NULL":
        time.sleep(1)
        print "Waiting for telemetry downlink..."
    
    rocky.ctrl.atp('Arm')
    rocky.ctrl.arm()
    rocky.ctrl.atp('Takeoff')
    rocky.ctrl.takeoff()
    rocky.ctrl.flight_mode(FlightMode.PosCtl)

    start_altitude = rocky.nav.altitude

    rocky.ctrl.atp('Start Spiral')
    rocky.fd.y = 0.75
    rocky.fd.z = 0.5
    rocky.fd.r = -0.2

    while rocky.nav.altitude < start_altitude + 10:
        time.sleep(1)
    rocky.fd.zero()

    rocky.ctrl.atp('Return')
    rocky.ctrl.rtl()
