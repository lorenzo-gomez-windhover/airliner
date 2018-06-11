""" This file was autogenerated from template version 0.0.0.1 and autogenerator version 0.0.0.1 """

from pyliner.python_pb import es_app_name_pb2
from pyliner.python_pb import es_query_all_tasks_pb2
from pyliner.python_pb import es_perf_set_trig_mask_pb2
from pyliner.python_pb import es_shell_pb2
from pyliner.python_pb import es_perf_start_pb2
from pyliner.python_pb import es_start_app_pb2
from pyliner.python_pb import es_dump_cds_reg_pb2
from pyliner.python_pb import es_delete_cds_pb2
from pyliner.python_pb import es_app_reload_pb2
from pyliner.python_pb import es_set_max_pr_count_pb2
from pyliner.python_pb import es_tlm_pool_stats_cmd_pb2
from pyliner.python_pb import es_hk_pb2
from pyliner.python_pb import es_perf_stop_pb2
from pyliner.python_pb import es_write_sys_log_pb2
from pyliner.python_pb import es_write_er_log_pb2
from pyliner.python_pb import es_query_all_pb2
from pyliner.python_pb import es_one_app_pb2
from pyliner.python_pb import es_shell_packet_pb2
from pyliner.python_pb import es_restart_pb2
from pyliner.python_pb import es_overwrite_sys_log_pb2
from pyliner.python_pb import es_perf_set_filter_mask_pb2
from pyliner.python_pb import px4_position_setpoint_triplet_pb2
from pyliner.python_pb import px4_manual_control_setpoint_pb2
from pyliner.python_pb import px4_vehicle_command_msg_pb2
from pyliner.python_pb import sens_hk_pb2
from pyliner.python_pb import gps_hk_pb2
from pyliner.python_pb import px4_vehicle_global_position_msg_pb2

proto_msg_map = { 
    "CFE_ES_AppNameCmd_t": es_app_name_pb2.es_app_name_pb,
    "CFE_ES_QueryAllTasksCmd_t": es_query_all_tasks_pb2.es_query_all_tasks_pb,
    "CFE_ES_PerfSetTrigMaskCmd_t": es_perf_set_trig_mask_pb2.es_perf_set_trig_mask_pb,
    "CFE_ES_ShellCmd_t": es_shell_pb2.es_shell_pb,
    "CFE_ES_PerfStartCmd_t": es_perf_start_pb2.es_perf_start_pb,
    "CFE_ES_StartAppCmd_t": es_start_app_pb2.es_start_app_pb,
    "CFE_ES_DumpCDSRegCmd_t": es_dump_cds_reg_pb2.es_dump_cds_reg_pb,
    "CFE_ES_DeleteCDSCmd_t": es_delete_cds_pb2.es_delete_cds_pb,
    "CFE_ES_AppReloadCmd_t": es_app_reload_pb2.es_app_reload_pb,
    "CFE_ES_SetMaxPRCountCmd_t": es_set_max_pr_count_pb2.es_set_max_pr_count_pb,
    "CFE_ES_TlmPoolStatsCmd_t": es_tlm_pool_stats_cmd_pb2.es_tlm_pool_stats_cmd_pb,
    "CFE_ES_HkPacket_t": es_hk_pb2.es_hk_pb,
    "CFE_ES_PerfStopCmd_t": es_perf_stop_pb2.es_perf_stop_pb,
    "CFE_ES_WriteSyslogCmd_t": es_write_sys_log_pb2.es_write_sys_log_pb,
    "CFE_ES_WriteERlogCmd_t": es_write_er_log_pb2.es_write_er_log_pb,
    "CFE_ES_QueryAllCmd_t": es_query_all_pb2.es_query_all_pb,
    "CFE_ES_OneAppTlm_t": es_one_app_pb2.es_one_app_pb,
    "CFE_ES_ShellPacket_t": es_shell_packet_pb2.es_shell_packet_pb,
    "CFE_ES_RestartCmd_t": es_restart_pb2.es_restart_pb,
    "CFE_ES_OverWriteSysLogCmd_t": es_overwrite_sys_log_pb2.es_overwrite_sys_log_pb,
    "CFE_ES_PerfSetFilterMaskCmd_t": es_perf_set_filter_mask_pb2.es_perf_set_filter_mask_pb,
    "PX4_PositionSetpointTripletMsg_t": px4_position_setpoint_triplet_pb2.px4_position_setpoint_triplet_pb,
    "PX4_ManualControlSetpointMsg_t": px4_manual_control_setpoint_pb2.px4_manual_control_setpoint_pb,
    "PX4_VehicleCommandMsg_t": px4_vehicle_command_msg_pb2.px4_vehicle_command_msg_pb,
    "SENS_HkTlm_t": sens_hk_pb2.sens_hk_pb,
    "GPS_HkTlm_t": gps_hk_pb2.gps_hk_pb,
    "PX4_VehicleGlobalPositionMsg_t": px4_vehicle_global_position_msg_pb2.px4_vehicle_global_position_msg_pb
}

