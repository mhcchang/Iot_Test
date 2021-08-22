/*******************************************************************************
 * @file        iot_center_sdk.h
 * @brief       Interface file of IoT Center Client SDK
 *
 * @authors     flowstar
 * @copyright   All rights reserved
 *
 * Modification History:
 * -----------------------------------------------------------------------------
 * Date        Author        Description
 * -----------------------------------------------------------------------------
 * 2018-11-06  flowstar      Create the file
 * 2018-12-21  flowstar      Add some synchronous APIs for open stream
 * 2019-01-22  flowstar      Update to v2.0: support cloud & terminal camera
 * 2019-02-26  flowstar      Add record retrieve and download APIs
 * 2019-05-20  flowstar      Update to v2.1: add clip playback control APIs
 * 2019-06-10  flowstar      Update to v3.0: add APIs of PTZ control & alarm in/out control
 * 2019-08-13  flowstar      Update to v3.1: add APIs of wifi detection device
 * 2019-09-25  flowstar      Update to v3.2: add support for GA1400
 * 2020-01-02  flowstar      Add support for record cache APIs
 * 2020-01-14  flowstar      Update to v3.3: add APIs of record & KeyFrame & extend open stream
 * 2020-04-21  flowstar      Update to v4.0: add alert APIs & more feature APIs
 * 2020-11-30  flowstar      Update to v4.1: add vision IoT APIs
 *
 ******************************************************************************/
#ifndef _INCLUDE_IOT_CENTER_CLIENT_SDK__H_
#define _INCLUDE_IOT_CENTER_CLIENT_SDK__H_
#pragma once
#include "iot_center_types.h"
#include "iot_center_errors.h"

/// 导出接口定义
#ifdef _WIN32
# ifdef IOT_SDK_EXPORTS
#   define IOT_API __declspec(dllexport)
# else
#   define IOT_API __declspec(dllimport)
# endif
#else
# define IOT_API __attribute__((visibility("default")))
#endif//_WIN32

/// 重定义句柄宏
#ifdef HANDLE
# undef HANDLE
#endif
#define HANDLE  IOT_HANDLE

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 接口概述
 * @note  1、接口较多，按功能主要分为：系统相关、设备管理、设备参数配置、设备控制、国标平台相关、实时流管理、历史流管理及业务相关等几类
 *        2、和服务端直接交互的接口一般都含参数 ext_info，主要用于后续扩展交互字段，SDK只负责透传，非必选项，可能的格式样例如下：
 * {
 *     "traceId" : "74019b8819a06b31-80b1f7d51771c6b8-74019b8819a06b31-1"   // 全链路业务跟踪ID，CBG后续业务要求此参数为必填项
 * }
 *        3、v4.1后，sdk内部会用TCP短连接一个集群中的多个master实例发送命令消息，但涉及到数据库的增删改和异步通知消息接口时还是采用主master连接发送
 *        4、对于新增接口来说，入参设备ID逐渐向通道ID转换，因此若为非多通道设备，传入的通道ID可等同于设备ID
 */


/**
 * @name SDK库系统级接口，除消息回调外都是本地调用，与IoT系统没有信令交互
 * @{
 */

/**
 * 初始化库
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   需在使用其他函数前第一个被调用
 */
IOT_API int STDCALL IOT_Startup(void);

/**
 * 释放库
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   需在其他函数后最后一个被调用，用于释放库内部相关资源；
 *         若之前已成功注册到服务器上，请确保注销后再调用此函数
 */
IOT_API int STDCALL IOT_Cleanup(void);

/**
 * 设置连接服务器时的相关参数
 *
 * @param  timeout: 连接超时等待时间，单位：毫秒，默认值为2000毫秒
 * @param  retry_num: 首次连接失败时的重试次数，默认值为2次（加上主动调用的1次，共3次）
 * @param  reconnect: 服务器异常断开时是否需要自动重连：0-不重连，非0-自动重连
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   建议在注册到服务器前调用，不调用时库内部按上面提到的默认值工作
 */
IOT_API int STDCALL IOT_SetConnectInfo(IN int timeout,
                                       IN int retry_num,
                                       IN int reconnect);
/**
 * 设置超时参数信息
 *
 * @param  cmd_time: 信令超时时间，单位：秒，默认值参见 @ref IOT_CMD_TIMEOUT
 * @param  stream_time: 视频流超时时间，单位：秒，默认值参见 @ref IOT_STREAM_TIMEOUT
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、建议在注册到服务器前调用，不调用时库内部按上面提到的默认值工作
 *         2、超时值的大小需保证为超时检测单位 @ref IOT_TIMEOUT_UNIT 的整数倍，否则实际大小会被扩大，如设为12秒，内部会更改为15秒
 *         3、从v3.2版本（含）后，为保持一致性，这两个参数在向master注册时会自动从服务端获取，获取不到会用默认值（比如服务端版本小于v3.2的情况）。
 *            故从此版本后，不再建议调用者使用此接口，因为此值随后会被从服务端中获取到的值覆盖掉！
 */
IOT_API int STDCALL IOT_SetTimeoutInfo(IN int cmd_time,
                                       IN int stream_time);

/**
 * 设置日志等级
 *
 * @param  log_level: 日志输出等级，值越小输出内容越多，可选值：0-TRACE/1-DEBUG/2-INFO(默认值)/3-WARN/4-ERROR/5-FATAL/6-CLOSE
 * @param  use_env_set: 是否使用环境变量（IOT_LOG_LEVEL）设置的等级：0-不使用，1-使用（默认值）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、建议在注册到服务器前调用，也可以在使用过程中随时调用用于即时生效，不调用时库内部按上面提到的默认值工作
 *         2、使用环境变量设定的日志等级时，库内部会在心跳线程中定时获取此环境变量，因此相当于支持自动更改日志等级功能
 */
IOT_API int STDCALL IOT_SetLogLevel(IN int log_level,
                                    IN int use_env_set);

/**
 * 设置消息回调
 *
 * @param  cb: 回调函数指针，为空时，表示关闭消息回调功能
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、需在注册到服务器前调用，设置成功后，后续会一直有效。支持的消息类型参见 @ref IotMessageType
 *         2、不要在回调中处理费时操作，如调用开、关流等接口，否则可能会阻塞sdk内部整个消息通知机制
 *         3、此回调消息为SDK级别的，如果设置多次，后面的就会将前面的覆盖，即最后一次设置有效
 */
IOT_API int STDCALL IOT_SetMessageCallback(IN IOT_CB_Message    cb,
                                           IN void *            user_data);
/**
 * 设置消息回调（扩展接口版本2，支持自定义接收的消息类别，防止调用者接收过多的无用消息）
 *
 * @param  cb: 回调函数指针，为空时，表示关闭消息回调功能
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  msg_mask: 消息类别掩码，参见 @ref IotMessageCategory
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、需在注册到服务器前调用，设置成功后，后续会一直有效。支持的消息类型参见 @ref IotMessageType
 *         2、不要在回调中处理费时操作，如调用开、关流等接口，否则可能会阻塞sdk内部整个消息通知机制
 *         3、此回调消息为SDK级别的，如果设置多次，后面的就会将前面的覆盖，即最后一次设置有效
 */
IOT_API int STDCALL IOT_SetMessageCallback2(IN IOT_CB_Message   cb,
                                            IN void *           user_data,
                                            IN uint32_t         msg_mask);

/**
 * 获取当前SDK库文件的版本号
 *
 * @return 返回版本号字符串，例如："1.2.3"
 * @note   此接口随时可以调用，始终返回版本串
 */
IOT_API const char* STDCALL IOT_GetSdkVersion(void);

/**
 * 获取当前SDK连接到的IoT服务端的版本号
 *
 * @return 返回IoT系统版本号字符串，未登录时返回空串""
 * @note   此接口需要在成功注册到服务器后调用，否则无法获取到服务端版本信息，且只有在每次注册成功后才更新版本串内容
 */
IOT_API const char* STDCALL IOT_GetIotServerVersion(void);

/**
 * 根据错误号，获取错误描述信息
 *
 * @param  error: 接口函数返回的错误号
 *
 * @return 返回错误描述信息字符串，其中含出错的模块名称，有助于使用者快速定位出错原因
 */
IOT_API const char* STDCALL IOT_GetErrorDescription(IN int error);
/**
 * 根据错误号及语言标识号，获取指定语种的错误描述信息
 *
 * @param  error: 接口函数返回的错误号
 * @param  lang_id: 语言标识号：0-中文，1-英文
 *
 * @return 返回错误描述信息字符串（非英文时采用UTF8编码），其中含出错的模块名称，有助于使用者快速定位出错原因
 */
IOT_API const char* STDCALL IOT_GetErrorDescription2(IN int error,
                                                     IN int lang_id);

/**
 * 根据分辨率类型，获取分辨率的大小
 *
 * @param  resolution_type: 分辨率枚举值，值参见 @ref IotVideoResolutionType
 * @param  width: 宽度
 * @param  height: 高度
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 */
IOT_API int STDCALL IOT_GetResolutionByType(IN int      resolution_type, 
                                            OUT int *   width, 
                                            OUT int *   height);

/** @} */


/**
 * @name 向IoT服务器的注册、注销等系统级接口（一个SDK一次只能连接到一套IoT系统中）
 * @{
 */

/**
 * 连接并注册到服务器上
 *
 * @param  svr_addr: master服务器IP地址或域名
 * @param  svr_port: master服务器端口号
 * @param  username: 用户名
 * @param  password: 密码
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，连接成功时返回比较快，否则会根据设定的策略重试几次，此时调用者可能等待超时后才得到返回值
 *         2、当前系统中只提供一个统一对外的主控master服务器，故只需成功注册一次即可
 *         3、如果设置了自动重连功能，则与服务端断开后，内部会每隔 @ref IOT_TIMEOUT_UNIT 秒重连一次，直到连接成功
 */
IOT_API int STDCALL IOT_Register(IN const char *    svr_addr, 
                                 IN uint16_t        svr_port, 
                                 IN const char *    username, 
                                 IN const char *    password);

/**
 * 从服务器上注销
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、成功注销后，后面相关功能函数将不再可用，同时库内部会关闭之前打开的取流数据通道
 *         2、为实现优雅关闭，建议在关闭所有流后再调用此函数
 */
IOT_API int STDCALL IOT_Unregister(void);

/**
 * 获取系统服务器节点统计信息
 *
 * @param  node_num: 请求节点的个数，输入建议值大于 @ref IOT_MAX_NODE_NUM, 调用成功后返回为实际节点个数
 * @param  node_list: 返回的节点统计信息，保存在一维数组中，需要调用者提供，数组大小要和上面的个数保持一致
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，服务端内部需要做汇总，可能返回稍慢
 *         2、请求节点的个数要和分配的数组大小保持一致，来避免内存访问越界问题
 *         3、若分配的节点个数N小于系统实际节点个数M，则返回时只填充数组中的前N项
 */
IOT_API int STDCALL IOT_GetSystemStatisticInfo(INOUT int *              node_num,
                                               OUT IotServerNodeInfo    node_list[]);

/**
 * 设置IoT系统配置参数
 *
 * @param  cfg_text: 配置参数字符串，一般为json串，串长度范围[1, 10M]
 * @param  res1: 预留参数1（指针类型）
 * @param  res2: 预留参数2（整型）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口用于将外部对IoT系统的配置参数透传到服务端，库内部不做任何解析，只负责透传
 */
IOT_API int STDCALL IOT_SetSystemCfgParam(IN const char *   cfg_text,
                                          IN void *         res1,
                                          IN int            res2);

/**
 * 向IoT系统的服务器中动态添加设备厂商类型
 *
 * @param  vendor_id: 厂商标识号，不能添加已存在的类型，当前支持的类型参见 @ref IotDeviceVendor
 * @param  vendor_name: 厂商名称
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器返回命令后函数才返回
 *         2、此接口一般用于项目上存在当前IoT系统不支持的某个厂商，为了快速对接此厂商，只需调用者新增类型，服务端新加一个proxy就可实现接入的情况
 */
IOT_API int STDCALL IOT_AddDeviceVendor(IN int          vendor_id,
                                        IN const char * vendor_name,
                                        IN const char * ext_info);
/**
 * 向IoT系统的服务器中删除动态添加的设备厂商类型
 *
 * @param  vendor_id: 厂商标识号，不能删除系统默认支持的类型，当前支持的类型参见 @ref IotDeviceVendor
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器返回命令后函数才返回
 *         2、若用此接口访问早期版本的服务端，具体的响应依赖服务端的支持情况，如服务端直接丢弃不支持的命令消息，则此接口会返回超时错误
 */
IOT_API int STDCALL IOT_DeleteDeviceVendor(IN int vendor_id);

/**
 * 获取设备厂商的SDK版本信息
 *
 * @param  vendor_id: 厂商标识号，参见 @ref IotDeviceVendor
 * @param  sdk_version: 返回的SDK版本串信息，需由调用者分配串内存，建议长度大于等于512字节；长度不足可能会引发崩溃问题
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   对于不支持的厂商类型，接口会返回对应的不支持错误码，此时版本串参数无效
 */
IOT_API int STDCALL IOT_GetVendorSdkVersion(IN int          vendor_id,
                                            OUT char *      sdk_version,
                                            IN const char * ext_info);

/** @} */


/**
 * @name 设备操作相关接口，包括增删改查，设备的参数获取及设置等功能
 * @note 后面提到的阻塞方式指的是，该接口需要等收到服务端响应后才返回，由于涉及到网络传输及各服务模块之间的交互，
 *       故函数返回可能有些慢；非阻塞方式指得是不含与服务端的交互，故一般返回比较快。若无特殊说明，接口一般为阻塞方式，
 *       只是内部实现没有较耗时的操作，返回较快
 * @{
 */

/**
 * 向IoT系统的服务器中添加设备
 *
 * @param  dev: 设备信息
 * @param  dev_id: 服务器分配给当前设备的唯一标识号（后续大部分接口都以此值为主要入参），
 *                 需由调用者分配串内存，长度大于等于 @ref IOT_LEN_DEVID
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器分配完设备标识号后函数才返回
 *         2、库内部使用统一的信令通道进行消息交互，调用者最好顺序调用
 */
IOT_API int STDCALL IOT_AddDevice(IN const IotDeviceConfig *    dev, 
                                  OUT char *                    dev_id);

/**
 * 从IoT系统的服务器中删除设备
 *
 * @param  dev_id: 设备标识号
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器完成删除后此函数才返回
 *         2、对于同一设备，添加和删除操作最好能保证由同一使用者调用，来避免将其他调用者增加的设备删除掉，影响他人正常使用
 *         3、删除设备前，请保证此设备未在使用中（全局范围内对此设备的流打开操作均已关闭），否则将删除失败
 */
IOT_API int STDCALL IOT_DeleteDevice(IN const char *dev_id);
/**
 * 从IoT系统的服务器中删除设备（扩展接口版本2）
 *
 * @param  dev_id: 设备标识号
 * @param  force_delete: 是否强制删除设备：0-不强制（若此设备还在被使用，则不会删除），非0-强制（关闭可能被打开的所有流，并删除此设备）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器完成删除后此函数才返回
 *         2、对于同一设备，添加和删除操作最好能保证由同一使用者调用，来避免将其他调用者增加的设备删除掉，影响他人正常使用
 */
IOT_API int STDCALL IOT_DeleteDevice2(IN const char *   dev_id, 
                                      IN int            force_delete);
/**
 * 从IoT系统的服务器中删除设备（扩展接口版本3，v4.0新增）
 *
 * @param  dev_id: 设备标识号
 * @param  force_delete: 是否强制删除设备：0-不强制（若此设备还在被使用，则不会删除），非0-强制（关闭可能被打开的所有流，并删除此设备）
 * @param  delete_channels: 是否删除其下的通道：0-不删除（暂不支持），非0-删除（默认值）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器完成删除后此函数才返回
 *         2、对于同一设备，添加和删除操作最好能保证由同一使用者调用，来避免将其他调用者增加的设备删除掉，影响他人正常使用
 *         3、对于其下无通道的设备类型，和版本2的接口效果一致
 */
IOT_API int STDCALL IOT_DeleteDevice3(IN const char *   dev_id,
                                      IN int            force_delete,
                                      IN int            delete_channels);

/**
 * 修改IoT系统服务器中的设备信息
 *
 * @param  dev_id: 设备标识号
 * @param  dev: 设备信息
 * @param  syn_flag: 同步标志，0-非阻塞方式，非0-阻塞方式
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、当为非阻塞方式时，一般会立刻返回，但是否真正更新成功，需由随后的事件回调得知
 *         2、当为阻塞方式时，直到服务端处理完此接口才会返回成功与否，此时不再有事件回调通知（除非返回值为超时错误）
 *         3、库内部使用统一的信令通道进行消息交互，调用者最好顺序调用
 *         4、当前设备若已打开了视频流，修改设备厂家、设备类型、IP地址、视频端口号、用户名、密码、通道号、设备型号、国标平台ID、国标设备ID及RTSP_URL时需要先关流
 *         5、当前设备若已打开了图片流，修改设备厂家、设备类型、IP地址、端口号、用户名、密码、通道号及设备型号时需要先关流
 */
IOT_API int STDCALL IOT_UpdateDevice(IN const char *            dev_id, 
                                     IN const IotDeviceConfig * dev, 
                                     IN int                     syn_flag);

/**
 * 获取IoT系统服务器中的单个设备的参数信息
 *
 * @param  dev_id: 设备标识号
 * @param  dev: 设备信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，库内部收到服务器响应消息后才返回
 *         2、库内部使用统一的信令通道进行消息交互，调用者最好顺序调用
 */
IOT_API int STDCALL IOT_GetDeviceInfo(IN const char *           dev_id,
                                      OUT IotDeviceConfig *     dev);

/**
 * 获取设备列表
 *
 * @param  cb: 回调函数指针，不能为空，否则无法返回列表数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为非阻塞接口，一般会立刻返回，库内部收到完整列表后，会通过回调函数一次回调出来
 *         2、当系统中设备较多时，获取一次可能花费较长时间，尽量避免在未回调完成前再次调用此接口
 *         3、设备列表为空时，也会回调一次，此时回调函数中的设备个数为0
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 */
IOT_API int STDCALL IOT_GetDeviceList(IN IOT_CB_DeviceList  cb, 
                                      IN void *             user_data);

/**
 * 启动设备发现
 *
 * @param  start_ip: 搜索网段的起始IP地址，为NULL或空串表示按系统默认规则，即依赖设备发现服务所在节点的地址，如 xxx.xxx.0.0
 * @param  end_ip: 搜索网段的结束IP地址，为NULL或空串表示按系统默认规则，即依赖设备发现服务所在节点的地址，如 xxx.xxx.255.255
 * @param  discovery_timeout: 查找设备的超时时间：0-不关闭，大于0的值-表示对应的秒后自动关闭，此时可不用调用停止接口（暂不支持）
 * @param  cb: 回调函数指针，不能为空，否则无法返回列表数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  session_id: 服务端返回的会话标识号，由用户传入，分配的串长需大于等于64字节，成功时置为有效值，用于后续停止操作；失败时未定义，此值不可用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，库内部收到服务端响应后才会返回
 *         2、调用成功后，每收到一次服务端通知，就会回调一次，其中可能会含多个设备信息（当前版本只含1个，0个表示回调结束）
 *         3、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 */
IOT_API int STDCALL IOT_StartDeviceDiscovery(IN const char *                start_ip,
                                             IN const char *                end_ip,
                                             IN int                         discovery_timeout,
                                             IN IOT_CB_DeviceDiscoveryList  cb,
                                             IN void *                      user_data,
                                             OUT char *                     session_id);
/**
 * 停止设备发现
 *
 * @param  session_id: 启动接口返回的会话标识号
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、服务端探测设备完成后，会自动关闭，若此后再次调用此停止接口或未调用启动，则统一返回 IOT_ERR_PROXY_ALREALDY_CLOSED
 *         2、此为阻塞接口，库内部收到服务端响应后才会返回
 */
IOT_API int STDCALL IOT_StopDeviceDiscovery(IN const char *session_id);

/**
 * 获取单个设备状态信息
 *
 * @param  dev_id: 设备标识号
 * @param  status: 设备状态信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   支持所有类型设备，普通设备类型中只有是否在线字段有效，GB28181设备类型所有字段都有效
 */
IOT_API int STDCALL IOT_GetDeviceStatus(IN const char *         dev_id, 
                                        OUT IotDeviceStatus *   status);

/**
 * 批量获取设备状态信息
 *
 * @param  dev_num: 请求设备的个数，大小不能超过 @ref IOT_MAX_LST_NUM, 超过此值请分多次查询
 * @param  dev_id_list: 要请求的设备标识号列表，用二维数组保存
 * @param  status_list: 获取到的设备状态信息，保存在一维数组中，只在返回成功时有效
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，当一次请求设备较多时，可能返回稍慢
 *         2、支持所有类型设备，普通设备类型中只有是否在线字段有效，GB28181设备类型所有字段都有效
 *         3、请求设备的个数要和下面调用者分配的数组大小保持一致，来避免内存访问越界问题
 */
IOT_API int STDCALL IOT_BatchGetDeviceStatus(IN int                 dev_num, 
                                             IN char                dev_id_list[][IOT_LEN_DEVID], 
                                             OUT IotDeviceStatus    status_list[]);

/**
 * 获取设备版本信息
 *
 * @param  dev_id: 设备标识号
 * @param  info: 返回的设备版本
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持 @ref IOT_DT_CLOUD_IPC 类型的设备，其他类型的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetDeviceVersion(IN const char *            dev_id, 
                                         OUT IotDeviceVersionInfo * info);
/**
 * 获取设备算法信息
 *
 * @param  dev_id: 设备标识号
 * @param  info: 返回的设备算法信息，包括算法状态等
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持 @ref IOT_DT_CLOUD_IPC 类型的设备，其他类型的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetDeviceAlgorithmInfo(IN const char *              dev_id, 
                                               OUT IotDeviceAlgorithmInfo * info);

/**
 * 获取设备图片参数
 *
 * @param  dev_id: 设备标识号
 * @param  info: 返回的设备图片参数
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持旷视ODM厂商的大部分设备型号，其他厂商的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetPictureParam(IN const char *             dev_id, 
                                        OUT IotPictureStreamParam * info);
/**
 * 设置设备图片参数
 *
 * @param  dev_id: 设备标识号
 * @param  info: 设备图片参数
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持旷视ODM厂商的大部分设备型号，其他厂商的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_SetPictureParam(IN const char *                 dev_id, 
                                        IN const IotPictureStreamParam *info);

/**
 * 获取设备视频参数
 *
 * @param  dev_id: 设备标识号
 * @param  profile_type: 码流类型，值参见 @ref IotChanProfileType
 * @param  info: 返回的设备视频参数
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持旷视ODM厂商的大部分设备型号，其他厂商的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetVideoParam(IN const char *           dev_id, 
                                      IN int                    profile_type, 
                                      OUT IotVideoStreamParam * info);
/**
 * 设置设备视频参数
 *
 * @param  dev_id: 设备标识号
 * @param  profile_type: 码流类型，值参见 @ref IotChanProfileType
 * @param  info: 返回的设备视频参数
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持旷视ODM厂商的大部分设备型号，其他厂商的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_SetVideoParam(IN const char *               dev_id, 
                                      IN int                        profile_type, 
                                      IN const IotVideoStreamParam *info);

/**
 * 获取设备全景图开关及压缩比参数
 *
 * @param  dev_id: 设备标识号
 * @param  info: 返回的全景图参数
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持 @ref IOT_DT_CLOUD_IPC 类型的设备，其他类型的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetPanoramaParam(IN const char *        dev_id,
                                         OUT IotPanoramaParam * info);
/**
 * 设置设备全景图开关及压缩比参数
 *
 * @param  dev_id: 设备标识号
 * @param  param_type: 要设置的参数类型：0-全部设置，1-开关，2-压缩比
 * @param  open_flag: 全景图开关：0-关，非0-开
 * @param  compress_ratio: 全景图压缩比，范围为[1-100]
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持 @ref IOT_DT_CLOUD_IPC 类型的设备，其他类型的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_SetPanoramaParam(IN const char *    dev_id,
                                         IN int             param_type,
                                         IN int             open_flag,
                                         IN int             compress_ratio);

/**
 * 获取设备的参数信息
 *
 * @param  dev_id: 设备标识号
 * @param  info: 从相机等设备上返回的设备参数信息，由调用者传入此参数用于接收信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口用于获取设备的参数信息，设备不支持此功能时返回的结构体内容为空
 */
IOT_API int STDCALL IOT_GetDeviceParams(IN const char *         dev_id,
                                        OUT IotDeviceParams *   info);

/**
 * 获取盒子设备的通道布点参数信息（目前只支持B3R协议）
 *
 * @param  dev_id: 设备/通道标识号。若为设备ID，则获取设备下所有通道的布点参数；若为通道ID，则获取此通道的布点参数
 * @param  param_info: 通道布点信息，json格式样例如下：
 * {
 *     "deviceId" : "110000200100000001",  // 设备/通道标识号，原样返回调用者输入的参数dev_id
 *     "videos" : [                        // 通道布点列表
 *     {
 *         "videoNo" : 0,          // 通道号，从0开始
 *         "videoName" : "xx路口",  // 通道名称
 *         "username" : "admin",   // 通道对应接入的IPC用户名
 *         "password" : "12345",   // 通道对应接入的IPC密码
 *         "url" : "rtsp://1.2.3.4/main",    // 通道对应接入的IPC主码流RTSP地址，最大长度128字节
 *         "subUrl" : "rtsp://1.2.3.4/sub",  // 通道对应接入的IPC子码流RTSP地址，最大长度128字节
 *         "rotation" : 1          // 图像旋转的角度，为配合不同的摄像头安装角度，目前只支持4个值：0，90，180，270，分别代表顺时针旋转的角度0°，90°，180°，270°。若错误将检测不到人脸，如输入不为以上4个值，将默认为0°来处理
 *     }]
 * }
 * @param  info_len: 输入时为调用者分配的串长（建议不小于2K），接口返回成功时输出json串长，失败时此值保持不变
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持B3R盒子，对应的协议类型为 @ref IOT_DV_MEGVII_B3R
 */
IOT_API int STDCALL IOT_GetDevChannelParams(IN const char * dev_id,
                                            OUT char *      param_info,
                                            INOUT int *     info_len,
                                            IN const char * ext_info);

/**
 * 获取设备分辨率能力集
 *
 * @param  dev_id: 设备标识号
 * @param  profile_type: 码流类型，值参见 @ref IotChanProfileType
 * @param  info: 返回的分辨率能力集
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持 @ref IOT_DT_CLOUD_IPC 类型的设备，其他类型的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetResolutionCap(IN const char *                dev_id, 
                                         IN int                         profile_type, 
                                         OUT IotResolutionCapability *  info);

/**
 * 获取设备模式能力集
 *
 * @param  dev_id: 设备标识号
 * @param  info: 返回的模式能力集信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持ODM厂商部分类型的设备，其他类型的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetCameraModeCap(IN const char *                dev_id,
                                         OUT IotCameraModeCapability *  info);

/**
 * 获取相机模式参数
 *
 * @param  dev_id: 设备标识号
 * @param  mode: 相机模式参数，取值参见 @ref IotCameraMode
 * @param  res: 预留参数（字符串类型）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持部分型号的结构化相机，对于不支持此功能的设备接口会返回不支持错误码
 */
IOT_API int STDCALL IOT_GetCameraMode(IN const char *   dev_id,
                                      OUT int *         mode,
                                      OUT char *        res);
/**
 * 设置相机模式参数
 *
 * @param  dev_id: 设备标识号
 * @param  mode: 相机模式参数，取值参见 @ref IotCameraMode
 * @param  res: 预留参数（字符串类型）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持部分型号的结构化相机，对于不支持此功能的设备接口会返回不支持错误码
 */
IOT_API int STDCALL IOT_SetCameraMode(IN const char *   dev_id,
                                      IN int            mode,
                                      IN const char *   res);

/**
 * 获取设备报警输入端子配置信息
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 端子通道号，从0开始
 * @param  cfg: 返回的报警输入配置信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持旷视ODM厂商的大部分设备型号，其他厂商的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetAlarmInConfig(IN const char *        dev_id, 
                                         IN int                 chan_no, 
                                         OUT IotAlarmInConfig * cfg);
/**
 * 设置设备报警输入端子配置信息
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 端子通道号，从0开始
 * @param  cfg: 报警输入配置信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持旷视ODM厂商的大部分设备型号，其他厂商的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_SetAlarmInConfig(IN const char *            dev_id, 
                                         IN int                     chan_no, 
                                         IN const IotAlarmInConfig *cfg);

/**
 * 获取设备报警输出端子配置信息
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 端子通道号，从0开始
 * @param  cfg: 返回的报警输出配置信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持旷视ODM厂商的大部分设备型号，其他厂商的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_GetAlarmOutConfig(IN const char *           dev_id, 
                                          IN int                    chan_no, 
                                          OUT IotAlarmOutConfig *   cfg);
/**
 * 设置设备报警输出端子配置信息
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 端子通道号，从0开始
 * @param  cfg: 报警输出配置信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持旷视ODM厂商的大部分设备型号，其他厂商的设备返回不支持错误码
 */
IOT_API int STDCALL IOT_SetAlarmOutConfig(IN const char *               dev_id, 
                                          IN int                        chan_no, 
                                          IN const IotAlarmOutConfig *  cfg);

/**
 * 相机设备警戒参数获取
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 通道号，从0开始
 * @param  cfg_type: 配置参数类型，参见 @ref IotAlertConfigType
 * @param  cfg_data: 配置参数结构体指针，不同的类型对应不同的结构体，参见上面的类型说明，由用户生成并传入
 * @param  data_len: 结构体的长度
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   传入结构体cfg_data时要注意，此结构体不只是出参，本身还是入参，具体哪些字段需要设置，需参见相关字段说明中的IN和OUT前缀
 */
IOT_API int STDCALL IOT_GetDeviceAlertConfig(IN const char *dev_id,
                                             IN int         chan_no,
                                             IN int         cfg_type,
                                             INOUT void *   cfg_data,
                                             IN int         data_len);

/**
 * 相机设备警戒参数设置
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 通道号，从0开始
 * @param  cfg_type: 配置参数类型，参见 @ref IotAlertConfigType
 * @param  cfg_data: 配置参数结构体指针，不同的类型对应不同的结构体，参见上面的类型说明，由用户生成并传入
 * @param  data_len: 结构体的长度
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 */
IOT_API int STDCALL IOT_SetDeviceAlertConfig(IN const char *dev_id,
                                             IN int         chan_no,
                                             IN int         cfg_type,
                                             IN void *      cfg_data,
                                             IN int         data_len);

/**
 * 设备云台、镜头控制
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 设备通道号，从0开始，默认值为0
 * @param  ptz_cmd: 云台控制命令，参见 @ref IotPtzControlCommand
 * @param  speed: 控制云台、镜头的速度，范围为[1-8]
 * @param  stop: 云台停止动作或开始动作：0-开始，非0-停止
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持抓拍机和云端协同类型的部分型号，并且设备本身支持云镜控制，否则返回不支持错误码
 */
IOT_API int STDCALL IOT_PtzControl(IN const char *  dev_id, 
                                   IN int           chan_no, 
                                   IN int           ptz_cmd, 
                                   IN int           speed,
                                   IN int           stop);
/**
 * 设备云台预置位控制
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 设备通道号，从0开始，默认值为0
 * @param  cmd: 预置位控制命令，参见 @ref IotPtzControlCommand 中的预置位相关命令
 * @param  index: 预置位索引号，范围为[1-256]
 * @param  param1: 预留参数1（暂未用到）
 * @param  param2: 预留参数2（暂未用到）
 * @param  param3: 预留参数3（暂未用到）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持抓拍机和云端协同类型的部分型号，并且设备本身支持云镜控制，否则返回不支持错误码
 */
IOT_API int STDCALL IOT_PtzPreset(IN const char *   dev_id,
                                  IN int            chan_no,
                                  IN int            cmd,
                                  IN int            index,
                                  IN int            param1,
                                  IN int            param2,
                                  OUT int *         param3);

/**
 * 远程设备重启
 *
 * @param  dev_id: 设备标识号
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，重启成功与否可通过返回值得知，返回成功时即认为设备已经开始重启
 *         2、此接口目前只支持抓拍机和云端协同类型的部分型号，否则返回不支持错误码
 */
IOT_API int STDCALL IOT_RebootDevice(IN const char *dev_id);

/**
 * 批量设备校时
 *
 * @param  info: 设备校时参数及设备列表信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为非阻塞接口，调用后一般会立刻返回，校时成功与否会通过消息回调通知
 *         2、此接口目前只支持抓拍机和云端协同类型的部分型号，并且设备本身支持云镜控制，否则返回不支持错误码
 */
IOT_API int STDCALL IOT_BatchTimingDevices(IN const IotTimingInfo *info);

/**
 * 批量设备升级
 *
 * @param  info: 设备升级参数及设备列表信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，在收到服务端响应消息后才返回，并且升级状态信息会通过消息回调多次分步通知
 *         2、此接口只支持 @ref IOT_DT_CLOUD_IPC 类型的设备，其他类型的设备返回相应错误码
 */
IOT_API int STDCALL IOT_BatchUpgradeDevices(IN const IotDeviceUpgradeInfo *info);

/**
 * 批量设备底库下发
 *
 * @param  info: 设备底库下发参数及设备列表信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，在收到服务端响应消息后才返回，并且下发状态信息会通过消息回调多次分步通知
 *         2、此接口只支持 @ref IOT_DT_CLOUD_IPC 类型的设备，其他类型的设备返回相应错误码
 */
IOT_API int STDCALL IOT_BatchDevicesRcgLibAdd(IN const IotDeviceRcgLibInfo *info);

/**
 * 获取GB28181设备信息
 *
 * @param  dev_id: 设备标识号
 * @param  info: 返回的设备信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持 @ref IOT_DT_GB28181_IPC 类型的设备，其他类型的设备返回相应错误码
 */
IOT_API int STDCALL IOT_GetGbDeviceInfo(IN const char *         dev_id, 
                                        OUT IotGbDeviceInfo *   info);

/**
 * 获取GB28181设备目录信息
 *
 * @param  platform_id: GB平台标识号，不能为空
 * @param  dev_id: 设备标识号，可为空
 * @param  cb: 回调函数指针，不能为空，否则无法返回获取到的数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此接口只支持 @ref IOT_DT_GB28181_IPC 类型的设备，其他类型的设备返回相应错误码
 *         2、此为非阻塞接口，一般会立刻返回，库内部收到完整设备目录信息后，会通过回调函数一次回调出来，列表为空也会回调一次
 *         3、当系统中设备较多时，获取一次可能花费较长时间，请耐心等待
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 *         5、platform_id不能为空，dev_id为空时，表示要获取此平台下面的一级设备信息，一般用于首次调用；
 *           dev_id不为空时，表示要获取此平台下此设备下面的所有子设备信息
 */
IOT_API int STDCALL IOT_GetGbDeviceCatalog(IN const char *          platform_id, 
                                           IN const char *          dev_id, 
                                           IN IOT_CB_DeviceCatalog  cb, 
                                           IN void *                user_data);

/**
 * 获取国标平台设备精简版目录信息
 *
 * @param  platform_id: 国标平台标识号，不能为空；当平台类型为GA时，此值代表GA服务器的IP:PORT字符串
 * @param  dev_id: 设备标识号，可为空
 * @param  platform_type: 国标平台类型：1-GB28181, 2-GA1400
 * @param  cb: 回调函数指针，不能为空，否则无法返回获取到的数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此接口支持 @ref IOT_DT_GB28181_IPC 及 @ref IOT_DT_GA1400_IPC 两种类型的设备，其他类型的设备返回相应错误码
 *         2、此为非阻塞接口，一般会立刻返回，库内部收到完整设备目录信息后，会通过回调函数一次回调出来，列表为空也会回调一次
 *         3、当系统中设备较多时，获取一次可能花费较长时间，请耐心等待
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 *         5、platform_id不能为空，dev_id为空时，表示要获取此平台下面的一级设备信息，一般用于首次调用；
 *           dev_id不为空时，表示要获取此平台下此设备下面的所有子设备信息
 *         6、与接口 @ref IOT_GetGbDeviceCatalog 的区别在于设备目录信息只含常用字段，且支持GA1400视图库国标平台
 */
IOT_API int STDCALL IOT_GetLiteDeviceCatalog(IN const char *                platform_id, 
                                             IN const char *                dev_id, 
                                             IN int                         platform_type, 
                                             IN IOT_CB_LiteDeviceCatalog    cb, 
                                             IN void *                      user_data);

/**
 * 批量获取国标平台精简版目录信息
 *
 * @param  platform_id: 国标平台标识号，不能为空
 * @param  dev_id: 设备标识号，可为空
 * @param  platform_type: 国标平台类型：1-GB28181, 2-GA1400
 * @param  packet_size: 每个数据包中的目录个数，即一次消息回调的目录个数，范围[0-1000]，传0时表示采用系统默认值，如50等
 * @param  cb: 回调函数指针，不能为空，否则无法返回获取到的数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  catalog_sum: 从下级平台返回的设备目录总数，由调用者传递此参数来获取此值，传NULL时表示不关心此值
 * @param  session_id: 返回的会话标识号，由用户传入，分配的串长需大于等于64字节，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、目前版本此接口只支持 @ref IOT_DT_GB28181_IPC 及 @ref IOT_DT_GA1400_IPC 两种类型的设备，其他类型的设备返回相应错误码
 *         2、此为阻塞接口，库内部收到设备目录总数后才会返回，后续每收到服务端发来的一包数据后会回调一次，最后一次回调中的列表个数为0用于表示接收完毕（中途接收超时也会回调0来表示结束）
 *         3、当下级平台设备较多时，总接收时间可能较长，请耐心等待
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 *         5、platform_id不能为空，dev_id为空时，表示要获取此平台下面的一级设备信息，一般用于首次调用；
 *           dev_id不为空时，表示要获取此平台下此设备下面的所有子设备信息
 *         6、与接口 @ref IOT_GetLiteDeviceCatalog 的区别在于前者一次回调所有设备目录信息，当前接口分批回调
 *         7、若在拉取过程中再次调用此接口，则库内部会返回错误，用于保证同时只有一次拉取操作
 */
IOT_API int STDCALL IOT_BatchGetLiteDeviceCatalog(IN const char *               platform_id,
                                                  IN const char *               dev_id,
                                                  IN int                        platform_type,
                                                  IN int                        packet_size,
                                                  IN IOT_CB_BatchDeviceCatalog  cb,
                                                  IN void *                     user_data,
                                                  OUT int *                     catalog_sum,
                                                  OUT char *                    session_id);
/**
 * 批量获取国标平台精简版目录信息的取消接口
 *
 * @param  session_id: 获取接口返回的会话标识号
 * @param  platform_id: 国标平台标识号，非必填参数，可为空
 * @param  dev_id: 设备标识号，非必填参数，可为空
 * @param  platform_type: 国标平台类型：1-GB28181, 2-GA1400
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、目前版本此接口只支持 @ref IOT_DT_GB28181_IPC 及 @ref IOT_DT_GA1400_IPC 两种类型的设备，其他类型的设备返回相应错误码
 *         2、此为阻塞接口，库内部收到服务端的响应后才会返回，取消成功后会回调一次列表个数为0的消息来表示取消完成
 *         3、若取消已完成或未开始的拉取命令，则直接返回成功，且不再有列表个数为0的消息回调通知
 */
IOT_API int STDCALL IOT_CancelBatchGetLiteDeviceCatalog(IN const char * session_id,
                                                        IN const char * platform_id,
                                                        IN const char * dev_id,
                                                        IN int          platform_type);

/**
 * 向系统中添加平台信息
 *
 * @param  platform_type: 视频/图像平台类型，参见 @ref IotPlatformType
 * @param  plat_info: 平台信息，不同的平台类型参数字段可能不一样，sdk只做透传，不做校验（未特殊说明的字段为可选项）
 *         GB28181平台格式样例如下：
 * {
 *     "name" : "xx视频联网平台",// 平台名称
 *     "addr" : "192.168.0.8", // 平台地址
 *     "port" : 8000,          // 平台端口
 *     "username" : "admin",   // 平台用户名
 *     "password" : "12345",   // 平台密码
 *     "platformType" : 1,     // 国标平台类型：1-上级(默认值)，2-下级
 *     "platformId" : "3402000000132xxxxxxx",  // 国标平台编码（必选项）
 *     "streamProtocol" : 0,   // 流通信协议：0-UDP（默认值），1-TCP Active，2-TCP Passive（暂不支持）
 *     "commandProtocol" : 0,  // 信令通信协议（主要由下级平台决定，不可控）：0-UDP（默认值），1-TCP
 *     "realm" : "3402000000",      // 域，一般为平台编码前十位
 *     "validPeriod" : 3600,        // 注册有效期，单位：秒，默认值3600
 *     "heartbeatEnabled" : 0,      // 是否开启心跳检测：0-不开启（默认值），1-开启
 *     "heartbeatTime" : 30,        // 心跳超时时间，单位：秒
 *     "heartbeatCount" : 3,        // 心跳超时次数
 *     "remark" : ""                // 备注
 * }
 *         GA1400平台格式样例如下：
 * {
 *     "name" : "xx视图平台",   // 平台名称
 *     "addr" : "192.168.0.8", // 平台地址（必选项）
 *     "port" : 8000,          // 平台端口（必选项）
 *     "username" : "admin",   // 平台用户名
 *     "password" : "12345",   // 平台密码
 *     "platformType" : 1,     // 国标平台类型：1-上级，2-下级
 *     "platformId" : "3402000000132xxxxxxx",  // 国标平台编码（必选项）
 *     "ipv6" : "",            // IPv6地址
 *     "remark" : ""           // 备注
 * }
 *         平台厂商私有平台格式样例如下：
 * {
 *     "name" : "xxxx",        // 平台名称
 *     "addr" : "192.168.0.9", // 平台地址（必选项）
 *     "port" : 8000,          // 平台端口（必选项）
 *     "username" : "admin",   // 平台用户名
 *     "password" : "12345",   // 平台密码
 *     "platformId" : "3402000000132xxxxxxx",  // 国标平台编码
 *     "remark" : ""           // 备注
 * }
 * @param  plat_id: 服务端分配给当前平台的唯一标识号（后续大部分接口都以此值为主要入参），
 *                 需由调用者分配串内存，长度大于等于 @ref IOT_LEN_DEVID
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务端分配完平台标识号后函数才返回
 *         2、平台添加成功后，才可以拉取通道列表（有的平台也叫设备列表），添加通道时需要用到此接口返回的平台标识号
 *         3、为保持接口的兼容性，拉取设备目录接口可以用当前接口返回的IoT平台标识号，也可以用国标平台ID
 */
IOT_API int STDCALL IOT_AddPlatform(IN int          platform_type,
                                    IN const char * plat_info,
                                    OUT char *      plat_id,
                                    IN const char * ext_info);

/**
 * 从系统中删除平台信息
 *
 * @param  plat_id: 平台标识号，由添加接口返回的值
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器完成删除后此函数才返回
 *         2、由于删除平台关联、影响较大，请谨慎调用当前接口
 *         3、删除平台不会自动删除它所包含的通道，请在其下所有通道后，再删除平台信息
 */
IOT_API int STDCALL IOT_DeletePlatform(IN const char *  plat_id,
                                       IN const char *  ext_info);

/**
 * 修改系统中指定平台的信息
 *
 * @param  plat_id: 平台标识号，由添加接口返回的值
 * @param  plat_info: 平台信息，json串格式可参考添加平台接口的相关说明
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器更新完平台信息后函数才返回
 *         2、修改参数plat_info中的设备地址、端口号、用户名、密码及协议类型等重要参数时，可能会引发系统自动关流，此时可能需要应用层来重新开流
 */
IOT_API int STDCALL IOT_UpdatePlatform(IN const char *  plat_id,
                                       IN const char *  plat_info,
                                       IN const char *  ext_info);

/**
 * 从系统中查询平台信息
 *
 * @param  plat_id: 平台标识号，由添加接口返回的值
 * @param  plat_info: 平台信息，json串格式可参考添加平台接口的相关说明
 * @param  info_len: 输入时为调用者分配的串长（建议不小于2K），接口返回成功时输出json串长，失败时此值保持不变
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此为阻塞接口，库内部收到服务器响应消息后才返回
 */
IOT_API int STDCALL IOT_QueryPlatform(IN const char * plat_id,
                                      OUT char *      plat_info,
                                      INOUT int *     info_len,
                                      IN const char * ext_info);

/**
 * 从设备上获取底库图
 *
 * @param  dev_id: 设备标识号
 * @param  req: 底库图的查询输入条件
 * @param  buf: 数据缓冲区，由调用者分配后传入，并确保大小足够，返回的数据为BASE64格式
 * @param  len: 数据长度，初始由调用者传入分配的缓冲区大小，当成功获取到图片数据后，会将此值置为实际数据长度后传出
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，获取成功与否可通过返回值得知
 *         2、传入的缓冲区大小暂时建议为128k，若低于32K则返回参数错误，后续根据底库图片真实大小进行相应缩放
 */
IOT_API int STDCALL IOT_GetRcgLibPicture(IN const char *                    dev_id,
                                         IN const IotRecognizeRequestInfo * req,
                                         OUT uint8_t *                      buf,
                                         INOUT int *                        len);

/** @} */


/**
 * @name 数据流访问的开关接口，包括抓拍图片、实时视音频流及历史流
 * @{
 */

/**
 * 打开实时图片流
 *
 * @param  dev_id: 设备标识号
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 图片流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为非阻塞接口，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         2、需要注意的是，抓拍图片流不像视频流一直有实时数据，一般几秒内消息回调未通知失败，就表明打开成功了
 *         3、尽量避免在回调函数中做比较耗时的操作，以防影响后续图片的接收
 *         4、目前只有抓拍机和云端协同相机支持图片流功能，其它相机类型不支持
 */
IOT_API int STDCALL IOT_OpenPictureStream(IN const char *           dev_id, 
                                          IN IOT_CB_PictureStream   cb, 
                                          IN void *                 user_data, 
                                          OUT HANDLE *              handle);
/**
 * 打开实时图片流的阻塞方式接口，相关说明和非阻塞接口基本一样
 *
 * @note   1、此为阻塞接口，开流成功与否可通过返回值得知，默认最长超时大小为 @ref IOT_STREAM_TIMEOUT
 *         2、若在正常的传流过程中出错，还会由消息回调函数通知失败原因
 *         3、由于接收数据的是其它线程，故可能会出现此接口还未返回，就收到流数据回调的情况
 */
IOT_API int STDCALL IOT_OpenPictureStreamSyn(IN const char *           dev_id, 
                                             IN IOT_CB_PictureStream   cb, 
                                             IN void *                 user_data, 
                                             OUT HANDLE *              handle);
/**
 * 打开图片流（扩展接口版本2，适合流数据为文本格式的相机类型）
 *
 * @param  dev_id: 设备标识号
 * @param  syn_flag: 同步标志，0-非阻塞方式，1或其它非0值-阻塞方式
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 图片流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为扩展接口，目前支持 @ref IOT_DT_GA1400_IPC 、@ref IOT_DT_KAFKA_IPC 等类型的相机，结构化信息及图片流数据会以json串方式回调给调用者
 *         2、使用非阻塞方式时，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         3、使用阻塞方式时，开流成功与否可通过返回值得知，返回成功时，只表明与服务端的信令交互是正确的，但并不表示一定会取流成功或立刻收到数据流回调；收不到流时默认超时 @ref IOT_STREAM_TIMEOUT 秒后会有消息回调通知
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 *         5、使用同步方式时要注意，由于接收数据的是其它线程，故可能会出现此接口还未返回，就收到流数据回调的情况
 */
IOT_API int STDCALL IOT_OpenPictureStream2(IN const char *      dev_id, 
                                           IN int               syn_flag, 
                                           IN IOT_CB_DataStream cb, 
                                           IN void *            user_data, 
                                           OUT HANDLE *         handle);
/**
 * 打开图片流（扩展接口版本3，适合全结构化相机类型）
 *
 * @param  dev_id: 设备标识号
 * @param  syn_flag: 同步标志，0-非阻塞方式，1或其它非0值-阻塞方式
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  ext_info: 扩展信息（一般为空，可用于透传core中的设备ID）
 * @param  handle: 图片流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为扩展接口，支持 @ref IOT_DT_SMART_IPC 、@ref IOT_DT_CLOUD_IPC 等类型的相机，结构化信息及图片流数据以结构体方式回调给调用者
 *         2、使用非阻塞方式时，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         3、使用阻塞方式时，开流成功与否可通过返回值得知，返回成功时，只表明与服务端的信令交互是正确的，但并不表示一定会取流成功或立刻收到数据流回调；收不到流时默认超时 @ref IOT_STREAM_TIMEOUT 秒后会有消息回调通知
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 *         5、使用同步方式时要注意，由于接收数据的是其它线程，故可能会出现此接口还未返回，就收到流数据回调的情况
 */
IOT_API int STDCALL IOT_OpenPictureStream3(IN const char *              dev_id,
                                           IN int                       syn_flag,
                                           IN IOT_CB_StructureStream    cb,
                                           IN void *                    user_data,
                                           IN const char *              ext_info,
                                           OUT HANDLE *                 handle);

/**
 * 打开实时图片流（扩展接口版本4，适合全链条结构化数据字典类型，来源于视觉IoT中台接口 VIOT_OpenPictureStream）
 *
 * @param  chan_id: 设备/通道标识号
 * @param  sync_flag: 同步标志，0-非阻塞方式，1或其它非0值-阻塞方式
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 图片流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、支持具有图片流能力的相机类型，结构化信息及图片流数据以回调方式通知给调用者
 *         2、使用非阻塞方式时，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         3、使用阻塞方式时，开流成功与否可通过返回值得知，返回成功时，只表明与服务端的信令交互是正确的，但并不表示一定会取流成功或立刻收到数据流回调；收不到流时默认超时 @ref IOT_STREAM_TIMEOUT 秒后会有消息回调通知
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 */
IOT_API int STDCALL IOT_OpenPictureStream4(IN const char *      chan_id,
                                           IN int               sync_flag,
                                           IN IOT_CB_PicStream  cb,
                                           IN void *            user_data,
                                           OUT HANDLE *         handle,
                                           IN const char *      ext_info);

/**
 * 关闭实时图片流
 *
 * @param  handle: 图片流句柄
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、设备掉线或流出错等原因会引发库内部自动关流操作并释放相应资源，此时使用者可以不调用此关闭接口，如果调用则会返回 IOT_ERR_NOEXIST
 *         2、由于关流接口内部会释放流相关对象，因此切记不能在数据或消息回调中调用此接口
 */
IOT_API int STDCALL IOT_ClosePictureStream(IN HANDLE handle);

/**
 * 打开实时视频流
 *
 * @param  dev_id: 设备标识号
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 实时视频流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为非阻塞接口，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         2、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 */
IOT_API int STDCALL IOT_OpenLiveStream(IN const char *          dev_id, 
                                       IN IOT_CB_VideoStream    cb, 
                                       IN void *                user_data, 
                                       OUT HANDLE *             handle);
/**
 * 打开实时视频流的阻塞方式接口，相关说明和非阻塞接口基本一样，参见 @ref IOT_OpenLiveStream
 *
 * @note   1、此为阻塞接口，开流成功与否可通过返回值得知
 *         2、返回成功时，只表明与服务端的信令交互是正确的，但并不表示一定会取流成功或立刻收到数据流回调
 *         3、若由于设备的原因一直没收到流，默认最长超时 @ref IOT_STREAM_TIMEOUT 秒后会有消息回调通知
 *         4、若在正常的传流过程中出错，也会由消息回调函数通知失败原因
 *         5、由于接收数据的是其它线程，故可能会出现此接口还未返回，就收到流数据回调的情况
 */
IOT_API int STDCALL IOT_OpenLiveStreamSyn(IN const char *          dev_id, 
                                          IN IOT_CB_VideoStream    cb, 
                                          IN void *                user_data, 
                                          OUT HANDLE *             handle);
/**
 * 打开实时视频流（扩展接口版本2）
 *
 * @param  dev_id: 设备标识号
 * @param  stream_type: 取流所用的设备类型，值参见 @ref IotDeviceStreamType, 当设备类型为 @ref IOT_DT_CLOUD_IPC 时，需要指定更具体的取流设备类型，否则默认为0
 * @param  profile_type: 通道码流类型（即主子码流），值参见 @ref IotChanProfileType （暂不支持，默认为0即可）
 * @param  syn_flag: 同步标志，0-非阻塞方式，非0-阻塞方式
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 实时视频流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为扩展接口，功能实现上可取代前面的两个接口，即调用前面接口的地方都可改为此接口。若设备类型为 @ref IOT_DT_CLOUD_IPC, 则必须调用此接口指定具体类型进行开流
 *         2、使用非阻塞方式时，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         3、使用阻塞方式时，开流成功与否可通过返回值得知，返回成功时，只表明与服务端的信令交互是正确的，但并不表示一定会取流成功或立刻收到数据流回调；收不到流时默认超时 @ref IOT_STREAM_TIMEOUT 秒后会有消息回调通知
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 *         5、使用同步方式时要注意，由于接收数据的是其它线程，故可能会出现此接口还未返回，就收到流数据回调的情况
 */
IOT_API int STDCALL IOT_OpenLiveStream2(IN const char *         dev_id, 
                                        IN int                  stream_type, 
                                        IN int                  profile_type, 
                                        IN int                  syn_flag, 
                                        IN IOT_CB_VideoStream   cb, 
                                        IN void *               user_data, 
                                        OUT HANDLE *            handle);
/**
 * 打开实时视频流（扩展接口版本3，来源于视觉IoT中台接口 VIOT_OpenLiveStream）
 *
 * @param  chan_id: 通道标识号
 * @param  stream_type: 取流类型，值参见 @ref IotDeviceStreamType （一般默认为0）
 * @param  profile_type: 通道码流类型（即主子码流），值参见 @ref IotChanProfileType （默认为0）
 * @param  sync_flag: 同步标志，0-非阻塞方式，非0-阻塞方式
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 实时视频流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、取流类型一般适用于既支持RTSP方式，又支持国标方式取流的智能机，此时可以指定取流类型，否则一般传0，按默认的方式进行开流
 *         2、使用非阻塞方式时，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         3、使用阻塞方式时，开流成功与否可通过返回值得知，返回成功时，只表明与服务端的信令交互是正确的，但并不表示一定会取流成功或立刻收到数据流回调；收不到流时默认超时 @ref IOT_STREAM_TIMEOUT 秒后会有消息回调通知
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 */
IOT_API int STDCALL IOT_OpenLiveStream3(IN const char *     chan_id,
                                        IN int              stream_type,
                                        IN int              profile_type,
                                        IN int              sync_flag,
                                        IN IOT_CB_VidStream cb,
                                        IN void *           user_data,
                                        OUT HANDLE *        handle,
                                        IN const char *     ext_info);
/**
 * 关闭实时视频流
 *
 * @param  handle: 实时视频流句柄
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、设备掉线或流出错等原因会引发库内部自动关流操作并释放相应资源，此时使用者可以不调用此关闭接口，如果调用则会返回 IOT_ERR_NOEXIST
 *         2、由于关流接口内部会释放流相关对象，因此切记不能在数据或消息回调中调用此接口
 */
IOT_API int STDCALL IOT_CloseLiveStream(IN HANDLE handle);

/**
 * 打开历史视频流片段
 *
 * @param  dev_id: 设备标识号
 * @param  start_time: 起始时间(UTC)，字符串格式为：yyyy-mm-dd hh:MM:ss，如：2019-02-03 12:01:10
 * @param  end_time: 结束时间(UTC)，串格式如上
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 历史视频流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为非阻塞接口，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         2、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 *         3、历史流接收完毕，会收到流结束的回调通知
 */
IOT_API int STDCALL IOT_OpenClipStream(IN const char *          dev_id, 
                                       IN const char *          start_time, 
                                       IN const char *          end_time, 
                                       IN IOT_CB_VideoStream    cb, 
                                       IN void *                user_data, 
                                       OUT HANDLE *             handle);
/**
 * 打开历史视频流的阻塞方式接口，相关说明和非阻塞接口基本一样，参见 @ref IOT_OpenClipStream
 *
 * @note   1、此为阻塞接口，开流成功与否可通过返回值得知
 *         2、返回成功时，只表明与服务端的信令交互是正确的，但并不表示一定会取流成功或立刻收到数据流回调
 *         3、若由于设备的原因一直没收到流，默认最长超时 @ref IOT_STREAM_TIMEOUT 秒后会有消息回调通知
 *         4、若在正常的传流过程中出错，也会由消息回调函数通知失败原因
 *         5、使用同步方式时要注意，由于接收数据的是其它线程，故可能会出现此接口还未返回，就收到流数据回调的情况
 */
IOT_API int STDCALL IOT_OpenClipStreamSyn(IN const char *          dev_id, 
                                          IN const char *          start_time, 
                                          IN const char *          end_time, 
                                          IN IOT_CB_VideoStream    cb, 
                                          IN void *                user_data, 
                                          OUT HANDLE *             handle);
/**
 * 关闭历史视频流
 *
 * @param  handle: 历史视频流句柄
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、设备掉线或流出错等原因会引发库内部自动关流操作并释放相应资源，此时使用者可以不调用此关闭接口，如果调用则会返回 IOT_ERR_NOEXIST
 *         2、在接收历史流的过程中，可调用此接口进行关闭；在收到历史流接收完成消息后，无需再调用此接口进行关闭
 *         3、由于关流接口内部会释放流相关对象，因此切记不能在数据或消息回调中调用此接口
 */
IOT_API int STDCALL IOT_CloseClipStream(IN HANDLE handle);

/**
 * 暂停/恢复历史视频流播放
 *
 * @param  handle: 历史视频流句柄
 * @param  pause: 暂停标示，0-恢复播放，1或其他非0值-暂停播放
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、历史流回放控制接口，可在播放过程中多次调用，用于暂停及恢复播放
 *         2、受限于下级国标平台的原因，此接口功能可能并不支持，根据返回值无法保证调用功能正常
 */
IOT_API int STDCALL IOT_PauseClipStream(IN HANDLE handle, IN int pause);

/**
 * 历史视频流倍速播放
 *
 * @param  handle: 历史视频流句柄
 * @param  speed: 播放速度，枚举值范围参见 @ref IotPlaybackSpeed
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、历史流回放控制接口，可在播放过程中多次调用，用于快慢放及倒放
 *         2、受限于下级国标平台的原因，此接口功能可能并不支持或只能部分支持，根据返回值无法保证调用功能正常
 */
IOT_API int STDCALL IOT_SpeedPlayClipStream(IN HANDLE handle, IN int speed);

/**
 * 历史视频流随机拖动播放
 *
 * @param  handle: 历史视频流句柄
 * @param  range: 拖放范围，值大小为开流时设置的播放时间范围，单位：秒
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、历史流回放控制接口，可在播放过程中多次调用，用于历史流的随机拖放
 *         2、受限于下级国标平台的原因，此接口功能可能并不支持，根据返回值无法保证调用功能正常
 */
IOT_API int STDCALL IOT_SeekPlayClipStream(IN HANDLE handle, IN uint32_t range);

/**
 * 检索历史媒体流列表
 *
 * @param  dev_id: 设备标识号
 * @param  start_time: 起始时间(UTC)，字符串格式为：yyyy-mm-dd hh:MM:ss，如：2019-02-03 12:01:10
 * @param  end_time: 结束时间(UTC)，串格式如上
 * @param  cb: 回调函数指针，不能为空，否则无法返回获取到的数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为非阻塞接口，一般会立刻返回，库内部收到完整列表信息后，会通过回调函数一次回调出来，列表为空也会回调一次
 *         2、当系统中媒体流片段个数较多时，获取一次可能花费较长时间，请耐心等待，不建议还未收到上次回调，就再次调用
 *         3、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 */
IOT_API int STDCALL IOT_RetrieveClipList(IN const char *    dev_id, 
                                         IN const char *    start_time, 
                                         IN const char *    end_time, 
                                         IN IOT_CB_ClipList cb, 
                                         IN void *          user_data);

/**
 * 开始历史视频流下载
 *
 * @param  dev_id: 设备标识号
 * @param  start_time: 起始时间(UTC)，字符串格式为：yyyy-mm-dd hh:MM:ss，如：2019-02-03 12:01:10
 * @param  end_time: 结束时间(UTC)，串格式如上
 * @param  speed: 下载速度，值参见 @ref IotDownloadSpeed
 * @param  syn_flag: 同步标志，0-非阻塞方式，非0-阻塞方式
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 下载句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、非阻塞模式下，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         2、阻塞模式下，开流成功与否可通过返回值得知，默认最长超时大小为 @ref IOT_STREAM_TIMEOUT
 *         3、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 *         4、历史视频流下载接收完毕，会收到流结束的回调通知
 */
IOT_API int STDCALL IOT_OpenClipDownload(IN const char *        dev_id, 
                                         IN const char *        start_time, 
                                         IN const char *        end_time, 
                                         IN int                 speed, 
                                         IN int                 syn_flag, 
                                         IN IOT_CB_VideoStream  cb, 
                                         IN void *              user_data, 
                                         OUT HANDLE *           handle);
/**
 * 关闭历史视频流下载
 *
 * @param  handle: 历史视频流下载句柄
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、设备掉线或流出错等原因会引发库内部自动关流操作并释放相应资源，此时使用者可以不调用此关闭接口，如果调用则会返回 IOT_ERR_NOEXIST
 *         2、在下载历史流的过程中，可调用此接口进行关闭；在收到历史流接收完成消息后，无需再调用此接口进行关闭
 *         3、由于关流接口内部会释放流相关对象，因此切记不能在数据或消息回调中调用此接口
 */
IOT_API int STDCALL IOT_CloseClipDownload(IN HANDLE handle);

/**
 * 获取当前已开流的总数量
 *
 * @param  stream_type: 媒体流类型，-1表示所有类型的流，其他值参见 @ref IotStreamType
 *
 * @return 返回指定类型的流总数
 * @note   1、此接口只统计当前sdk打开的流数量，不会与服务端进行交互
 *         2、获取所有类型的流不用加锁，返回较快；获取指定类型的流需要加锁，返回稍慢，这种情况下不建议调用的太频繁，建议间隔在5秒以上
 *         3、对于正处于开流和关流过程中的流并未统计在内，因此可能与预计值有些偏差，属于正常情况
 */
IOT_API int STDCALL IOT_GetCurrentStreamCount(IN int stream_type);

/**
 * 启动设备开流并向指定服务端推流
 *
 * @param  dev_id: 设备标识号
 * @param  stream_type: 媒体流类型，值参见 @ref IotStreamType
 * @param  stream_way: 取流方式，值参见 @ref IotDeviceStreamType （暂不支持，传0即可）
 * @param  dest_type: 收流服务端类型：0-core，1-kafka（暂不支持），2-GA（云图），3-图片流HTTP订阅，4-全链条结构化数据字典HTTP订阅
 * @param  dest_addr: 收流服务端地址（如core的推送图片流URL、HTTP订阅地址或kafka服务器地址等）
 * @param  ext_info: 扩展信息（一般为空，可用于传递bucket信息等参数）
 * @param  session_id: 返回的推流会话标识号，由用户传入，分配的串长需大于等于64字节，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，收到服务端响应消息后接口才会返回
 *         2、系统内部推流服务模块收到此消息后，先开流然后再将收到的流数据推送到参数指定的服务器上
 */
IOT_API int STDCALL IOT_StartPushStream(IN const char * dev_id,
                                        IN int          stream_type,
                                        IN int          stream_way,
                                        IN int          dest_type,
                                        IN const char * dest_addr,
                                        IN const char * ext_info,
                                        OUT char *      session_id);
/**
 * 停止向服务端推流
 *
 * @param  dev_id: 设备标识号
 * @param  session_id: 推流会话标识号
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、在开始推流成功的条件，系统内部会保证一直在推流（即使设备下线又上线），只有调用此接口后才会停止推流
 *         2、若返回错误码为 IOT_ERR_NOLOGIN，表示当前与服务端连接已断开，消息发送失败，则需等待后续连接成功后再次调用此接口
 */
IOT_API int STDCALL IOT_StopPushStream(IN const char *dev_id, IN const char *session_id);

/**
 * 批量更新推流配置参数信息
 *
 * @param  req_info: 设备列表信息，由调用者分配后传入，json格式样例如下：
 * [ // 当前推流信息列表（注：目前后台服务不支持批量，只支持单个）
 *     {
 *         "session" : "xxx",                   // 推流会话标识号（由启动推流接口返回）
 *         "streamType" : 0,                    // 媒体流类型，值参见 @ref IotStreamType ，当前只支持图片流，传0即可
 *         "streamWay" : 0,                     // 取流方式，值参见 @ref IotDeviceStreamType （暂不支持，传0即可）
 *         "profileType" : 0,                   // 通道码流类型（即主子码流），值参见 @ref IotChanProfileType （暂不支持，传0即可）
 *         "destAddr" : "http://xxx/yy",        // 收流服务端地址（如core的推送图片流URL或kafka服务器地址）
 *         "faceFullBucket" : "faceFull",       // 人脸全景图bucket
 *         "faceCapBucket" : "faceCap",         // 人脸抓拍图bucket
 *         "personFullBucket" : "personFull",   // 人体全景图bucket
 *         "personCapBucket" : "personCap",     // 人体抓拍图bucket
 *         "motorFullBucket" : "motorFull",     // 机动车全景图bucket
 *         "motorCapBucket" : "motorCap",       // 机动车抓拍图bucket
 *         "nonmotorFullBucket" : "nonmotorFull",// 非机动车全景图bucket
 *         "nonmotorCapBucket" : "nonmotorCap"  // 非机动车抓拍图bucket
 *     }
 * ]
 * @param  ext_info: 扩展信息（暂时为空）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，收到服务端响应消息后接口才会返回
 *         2、SDK只负责透传这些参数，系统内部推流服务模块收到此消息后，先更新参数然后再将收到的流数据推送到参数指定的服务器上
 */
IOT_API int STDCALL IOT_BatchUpdatePushStreamInfo(IN const char * req_info,
                                                  IN const char * ext_info);

/**
 * 查询推流配置参数信息
 *
 * @param  session_id: 推流会话标识号
 * @param  info_str: 返回的json信息串内容，该字符串缓冲区需由调用者分配，格式样例如下：
 * {
 *     "status" : 0,                    // 推流实时状态：0-正常推流，1-设备掉线，2-开流失败，3-存图地址不可达
 *     "streamType" : 0,                // 媒体流类型，值参见 @ref IotStreamType ，当前只支持图片流，传0即可
 *     "streamWay" : 0,                 // 取流方式，值参见 @ref IotDeviceStreamType （暂不支持，传0即可）
 *     "profileType" : 0,               // 通道码流类型（即主子码流），值参见 @ref IotChanProfileType （暂不支持，传0即可）
 *     "destAddr" : "http://xxx/yy",    // 收流服务端地址（如core的推送图片流URL或kafka服务器地址）
 *     "extInfo" : ""                   // 启动推流时传入的扩展信息（目前主要用于传递bucket信息等参数）
 * }
 * @param  info_len: 输入时为调用者分配的串长（建议不小于1K），接口返回成功时输出实际串长，失败时此值一般保持不变（若错误码为分配缓冲区长度过短，则此值会保存实际长度）
 * @param  ext_info: 扩展信息（暂时为空）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，收到服务端响应消息后接口才会返回
 *         2、SDK只负责透传这些参数，具体参数及运行状态值由系统内部推流服务生成并返回给SDK
 */
IOT_API int STDCALL IOT_QueryPushStreamInfo(IN const char * session_id,
                                            OUT char *      info_str,
                                            INOUT int *     info_len,
                                            IN const char * ext_info);


/**
 * 打开设备录像缓存功能（内存缓存方式）
 *
 * @param  dev_id: 设备标识号
 * @param  res1: 预留参数1（字符串类型）
 * @param  res2: 预留参数2（整型）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，收到服务端响应消息后接口才会返回
 *         2、目前只支持内存缓存方式的录像方式
 *         3、V3.3后，此接口已被废弃，统一为 @ref IOT_StartDeviceRecord
 */
IOT_API int STDCALL IOT_OpenDeviceCache(IN const char *  dev_id,
                                        IN const char *  res1,
                                        IN int           res2);
/**
 * 关闭设备录像缓存功能（内存缓存方式）
 *
 * @param  dev_id: 设备标识号
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   V3.3后，此接口已被废弃，统一为 @ref IOT_StopDeviceRecord
 */
IOT_API int STDCALL IOT_CloseDeviceCache(IN const char *dev_id);

/**
 * 获取设备录像缓存配置信息
 *
 * @param  dev_id: 设备标识号
 * @param  info: 返回的设备录像缓存配置信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此为IoT内部接口，目前主要用于获取设备录像所属的服务器地址（V3.3后此接口已被废弃）
 */
IOT_API int STDCALL IOT_GetDeviceCacheInfo(IN const char *          dev_id,
                                           OUT IotDeviceCacheInfo * info);

/**
 * 开始设备录像
 *
 * @param  dev_id: 设备标识号
 * @param  record_type: 录像类型：1-内存缓存，2-磁盘存储
 * @param  period: 录像最大保存周期，单位为秒：0-使用系统默认值，其他值表示实际秒数
 * @param  res: 预留参数
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，收到服务端响应消息后接口才会返回
 *         2、目前可同时支持内存和磁IOT_BatchUpdatePushStreamInfo盘两种类型的录像方式（需要调用两次）
 *         3、使用内存缓存方式时功能和上面的 @ref IOT_OpenDeviceCache 一致，可完全取代这个接口
 */
IOT_API int STDCALL IOT_StartDeviceRecord(IN const char *dev_id,
                                          IN int         record_type,
                                          IN int         period,
                                          IN const char *res);
/**
 * 停止设备录像
 *
 * @param  dev_id: 设备标识号
 * @param  record_type: 录像类型：1-内存缓存，2-磁盘存储
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   重复调用此停止接口会返回 IOT_ERR_RECORD_DEV_NOEXIST
 */
IOT_API int STDCALL IOT_StopDeviceRecord(IN const char *dev_id,
                                         IN int         record_type);

/**
 * 录像小视频另存到其他存储系统
 *
 * @param  dev_id: 设备标识号
 * @param  record_type: 录像类型：1-内存缓存，2-磁盘存储，3-国标平台存储
 * @param  server_type: 存储系统：1-ObjectStorage（默认值），2-GSP
 * @param  server_addr: 存储服务器地址URL串（含bucket名称）
 * @param  start_time: 起始时间(UTC)，单位：毫秒
 * @param  end_time: 结束时间(UTC)，单位：毫秒
 * @param  syn_flag: 同步标志：0-非阻塞方式（适合国标平台存储类型），1或其他非0值-阻塞方式（适合内存和磁盘的录像类型）
 * @param  file_url: 返回的小视频文件在存储系统上的URL地址或会话标识串，此缓冲区需要由调用者根据实际情况分配，大小建议在512个字节以上
 * @param  resource_id: 返回的小视频文件资源标识号，目前存储到ObjectStorage时此值有效（洞鉴、灵探可能用到），大小建议在512个字节以上
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、使用阻塞方式时，直到收到服务端响应消息后接口才会返回，由于向服务器上推送大文件可能比较费时间，故接口返回可能较慢
 *         2、使用非阻塞方式时，成功返回后file_url保存的内容为会话标识串，URL地址需等服务端存储完毕后通过消息方式回调通知，并通过此会话串进行对应
 *         3、目前可同时支持多种类型的录像方式，不过需要提前配置好
 *         4、由调用者分配file_url和resource_id的内存缓冲区，且要确保大小足够，否则可能会导致崩溃问题
 */
IOT_API int STDCALL IOT_SaveRecordTo(IN const char *dev_id,
                                     IN int         record_type,
                                     IN int         server_type,
                                     IN const char *server_addr,
                                     IN int64_t     start_time,
                                     IN int64_t     end_time,
                                     IN int         syn_flag,
                                     OUT char *     file_url,
                                     OUT char *     resource_id);

/**
 * 获取设备录像配置信息
 *
 * @param  dev_id: 设备标识号
 * @param  record_type: 录像类型：1-内存缓存，2-磁盘存储
 * @param  period: 录像最大保存周期，单位为秒
 * @param  cfg: 配置信息（暂不支持）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此接口一般在设备开启录像后调用，返回开启时或设置后的录像周期参数值
 *         2、若未在设备录像状态下调用，则会返回IoT内部默认的环境变量值，如内存为60秒，磁盘为1800秒
 */
IOT_API int STDCALL IOT_GetDeviceRecordInfo(IN const char * dev_id,
                                            IN int          record_type,
                                            OUT int *       period,
                                            OUT char *      cfg);
/**
 * 设置设备录像配置信息
 *
 * @param  dev_id: 设备标识号
 * @param  record_type: 录像类型：1-内存缓存，2-磁盘存储
 * @param  period: 录像最大保存周期，单位为秒
 * @param  cfg: 配置信息（暂不支持）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口需要在设备开启录像后调用用于修改参数，否则无法进行设置
 */
IOT_API int STDCALL IOT_SetDeviceRecordInfo(IN const char * dev_id,
                                            IN int          record_type,
                                            IN int          period,
                                            IN const char * cfg);

/**
 * 获取关键帧
 *
 * @param  dev_id: 设备标识号
 * @param  info: 获取到的关键帧对应的参数信息，由调用者分配后传入；可为NULL，此时内部不会给此参数赋值
 * @param  buf: 数据缓冲区，由调用者分配后传入，并确保大小足够
 * @param  len: 数据长度，初始由调用者传入分配的缓冲区大小，当成功获取到关键帧后，会将此值置为实际帧长度后传出
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，获取成功与否可通过返回值得知
 *         2、传入的缓冲区大小建议为2M，当视频分辨率大于等于4K时，建议采用更大值，例如8M
 *         3、内部实现方式相当于开一个实时流，直到收到第一个关键帧后返回，并自动关闭实时流
 *         4、若内部开流成功，但一直收不到流数据或关键帧，默认15秒后超时退出
 */
IOT_API int STDCALL IOT_GetKeyFrame(IN const char *         dev_id,
                                    OUT IotVideoFrameInfo * info,
                                    OUT uint8_t *           buf,
                                    INOUT int *             len);

/**
 * 视频诊断管理
 *
 * @param  cmd: 命令类型：1-添加诊断任务，2-删除诊断任务，3-启动/停止诊断任务，4-查询诊断结果
 * @param  req_info: 透传的请求json格式字符串
 * @param  rsp_info: 回复的json字符串，该字符串缓冲区需由调用者分配
 * @param  rsp_len: 调用者输入分配的串长（根据回复json串长进行合理分配，查询类型功能建议不小于4K），接口调用成功时返回实际串长，失败时此值保持不变
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   当前接口只负责透传数据，不对请求及返回数据做校验，具体的输入及输出字段说明参见 http://api-insight.cbg.megvii-inc.com/project/2237/interface/api/cat_44059
 */
IOT_API int STDCALL IOT_VideoDiagnoseMgr(IN int         cmd,
                                         IN const char *req_info,
                                         OUT char *     rsp_info,
                                         INOUT int *    rsp_len,
                                         IN const char *ext_info);



/** @} */


/**
 * @name 传感器设备操作相关接口，包括增删改查，打开及关闭等功能
 * @{
 */

/**
 * 向IoT系统中添加传感器设备
 *
 * @param  dev: 传感器设备信息
 * @param  dev_id: 服务器分配给当前设备的唯一标识号（后续大部分接口都以此值为主要入参），
 *                 需由调用者分配串内存，长度大于等于 @ref IOT_LEN_DEVID
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器分配完设备标识号后函数才返回
 *         2、库内部使用统一的信令通道进行消息交互，调用者最好顺序调用
 */
IOT_API int STDCALL IOT_AddSensorDevice(IN const IotSensorDeviceConfig *dev, 
                                        OUT char *                      dev_id);

/**
 * 从IoT系统中删除传感器设备
 *
 * @param  dev_id: 传感器设备标识号
 * @param  force_delete: 是否强制删除设备：0-不强制（若此设备还在使用中，则不会删除），非0-强制（无论设备是否被打开，都会强制删除此设备，当前只支持此种方式）
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器完成删除后此函数才返回
 *         2、对于同一设备，添加和删除操作最好能保证由同一使用者调用，来避免将其他调用者增加的设备删除掉，影响他人正常使用
 */
IOT_API int STDCALL IOT_DeleteSensorDevice(IN const char *   dev_id, 
                                           IN int            force_delete);

/**
 * 修改IoT系统中的传感器设备信息
 *
 * @param  dev_id: 传感器设备标识号
 * @param  dev: 传感器设备信息
 * @param  syn_flag: 同步标志，0-非阻塞方式，非0-阻塞方式
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、当为非阻塞方式时，信令的成功与否一般会立刻返回，但是否真正更新成功，需由随后的事件回调得知
 *         2、当为阻塞方式时，直到服务端处理完此接口才会返回成功与否，此时不再有事件回调通知（除非返回值为超时错误）
 *         3、库内部使用统一的信令通道进行消息交互，调用者最好顺序调用
 */
IOT_API int STDCALL IOT_UpdateSensorDevice(IN const char *                  dev_id, 
                                           IN const IotSensorDeviceConfig * dev, 
                                           IN int                           syn_flag);

/**
 * 从IoT系统中获取传感器设备信息
 *
 * @param  dev_id: 传感器设备标识号
 * @param  dev: 返回的传感器设备信息
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器获取到参数信息后函数才返回
 *         2、库内部使用统一的信令通道进行消息交互，调用者最好顺序调用
 */
IOT_API int STDCALL IOT_GetSensorDevice(IN const char *             dev_id, 
                                        OUT IotSensorDeviceConfig * dev);

/**
 * 打开传感器设备
 *
 * @param  dev_id: 传感器设备标识号
 * @param  topic_name: kafka的目标topic名称（传感器proxy向此topic推送数据）
 * @param  syn_flag: 同步标志，0-非阻塞方式，非0-阻塞方式
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、使用非阻塞方式时，一般会立刻返回，但能否真正打开，需由随后的回调得知
 *         2、使用阻塞方式时，打开成功与否可通过返回值得知
 */
IOT_API int STDCALL IOT_OpenSensor(IN const char *  dev_id, 
                                   IN const char *  topic_name, 
                                   IN int           syn_flag);
/**
 * 关闭传感器设备
 *
 * @param  dev_id: 传感器设备标识号
 * @param  topic_name: kafka的目标topic名称
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 */
IOT_API int STDCALL IOT_CloseSensor(IN const char *dev_id, 
                                    IN const char *topic_name);

/**
 * 获取传感器开关状态
 *
 * @param  dev_id: 传感器设备标识号
 * @param  topic_name: kafka的目标topic名称
 * @param  status: 0为关闭状态，1或其它非0值表示已打开
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 */
IOT_API int STDCALL IOT_GetSensorStatus(IN const char * dev_id, 
                                        IN const char * topic_name, 
                                        OUT int *       status);

/** @} */


#ifdef __cplusplus
}
#endif
#endif
