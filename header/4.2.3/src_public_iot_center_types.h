/*******************************************************************************
 * @file        iot_center_types.h
 * @brief       Type definition file of iot-center project
 *
 * @authors     flowstar
 * @copyright   All rights reserved
 *
 * Modification History:
 * -----------------------------------------------------------------------------
 * Date        Author        Description
 * -----------------------------------------------------------------------------
 * 2018-11-06  flowstar      Create the file
 * 2018-12-29  flowstar      Add video frame info for video callback
 * 2019-01-22  flowstar      Update to v2.0: support cloud & terminal camera
 * 2019-05-20  flowstar      Update to v2.1: support clip playback & H265 & vehicle info
 * 2019-06-10  flowstar      Update to v3.0: add more features: PtzControl & Alarm in/out, etc
 * 2019-08-13  flowstar      Update to v3.1: add wifi detection device
 * 2019-09-25  flowstar      Update to v3.2: add support for GA1400
 * 2019-12-23  flowstar      Add support for KAFKA camera
 * 2020-01-02  flowstar      Add support for record cache
 * 2020-01-14  flowstar      Update to v3.3: add some features: alarm types & preset & extend face/its info
 * 2020-04-21  flowstar      Update to v4.0: add alert info: type & structs & callback function
 * 2020-11-30  flowstar      Update to v4.1: add vision IoT type and structs
 *
 ******************************************************************************/
#ifndef _INCLUDE_IOT_CENTER_BASE_TYPES__H_
#define _INCLUDE_IOT_CENTER_BASE_TYPES__H_
#pragma once


//=============================================================================
// = 类型定义及宏定义

// 整型类型定义
typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;

#ifdef _WIN32
typedef long long           int64_t;
typedef unsigned long long	uint64_t;
#else
# if __WORDSIZE == 64
typedef long int            int64_t;
typedef unsigned long int   uint64_t;
# else
__extension__
typedef long long int       int64_t;
typedef unsigned long long int  uint64_t;
# endif
#endif

// 常用宏定义
#ifdef _WIN32
typedef void*               IOT_HANDLE;
# ifndef CALLBACK
#   define CALLBACK         __stdcall
# endif
# ifndef STDCALL
#   define STDCALL          __stdcall
# endif
#else
typedef int                 IOT_HANDLE;
# define STDCALL
# define CALLBACK
#endif //_WIN32

#ifndef FALSE
# define FALSE              0
#endif
#ifndef TRUE
# define TRUE               1
#endif

#ifndef NULL
# ifdef __cplusplus
#   define NULL             0
# else
#   define NULL             ((void *)0)
# endif
#endif

#ifndef MAX
# define MAX(a, b)          (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
# define MIN(a, b)          (((a) < (b)) ? (a) : (b))
#endif

// 函数参数类型定义
#ifndef IN
# define IN                 ///< 函数输入参数
#endif
#ifndef OUT
# define OUT                ///< 函数输出参数
#endif
#ifndef INOUT
# define INOUT              ///< 函数输入且输出参数
#endif

// 常量定义
#define IOT_LEN_ADDR        32      ///< 地址串/序列号长度
#define IOT_MAX_ADDR_LEN    256     ///< 地址串/序列号最大长度（为支持长域名串新增）
#define IOT_LEN_DEVID       24      ///< 设备标识号串长度（实际串长度为18字节）
#define IOT_LEN_GBID        24      ///< GB标识号串长度（实际串长度为20字节）
#define IOT_LEN_GBNAME      256     ///< GB名称串长度
#define IOT_LEN_CODE        32      ///< 编码串长度
#define IOT_LEN_TIME        32      ///< 时间串长度
#define IOT_LEN_USERNAME    32      ///< 用户名串长度
#define IOT_LEN_PWD         32      ///< 密码串长度
#define IOT_LEN_SESSION     64      ///< 会话串长度
#define IOT_LEN_VERSION     128     ///< 版本信息串长度
#define IOT_LEN_URL         512     ///< URL串长度
#define IOT_IPV4_LEN        16      ///< IP地址v4格式字符串长度
#define IOT_IPV6_LEN        46      ///< IP地址v6格式字符串长度
#define IOT_SUB_PIC_NUM     32      ///< 抓拍图中子图的最大个数
#define IOT_MAX_NODE_NUM    20      ///< 集群节点服务器最大个数
#define IOT_MAX_LST_NUM     100     ///< 设备列表最大个数
#define IOT_QUERY_NUM       IOT_MAX_LST_NUM ///< 一次查询状态时设备列表的最大个数（已废弃，为向之前版本兼容所保留）
#define IOT_TIMEOUT_UNIT    5       ///< 超时检测最小单位
#define IOT_CMD_TIMEOUT     20      ///< 信令超时的默认秒数，可通过接口函数或环境变量更改（都设置的情况下优先采用环境变量）
#define IOT_STREAM_TIMEOUT  30      ///< 视频流超时的默认秒数，可通过接口函数或环境变量更改（都设置的情况下优先采用环境变量）
#define IOT_CATALOG_TIMEOUT 180     ///< 获取国标平台目录信息超时的默认秒数，可通过环境变量更改
#define IOT_MAX_LINK_NUM 4          ///< 结构化信息中最大关联对象个数


//=============================================================================
// = 枚举定义

/// 摄像机设备类型
typedef enum IotDeviceType
{
    IOT_DT_RTSP         = 0,///< RTSP相机
    IOT_DT_IPC          = 1,///< 普通摄像机
    IOT_DT_SMART_IPC    = 2,///< 智能抓拍机（含识别机、结构化相机等）
    IOT_DT_GB28181_IPC  = 3,///< GB28181平台相机
    IOT_DT_BOX          = 4,///< 智能分析盒
    IOT_DT_CLOUD_IPC    = 5,///< 云端协同相机
    IOT_DT_GA1400_IPC   = 6,///< GA1400平台相机
    IOT_DT_KAFKA_IPC    = 7,///< KAFKA相机（旷视私有定制化类图片流相机）
    IOT_DT_ONVIF        = 8,///< ONVIF设备（v4.1版本开始逐渐废弃此类型，统一到类型 @ref IOT_DT_IPC 中）
    IOT_DT_MULTI_CHAN   = 9,///< 多通道设备（含双目、枪球一体化、双光热成像相机，NVR等可以包含多个通道的设备）
    IOT_DT_MAX              ///< 摄像机设备类型最大值
} IotDeviceType;

/// 传感器设备类型
typedef enum IotSensorDeviceType
{
    IOT_SDT_WIFI = 0,       ///< WIFI探针
    IOT_SDT_MAX             ///< 传感器设备类型最大值
} IotSensorDeviceType;

/// 视频/图像平台类型
typedef enum IotPlatformType
{
    IOT_PT_GB28181      = 1,    ///< GB/T 28181-2016平台
    IOT_PT_GA1400       = 2,    ///< GA/T 1400平台
    //IOT_PT_ISYSCORE     = 3,    ///< iSysCore平台（暂不支持）
    IOT_PT_DH_VCLOUD    = 20,   ///< 大华视频云平台（暂不支持）
    IOT_PT_HW_IVS3800   = 21,   ///< 华为IVS3800平台（暂不支持）
} IotPlatformType;

/// 设备厂家/相机协议
typedef enum IotDeviceVendor
{
    IOT_DV_RTSP         = 0,    ///< RTSP方式接入的设备
    IOT_DV_MEGVII       = 1,    ///< 旷视（v4.0后，此类型细分为下面的子类型，此类型不再有效）
    IOT_DV_HK           = 2,    ///< 海康
    IOT_DV_DH           = 3,    ///< 大华
    IOT_DV_GB28181      = 4,    ///< 国标GB28181
    IOT_DV_HW           = 5,    ///< 华为
    IOT_DV_YS           = 6,    ///< 宇视
    IOT_DV_KD           = 7,    ///< 科达
    IOT_DV_GA1400       = 8,    ///< 国标GA1400
    IOT_DV_KAFKA        = 9,    ///< KAFKA相机
    IOT_DV_ONVIF        = 10,   ///< ONVIF协议
    IOT_DV_MULTICAST    = 11,   ///< 组播方式接入的相机

    IOT_DV_DH_VCLOUD    = 20,   ///< 大华视频云平台相机
    IOT_DV_HW_IVS3800   = 21,   ///< 华为IVS3800平台相机
    IOT_DV_KD_VEHICLE   = 22,   ///< 科达车辆结构化相机（暂不支持）

    IOT_DV_MEGVII_T     = 51,   ///< 旷视T系列相机
    IOT_DV_MEGVII_X     = 52,   ///< 旷视X系列相机
    IOT_DV_MEGVII_R     = 53,   ///< 旷视R系列相机
    IOT_DV_MEGVII_B2S   = 54,   ///< 旷视B2S盒子
    IOT_DV_MEGVII_B2R   = 55,   ///< 旷视B2R盒子
    IOT_DV_MEGVII_B3R   = 56,   ///< 旷视B3R盒子
    IOT_DV_MEGVII_RS    = 57,   ///< 旷视RS系列相机（旷鹰IPC）
    IOT_DV_MEGVII_CONNECT = 58, ///< 旷视CONNECT协议接入的设备

    //注：枚举值[90~99]暂时预留给内部服务用
    IOT_DV_YF           = 100,  ///< 云天励飞
    IOT_DV_JVT          = 101,  ///< 深圳巨龙（暂不支持）
    IOT_DV_DG           = 102,  ///< 格林深瞳（暂不支持）
    IOT_DV_CW           = 103,  ///< 云从（暂不支持）
    IOT_DV_ZGHZ         = 104,  ///< 紫光华智（暂不支持）
} IotDeviceVendor;

/// 传感器设备厂家
typedef enum IotSensorDeviceVendor
{
    IOT_SDV_KMD     = 0,    ///< 科曼达
    IOT_SDV_MAX             ///< 设备厂商最大值
} IotSensorDeviceVendor;

/// 设备通道能力集合（除0外，其他值支持按位组合使用）
typedef enum IotChannelCapability
{
    IOT_CC_DEFAULT      = 0,            ///< 未定义，默认使用所属设备类型所具备的能力
    IOT_CC_VIDEO        = 0x1,          ///< 视频流
    IOT_CC_PICTURE      = (0x1 << 1),   ///< 图片流
    IOT_CC_PTZ          = (0x1 << 2),   ///< 云台控制
} IotChannelCapability;

/// 设备参数配置命令（中括号中的内容说明了应用的对象是设备还是通道，支持的操作能力是获取还是设置）
typedef enum IotDeviceConfigCommand
{
    /**
     * GET请求参数：无
     * GET回复内容如下：
     * {
     *     "vendorId" : 51,             // 厂商标识号
     *     "model" : "MegEye-C3R-221",  // 设备型号
     *     "firmware" : "x.x.x",        // 固件版本
     *     "algorithm" : "x.x.x",       // 算法版本
     *     "serialNo" : "10xxxxxxx"     // 设备序列号
     * }
     */
    IOT_DCC_GENERAL             = 1,    ///< 设备参数，包括设备厂商、型号、固件/算法版本信息等 [设备，GET]

    /**
     * GET请求参数如下：
     * {
     *     "channelNo" : 0,     // 设备通道号，从0开始
     *     "profileType" : 0,   // 通道码流类型：0-主码流，1-子码流，2-第二子码流
     * }
     * GET回复内容如下：
     * {
     *     "channelNo" : 0,     // 设备通道号，从0开始
     *     "profileType" : 0,   // 通道码流类型：0-主码流，1-子码流，2-第二子码流
     *     "list" : ["1280x720", "1920x1080"]  // 支持的分辨率能力列表
     * }
     */
    IOT_DCC_RESOLUTION_CAP      = 2,    ///< 分辨率能力集 [通道，GET]

    /**
     * GET请求参数：无
     * GET回复内容如下：
     * {
     *     "list" : [1,2,3]     // 支持的模式类型列表，元素值参见 @ref IotCameraMode
     * }
     */
    IOT_DCC_CAMERA_MODE_CAP     = 3,    ///< 相机模式能力集  [设备，GET]

    /**
     * GET请求参数如下：
     * {
     *     "channelNo" : 0,     // 设备通道号，从0开始
     *     "profileType" : 0,   // 通道码流类型：0-主码流，1-子码流，2-第二子码流
     * }
     * GET回复内容、SET请求参数如下：
     * {
     *     "channelNo" : 0,         // 设备通道号，从0开始
     *     "profileType" : 0,       // 通道码流类型：0-主码流，1-子码流，2-第二子码流
     *     "bitrateType" : 0,       // 码率控制类型：0-定码率，1-变码率
     *     "bitrate" : 2000,        // 码率，单位：kbps
     *     "frameRate" : 25,        // 帧率，值范围[0, 120]，常用值如：15/25/30/60
     *     "resolution" : "1920x1080",  // 分辨率
     *     "iFrameInterval" : 50    // I帧间隔，一般为帧率的整数倍，常用值如：25/30/50/60
     * }
     * SET回复内容：无
     */
    IOT_DCC_VIDEO               = 11,   ///< 视频流参数  [通道，GET/SET]

    /**
     * GET请求参数如下：
     * {
     *     "channelNo" : 0,     // 设备通道号，从0开始
     *     "profileType" : 0,   // 通道码流类型：0-主码流，1-子码流，2-第二子码流
     * }
     * GET回复内容、SET请求参数如下：
     * 注：不支持的字段在获取时无需填充，即不存在，从而设置时可先以获取到的字段为准进行配置，来尽量保证一致性
     * {
     *     "channelNo" : 0,             // 设备通道号，从0开始
     *     "profileType" : 0,           // 通道码流类型：0-主码流，1-子码流，2-第二子码流
     *     "resolution" : "1920x1080",  // 分辨率（部分类型设备会和视频共用此参数，此时此值可能不生效）
     *     "picQuality" : 80,           // 图片质量，范围在[1-100]
     *     "uploadPanorama" : 1,        // 是否上传全景图：0-不上传，1-上传
     *     "uploadStrategy" : 1,        // 推图策略：0-未知，1-最快，2-最优
     *     "snapMode" : 2,              // 抓拍模式：0-未知，1-全抓模式，2-高质量模式，3-用户自定义
     *     "snapNum" : 1,               // 抓拍张数，范围在[1-3]
     *     "recogMode" : 1,             // 识别模式：0-未知，1-门禁模式，2-VIP模式
     *     "recogUploadNum" : 1,        // 识别结果推送次数：范围在[1-10]
     *     "recogUploadInterval" : 100, // 识别结果推送间隔，单位：毫秒，常用值如：100/300/500/1000
     *     "minFacePixels" : 60         // 人脸最小像素，默认60，范围在[30-800]
     * }
     * SET回复内容：无
     */
    IOT_DCC_PICTURE             = 12,   ///< 图片流参数  [通道，GET/SET]

    /**
     * 注：目前只有ODM的几种型号支持，在获取或设置前可先通过获取相机模式能力集来判断设备是否支持
     * GET请求参数、SET回复内容：无
     * GET回复内容、SET请求参数如下：
     * {
     *     "mode" : 1,      // 相机模式参数，取值参见 @ref IotCameraMode
     * }
     */
    IOT_DCC_CAMERA_MODE         = 13,   ///< 相机模式  [设备，GET/SET]

    /**
     * GET请求参数如下：
     * {
     *     "channelNo" : 0, // 报警端子通道号，从0开始
     * }
     * GET回复内容、SET请求参数如下：
     * {
     *     "channelNo" : 0, // 报警端子通道号，从0开始
     *     "alarmMode" : 0, // 端子工作模式：0-常开，1-常闭
     *     "enabled" : 1    // 是否启用：0-未启用，1-启用
     * }
     * SET回复内容：无
     */
    IOT_DCC_ALARM_IN            = 14,   ///< 报警输入端子  [设备，GET/SET]

    /**
     * GET请求参数如下：
     * {
     *     "channelNo" : 0, // 报警端子通道号，从0开始
     * }
     * GET回复内容、SET请求参数如下：
     * {
     *     "channelNo" : 0, // 报警端子通道号，从0开始
     *     "alarmMode" : 0, // 端子工作模式：0-常开，1-常闭
     *     "delayTime" : 1  // 输出信号状态维持时间，单位：秒，范围一般在[0-600]，无符号双字节最大值65535表示一直维持，需手工关闭；若设备不支持设定的大小，系统内部会找一个最接近的值
     * }
     * SET回复内容：无
     */
    IOT_DCC_ALARM_OUT           = 15,   ///< 报警输出端子  [设备，GET/SET]
    //IOT_DCC_ALERT               = 16,   ///< 警戒  [设备，GET/SET]


    // = 以下为批量操作相关命令，设置成功与否会通过消息回调通知
    /**
     * 注：支持智能机和具备真实厂商的视频流相机（即用其设备SDK接入的设备，含onvif协议接入），后续会有异步消息通知执行结果
     * SET请求参数如下：
     * {
     *     "type" : 0,      // 校时类型：0-NTP校时，1-手动校时
     *     "ntp" : {        // NTP服务器校时信息，类型为0使用此对象
     *         "serverAddr" : "10.12.22.36",    // NTP服务器域名或地址
     *         "serverPort" : 445,              // NTP服务器端口
     *         "interval" : 720                 // 校时间隔，单位：分钟，需为60的整数倍，范围在[60, 720*60]
     *     },
     *     "manual" : {     // 手工校时时间信息，类型为1使用此对象
     *         "year" : 2020,       // 年
     *         "month" : 5,         // 月
     *         "day" : 12,          // 日
     *         "hour" : 10,         // 时
     *         "minute" : 30,       // 分
     *         "second" : 0,        // 秒
     *         "millisecond" : 0    // 毫秒
     *     }
     * }
     * SET回复内容：无
     */
    IOT_DCC_TIMING              = 101,   ///< 校时  [设备，SET]

    /**
     * 注：支持智能机和具备真实厂商的视频流相机（即用其设备SDK接入的设备），升级状态信息会通过消息回调多次分步通知
     * SET请求参数如下：
     * {
     *     "fileUrl" : "http://ip:port/xxx.zip"     // 升级文件所在路径的URL
     * }
     * SET回复内容：无
     */
    IOT_DCC_UPGRADE             = 102,   ///< 固件升级  [设备，SET]
    //IOT_DCC_BASELIB               = 103,   ///< 底库  [设备，GET/SET]
} IotDeviceConfigCommand;

/// 设备在线状态
typedef enum IotDeviceOnlineStatus
{
    IOT_DOS_ONLINE = 0,     ///< 正常在线
    IOT_DOS_OFFLINE,        ///< 异常掉线
    IOT_DOS_UNKNOWN,        ///< 未知状态
} IotDeviceOnlineStatus;

/// 设备工作状态
typedef enum IotDeviceWorkStatus
{
    IOT_DWS_OK = 0,         ///< 正常状态
    IOT_DWS_ERROR,          ///< 异常状态
    IOT_DWS_UNKNOWN,        ///< 未知状态
} IotDeviceWorkStatus;

/// 设备编码状态
typedef enum IotDeviceEncodeStatus
{
    IOT_DES_ON = 0,         ///< 正在编码
    IOT_DES_OFF,            ///< 未编码
    IOT_DES_UNKNOWN,        ///< 未知
} IotDeviceEncodeStatus;

/// 设备录像状态
typedef enum IotDeviceRecordStatus
{
    IOT_DRS_ON = 0,         ///< 正在录像
    IOT_DRS_OFF,            ///< 未录像
    IOT_DRS_UNKNOWN,        ///< 未知
} IotDeviceRecordStatus;

/// 设备取流类型（设备类型 @ref IOT_DT_CLOUD_IPC 取流时要用到）
typedef enum IotDeviceStreamType
{
    IOT_DST_RTSP = 0,       ///< RSTP方式
    IOT_DST_GB28181,        ///< 国标方式
    IOT_DST_MAX             ///< 设备取流类型最大值
} IotDeviceStreamType;

/// 通道码流类型
typedef enum IotChanProfileType
{
    IOT_CPT_MAIN = 0,       ///< 主码流
    IOT_CPT_SUB,            ///< 子码流
    IOT_CPT_SUB2,           ///< 第二子码流
    IOT_CPT_MAX             ///< 设备码流类型最大值
} IotChanProfileType;

/// 码率控制类型
typedef enum IotRateControlType
{
    IOT_RCT_CBR = 0,        ///< 固定码率
    IOT_RCT_VBR,            ///< 可变码率
} IotRateControlType;

/// 媒体流类型
typedef enum IotStreamType
{
    IOT_ST_PICTURE = 0,     ///< 实时图片流
    IOT_ST_LIVE,            ///< 实时视频流
    IOT_ST_CLIP,            ///< 历史视频流
    IOT_ST_TEXT,            ///< 文本数据流
    IOT_ST_ALERT,           ///< 警戒图片流
    IOT_ST_MAX              ///< 类型最大值
} IotStreamType;

/// 图片数据格式类型
typedef enum IotPictureType
{
    IOT_PT_JPG = 0,        ///< JPG/JPEG
    IOT_PT_BMP,            ///< BMP
    IOT_PT_YUV,            ///< YUV
    IOT_PT_OTHER,          ///< Other type
} IotPictureType;

/// 视频数据编码类型
typedef enum IotEncodeType
{
    IOT_ET_H264 = 0,        ///< H264
    IOT_ET_H265,            ///< H265（V2.1开始支持）
    IOT_ET_SVAC,            ///< SVAC（V4.0开始支持）
} IotEncodeType;

/// 数据帧类型
typedef enum IotFrameType
{
    IOT_FT_SMART = 0,       ///< 智能数据帧（含可能的特定文件头）
    IOT_FT_I,               ///< I帧
    IOT_FT_P,               ///< P帧
    IOT_FT_B,               ///< B帧
} IotFrameType;

/// 设备校时类型
typedef enum IotTimingType
{
    IOT_TT_NTP = 0,         ///< NTP校时
    IOT_TT_MANUAL,          ///< 手动校时
    IOT_TT_MAX              ///< 设备校时类型最大值
} IotTimingType;

/// 相机模式
typedef enum IotCameraMode
{
    IOT_CM_UNKNOWN              = 0,    ///< 未知模式
    IOT_CM_FACE_CAPTURE         = 1,    ///< 人脸抓拍
    IOT_CM_FACE_RECOGNIZE       = 2,    ///< 人脸识别
    IOT_CM_SMART                = 3,    ///< 智能监控
    IOT_CM_TRAFFIC              = 4,    ///< 道路监控
    IOT_CM_MIX                  = 5,    ///< 混合检测
    IOT_CM_WATER                = 6,    ///< 水利模式
    IOT_CM_WATER_WARNING        = 7,    ///< 水利预警站模式
    IOT_CM_TRAFFIC_FLOW         = 8,    ///< 交通流量统计
    IOT_CM_SUPERVISION_COMMITTEE= 9,    ///< 智能监委
    IOT_CM_PUBLIC_SECURITY      = 10,   ///< 智能公安
    IOT_CM_EDUCATION            = 11,   ///< 智能教育
    IOT_CM_DISCIPLINE           = 12,   ///< 智能管教
    IOT_CM_RESOURCE_TIMING_SWITCH=13,   ///< 资源分配定时切换
    IOT_CM_MAX                          ///< 相机模式类型最大值
} IotCameraMode;

/// 历史视频流下载速度
typedef enum IotDownloadSpeed
{
    IOT_DS_1    = 1,        ///< 正常速度
    IOT_DS_2    = 2,        ///< 2倍速
    IOT_DS_4    = 4,        ///< 4倍速
    IOT_DS_8    = 8,        ///< 8倍速
    IOT_DS_16   = 16,       ///< 16倍速
} IotDownloadSpeed;

/// 历史视频流回放控制命令
typedef enum IotPlaybackCommand
{
    IOT_PC_PAUSE    = 1,        ///< 暂停播放
    IOT_PC_RESUME   = 2,        ///< 恢复播放
    IOT_PC_SPEED    = 3,        ///< 快慢放/倍速播放，此时参数param对应速度值，参见 @ref IotPlaybackSpeed
    IOT_PC_SEEK     = 4,        ///< 跳转播放，此时参数param对应拖放范围，值大小为开流时设置的播放时间范围，单位：秒
} IotPlaybackCommand;

/// 历史视频流回放控制速度
typedef enum IotPlaybackSpeed
{
    IOT_PS_N400 = -5,       ///< 倒放4倍速
    IOT_PS_N200 = -4,       ///< 倒放2倍速
    IOT_PS_N100 = -3,       ///< 倒放正常速度
    IOT_PS_N50  = -2,       ///< 倒放1/2倍速
    IOT_PS_N25  = -1,       ///< 倒放1/4倍速
    IOT_PS_25   = 1,        ///< 1/4倍速
    IOT_PS_50   = 2,        ///< 1/2倍速
    IOT_PS_100  = 3,        ///< 正常速度
    IOT_PS_200  = 4,        ///< 2倍速
    IOT_PS_400  = 5,        ///< 4倍速
} IotPlaybackSpeed;

/// 云台、镜头控制命令
typedef enum IotPtzControlCommand
{
    IOT_PTZ_UP          = 1,    ///< 上
    IOT_PTZ_DOWN        = 2,    ///< 下
    IOT_PTZ_LEFT        = 3,    ///< 左
    IOT_PTZ_RIGHT       = 4,    ///< 右
    IOT_PTZ_LEFT_TOP    = 5,    ///< 左上
    IOT_PTZ_RIGHT_TOP   = 6,    ///< 右上
    IOT_PTZ_LEFT_DOWN   = 7,    ///< 左下
    IOT_PTZ_RIGHT_DOWN  = 8,    ///< 右下
    IOT_PTZ_ZOOM_INC    = 9,    ///< 焦距变大（变倍+）
    IOT_PTZ_ZOOM_DEC    = 10,   ///< 焦距变小（变倍-）
    IOT_PTZ_FOCUS_INC   = 11,   ///< 焦点前调（调焦+）
    IOT_PTZ_FOCUS_DEC   = 12,   ///< 焦点后调（调焦-）
    IOT_PTZ_IRIS_INC    = 13,   ///< 光圈扩大
    IOT_PTZ_IRIS_DEC    = 14,   ///< 光圈缩小
    IOT_PTZ_GET_PRESET  = 15,   ///< 获取预置点（暂不支持）
    IOT_PTZ_SET_PRESET  = 16,   ///< 设置预置点
    IOT_PTZ_CLE_PRESET  = 17,   ///< 清除预置点（暂不支持）
    IOT_PTZ_GOTO_PRESET = 18,   ///< 转到预置点
} IotPtzControlCommand;

/// 设备事件/报警主类型
typedef enum IotDeviceAlarmMainType
{
    IOT_DAM_HARDWARE        = 1,    ///< 设备硬件事件
    IOT_DAM_INTELLIGENCE    = 2,    ///< 设备智能事件
    IOT_DAM_OPERATION       = 3,    ///< 运维事件
    IOT_DAM_STATISTICS      = 4,    ///< 统计事件
} IotDeviceAlarmMainType;

/// 设备通用事件/报警类型
typedef enum IotDeviceAlarmType
{
	// 设备硬件事件
    IOT_DAT_SWITCH                      = 1,    ///< 开关量（报警输入端子）报警
	// 设备智能事件
    IOT_DAT_SIGNAL_LOST                 = 1000, ///< 信号丢失
    IOT_DAT_MOVE_DETECT                 = 1001, ///< 移动侦测
    IOT_DAT_OCCLUSION                   = 1002, ///< 遮挡报警
    IOT_DAT_VIDEO_ABNORMAL              = 1003, ///< 视频信号异常
    IOT_DAT_SCENE_CHANGE                = 1004, ///< 场景变更
    IOT_DAT_DEFOCUS                     = 1005, ///< 虚焦检测
    IOT_DAT_LUMA                        = 1006, ///< 亮度异常
    IOT_DAT_CHROMA                      = 1007, ///< 偏色检测
    IOT_DAT_SNOW                        = 1008, ///< 雪花干扰
    IOT_DAT_STREAK                      = 1009, ///< 条纹干扰
    IOT_DAT_FREEZE                      = 1010, ///< 画面冻结
    IOT_DAT_CLARITY                     = 1011, ///< 清晰度异常
    IOT_DAT_PICTURE_SHAKE               = 1012, ///< 画面抖动
    IOT_DAT_BLURRED_SCREEN              = 1013, ///< 花屏检测
    IOT_DAT_HOT_PIXEL                   = 1014, ///< 噪点检测
    IOT_DAT_ABNORMAL_RACULA             = 1015, ///< 异常光斑
    IOT_DAT_PURPLE_EDGE                 = 1016, ///< 紫边检测
    IOT_DAT_RESIST_FILM                 = 1017, ///< 保护膜未撕
    IOT_DAT_GAIN_IMBALANCE              = 1018, ///< 增益失衡
    IOT_DAT_VIDEO_DIAGNOSIS             = 1019, ///< 视频诊断
    IOT_DAT_INTRUSION_DETECTION         = 1020, ///< 入侵检测
    IOT_DAT_LEGACY_DETECTION            = 1021, ///< 遗留检测
    IOT_DAT_TRIP_WIRE                   = 1022, ///< 绊线
    IOT_DAT_PERIMETER_INTRUSION         = 1023, ///< 周界入侵
    IOT_DAT_PEOPLE_GATHERING            = 1024, ///< 人员聚集
    IOT_DAT_LOITERING                   = 1025, ///< 徘徊检测
    IOT_DAT_RAPID_MOVE                  = 1026, ///< 快速移动检测
    IOT_DAT_PERSONQUEUE                 = 1027, ///< 人员排队检测
    IOT_DAT_TARGET_LEFT_REGION          = 1028, ///< 教师离开讲台
    IOT_DAT_RECOGNIZATION               = 1029, ///< 比中事件
    IOT_DAT_PARKING                     = 1030, ///< 停车侦测
    IOT_DAT_NON_VEHICLE_EXIST           = 1031, ///< 非占机
    IOT_DAT_VEHICLE_EXIST               = 1032, ///< 机占非
    IOT_DAT_ILLEGAL_PARKING             = 1033, ///< 违法停车
    IOT_DAT_WRONG_DIRECTION             = 1034, ///< 逆行
    IOT_DAT_VEHICLE_REVERSE             = 1035, ///< 倒车
    IOT_DAT_CROSS_LINE                  = 1036, ///< 压线/越线
    IOT_DAT_CONGESTION                  = 1037, ///< 拥堵告警
    IOT_DAT_ITS_BLACKLIST               = 1038, ///< 车辆黑名单告警
    IOT_DAT_SIGNAL_LAMP_ABNORMAL        = 1039, ///< 信号灯异常检测
    IOT_DAT_SAFETY_HELMET               = 1040, ///< 安全帽检测
    IOT_DAT_SWITCH_LAMP                 = 1041, ///< 开关灯报警
    IOT_DAT_SHIPSDETECTION              = 1042, ///< 船只检测报警
    IOT_DAT_AUDIO_ABNORMAL              = 1043, ///< 声音异常
    IOT_DAT_AUDIO_ABNORMAL_UP           = 1044, ///< 音频陡升
    IOT_DAT_AUDIO_ABNORMAL_DOWN         = 1045, ///< 音频陡降
    IOT_DAT_AUDIO_LOST                  = 1046, ///< 声音丢失
    IOT_DAT_FACE_UNIQUE_ALERT_MS        = 1047, ///< 特色警戒报警
    IOT_DAT_DB_TRIP_WIRE                = 1048, ///< 双绊线
    IOT_DAT_OBJ_STOLEN                  = 1049, ///< 物品丢失
    IOT_DAT_NO_WEAR_RESPIRATOR          = 1050, ///< 未戴口罩
    IOT_DAT_FACE_COMPARISON_SUCCESSFUL  = 1051, ///< 人脸比对成功
    IOT_DAT_AC_NON_LIVING_ATTACK               = 1100, ///< 非活体攻击
    IOT_DAT_AC_IMPORT_PERSON_TRY_TO_PASS       = 1101, ///< 重点人员尝试通行
    IOT_DAT_AC_STRANGER_TRY_TO_PASS            = 1102, ///< 陌生人尝试通行
    IOT_DAT_AC_NORMAL_ACCESS_OF_STAFF          = 1103, ///< 员工正常通行时间
    IOT_DAT_AC_ABNORMAL_ACCESS_OF_STAFF        = 1104, ///< 员工非通行时间尝试访问
    IOT_DAT_AC_NORMAL_ACCESS_OF_VISITOR        = 1105, ///< 访客正常通行时间
    IOT_DAT_AC_ABNORMAL_ACCESS_OF_VISITOR      = 1106, ///< 访客非通行时间尝试访问
    IOT_DAT_AC_FIRE_CONTROL                    = 1107, ///< 消防
    IOT_DAT_AC_DOOR_ALWAYS_OPEN                = 1108, ///< 门常开未关
    IOT_DAT_AC_DOORBELL_RINGS                  = 1109, ///< 门铃响
    
	// 运维事件
    IOT_DAT_TEMPERATURE_ABNARMAL        = 2000, ///< 温度告警
    IOT_DAT_HD_ERROR                    = 2001, ///< 磁盘告警
    IOT_DAT_CPU_EXCEED_THRESHOLD        = 2002, ///< CPU超过阈值
    IOT_DAT_NETWORK                     = 2003, ///< 网络报警
    IOT_DAT_STORAGE_NOT_EXIST           = 2004, ///< 存储设备不存在
    IOT_DAT_STORAGE_FAILURE             = 2005, ///< 存储设备访问失败
    IOT_DAT_LOW_SPACE                   = 2006, ///< 存储设备容量过低
    IOT_DAT_STORAGE_READ_ERROR          = 2007, ///< 存储设备读错误
    IOT_DAT_STORAGE_WRITE_ERROR         = 2008, ///< 存储设备写错误
    IOT_DAT_IP_CONFLICT                 = 2009, ///< IP冲突
    IOT_DAT_EXCEPTION                   = 2010, ///< 异常报警
    IOT_DAT_MAC_CONFLICT                = 2011, ///< mac地址冲突
    IOT_DAT_SD_CARD_ABNORMAL            = 2012, ///< sd卡异常
    IOT_DAT_NETWORK_RECOVERY            = 2013, ///< 网络恢复
    // 统计/分析事件
    IOT_DAT_ABNORMAL_FRAME_RATE         = 3000, ///< 帧率异常
    IOT_DAT_PACKET_LOST_HIGH            = 3001, ///< 丢包率超过阈值
    IOT_DAT_PICTURE_DROP                = 3002, ///< 图片丢失
    IOT_DAT_FRAME_DROP                  = 3003, ///< 帧丢弃
    IOT_DAT_DEVICE_OFFLINE              = 3004, ///< 设备掉线（注：为保持对老版本的兼容，复用消息通知类型 @ref IOT_MT_DEV_OFFLINE 即两种类型会同时通知）
    IOT_DAT_STREAM_OFTEN_RESTART        = 3005, ///< 流频繁重启
    IOT_DAT_STREAM_SLOW                 = 3006, ///< 慢流（等同于帧率异常）
    IOT_DAT_AVERAGE_SNAP_NUM            = 3007, ///< 日均抓拍异常
    IOT_DAT_SNAP_STATISTIC_INTERVAL     = 3008, ///< 设备固定间隔内的抓拍量
} IotDeviceAlarmType;

/// 回调消息类别
typedef enum IotMessageCategory
{
    IOT_MC_STREAM       = 0x1,              ///< 流（包括消息通知类型：32/33/36/37）
    IOT_MC_SERVICE      = (0x1 << 1),       ///< 服务（包括消息通知类型：30/31/201/202）
    IOT_MC_DEVICE       = (0x1 << 2),       ///< 设备（包括消息通知类型：0/1/4/50/51/101/308）
    IOT_MC_ALL          = 0xFFFFFFFF        ///< 所有（默认值）
} IotMessageCategory;

/// 回调消息通知类型
typedef enum IotMessageType
{
    IOT_MT_DEV_ONLINE       = 0,    ///< 设备上线，回调参数content内容为设备ID串
    IOT_MT_DEV_OFFLINE      = 1,    ///< 设备掉线，回调参数content内容为设备ID串
    IOT_MT_DEV_ADD          = 2,    ///< 设备添加（暂不支持），回调参数content内容可参见 @ref IotDeviceConfig
    IOT_MT_DEV_DELETE       = 3,    ///< 设备删除（暂不支持），回调参数content内容为设备ID串
    IOT_MT_DEV_UPDATE       = 4,    ///< 设备信息更新，回调参数content内容可参见 @ref IotDeviceInfo
    IOT_MT_DEV_UPDATE_OK    = 5,    ///< 设备更新成功（只有调用更新操作的客户端才会收到此通知），回调参数content内容为设备ID串
    IOT_MT_DEV_UPDATE_FAIL  = 6,    ///< 设备更新失败（只有调用更新操作的客户端才会收到此通知），回调参数content内容为设备ID串
    IOT_MT_DEV_TIMING       = 7,    ///< 设备校时（一次批量校时，可能收到多次回调响应），回调参数content内容可参见 @ref IotDeviceTimingNotify
    IOT_MT_UPGRADE_STATE    = 8,    ///< 设备升级状态及进度，回调参数content内容可参见 @ref IotUpgradeStateNotify
    IOT_MT_DEV_OPEN_OK      = 9,    ///< 打开传感器设备成功（只有调用该操作的客户端才会收到此通知），回调参数content内容为设备ID串
    IOT_MT_DEV_OPEN_FAIL    = 10,   ///< 打开传感器设备失败（只有调用该操作的客户IOT_CB_Message端才会收到此通知），回调参数content内容为设备ID串
    IOT_MT_RECORD_SAVE      = 11,   ///< 录像另存为功能异步方式结果通知，回调参数content内容可参见 @ref IotRecordSaveNotify
    IOT_MT_RCG_LIB_ADD_STATE= 12,   ///< 底库下发进度，回调参数content内容可参见 @ref IotRcgLibAddStateNotify
    IOT_MT_SERVER_ONLINE    = 30,   ///< master服务上线，回调参数content内容为服务器的IP地址
    IOT_MT_SERVER_OFFLINE   = 31,   ///< master服务掉线，回调参数content内容为服务器的IP地址
    IOT_MT_RCV_STREAM_ERR   = 32,   ///< 接收流失败，回调参数content内容可参见 @ref IotStreamNotifyInfo
    IOT_MT_RCV_STREAM_END   = 33,   ///< 接收历史流完成，回调参数content内容可参见 @ref IotStreamNotifyInfo
    IOT_MT_ALGORITHM_OK     = 34,   ///< 算法工作正常（暂不支持），回调参数content内容为设备ID串
    IOT_MT_ALGORITHM_ERR    = 35,   ///< 算法工作异常（暂不支持），回调参数content内容为设备ID串
    IOT_MT_BUFFER_EMPTY     = 36,   ///< 缓冲区持续一段时间为空通知，回调参数content内容可参见 @ref IotStreamNotifyInfo
    IOT_MT_LOW_FRAMERATE    = 37,   ///< 视频流持续低帧率通知（如5秒内实际帧率持续低于正常帧率的80%），回调参数content内容可参见 @ref IotStreamNotifyInfo
    IOT_MT_DEV_ALARM        = 50,   ///< 设备通用类型报警，回调参数content内容可参见 @ref IotDeviceAlarmInfo
    IOT_MT_FACE_MATCH_ALARM = 51,   ///< 人脸比对报警，回调参数content内容可参见 @ref IotFaceMatchAlarmInfo

    /**
     * 报警信息格式样例如下：
     * {
     *     "timestamp" : 1595226598000,         // UTC时间戳（有符号64位整型），单位：毫秒
     *     "mainType" : 1,                      // 报警主类型，参见 @ref IotDeviceAlarmMainType
     *     "subType" : 20,                      // 报警类型，参见 @ref IotDeviceAlarmType
     *     "alarmState" : 0,                    // 报警状态：0-报警，1-消警
     *     "deviceId" : "110000200100000005",   // 设备标识号
     *     "channelId" : "110000200300000005",  // 通道标识号
     *     "isChannel" : 1,                     // 消息是否为通道报警类型：0-设备，1-通道
     *     "channelNo" : 0                      // 输入端子通道号，与通道无关的类型，此值默认为0
     * }
     */
    IOT_MT_ALARM_MSG            = 101,  ///< 通用报警消息，回调参数content内容为json串，格式参见报警信息格式说明

    /**
     * 后台服务上下线格式样例如下：
     * {
     *     "type" : 1,                  // 服务类型：1-master（为保持兼容性，此版本还是使用类型值30/31通知），2-cvserver
     *     "addr" : "192.168.0.8",      // 服务所在节点地址：可为IP地址、主机名或域名
     *     "port" : 8500                // 服务端口号（可选项）
     * }
     */
    IOT_MT_SERVICE_ONLINE       = 201,  ///< 服务上线，回调参数content内容为json串，格式参见服务上下线格式说明
    IOT_MT_SERVICE_OFFLINE      = 202,  ///< 服务掉线，回调参数content内容为json串，格式参见服务上下线格式说明

    /**
     * 通道信息更新通知格式样例如下：
     * {
     *     "parentId" : "110000200100000005",   // 所属的设备或平台ID
     *     "channelId" : "110000200300000005"   // 通道ID
     * }
     */
    IOT_MT_CHN_UPDATE           = 308,  ///< 通道信息更新，回调参数content内容为json串
#if 0
    IOT_MT_DEV_ONLINE           = 301,  ///< 设备上线，回调参数content内容为设备ID串
    IOT_MT_DEV_OFFLINE          = 302,  ///< 设备掉线，回调参数content内容为设备ID串
    IOT_MT_DEV_ADD              = 303,  ///< 设备添加
    IOT_MT_DEV_DELETE           = 304,  ///< 设备删除
    IOT_MT_DEV_UPDATE           = 305,  ///< 设备信息更新
    IOT_MT_CHN_ADD              = 306,  ///< 通道添加
    IOT_MT_CHN_DELETE           = 307,  ///< 通道删除
    IOT_MT_DEV_TIMING           = 310,  ///< 设备校时（一次批量校时，可能收到多次回调响应），回调参数content内容可参见 @ref IotDeviceTimingNotify
    IOT_MT_UPGRADE_STATE        = 311,  ///< 设备升级状态及进度，回调参数content内容可参见 @ref IotUpgradeStateNotify
    IOT_MT_RCG_LIB_ADD_STATE    = 312,  ///< 底库下发进度，回调参数content内容可参见 @ref IotRcgLibAddStateNotify

    IOT_MT_RCV_STREAM_ERR       = 401,  ///< 接收流失败，回调参数content内容可参见 @ref IotStreamNotifyInfo
    IOT_MT_BUFFER_EMPTY         = 402,  ///< 缓冲区持续一段时间为空通知，回调参数content内容可参见 @ref IotStreamNotifyInfo
    IOT_MT_LOW_FRAMERATE        = 403,  ///< 视频流持续低帧率通知（5秒内实际帧率持续低于正常帧率的80%），回调参数content内容可参见 @ref IotStreamNotifyInfo
    IOT_MT_RCV_STREAM_END       = 410,  ///< 接收历史流完成，回调参数content内容可参见 @ref IotStreamNotifyInfo

    IOT_MT_RECORD_SAVE          = 501,  ///< 录像另存为功能异步方式结果通知，回调参数content内容可参见 @ref IotRecordSaveNotify
#endif
    IOT_MT_VIDEO_DIAGNOSE_RESULT= 502,  ///< 视频诊断结果通知，回调参数content内容为json串，格式参见 http://api-insight.cbg.megvii-inc.com/project/2237/interface/api/291241
} IotMessageType;

/// 分辨率的定义
typedef enum IotVideoResolutionType
{
    IOT_VRT_UNKNOWN         = 0,    ///< Unknown
    IOT_VRT_HCIF            = 1,    ///< HCIF：352x120
    IOT_VRT_FCIF            = 2,    ///< CIF：352x240
    IOT_VRT_HD1             = 3,    ///< HD1：704x288
    IOT_VRT_FD1             = 4,    ///< 4CIF：704x576
    IOT_VRT_MD1             = 5,    ///< MD1：720*288
    IOT_VRT_QVGA            = 6,    ///< QVGA：320x240
    IOT_VRT_VGA             = 7,    ///< VGA：640*480
    IOT_VRT_HVGA            = 8,    ///< HVGA：640*240
    IOT_VRT_HD_720P         = 9,    ///< 720p：1280*720
    IOT_VRT_HD_960P         = 10,   ///< 960P：1280*960
    IOT_VRT_HD_200W         = 11,   ///< 200W：1600*1200
    IOT_VRT_HD_1080P        = 12,   ///< 1080P：1920*1080
    IOT_VRT_HD_QXGA         = 13,   ///< QXGA：2048*1536
    IOT_VRT_QHD             = 14,   ///< QHD：960*540
    IOT_VRT_VZ_960H         = 15,   ///< 960H：960*576
    IOT_VRT_VZ_1440P        = 16,   ///< 1440P：2560*1440
    IOT_VRT_VZ_4MP          = 17,   ///< 4MP(1)：2592*1520
    IOT_VRT_WUXGA           = 18,   ///< WUXGA 1920*1200
    IOT_VRT_HK_4MP          = 19,   ///< 4MP(2)：2688x1520
    IOT_VRT_VZ_5MA          = 20,   ///< 5.0MP：2448*2048
    IOT_VRT_VZ_5M           = 21,   ///< 5M(2)：2560*1920
    IOT_VRT_VZ_5MB          = 22,   ///< 5M(3)：2592*1944
    IOT_VRT_VZ_5MC          = 23,   ///< 5M(4)：2592*2048
    IOT_VRT_VZ_5MD          = 24,   ///< 5M(5)：2528*2128
    IOT_VRT_VZ_5ME          = 25,   ///< 5M(6)：2560*2048
    IOT_VRT_VZ_6M           = 26,   ///< 6M(1)：2752*2208
    IOT_VRT_VZ_6MA          = 27,   ///< 6M(2)：3008*2008
    IOT_VRT_VZ_6MB          = 28,   ///< 6M(3)：3408*2008
    IOT_VRT_VZ_7M           = 29,   ///< 7M 3392*2008
    IOT_VRT_VZ_8MA          = 30,   ///< 8M(1)：3840*2160
    IOT_VRT_VZ_8MB          = 31,   ///< 8M(2)：3264x2448
    IOT_VRT_VZ_8MC          = 32,   ///< 8M(3)：3296x2472
    IOT_VRT_4K              = 33,	///< 4K：4096x2160
    IOT_VRT_VZ_HD900P       = 34,	///< HD900P：1600x900
    IOT_VRT_640_360         = 35,   ///< 640*360
    IOT_VRT_352_288         = 36,   ///< 352*288
    IOT_VRT_3072_2048       = 37,   ///< 3072*2048
    IOT_VRT_3072_1728       = 38,   ///< 3072*1728
    IOT_VRT_2304_1296       = 39,   ///< 2304*1296
    IOT_VRT_720_576         = 40,   ///< 720*576
    IOT_VRT_720_480         = 41,   ///< 720*480
    IOT_VRT_704_480         = 42,   ///< 704*480
    IOT_VRT_704_240         = 43,   ///< 704*240
    IOT_VRT_800_600         = 44,   ///< 800*600
    IOT_VRT_1280_1024       = 45,   ///< 1280*1024
    IOT_VRT_2720_2048       = 46,   ///< 2720*2048
    IOT_VRT_2046_1536       = 47,   ///< 2046*1536
    IOT_VRT_QCIF            = 48,   ///< QCIF：176x120
    IOT_VRT_2064_1544       = 49,   ///< 2064*1544
    IOT_VRT_MAX                     ///< 分辨率类型最大值（实际分辨率不在此枚举范围内时也置为此值，表示暂未支持）
} IotVideoResolutionType;

/// 车牌颜色
typedef enum IotPlateColor
{
    IOT_PLATE_COLOR_UNKNOWN = 0,    ///< 未知
    IOT_PLATE_COLOR_BLUE,           ///< 蓝色
    IOT_PLATE_COLOR_YELLOW,         ///< 黄色
    IOT_PLATE_COLOR_WHITE,          ///< 白色
    IOT_PLATE_COLOR_BLACK,          ///< 黑色
    IOT_PLATE_COLOR_GREEN,          ///< 绿色
    IOT_PLATE_COLOR_GRADIENT_GREEN, ///< 渐变绿底黑字
    IOT_PLATE_COLOR_YELLOW_GREEN,   ///< 黄绿双拼底黑字
} IotPlateColor;

/// 车牌类型
typedef enum IotPlateType
{
    IOT_PLATE_TYPE_UNKNOWN = 0,             ///< 未知类型
    IOT_PLATE_TYPE_CAR = 0x01,              ///< 普通小车、私家车牌（蓝色、黑色）
    IOT_PLATE_TYPE_TRUCK = 0x02,            ///< 普通大车、卡车牌（黄色）
    IOT_PLATE_TYPE_POLICECAR = 0x04,        ///< 警车牌（白色）
    IOT_PLATE_TYPE_ARMEDPOLICECAR = 0x08,   ///< wujing车牌
    IOT_PLATE_TYPE_HK_MACAU = 0x10,         ///< 港澳车牌
    IOT_PLATE_TYPE_DBLYELLOW = 0x20,        ///< 双层黄牌
    IOT_PLATE_TYPE_ARMY = 0x40,             ///< 军牌
    IOT_PLATE_TYPE_EMBASSY = 0x80,          ///< 领使馆牌
    IOT_PLATE_TYPE_ELECTRICBICYCLE = 0x100, ///< 电动自行车车牌
    IOT_PLATE_TYPE_DBLARMY = 0x200,         ///< 双层军牌
    IOT_PLATE_STUDY = 0x400,                ///< "学"车牌
    IOT_PLATE_MOTORCYCLE = 0x800,           ///< 摩托车牌
    IOT_PLATE_TEMPORARY = 0x1000,           ///< 临时车牌
    IOT_PLATE_TYPE_AGRICULTURE = 0x2000,    ///< 农用车牌 拖拉机
    IOT_PLATE_TYPE_TRAILER = 0x4000,        ///< 挂车车牌
    IOT_PLATE_TYPE_NEWNENRGY = 0x8000,      ///< 新能源牌
    IOT_PLATE_TRANSPORT = 0x10000,          ///< 运输车
    IOT_PLATE_COMMERCIAL = 0x20000,         ///< 商用车
    IOT_PLATE_LEARNING = 0x40000,           ///< 教练车
    IOT_PLATE_GOVERNMENT = 0x80000,         ///< 政府车
    IOT_PLATE_TAXI = 0x100000,              ///< 出租车
} IotPlateType;

/// 车身颜色
typedef enum IotVehicleColor
{
    IOT_VEHICLE_COLOR_WHITE     = 0,	///< 白色
    IOT_VEHICLE_COLOR_RED       = 1,    ///< 红色
    IOT_VEHICLE_COLOR_YELLOW    = 2,    ///< 黄色
    IOT_VEHICLE_COLOR_ORANGE    = 3,    ///< 橙色
    IOT_VEHICLE_COLOR_GREEN     = 5,    ///< 绿色
    IOT_VEHICLE_COLOR_PURPLE    = 7,    ///< 紫色
    IOT_VEHICLE_COLOR_PINK      = 8,    ///< 粉色
    IOT_VEHICLE_COLOR_BLACK     = 9,    ///< 黑色
    IOT_VEHICLE_COLOR_GRAY      = 13,   ///< 灰色
    IOT_VEHICLE_COLOR_BLUE      = 15,   ///< 蓝色
    IOT_VEHICLE_COLOR_CYAN      = 21,   ///< 青色
    IOT_VEHICLE_COLOR_BROWN     = 29,   ///< 棕色
    IOT_VEHICLE_COLOR_DARKBLUE  = 32,   ///< 深蓝
    IOT_VEHICLE_COLOR_LIGHTBLUE = 33,   ///< 浅蓝
    IOT_VEHICLE_COLOR_MULTI     = 34,   ///< 彩色
    IOT_VEHICLE_COLOR_NOT       = 99,   ///< 未知
} IotVehicleColor;

/// 车辆类型
typedef enum IotVehicleType
{
    IOT_VEHICLE_TYPE_NOT = 0,           ///< 未知
    IOT_VEHICLE_TYPE_HATCHBACKCAR,      ///< 两厢轿车
    IOT_VEHICLE_TYPE_CAR,               ///< 轿车
    IOT_VEHICLE_TYPE_SPORTSCAR,         ///< 轿跑
    IOT_VEHICLE_TYPE_SMALLCAR,          ///< 小型轿车
    IOT_VEHICLE_TYPE_MINICAR,           ///< 微型轿车
    IOT_VEHICLE_TYPE_MPV,               ///< MPV
    IOT_VEHICLE_TYPE_SUV,               ///< SUV
    IOT_VEHICLE_TYPE_LARGEBUSES,        ///< 大型客车
    IOT_VEHICLE_TYPE_MEDIUM_BUS,        ///< 中型客车
    IOT_VEHICLE_TYPE_VAN = 10,          ///< 面包车
    IOT_VEHICLE_TYPE_MINIVAN,           ///< 微型面包车
    IOT_VEHICLE_TYPE_TRUCK,             ///< 大货车
    IOT_VEHICLE_TYPE_MEDIUMTRUCK,       ///< 中型货车
    IOT_VEHICLE_TYPE_TANKTRUCK,         ///< 油罐车
    IOT_VEHICLE_TYPE_CRANE,             ///< 吊车
    IOT_VEHICLE_TYPE_MUCKTRUCK,         ///< 渣土车
    IOT_VEHICLE_TYPE_BUGGY,             ///< 小货车
    IOT_VEHICLE_TYPE_PICKUP,            ///< 皮卡
    IOT_VEHICLE_TYPE_MINIPICKUP,        ///< 微卡
    IOT_VEHICLE_TYPE_TWOWHEELER = 20,   ///< 两轮车
    IOT_VEHICLE_TYPE_TRICYCLE,          ///< 三轮车
    IOT_VEHICLE_TYPE_PEDESTRAIN,        ///< 行人
    IOT_VEHICLE_TYPE_PLATE_HANGUP,      ///< 车牌挂偏
    IOT_VEHICLE_TYPE_PLATE_DECT,        ///< 车牌检测
    IOT_VEHICLE_TYPE_HEAD,              ///< 车头
    IOT_VEHICLE_TYPE_TAIL,              ///< 车尾
    IOT_VEHICLE_TYPE_LIGHT,             ///< 车灯
    IOT_VEHICLE_TYPE_SUV_MPV,           ///< SUV/ MPV
    IOT_VEHICLE_TYPE_TRAILER = 29,      ///< 挂车
    IOT_VEHICLE_TYPE_SMALLVEHICLE = 30, ///< 小型车(大范围)
    IOT_VEHICLE_TYPE_LARGEVEHICLE = 31, ///< 大型车(大范围)
    IOT_VEHICLE_TYPE_BICYCLE = 100,     ///< 自行车
    IOT_VEHICLE_TYPE_ELECTRIC = 101,    ///< 电动车
    IOT_VEHICLE_TYPE_MOTOR = 102        ///< 摩托车
} IotVehicleType;

/// 车辆品牌类型
typedef enum IotVehicleClass
{
    IOT_VEHICLE_CLASS_OTHER = 0,        ///< 其它
    IOT_VEHICLE_CLASS_VOLKSWAGEN = 1,   ///< 大众
    IOT_VEHICLE_CLASS_AUDI = 2,         ///< 奥迪
    IOT_VEHICLE_CLASS_TOYOTA = 3,       ///< 丰田
    IOT_VEHICLE_CLASS_HONDA = 4,        ///< 本田
    IOT_VEHICLE_CLASS_BENZ = 5,         ///< 奔驰
    IOT_VEHICLE_CLASS_CHEVROLET = 6,    ///< 雪佛兰
    IOT_VEHICLE_CLASS_CHERY = 7,        ///< 奇瑞
    IOT_VEHICLE_CLASS_BUICK = 8,        ///< 别克
    IOT_VEHICLE_CLASS_GREATWALL = 9,    ///< 长城
    IOT_VEHICLE_CLASS_HYUNDAI = 10,     ///< 现代
    IOT_VEHICLE_CLASS_NISSAN = 11,      ///< 尼桑
    IOT_VEHICLE_CLASS_FORD = 12,        ///< 福特
    IOT_VEHICLE_CLASS_BMW = 13,         ///< 宝马
    IOT_VEHICLE_CLASS_CITROEN = 14,     ///< 雪铁龙
    IOT_VEHICLE_CLASS_KIA = 15,         ///< 起亚
    IOT_VEHICLE_CLASS_SUZUKI = 16,      ///< 铃木
    IOT_VEHICLE_CLASS_MAZDA = 17,       ///< 马自达
    IOT_VEHICLE_CLASS_BYD = 18,         ///< 比亚迪
    IOT_VEHICLE_CLASS_PEUGEOT = 20,     ///< 标致
    IOT_VEHICLE_CLASS_CHANA = 21,       ///< 长安
    IOT_VEHICLE_CLASS_LEXUS = 22,       ///< 雷克萨斯
    IOT_VEHICLE_CLASS_ZHONGHUA = 23,    ///< 中华
    IOT_VEHICLE_CLASS_SKODA = 24,       ///< 斯柯达
    IOT_VEHICLE_CLASS_HAIMA = 25,       ///< 海马
    IOT_VEHICLE_CLASS_XIALI = 26,       ///< 夏利
    IOT_VEHICLE_CLASS_SGMW = 27,        ///< 五菱
    IOT_VEHICLE_CLASS_DONGFENG = 28,    ///< 东风
    IOT_VEHICLE_CLASS_HAFEI = 29,       ///< 哈飞
    IOT_VEHICLE_CLASS_FAW = 30,         ///< 一汽
    IOT_VEHICLE_CLASS_BAOJUN = 31,      ///< 宝骏
    IOT_VEHICLE_CLASS_EMGRAND = 32,     ///< 帝豪(吉利)
    IOT_VEHICLE_CLASS_MG = 33,          ///< MG名爵
    IOT_VEHICLE_CLASS_SOUEAST = 34,     ///< 东南
    IOT_VEHICLE_CLASS_CROWN = 35,       ///< 皇冠(丰田)
    IOT_VEHICLE_CLASS_JINBEI = 36,      ///< 金杯
    IOT_VEHICLE_CLASS_MITSUBISHI = 37,  ///< 三菱
    IOT_VEHICLE_CLASS_ROEWE = 38,       ///< 荣威
    IOT_VEHICLE_CLASS_GEELY = 39,       ///< 吉利
    IOT_VEHICLE_CLASS_ENGLON = 40,      ///< 英伦(吉利)
    IOT_VEHICLE_CLASS_GLEAGLE = 41,     ///< 吉利全球鹰(吉利)
    IOT_VEHICLE_CLASS_SAIBAO = 42,      ///< 哈飞赛豹
    IOT_VEHICLE_CLASS_CHANGFENG = 43,   ///< 长丰
    IOT_VEHICLE_CLASS_BQWEIWANG = 44,   ///< 北汽威旺
    IOT_VEHICLE_CLASS_BEIJING = 45,     ///< 北京汽车
    IOT_VEHICLE_CLASS_XINKAI = 46,      ///< 新凯
    IOT_VEHICLE_CLASS_GONOW = 47,       ///< 吉奥汽车
    IOT_VEHICLE_CLASS_MASHALADI = 48,   ///< 玛莎拉蒂
    IOT_VEHICLE_CLASS_ROVER = 49,       ///< 罗孚
    IOT_VEHICLE_CLASS_AUSTIN = 50,      ///< 奥斯汀
    IOT_VEHICLE_CLASS_DS = 52,          ///< 道奇
    IOT_VEHICLE_CLASS_GAGUAR = 55,      ///< 捷豹
    IOT_VEHICLE_CLASS_ALFA = 57,        ///< 阿尔法
    IOT_VEHICLE_CLASS_LANBOJINI = 58,   ///< 兰博基尼
    IOT_VEHICLE_CLASS_BUGATTI = 59,     ///< 布加迪
    IOT_VEHICLE_CLASS_LICOLN = 60,      ///< 林肯
    IOT_VEHICLE_CLASS_FALALI = 61,      ///< 法拉利汽车
    IOT_VEHICLE_CLASS_CHANGHE = 62,     ///< 昌河
    IOT_VEHICLE_CLASS_FIAT = 63,        ///< 菲亚特
    IOT_VEHICLE_CLASS_FOTON = 64,       ///< 福田
    IOT_VEHICLE_CLASS_OGA = 65,         ///< 讴歌
    IOT_VEHICLE_CLASS_LOTUS = 66,       ///< 莲花汽车
    IOT_VEHICLE_CLASS_SMA = 67,         ///< 华普汽车
    IOT_VEHICLE_CLASS_HONGQI = 68,      ///< 红旗
    IOT_VEHICLE_CLASS_RUILIN = 69,      ///< 瑞麟
    IOT_VEHICLE_CLASS_BESTURN = 70,     ///< 一汽奔腾(一汽)
    IOT_VEHICLE_CLASS_WEILIN = 71,      ///< 威麟汽车
    IOT_VEHICLE_CLASS_ZOTYE = 72,       ///< 众泰
    IOT_VEHICLE_CLASS_LIFAN = 73,       ///< 力帆
    IOT_VEHICLE_CLASS_BJJEEP = 74,      ///< JEEP(吉普)
    IOT_VEHICLE_CLASS_ZTE = 75,         ///< 中兴
    IOT_VEHICLE_CLASS_KARRY = 76,       ///< 开瑞
    IOT_VEHICLE_CLASS_LANDROVER = 77,   ///< 路虎
    IOT_VEHICLE_CLASS_MAYBACH = 78,     ///< 迈巴赫
    IOT_VEHICLE_CLASS_RENAULT = 79,     ///< 雷诺
    IOT_VEHICLE_CLASS_OPEL = 80,        ///< 欧宝
    IOT_VEHICLE_CLASS_YEMA = 81,        ///< 野马
    IOT_VEHICLE_CLASS_JEEP = 82,        ///< 吉普
    IOT_VEHICLE_CLASS_NAVECO = 83,      ///< 依维柯
    IOT_VEHICLE_CLASS_INFINITI = 84,    ///< 英菲尼迪
    IOT_VEHICLE_CLASS_SUBARU = 85,      ///< 斯巴鲁
    IOT_VEHICLE_CLASS_ASTONMARTIN = 86, ///< 阿斯顿·马丁
    IOT_VEHICLE_CLASS_ANKAI = 87,       ///< 安凯客车
    IOT_VEHICLE_CLASS_PORSCHE = 88,     ///< 保时捷
    IOT_VEHICLE_CLASS_BINLI = 89,       ///< 宾利
    IOT_VEHICLE_CLASS_FODAY = 90,       ///< 福迪
    IOT_VEHICLE_CLASS_FUJIANBENZ = 91,  ///< 福建奔驰
    IOT_VEHICLE_CLASS_GMC = 92,         ///< 吉姆斯
    IOT_VEHICLE_CLASS_GUANZHI = 93,     ///< 观致
    IOT_VEHICLE_CLASS_RIY = 94,         ///< 广汽
    IOT_VEHICLE_CLASS_SHUANGLONG = 95,  ///< 双龙
    IOT_VEHICLE_CLASS_HIGER = 96,       ///< 海格
    IOT_VEHICLE_CLASS_HUMMER = 97,      ///< 悍马
    IOT_VEHICLE_CLASS_HAWTAI = 98,      ///< 华泰
    IOT_VEHICLE_CLASS_HUANGHAI = 99,    ///< 黄海
    IOT_VEHICLE_CLASS_JIULONG = 100,    ///< 九龙客车
    IOT_VEHICLE_CLASS_EVERUS = 101,     ///< 理念
    IOT_VEHICLE_CLASS_SMART = 102,      ///< 奔驰SMART
    IOT_VEHICLE_CLASS_LUFENG = 103,     ///< 陆风
    IOT_VEHICLE_CLASS_LUXGEN = 104,     ///< 纳智捷
    IOT_VEHICLE_CLASS_OLEY = 105,       ///< 欧朗 
    IOT_VEHICLE_CLASS_VENUCIA = 106,    ///< 启辰
    IOT_VEHICLE_CLASS_HAVAL = 107,      ///< 哈弗HAVAL
    IOT_VEHICLE_CLASS_HOWO = 108,       ///< 豪沃
    IOT_VEHICLE_CLASS_HUIZHONG = 109,   ///< 上海汇众(上汽集团)
    IOT_VEHICLE_CLASS_KINGLONG = 110,   ///< 金龙
    IOT_VEHICLE_CLASS_JAC = 112,        ///< 江淮
    IOT_VEHICLE_CLASS_JMC = 113,        ///< JMC(江铃)
    IOT_VEHICLE_CLASS_CADILLAC = 114,   ///< 凯迪拉克
    IOT_VEHICLE_CLASS_MINI = 116,       ///< 宝马MINI
    IOT_VEHICLE_CLASS_SHANQI = 117,     ///< 陕汽
    IOT_VEHICLE_CLASS_SHAOLIN = 118,    ///< 少林
    IOT_VEHICLE_CLASS_VOLVO = 119,      ///< 沃尔沃
    IOT_VEHICLE_CLASS_ISUZU = 120,      ///< 五十铃(庆铃)
    IOT_VEHICLE_CLASS_YUEJIN = 121,     ///< 跃进
    IOT_VEHICLE_CLASS_YUTONG = 122,     ///< 宇通
    IOT_VEHICLE_CLASS_ZHONGTONG = 123,  ///< 中通
    IOT_VEHICLE_CLASS_SUNWIN = 125,     ///< 申沃
    IOT_VEHICLE_CLASS_YZJIANG = 126,    ///< 扬子江
    IOT_VEHICLE_CLASS_BEIBEN = 128,     ///< 北奔重卡
    IOT_VEHICLE_CLASS_HONGYAN = 129,    ///< 红岩汽车(上汽依维柯红岩)
    IOT_VEHICLE_CLASS_ROLISROYCE = 130, ///< 劳斯莱斯
    IOT_VEHICLE_CLASS_TESLA = 131,      ///< 特斯拉
    IOT_VEHICLE_CLASS_DENZA = 132,      ///< 腾势
    IOT_VEHICLE_CLASS_ENRANGER = 134,   ///< 英致
    IOT_VEHICLE_CLASS_XIYATE = 135,     ///< 西雅特
    IOT_VEHICLE_CLASS_YAXING = 136,     ///< 亚星客车
    IOT_VEHICLE_CLASS_DAEWOO = 137,     ///< 大宇客车
    IOT_VEHICLE_CLASS_CHANADS = 138,    ///< 长安谛艾仕
    IOT_VEHICLE_CLASS_COWIN = 139,      ///< 凯翼
    IOT_VEHICLE_CLASS_DATONG = 140,     ///< 上汽大通
    IOT_VEHICLE_CLASS_CIIMO = 141,      ///< 本田思铭
    IOT_VEHICLE_CLASS_KAMA = 142,       ///< 凯马
} IotVehicleClass;

/// 证件类型
typedef enum IotCardType
{
    IOT_CARD_TYPE_INVALID       = 0,    ///< 无效
    IOT_CARD_TYPE_UNKNOWN       = 1,    ///< 未知
    IOT_CARD_TYPE_ID_CARD       = 2,    ///< 身份证
    IOT_CARD_TYPE_OFFICER_CARD  = 3,    ///< 军官证
    IOT_CARD_TYPE_PASSPORT      = 4,    ///< 护照
} IotCardType;

/// 性别
typedef enum IotGenderType
{
    IOT_GENDER_INVALID  = 0,            ///< 无效
    IOT_GENDER_UNKNOWN  = 1,            ///< 未知
    IOT_GENDER_MALE     = 2,            ///< 男性
    IOT_GENDER_FEMALE   = 3,            ///< 女性
} IotGenderType;

//=============================================================================
// = 结构体定义

/**
 * 设备系列/型号特别说明
 * @note 对于设备类型为旷视时，不能为空，取值如下：
 *       相机：MegEye-T, c3s, c3r-221/MegEye-C3R-221/MegEye-C3R-221-Cloud, c3r-321/MegEye-C3R-321,
 *            MegEye-X, c3slc, c3s-123/MegEye-C3S-123,
 *            MegEye-R, hz, c3s-226, c3s-826, MegEye-C3R-125/MegEye-C3R-125-4G
 *       盒子：b2r-411/MegBox-B2R-411, b3r/MegBox-B3R-1611, MegBox-B2S-423
 */
#define IOT_DEVICE_MODEL_LIST

/// 普通IPC摄像机
typedef struct IotIpcConfig
{
    char addr[IOT_LEN_ADDR];            ///< 地址
    uint16_t port;                      ///< 端口号
    char username[IOT_LEN_USERNAME];    ///< 用户名
    char password[IOT_LEN_PWD];         ///< 密码
    uint16_t chan_no;                   ///< 通道号，从0开始，默认值为0
    uint16_t chan_profile;              ///< 通道码流类型，值参见 @ref IotChanProfileType
    char model[IOT_LEN_CODE];           ///< 设备系列/型号，值参见 @ref IOT_DEVICE_MODEL_LIST 的注释说明
    char rtsp_url[IOT_LEN_URL];         ///< 视频流RTSP串地址（可选项，不为空时，视频流访问地址以此串为准）
} IotIpcConfig;

/// 智能抓拍机
typedef struct IotSmartIpcConfig
{
    char addr[IOT_LEN_ADDR];            ///< 地址
    uint16_t port;                      ///< 端口号
    uint16_t video_port;                ///< 视频流端口号
    char username[IOT_LEN_USERNAME];    ///< 用户名
    char password[IOT_LEN_PWD];         ///< 密码
    uint16_t chan_no;                   ///< 通道号，从0开始，默认值为0
    uint16_t chan_profile;              ///< 通道码流类型，值参见 @ref IotChanProfileType
    char model[IOT_LEN_CODE];           ///< 设备系列/型号，值参见 @ref IOT_DEVICE_MODEL_LIST 的注释说明
    char rtsp_url[IOT_LEN_URL];         ///< 视频流RTSP串地址（可选项，不为空时，视频流访问地址以此串为准）
    char platform_id[IOT_LEN_GBID];     ///< 国标平台标识号
    char device_code[IOT_LEN_GBID];     ///< 设备编码
} IotSmartIpcConfig;

/// 国标平台相机
typedef struct IotGbIpcConfig
{
    char platform_id[IOT_LEN_GBID];     ///< 国标平台标识号
    char device_code[IOT_LEN_GBID];     ///< 设备编码
} IotGbIpcConfig;

/// 盒子（指多通道设备）
typedef struct IotBoxConfig
{
    char addr[IOT_LEN_ADDR];            ///< 地址
    uint16_t port;                      ///< 端口号
    char username[IOT_LEN_USERNAME];    ///< 用户名
    char password[IOT_LEN_PWD];         ///< 密码
    uint16_t chan_num;                  ///< 通道个数
    char model[IOT_LEN_CODE];           ///< 设备系列/型号，值参见 @ref IOT_DEVICE_MODEL_LIST 的注释说明
    char platform_id[IOT_LEN_GBID];     ///< 国标平台标识号
    char device_code[IOT_LEN_GBID];     ///< 设备编码
} IotBoxConfig;

/// 云端协同相机
typedef struct IotCloudIpcConfig
{
    char addr[IOT_LEN_ADDR];            ///< 地址
    uint16_t port;                      ///< 端口号
    uint16_t video_port;                ///< 视频流端口号
    char username[IOT_LEN_USERNAME];    ///< 用户名
    char password[IOT_LEN_PWD];         ///< 密码
    uint16_t chan_no;                   ///< 通道号，从0开始，默认值为0
    uint16_t chan_num;                  ///< 通道个数
    uint16_t chan_profile;              ///< 通道码流类型，值参见 @ref IotChanProfileType
    char model[IOT_LEN_CODE];           ///< 设备系列/型号，值参见 @ref IOT_DEVICE_MODEL_LIST 的注释说明
    char rtsp_url[IOT_LEN_URL];         ///< 视频流RTSP串地址
    char platform_id[IOT_LEN_GBID];     ///< 国标平台标识号
    char device_code[IOT_LEN_GBID];     ///< 设备编码
} IotCloudIpcConfig;

/// KAFKA相机
typedef struct IotKafkaIpcConfig
{
    char addr[IOT_LEN_ADDR];            ///< 地址（暂未用到）
    uint16_t port;                      ///< 端口号（暂未用到）
    char username[IOT_LEN_USERNAME];    ///< 用户名（暂未用到）
    char password[IOT_LEN_PWD];         ///< 密码（暂未用到）
    char model[IOT_LEN_CODE];           ///< 设备系列/型号（暂未用到）
    char url[IOT_LEN_URL];              ///< KAFKA抓拍流地址串
    char topic_name[64];                ///< TOPIC名称串
} IotKafkaIpcConfig;

/// 摄像机设备信息
typedef struct IotDeviceConfig
{
    int vendor;                         ///< 设备厂家，值参见 @ref IotDeviceVendor
    int type;                           ///< 设备类型，值参见 @ref IotDeviceType
    union {
        char rtsp_url[IOT_LEN_URL];     ///< RTSP摄像机视频访问URL，对应设备类型参见 @ref IOT_DT_RTSP
        IotIpcConfig ipc;               ///< 普通摄像机，对应设备类型参见 @ref IOT_DT_IPC 及 @ref IOT_DT_ONVIF
        IotSmartIpcConfig smart_ipc;    ///< 智能抓拍机，对应设备类型参见 @ref IOT_DT_SMART_IPC
        IotGbIpcConfig gb_ipc;          ///< 国标平台相机，对应设备类型参见 @ref IOT_DT_GB28181_IPC 及 @ref IOT_DT_GA1400_IPC
        IotBoxConfig box;               ///< 盒子/多通道设备，对应设备类型参见 @ref IOT_DT_BOX 及 @ref IOT_DT_MULTI_CHAN
        IotCloudIpcConfig cloud_ipc;    ///< 云端协同相机，对应设备类型参见 @ref IOT_DT_CLOUD_IPC
        IotKafkaIpcConfig kafka_ipc;    ///< KAFKA相机，对应设备类型参见 @ref IOT_DT_KAFKA_IPC
    };
    char parent_id[IOT_LEN_DEVID];      ///< 父设备ID，对于没有父节点的情况，设置为空即可
    char extra_info[1024];              ///< 其他信息字段，用于透传上层业务发给proxy的“其他”字段信息，一般为json串
} IotDeviceConfig;

/// WIFI探针信息
typedef struct IotWifiSensorConfig
{
    char addr[IOT_LEN_ADDR];            ///< 地址（暂未用到）
    uint16_t port;                      ///< 端口号（暂未用到）
    char username[IOT_LEN_USERNAME];    ///< 用户名（暂未用到）
    char password[IOT_LEN_PWD];         ///< 密码（暂未用到）
    char mark_id[IOT_LEN_DEVID];        ///< 探针设备ID
    char business_id[IOT_LEN_DEVID];    ///< 上层业务ID
} IotWifiSensorConfig;

/// 传感器设备信息
typedef struct IotSensorDeviceConfig
{
    int type;                           ///< 传感器设备类型，值参见 @ref IotSensorDeviceType
    int vendor;                         ///< 传感器设备厂家，值参见 @ref IotSensorDeviceVendor
    union {
        IotWifiSensorConfig wifi;       ///< WIFI探针设备
    };
} IotSensorDeviceConfig;

/// 设备完整信息（获取设备列表结构体）
typedef struct IotDeviceInfo
{
    char id[IOT_LEN_DEVID];             ///< 设备ID
    IotDeviceConfig config;             ///< 设备配置参数
    int online;                         ///< 设备在线状态，值参见 @ref IotDeviceOnlineStatus
} IotDeviceInfo;

/// 设备参数信息（用于设备发现功能）
typedef struct IotDeviceDiscoveryInfo
{
    char ip[IOT_IPV6_LEN];              ///< 设备IP地址串
    uint16_t port;                      ///< 设备端口
    uint8_t res[80];                    ///< 预留字段（结构体总大小为128字节）
} IotDeviceDiscoveryInfo;

/// 设备实时状态信息（GB28181设备才能完整支持这些信息）
typedef struct IotDeviceStatus
{
    uint8_t online;                     ///< 设备在线状态（所有设备都支持此字段），值参见 @ref IotDeviceOnlineStatus
    uint8_t status;                     ///< 设备工作状态，值参见 @ref IotDeviceWorkStatus
    uint8_t encode;                     ///< 是否编码，值参见 @ref IotDeviceEncodeStatus
    uint8_t record;                     ///< 是否录像，值参见 @ref IotDeviceRecordStatus
    char device_time[IOT_LEN_TIME];     ///< 设备当前时间
} IotDeviceStatus;

/// GB28181设备信息
typedef struct IotGbDeviceInfo
{
    char manufacturer[32];              ///< 厂商
    char model[32];                     ///< 型号
    char firmware[32];                  ///< 固件版本
    uint16_t max_camera_num;            ///< 最大视频通道数
    uint16_t max_alarm_num;             ///< 最大告警通道数
} IotGbDeviceInfo;

/// GB28181设备目录信息
typedef struct IotGbDeviceCatalog
{
    char sub_device_id[IOT_LEN_GBID];   ///< 子设备ID
    char name[IOT_LEN_GBNAME];          ///< 子设备名称
    char manufacturer[32];              ///< 设备厂商
    char model[32];                     ///< 设备型号
    char owner[32];                     ///< 设备归属
    char civil_code[32];                ///< 行政区域
    char block[32];                     ///< 警区
    char address[128];                  ///< 安装地址
    char parental[16];                  ///< 当为设备时，是否有子设备
    char parent_id[IOT_LEN_GBNAME];     ///< 父节点ID
    char safety_way[32];                ///< 信令安全模式
    char register_way[32];              ///< 注册方式
    char cert_num[32];                  ///< 证书序列号
    char certifiable[32];               ///< 证书有效标识
    char err_code[32];                  ///< 无效原因码
    char end_time[32];                  ///< 证书终止有效期
    char secrecy[32];                   ///< 保密属性
    char ip_address[IOT_LEN_ADDR];      ///< 设备/区域/系统IP地址
    uint16_t port;                      ///< 设备/区域/系统端口号
    char password[32];                  ///< 设备口令
    char status[32];                    ///< 设备状态
    char longitude[32];                 ///< 经度
    char latitude[32];                  ///< 纬度
} IotGbDeviceCatalog;

/// 国标平台设备目录信息（精简版本，只含必要字段）
typedef struct IotLiteDeviceCatalog
{
    int  is_catalog;                    ///< 是否为目录：0-否（设备），1-是（目录）
    char name[IOT_LEN_GBNAME];          ///< 子设备名称
    char sub_device_id[IOT_LEN_GBID];   ///< 子设备ID
    char parent_id[IOT_LEN_GBNAME];     ///< 父节点ID
    char longitude[32];                 ///< 经度
    char latitude[32];                  ///< 纬度
    char civil_code[32];                ///< 行政区域
} IotLiteDeviceCatalog;

/// 历史视频流片段信息结构体
typedef struct IotRecordClipInfo
{
    char start_time[IOT_LEN_TIME];      ///< 开始时间
    char end_time[IOT_LEN_TIME];        ///< 结束时间
} IotRecordClipInfo;

/// 矩形框坐标信息
typedef struct IotRectInfo
{
    uint32_t left;                      ///< 左
    uint32_t top;                       ///< 上
    uint32_t right;                     ///< 右
    uint32_t bottom;                    ///< 下
} IotRectInfo;

/// 关联对象（脸、人、车、非）信息
typedef struct IotLinkInfo
{
    int track_id;                       ///< 绑定对象的track ID
    uint8_t type;                       ///< 绑定对象类型：1-人脸，2-人体，3-机动车，4-非机动车，5-车牌
    uint8_t res[3];                     ///< 预留字段
} IotLinkInfo;

/// 人脸图信息
typedef struct IotFacePicInfo
{
    int face_id;                        ///< 人脸图ID（透传）
    uint8_t	face_level;                 ///< 图像质量，范围[0, 100]（目前仅有HK支持）
    uint8_t pic_format;                 ///< 图片数据格式，值参见 @ref IotPictureType （目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t res1[2];                    ///< 预留字段1
    int rect_type;                      ///< 区域坐标值类型：0-无坐标值，1-在全景图中的绝对值，2-在全景图中的千分比
    IotRectInfo rect;                   ///< 人脸框图区域，如果厂商不支持框图，则保持和抠图大小一致（坐标类型为1时透传，为2时根据各厂商情况转换为千分比）
    IotRectInfo face_rect;              ///< 人脸抠图区域，一般比框图小一些，如果厂商不支持抠图，则保持和框图大小一致（坐标类型为1时透传，为2时根据各厂商情况转换为千分比）
    uint8_t age;                        ///< 年龄（透传，不支持此字段时默认值为0）
    uint8_t gender;                     ///< 性别，值参见 @ref IotGenderType （除DH透传外，其它厂商做了转换，不支持时默认值为0）
    uint8_t masks;                      ///< 口罩：0-无效，1-无，2-有，3-面具（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t beard;                      ///< 胡须：0-无效，1-无，2-有（目前只有MEGVII及其B3R盒子支持，不支持时默认值为0）
    uint8_t eye;                        ///< 睁眼：0-无效，1-无，2-有（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t mouth;                      ///< 张嘴：0-无效，1-无，2-有（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t glasses;                    ///< 眼镜：0-无效，1-无，2-普通眼睛，3-太阳镜（目前只有MEGVII和HK支持，不支持时默认值为0）
    uint8_t race;                       ///< 肤色：0-无效，1-黄种人，2-黑种人，3-白种人（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t emotion;                    ///< 表情：0-无效，1-生气，2-平静，3-厌恶，4-困惑，5-高兴，6-悲伤，7-害怕，8-惊讶，9-斜视，10-尖叫（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t smile;                      ///< 微笑：0-无效，1-无，2-有（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t value;                      ///< 颜值（暂不支持）
    uint8_t nation;                     ///< 民族：0-无效，1-汉族，2-少数民族（目前只有MEGVII及其B3R盒子支持，不支持时默认值为0）
    uint16_t face_width;                ///< 人脸宽度（暂不支持）
	uint16_t face_height;               ///< 人脸高度（暂不支持）
    uint8_t res2[16];                   ///< 预留字段2（结构体总大小为76字节）
} IotFacePicInfo;

/// 人脸图信息（扩展版本2）
typedef struct IotFacePicInfo2
{
    int face_id;                        ///< 人脸图ID（透传）
    uint8_t	level;                      ///< 图像质量，范围[0, 100]（目前仅有HK支持）
    uint8_t pic_format;                 ///< 图片数据格式，值参见 @ref IotPictureType （目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t res1[1];                    ///< 预留字段1
    uint8_t rect_type;                  ///< 区域坐标值类型：0-无坐标值，1-在全景图中的绝对值，2-在全景图中的千分比
    IotRectInfo rect;                   ///< 人脸框图区域，如果厂商不支持框图，则保持和抠图大小一致（在全景图中的位置，坐标类型为1时透传，为2时根据各厂商情况转换为千分比）
    IotRectInfo face_rect;              ///< 人脸抠图区域，一般比框图小一些，如果厂商不支持抠图，则保持和框图大小一致（在全景图中的位置，坐标类型为1时透传，为2时根据各厂商情况转换为千分比）
    uint32_t face_len;                  ///< 人脸图大小，值大于0时，再从子图数据缓冲区中读取数据（透传）
    uint32_t feature_data_len;          ///< 特征值数据长度（目前只有MEGVII支持，透传）
    uint32_t landmark_data_len;         ///< 关键点数据长度（目前只有MEGVII支持，透传）
    uint32_t extend_data_len;           ///< 扩展数据长度（目前只有MEGVII支持，透传）
    uint8_t *face_buf;                  ///< 人脸图数据（透传）
    uint8_t *feature_data;              ///< 特征值数据，值大于0时，再从数据缓冲区中读取数据（目前只有MEGVII支持，透传）
    uint8_t *landmark_data;             ///< 关键点数据，值大于0时，再从数据缓冲区中读取数据（目前只有MEGVII支持，透传）
    uint8_t *extend_data;               ///< 扩展数据，值大于0时，再从数据缓冲区中读取数据（目前只有MEGVII支持，透传）
    uint16_t face_width;                ///< 人脸宽度（暂不支持）
	uint16_t face_height;               ///< 人脸高度（暂不支持）
    uint8_t age;                        ///< 年龄（透传，不支持此字段时默认值为0）
    uint8_t gender;                     ///< 性别，值参见 @ref IotGenderType （除DH透传外，其它厂商做了转换，不支持时默认值为0）
    uint8_t masks;                      ///< 口罩：0-无效，1-无，2-有，3-面具（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t beard;                      ///< 胡须：0-无效，1-无，2-有（目前只有MEGVII及其B3R盒子支持，不支持时默认值为0）
    uint8_t eye;                        ///< 睁眼：0-无效，1-无，2-有（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t mouth;                      ///< 张嘴：0-无效，1-无，2-有（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t glasses;                    ///< 眼镜：0-无效，1-无，2-普通眼睛，3-太阳镜（目前只有MEGVII和HK支持，不支持时默认值为0）
    uint8_t race;                       ///< 肤色：0-无效，1-黄种人，2-黑种人，3-白种人（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t emotion;                    ///< 表情：0-无效，1-生气，2-平静，3-厌恶，4-困惑，5-高兴，6-悲伤，7-害怕，8-惊讶，9-斜视，10-尖叫（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t smile;                      ///< 微笑：0-无效，1-无，2-有（目前只有MEGVII支持，不支持时默认值为0）
    uint8_t value;                      ///< 颜值（暂不支持）
    uint8_t nation;                     ///< 民族：0-无效，1-汉族，2-少数民族（目前只有MEGVII及其B3R盒子支持，不支持时默认值为0）
    int related_id;                     ///< 人体或车辆关联ID（透传，V4.0版本后，优先使用link_infos字段中内容）
    uint8_t res3[3];                    ///< 预留字段3
    uint8_t link_count;                 ///< 关联对象信息列表个数
    IotLinkInfo link_infos[IOT_MAX_LINK_NUM]; ///< 关联对象信息列表
    IotRectInfo object_rect;            ///< 目标区域，特指在人脸小图中的位置信息
    uint8_t hair;                       ///< 头发：0-无效，1-未知，2-短发，3-长发，4-少发
    uint8_t hair_colour;                ///< 头发颜色（暂不支持）：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t hat;                        ///< 帽子（暂不支持）：0-无效，1-未知，2-无， 3-有
    uint8_t hat_colour;                 ///< 帽子颜色（暂不支持）：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t res2[28];                   ///< 预留字段2（结构体总大小为192字节）
} IotFacePicInfo2;

/// 人体图信息
typedef struct IotBodyPicInfo
{
    int body_id;                        ///< 人体图ID
    int track_face_id;                  ///< 关联的人脸ID（暂未用到）
    uint8_t level;                      ///< 人体图质量，范围[0, 100]
    uint8_t pic_format;                 ///< 图片数据格式，值参见 @ref IotPictureType （目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t res1[5];                    ///< 预留字段1
    uint8_t rect_type;                  ///< 区域坐标值类型：0-无坐标值，1-在全景图中的绝对值，2-在全景图中的千分比
    IotRectInfo rect;                   ///< 人体框图坐标（在全景图中的位置）
    IotRectInfo cut_rect;               ///< 人体抠图坐标（在全景图中的位置）
    uint16_t body_width;                ///< 人体宽度
    uint16_t body_height;               ///< 人体高度
    uint32_t body_len;                  ///< 人体图大小，值大于0时，再从子图数据缓冲区中读取数据（透传）
    uint8_t *body_buf;                  ///< 人体图数据（透传）
    uint8_t rucksack;                   ///< 背包：0-无效，1-未知，2-无， 3-有
    uint8_t hat;                        ///< 帽子：0-无效，1-未知，2-无， 3-有
    uint8_t hat_colour;                 ///< 帽子颜色：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t hair;                       ///< 头发：0-无效，1-未知，2-短发，3-长发，4-少发
    uint8_t hair_colour;                ///< 头发颜色：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t upper_type;                 ///< 上衣款式：0-无效，1-未知，2-长款大衣，3-夹克及牛仔服，4-T恤，5-运动服，6-羽绒服，7-衬衫，8-连衣裙，9-西装，10-长袖，11-短袖
    uint8_t upper_mode;                 ///< 上衣模式：0-无效，1-未知，2-纯色，3-条纹，4-图案，5-拼接，6-格子
    uint8_t upper_colour;               ///< 上身颜色：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t lower_type;                 ///< 裤子类型：0-无效，1-未知，2-短裤，3-长裤，4-裙子，5-长裙，6-短裙
    uint8_t lower_mode;                 ///< 裤子模式：0-无效，1-未知，2-纯色，3-条纹，4-图案，5-拼接，6-格子
    uint8_t lower_colour;               ///< 下身颜色：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t shoes_type;                 ///< 鞋子款式：0-无效，1-未知，2-皮鞋，3-靴子，4-休闲鞋，5-凉鞋
    uint8_t shoes_colour;               ///< 鞋子颜色：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t bags_type;                  ///< 箱包类型：0-无效，1-未知，2-无， 3-单肩，4-双肩，5-手拎，6-腰包，7-拉杆
    uint8_t bags_colour;                ///< 箱包颜色：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t umbrella_type;              ///< 雨伞：0-无效，1-未知，2-未打伞，3-打伞
    uint8_t umbrella_colour;            ///< 雨伞颜色：0-无效，1-未知，2-白色，3-灰色，4-棕色，5-红色，6-蓝色，7-黄色，8-绿色，9-粉色，10-橙色，11-青色，12-紫色，13-浅蓝，14-黑色，15-彩色
    uint8_t something_on_chest;         ///< 胸前抱东西：0-无效，1-未知，2-无， 3-有
    uint8_t direction;                  ///< 运动方向：0-无效，1-未知，2-向上，3-向下，4-向左，5-向右，6-左上，7-左下，8-右上，9-右下
    uint8_t speed;                      ///< 运动状态：0-无效，1-未知，2-静止，3-运动
    uint8_t ride;                       ///< 骑车：0-无效，1-未知，2-无骑车，3-有骑车
    uint8_t age;                        ///< 年龄（透传，不支持此字段时默认值为0）
    uint8_t gender;                     ///< 性别，值参见 @ref IotGenderType （除DH透传外，其它厂商做了转换，不支持时默认值为0）
    uint8_t link_count;                 ///< 关联对象信息列表个数
    IotLinkInfo link_infos[IOT_MAX_LINK_NUM]; ///< 关联对象信息列表
    IotRectInfo object_rect;            ///< 目标区域，特指在人体小图中的位置信息
    uint8_t long_sleeves;               ///< 有无长袖：0-无效，1-未知，2-无，3-有
    uint8_t res2[55];                   ///< 预留字段2（结构体总大小为192字节）
} IotBodyPicInfo;

/// 交通车辆图信息
typedef struct IotItsPicInfo
{
    int its_id;                         ///< 交通图ID（目前仅有HK支持，透传，不支持时默认值为0）
    uint8_t	face_level;                 ///< 图像质量（目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t pic_format;                 ///< 图片数据格式，值参见 @ref IotPictureType （目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t direction;                  ///< 车辆方向：0-无方向，1-正行，2-逆行，3-向上，4-向下，5-向左，6-向右（目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t brand_confidence;           ///< 车标置信度（目前仅有MEGVII支持，透传，不支持时默认值为0）
    int rect_type;                      ///< 区域坐标值类型：0-无坐标值，1-在全景图中的绝对值，2-在全景图中的千分比
    IotRectInfo rect;                   ///< 子图区域（坐标类型为1时透传，为2时根据厂商情况转换为千分比，厂商不支持时值都为0）
    char plate[32];                     ///< 车牌号（MEGVII和HK透传，不支持时默认值为空）
    int  plate_color;                   ///< 车牌颜色，值参见 @ref IotPlateColor （目前仅有MEGVII和HK支持，不支持时默认值为未知-0）
    int  plate_type;                    ///< 车牌类型，值参见 @ref IotPlateType （目前仅有MEGVII和HK支持，不支持时默认值为未知-0）
    int  car_color;                     ///< 车身颜色，值参见 @ref IotVehicleColor （目前仅有MEGVII和HK支持，不支持时默认值为未知-99）
    int  speed;                         ///< 车速（目前仅有HK支持，透传，不支持时默认值为0）
    int  alarm_type;                    ///< 报警类型（暂不支持）
    int  vehicle_brand;                 ///< 车标，值参见 @ref IotVehicleClass （MEGVII透传，HK转换，不支持的默认值为其它-0）
    int  vehicle_type;                  ///< 车辆类型，值参见 @ref IotVehicleType （MEGVII透传，HK转换，不支持的默认值为未知-0）
    IotRectInfo plate_rect;             ///< 车牌位置区域（目前仅有MEGVII支持，不支持时默认值都为0）
    int  plate_len;                     ///< 车牌数据长度，值大于0时，再从数据缓冲区中读取数据（透传）
    uint8_t *plate_data;                ///< 车牌数据（透传）
    uint8_t res2[8];                    ///< 预留字段（结构体总大小为128字节）
} IotItsPicInfo;

/// 交通车辆图信息（扩展版本2）
typedef struct IotItsPicInfo2
{
    int its_id;                         ///< 交通图ID（目前仅有HK支持，透传，不支持时默认值为0）
    uint8_t	level;                      ///< 图像质量（目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t pic_format;                 ///< 图片数据格式，值参见 @ref IotPictureType （目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t moving_status;              ///< 运动状态：0-无效，1-未知，2-静止，3-运动
    uint8_t rect_type;                  ///< 区域坐标值类型：0-无坐标值，1-在全景图中的绝对值，2-在全景图中的千分比
    IotRectInfo rect;                   ///< 子图区域（在全景图中的位置，坐标类型为1时透传，为2时根据厂商情况转换为千分比，厂商不支持时值都为0）
    IotRectInfo plate_rect;             ///< 车牌位置区域（在全景图中的位置，目前仅有MEGVII支持，不支持时默认值都为0）
    IotRectInfo brand_rect;             ///< 车标位置（在全景图中的位置，目前仅有MEGVII支持，不支持时默认值都为0）
    uint32_t its_len;                   ///< 车辆图大小，值大于0时，再从子图数据缓冲区中读取数据（透传）
    uint32_t plate_len;                 ///< 车牌数据长度，值大于0时，再从数据缓冲区中读取数据（透传）
    uint8_t *its_buf;                   ///< 车辆图数据（透传）
    uint8_t *plate_data;                ///< 车牌数据（透传）
    char plate[32];                     ///< 车牌号（MEGVII和HK透传，不支持时默认值为空）
    int alarm_type;                     ///< 报警类型（暂不支持）
    int plate_color;                    ///< 车牌颜色，值参见 @ref IotPlateColor （目前仅有MEGVII和HK支持，不支持时默认值为未知-0）
    int plate_type;                     ///< 车牌类型，值参见 @ref IotPlateType （目前仅有MEGVII和HK支持，不支持时默认值为未知-0）
    int car_color;                      ///< 车身颜色，值参见 @ref IotVehicleColor （目前仅有MEGVII和HK支持，不支持时默认值为未知-99）
    int speed;                          ///< 车速（目前仅有HK支持，透传，不支持时默认值为0）
    int vehicle_brand;                  ///< 车标，值参见 @ref IotVehicleClass （MEGVII透传，HK转换，不支持的默认值为其它-0）
    int vehicle_type;                   ///< 车辆类型，值参见 @ref IotVehicleType （MEGVII透传，HK转换，不支持的默认值为未知-0）
    uint8_t direction;                  ///< 车辆方向：0-无方向，1-正行，2-逆行，3-向上，4-向下，5-向左，6-向右，7-左上，8-左下，9-右上，10-右下（目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t brand_confidence;           ///< 车标置信度（目前仅有MEGVII支持，透传，不支持时默认值为0）
    uint8_t object_type;                ///< 当前抓拍对象类型：0-车或车+牌，1-车牌
    uint8_t link_count;                 ///< 关联对象信息列表个数
    IotLinkInfo link_infos[IOT_MAX_LINK_NUM]; ///< 关联对象信息列表
    IotRectInfo object_rect;            ///< 目标区域，特指在车辆小图中的位置信息
    //uint8_t res2[16];                   ///< 预留字段2（结构体总大小为192字节）
} IotItsPicInfo2;

/// 子图信息
typedef struct IotSubPicInfo
{
    int pic_type;                       ///< 子图类型：1-人脸（对应联合体中的face成员），2-交通（对应联合体中的its成员）
    uint32_t data_len;                  ///< 子图大小，值大于0时，再从子图数据缓冲区中读取数据（透传）
    uint8_t *data_buf;                  ///< 子图数据（透传）
    uint32_t feature_data_len;          ///< 特征值数据长度（目前只有MEGVII支持，透传）
    uint8_t *feature_data;              ///< 特征值数据，值大于0时，再从数据缓冲区中读取数据（目前只有MEGVII支持，透传）
    uint32_t landmark_data_len;         ///< 关键点数据长度（目前只有MEGVII支持，透传）
    uint8_t *landmark_data;             ///< 关键点数据，值大于0时，再从数据缓冲区中读取数据（目前只有MEGVII支持，透传）
    uint32_t extend_data_len;           ///< 扩展数据长度（目前只有MEGVII支持，透传）
    uint8_t *extend_data;               ///< 扩展数据，值大于0时，再从数据缓冲区中读取数据（目前只有MEGVII支持，透传）
    union {
        IotFacePicInfo face;            ///< 人脸子图信息
        IotItsPicInfo  its;             ///< 交通子图信息
    };
} IotSubPicInfo;

/// 人脸底库识别信息
typedef struct IotFaceRecognizeInfo
{
    int group_id;                       ///< 底库ID
    int people_id;                      ///< 底库人员ID
    char group_name[64];                ///< 底库名称
    char people_name[32];               ///< 底库人员名字
    char cert_id[32];                   ///< 证件号
    int cert_type;                      ///< 证件类型，值参见 @ref IotCardType
    float score;                        ///< 相似分数
    uint8_t *data_buf;                  ///< 底库图片数据（透传）
    uint32_t data_len;                  ///< 底库图片数据长度，值大于0时，再从数据缓冲区中读取数据（透传）
    int birth_place;                    ///< 籍贯
    uint8_t	sex;                        ///< 性别，值参见 @ref IotGenderType
    uint8_t nation;                     ///< 民族：0-无效，1-汉族，2-少数民族（目前只有MEGVII部分类型支持，不支持时默认值为0）
    uint8_t res2[6];                    ///< 预留字段2
    char image_mark_id[64];             ///< 底库唯一标识（目前只有MegEye-T和MegEye-R支持）
    uint8_t res[24];                    ///< 预留字段（结构体总大小为256字节）
} IotFaceRecognizeInfo;

/// 车辆底库识别信息
typedef struct IotItsRecognizeInfo
{
    int group_id;                       ///< 底库ID
    int its_id;                         ///< 底库车辆ID
    char group_name[64];                ///< 底库名称
    char its_name[32];                  ///< 底库车牌号
    char cert_id[32];                   ///< 车辆拥有者证件号
    int cert_type;                      ///< 车辆拥有者证件类型，值参见 @ref IotCardType
    float score;                        ///< 相似分数
    uint8_t *data_buf;                  ///< 底库图片数据（透传）
    uint32_t data_len;                  ///< 底库图片数据长度，值大于0时，再从数据缓冲区中读取数据（透传）
    uint8_t res[36];                    ///< 预留字段（结构体总大小为192字节）
} IotItsRecognizeInfo;

/// 底库图检索条件信息
typedef struct IotRecognizeRequestInfo
{
    int group_type;                     ///< 底库类型：0-人脸，1-车辆（暂不支持）
    int group_id;                       ///< 底库ID
    int target_id;                      ///< 底库中目标图ID
    char mark_id[64];                   ///< 底库中目标图标识串
    uint8_t res[52];                    ///< 预留字段（结构体总大小为128字节）
} IotRecognizeRequestInfo;

/// 视频智能分析图片流信息
typedef struct IotVcaPicInfo
{
    //int64_t timestamp;                  ///< UTC时间戳，正值，单位：毫秒
    //uint32_t seq;                       ///< 序号，从0开始，顺序递增
    uint32_t pic_format;                ///< 图片数据格式，值参见 @ref IotPictureType
    uint32_t width;                     ///< 图片宽度（透传，设备sdk不支持此参数时值为0）
    uint32_t height;                    ///< 图片高度（透传，设备sdk不支持此参数时值为0）
    uint32_t data_len;                  ///< 图片数据长度，长度为0时表示无全景图，缓冲区指针无效
    uint8_t *data_buf;                  ///< 图片数据缓冲区
    IotRectInfo target_position;        ///< 目标位置
    int rect_type;                      ///< 区域坐标值类型：0-无坐标值，1-在全景图中的绝对值，2-在全景图中的千分比
    int channel_no;                     ///< 通道号
    int event_type;                     ///< 事件类型
    int rule_id;                        ///< 规则号
    int target_id;                      ///< 目标号
    int target_type;                    ///< 目标类型：1-人，2-其他，3-车
    int target_speed;                   ///< 目标速度（每秒移动的像素数）
    int target_direction;               ///< 目标方向：0-359度
    int preset_no;                      ///< 预设场景号：vca:0~32，alert:0~3
    int alarm_type;                     ///< 报警类型：0-智能分析，1-特色警戒
    int alarm_type_param;               ///< 特色警戒类型（只在类型为特色警戒时有效）：1-周界入侵，2-周界离开，3-绊线
    uint8_t res[104];                   ///< 预留字段
} IotVcaPicInfo;

/// 结构化子图信息
typedef struct IotSubStructureInfo
{
    int have_face;                      ///< 是否有人脸图：0-无，1（其他值）-有
    IotFacePicInfo2 face;               ///< 人脸图信息
    int have_body;                      ///< 是否有人体图：0-无，1（其他值）-有
    IotBodyPicInfo body;                ///< 人体图信息
    int have_its;                       ///< 是否有车辆图：0-无，1（其他值）-有
    IotItsPicInfo2 its;                 ///< 车辆图信息
    int face_ri_num;                    ///< 人脸底库个数，即底库数组中的有效元素个数
    IotFaceRecognizeInfo face_ri[5];    ///< 人脸底库数组
    int its_ri_num;                     ///< 车辆底库个数，即底库数组中的有效元素个数
    IotItsRecognizeInfo its_ri[5];      ///< 车辆底库数组
    int have_vca;                       ///< 是否有视频智能分析图：0-无，1（其他值）-有
    IotVcaPicInfo vca;                  ///< 视频智能分析信息
} IotSubStructureInfo;

/// 抓拍图片流信息
typedef struct IotCapPicturesInfo
{
    int64_t timestamp;                  ///< UTC时间戳，正值，单位：毫秒
    uint32_t seq;                       ///< 序号，从0开始，顺序递增
    uint32_t pic_format;                ///< 全景图图片数据格式，值参见 @ref IotPictureType
    uint32_t full_len;                  ///< 全景图数据长度，长度为0时表示无全景图，缓冲区指针无效
    uint8_t *full_buf;                  ///< 全景图数据缓冲区
    uint32_t sub_num;                   ///< 子图个数，值范围[0, IOT_SUB_PIC_NUM]
    IotSubPicInfo sub_pic[IOT_SUB_PIC_NUM]; ///< 子图数组
    uint8_t res[12];                    ///< 预留字段
} IotCapPicturesInfo;

/// 全结构化图片流信息
typedef struct IotStructurePicturesInfo
{
    int64_t timestamp;                  ///< UTC时间戳，正值，单位：毫秒
    uint32_t seq;                       ///< 序号，从0开始，顺序递增
    uint32_t pic_format;                ///< 全景图图片数据格式，值参见 @ref IotPictureType
    uint32_t full_width;                ///< 全景图宽（透传，设备sdk不支持此参数时值为0）
    uint32_t full_height;               ///< 全景图高（透传，设备sdk不支持此参数时值为0）
    uint8_t *full_buf;                  ///< 全景图数据缓冲区
    uint32_t full_len;                  ///< 全景图数据长度，长度为0时表示无全景图，缓冲区指针无效
    uint8_t res[32];                    ///< 预留字段
    uint32_t sub_num;                   ///< 子图个数，即下面可变数组的大小，等于0时表示无子图，下面的数组不可用
    IotSubStructureInfo sub_pic[1];     ///< 子图的可变数组，根据子图个数直接按数组下标获取子图数据
} IotStructurePicturesInfo;

/// 视频流数据帧信息
typedef struct IotVideoFrameInfo
{
    int64_t timestamp;                  ///< DTS时间戳，正值，单位：1/90000秒
    uint32_t seq;                       ///< 序号，从0开始，顺序递增
    uint8_t encode_type;                ///< 数据编码类型，值参见 @ref IotEncodeType
    uint8_t frame_type;                 ///< 帧类型，值参见 @ref IotFrameType
    uint8_t resolution;                 ///< 分辨率类型，值参见 @ref IotVideoResolutionType
    uint8_t frame_rate;                 ///< 帧率，值范围一般在[0, 120]。此值由服务端直接分析SPS/PPS信息进行获取，当获取不到或值异常时置为0（若调用者必须依赖此字段，建议其累计多帧数据进行计算）
    uint8_t res[8];                     ///< 预留字段
} IotVideoFrameInfo;

/// 视频流数据帧参数信息（视觉IoT扩展版本）
typedef struct IotVideoFrameParam
{
    int64_t timestamp;                  ///< DTS时间戳，正值，单位：1/90000秒
    uint32_t seq;                       ///< 序号，从0开始，顺序递增
    uint32_t width;                     ///< 视频图像宽度
    uint32_t height;                    ///< 视频图像高度
    uint8_t encode_type;                ///< 数据编码类型，值参见 @ref IotEncodeType
    uint8_t frame_type;                 ///< 帧类型，值参见 @ref IotFrameType
    uint8_t frame_rate;                 ///< 帧率，值范围一般在[0, 120]。此值由服务端直接分析SPS/PPS信息进行获取，当获取不到或值异常时置为0（若调用者必须依赖此字段，建议其累计多帧数据进行计算）
    uint8_t avg_frame_rate;             ///< 平均帧率，由流媒体服务实时计算所得
    uint8_t profile;                    ///< 编码档次，值范围参见相关标准协议文档（如H264包括44-CAVLC, 66-Baseline, 77-Main, 88-Extended, 100-High, 110-High_10, 122-High_422, 244-High_444, 118-Multiview_High, 128-Stereo_High；
                                        ///< H265包括1-Main, 2-Main_10, 3-Main_Still_Picture, 4-Rext等）
    uint8_t res[39];                    ///< 预留字段（共64字节）
} IotVideoFrameParam;

/// 流通知消息结构体
typedef struct IotStreamNotifyInfo
{
    char dev_id[IOT_LEN_DEVID];         ///< 设备标识号
    IOT_HANDLE handle;                  ///< 流句柄
    int error;                          ///< 错误号
    void *user_data;                    ///< 流数据回调对应的调用者用户参数
    uint8_t frame_rate;                 ///< 帧率，此值由服务端直接分析SPS/PPS信息进行获取，当获取不到或值异常时为0
    uint8_t avg_frame_rate;             ///< 平均帧率，由sdk内部实时统计所得
    uint8_t res[22];                    ///< 预留字段（共64字节）
} IotStreamNotifyInfo;

/// 设备升级状态通知结构体
typedef struct IotUpgradeStateNotify
{
    char dev_id[IOT_LEN_DEVID];         ///< 设备标识号
    int  step;                          /**< 升级步骤
                                             0:unstart
                                             1-down:下载升级文件过程
                                             2-send file:发送文件进度（发送升级包到设备）
                                             3-send file ok:发送文件完成
                                             4-send file fail:发送升级文件失败，升级过程终止
                                             5-upgrade:设备升级进度
                                             6-upgrade ok:升级完成
                                             7-upgrade fail:升级过程中发送错误失败，升级过程终止
                                             8-restart:重启进度 */

    int  process;                       /**< 升级进度
                                             step为1时，进度0~100: 下载升级文件过程
                                             step为2时，进度0~100: 发送文件进度
                                             step为3时，进度0: 发送文件完成
                                             step为5时，进度0~100: 升级过程进度，进度515: 升级完成，需要重启
                                             step为6时，进度0: 升级完成
                                             step为7时，进度5006：设备不存在，进度5023：设备不在线
                                             step为8时，进度1: 升级过程结束等待设备重启，进度50: 设备正在重启，进度100: 设备重启成功，小于0: 失败错误返回 */
} IotUpgradeStateNotify;

/// 底库下发设备状态信息
typedef struct IotRcgLibDevStatus
{
    char dev_id[IOT_LEN_DEVID];         ///< 设备标识号
    int  status;                        ///< 当前设备的执行状态：0-未开始，1-已完成，2-执行中，3-执行失败
    int  send_num;                      ///< 下发图片成功个数
    int  error_num;                     ///< 下发图片失败个数
    char misdescription[128];           ///< 错误描述信息
} IotRcgLibDevStatus;

/// 底库下发状态通知信息
typedef struct IotRcgLibAddStateNotify
{
	char task_id[IOT_LEN_SESSION];      ///< 任务ID号
    int  pic_sum;                       ///< 底库图总数
    int  dev_count;                     ///< 设备总数
    IotRcgLibDevStatus dev_list[IOT_MAX_LST_NUM];///< 设备列表
} IotRcgLibAddStateNotify;

/// 设备版本信息
typedef struct IotDeviceVersionInfo
{	
	char firmware[IOT_LEN_VERSION];     ///< 固件版本
	char algorithm[IOT_LEN_VERSION];    ///< 算法版本
} IotDeviceVersionInfo;

/// 设备算法信息
typedef struct IotDeviceAlgorithmInfo
{
	uint8_t status;                     ///< 算法工作状态，值参见 @ref IotDeviceWorkStatus
    uint8_t res[31];                    ///< 预留字段
} IotDeviceAlgorithmInfo;

/// 设备图片流参数信息
typedef struct IotPictureStreamParam
{
    int  resolution;                    ///< 分辨率类型（部分类型设备会和视频共用此参数，此时此值可能不生效），值参见 @ref IotVideoResolutionType
    uint8_t pic_quality;                ///< 图片质量，范围在[1-100]
    uint8_t upload_panorama;            ///< 是否上传全景图：0-不上传，1-上传
    uint8_t upload_strategy;            ///< 推图策略：1-最快，2-最优
    uint8_t snap_mode;                  ///< 抓拍模式：1-全抓模式，2-高质量模式，3-用户自定义
    uint8_t snap_num;                   ///< 抓拍张数，范围在[1-3]
    uint8_t recognize_mode;             ///< 识别模式：1-门禁模式，2-VIP模式
    uint8_t recog_upload_num;           ///< 识别结果推送次数：范围在[1-10]
    uint16_t recog_upload_interval;     ///< 识别结果推送间隔，单位：毫秒，常用值如：100/300/500/1000
    uint16_t min_face_pixels;           ///< 人脸最小像素，默认60，范围在[30-800]
    uint8_t res[113];                   ///< 预留字段
} IotPictureStreamParam;

/// 设备视频流参数信息
typedef struct IotVideoStreamParam
{	
    int  profile_type;                  ///< 通道码流类型，值参见 @ref IotChanProfileType
    int  bitrate_type;                  ///< 码率控制类型，值参见 @ref IotRateControlType
    int  bitrate;                       ///< 码率，单位：kbps
    int  frame_rate;                    ///< 帧率，值范围[0, 120]，常用值如：15/25/30/60
    int  resolution;                    ///< 分辨率类型，值参见 @ref IotVideoResolutionType
    uint16_t iframe_interval;           ///< I帧间隔，一般为帧率的整数倍，常用值如：25/30/50/60
    uint8_t res[42];                    ///< 预留字段
} IotVideoStreamParam;

/// 设备全景图开关及压缩比参数
typedef struct IotPanoramaParam
{
    int  open_flag;                     ///< 全景图开关：0-关，1-开
    int  compress_ratio;                ///< 全景图压缩比
} IotPanoramaParam;

/// 设备分辨率能力集
typedef struct IotResolutionCapability
{	
    int  profile_type;                  ///< 通道码流类型，值参见 @ref IotChanProfileType
    int  num;                           ///< 分辨率个数
    int  list[IOT_MAX_LST_NUM];         ///< 分辨率类型列表，元素值参见 @ref IotVideoResolutionType
} IotResolutionCapability;

/// 设备模式能力集
typedef struct IotCameraModeCapability
{
    int  num;                           ///< 支持的模式类型个数
    int  list[32];                      ///< 支持的模式类型列表，元素值参见 @ref IotCameraMode
} IotCameraModeCapability;

/// 设备参数信息
typedef struct IotDeviceParams
{
    int vendor;                         ///< 厂商ID号
    char model[IOT_LEN_CODE];           ///< 设备型号
    char firmware[IOT_LEN_VERSION];     ///< 固件版本
	char algorithm[IOT_LEN_VERSION];    ///< 算法版本
    char serial_no[64];                 ///< 设备序列号
    uint8_t res[668];                   ///< 预留字段（结构体总大小为1024字节）
} IotDeviceParams;

/// 日期时间结构体
typedef struct IotDateTime
{
    uint16_t    year;                   ///< 年
    uint16_t    month;                  ///< 月
    uint16_t    day;                    ///< 日
    uint16_t    hour;                   ///< 时
    uint16_t    minute;                 ///< 分
    uint16_t    second;                 ///< 秒
    uint32_t    millisecond;            ///< 毫秒
} IotDateTime;

/// NTP服务器校时信息
typedef struct IotNtpServerInfo
{
    char server_addr[64];               ///< NTP服务器域名或地址
    uint16_t server_port;               ///< NTP服务器端口
    int interval;                       ///< 校时间隔，单位：分钟，需为60的整数倍，范围在[60, 720*60]
} IotNtpServerInfo;

/// 设备批量校时信息结构体
typedef struct IotTimingInfo
{
    int type;                           ///< 校时类型，值参见 @ref IotTimingType
    union {
        IotDateTime datetime;           ///< 手工校时时间（UTC时间）
        IotNtpServerInfo ntp;           ///< NTP校时服务器信息
    };
    int dev_num;                        ///< 设备个数，大小不能超过 @ref IOT_MAX_LST_NUM, 超过此值请分多次校时
    char dev_list[IOT_MAX_LST_NUM][IOT_LEN_DEVID]; ///< 设备列表
} IotTimingInfo;

/// 设备校时回复消息结构体
typedef struct IotDeviceTimingNotify
{
    int error;                          ///< 错误号
    int dev_num;                        ///< 设备个数
    char dev_list[IOT_MAX_LST_NUM][IOT_LEN_DEVID]; ///< 设备列表
    int dev_status[IOT_MAX_LST_NUM];    ///< 校时结果：0表示成功，其他值表示失败
} IotDeviceTimingNotify;

/// 设备批量升级信息结构体
typedef struct IotDeviceUpgradeInfo
{
    char file_url[IOT_LEN_URL];         ///< 升级文件所在路径的URL
    int dev_num;                        ///< 设备个数，大小不能超过 @ref IOT_MAX_LST_NUM, 超过此值请分多次升级
    char dev_list[IOT_MAX_LST_NUM][IOT_LEN_DEVID]; ///< 设备列表
} IotDeviceUpgradeInfo;

/// 设备底库下发信息结构体
typedef struct IotDeviceRcgLibInfo
{
    char task_id[IOT_LEN_SESSION];      ///< 任务ID号
    char file_url[IOT_LEN_URL];         ///< 底库文件所在路径的URL
    char group_name[64];                ///< 底库名称
    char extra_info[64];                ///< 底库附件描述信息
    int  search_threshold;              ///< 识别比对阈值[0-100]
    int  top_rank;                      ///< 上报识别得分超过阈值的排名靠前的底库人脸个数[1-5]
    int  dev_num;                       ///< 设备个数，大小不能超过 @ref IOT_MAX_LST_NUM, 超过此值请分多次下发
    char dev_list[IOT_MAX_LST_NUM][IOT_LEN_DEVID]; ///< 设备列表
} IotDeviceRcgLibInfo;

/// 设备报警输入配置信息
typedef struct IotAlarmInConfig
{
    uint8_t alarm_mode;                 ///< 端子工作模式：0-常开，1-常闭
    uint8_t enabled;                    ///< 是否启用：0-未启用，1-启用
    uint8_t res[126];                   ///< 预留字段
} IotAlarmInConfig;

/// 设备报警输出配置信息
typedef struct IotAlarmOutConfig
{
    uint8_t alarm_mode;                 ///< 端子工作模式：0-常开，1-常闭
    uint16_t delay_time;                /**< 输出信号状态维持时间，单位：秒，范围一般在[0-600]，无符号双字节最大值65535表示一直维持，需手工关闭；
                                             若设备不支持设定的大小，系统内部会找一个最接近的值 */
    uint8_t res[61];                    ///< 预留字段
} IotAlarmOutConfig;

/*/// 设备AI类型报警配置信息
typedef struct IotAiAlarmConfig
{
    uint32_t alarm_type;                ///< 报警类型，参见 @ref IotDeviceAlarmType
    uint8_t res[28];                    ///< 预留字段
} IotAiAlarmConfig;*/

/// 设备通用事件/报警信息
typedef struct IotDeviceAlarmInfo
{
    int64_t timestamp;                  ///< UTC时间戳，单位：毫秒
    char dev_id[IOT_LEN_DEVID];         ///< 设备标识号
    uint8_t chan_no;                    ///< 输入端子通道号，与通道无关的类型，此值默认为0
    uint8_t main_type;                  ///< 报警主类型，参见 @ref IotDeviceAlarmMainType
    uint16_t alarm_type;                ///< 报警类型，参见 @ref IotDeviceAlarmType
    uint8_t  alarm_state;               ///< 报警状态：0-报警，1-消警
    uint8_t  is_channel;                ///< 消息是否为通道类型：0-设备，1-通道
    uint32_t capture_num;               ///< 指定时间间隔内的抓拍量
    uint8_t res[22];                    ///< 预留字段
    char chan_id[IOT_LEN_DEVID];        ///< 通道标识号
    char alarm_params[2048];            ///< 报警参数（json串，适用于参数较多的情况，如警戒报警消息）
} IotDeviceAlarmInfo;

/// 人脸比对结果报警信息
typedef struct IotFaceMatchAlarmInfo
{
    int64_t timestamp;                  ///< UTC时间戳，单位：毫秒
    char dev_id[IOT_LEN_DEVID];         ///< 设备标识号
    uint8_t chan_no;                    ///< 通道号
    uint8_t similarity;                 ///< 相似度，取值范围：[1-100]
    uint32_t face_id;                   ///< 抓拍人脸ID
    uint32_t blacklist_face_id;         ///< 黑名单库中的人脸ID
    uint8_t res[86];                    ///< 预留字段
} IotFaceMatchAlarmInfo;

/// 录像另存为功能结果通知信息
typedef struct IotRecordSaveNotify
{
    int error;                          ///< 错误号，值参见 @ref IotErrorType
    char dev_id[IOT_LEN_DEVID];         ///< 设备标识号
    char sess_id[IOT_LEN_SESSION];      ///< 会话标识号
    char file_url[IOT_LEN_URL];         ///< 小视频文件在存储系统上的URL地址
    char resource_id[IOT_LEN_URL];      ///< 返回的小视频文件资源标识号，目前存储到ObjectStorage时此值有效（洞鉴、灵探可能用到）
    uint8_t res[36];                    ///< 预留字段
} IotRecordSaveNotify;

/// IoT服务器节点统计信息
typedef struct IotServerNodeInfo
{
    char node_addr[IOT_LEN_ADDR];       ///< 节点地址（域名或主机名或IP地址）
    uint8_t node_type;                  ///< 节点类型：1-主控节点，2-工作节点
    uint8_t node_status;                ///< 节点状态，值参见 @ref IotDeviceWorkStatus
    uint32_t device_num;                ///< 管理的设备总数
    uint32_t stream_in_num;             ///< 接入流总数
    uint32_t stream_out_num;            ///< 转发流总数
    uint32_t picture_per_hour;          ///< 每小时抓拍图片数
    uint32_t alarm_per_hour;            ///< 每小时报警数
    uint8_t res[74];                    ///< 预留字段
} IotServerNodeInfo;

/// 设备录像缓存配置信息
typedef struct IotDeviceCacheInfo
{
    char server_addr[IOT_LEN_ADDR];     ///< 服务IP或域名地址
    uint16_t server_port;               ///< 服务端口号
    uint16_t cache_type;                ///< 缓存类型（暂未用到）
    uint8_t res[28];                    ///< 预留字段
} IotDeviceCacheInfo;


//=============================================================================
// = 回调函数类型声明

/**
 * 消息回调函数
 *
 * @param  msg_type: 消息类型，值参见 @ref IotMessageType
 * @param  content: 消息内容（类型不同，对应的内容不同，包括设备ID、服务器名称及结构体等，参见消息类型说明）
 * @param  content_len: 消息内容长度
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_Message) (IN int           msg_type,
                                        IN const char *  content,
                                        IN int           content_len,
                                        IN void *        user_data);

/**
 * 设备列表回调函数
 *
 * @param  dev_list: 设备列表
 * @param  dev_num: 列表中设备个数，0表示当前系统中无设备
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_DeviceList) (IN IotDeviceInfo *   dev_list,
                                           IN int               dev_num,
                                           IN void *            user_data);

/**
 * 设备发现列表回调函数
 *
 * @param  session_id: 获取接口返回的会话标识号
 * @param  dev_list: 设备列表
 * @param  dev_num: 列表中设备个数，0表示当前系统中无设备
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_DeviceDiscoveryList) (IN const char *             session_id,
                                                    IN IotDeviceDiscoveryInfo * dev_list,
                                                    IN int                      dev_num,
                                                    IN void *                   user_data);

/**
 * 设备目录回调函数
 *
 * @param  platform_id: GB平台ID
 * @param  dev_id: 设备ID
 * @param  catalog_list: 设备目录列表
 * @param  catalog_num: 列表中目录个数
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_DeviceCatalog) (IN const char *               platform_id, 
                                              IN const char *               dev_id,
                                              IN const IotGbDeviceCatalog * catalog_list, 
                                              IN int                        catalog_num,
                                              IN void *                     user_data);

/**
 * 平台设备目录回调函数（精简版）
 *
 * @param  platform_id: 国标平台ID
 * @param  dev_id: 设备ID
 * @param  catalog_list: 设备目录列表
 * @param  catalog_num: 列表中目录个数
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_LiteDeviceCatalog) (IN const char *                   platform_id, 
                                                  IN const char *                   dev_id,
                                                  IN const IotLiteDeviceCatalog *   catalog_list, 
                                                  IN int                            catalog_num,
                                                  IN void *                         user_data);

/**
 * 平台设备目录批量回调函数（精简版）
 *
 * @param  session_id: 获取接口返回的会话标识号
 * @param  platform_id: 国标平台ID
 * @param  dev_id: 设备ID
 * @param  catalog_list: 设备目录列表
 * @param  catalog_num: 列表中目录个数
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_BatchDeviceCatalog) (IN const char *                  session_id,
                                                   IN const char *                  platform_id,
                                                   IN const char *                  dev_id,
                                                   IN const IotLiteDeviceCatalog *  catalog_list,
                                                   IN int                           catalog_num,
                                                   IN void *                        user_data);

/**
 * 历史视频流片段检索回调函数
 *
 * @param  dev_id: 设备ID
 * @param  clip_list: 录像片段列表，连续内存存储，可用数组方式访问
 * @param  clip_num: 列表中片段个数，值大于等于0
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_ClipList) (IN const char *                dev_id,
                                         IN const IotRecordClipInfo *   clip_list,
                                         IN int                         clip_num,
                                         IN void *                      user_data);

/**
 * 设备目录列表回调函数
 *
 * @param  dev_list: 设备目录列表，json格式样例如下：
 * {
 *     "pageSize" : 50,     // 设备分页大小
 *     "deviceSum" : 2,     // 设备及通道总数
 *     "deviceList" : [     // 设备列表数组
 *     {
 *         "deviceId" : "110000200100000215",   // 设备标识号
 *         "name" : "中关村大街东路口",            // 设备名称
 *         "type" : 1,                          // 设备类型（必选项），参见 @ref IotDeviceType
 *         "vendorId" : 11,                     // 设备厂商（必选项），参见 @ref IotDeviceVendor
 *         "addr" : "192.168.0.8",                  // 设备地址（类型为1/2/4/5/9时为必选项）
 *         "port" : 8000,                           // 信令端口号（类型为1/2/4/5/9时为必选项）
 *         "videoPort" : 554,                       // 视频流端口号（类型为2/5时为必选项）
 *         "username" : "admin",                    // 用户名（类型为1/2/4/5/9时为必选项）
 *         "password" : "12345",                    // 密码（类型为1/2/4/5/9时为必选项）
 *         "platformId" : "3402000000132xxxxxxx",   // 国标平台标识（类型为3/6时为必选项）
 *         "deviceCode" : "3402000000131xxxxxxx",   // 国标设备编码（类型为3/6时为必选项）
 *         "channelNum" : 1,                        // 通道个数（必选项）
 *         "onlineStatus" : 1                       // 是否在线：0-掉线，1-在线，2-未知
 *     }]
 *     "channelList" : [    // 通道列表数组
 *     {
 *         "channelId" : "110000200100000005",      // 通道标识号（必选项）
 *         "parentId" : "110000200100000215",       // 所属的设备或平台标识号（必选项）
 *         "capability" : 1,                        // 通道能力，参见 @ref IotChannelCapability
 *         "name" : "中关村大街路口1号",               // 通道名称
 *         "channelNo" : 0,                         // 通道号，起始值从0开始（通道类型为设备时必选）
 *         "channelCode" : "3402000000131xxxxxxx",  // 通道编码（通道类型为平台时必选）
 *         "url" : "rtsp://1.2.3.4/554",            // 取流地址串，可为相机rtsp串、kafka抓拍流地址串等（kafka类型相机时为必选项）
 *         "topicName" : "xxx",                     // kafka的topic名称串（kafka类型相机时为必选项）
 *         "extraInfo" : ""                         // 额外信息字段，用于透传上层业务的“其他”字段信息，一般为json串
 *     }]
 * }
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_CatalogList) (IN const char *  dev_list,
                                            IN void *        user_data);

/**
 * 平台设备目录回调函数
 *
 * @param  session_id: 获取接口返回的会话标识号
 * @param  platform_id: 国标平台ID
 * @param  dev_id: 设备ID
 * @param  catalog_list: 设备目录列表，json格式样例如下：
 * {
 *     "catalogList" : [    // 设备目录数组
 *     {
 *         "isCatalog" : 0,             // 是否为目录：0-否（设备），1-是（目录）
 *         "name" : "abc",              // 子设备名称
 *         "subDeviceId" : "xxx",       // 子设备ID
 *         "parentId" : "yyy",          // 父节点ID
 *         "civilCode" : "10",          // 行政区域
 *         "longitude" : "112.123456",  // 经度
 *         "latitude" : "78.654321"     // 纬度
 *     }]
 * }
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_PlatformDeviceCatalog) (IN const char *  session_id,
                                                      IN const char *  platform_id,
                                                      IN const char *  dev_id,
                                                      IN const char *  catalog_list,
                                                      IN void *        user_data);

/**
 * 图片流回调函数
 *
 * @param  handle: 数据流句柄
 * @param  info: 图片信息，含全景图及人脸/交通子图等图像数据及属性字段
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_PictureStream) (IN IOT_HANDLE                 handle, 
                                              IN const IotCapPicturesInfo * info, 
                                              IN void *                     user_data);

/**
 * 全链条结构化数据字典图片流回调函数
 *
 * @param  handle: 数据流句柄
 * @param  pic_info: json串格式的图片信息，含全景图及脸/人/车/非等子图相关属性信息，具体格式参照全链条字典数据文档
 * @param  pic_len: 二进制图片数据长度数组
 * @param  pic_data: 二进制图片数据数组，数据长度由上面数组对应索引的长度决定
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_PicStream) (IN IOT_HANDLE     handle,
                                          IN const char *   pic_info,
                                          IN int            pic_len[],
                                          IN uint8_t *      pic_data[],
                                          IN void *         user_data);

/**
 * 全结构化信息图片流回调函数
 *
 * @param  handle: 数据流句柄
 * @param  info: 全结构化信息，含全景图及人脸/人体/机动车/非机动车子图等图像数据及结构化属性字段
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_StructureStream) (IN IOT_HANDLE                       handle,
                                                IN const IotStructurePicturesInfo * info,
                                                IN void *                           user_data);

/**
 * 警戒图片流回调函数
 *
 * @param  handle: 数据流句柄
 * @param  info: 警戒图片及相关参数信息
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_AlertPictureStream) (IN IOT_HANDLE            handle,
                                                   IN const IotVcaPicInfo * info,
                                                   IN void *                user_data);

/**
 * 数据流回调函数（包含json串格式及图片流数据）
 *
 * @param  handle: 数据流句柄
 * @param  text_buf: 文本串缓冲区指针，一般为json格式字符串
 * @param  text_len: 文本串长度，值大于0时，缓冲区指针才有效
 * @param  buf: 二进制数据缓冲区指针（保留值）
 * @param  buf_len: 二进制数据长度，值大于0时，缓冲区指针才有效（保留值）
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可F
 */
typedef int (CALLBACK *IOT_CB_DataStream) (IN IOT_HANDLE    handle, 
                                           IN const char *  text_buf,
                                           IN int           text_len, 
                                           IN const void *  buf, 
                                           IN int           buf_len,
                                           IN void *        user_data);

/**
 * 视频流回调函数
 *
 * @param  handle: 数据流句柄
 * @param  info: 帧参数信息
 * @param  buf: 数据缓冲区
 * @param  len: 数据长度，值大于0时，缓冲区指针才有效
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_VideoStream) (IN IOT_HANDLE               handle, 
                                            IN const IotVideoFrameInfo *info, 
                                            IN const uint8_t *          buf, 
                                            IN int                      len, 
                                            IN void *                   user_data);
/**
 * 视频流回调函数（视觉IoT中台扩展版本）
 *
 * @param  handle: 数据流句柄
 * @param  video_info: 流参数信息
 * @param  buf: 数据缓冲区
 * @param  len: 数据长度，值大于0时，缓冲区指针才有效
 * @param  user_data: 调用者用户参数，由调用者在开流时传入
 *
 * @return 当前版本暂未用到返回值，始终返回0即可
 */
typedef int (CALLBACK *IOT_CB_VidStream) (IN IOT_HANDLE                 handle,
                                          IN const IotVideoFrameParam * video_info,
                                          IN const uint8_t *            buf,
                                          IN int                        len,
                                          IN void *                     user_data);

#endif
