from os import path, sys
sys.path.append(path.dirname( path.dirname( path.dirname( path.abspath(__file__) ) ) ) )
from pyliner import Pyliner
import time
import math
from flight_control_lib import *

# Initialize pyliner object
rocky = Pyliner(**{"airliner_map": "cookiecutter.json", 
                   "ci_port": 5009,
                   "to_port": 5012,
                   "script_name": "FT6_Onboard",
                   "log_dir": "./logs/"})

# Subscribe to desired telemetry
rocky.subscribe({'tlm': ['/Airliner/CNTL/VehicleGlobalPosition/Lat',
                         '/Airliner/CNTL/VehicleGlobalPosition/Lon',
                         '/Airliner/CNTL/VehicleGlobalPosition/Alt',
                         '/Airliner/CNTL/VehicleGlobalPosition/Yaw',
                         '/Airliner/CNTL/VehicleGlobalPosition/VelN',
                         '/Airliner/CNTL/VehicleGlobalPosition/VelE',
                         '/Airliner/CNTL/VehicleGlobalPosition/VelD']})

# Wait for pyliner data dictionary to populate with initial values
while rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt') == 'NULL':
    print "Waiting for telemetry downlink..."
    time.sleep(1)

alt = rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt')
print "alt: " + str(alt)

vehicle_arm(rocky)
atp(rocky, "Takeoff")
vehicle_takeoff(rocky)
vehicle_flight_mode(rocky, FlightMode.PosCtl)

alt = rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt')
print "alt: " + str(alt)

vehicle_move(rocky, Direction.Forward, speed = 1.0, time = 2, stop = True, stop_wait = 3)
vehicle_move(rocky, Direction.Left, speed = 1.0, time = 2, stop = True, stop_wait = 3)
vehicle_move(rocky, Direction.Backward, speed = 1.0, time = 2, stop = True, stop_wait = 3)
vehicle_move(rocky, Direction.Right, speed = 1.0, time = 2, stop = True, stop_wait = 3)

atp(rocky, "RTL")
vehicle_rtl(rocky)

alt = rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt')
print "alt: " + str(alt)
