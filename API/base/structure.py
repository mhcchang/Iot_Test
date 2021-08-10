# coding=utf-8

from ctypes import *


class struct_IotIpcConfig(Structure):
    _fields_ = [

        ('addr', (c_char * 32)),

        ('port', c_uint16),

        ('username', (c_char * 32)),

        ('password', (c_char * 32)),

        ('chan_no', c_uint16),

        ('chan_profile', c_uint16),

        ('model', (c_char * 32)),

        ('rtsp_url', (c_char * 512))

    ]


class struct_IotSmartIpcConfig(Structure):
    _fields_ = [

        ('addr', (c_char * 32)),

        ('port', c_uint16),

        ('video_port', c_uint16),

        ('username', (c_char * 32)),

        ('password', (c_char * 32)),

        ('chan_no', c_uint16),

        ('chan_profile', c_uint16),

        ('model', (c_char * 32)),

        ('rtsp_url', (c_char * 512)),

        ('platform_id', (c_char * 24)),

        ('device_code', (c_char * 24))

    ]


class struct_IotGbIpcConfig(Structure):
    _fields_ = [

        ('platform_id', (c_char * 24)),

        ('device_code', (c_char * 24))

    ]


class struct_IotBoxConfig(Structure):
    _fields_ = [

        ('addr', (c_char * 32)),

        ('port', c_uint16),

        ('username', (c_char * 32)),

        ('password', (c_char * 32)),

        ('chan_num', c_uint16),

        ('model', (c_char * 32)),

        ('platform_id', (c_char * 24)),

        ('device_code', (c_char * 24))

    ]


class struct_IotCloudIpcConfig(Structure):
    _fields_ = [

        ('addr', (c_char * 32)),

        ('port', c_uint16),

        ('video_port', c_uint16),

        ('username', (c_char * 32)),

        ('password', (c_char * 32)),

        ('chan_no', c_uint16),

        ('chan_num', c_uint16),

        ('chan_profile', c_uint16),

        ('model', (c_char * 32)),

        ('rtsp_url', (c_char * 512)),

        ('platform_id', (c_char * 24)),

        ('device_code', (c_char * 24))

    ]


class struct_IotKafkaIpcConfig(Structure):
    _fields_ = [

        ('addr', (c_char * 32)),

        ('port', c_uint16),

        ('username', (c_char * 32)),

        ('password', (c_char * 32)),

        ('model', (c_char * 32)),

        ('url', (c_char * 512)),

        ('topic_name', (c_char * 64))

    ]


class union_IotDeviceConfig(Union):
    _fields_ = [

        ('rtsp_url', (c_char * 512)),

        ('ipc', struct_IotIpcConfig),

        ('smart_ipc', struct_IotSmartIpcConfig),

        ('gb_ipc', struct_IotGbIpcConfig),

        ('box', struct_IotBoxConfig),

        ('cloud_ipc', struct_IotCloudIpcConfig),

        ('kafka_ipc', struct_IotKafkaIpcConfig)

    ]


class struct_IotDeviceConfig(Structure):
    _fields_ = [

        ('vendor', c_int),

        ('type', c_int),

        ('anon_union', union_IotDeviceConfig)

    ]


class struct_IotWifiSensorConfig(Structure):
    _fields_ = [

        ('addr', (c_char * 32)),

        ('port', c_uint16),

        ('username', (c_char * 32)),

        ('password', (c_char * 32)),

        ('mark_id', (c_char * 24)),

        ('business_id', (c_char * 24))

    ]


class union_IotSensorDeviceConfig(Union):
    _fields_ = [

        ('wifi', struct_IotWifiSensorConfig)

    ]


class struct_IotSensorDeviceConfig(Structure):
    _fields_ = [

        ('type', c_int),

        ('vendor', c_int),

        ('anon_union', union_IotSensorDeviceConfig)

    ]


class struct_IotDeviceInfo(Structure):
    _fields_ = [

        ('id', (c_char * 24)),

        ('config', struct_IotDeviceConfig),

        ('online', c_int)

    ]


class struct_IotDeviceStatus(Structure):
    _fields_ = [

        ('online', c_uint8),

        ('status', c_uint8),

        ('encode', c_uint8),

        ('record', c_uint8),

        ('device_time', (c_char * 32))

    ]


class struct_IotGbDeviceInfo(Structure):
    _fields_ = [

        ('manufacturer', (c_char * 32)),

        ('model', (c_char * 32)),

        ('firmware', (c_char * 32)),

        ('max_camera_num', c_uint16),

        ('max_alarm_num', c_uint16)

    ]


class struct_IotGbDeviceCatalog(Structure):
    _fields_ = [

        ('sub_device_id', (c_char * 24)),

        ('name', (c_char * 64)),

        ('manufacturer', (c_char * 32)),

        ('model', (c_char * 32)),

        ('owner', (c_char * 32)),

        ('civil_code', (c_char * 32)),

        ('block', (c_char * 32)),

        ('address', (c_char * 128)),

        ('parental', (c_char * 16)),

        ('parent_id', (c_char * 24)),

        ('safety_way', (c_char * 32)),

        ('register_way', (c_char * 32)),

        ('cert_num', (c_char * 32)),

        ('certifiable', (c_char * 32)),

        ('err_code', (c_char * 32)),

        ('end_time', (c_char * 32)),

        ('secrecy', (c_char * 32)),

        ('ip_address', (c_char * 32)),

        ('port', c_uint16),

        ('password', (c_char * 32)),

        ('status', (c_char * 32)),

        ('longitude', (c_char * 32)),

        ('latitude', (c_char * 32))

    ]


class struct_IotLiteDeviceCatalog(Structure):
    _fields_ = [

        ('is_catalog', c_int),

        ('name', (c_char * 64)),

        ('sub_device_id', (c_char * 24)),

        ('parent_id', (c_char * 24)),

        ('longitude', (c_char * 32)),

        ('latitude', (c_char * 32))

    ]


class struct_IotRecordClipInfo(Structure):
    _fields_ = [

        ('start_time', (c_char * 32)),

        ('end_time', (c_char * 32))

    ]


class struct_IotRectInfo(Structure):
    _fields_ = [

        ('left', c_uint32),

        ('top', c_uint32),

        ('right', c_uint32),

        ('bottom', c_uint32)

    ]


class struct_IotFacePicInfo(Structure):
    _fields_ = [

        ('face_id', c_int),

        ('face_level', c_uint8),

        ('pic_format', c_uint8),

        ('res1', (c_uint8 * 2)),

        ('rect_type', c_int),

        ('rect', struct_IotRectInfo),

        ('face_rect', struct_IotRectInfo),

        ('age', c_uint8),

        ('gender', c_uint8),

        ('masks', c_uint8),

        ('beard', c_uint8),

        ('eye', c_uint8),

        ('mouth', c_uint8),

        ('glasses', c_uint8),

        ('race', c_uint8),

        ('emotion', c_uint8),

        ('smile', c_uint8),

        ('value', c_uint8),

        ('nation', c_uint8),

        ('face_width', c_uint16),

        ('face_height', c_uint16),

        ('res2', (c_uint8 * 16))

    ]


class struct_IotFacePicInfo2(Structure):
    _fields_ = [

        ('face_id', c_int),

        ('level', c_uint8),

        ('pic_format', c_uint8),

        ('res1', (c_uint8 * 1)),

        ('rect_type', c_uint8),

        ('rect', struct_IotRectInfo),

        ('face_rect', struct_IotRectInfo),

        ('face_len', c_uint32),

        ('feature_data_len', c_uint32),

        ('landmark_data_len', c_uint32),

        ('extend_data_len', c_uint32),

        ('face_buf', POINTER(c_uint8)),

        ('feature_data', POINTER(c_uint8)),

        ('landmark_data', POINTER(c_uint8)),

        ('extend_data', POINTER(c_uint8)),

        ('face_width', c_uint16),

        ('face_height', c_uint16),

        ('age', c_uint8),

        ('gender', c_uint8),

        ('masks', c_uint8),

        ('beard', c_uint8),

        ('eye', c_uint8),

        ('mouth', c_uint8),

        ('glasses', c_uint8),

        ('race', c_uint8),

        ('emotion', c_uint8),

        ('smile', c_uint8),

        ('value', c_uint8),

        ('nation', c_uint8),

        ('related_id', c_int),

        ('res2', (c_uint8 * 84))

    ]


class struct_IotBodyPicInfo(Structure):
    _fields_ = [

        ('body_id', c_int),

        ('track_face_id', c_int),

        ('level', c_uint8),

        ('pic_format', c_uint8),

        ('res1', (c_uint8 * 5)),

        ('rect_type', c_uint8),

        ('rect', struct_IotRectInfo),

        ('cut_rect', struct_IotRectInfo),

        ('body_width', c_uint16),

        ('body_height', c_uint16),

        ('body_len', c_uint32),

        ('body_buf', POINTER(c_uint8)),

        ('rucksack', c_uint8),

        ('hat', c_uint8),

        ('hat_colour', c_uint8),

        ('hair', c_uint8),

        ('hair_colour', c_uint8),

        ('upper_type', c_uint8),

        ('upper_mode', c_uint8),

        ('upper_colour', c_uint8),

        ('lower_type', c_uint8),

        ('lower_mode', c_uint8),

        ('lower_colour', c_uint8),

        ('shoes_type', c_uint8),

        ('shoes_colour', c_uint8),

        ('bags_type', c_uint8),

        ('bags_colour', c_uint8),

        ('umbrella_type', c_uint8),

        ('umbrella_colour', c_uint8),

        ('something_on_chest', c_uint8),

        ('direction', c_uint8),

        ('speed', c_uint8),

        ('ride', c_uint8),

        ('res2', (c_uint8 * 107))

    ]


class struct_IotItsPicInfo(Structure):
    _fields_ = [

        ('its_id', c_int),

        ('face_level', c_uint8),

        ('pic_format', c_uint8),

        ('direction', c_uint8),

        ('brand_confidence', c_uint8),

        ('rect_type', c_int),

        ('rect', struct_IotRectInfo),

        ('plate', (c_char * 32)),

        ('plate_color', c_int),

        ('plate_type', c_int),

        ('car_color', c_int),

        ('speed', c_int),

        ('alarm_type', c_int),

        ('vehicle_brand', c_int),

        ('vehicle_type', c_int),

        ('plate_rect', struct_IotRectInfo),

        ('plate_len', c_int),

        ('plate_data', POINTER(c_uint8)),

        ('res2', (c_uint8 * 8))

    ]


class struct_IotItsPicInfo2(Structure):
    _fields_ = [

        ('its_id', c_int),

        ('level', c_uint8),

        ('pic_format', c_uint8),

        ('res1', (c_uint8 * 1)),

        ('rect_type', c_uint8),

        ('rect', struct_IotRectInfo),

        ('plate_rect', struct_IotRectInfo),

        ('brand_rect', struct_IotRectInfo),

        ('its_len', c_uint32),

        ('plate_len', c_uint32),

        ('its_buf', POINTER(c_uint8)),

        ('plate_data', POINTER(c_uint8)),

        ('plate', (c_char * 32)),

        ('alarm_type', c_int),

        ('plate_color', c_int),

        ('plate_type', c_int),

        ('car_color', c_int),

        ('speed', c_int),

        ('vehicle_brand', c_int),

        ('vehicle_type', c_int),

        ('direction', c_uint8),

        ('brand_confidence', c_uint8),

        ('res2', (c_uint8 * 50))

    ]


class union_IotSubPicInfo(Union):
    _fields_ = [

        ('face', struct_IotFacePicInfo),

        ('its', struct_IotItsPicInfo)

    ]


class struct_IotSubPicInfo(Structure):
    _fields_ = [

        ('pic_type', c_int),

        ('data_len', c_uint32),

        ('data_buf', POINTER(c_uint8)),

        ('feature_data_len', c_uint32),

        ('feature_data', POINTER(c_uint8)),

        ('landmark_data_len', c_uint32),

        ('landmark_data', POINTER(c_uint8)),

        ('extend_data_len', c_uint32),

        ('extend_data', POINTER(c_uint8)),

        ('anon_union', union_IotSubPicInfo)

    ]


class struct_IotFaceRecognizeInfo(Structure):
    _fields_ = [

        ('group_id', c_int),

        ('people_id', c_int),

        ('group_name', (c_char * 64)),

        ('people_name', (c_char * 32)),

        ('cert_id', (c_char * 32)),

        ('cert_type', c_int),

        ('score', c_float),

        ('data_buf', POINTER(c_uint8)),

        ('data_len', c_uint32),

        ('sex', c_uint8),

        ('res', (c_uint8 * 35))

    ]


class struct_IotItsRecognizeInfo(Structure):
    _fields_ = [

        ('group_id', c_int),

        ('its_id', c_int),

        ('group_name', (c_char * 64)),

        ('its_name', (c_char * 32)),

        ('cert_id', (c_char * 32)),

        ('cert_type', c_int),

        ('score', c_float),

        ('data_buf', POINTER(c_uint8)),

        ('data_len', c_uint32),

        ('res', (c_uint8 * 36))

    ]


class struct_IotSubStructureInfo(Structure):
    _fields_ = [

        ('have_face', c_int),

        ('face', struct_IotFacePicInfo2),

        ('have_body', c_int),

        ('body', struct_IotBodyPicInfo),

        ('have_its', c_int),

        ('its', struct_IotItsPicInfo2),

        ('face_ri_num', c_int),

        ('face_ri', (struct_IotFaceRecognizeInfo * 5)),

        ('its_ri_num', c_int),

        ('its_ri', (struct_IotItsRecognizeInfo * 5))

    ]


class struct_IotCapPicturesInfo(Structure):
    _fields_ = [

        ('timestamp', c_int64),

        ('seq', c_uint32),

        ('pic_format', c_uint32),

        ('full_len', c_uint32),

        ('full_buf', POINTER(c_uint8)),

        ('sub_num', c_uint32),

        ('sub_pic', (struct_IotSubPicInfo * 32)),

        ('res', (c_uint8 * 12))

    ]


class struct_IotStructurePicturesInfo(Structure):
    _fields_ = [

        ('timestamp', c_int64),

        ('seq', c_uint32),

        ('pic_format', c_uint32),

        ('full_width', c_uint32),

        ('full_height', c_uint32),

        ('full_buf', POINTER(c_uint8)),

        ('full_len', c_uint32),

        ('res', (c_uint8 * 32)),

        ('sub_num', c_uint32),

        ('sub_pic', (struct_IotSubStructureInfo * 1))

    ]


class struct_IotVideoFrameInfo(Structure):
    _fields_ = [

        ('timestamp', c_int64),

        ('seq', c_uint32),

        ('encode_type', c_uint8),

        ('frame_type', c_uint8),

        ('resolution', c_uint8),

        ('frame_rate', c_uint8),

        ('res', (c_uint8 * 8))

    ]


class struct_IotStreamNotifyInfo(Structure):
    _fields_ = [

        ('dev_id', (c_char * 24)),

        ('handle', c_int),

        ('error', c_int)

    ]


class struct_IotUpgradeStateNotify(Structure):
    _fields_ = [

        ('dev_id', (c_char * 24)),

        ('step', c_int),

        ('process', c_int)

    ]


class struct_IotDeviceVersionInfo(Structure):
    _fields_ = [

        ('firmware', (c_char * 128)),

        ('algorithm', (c_char * 128))

    ]


class struct_IotDeviceAlgorithmInfo(Structure):
    _fields_ = [

        ('status', c_uint8),

        ('res', (c_uint8 * 31))

    ]


class struct_IotPictureStreamParam(Structure):
    _fields_ = [

        ('resolution', c_int),

        ('pic_quality', c_uint8),

        ('upload_panorama', c_uint8),

        ('upload_strategy', c_uint8),

        ('snap_mode', c_uint8),

        ('snap_num', c_uint8),

        ('recognize_mode', c_uint8),

        ('recog_upload_num', c_uint8),

        ('recog_upload_interval', c_uint16),

        ('min_face_pixels', c_uint16),

        ('res', (c_uint8 * 113))

    ]


class struct_IotVideoStreamParam(Structure):
    _fields_ = [

        ('profile_type', c_int),

        ('bitrate_type', c_int),

        ('bitrate', c_int),

        ('frame_rate', c_int),

        ('resolution', c_int),

        ('iframe_interval', c_uint16),

        ('res', (c_uint8 * 42))

    ]


class struct_IotPanoramaParam(Structure):
    _fields_ = [

        ('open_flag', c_int),

        ('compress_ratio', c_int)

    ]


class struct_IotResolutionCapability(Structure):
    _fields_ = [

        ('profile_type', c_int),

        ('num', c_int),

        ('list', (c_int * 100))

    ]


class struct_IotDateTime(Structure):
    _fields_ = [

        ('year', c_uint16),

        ('month', c_uint16),

        ('day', c_uint16),

        ('hour', c_uint16),

        ('minute', c_uint16),

        ('second', c_uint16),

        ('millisecond', c_uint32)

    ]


class struct_IotNtpServerInfo(Structure):
    _fields_ = [

        ('server_addr', (c_char * 64)),

        ('server_port', c_uint16),

        ('interval', c_int)

    ]


class union_IotTimingInfo(Union):
    _fields_ = [

        ('datetime', struct_IotDateTime),

        ('ntp', struct_IotNtpServerInfo)

    ]


class struct_IotTimingInfo(Structure):
    _fields_ = [

        ('type', c_int),

        ('anon_union', union_IotTimingInfo),

        ('dev_num', c_int),

        ('dev_list', ((c_char * 24) * 100))

    ]


class struct_IotDeviceTimingNotify(Structure):
    _fields_ = [

        ('error', c_int),

        ('dev_num', c_int),

        ('dev_list', ((c_char * 24) * 100)),

        ('dev_status', (c_int * 100))

    ]


class struct_IotDeviceUpgradeInfo(Structure):
    _fields_ = [

        ('file_url', (c_char * 512)),

        ('dev_num', c_int),

        ('dev_list', ((c_char * 24) * 100))

    ]


class struct_IotAlarmInConfig(Structure):
    _fields_ = [

        ('alarm_mode', c_uint8),

        ('enabled', c_uint8),

        ('res', (c_uint8 * 126))

    ]


class struct_IotAlarmOutConfig(Structure):
    _fields_ = [

        ('alarm_mode', c_uint8),

        ('delay_time', c_uint16),

        ('res', (c_uint8 * 61))

    ]


class struct_IotDeviceAlarmInfo(Structure):
    _pack_ = 1

    _fields_ = [

        ('timestamp', c_int64),

        ('dev_id', (c_char * 24)),

        ('chan_no', c_uint8),

        ('main_type', c_uint8),

        ('alarm_type', c_uint16),

        ('alarm_state', c_uint8),

        ('is_channel', c_uint8),

        ('capture_num', c_uint32),

        ('res', (c_uint8 * 28)),

        ('chan_id', (c_char * 24)),

        ('alarm_params', (c_char * 24))



    ]


class struct_IotFaceMatchAlarmInfo(Structure):
    _fields_ = [

        ('timestamp', c_int64),

        ('dev_id', (c_char * 24)),

        ('chan_no', c_uint8),

        ('similarity', c_uint8),

        ('face_id', c_uint32),

        ('blacklist_face_id', c_uint32),

        ('res', (c_uint8 * 86))

    ]


class struct_IotRecordSaveNotify(Structure):
    _fields_ = [

        ('error', c_int),

        ('dev_id', (c_char * 24)),

        ('sess_id', (c_char * 64)),

        ('file_url', (c_char * 512)),

        ('res', (c_uint8 * 36))

    ]


class struct_IotServerNodeInfo(Structure):
    _fields_ = [

        ('node_addr', (c_char * 32)),

        ('node_type', c_uint8),

        ('node_status', c_uint8),

        ('device_num', c_uint16),

        ('stream_in_num', c_uint16),

        ('stream_out_num', c_uint16),

        ('picture_per_hour', c_uint32),

        ('alarm_per_hour', c_uint32),

        ('res', (c_uint8 * 80))

    ]


class struct_IotDeviceCacheInfo(Structure):
    _fields_ = [

        ('server_addr', (c_char * 32)),

        ('server_port', c_uint16),

        ('cache_type', c_uint16),

        ('res', (c_uint8 * 28))

    ]


