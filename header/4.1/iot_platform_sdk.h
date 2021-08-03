/*******************************************************************************
 * @file        iot_platform_sdk.h
 * @brief       Interface file of IoT vision platform SDK
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
#ifndef _INCLUDE_IOT_VISION_PLATFORM_SDK__H_
#define _INCLUDE_IOT_VISION_PLATFORM_SDK__H_
#pragma once
#include "iot_center_errors.h"
//#include "iot_platform_types.h"

/// 导出接口定义
#ifdef _WIN32
# ifdef IOT_SDK_EXPORTS
#   define IOT_API __declspec(dllexport)
# else
#   define IOT_API __declspec(dllimport)
# endif
# ifndef STDCALL
#   define STDCALL          __stdcall
# endif
#else
# define IOT_API __attribute__((visibility("default")))
# define STDCALL
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
 * @brief 视觉中台SDK接入接口概述
 * @note  1、接口较多，按功能主要分为：系统相关、设备管理、设备参数配置、设备控制、国标平台相关、实时流管理、历史流管理及业务相关等几类
 *        2、和服务端直接交互的接口一般都含参数 ext_info，主要用于后续扩展交互字段，SDK只负责透传，非必选项，可能的格式样例如下：
 * {
 *     "traceId" : "74019b8819a06b31-80b1f7d51771c6b8-74019b8819a06b31-1"   // 全链路追踪ID，CBG后续业务要求此参数为必填项
 * }
 */


/**
 * @name SDK库系统级相关接口
 * @{
 */

/**
 * 初始化库
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   需在使用其他函数前第一个被调用
 */
IOT_API int STDCALL VIOT_Startup(void);

/**
 * 释放库
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   需在其他函数后最后一个被调用，用于释放库内部相关资源；
 *         若之前已成功注册到服务器上，请确保注销后再调用此函数
 */
IOT_API int STDCALL VIOT_Cleanup(void);

/**
 * 设置连接服务器超时相关参数
 *
 * @param  timeout: 连接超时等待时间，单位：毫秒，默认值为2000毫秒
 * @param  retry_num: 首次连接失败时的重试次数，默认值为2次（加上主动调用的1次，共3次）
 * @param  reconnect: 服务器异常断开时是否需要自动重连：0-不重连，非0-自动重连
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   建议在注册到服务器前调用，不调用时库内部按上面提到的默认值工作
 */
IOT_API int STDCALL VIOT_SetConnectInfo(IN int timeout,
                                        IN int retry_num,
                                        IN int reconnect);

/**
 * 设置消息回调，用于接收服务端主动回传的服务模块及设备的事件、报警等通知消息
 *
 * @param  cb: 回调函数指针，为空时，表示关闭消息回调功能
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  msg_msk: 消息类别掩码，参见 @ref IotMessageCategory
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、需在注册到服务器前调用，设置成功后，后续会一直有效。支持的消息类型参见 @ref IotMessageType
 *         2、不要在回调中处理费时操作，如调用开、关流等接口，否则可能会阻塞sdk内部整个消息通知机制
 *         3、此回调消息为SDK级别的，如果设置多次，后面的就会将前面的覆盖，即最后一次设置有效
 */
IOT_API int STDCALL VIOT_SetMessageCallback(IN IOT_CB_Message   cb,
                                            IN void *           user_data,
                                            IN uint32_t         msg_mask);

/**
 * 根据错误号及语言标识号，获取指定语种的错误描述信息
 *
 * @param  error: 接口函数返回的错误号
 * @param  lang_id: 语言标识号：0-中文，1-英文
 *
 * @return 返回错误描述信息字符串（非英文时采用UTF8编码），其中含出错的模块名称，有助于使用者快速定位出错原因
 */
IOT_API const char* STDCALL VIOT_GetErrorDescription(IN int error,
                                                     IN int lang_id);


/**
 * 连接并注册到服务器上（一个SDK一次只能连接到一套IoT系统中）
 *
 * @param  svr_addr: master服务器IP地址或域名
 * @param  svr_port: master服务器端口号
 * @param  username: 用户名
 * @param  password: 密码
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，连接成功时返回比较快，否则会根据设定的策略重试几次，此时调用者可能等待超时后才得到返回值
 *         2、当前系统中只提供一个统一对外的主控master服务器，故只需成功注册一次即可
 *         3、如果设置了自动重连功能，则与服务端断开后，内部会每隔 @ref IOT_TIMEOUT_UNIT 秒重连一次，直到连接成功
 */
IOT_API int STDCALL VIOT_Register(IN const char *   svr_addr,
                                  IN uint16_t       svr_port,
                                  IN const char *   username,
                                  IN const char *   password,
                                  IN const char *   ext_info);

/**
 * 从服务器上注销
 *
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、成功注销后，后面相关功能函数将不再可用，同时库内部会关闭之前打开的取流数据通道
 *         2、为实现优雅关闭，建议在关闭所有流后再调用此函数
 */
IOT_API int STDCALL VIOT_Unregister(IN const char *ext_info);

/**
 * 获取系统信息（含服务模块版本，节点统计信息等）
 *
 * @param  info_str: 返回的json信息串内容，该字符串缓冲区需由调用者分配。格式样例如下：
 * {
 *     "systemVersion" : "iot-center:4.0.2006070003",   // 当前服务端系统版本号
 *     "nodeList" : [                                   // 集群节点列表
 *     {
 *         "nodeAddr" : "MEGVII20060000296530",     // 节点地址（域名或主机名或IP地址）
 *         "nodeType" : 1,                          // 节点类型：1-主控节点，2-工作节点
 *         "nodeStatus" : 0,                        // 节点状态：0-正常状态，1-异常状态，2-未知状态
 *         "deviceNum" : 9,                         // 管理的设备总数
 *         "streamInNum" : 0,                       // 接入流总数
 *         "streamOutNum" : 0,                      // 转发流总数
 *         "picturePerHour" : 0,                    // 每小时抓拍图片数
 *         "alarmPerHour" : 0                       // 每小时报警数
 *     }]
 * }
 * @param  info_len: 输入时为调用者分配的串长（建议不小于4K），接口返回成功时输出实际串长，失败时此值一般保持不变（若错误码为分配缓冲区长度过短，则此值会保存实际长度）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此为阻塞接口，服务端内部需要做汇总，可能返回稍慢
 */
IOT_API int STDCALL VIOT_GetSystemInfo(OUT char *       info_str,
                                       INOUT int *      info_len,
                                       IN const char *  ext_info);

/**
 * 向系统服务中动态添加设备厂商类型，用于最小化开发工作量来支持现场项目中遇到新设备厂商的场景
 *
 * @param  vendor_id: 厂商标识号，不能添加已存在的类型，当前支持的类型参见 @ref IotDeviceVendor
 * @param  vendor_name: 厂商名称
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器返回命令后函数才返回
 *         2、此接口一般用于项目上存在当前IoT系统不支持的某个厂商，为了快速对接此厂商，只需调用者新增类型，服务端新加一个proxy就可实现接入的情况
 */
IOT_API int STDCALL VIOT_AddDeviceVendor(IN int          vendor_id,
                                         IN const char * vendor_name,
                                         IN const char * ext_info);
/**
 * 从系统服务中删除动态添加的设备厂商类型
 *
 * @param  vendor_id: 厂商标识号，不能删除系统默认支持的类型，当前支持的类型参见 @ref IotDeviceVendor
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器返回命令后函数才返回
 *         2、若用此接口访问早期版本的服务端，具体的响应依赖服务端的支持情况，如服务端直接丢弃不支持的命令消息，则此接口会返回超时错误
 */
IOT_API int STDCALL VIOT_DeleteDeviceVendor(IN int          vendor_id,
                                            IN const char * ext_info);

/** @} */


/**
 * @name 设备操作相关接口，包括设备、通道的增删改查，设备目录的拉取等功能
 * @note 后面提到的阻塞方式指的是，该接口需要等收到服务端响应后才返回，由于涉及到网络传输及各服务模块之间的交互，故函数返回可能有些慢；
 *       非阻塞方式指得是返回时不包括与服务端的交互，故一般返回比较快。
 *       对于无特殊说明的接口，内部实现基本没有较耗时的操作，一般都能快速返回
 * @{
 */

/**
 * 向系统中添加设备
 *
 * @param  dev_info: 设备信息，json格式样例如下：（未特殊说明的字段为可选项）
 * {
 *     "name" : "中关村大街东路口",  // 设备名称
 *     "type" : 1,                // 设备类型（必选项），参见 @ref IotDeviceType
 *     "vendorId" : 11,           // 设备厂商（必选项），参见 @ref IotDeviceVendor
 *     "addr" : "192.168.0.8",                  // 设备地址（类型为1/2/4/5时为必选项）
 *     "port" : 8000,                           // 信令端口号（类型为1/2/4/5时为必选项）
 *     "videoPort" : 554,                       // 视频流端口号（类型为2/5时为必选项）
 *     "username" : "admin",                    // 用户名（类型为1/2/4/5时为必选项）
 *     "password" : "12345",                    // 密码（类型为1/2/4/5时为必选项）
 *     "platformId" : "3402000000132xxxxxxx",   // 国标平台标识（类型为3/6时为必选项）
 *     "deviceCode" : "3402000000131xxxxxxx",   // 国标设备编码（类型为3/6时为必选项）
 *     "channelNum" : 1                         // 通道个数（必选项）
 * }
 * @param  dev_id: 服务器分配给当前设备的唯一标识号（后续大部分接口都以此值为主要入参），
 *                 需由调用者分配串内存，长度大于等于 @ref IOT_LEN_DEVID
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器分配完设备标识号后函数才返回
 *         2、设备可认为是个空壳，需要添加通道后才可进行开关流等操作，添加通道时需要用到此接口返回的设备标识号
 */
IOT_API int STDCALL VIOT_AddDevice(IN const char *  dev_info,
                                   OUT char *       dev_id,
                                   IN const char *  ext_info);

/**
 * 从系统中删除设备
 *
 * @param  dev_id: 设备标识号
 * @param  force_delete: 是否强制删除设备：0-不强制（若此设备还在被使用，则不会删除），非0-强制（关闭可能被打开的所有流，并删除此设备）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器完成删除后此函数才返回
 *         2、对于同一设备，添加和删除操作最好能保证由同一使用者调用，来避免将其他调用者增加的设备删除掉，影响他人正常使用
 *         3、删除设备时，会自动删除其所包含的所有通道
 */
IOT_API int STDCALL VIOT_DeleteDevice(IN const char *   dev_id,
                                      IN int            force_delete,
                                      IN const char *   ext_info);

/**
 * 修改系统中指定设备的设备信息
 *
 * @param  dev_id: 设备标识号
 * @param  dev_info: 设备信息，json串格式可参考添加设备接口的相关说明。需要注意“设备类型”字段不支持修改
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器更新完设备信息后函数才返回
 *         2、设备类型为系统分配服务的一个关键字段，不支持修改。若一定修改，可通过删除设备，并添加设备的方式来实现
 *         3、修改参数含设备厂商、设备地址、端口号、用户名、密码、通道数等重要参数时，可能会引发系统自动关闭已经打开的流，其它已经开流的应用可能需要重新开流
 */
IOT_API int STDCALL VIOT_UpdateDevice(IN const char *   dev_id,
                                      IN const char *   dev_info,
                                      IN const char *   ext_info);

/**
 * 从系统中查询指定设备的设备信息
 *
 * @param  dev_id: 设备标识号
 * @param  dev_info: 设备信息，json格式样例如下：
 * {
 *     "name" : "中关村大街东路口",  // 设备名称
 *     "type" : 1,                // 设备类型（必选项），参见 @ref IotDeviceType
 *     "vendorId" : 11,           // 设备厂商（必选项），参见 @ref IotDeviceVendor
 *     "addr" : "192.168.0.8",                  // 设备地址（类型为1/2/4/5时为必选项）
 *     "port" : 8000,                           // 信令端口号（类型为1/2/4/5时为必选项）
 *     "videoPort" : 554,                       // 视频流端口号（类型为2/5时为必选项）
 *     "username" : "admin",                    // 用户名（类型为1/2/4/5时为必选项）
 *     "password" : "12345",                    // 密码（类型为1/2/4/5时为必选项）
 *     "platformId" : "3402000000132xxxxxxx",   // 国标平台标识（类型为3/6时为必选项）
 *     "deviceCode" : "3402000000131xxxxxxx",   // 国标设备编码（类型为3/6时为必选项）
 *     "channelNum" : 4,                        // 通道个数（必选项），添加设备时设置的个数，大于等于通道列表中的实际个数
 *     "chanList" : [                           // 通道列表（必选项）
 *     {
 *         "channelId" : "110000200100000215",      // 通道标识号（必选项）
 *         "capability" : 1,                        // 通道能力，参见 @ref IotChannelCapability
 *         "name" : "中关村大街路口1号",               // 通道名称
 *         "channelNo" : 0,                         // 通道号，起始值从0开始（必选项）
 *         "channelCode" : "3402000000131xxxxxxx",  // 通道国标编码
 *         "url" : "rtsp://1.2.3.4/554",            // 取流地址串，可为相机rtsp串、kafka抓拍流地址串等（kafka类型相机时为必选项）
 *         "topicName" : "xxx",                     // kafka的topic名称串（kafka类型相机时为必选项）
 *         "extraInfo" : ""                         // 额外信息字段，用于透传上层业务的“其他”字段信息，一般为json串
 *     }]
 * }
 * @param  info_len: 输入时为调用者分配的串长（建议不小于4K），接口返回成功时输出实际串长，失败时此值一般保持不变（若错误码为分配缓冲区长度过短，则此值会保存实际长度）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此为阻塞接口，库内部收到服务器响应消息后才返回
 */
IOT_API int STDCALL VIOT_QueryDevice(IN const char * dev_id,
                                     OUT char *      dev_info,
                                     INOUT int *     info_len,
                                     IN const char * ext_info);

/**
 * 向系统中指定设备下添加通道
 *
 * @param  chan_info: 通道信息，json格式样例如下：（未特殊说明的字段为可选项）
 * {
 *     "name" : "中关村大街路口1号",               // 通道名称
 *     "capability" : 1,                        // 通道能力，参见 @ref IotChannelCapability
 *     "parentId" : "110000200100000001",       // 所属的设备或平台标识号（必选项）
 *     "channelNo" : 0,                         // 通道号，起始值从0开始（通道类型为设备时必选）
 *     "channelCode" : "3402000000131xxxxxxx",  // 通道编码（通道类型为平台时必选）
 *     "url" : "rtsp://1.2.3.4/554",            // 取流地址串，可为相机rtsp串、kafka抓拍流地址串等（kafka类型相机时为必选项）
 *     "topicName" : "xxx",                     // kafka的topic名称串（kafka类型相机时为必选项）
 *     "extraInfo" : ""                         // 额外信息字段，用于透传上层业务的“其他”字段信息，一般为json串
 * }
 * @param  chan_id: 服务器分配给当前通道的唯一标识号，需由调用者分配串内存，长度大于等于 @ref IOT_LEN_DEVID
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器分配完通道标识号后函数才返回
 *         2、设备可认为是个空壳，需要添加通道后才可进行开关流等操作，故添加设备成功后一般会紧接着添加通道
 *         3、添加的通道总数不能超过添加设备时设定的通道个数，且要保证通道号不要重复，否则会添加失败
 */
IOT_API int STDCALL VIOT_AddChannel(IN const char * chan_info,
                                    OUT char *      chan_id,
                                    IN const char * ext_info);
/**
 * 从系统中指定的设备下删除通道
 *
 * @param  chan_id: 通道标识号
 * @param  force_delete: 是否强制删除通道：0-不强制（若此通道还在被使用，则不会删除），非0-强制（关闭可能被打开的所有流，并删除此通道）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器完成删除后此函数才返回
 *         2、强制删除通道时，可能会造成此通道的使用者出现错误
 */
IOT_API int STDCALL VIOT_DeleteChannel(IN const char *   chan_id,
                                       IN int            force_delete,
                                       IN const char *   ext_info);
/**
 * 修改系统中的指定设备的通道信息
 *
 * @param  chan_id: 通道标识号
 * @param  chan_info: 通道信息，json串格式可参考添加通道接口的相关说明。需要注意“设备标识号”字段不支持修改
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，一般需要等待服务器更新完通道信息后函数才返回
 *         2、修改参数含通道类型、通道号、地址等重要参数时，可能会引发系统自动关闭已经打开的流，其它已经开流的应用可能需要重新开流
 *         3、修改成功后，其它连接到服务端的SDK会收到通道更新通知
 */
IOT_API int STDCALL VIOT_UpdateChannel(IN const char *  chan_id,
                                       IN const char *  chan_info,
                                       IN const char *  ext_info);

/**
 * 批量获取设备状态信息
 *
 * @param  dev_num: 请求设备的个数，大小不能超过 @ref IOT_MAX_LST_NUM, 超过此值请分多次查询
 * @param  dev_id_list: 要请求的设备标识号列表，用二维数组保存
 * @param  status_list: 获取到的设备状态信息，保存在一维数组中，只在返回成功时有效。状态值：0-在线，1-掉线，2-未知
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，当一次请求设备较多时，可能返回稍慢
 *         2、请求设备的个数要和下面调用者分配的数组大小保持一致，来避免内存访问越界问题
 */
IOT_API int STDCALL VIOT_BatchGetDeviceStatus(IN int            dev_num,
                                              IN char           dev_id_list[][IOT_LEN_DEVID],
                                              OUT int           status_list[],
                                              IN const char *   ext_info);

/**
 * 获取设备目录列表（包括设备及通道）
 *
 * @param  list_type: 拉取的列表类型：0-设备和通道的合集，1-只拉取设备，2-只拉取通道
 * @param  page_size: 设备批量分页大小，即一次消息回调的设备个数，范围[1-1000]，超出此范围则采用系统默认值，如50等
 * @param  cb: 回调函数指针，不能为空，否则无法返回列表数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为非阻塞接口，一般会立刻返回，随后每次回调指定大小的设备数，最后一包可能不满，会返回实际剩余设备个数
 *         2、若系统中无设备，即设备列表为空时，也会回调一次，此时回调函数中的设备个数为0
 *         3、通过额外回调设备目录列表参数为NULL来表示此次获取结束，如列表为空，其实会收到两次回调，即第一次为json中的列表总数字段为0，第二次串指针为NULL
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 */
IOT_API int STDCALL VIOT_GetDeviceList(IN int                list_type,
                                       IN int                page_size,
                                       IN IOT_CB_CatalogList cb,
                                       IN void *             user_data,
                                       IN const char *       ext_info);

/**
 * 分页获取设备目录列表（包括设备及通道）
 *
 * @param  list_type: 拉取的列表类型：0-设备和通道的合集，1-只拉取设备，2-只拉取通道
 * @param  page_size: 设备分页大小，即一次能够拉取的设备个数，范围[1-1000]，超出此范围则采用系统默认值，如50等
 * @param  page_no: 设备列表页号，起始值从0开始
 * @param  list_info: 设备列表信息，由调用者分配后传入，json格式样例如下：
 * {
 *     "pageSize" : 50,     // 分页大小
 *     "pageNo" : 0,        // 当前页号
 *     "deviceSum" : 2,     // 设备及通道总数
 *     "curPageNum" : 2,    // 当前页设备及通道总数
 *     "deviceList" : [     // 当前页设备列表
 *     {
 *         "deviceId" : "110000200100000215",   // 设备标识号
 *         "name" : "中关村大街东路口",            // 设备名称
 *         "type" : 1,                          // 设备类型（必选项），参见 @ref IotDeviceType
 *         "vendorId" : 11,                     // 设备厂商（必选项），参见 @ref IotDeviceVendor
 *         "addr" : "192.168.0.8",                  // 设备地址（类型为1/2/4/5时为必选项）
 *         "port" : 8000,                           // 信令端口号（类型为1/2/4/5时为必选项）
 *         "videoPort" : 554,                       // 视频流端口号（类型为2/5时为必选项）
 *         "username" : "admin",                    // 用户名（类型为1/2/4/5时为必选项）
 *         "password" : "12345",                    // 密码（类型为1/2/4/5时为必选项）
 *         "platformId" : "3402000000132xxxxxxx",   // 国标平台标识（类型为3/6时为必选项）
 *         "deviceCode" : "3402000000131xxxxxxx",   // 国标设备编码（类型为3/6时为必选项）
 *         "channelNum" : 1,                        // 通道个数（必选项）
 *         "onlineStatus" : 1                       // 是否在线：0-掉线，1-在线，2-未知
 *     }],
 *     "channelList" : [    // 当前页通道列表
 *     {
 *         "parentId" : "110000200100000215",       // 所属的设备或平台标识号
 *         "channelId" : "110000200100000005",      // 通道标识号
 *         "capability" : 1,                        // 通道能力，参见 @ref IotChannelCapability
 *         "name" : "中关村大街路口1号",               // 通道名称
 *         "channelNo" : 0,                         // 通道号，起始值从0开始
 *         "channelCode" : "3402000000131xxxxxxx",  // 通道国标编码
 *         "url" : "rtsp://1.2.3.4/554",            // 取流地址串，可为相机rtsp串、kafka抓拍流地址串等（kafka类型相机时为必选项）
 *         "topicName" : "xxx",                     // kafka的topic名称串（kafka类型相机时为必选项）
 *         "extraInfo" : ""                         // 额外信息字段，用于透传上层业务的“其他”字段信息，一般为json串
 *     }]
 * }
 * @param  info_len: 输入时为调用者分配的串长（根据分页大小定义串长，如页大小为50时建议值为1K），接口返回成功时输出实际串长，失败时此值一般保持不变（若错误码为分配缓冲区长度过短，则此值会保存实际长度）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，库内部收到服务端响应后才会返回
 *         2、每次返回指定大小的设备数，最后一包不满时，会返回实际剩余设备个数
 *         3、服务端每次根据输入参数实时计算，故在多次获取过程中系统设备存在CRUD的情况下，返回的列表并不能保证没有遗漏或重复
 */
IOT_API int STDCALL VIOT_GetDeviceListByPage(IN int             list_type,
                                             IN int             page_size,
                                             IN int             page_no,
                                             OUT char *         list_info,
                                             INOUT int *        info_len,
                                             IN const char *    ext_info);


/**
 * 启动设备探测
 *
 * @param  start_ip: 搜索网段的起始IP地址，为NULL或空串表示按系统默认规则，即依赖设备发现服务所在节点的地址，如 xxx.xxx.0.0
 * @param  end_ip: 搜索网段的结束IP地址，为NULL或空串表示按系统默认规则，即依赖设备发现服务所在节点的地址，如 xxx.xxx.255.255
 * @param  discovery_timeout: 查找设备的超时时间：0-不关闭，大于0的值-表示对应的秒后自动关闭，此时可不用调用停止接口（暂不支持）
 * @param  cb: 回调函数指针，不能为空，否则无法返回列表数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  session_id: 服务端返回的会话标识号，由用户传入，分配的串长需大于等于64字节，成功时置为有效值，用于后续停止操作；失败时未定义，此值不可用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，库内部收到服务端响应后才会返回
 *         2、一个sdk不支持同时进行两次查询，即调用者需保证在回调完成前不要再次调用此接口
 *         3、调用成功后，每收到一次服务端通知，就会回调一次，其中可能会含多个设备信息（当前版本只含1个，0个表示回调结束）
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 */
IOT_API int STDCALL VIOT_StartDeviceDiscovery(IN const char *               start_ip,
                                              IN const char *               end_ip,
                                              IN int                        discovery_timeout,
                                              IN IOT_CB_DeviceDiscoveryList cb,
                                              IN void *                     user_data,
                                              OUT char *                    session_id,
                                              IN const char *               ext_info);
/**
 * 停止设备探测
 *
 * @param  session_id: 启动接口返回的会话标识号
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、服务端探测设备完成后，会自动关闭，若此后再次调用此停止接口或未调用启动，则统一返回 IOT_ERR_PROXY_ALREALDY_CLOSED
 *         2、此为阻塞接口，库内部收到服务端响应后才会返回
 */
IOT_API int STDCALL VIOT_StopDeviceDiscovery(IN const char *    session_id,
                                             IN const char *    ext_info);

/** @} */


/**
 * @name 设备参数获取及设置等相关功能
 * @note 该类接口涉及多个模块之间相互通信，且一般需要proxy服务与设备之间进行交互，得到设备的响应后才能返回，故函数返回可能稍慢
 * @{
 */

/**
 * 获取设备配置信息
 *
 * @param  cmd: 配置命令类型，参见 @ref IotDeviceConfigCommand
 * @param  dev_id: 设备标识号
 * @param  req_info: 请求信息，当命令类型涉及到更多输入参数时，需要用到此参数中的相关字段，否则为NULL即可。目前可能用到的字段如下：
 * {
 *     "channelNo" : 0,     // 设备通道号，当命令类型涉及设备时，此参数无效，传0即可；当命令类型涉及通道时，此参数必选且为有效值
 *     "profileType" : 0,   // 通道码流类型：0-主码流（默认值），1-子码流，2-第二子码流
 * }
 * @param  rsp_info: 返回的json信息串内容，该字符串缓冲区需由调用者分配。字段名参考命令类型中对应的样例说明
 * @param  rsp_len: 输入时为调用者分配的串长（不同命令对应的串长不一样，建议统一定义为不小于4K），接口返回成功时输出实际串长，失败时此值一般保持不变（若错误码为分配缓冲区长度过短，则此值会保存实际长度）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持 @ref IOT_DT_SMART_IPC 类型的设备，其他类型的设备返回不支持错误码
 */
IOT_API int STDCALL VIOT_GetDeviceConfig(IN int          cmd,
                                         IN const char * dev_id,
                                         IN const char * req_info,
                                         OUT char *      rsp_info,
                                         INOUT int *     rsp_len,
                                         IN const char * ext_info);
/**
 * 设置设备配置信息
 *
 * @param  cmd: 配置命令类型，参见 @ref IotDeviceConfigCommand
 * @param  dev_id: 设备标识号
 * @param  req_info: 要设置的json配置串内容。字段名参考命令类型中对应的样例说明
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持 @ref IOT_DT_SMART_IPC 类型的设备，其他类型的设备返回不支持错误码
 */
IOT_API int STDCALL VIOT_SetDeviceConfig(IN int          cmd,
                                         IN const char * dev_id,
                                         IN const char * req_info,
                                         IN const char * ext_info);
/**
 * 批量设置设备配置信息
 *
 * @param  cmd: 配置命令类型，参见 @ref IotDeviceConfigCommand
 * @param  dev_num: 请求设备的个数，大小不能超过 @ref IOT_MAX_LST_NUM, 超过此值请分多次设置
 * @param  dev_id_list: 要请求的设备标识号列表，用二维数组保存
 * @param  req_info: 要设置的json配置串内容。字段名参考命令类型中对应的样例说明
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此接口只支持 @ref IOT_DT_SMART_IPC 类型的部分厂商的设备，其他类型的设备返回不支持错误码
 *         2、部分命令类型可能会有一次或多次的异步消息通知，请参考对应配置命令中的相关说明
 */
IOT_API int STDCALL VIOT_BatchSetDeviceConfig(IN int            cmd,
                                              IN int            dev_num,
                                              IN char           dev_id_list[][IOT_LEN_DEVID],
                                              IN const char *   req_info,
                                              IN const char *   ext_info);


/**
 * 设备云台、镜头控制
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 设备通道号，从0开始，默认值为0
 * @param  ptz_cmd: 云台控制命令，参见 @ref IotPtzControlCommand
 * @param  speed: 控制云台、镜头的速度，范围为[1-8]
 * @param  stop: 云台停止动作或开始动作：0-开始，非0-停止
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持智能机和具备真实厂商的视频流相机（即用其设备SDK接入的设备，含onvif协议接入），并且设备本身支持云镜控制，否则返回不支持错误码
 */
IOT_API int STDCALL VIOT_PtzControl(IN const char *  dev_id,
                                    IN int           chan_no,
                                    IN int           ptz_cmd,
                                    IN int           speed,
                                    IN int           stop,
                                    IN const char *  ext_info);
/**
 * 设备云台预置位控制
 *
 * @param  dev_id: 设备标识号
 * @param  chan_no: 设备通道号，从0开始，默认值为0
 * @param  cmd: 预置位控制命令，参见 @ref IotPtzControlCommand 中的预置位相关命令
 * @param  index: 预置位索引号，范围为[1-256]
 * @param  param: 预留参数（暂未用到）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口目前只支持智能机和具备真实厂商的视频流相机（即用其设备SDK接入的设备，含onvif协议接入），并且设备本身支持云镜控制，否则返回不支持错误码
 */
IOT_API int STDCALL VIOT_PtzPreset(IN const char *   dev_id,
                                   IN int            chan_no,
                                   IN int            cmd,
                                   IN int            index,
                                   IN int            param,
                                   IN const char *   ext_info);

/**
 * 远程设备重启
 *
 * @param  dev_id: 设备标识号
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，重启成功与否可通过返回值得知，返回成功时即认为设备已经开始重启
 *         2、此接口目前只支持智能机和具备真实厂商的视频流相机（即用其设备SDK接入的设备，含onvif协议接入），否则返回不支持错误码
 */
IOT_API int STDCALL VIOT_RebootDevice(IN const char *   dev_id,
                                      IN const char *   ext_info);

/** @} */


/**
 * @name 国标平台管理相关功能，包括GB28181及GA1400两类
 * @{
 */

/**
 * 获取国标平台目录信息（异步分包方式）
 *
 * @param  platform_id: 国标平台标识号，不能为空
 * @param  device_code: 设备编码，可为空
 * @param  platform_type: 国标平台类型：1-GB28181, 2-GA1400
 * @param  packet_size: 每个数据包中的目录个数，即一次消息回调的目录个数，范围[0-1000]，传0时表示采用系统默认值，如50等
 * @param  cb: 回调函数指针，不能为空，否则无法返回获取到的数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  catalog_sum: 从下级平台返回的设备目录总数，由调用者传递此参数来获取此值，传NULL时表示不关心此值
 * @param  session_id: 返回的会话标识号，由用户传入，分配的串长需大于等于64字节，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、目前版本此接口只支持 @ref IOT_DT_GB28181_IPC 及 @ref IOT_DT_GA1400_IPC 两种类型的设备，其他类型的设备返回相应错误码
 *         2、此为阻塞接口，库内部收到设备目录总数后才会返回，后续每收到服务端发来的一包数据后会回调一次，最后一次回调中的列表串指针为NULL用于表示接收完毕（中途接收超时也会回调NULL来表示结束）
 *         3、当下级平台设备较多时，总接收时间可能较长，请耐心等待
 *         4、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 *         5、platform_id不能为空，device_code为空时，表示要获取此平台下面的一级设备信息，一般用于首次调用；
 *           device_code不为空时，表示要获取此平台下此设备下面的所有子设备信息
 *         6、若在拉取过程中再次调用此接口，则库内部会返回错误，用于保证同时只有一次拉取操作
 */
IOT_API int STDCALL VIOT_GetPlatformCatalog(IN const char *                 platform_id,
                                            IN const char *                 device_code,
                                            IN int                          platform_type,
                                            IN int                          packet_size,
                                            IN IOT_CB_PlatformDeviceCatalog cb,
                                            IN void *                       user_data,
                                            OUT int *                       catalog_sum,
                                            OUT char *                      session_id,
                                            IN const char *                 ext_info);
/**
 * 获取国标平台目录信息的取消接口
 *
 * @param  session_id: 获取接口返回的会话标识号
 * @param  platform_id: 国标平台标识号，非必填参数，可为空
 * @param  device_code: 设备编码，非必填参数，可为空
 * @param  platform_type: 国标平台类型：1-GB28181, 2-GA1400
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、目前版本此接口只支持 @ref IOT_DT_GB28181_IPC 及 @ref IOT_DT_GA1400_IPC 两种类型的设备，其他类型的设备返回相应错误码
 *         2、此为阻塞接口，库内部收到服务端的响应后才会返回，取消成功后会回调一次列表串指针为NULL的消息来表示取消完成
 *         3、若取消已完成或未开始的拉取命令，则直接返回成功，且不再有列表串指针为NULL的消息回调通知
 */
IOT_API int STDCALL VIOT_CancelGetPlatformCatalog(IN const char * session_id,
                                                  IN const char * platform_id,
                                                  IN const char * device_code,
                                                  IN int          platform_type,
                                                  IN const char * ext_info);

/**
 * 获取平台设备类型的设备信息
 *
 * @param  dev_id: 设备标识号
 * @param  dev_info: 返回的设备信息，json格式样例如下：
 * {
 *     "manufacturer" : "MEGVII",   // 厂商
 *     "model" : "c3s",             // 型号
 *     "firmware" : "x.x.x",        // 固件版本
 *     "maxCameraNum" : 1,          // 最大视频通道数
 *     "maxAlarmNum" : 2            // 最大告警通道数
 * }
 * @param  info_len: 输入时为调用者分配的串长（建议不小于1K），接口返回成功时输出实际串长，失败时此值一般保持不变（若错误码为分配缓冲区长度过短，则此值会保存实际长度）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   此接口只支持平台类型的设备，其他类型的设备返回相应错误码
 */
IOT_API int STDCALL VIOT_GetPlatformDeviceInfo(IN const char *  dev_id,
                                               OUT char *       dev_info,
                                               INOUT int *      info_len,
                                               IN const char *  ext_info);

/** @} */


/**
 * @name 数据流访问的开关接口，包括抓拍图片、实时视频流
 * @{
 */

/**
 * 打开实时图片流
 *
 * @param  chan_id: 通道标识号
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
IOT_API int STDCALL VIOT_OpenPictureStream(IN const char *      chan_id,
                                           IN int               sync_flag,
                                           IN IOT_CB_PicStream  cb,
                                           IN void *            user_data,
                                           OUT HANDLE *         handle,
                                           IN const char *      ext_info);

/**
 * 关闭实时图片流
 *
 * @param  handle: 图片流句柄
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   设备掉线或流出错等原因会引发库内部自动关流操作并释放相应资源，此时使用者可以不调用此关闭接口，如果调用则会返回 IOT_ERR_NOEXIST
 */
IOT_API int STDCALL VIOT_ClosePictureStream(IN HANDLE       handle,
                                            IN const char * ext_info);

/**
 * 打开实时视频流
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
IOT_API int STDCALL VIOT_OpenLiveStream(IN const char *     chan_id,
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
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   设备掉线或流出错等原因会引发库内部自动关流操作并释放相应资源，此时使用者可以不调用此关闭接口，如果调用则会返回 IOT_ERR_NOEXIST
 */
IOT_API int STDCALL VIOT_CloseLiveStream(IN HANDLE          handle,
                                         IN const char *    ext_info);

/** @} */


/**
 * @name 历史流访问相关接口，包括录像文件检索，开关流，回放控制及下载等功能
 * @{
 */

/**
 * 打开历史视频流
 *
 * @param  chan_id: 通道标识号
 * @param  start_time: 起始时间(UTC)，字符串格式为：yyyy-mm-dd hh:MM:ss，如：2019-02-03 12:01:10
 * @param  end_time: 结束时间(UTC)，串格式如上
 * @param  sync_flag: 同步标志，0-非阻塞方式，非0-阻塞方式
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 历史视频流句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、使用非阻塞方式时，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         2、使用阻塞方式时，开流成功与否可通过返回值得知。返回成功时，只表明与服务端的信令交互是正确的，但并不表示一定会取流成功或立刻收到数据流回调。
 *            若由于设备的原因一直没收到流，默认最长超时 @ref IOT_STREAM_TIMEOUT 秒后会有消息回调通知
 *         3、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 *         4、历史流接收完毕，会收到流结束的回调通知
 */
IOT_API int STDCALL VIOT_OpenClipStream(IN const char *     chan_id,
                                        IN const char *     start_time,
                                        IN const char *     end_time,
                                        IN int              sync_flag,
                                        IN IOT_CB_VidStream cb,
                                        IN void *           user_data,
                                        OUT HANDLE *        handle,
                                        IN const char *     ext_info);

/**
 * 关闭历史视频流
 *
 * @param  handle: 历史视频流句柄
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、设备掉线或流出错等原因会引发库内部自动关流操作并释放相应资源，此时使用者可以不调用此关闭接口，如果调用则会返回 IOT_ERR_NOEXIST
 *         2、在接收历史流的过程中，可调用此接口进行关闭；在收到历史流接收完成消息后，无需再调用此接口进行关闭
 */
IOT_API int STDCALL VIOT_CloseClipStream(IN HANDLE          handle,
                                         IN const char *    ext_info);

/**
 * 历史视频流回放控制
 *
 * @param  handle: 视频流句柄
 * @param  command: 命令码，枚举值范围参见 @ref IotPlaybackCommand
 * @param  param: 命令码对应的参数值，不同的命令码对应的参数值不一样，具体值参见命令码说明
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，库内部收到服务端响应后才返回，可在播放过程中多次调用，建议单线程方式调用
 *         2、受限于下级国标平台的原因，部分命令码可能不支持或支持的不好，目前根据返回值无法保证功能调用正常
 */
IOT_API int STDCALL VIOT_PlaybackControl(IN HANDLE          handle,
                                         IN int             command,
                                         IN int             param,
                                         IN const char *    ext_info);

/**
 * 检索历史流录像列表
 *
 * @param  chan_id: 通道标识号
 * @param  start_time: 起始时间(UTC)，字符串格式为：yyyy-mm-dd hh:MM:ss，如：2019-02-03 12:01:10
 * @param  end_time: 结束时间(UTC)，串格式如上
 * @param  cb: 回调函数指针，不能为空，否则无法返回获取到的数据
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为非阻塞接口，一般会立刻返回，库内部收到完整列表信息后，会通过回调函数一次回调出来，列表为空也会回调一次
 *         2、当系统中媒体流片段个数较多时，获取一次可能花费较长时间，请耐心等待，不建议还未收到上次回调，就再次调用
 *         3、尽量避免在回调函数中做比较耗时的操作，以防影响其他命令的处理
 */
IOT_API int STDCALL VIOT_RetrieveClipList(IN const char *    chan_id,
                                          IN const char *    start_time,
                                          IN const char *    end_time,
                                          IN IOT_CB_ClipList cb,
                                          IN void *          user_data,
                                          IN const char *    ext_info);

/**
 * 开始历史视频流下载
 *
 * @param  chan_id: 通道标识号
 * @param  start_time: 起始时间(UTC)，字符串格式为：yyyy-mm-dd hh:MM:ss，如：2019-02-03 12:01:10
 * @param  end_time: 结束时间(UTC)，串格式如上
 * @param  speed: 下载速度，值参见 @ref IotDownloadSpeed
 * @param  sync_flag: 同步标志，0-非阻塞方式，非0-阻塞方式
 * @param  cb: 回调函数指针
 * @param  user_data: 用户参数，用于传递进回调函数中作为参数供调用者使用
 * @param  handle: 下载句柄，由用户传入，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、非阻塞模式下，一般会立刻返回，但能否真正获取到流，需由随后的回调得知：若成功，则数据回调函数正常回调数据；若失败，则由消息回调函数通知失败原因
 *         2、阻塞模式下，开流成功与否可通过返回值得知，默认最长超时大小为 @ref IOT_STREAM_TIMEOUT
 *         3、尽量避免在回调函数中做比较耗时的操作，以防影响后续流数据的接收
 *         4、历史视频流下载接收完毕，会收到流结束的回调通知
 */
IOT_API int STDCALL VIOT_OpenClipDownload(IN const char *       chan_id,
                                          IN const char *       start_time,
                                          IN const char *       end_time,
                                          IN int                speed,
                                          IN int                sync_flag,
                                          IN IOT_CB_VidStream   cb,
                                          IN void *             user_data,
                                          OUT HANDLE *          handle,
                                          IN const char *       ext_info);
/**
 * 关闭历史视频流下载
 *
 * @param  handle: 历史视频流下载句柄
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、设备掉线或流出错等原因会引发库内部自动关流操作并释放相应资源，此时使用者可以不调用此关闭接口，如果调用则会返回 IOT_ERR_NOEXIST
 *         2、在下载历史流的过程中，可调用此接口进行关闭；在收到历史流接收完成消息后，无需再调用此接口进行关闭
 */
IOT_API int STDCALL VIOT_CloseClipDownload(IN HANDLE        handle,
                                           IN const char *  ext_info);

/** @} */


/**
 * @name 业务应用相关接口，包括图片转存，录像文件转存等功能
 * @{
 */

/**
 * 启动设备开流并向指定服务端推流
 *
 * @param  chan_id: 通道标识号
 * @param  stream_type: 媒体流类型，值参见 @ref IotStreamType ，当前只支持图片流，传0即可
 * @param  stream_way: 取流方式，值参见 @ref IotDeviceStreamType （暂不支持，传0即可）
 * @param  dest_type: 收流服务器类型：0-core，1-kafka（暂不支持），2-GA（云图）
 * @param  dest_addr: 收流服务端地址（如core的推送图片流URL或kafka服务器地址）
 * @param  session_id: 返回的推流会话标识号，由用户传入，分配的串长需大于等于64字节，成功时置为有效值，用户可用于后续操作；失败时未定义，用户不能使用
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，收到服务端响应消息后接口才会返回
 *         2、系统内部推流服务模块收到此消息后，先开流然后再将收到的流数据推送到参数指定的服务器上
 */
IOT_API int STDCALL VIOT_StartPushStream(IN const char * chan_id,
                                         IN int          stream_type,
                                         IN int          stream_way,
                                         IN int          dest_type,
                                         IN const char * dest_addr,
                                         OUT char *      session_id,
                                         IN const char * ext_info);
/**
 * 停止向服务端推流
 *
 * @param  chan_id: 通道标识号
 * @param  session_id: 推流会话标识号
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、在开始推流成功的条件，系统内部会保证一直在推流（即使设备下线又上线），只有调用此接口后才会停止推流
 *         2、若返回错误码为 IOT_ERR_NOLOGIN，表示当前与服务端连接已断开，消息发送失败，则需等待后续连接成功后再次调用此接口
 */
IOT_API int STDCALL VIOT_StopPushStream(IN const char * chan_id,
                                        IN const char * session_id,
                                        IN const char * ext_info);


/**
 * 录像小视频转存到其他存储系统
 *
 * @param  chan_id: 通道标识号
 * @param  record_type: 录像类型：0-未知（服务端会智能查找录像存储类型），1-内存缓存，2-磁盘存储，3-国标平台存储
 * @param  server_type: 存储系统：1-ObjectStorage（默认值），2-GSP
 * @param  server_addr: 存储服务器地址URL串（含bucket名称）
 * @param  start_time: 起始时间(UTC)，单位：毫秒
 * @param  end_time: 结束时间(UTC)，单位：毫秒
 * @param  sync_flag: 同步标志：0-非阻塞方式（适合国标平台存储类型），1或其他非0值-阻塞方式（适合内存和磁盘的录像类型）
 * @param  file_url: 返回的小视频文件在存储系统上的URL地址或会话标识串，此缓冲区需要由调用者根据实际情况分配，大小建议在512个字节以上
 * @param  resource_id: 返回的小视频文件资源标识号，目前存储到ObjectStorage时此值有效（洞鉴、灵探可能用到），大小建议在512个字节以上
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、使用阻塞方式时，直到收到服务端响应消息后接口才会返回，由于向服务器上推送大文件可能比较费时间，故接口返回可能较慢
 *         2、使用非阻塞方式时，成功返回后file_url保存的内容为会话标识串，URL地址需等服务端存储完毕后通过消息方式回调通知，并通过此会话串进行对应
 *         3、由于录像开关接口单独放入《视频存储组件数据协议》中，目前此接口只支持国标平台存储的转存
 *         4、由调用者分配file_url和resource_id的内存缓冲区，且要确保大小足够，否则可能会导致崩溃问题
 */
IOT_API int STDCALL VIOT_SaveRecordTo(IN const char *   chan_id,
                                      IN int            record_type,
                                      IN int            server_type,
                                      IN const char *   server_addr,
                                      IN int64_t        start_time,
                                      IN int64_t        end_time,
                                      IN int            sync_flag,
                                      OUT char *        file_url,
                                      OUT char *        resource_id,
                                      IN const char *   ext_info);

/**
 * 获取关键帧
 *
 * @param  chan_id: 通道标识号
 * @param  video_info: 获取到的关键帧对应的参数信息，由调用者分配后传入；可为NULL，此时内部不会给此参数赋值
 * @param  buf: 数据缓冲区，由调用者分配后传入，并确保大小足够
 * @param  len: 数据长度，初始由调用者传入分配的缓冲区大小，当成功获取到关键帧后，会将此值置为实际帧长度后传出
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此为阻塞接口，获取成功与否可通过返回值得知
 *         2、传入的缓冲区大小建议为2M，当视频分辨率大于等于4K时，建议采用更大值，例如8M
 *         3、内部实现方式相当于开一个实时流，直到收到第一个关键帧后返回，并自动关闭实时流
 *         4、若内部开流成功，但一直收不到流数据或关键帧，默认15秒后超时退出
 */
IOT_API int STDCALL VIOT_GetKeyFrame(IN const char *         chan_id,
                                     OUT IotVideoFrameInfo * video_info,
                                     OUT uint8_t *           buf,
                                     INOUT int *             len);


/**
 * API远程调用透传接口
 *
 * @param  dev_id: 设备标识号
 * @param  req_info: 透传的json信息串内容，格式样例如下：
 * 1、获取警戒配置参数接口 MegSDK_GetUnipueAlertConfig （此接口并未完全实现，当前以警戒类型列表获取为例进行说明）
    {
        "name": "MegSDK_GetUnipueAlertConfig",  // 接口名称
        "params": {                             // 参数列表
            "loginid": 0,       // 登录ID（外部无需感知，传0即可）
            "chanNo": 0,        // 通道号
            "cmdId": 0,         // 控制ID，参见 MEG_UNIQUE_ALERT_GET_E
            "pCmdBuf": {        // 传入结构体（不同的CmdId对应不同的结构体，需对应转换成相应json字段，当只做为输出字段时，可以为空）
            },
            "CmdBufLen": 0      // 传入结构体长度（外部无需感知，传0即可）
        }
    }

 * @param  rsp_info: 返回的json信息串内容，该字符串缓冲区需由调用者分配。格式样例如下：
 * 1、获取警戒配置参数接口 MegSDK_GetUnipueAlertConfig （此接口并未完全实现，当前以警戒类型列表获取为例进行说明）
    {
        "params": {       // 回复内容
            "pCmdBuf": {  // cmdId为0时，对应结构体为 MegUniqueAlertList
                "perimeterIn": 1,   // 周界警戒入侵, 0表示不支持,1表示支持
                "perimeterOut": 1,  // 周界警戒离开, 0表示不支持,1表示支持
                "tripwire": 0       // 绊线警戒，0表示不支持,1表示支持
            }
        }
        "return": 0       // 调用接口返回值
    }

 * @param  rsp_len: 输入时为调用者分配的串长（建议不小于16K），接口返回成功时输出实际串长，失败时此值一般保持不变（若错误码为分配缓冲区长度过短，则此值会保存实际长度）
 * @param  ext_info: 扩展信息，一般为json字符串，可传NULL或空字符串
 *
 * @return 成功返回0，失败返回相应错误码，参见 @ref IotErrorType
 * @note   1、此接口一般用于业务直接调用当前IoT系统未封装的设备sdk的接口的情况，这些接口一般指的是贵司ODM厂商的SDK接口
 *         2、此接口要实现的能力是在不更新sdk的情况下，只通过在当前说明中更新接口描述及在proxy中实现对应功能就能完成到这些接口的调用，达到远程调用的效果
 *         3、此次版本选取了一个较复杂的接口，以获取警戒配置参数接口中的获取警戒列表为例进行功能描述并完成实现，说明了此接口的可用性。后续其他功能根据协商来更改proxy进行实现
 *         4、通过接口参数及相关描述可以看出，目前适用于同步方式的接口，对于异步方式的接口由于涉及到多次异步消息通知，暂不方便支持
 */
IOT_API int STDCALL VIOT_PenetrateCallApi(IN const char * dev_id,
                                          IN const char * req_info,
                                          OUT char *      rsp_info,
                                          INOUT int *     rsp_len,
                                          IN const char * ext_info);


/** @} */


#ifdef __cplusplus
}
#endif
#endif
