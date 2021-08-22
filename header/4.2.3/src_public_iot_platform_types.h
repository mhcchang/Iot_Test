/*******************************************************************************
 * @file        iot_platform_type.h
 * @brief       Type definition file of IoT vision platform SDK
 *
 * @authors     flowstar
 * @copyright   All rights reserved
 *
 * Modification History:
 * -----------------------------------------------------------------------------
 * Date        Author        Description
 * -----------------------------------------------------------------------------
 * 2020-07-17  flowstar      Create the file
 *
 ******************************************************************************/
#ifndef _INCLUDE_IOT_VISION_PLATFORM_SDK_TYPE__H_
#define _INCLUDE_IOT_VISION_PLATFORM_SDK_TYPE__H_
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

/// 设备类型
typedef enum IotDeviceType
{
    IOT_DT_IPC          = 1,    ///< 视频流相机（只支持视频流）
    IOT_DT_SMART_IPC    = 2,    ///< 智能相机（含抓拍机、识别机、结构化相机等，可支持视频流及图片流）
    IOT_DT_GB28181_IPC  = 3,    ///< GB28181平台相机（只支持视频流）
    IOT_DT_BOX          = 4,    ///< 智能盒（含NVR等，一般支持视频流及图片流）
    IOT_DT_CLOUD_IPC    = 5,    ///< 云端协同相机
    IOT_DT_GA1400_IPC   = 6,    ///< GA1400平台相机（只支持图片流）
    IOT_DT_MULTI_CHAN   = 9,    ///< 多通道设备（含双目、枪球一体化、双光热成像相机等可以包含多个通道的设备）
} IotDeviceType;

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
    IOT_DV_KAFKA        = 9,    ///< KAFKA相机（暂不支持）
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

    //注：枚举值[90~99]暂时预留给内部服务用
    IOT_DV_YF           = 100,  ///< 云天励飞（暂不支持）
    IOT_DV_JVT          = 101,  ///< 深圳巨龙（暂不支持）
    IOT_DV_DG           = 102,  ///< 格林深瞳（暂不支持）
    IOT_DV_CW           = 103,  ///< 云从（暂不支持）
} IotDeviceVendor;

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
     *     "profileType" : 0    // 通道码流类型：0-主码流，1-子码流，2-第二子码流
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
     *     "profileType" : 0    // 通道码流类型：0-主码流，1-子码流，2-第二子码流
     * }
     * GET回复内容、SET请求参数如下：
     * {
     *     "channelNo" : 0,             // 设备通道号，从0开始
     *     "profileType" : 0,           // 通道码流类型：0-主码流，1-子码流，2-第二子码流
     *     "bitrateType" : 0,           // 码率控制类型：0-定码率，1-变码率
     *     "bitrate" : 2000,            // 码率，单位：kbps
     *     "frameRate" : 25,            // 帧率，值范围[0, 120]，常用值如：15/25/30/60
     *     "resolution" : "1920x1080",  // 分辨率
     *     "iFrameInterval" : 50        // I帧间隔，一般为帧率的整数倍，常用值如：25/30/50/60
     * }
     * SET回复内容：无
     */
    IOT_DCC_VIDEO               = 11,   ///< 视频流参数  [通道，GET/SET]

    /**
     * GET请求参数如下：
     * {
     *     "channelNo" : 0,     // 设备通道号，从0开始
     *     "profileType" : 0    // 通道码流类型：0-主码流，1-子码流，2-第二子码流
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
     *     "channelNo" : 0  // 报警端子通道号，从0开始
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
     *     "channelNo" : 0  // 报警端子通道号，从0开始
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

/// 设备取流类型
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

/// 媒体流类型
typedef enum IotStreamType
{
    IOT_ST_PICTURE = 0,     ///< 实时图片流
    IOT_ST_LIVE,            ///< 实时视频流
    IOT_ST_CLIP,            ///< 历史视频流
    IOT_ST_TEXT,            ///< 文本数据流
    IOT_ST_ALERT,           ///< 警戒图片流
} IotStreamType;

/// 视频数据编码类型
typedef enum IotEncodeType
{
    IOT_ET_H264 = 0,        ///< H264
    IOT_ET_H265,            ///< H265
    IOT_ET_SVAC,            ///< SVAC
} IotEncodeType;

/// 数据帧类型
typedef enum IotFrameType
{
    IOT_FT_SMART = 0,       ///< 智能数据帧（含可能的特定文件头）
    IOT_FT_I,               ///< I帧
    IOT_FT_P,               ///< P帧
    IOT_FT_B,               ///< B帧
} IotFrameType;

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
    IOT_MC_DEVICE       = (0x1 << 2),       ///< 设备（包括消息通知类型：0/1/4/50/51/101）
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
    IOT_MT_DEV_OPEN_FAIL    = 10,   ///< 打开传感器设备失败（只有调用该操作的客户端才会收到此通知），回调参数content内容为设备ID串
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

    IOT_MT_VIDEO_DIAGNOSE_RESULT= 502,  ///< 视频诊断结果通知，回调参数content内容为json串，格式参见 http://api-insight.cbg.megvii-inc.com/project/1425/interface/api/215650
} IotMessageType;


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


/// 设备参数信息（用于设备发现功能）
typedef struct IotDeviceDiscoveryInfo
{
    char ip[IOT_IPV6_LEN];              ///< 设备IP地址串
    uint16_t port;                      ///< 设备端口
    uint8_t res[80];                    ///< 预留字段（结构体总大小为128字节）
} IotDeviceDiscoveryInfo;

/// 历史视频流片段信息结构体
typedef struct IotRecordClipInfo
{
    char start_time[IOT_LEN_TIME];      ///< 开始时间
    char end_time[IOT_LEN_TIME];        ///< 结束时间
} IotRecordClipInfo;

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
    uint8_t res[40];                    ///< 预留字段（共64字节）
} IotVideoFrameParam;

/// 流通知消息结构体
typedef struct IotStreamNotifyInfo
{
    char dev_id[IOT_LEN_DEVID];         ///< 设备标识号
    IOT_HANDLE handle;                  ///< 流句柄
    int error;                          ///< 错误号
    void *user_data;                    ///< 流数据回调对应的调用者用户参数
    uint8_t res[24];                    ///< 预留字段（共64字节）
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

/// 设备校时回复消息结构体
typedef struct IotDeviceTimingNotify
{
    int error;                          ///< 错误号
    int dev_num;                        ///< 设备个数
    char dev_list[IOT_MAX_LST_NUM][IOT_LEN_DEVID]; ///< 设备列表
    int dev_status[IOT_MAX_LST_NUM];    ///< 校时结果：0表示成功，其他值表示失败
} IotDeviceTimingNotify;

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
 * 视频流回调函数
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
