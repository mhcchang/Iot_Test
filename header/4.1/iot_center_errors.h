/*******************************************************************************
 * @file        iot_center_errors.h
 * @brief       Error number definition file of iot-center project
 *
 * @authors     flowstar
 * @copyright   All rights reserved
 *
 * Modification History:
 * -----------------------------------------------------------------------------
 * Date        Author        Description
 * -----------------------------------------------------------------------------
 * 2019-01-25  flowstar      Create the file
 * 2020-01-02  flowstar      Add record cache errors
 * 2020-05-21  flowstar      Support international text
 *
 ******************************************************************************/
#ifndef _INCLUDE_IOT_CENTER_ERROR_TYPES__H_
#define _INCLUDE_IOT_CENTER_ERROR_TYPES__H_
#pragma once

#define IOT_LANG_NUM        2       ///< 支持的语言版本个数
#define IOT_LEN_ERR_TEXT    128     ///< 错误描述信息最大串长度

#define IOT_ERR_DEF(e, l0, l1)  { e, {l0, l1} }


/// 错误码国际化信息结构体定义
typedef struct IotErrorDef {
    int  code;
    char text[IOT_LANG_NUM][IOT_LEN_ERR_TEXT];
} IotErrorDef;


/// IoT平台错误码及其描述信息数组集合
static const IotErrorDef iot_errors[] = {
    // = common
#define IOT_ERR_UNSUPPORT_CODE  -1
    IOT_ERR_DEF(IOT_ERR_UNSUPPORT_CODE, "未识别的错误码", "Unsupport error code"),
#define IOT_ERR_SUCCESS         0
    IOT_ERR_DEF(IOT_ERR_SUCCESS, "成功", "Success"),

    // = SDK
#define IOT_ERR_UNKNOWN         1001
    IOT_ERR_DEF(IOT_ERR_UNKNOWN, "[IoT-sdk] 未知错误", "[IoT-sdk] Unknown error"),
#define IOT_ERR_INVALIDPARAM    1002
    IOT_ERR_DEF(IOT_ERR_INVALIDPARAM, "[IoT-sdk] 无效参数", "[IoT-sdk] Invalid parameter"),
#define IOT_ERR_NOMEM           1003
    IOT_ERR_DEF(IOT_ERR_NOMEM, "[IoT-sdk] 内存不足", "[IoT-sdk] Insufficient memory"),
#define IOT_ERR_UNSUPPORT       1004
    IOT_ERR_DEF(IOT_ERR_UNSUPPORT, "[IoT-sdk] 不支持的操作或函数", "[IoT-sdk] Unsupport operation or function"),
#define IOT_ERR_EXIST           1005
    IOT_ERR_DEF(IOT_ERR_EXIST, "[IoT-sdk] 设备或流已经被打开", "[IoT-sdk] Device or stream is already open"),
#define IOT_ERR_NOEXIST         1006
    IOT_ERR_DEF(IOT_ERR_NOEXIST, "[IoT-sdk] 设备或流不存在", "[IoT-sdk] Device or stream does not exist"),
#define IOT_ERR_LOGGEDIN        1007
    IOT_ERR_DEF(IOT_ERR_LOGGEDIN, "[IoT-sdk] 已经注册过", "[IoT-sdk] Already registered"),
#define IOT_ERR_NOLOGIN         1008
    IOT_ERR_DEF(IOT_ERR_NOLOGIN, "[IoT-sdk] 未注册", "[IoT-sdk] Not registered"),
#define IOT_ERR_SNDDATA         1009
    IOT_ERR_DEF(IOT_ERR_SNDDATA, "[IoT-sdk] 发送数据错误", "[IoT-sdk] Error sending data"),
#define IOT_ERR_RCVDATA         1010
    IOT_ERR_DEF(IOT_ERR_RCVDATA, "[IoT-sdk] 接收数据错误", "[IoT-sdk] Error receiving data"),
#define IOT_ERR_START           1011
    IOT_ERR_DEF(IOT_ERR_START, "[IoT-sdk] 启动出错", "[IoT-sdk] Failed to start"),
#define IOT_ERR_STOP            1012
    IOT_ERR_DEF(IOT_ERR_STOP, "[IoT-sdk] 停止出错", "[IoT-sdk] Failed to stop"),
#define IOT_ERR_CONNECT         1013
    IOT_ERR_DEF(IOT_ERR_CONNECT, "[IoT-sdk] 连接服务端失败", "[IoT-sdk] Failed to connect to service"),
#define IOT_ERR_BEGINTHREAD     1014
    IOT_ERR_DEF(IOT_ERR_BEGINTHREAD, "[IoT-sdk] 启动线程出错", "[IoT-sdk] Failed to start a thread"),
#define IOT_ERR_ENDTHREAD       1015
    IOT_ERR_DEF(IOT_ERR_ENDTHREAD, "[IoT-sdk] 停止线程出错", "[IoT-sdk] Failed to end a thread"),
#define IOT_ERR_UNSETCB         1016
    IOT_ERR_DEF(IOT_ERR_UNSETCB, "[IoT-sdk] 未设置回调函数", "[IoT-sdk] Callback function not set"),
#define IOT_ERR_SOCKET          1017
    IOT_ERR_DEF(IOT_ERR_SOCKET, "[IoT-sdk] 网络套接字错误", "[IoT-sdk] Socket error"),
#define IOT_ERR_USERINFO        1018
    IOT_ERR_DEF(IOT_ERR_USERINFO, "[IoT-sdk] 用户名或密码错误", "[IoT-sdk] Incorrect username or password"),
#define IOT_ERR_SERVERBUSY      1019
    IOT_ERR_DEF(IOT_ERR_SERVERBUSY, "[IoT-sdk] 服务端忙", "[IoT-sdk] Server busy"),
#define IOT_ERR_EXCEEDMAX       1020
    IOT_ERR_DEF(IOT_ERR_EXCEEDMAX, "[IoT-sdk] 超出最大值范围", "[IoT-sdk] Maximum value exceeded"),
#define IOT_ERR_TIMEOUT         1021
    IOT_ERR_DEF(IOT_ERR_TIMEOUT, "[IoT-sdk] 连接对端或命令操作超时", "[IoT-sdk] Connection or operation timed out"),
#define IOT_ERR_NOTFIND         1022
    IOT_ERR_DEF(IOT_ERR_NOTFIND, "[IoT-sdk] 未发现指定的设备或流", "[IoT-sdk] Specified device or stream not found"),
#define IOT_ERR_NORUN           1023
    IOT_ERR_DEF(IOT_ERR_NORUN, "[IoT-sdk] 命令操作未在运行中", "[IoT-sdk] The operation is not running"),
#define IOT_ERR_NOINIT          1024
    IOT_ERR_DEF(IOT_ERR_NOINIT, "[IoT-sdk] SDK未初始化", "[IoT-sdk] SDK uninitialized"),
#define IOT_ERR_SYSTEM          1025
    IOT_ERR_DEF(IOT_ERR_SYSTEM, "[IoT-sdk] 调用操作系统接口错误", "[IoT-sdk] Error in calling operating system API"),
#define IOT_ERR_UNMATCHINFO     1026
    IOT_ERR_DEF(IOT_ERR_UNMATCHINFO, "[IoT-sdk] 不匹配的设备所属信息：当前设备可能属于另一个平台", "[IoT-sdk] Device information mismatch: current device may belong to another platform"),
#define IOT_ERR_LEN_TOO_SHORT   1027
    IOT_ERR_DEF(IOT_ERR_LEN_TOO_SHORT, "[IoT-sdk] 分配的缓冲区长度太短", "[IoT-sdk] The allocated buffer length is too short"),

    // = MASTER
#define IOT_ERR_MASTER_NULL                 2001
    IOT_ERR_DEF(IOT_ERR_MASTER_NULL, "[IoT-master] 空指针错误", "[IoT-master] Null pointer exception"),
#define IOT_ERR_MASTER_DBQueryFail          2002
    IOT_ERR_DEF(IOT_ERR_MASTER_DBQueryFail, "[IoT-master] 数据库查询失败", "[IoT-master] Failed to query database"),
#define IOT_ERR_MASTER_NetError             2003
    IOT_ERR_DEF(IOT_ERR_MASTER_NetError, "[IoT-master] 网络错误", "[IoT-master] Network error"),
#define IOT_ERR_MASTER_NoData               2004
    IOT_ERR_DEF(IOT_ERR_MASTER_NoData, "[IoT-master] 未找到相应的数据", "[IoT-master] Corresponding data not found"),
#define IOT_ERR_MASTER_UserName             2005
    IOT_ERR_DEF(IOT_ERR_MASTER_UserName, "[IoT-master] 用户名错误", "[IoT-master] Incorrect username"),
#define IOT_ERR_MASTER_Password             2006
    IOT_ERR_DEF(IOT_ERR_MASTER_Password, "[IoT-master] 密码错误", "[IoT-master] Wrong password"),
#define IOT_ERR_MASTER_DevOccupied          2007
    IOT_ERR_DEF(IOT_ERR_MASTER_DevOccupied, "[IoT-master] 设备被占用", "[IoT-master] Device is already in use"),
#define IOT_ERR_MASTER_TypeMisMatch         2008
    IOT_ERR_DEF(IOT_ERR_MASTER_TypeMisMatch, "[IoT-master] 类型不匹配", "[IoT-master] Type mismatch"),
#define IOT_ERR_MASTER_ModuleOffline        2009
    IOT_ERR_DEF(IOT_ERR_MASTER_ModuleOffline, "[IoT-master] 模块离线", "[IoT-master] Module offline"),
#define IOT_ERR_MASTER_DeviceOffline        2010
    IOT_ERR_DEF(IOT_ERR_MASTER_DeviceOffline, "[IoT-master] 设备离线", "[IoT-master] Device offline"),
#define IOT_ERR_MASTER_NotFindProxy         2011
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindProxy, "[IoT-master] 找不到代理模块", "[IoT-master] No proxy module found"),
#define IOT_ERR_MASTER_NotFindStreamer      2012
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindStreamer, "[IoT-master] 找不到流媒体模块", "[IoT-master] No streaming media module found"),
#define IOT_ERR_MASTER_OpenDBFail           2013
    IOT_ERR_DEF(IOT_ERR_MASTER_OpenDBFail, "[IoT-master] 打开数据库失败", "[IoT-master] Failed to open database"),
#define IOT_ERR_MASTER_AddDataFail          2014
    IOT_ERR_DEF(IOT_ERR_MASTER_AddDataFail, "[IoT-master] 数据库添加数据失败", "[IoT-master] Failed to add data to database"),
#define IOT_ERR_MASTER_ModDataFail          2015
    IOT_ERR_DEF(IOT_ERR_MASTER_ModDataFail, "[IoT-master] 数据库数据查询失败", "[IoT-master] Failed to search data in database"),
#define IOT_ERR_MASTER_DelDataFail          2016
    IOT_ERR_DEF(IOT_ERR_MASTER_DelDataFail, "[IoT-master] 数据库数据删除失败", "[IoT-master] Failed to delete data from database"),
#define IOT_ERR_MASTER_Timeout              2017
    IOT_ERR_DEF(IOT_ERR_MASTER_Timeout, "[IoT-master] 命令超时", "[IoT-master] Command timed out"),
#define IOT_ERR_MASTER_CodeError            2018
    IOT_ERR_DEF(IOT_ERR_MASTER_CodeError, "[IoT-master] 编码错误", "[IoT-master] Encoding error"),
#define IOT_ERR_MASTER_ParserFail           2019
    IOT_ERR_DEF(IOT_ERR_MASTER_ParserFail, "[IoT-master] 消息解析失败", "[IoT-master] Failed to parse message"),
#define IOT_ERR_MASTER_ErrorMsg             2020
    IOT_ERR_DEF(IOT_ERR_MASTER_ErrorMsg, "[IoT-master] 消息内容不正确", "[IoT-master] Incorrect message content"),
#define IOT_ERR_MASTER_PlatID               2021
    IOT_ERR_DEF(IOT_ERR_MASTER_PlatID, "[IoT-master] 国标设备已添加到别的平台", "[IoT-master] The GB device has already been added to another platform"),
#define IOT_ERR_MASTER_GBModuleExist        2022
    IOT_ERR_DEF(IOT_ERR_MASTER_GBModuleExist, "[IoT-master] 国标模块已存在", "[IoT-master] GB module already exists"),
#define IOT_ERR_MASTER_VersionErr           2023
    IOT_ERR_DEF(IOT_ERR_MASTER_VersionErr, "[IoT-master] 当前设备厂商不支持版本信息查询", "[IoT-master] The current device manufacturer does not support the query of version information"),
#define IOT_ERR_MASTER_NoChange             2024
    IOT_ERR_DEF(IOT_ERR_MASTER_NoChange, "[IoT-master] 设备信息未变更", "[IoT-master] Device information is unchanged"),
#define IOT_ERR_MASTER_ChannelExist         2025
    IOT_ERR_DEF(IOT_ERR_MASTER_ChannelExist, "[IoT-master] 设备地址被占用", "[IoT-master] Device address is already in use"),
#define IOT_ERR_MASTER_IllegalDev           2026
    IOT_ERR_DEF(IOT_ERR_MASTER_IllegalDev, "[IoT-master] 升级操作中的某些设备是非法的", "[IoT-master] Some devices are not supported in a batch updating requests"),
#define IOT_ERR_MASTER_UpdateTypeErr        2027
    IOT_ERR_DEF(IOT_ERR_MASTER_UpdateTypeErr, "[IoT-master] 不支持设备类型变更", "[IoT-master] Changing of device type is not supported"),
#define IOT_ERR_MASTER_RegisterFail         2028
    IOT_ERR_DEF(IOT_ERR_MASTER_RegisterFail, "[IoT-master] 重复注册", "[IoT-master] Repeated registration"),
#define IOT_ERR_MASTER_StreamType           2029
    IOT_ERR_DEF(IOT_ERR_MASTER_StreamType, "[IoT-master] 请求流类型错误", "[IoT-master] Error in requesting stream type"),
#define IOT_ERR_MASTER_CacheNotOpen         2030
    IOT_ERR_DEF(IOT_ERR_MASTER_CacheNotOpen, "[IoT-master] 设备缓存未开启", "[IoT-master] Device cache is not enabled"),
#define IOT_ERR_MASTER_CacheRepeatOpen      2031
    IOT_ERR_DEF(IOT_ERR_MASTER_CacheRepeatOpen, "[IoT-master] 设备缓存已开启", "[IoT-master] Device cache is enabled"),
#define IOT_ERR_MASTER_CacheAlreadyClose    2032
    IOT_ERR_DEF(IOT_ERR_MASTER_CacheAlreadyClose, "[IoT-master] 设备缓存已关闭", "[IoT-master] Device cache is disabled"),
#define IOT_ERR_MASTER_RecordParamErr       2033
    IOT_ERR_DEF(IOT_ERR_MASTER_RecordParamErr, "[IoT-master] 录像周期参数错误", "[IoT-master] Recording cycle parameter error"),
#define IOT_ERR_MASTER_NotFindVendor        2034
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindVendor, "[IoT-master] 未找到动态添加的厂商", "[IoT-master] No dynamically added vendor found"),
#define IOT_ERR_MASTER_VendorBeUsed         2035
    IOT_ERR_DEF(IOT_ERR_MASTER_VendorBeUsed, "[IoT-master] 动态厂商被使用禁止删除", "[IoT-master] Dynamic vendors are prohibited from being deleted while in use"),
#define IOT_ERR_MASTER_VendorExist          2036
    IOT_ERR_DEF(IOT_ERR_MASTER_VendorExist, "[IoT-master] 动态厂商已存在", "[IoT-master] Dynamic vendor already exists"),
#define IOT_ERR_MASTER_ChannelMaximum       2037
    IOT_ERR_DEF(IOT_ERR_MASTER_ChannelMaximum, "[IoT-master] 超过最大通道上限", "[IoT-master] Maximum channel limit exceeded"),
#define IOT_ERR_MASTER_MutilDeviceNotExist  2038
    IOT_ERR_DEF(IOT_ERR_MASTER_MutilDeviceNotExist, "[IoT-master] 多通道设备信息不存在", "[IoT-master] Multi-channel device information does not exist"),
#define IOT_ERR_MASTER_BindMaximum          2039
    IOT_ERR_DEF(IOT_ERR_MASTER_BindMaximum, "[IoT-master] 达到模块绑定设备最大上限", "[IoT-master] Reached the maximum limit of module binding equipment"),
#define IOT_ERR_MASTER_NotFindGAProxy       2040
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindGAProxy, "[IoT-master] 未找到相应的GA接入代理", "[IoT-master] No corresponding GA access agent found"),
#define IOT_ERR_MASTER_GAModuleOffline      2041
    IOT_ERR_DEF(IOT_ERR_MASTER_GAModuleOffline , "[IoT-master] GA接入服务离线", "[IoT-master] GA access service offline"),
#define IOT_ERR_MASTER_RecordModuleOffline  2042
    IOT_ERR_DEF(IOT_ERR_MASTER_RecordModuleOffline , "[IoT-master] 录像服务离线", "[IoT-master] Recording service offline"),
#define IOT_ERR_MASTER_GBModuleOffline      2043
    IOT_ERR_DEF(IOT_ERR_MASTER_GBModuleOffline , "[IoT-master] GB接入服务离线", "[IoT-master] GB access service offline"),
#define IOT_ERR_MASTER_NotFindGBModule      2044
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindGBModule , "[IoT-master]  未找到相应的GB接入服务", "[IoT-master] No corresponding GB access service found"),
#define IOT_ERR_MASTER_TimeingDevIllegal    2045
    IOT_ERR_DEF(IOT_ERR_MASTER_TimeingDevIllegal , "[IoT-master]  设备校时部分ID非法", "[IoT-master] Some IDs are illegal during device calibration"),
#define IOT_ERR_MASTER_NotFindSensorProxy   2046
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindSensorProxy , "[IoT-master]  未找到相应的传感器接入代理", "[IoT-master] The corresponding sensor access agent was not found"),
#define IOT_ERR_MASTER_SensorProxyOffine    2047
    IOT_ERR_DEF(IOT_ERR_MASTER_SensorProxyOffine , "[IoT-master]  传感器接入代理离线", "[IoT-master] Sensor access agent offline"),
#define IOT_ERR_MASTER_NotFindCacheModule   2048
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindCacheModule , "[IoT-master]  未找到报警短视频接入服务", "[IoT-master] No corresponding alarm cache video access service was found"),
#define IOT_ERR_MASTER_NotFindPushModule    2049
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindPushModule , "[IoT-master]  未找到相应的推流服务", "[IoT-master] No corresponding push service found"),
#define IOT_ERR_MASTER_PushModuleOffline    2050
    IOT_ERR_DEF(IOT_ERR_MASTER_PushModuleOffline , "[IoT-master]  推流服务离线", "[IoT-master] Push streaming service offline"),
#define IOT_ERR_MASTER_NotFindRecordModule  2051
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindRecordModule , "[IoT-master]  未找到录像服务", "[IoT-master] No recording service found"),
#define IOT_ERR_MASTER_NotFindOnvifProxy    2052
    IOT_ERR_DEF(IOT_ERR_MASTER_NotFindOnvifProxy , "[IoT-master]  未找到onvif代理", "[IoT-master] Onvif proxy not found"),
#define IOT_ERR_MASTER_BaselibDevIllegal    2053
    IOT_ERR_DEF(IOT_ERR_MASTER_BaselibDevIllegal , "[IoT-master]  底库下发任务部分ID非法", "[IoT-master] Part of the ID issued by the library is illegal"),
#define IOT_ERR_MASTER_PlatformExist        2054
    IOT_ERR_DEF(IOT_ERR_MASTER_PlatformExist , "[IoT-master]  平台信息已存在", "[IoT-master] Platform information already exists"),
#define IOT_ERR_MASTER_PlatformOccupied     2055
    IOT_ERR_DEF(IOT_ERR_MASTER_PlatformOccupied , "[IoT-master]  平台被占用", "[IoT-master] Platform occupied"),
#define IOT_ERR_MASTER_BatchCfgDevIllegal   2056
    IOT_ERR_DEF(IOT_ERR_MASTER_BatchCfgDevIllegal , "[IoT-master]  批量设备设置任务部分ID非法", "[IoT-master] Partial ID of batch device setting task is illegal"),
#define IOT_ERR_MASTER_InputParam           2057
    IOT_ERR_DEF(IOT_ERR_MASTER_InputParam , "[IoT-master]  输入参数非法", "[IoT-master] Illegal input parameter"),


    // = GB-MANAGER
#define IOT_ERR_GBMANAGER_UNKNOWN       3001
    IOT_ERR_DEF(IOT_ERR_GBMANAGER_UNKNOWN, "[IoT-gb_manager] 未知通用错误", "[IoT-gb_manager] Unknown generic error"),
#define IOT_ERR_GBMANAGER_MEDIA_FAILURE 3002
    IOT_ERR_DEF(IOT_ERR_GBMANAGER_MEDIA_FAILURE, "[IoT-gb_manager] 开流下级未响应或响应4xx错误", "[IoT-gb_manager] Failed to open the video stream of inferior platform"),
#define IOT_ERR_GBMANAGER_TIMEOUT       3003
    IOT_ERR_DEF(IOT_ERR_GBMANAGER_TIMEOUT, "[IoT-gb_manager] 一般请求下级未响应", "[IoT-gb_manager] No response from inferior platform"),
#define IOT_ERR_GBMANAGER_REG_NOTFOUND  3004
    IOT_ERR_DEF(IOT_ERR_GBMANAGER_REG_NOTFOUND, "[IoT-gb_manager] 下级平台未向GB-Manager注册", "[IoT-gb_manager] Lower platform has not registered to GB-Manager"),
#define IOT_ERR_GBMANAGER_MSG_NOTFOUND  3005
    IOT_ERR_DEF(IOT_ERR_GBMANAGER_MSG_NOTFOUND, "[IoT-gb_manager] 无此相关的流媒体链路信息", "[IoT-gb_manager] No related streaming media link information"),
#define IOT_ERR_GBMANAGER_RCD_NOTFOUND  3006
    IOT_ERR_DEF(IOT_ERR_GBMANAGER_RCD_NOTFOUND, "[IoT-gb_manager] 下级平台无该相机录像", "[IoT-gb_manager] No recordings of this camera in inferior platform"),
#define IOT_ERR_GBMANAGER_CATALOG_NOTFOUND  3007
    IOT_ERR_DEF(IOT_ERR_GBMANAGER_CATALOG_NOTFOUND, "[IoT-gb_manager] 该异步查询不存在", "[IoT-gb_manager] No catalog of this session"),


    // = STREAMER
#define IOT_ERR_STREAMER_INNER_ERROR    4001
    IOT_ERR_DEF(IOT_ERR_STREAMER_INNER_ERROR, "[IoT-streamer] 未知错误", "[IoT-streamer] Unknown error"),
#define IOT_ERR_STREAMER_INVALIDPARAM   4002
    IOT_ERR_DEF(IOT_ERR_STREAMER_INVALIDPARAM, "[IoT-streamer] 无效参数", "[IoT-streamer] Invalid parameter"),
#define IOT_ERR_STREAMER_MISS_PARAM     4003
    IOT_ERR_DEF(IOT_ERR_STREAMER_MISS_PARAM, "[IoT-streamer] 参数缺失", "[IoT-streamer] Missing parameter"),
#define IOT_ERR_STREAMER_UNKNOWN_COMMAND 4004
    IOT_ERR_DEF(IOT_ERR_STREAMER_UNKNOWN_COMMAND, "[IoT-streamer] 不支持的操作", "[IoT-streamer] Unsupported operation"),
#define IOT_ERR_STREAMER_NO_MEMORY      4005
    IOT_ERR_DEF(IOT_ERR_STREAMER_NO_MEMORY, "[IoT-streamer] 内存不足", "[IoT-streamer] Insufficient memory"),
#define IOT_ERR_STREAMER_STREAM_NOT_FOUND 4006
    IOT_ERR_DEF(IOT_ERR_STREAMER_STREAM_NOT_FOUND, "[IoT-streamer] 媒体流不存在", "[IoT-streamer] Media stream does not exist"),

    // = PROXY
#define IOT_ERR_PROXY_UNKNOWN           5001
    IOT_ERR_DEF(IOT_ERR_PROXY_UNKNOWN, "[IoT-proxy] 未知错误", "[IoT-proxy] Unknown error"),
#define IOT_ERR_PROXY_INVALIDPARAM      5002
    IOT_ERR_DEF(IOT_ERR_PROXY_INVALIDPARAM, "[IoT-proxy] 无效参数", "[IoT-proxy] Invalid parameter"),
#define IOT_ERR_PROXY_NOMEM             5003
    IOT_ERR_DEF(IOT_ERR_PROXY_NOMEM, "[IoT-proxy] 内存不足", "[IoT-proxy] Insufficient memory"),
#define IOT_ERR_PROXY_UNSUPPORT         5004
    IOT_ERR_DEF(IOT_ERR_PROXY_UNSUPPORT, "[IoT-proxy] 不支持的操作或函数", "[IoT-proxy] Unsupport operation or function"),
#define IOT_ERR_PROXY_EXIST             5005
    IOT_ERR_DEF(IOT_ERR_PROXY_EXIST, "[IoT-proxy] 设备或流已存在", "[IoT-proxy] Device or stream is already exist"),
#define IOT_ERR_PROXY_NOEXIST           5006
    IOT_ERR_DEF(IOT_ERR_PROXY_NOEXIST, "[IoT-proxy] 设备或流不存在", "[IoT-proxy] Device or stream does not exist"),
#define IOT_ERR_PROXY_NO_IDLE_PORT      5007
    IOT_ERR_DEF(IOT_ERR_PROXY_NO_IDLE_PORT, "[IoT-proxy] 获取空闲端口失败", "[IoT-proxy] Get idle port failed"),
#define IOT_ERR_PROXY_NOLOGIN           5008
    IOT_ERR_DEF(IOT_ERR_PROXY_NOLOGIN, "[IoT-proxy] 未登录", "[IoT-proxy] Not logged in"),
#define IOT_ERR_PROXY_SNDDATA           5009
    IOT_ERR_DEF(IOT_ERR_PROXY_SNDDATA, "[IoT-proxy] 发送数据错误", "[IoT-proxy] Error sending data"),
#define IOT_ERR_PROXY_RCVDATA           5010
    IOT_ERR_DEF(IOT_ERR_PROXY_RCVDATA, "[IoT-proxy] 接收数据错误", "[IoT-proxy] Error receiving data"),
#define IOT_ERR_PROXY_START             5011
    IOT_ERR_DEF(IOT_ERR_PROXY_START, "[IoT-proxy] 启动出错", "[IoT-proxy] Failed to start"),
#define IOT_ERR_PROXY_STOP              5012
    IOT_ERR_DEF(IOT_ERR_PROXY_STOP, "[IoT-proxy] 停止出错", "[IoT-proxy] Failed to stop"),
#define IOT_ERR_PROXY_CONNECT           5013
    IOT_ERR_DEF(IOT_ERR_PROXY_CONNECT, "[IoT-proxy] 连接服务端失败", "[IoT-proxy] Failed to connect to service"),
#define IOT_ERR_PROXY_BEGINTHREAD       5014
    IOT_ERR_DEF(IOT_ERR_PROXY_BEGINTHREAD, "[IoT-proxy] 启动线程出错", "[IoT-proxy] Failed to start a thread"),
#define IOT_ERR_PROXY_ENDTHREAD         5015
    IOT_ERR_DEF(IOT_ERR_PROXY_ENDTHREAD, "[IoT-proxy] 停止线程出错", "[IoT-proxy] Failed to end a thread"),
#define IOT_ERR_PROXY_UNSUPPORT_STREAM  5016
    IOT_ERR_DEF(IOT_ERR_PROXY_UNSUPPORT_STREAM, "[IoT-proxy] 不支持的媒体流格式", "[IoT-proxy] Unsupported media streaming format"),
#define IOT_ERR_PROXY_SOCKET            5017
    IOT_ERR_DEF(IOT_ERR_PROXY_SOCKET, "[IoT-proxy] 网络套接字错误", "[IoT-proxy] Socket error"),
#define IOT_ERR_PROXY_USERINFO          5018
    IOT_ERR_DEF(IOT_ERR_PROXY_USERINFO, "[IoT-proxy] 用户名或密码错误", "[IoT-proxy] Incorrect username or password"),
#define IOT_ERR_PROXY_SERVERBUSY        5019
    IOT_ERR_DEF(IOT_ERR_PROXY_SERVERBUSY, "[IoT-proxy] 服务端忙", "[IoT-proxy] Server busy"),
#define IOT_ERR_PROXY_EXCEEDMAX         5020
    IOT_ERR_DEF(IOT_ERR_PROXY_EXCEEDMAX, "[IoT-proxy] 超出最大值范围", "[IoT-proxy] Maximum value exceeded"),
#define IOT_ERR_PROXY_TIMEOUT           5021
    IOT_ERR_DEF(IOT_ERR_PROXY_TIMEOUT, "[IoT-proxy] 连接对端或命令操作超时", "[IoT-proxy] Connection or operation timed out"),
#define IOT_ERR_PROXY_SDKAPI            5022
    IOT_ERR_DEF(IOT_ERR_PROXY_SDKAPI, "[IoT-proxy] 调用设备SDK接口错误", "[IoT-proxy] Error in while calling device SDK API"),
#define IOT_ERR_PROXY_DEV_OFFLINE       5023
    IOT_ERR_DEF(IOT_ERR_PROXY_DEV_OFFLINE, "[IoT-proxy] 设备掉线", "[IoT-proxy] Device offline"),
#define IOT_ERR_PROXY_TIMING            5024
    IOT_ERR_DEF(IOT_ERR_PROXY_TIMING, "[IoT-proxy] 设备校时出错", "[IoT-proxy] Device timing error"),
#define IOT_ERR_PROXY_GET_DEVICE_INFO   5025
    IOT_ERR_DEF(IOT_ERR_PROXY_GET_DEVICE_INFO, "[IoT-proxy] 获取设备信息出错", "[IoT-proxy] Error getting device information"),
#define IOT_ERR_PROXY_GET_CAPABILITIES  5026
    IOT_ERR_DEF(IOT_ERR_PROXY_GET_CAPABILITIES, "[IoT-proxy] 获取设备能力出错", "[IoT-proxy] Error getting device capabilities"),
#define IOT_ERR_PROXY_GET_PROFILES      5027
    IOT_ERR_DEF(IOT_ERR_PROXY_GET_PROFILES, "[IoT-proxy] 获取设备配置出错", "[IoT-proxy] Error getting device profiles"),
#define IOT_ERR_PROXY_GET_STREAM_URL    5028
    IOT_ERR_DEF(IOT_ERR_PROXY_GET_STREAM_URL, "[IoT-proxy] 获取设备RTSP URL出错", "[IoT-proxy] Error getting device rtsp url"),
#define IOT_ERR_PROXY_PTZ_CONTROL       5029
    IOT_ERR_DEF(IOT_ERR_PROXY_PTZ_CONTROL, "[IoT-proxy] 云台控制失败", "[IoT-proxy] Error in ptz control"),
#define IOT_ERR_PROXY_DOWNLOAD_FILE     5030
    IOT_ERR_DEF(IOT_ERR_PROXY_DOWNLOAD_FILE, "[IoT-proxy] 下载文件失败", "[IoT-proxy] Failed to download file"),
#define IOT_ERR_PROXY_OPEN_FILE         5031
    IOT_ERR_DEF(IOT_ERR_PROXY_OPEN_FILE, "[IoT-proxy] 打开文件失败", "[IoT-proxy] Failed to open file"),
#define IOT_ERR_PROXY_CREATE_DIR        5032
    IOT_ERR_DEF(IOT_ERR_PROXY_CREATE_DIR, "[IoT-proxy] 创建本地目录失败", "[IoT-proxy] Failed to create directory"),
#define IOT_ERR_PROXY_GET_DATA          5033
    IOT_ERR_DEF(IOT_ERR_PROXY_GET_DATA, "[IoT-proxy] 获取数据失败", "[IoT-proxy] Failed to get data"),
#define IOT_ERR_PROXY_UZIP_FILE         5034
    IOT_ERR_DEF(IOT_ERR_PROXY_UZIP_FILE, "[IoT-proxy] 文件解压失败", "[IoT-proxy] Failed to uzip file"),
#define IOT_ERR_PROXY_RAISE_PERMISSION  5035
    IOT_ERR_DEF(IOT_ERR_PROXY_RAISE_PERMISSION, "[IoT-proxy] 提升文件权限失败", "[IoT-proxy] Failed to raise file permissions"),
#define IOT_ERR_PROXY_PARSE_FILE        5036
    IOT_ERR_DEF(IOT_ERR_PROXY_PARSE_FILE, "[IoT-proxy] 解析文件失败", "[IoT-proxy] Failed to parse file"),
#define IOT_ERR_PROXY_SUSPEND_ALG       5037
    IOT_ERR_DEF(IOT_ERR_PROXY_SUSPEND_ALG, "[IoT-proxy] 暂停设备算法失败", "[IoT-proxy] Failed to suspend device algorithm"),
#define IOT_ERR_PROXY_CREATE_BASELIB    5038
    IOT_ERR_DEF(IOT_ERR_PROXY_CREATE_BASELIB, "[IoT-proxy] 创建底库失败", "[IoT-proxy] Failed to create base library"),
#define IOT_ERR_PROXY_ALREALDY_CLOSED   5039
    IOT_ERR_DEF(IOT_ERR_PROXY_ALREALDY_CLOSED, "[IoT-proxy] 该设备发现已由服务自动关闭", "[IoT-proxy] This device discovery already closed by server"),
#define IOT_ERR_PROXY_PARSE_DATA        5040
    IOT_ERR_DEF(IOT_ERR_PROXY_PARSE_DATA, "[IoT-proxy] 数据解析失败", "[IoT-proxy] Failed to parse data"),
#define IOT_ERR_PROXY_NO_AUTH  5041
    IOT_ERR_DEF(IOT_ERR_PROXY_NO_AUTH, "[IoT-proxy] 设备鉴权失败", "[IoT-proxy] No authority"),

// = HTTP API
#define IOT_ERR_HTTP_UNKNOWN_URL        6001
    IOT_ERR_DEF(IOT_ERR_HTTP_UNKNOWN_URL, "[IoT-http_api] 不支持的请求", "[IoT-http_api] Unsupported request"),
#define IOT_ERR_HTTP_IOT_OFFLINE        6002
    IOT_ERR_DEF(IOT_ERR_HTTP_IOT_OFFLINE, "[IoT-http_api] 达尔文服务离线", "[IoT-http_api] IoT service is offline"),
#define IOT_ERR_HTTP_INVALIDPARAM       6003
    IOT_ERR_DEF(IOT_ERR_HTTP_INVALIDPARAM, "[IoT-http_api] 无效参数", "[IoT-http_api] Invalid parameter"),
#define IOT_ERR_HTTP_NOMEM              6004
    IOT_ERR_DEF(IOT_ERR_HTTP_NOMEM, "[IoT-http_api] 内存不足", "[IoT-http_api] Insufficient memory"),
#define IOT_ERR_HTTP_UNSUPPORT          6005
    IOT_ERR_DEF(IOT_ERR_HTTP_UNSUPPORT, "[IoT-http_api] 操作不支持", "[IoT-http_api] Operation not supported"),
#define IOT_ERR_HTTP_EXIST              6006
    IOT_ERR_DEF(IOT_ERR_HTTP_EXIST, "[IoT-http_api] 设备已存在", "[IoT-http_api] Device already exist"),
#define IOT_ERR_HTTP_NOEXIST            6007
    IOT_ERR_DEF(IOT_ERR_HTTP_NOEXIST, "[IoT-http_api] 设备不存在", "[IoT-http_api] Device does not exist"),
#define IOT_ERR_HTTP_RTMP               6008
    IOT_ERR_DEF(IOT_ERR_HTTP_RTMP, "[IoT-http_api] RTMP服务启动失败", "[IoT-http_api] Failed to start RTMP server"),
#define IOT_ERR_HTTP_TIMEOUT            6009
    IOT_ERR_DEF(IOT_ERR_HTTP_TIMEOUT, "[IoT-http_api] 异步调用超时", "[IoT-http_api] Asynchronous call timed out"),
#define IOT_ERR_HTTP_EXCEEDLIMIT        6010
    IOT_ERR_DEF(IOT_ERR_HTTP_EXCEEDLIMIT, "[IoT-http_api] 超过最大查询限制", "[IoT-http_api] Maximum query limit exceeded"),
#define IOT_ERR_HTTP_KAFKA_ERROR        6011
    IOT_ERR_DEF(IOT_ERR_HTTP_KAFKA_ERROR, "[IoT-http_api] 连接kafka失败", "[IoT-http_api] Start kafka producer error"),
#define IOT_ERR_HTTP_ONVIF_BUSY         6012
    IOT_ERR_DEF(IOT_ERR_HTTP_ONVIF_BUSY, "[IoT-http_api] Onvif探测正在进行中", "[IoT-http_api] Onvif discovery is busy"),
#define IOT_ERR_HTTP_INVALID_PLAT         6013
    IOT_ERR_DEF(IOT_ERR_HTTP_INVALID_PLAT, "[IoT-http_api] 不支持的平台类型", "[IoT-http_api] Unsupported platform type"),

    // = GA READER
#define IOT_ERR_GAR_UNKNOWN_URL         7001
    IOT_ERR_DEF(IOT_ERR_GAR_UNKNOWN_URL, "[IoT-gar] 不支持的请求", "[IoT-gar] Unsupported request"),
#define IOT_ERR_GAR_INVALIDPARAM        7002
    IOT_ERR_DEF(IOT_ERR_GAR_INVALIDPARAM, "[IoT-gar] 无效参数", "[IoT-gar] Invalid parameter"),
#define IOT_ERR_GAR_NOMEM               7003
    IOT_ERR_DEF(IOT_ERR_GAR_NOMEM, "[IoT-gar] 内存不足", "[IoT-gar] Insufficient memory"),
#define IOT_ERR_GAR_UNSUPPORT           7004
    IOT_ERR_DEF(IOT_ERR_GAR_UNSUPPORT, "[IoT-gar] 操作不支持", "[IoT-gar] Operation not supported"),
#define IOT_ERR_GAR_EXIST               7005
    IOT_ERR_DEF(IOT_ERR_GAR_EXIST, "[IoT-gar] 设备已存在", "[IoT-gar] Device already exists"),
#define IOT_ERR_GAR_NOEXIST             7006
    IOT_ERR_DEF(IOT_ERR_GAR_NOEXIST, "[IoT-gar] 设备不存在", "[IoT-gar] Device does not exist"),
#define IOT_ERR_GAR_VIIDERROR           7007
    IOT_ERR_DEF(IOT_ERR_GAR_VIIDERROR, "[IoT-gar] 视图库错误", "[IoT-gar] VIID error"),
#define IOT_ERR_GAR_SESSION_NOEXIST     7008
    IOT_ERR_DEF(IOT_ERR_GAR_SESSION_NOEXIST, "[IoT-gar] 会话不存在", "[IoT-gar] Session not exists"),
    
    // = VIDEO CACHE & RECORD
#define IOT_ERR_RECORD_UNKNOWN_INTERNAL 8001
    IOT_ERR_DEF(IOT_ERR_RECORD_UNKNOWN_INTERNAL, "[IoT-record] 未知错误", "[IoT-record] Unknown error"),
#define IOT_ERR_RECORD_SQLITE           8002
    IOT_ERR_DEF(IOT_ERR_RECORD_SQLITE, "[IoT-record] 数据库错误", "[IoT-record] Database error"),
#define IOT_ERR_RECORD_INVALIDPARAM     8003
    IOT_ERR_DEF(IOT_ERR_RECORD_INVALIDPARAM, "[IoT-record] 无效参数", "[IoT-record] Invalid parameter"),
#define IOT_ERR_RECORD_FILE             8004
    IOT_ERR_DEF(IOT_ERR_RECORD_FILE, "[IoT-record] 文件操作错误", "[IoT-record] File operation error"),
#define IOT_ERR_RECORD_SPACE_FULL       8005
    IOT_ERR_DEF(IOT_ERR_RECORD_SPACE_FULL, "[IoT-record] 分配空间已满", "[IoT-record] Allocated space is full"),
#define IOT_ERR_RECORD_NO_RECORD_READ   8006
    IOT_ERR_DEF(IOT_ERR_RECORD_NO_RECORD_READ, "[IoT-record] 指定时间无录像", "[IoT-record] No recording for the specified time"),
#define IOT_ERR_RECORD_DEV_USING        8007
    IOT_ERR_DEF(IOT_ERR_RECORD_DEV_USING, "[IoT-record] 设备占用中，无法删除", "[IoT-record] The device is in use and cannot be deleted"),
#define IOT_ERR_RECORD_RECORD_EXIST     8008
    IOT_ERR_DEF(IOT_ERR_RECORD_RECORD_EXIST, "[IoT-record] 录像已开启", "[IoT-record] Recording has started"),
#define IOT_ERR_RECORD_DEV_NOEXIST      8009
    IOT_ERR_DEF(IOT_ERR_RECORD_DEV_NOEXIST, "[IoT-record] 设备不存在", "[IoT-record] Device does not exist"),
#define IOT_ERR_RECORD_CON_OS           8010
    IOT_ERR_DEF(IOT_ERR_RECORD_CON_OS, "[IoT-record] 连接到存储系统失败", "[IoT-record] Failed to connect to object-storage"),
#define IOT_ERR_RECORD_OS_SOCKET        8011
    IOT_ERR_DEF(IOT_ERR_RECORD_OS_SOCKET, "[IoT-record] 存储系统网络错误", "[IoT-record] Object-storage network error"),
#define IOT_ERR_RECORD_OS_REPLY         8012
    IOT_ERR_DEF(IOT_ERR_RECORD_OS_REPLY, "[IoT-record] 存储系统回复错误", "[IoT-record] Object-storage response error"),
#define IOT_ERR_RECORD_OS_ERROR         8013
        IOT_ERR_DEF(IOT_ERR_RECORD_OS_ERROR, "[IoT-record] 保存到存储系统失败", "[IoT-record] Object-storage save error"),
#define IOT_ERR_RECORD_EXCEED_MAX       8014
    IOT_ERR_DEF(IOT_ERR_RECORD_EXCEED_MAX, "[IoT-record] 录像通道数超过最大值", "[IoT-record] The number of record exceeds the maximum"),
#define IOT_ERR_RECORD_SEND_STREAM_SOCKET 8015
    IOT_ERR_DEF(IOT_ERR_RECORD_SEND_STREAM_SOCKET, "[IoT-record] 流发送错误", "[IoT-record] Stream send error"),
#define IOT_ERR_RECORD_NO_MATCH_STREAM  8016
    IOT_ERR_DEF(IOT_ERR_RECORD_NO_MATCH_STREAM, "[IoT-record] 没有找到对应的流", "[IoT-record] No matching stream"),

    // = Capture Pusher
#define IOT_ERR_CAPTURE_INNER_ERROR     9001
    IOT_ERR_DEF(IOT_ERR_CAPTURE_INNER_ERROR, "[IoT-capture] 未知错误", "[IoT-capture] Unknown error"),
#define IOT_ERR_CAPTURE_PARAM           9002
    IOT_ERR_DEF(IOT_ERR_CAPTURE_PARAM, "[IoT-capture] 无效参数", "[IoT-capture] Invalid parameter"),
#define IOT_ERR_CAPTURE_MISS_PARAM      9003
    IOT_ERR_DEF(IOT_ERR_CAPTURE_MISS_PARAM, "[IoT-capture] 参数缺失", "[IoT-capture] Missing parameter"),
#define IOT_ERR_CAPTURE_SDK_ERROR       9004
    IOT_ERR_DEF(IOT_ERR_CAPTURE_SDK_ERROR, "[IoT-capture] SDK调用失败", "[IoT-capture] Failed to call SDK"),
#define IOT_ERR_CAPTURE_GAID_NOT_EXIST  9005
    IOT_ERR_DEF(IOT_ERR_CAPTURE_GAID_NOT_EXIST, "[IoT-capture] 未配置ga_id信息", "[IoT-capture] ga_id not exist"),
    
    // = cvserver
#define IOT_ERR_CVSERVER_INNER_ERROR     11003
    IOT_ERR_DEF(IOT_ERR_CVSERVER_INNER_ERROR, "[IoT-cvserver] 未知错误", "[IoT-cvserver] Unknown error"),
#define IOT_ERR_CVSERVER_PARAM           11004
    IOT_ERR_DEF(IOT_ERR_CVSERVER_PARAM, "[IoT-cvserver] 无效参数", "[IoT-cvserver] Invalid parameter"),
#define IOT_ERR_CVSERVER_MISS_PARAM      11005
    IOT_ERR_DEF(IOT_ERR_CVSERVER_MISS_PARAM, "[IoT-cvserver] 参数缺失", "[IoT-cvserver] Missing parameter"),
#define IOT_ERR_CVSERVER_SDK_ERROR       11006
    IOT_ERR_DEF(IOT_ERR_CVSERVER_SDK_ERROR, "[IoT-cvserver] SDK调用失败", "[IoT-cvserver] Failed to call SDK"),    
};

/// 错误返回值类型列表
typedef enum IotErrorType
{
    // 说明：v4.0后支持错误描述信息的国际化功能，为保持错误码及描述信息维护时的一致性（不容易遗漏），
    // 现将其更改为宏，并统一提取到上面的错误码数组定义中
    IOT_ERR_PLACEHOLDER
#if 0
    IOT_ERR_SUCCESS                 = 0,                    ///< Success
    
    // = SDK
    IOT_ERR_STARTNO                 = 1000,                 ///< Start number of SDK
    IOT_ERR_UNKNOWN                 = IOT_ERR_STARTNO + 1,  ///< Unknown error
    IOT_ERR_INVALIDPARAM            = IOT_ERR_STARTNO + 2,  ///< Invalid parameters
    IOT_ERR_NOMEM                   = IOT_ERR_STARTNO + 3,  ///< Out of memory
    IOT_ERR_UNSUPPORT               = IOT_ERR_STARTNO + 4,  ///< Unsupport operation or function
    IOT_ERR_EXIST                   = IOT_ERR_STARTNO + 5,  ///< The device or stream already exist
    IOT_ERR_NOEXIST                 = IOT_ERR_STARTNO + 6,  ///< The device or stream isnot exist
    IOT_ERR_LOGGEDIN                = IOT_ERR_STARTNO + 7,  ///< Already registered
    IOT_ERR_NOLOGIN                 = IOT_ERR_STARTNO + 8,  ///< No registered
    IOT_ERR_SNDDATA                 = IOT_ERR_STARTNO + 9,  ///< Send data error
    IOT_ERR_RCVDATA                 = IOT_ERR_STARTNO + 10, ///< Receive data error
    IOT_ERR_START                   = IOT_ERR_STARTNO + 11, ///< Failed to start
    IOT_ERR_STOP                    = IOT_ERR_STARTNO + 12, ///< Failed to stop
    IOT_ERR_CONNECT                 = IOT_ERR_STARTNO + 13, ///< Connect server failed
    IOT_ERR_BEGINTHREAD             = IOT_ERR_STARTNO + 14, ///< Failed to begin thread
    IOT_ERR_ENDTHREAD               = IOT_ERR_STARTNO + 15, ///< Failed to end thread
    IOT_ERR_UNSETCB                 = IOT_ERR_STARTNO + 16, ///< Not set callback function
    IOT_ERR_SOCKET                  = IOT_ERR_STARTNO + 17, ///< Socket error
    IOT_ERR_USERINFO                = IOT_ERR_STARTNO + 18, ///< Username or password error
    IOT_ERR_SERVERBUSY              = IOT_ERR_STARTNO + 19, ///< Server busy
    IOT_ERR_EXCEEDMAX               = IOT_ERR_STARTNO + 20, ///< Exceed the max value
    IOT_ERR_TIMEOUT                 = IOT_ERR_STARTNO + 21, ///< Connection or operation timed out
    IOT_ERR_NOTFIND                 = IOT_ERR_STARTNO + 22, ///< Not find the specified device or stream
    IOT_ERR_NORUN                   = IOT_ERR_STARTNO + 23, ///< The operation is not running
    IOT_ERR_NOINIT                  = IOT_ERR_STARTNO + 24, ///< The sdk is not startup
    IOT_ERR_SYSTEM                  = IOT_ERR_STARTNO + 25, ///< Call system api error
    IOT_ERR_UNMATCHINFO             = IOT_ERR_STARTNO + 26, ///< Unmatched device info: maybe the device belongs to another platform

    // = MASTER
    IOT_ERR_MASTER_STARTNO          = 2000,                         ///< Start number of master
    IOT_ERR_MASTER_NULL             = IOT_ERR_MASTER_STARTNO + 1,   ///< The pointer is null
    IOT_ERR_MASTER_DBQueryFail      = IOT_ERR_MASTER_STARTNO + 2,   ///< Database query failed
    IOT_ERR_MASTER_NetError         = IOT_ERR_MASTER_STARTNO + 3,   ///< Network error
    IOT_ERR_MASTER_NoData           = IOT_ERR_MASTER_STARTNO + 4,   ///< No matching data
    IOT_ERR_MASTER_UserName         = IOT_ERR_MASTER_STARTNO + 5,   ///< Username error
    IOT_ERR_MASTER_Password         = IOT_ERR_MASTER_STARTNO + 6,   ///< Password error
    IOT_ERR_MASTER_DevOccupied      = IOT_ERR_MASTER_STARTNO + 7,   ///< Device is occupied
    IOT_ERR_MASTER_TypeMisMatch     = IOT_ERR_MASTER_STARTNO + 8,   ///< Type mismatch
    IOT_ERR_MASTER_ModuleOffline    = IOT_ERR_MASTER_STARTNO + 9,   ///< Module offline
    IOT_ERR_MASTER_DeviceOffline    = IOT_ERR_MASTER_STARTNO + 10,  ///< Device offline
    IOT_ERR_MASTER_NotFindProxy     = IOT_ERR_MASTER_STARTNO + 11,  ///< The corresponding proxy not found
    IOT_ERR_MASTER_NotFindStreamer  = IOT_ERR_MASTER_STARTNO + 12,  ///< The corresponding streamer not found
    IOT_ERR_MASTER_OpenDBFail       = IOT_ERR_MASTER_STARTNO + 13,  ///< Open database failed
    IOT_ERR_MASTER_AddDataFail      = IOT_ERR_MASTER_STARTNO + 14,  ///< Add data to database failed
    IOT_ERR_MASTER_ModDataFail      = IOT_ERR_MASTER_STARTNO + 15,  ///< Modify data from database failed
    IOT_ERR_MASTER_DelDataFail      = IOT_ERR_MASTER_STARTNO + 16,  ///< Delete data from database failed
    IOT_ERR_MASTER_Timeout          = IOT_ERR_MASTER_STARTNO + 17,  ///< Command timeout
    IOT_ERR_MASTER_CodeError        = IOT_ERR_MASTER_STARTNO + 18,  ///< Encode error
    IOT_ERR_MASTER_ParserFail       = IOT_ERR_MASTER_STARTNO + 19,  ///< Message parsing failed
    IOT_ERR_MASTER_ErrorMsg         = IOT_ERR_MASTER_STARTNO + 20,  ///< Incorrect message content
    IOT_ERR_MASTER_PlatID           = IOT_ERR_MASTER_STARTNO + 21,  ///< The GB device already belonged to other platform
    IOT_ERR_MASTER_GBModuleExist    = IOT_ERR_MASTER_STARTNO + 22,  ///< The GB module already exist
    IOT_ERR_MASTER_VersionErr       = IOT_ERR_MASTER_STARTNO + 23,  ///< Not support current device vendors to query version information
    IOT_ERR_MASTER_NoChange        	= IOT_ERR_MASTER_STARTNO + 24,  ///< The update request failed because of the same device info
    IOT_ERR_MASTER_ChannelExist     = IOT_ERR_MASTER_STARTNO + 25,  ///< The device IP address is occupied
    IOT_ERR_MASTER_IllegalDev       = IOT_ERR_MASTER_STARTNO + 26,  ///< Some devices in the upgrade operation are illegal
    IOT_ERR_MASTER_UpdateTypeErr    = IOT_ERR_MASTER_STARTNO + 27,  ///< Device type change is not supported
    IOT_ERR_MASTER_RegisterFail     = IOT_ERR_MASTER_STARTNO + 28,  ///< Repeat registration
    IOT_ERR_MASTER_StreamType       = IOT_ERR_MASTER_STARTNO + 29,  ///< Request stream type error
    IOT_ERR_MASTER_CacheNotOpen     = IOT_ERR_MASTER_STARTNO + 30,  ///< Device cache is not opened
    IOT_ERR_MASTER_CacheRepeatOpen  = IOT_ERR_MASTER_STARTNO + 31,  ///< Device cache is opened
    IOT_ERR_MASTER_CacheAlreadyClose= IOT_ERR_MASTER_STARTNO + 32,  ///< Device cache is closed
    IOT_ERR_MASTER_RecordParamErr   = IOT_ERR_MASTER_STARTNO + 33,  ///< Record period error

    // = GB-MANAGER
    IOT_ERR_GBMANAGER_STARTNO       = 3000,                             ///< Start number of gb-manager
    IOT_ERR_GBMANAGER_UNKNOWN       = IOT_ERR_GBMANAGER_STARTNO + 1,    ///< General error
    IOT_ERR_GBMANAGER_MEDIA_FAILURE = IOT_ERR_GBMANAGER_STARTNO + 2,    ///< Media failure
    IOT_ERR_GBMANAGER_TIMEOUT       = IOT_ERR_GBMANAGER_STARTNO + 3,    ///< Request timed out
    IOT_ERR_GBMANAGER_REG_NOTFOUND  = IOT_ERR_GBMANAGER_STARTNO + 4,    ///< PlatformId not found in register list
    IOT_ERR_GBMANAGER_MSG_NOTFOUND  = IOT_ERR_GBMANAGER_STARTNO + 5,    ///< Message identify not found in message cache
    IOT_ERR_GBMANAGER_RCD_NOTFOUND  = IOT_ERR_GBMANAGER_STARTNO + 6,    ///< Record not found
    
    // = STREAMER
    IOT_ERR_STREAMER_STARTNO            = 4000,                         ///< Start number of streamer
    IOT_ERR_STREAMER_INNER_ERROR        = IOT_ERR_STREAMER_STARTNO + 1, ///< Inner error
    IOT_ERR_STREAMER_INVALIDPARAM       = IOT_ERR_STREAMER_STARTNO + 2, ///< Invalid parameters
    IOT_ERR_STREAMER_MISS_PARAM         = IOT_ERR_STREAMER_STARTNO + 3, ///< Miss parameters
    IOT_ERR_STREAMER_UNKNOWN_COMMAND    = IOT_ERR_STREAMER_STARTNO + 4, ///< Unknown command
    IOT_ERR_STREAMER_NO_MEMORY          = IOT_ERR_STREAMER_STARTNO + 5, ///< No memory
    IOT_ERR_STREAMER_STREAM_NOT_FOUND   = IOT_ERR_STREAMER_STARTNO + 6, ///< Stream not found

    // = PROXY
    IOT_ERR_PROXY_STARTNO               = 5000,                         ///< Start number of xxx-proxy
    IOT_ERR_PROXY_UNKNOWN               = IOT_ERR_PROXY_STARTNO + 1,    ///< Unknown error
    IOT_ERR_PROXY_INVALIDPARAM          = IOT_ERR_PROXY_STARTNO + 2,    ///< Invalid parameters
    IOT_ERR_PROXY_NOMEM                 = IOT_ERR_PROXY_STARTNO + 3,    ///< Out of memory
    IOT_ERR_PROXY_UNSUPPORT             = IOT_ERR_PROXY_STARTNO + 4,    ///< Unsupport operation or function
    IOT_ERR_PROXY_EXIST                 = IOT_ERR_PROXY_STARTNO + 5,    ///< The device already exist
    IOT_ERR_PROXY_NOEXIST               = IOT_ERR_PROXY_STARTNO + 6,    ///< The device isnot exist
    IOT_ERR_PROXY_NO_IDLE_PORT          = IOT_ERR_PROXY_STARTNO + 7,    ///< Get idle port failed
    IOT_ERR_PROXY_NOLOGIN               = IOT_ERR_PROXY_STARTNO + 8,    ///< No registered
    IOT_ERR_PROXY_SNDDATA               = IOT_ERR_PROXY_STARTNO + 9,    ///< Send data error
    IOT_ERR_PROXY_RCVDATA               = IOT_ERR_PROXY_STARTNO + 10,   ///< Receive data error
    IOT_ERR_PROXY_START                 = IOT_ERR_PROXY_STARTNO + 11,   ///< Failed to start
    IOT_ERR_PROXY_STOP                  = IOT_ERR_PROXY_STARTNO + 12,   ///< Failed to stop
    IOT_ERR_PROXY_CONNECT               = IOT_ERR_PROXY_STARTNO + 13,   ///< Connection to server failed
    IOT_ERR_PROXY_BEGINTHREAD           = IOT_ERR_PROXY_STARTNO + 14,   ///< Failed to begin thread
    IOT_ERR_PROXY_ENDTHREAD             = IOT_ERR_PROXY_STARTNO + 15,   ///< Failed to end thread
    IOT_ERR_PROXY_UNSUPPORT_STREAM      = IOT_ERR_PROXY_STARTNO + 16,   ///< Unsupported media streaming format
    IOT_ERR_PROXY_SOCKET                = IOT_ERR_PROXY_STARTNO + 17,   ///< Socket error
    IOT_ERR_PROXY_USERINFO              = IOT_ERR_PROXY_STARTNO + 18,   ///< Username or password error
    IOT_ERR_PROXY_SERVERBUSY            = IOT_ERR_PROXY_STARTNO + 19,   ///< Server busy
    IOT_ERR_PROXY_EXCEEDMAX             = IOT_ERR_PROXY_STARTNO + 20,   ///< Exceed the max value
    IOT_ERR_PROXY_TIMEOUT               = IOT_ERR_PROXY_STARTNO + 21,   ///< Connection or operation timed out
    IOT_ERR_PROXY_SDKAPI                = IOT_ERR_PROXY_STARTNO + 22,   ///< Call device sdk api error
    IOT_ERR_PROXY_DEV_OFFLINE           = IOT_ERR_PROXY_STARTNO + 23,   ///< Device is offline
    IOT_ERR_ONVIF_AUTH                  = IOT_ERR_PROXY_STARTNO + 24,   ///< Username or password error
    IOT_ERR_ONVIF_TIMING                = IOT_ERR_PROXY_STARTNO + 25,   ///< Server busy
    IOT_ERR_ONVIF_GET_DEVICE_INFO       = IOT_ERR_PROXY_STARTNO + 26,   ///< Exceed the max value
    IOT_ERR_ONVIF_GET_DEVICE_CAPABLITIES= IOT_ERR_PROXY_STARTNO + 27,   ///< Connection or operation timed out
    IOT_ERR_ONVIF_GET_DEVICE_PROFILES   = IOT_ERR_PROXY_STARTNO + 28,   ///< Call device sdk api error
    IOT_ERR_ONVIF_GET_DEVICE_STREAM_URL = IOT_ERR_PROXY_STARTNO + 29,   ///< Device is offline
    IOT_ERR_ONVIF_PTZ_CONTROL           = IOT_ERR_PROXY_STARTNO + 30,   ///< Device is offline

    // = HTTP API
    IOT_ERR_HTTP_STARTNO                = 6000,                         ///< Start number of HTTP API
    IOT_ERR_HTTP_UNKNOWN_URL            = IOT_ERR_HTTP_STARTNO + 1,     ///< Unknown URL
    IOT_ERR_HTTP_IOT_OFFLINE            = IOT_ERR_HTTP_STARTNO + 2,     ///< IoT server offline
    IOT_ERR_HTTP_INVALIDPARAM           = IOT_ERR_HTTP_STARTNO + 3,     ///< Invalid parameters
    IOT_ERR_HTTP_NOMEM                  = IOT_ERR_HTTP_STARTNO + 4,     ///< Out of memory
    IOT_ERR_HTTP_UNSUPPORT              = IOT_ERR_HTTP_STARTNO + 5,     ///< Unsupport operation or function
    IOT_ERR_HTTP_NOEXIST                = IOT_ERR_HTTP_STARTNO + 6,     ///< The device does not exist
    IOT_ERR_HTTP_RTMP                   = IOT_ERR_HTTP_STARTNO + 7,     ///< Rtmp Start Fail
    IOT_ERR_HTTP_TIMEOUT                = IOT_ERR_HTTP_STARTNO + 8,     ///< Async Call Timeout
    IOT_ERR_HTTP_EXCEEDLIMIT            = IOT_ERR_HTTP_STARTNO + 9,     ///< Exceed Max Query Limit

    // = GA READER
    IOT_ERR_GAR_STARTNO                 = 7000,                         ///< Start number of ga-reader
    IOT_ERR_GAR_UNKNOWN_URL             = IOT_ERR_GAR_STARTNO + 1,      ///< Unknown URL
    IOT_ERR_GAR_INVALIDPARAM            = IOT_ERR_GAR_STARTNO + 2,      ///< Invalid parameters
    IOT_ERR_GAR_NOMEM                   = IOT_ERR_GAR_STARTNO + 3,      ///< Out of memory
    IOT_ERR_GAR_UNSUPPORT               = IOT_ERR_GAR_STARTNO + 4,      ///< Unsupport operation or function
    IOT_ERR_GAR_EXIST                   = IOT_ERR_GAR_STARTNO + 5,      ///< Already Exist
    IOT_ERR_GAR_NOEXIST                 = IOT_ERR_GAR_STARTNO + 6,      ///< The device already exist
    IOT_ERR_GAR_VIIDERROR               = IOT_ERR_GAR_STARTNO + 7,      ///< VIID Error

    // = CACHE & RECORD SERVER
    IOT_ERR_RECORD_STARTNO              = 8000,                         ///< Start number of video cache and record server
    IOT_ERR_RECORD_UNKNOWN_INTERNAL     = IOT_ERR_RECORD_STARTNO + 1,   ///< Unknown internal error
    IOT_ERR_RECORD_SQLITE               = IOT_ERR_RECORD_STARTNO + 2,   ///< Exec sqlite3 error
    IOT_ERR_RECORD_INVALIDPARAM         = IOT_ERR_RECORD_STARTNO + 3,   ///< Invalid parameters
    IOT_ERR_RECORD_FILE                 = IOT_ERR_RECORD_STARTNO + 4,   ///< File operate error
    IOT_ERR_RECORD_SPACE_FULL           = IOT_ERR_RECORD_STARTNO + 5,   ///< Disk full
    IOT_ERR_RECORD_NO_RECORD_READ       = IOT_ERR_RECORD_STARTNO + 6,   ///< Have no record to read
    IOT_ERR_RECORD_DEV_USING            = IOT_ERR_RECORD_STARTNO + 7,   ///< Device is using, cannot delete
    IOT_ERR_RECORD_RECORD_EXIST         = IOT_ERR_RECORD_STARTNO + 8,   ///< Record already exist
    IOT_ERR_RECORD_DEV_NOEXIST          = IOT_ERR_RECORD_STARTNO + 9,   ///< Device does not exist
    IOT_ERR_RECORD_CON_OS               = IOT_ERR_RECORD_STARTNO + 10,  ///< Connect object storage error
    IOT_ERR_RECORD_OS_SOCKET            = IOT_ERR_RECORD_STARTNO + 11,  ///< Object storage network error
    IOT_ERR_RECORD_OS_REPLY             = IOT_ERR_RECORD_STARTNO + 12,  ///< Object storage reply error
    IOT_ERR_RECORD_OS_ERROR             = IOT_ERR_RECORD_STARTNO + 13,  ///< Object storage error
    IOT_ERR_RECORD_EXCEED_MAX           = IOT_ERR_RECORD_STARTNO + 14,  ///< The number of record exceeds the maximum
    IOT_ERR_RECORD_SEND_STREAM_SOCKET   = IOT_ERR_RECORD_STARTNO + 15,  ///< Stream send network error
    IOT_ERR_RECORD_NO_MATCH_STREAM      = IOT_ERR_RECORD_STARTNO + 16,  ///< No matching stream

    // = Capture Pusher
    IOT_ERR_CAPTURE_STARTNO             = 9000,                         ///< Start number of capture pusher
    IOT_ERR_CAPTURE_INNER_ERROR         = IOT_ERR_CAPTURE_STARTNO + 1,  ///< Unknown internal error
	IOT_ERR_CAPTURE_PARAM               = IOT_ERR_CAPTURE_STARTNO + 2,  ///< Invalid parameters
	IOT_ERR_CAPTURE_MISS_PARAM          = IOT_ERR_CAPTURE_STARTNO + 3,  ///< Miss parameters
	IOT_ERR_CAPTURE_SDK_ERROR           = IOT_ERR_CAPTURE_STARTNO + 4,  ///< Call sdk api error
    IOT_ERR_CAPTURE_GAID_NOT_EXIST      = IOT_ERR_CAPTURE_STARTNO + 5,  ///< Ga ID not exist
#endif
} IotErrorType;

#endif
