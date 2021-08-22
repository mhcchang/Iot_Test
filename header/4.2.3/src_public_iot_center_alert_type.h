/*******************************************************************************
 * @file        iot_center_alert_types.h
 * @brief       Alert type definition file of IoT Center Client SDK
 *
 * @authors     wubo, flowstar
 * @copyright   All rights reserved
 *
 * Modification History:
 * -----------------------------------------------------------------------------
 * Date        Author        Description
 * -----------------------------------------------------------------------------
 * 2020-04-03  wubo          Create the file
 *
 ******************************************************************************/
#ifndef _INCLUDE_IOT_CENTER_ALERT_TYPES__H_
#define _INCLUDE_IOT_CENTER_ALERT_TYPES__H_
#pragma once

#include "iot_center_types.h"
#include "iot_center_sdk.h"


//=============================================================================
// = 类型定义及宏定义

#define IOT_MAX_ALERT_DRAW_AREA_NUM     1   ///< 最大警戒划线区域数
#define IOT_MAX_ALERT_SUPPORT_NAME_NUM  5   ///< 最大警戒支持名称数
#define IOT_MAX_CHAN_NUM                32  ///< 最大通道数
#define IOT_MAX_ALARM_LINK_NUM          12  ///< 最大警戒报警联动数
#define IOT_AT_NUM                      32  ///< 警戒事件类型数
#define IOT_MAX_POLYGON_POINT_NUM       16  ///< 多边形最大顶点数


//=============================================================================
// = 枚举定义

/// 警戒配置类型
typedef enum IotAlertConfigType
{
    IOT_ACT_LIST                = 0,    ///< 支持的警戒类型列表(Get)，对应结构体参见 @ref IotAlertList
    IOT_ACT_TEMPLAE_LIST        = 1,    ///< 支持的警戒预案列表(Get)，对应结构体参见 @ref IotAlertTemplate
    IOT_ACT_CFGCHN              = 2,    ///< 通道使能(Get/Set)，对应结构体参见 @ref IotAlertCfgChn
    IOT_ACT_EVENT               = 3,    ///< 警戒事件(Get/Set)，对应结构体参见 @ref IotAlertEvent
    IOT_ACT_SCENE_TIMESEG       = 4,    ///< 警戒场景巡航信息(Get/Set)，对应结构体参见 @ref IotAlertSceneTimeSeg
    IOT_ACT_DRAW_LINE           = 5,    ///< 警戒场景画线信息(Get/Set)，对应结构体参见 @ref IotAlertDrawLine
    IOT_ACT_LINK_MODE           = 6,    ///< 警戒场景内算法联动模式(Get/Set)，对应结构体参见 @ref IotAlertLinkMode
    IOT_ACT_WHITE_LIGHT_MODE    = 7,    ///< 警戒算法支持的白光灯联动分级数(Get)，对应结构体参见 @ref IotAlertWhiteLightMode
    IOT_ACT_WHITE_LIGHT_PARA    = 8,    ///< 警戒算法支持的白光灯联动分级信息(Get)，对应结构体参见 @ref IotAlertWhiteLightParam
    IOT_ACT_PERIMETER           = 9,    ///< 周界警戒算法参数(Get/Set)，对应结构体参见 @ref IotAlertPerimeter
    IOT_ACT_TRIPWIRE            = 10,   ///< 绊线警戒算法参数(Get/Set)，对应结构体参见 @ref IotAlertTripwire
    IOT_ACT_ALARM_LINK          = 11,   ///< 警戒报警联动参数(Get/Set)，对应结构体参见 @ref IotAlertAlarmLink
    IOT_ACT_ALARM_SCHEDULE      = 12,   ///< 警戒报警布防模板(Get/Set)，对应结构体参见 @ref IotAlertAlarmSchedule
    IOT_ACT_ALARM_MESSAGE       = 13,   ///< 警戒报警信息（暂不支持）
    IOT_ACT_CFG_ADV             = 17,   ///< 智能分析高级参数(Get/Set)，对应结构体参见 @ref IotVCAAdvanceParam
    IOT_ACT_SCENE_REV           = 18,   ///< 警戒场景恢复时间（暂不支持）
    IOT_ACT_ALARM_STAT_CLR      = 19,   ///< 新警戒报警计数统计清零(Set)，对应结构体参见 @ref IotAlertAlarmState
} IotAlertConfigType;


//=============================================================================
// = 结构体定义

/// VCA坐标点信息
typedef struct IotVCAPoint
{
    int x;                      ///< 坐标X
    int y;                      ///< 坐标Y
} IotVCAPoint;

/// VCA线段信息
typedef struct IotVCALine
{
    IotVCAPoint start_point;    ///< 起点
    IotVCAPoint end_point;      ///< 终点
} IotVCALine;

/// VCA显示参数
typedef struct IotVCADisplayParam
{
    uint8_t display_rule;       ///< 是否显示规则,比如绊线,周界线,0--不显示;1--显示
    uint8_t display_stat;       ///< 是否显示报警计数,0--不显示;1--显示
    uint8_t color;              ///< 正常时的颜色,1--红色;2--绿色;3--黄色;4--蓝色;5--紫色;6--青色;7--黑色;8--白色
    uint8_t alarm_color;        ///< 报警时的颜色,1--红色;2--绿色;3--黄色;4--蓝色;5--紫色;6--青色;7--黑色;8--白色
    uint8_t res[12];            ///< 预留字段
} IotVCADisplayParam;

/// VCA区域多边形
typedef struct IotVCAPolygon
{
    int point_num;                                  ///< 顶点个数
    IotVCAPoint points[IOT_MAX_POLYGON_POINT_NUM];  ///< 顶点数组
} IotVCAPolygon;

/// 警戒列表类型
typedef struct IotAlertList
{
    uint8_t perimeter_in;   ///< [OUT]周界警戒入侵, 0表示不支持,1表示支持
    uint8_t perimeter_out;  ///< [OUT]周界警戒离开, 0表示不支持,1表示支持
    uint8_t tripwire;       ///< [OUT]绊线警戒, 0表示不支持,1表示支持
    uint8_t res[13];        ///< 预留字段
} IotAlertList;

/// 警戒模板预案
typedef struct IotAlertTemplate
{
    uint8_t scene_id;       ///< [IN]警戒场景编号，范围[0~3]
    uint8_t alert_type;     ///< [IN]警戒算法类型：0-周界警戒；1-绊线警戒
    uint8_t res[14];        ///< 预留字段
    /// [OUT]支持的警戒预案列表：1:抓拍并联动白光;2:抓拍并联动白光、单次警音;3:抓拍并联动激光、白光、循环警音;
    /// 4:抓拍并联动炸裂式多级声光;5:抓拍并联动渐变式多级声光;6:抓拍并联动白光频闪、循环警音
    int supprot_names[IOT_MAX_ALERT_SUPPORT_NAME_NUM];
} IotAlertTemplate;

/// 警戒通道启用配置
typedef struct IotAlertCfgChn
{
    uint8_t enable;         ///< [OUT]警戒启用状态：0-此通道不启用；1-此通道启用
    uint8_t en_chn_type;    ///< [IN]分析类型：0-本地通道；1-前端通道
    uint8_t res[14];        ///< 预留字段
} IotAlertCfgChn;

/// 警戒事件
typedef struct IotAlertEvent
{
    uint8_t scene_id;                   ///< [IN]警戒场景编号，范围[0~3]
    uint8_t res[15];                    ///< 预留字段
    uint8_t type_enable[IOT_AT_NUM];    ///< [OUT]警戒算法启用状态：数组元素(0-周界警戒;1-绊线警戒);使能状态(0-不使能;1-使能)
} IotAlertEvent;

/// 警戒场景巡航信息
typedef struct IotAlertSceneTimeSeg
{
    uint8_t scene_id;       ///< [IN]警戒场景编号，范围[0~3]
    uint8_t enable;         ///< [OUT]时间巡航使能：0-不使能；1-使能
    uint8_t start_hour;     ///< [OUT]巡航开始的时间-小时：范围[0~23]
    uint8_t start_minute;   ///< [OUT]巡航开始的时间-分钟：范围[0~59]
    uint8_t stop_hour;      ///< [OUT]巡航结束的时间-小时：范围[0~23]
    uint8_t stop_minute;    ///< [OUT]巡航结束的时间-分钟：范围[0~59]
    uint8_t res[10];        ///< 预留字段
} IotAlertSceneTimeSeg;

/// 警戒场景区域信息
typedef struct IotAlertDrawLine
{
    uint8_t scene_id;       ///< [IN]警戒场景编号,范围[0~3]
    uint8_t alert_type;     ///< [IN]警戒算法类型:0-周界警戒;1-绊线警戒
    uint8_t event_no;       ///< [IN]事件编号，默认0
    uint8_t area_num;       ///< [OUT]区域个数:范围[0~1]
    IotVCAPolygon area_info[IOT_MAX_ALERT_DRAW_AREA_NUM];   ///< [OUT]区域信息
    uint8_t res[16];        ///< 预留字段
} IotAlertDrawLine;

/// 警戒联动
typedef struct IotAlertLinkMode
{
    uint8_t scene_id;       ///< [IN]警戒场景编号，范围[0~3]
    uint8_t alert_type;     ///< [IN]警戒算法类型：0-周界警戒；1-绊线警戒
    uint8_t event_no;       ///< [IN]事件编号，默认0
    uint8_t link_mode;      ///< [OUT]联动模式:0-使用自定义报警参数;[1-6]表示警戒预案1~6,详情参考IotAlertTemplate中的预案信息定义。
    uint8_t res[12];        ///< 预留字段
} IotAlertLinkMode;

/// 警戒算法支持的白光灯联动分级数
typedef struct IotAlertWhiteLightMode
{
    uint8_t perimeter_support_grade;    ///< [OUT]周界支持的联动分级数:范围[1~3]
    uint8_t tripwire_support_grade;     ///< [OUT]绊线支持的联动分级数:范围[1~3]
    uint8_t res[14];                    ///< 预留字段
} IotAlertWhiteLightMode;

/// 警戒算法支持的白光灯联动分级信息
typedef struct IotAlertWhiteLightParam
{
    int delay_time;         ///< [OUT]白光灯常亮支持的最大延时熄灭时间:0-不支持;1~999支持的最大延时熄灭时间,单位秒
    uint8_t alert_type;     ///< [IN]警戒算法类型:0-周界警戒;1-绊线警戒
    uint8_t grade;          ///< [IN]联动级别:范围[1~3]
    uint8_t default_mode;   ///< [OUT]是否支持闪光默认模式:0-不支持;1-支持
    uint8_t flash_num;      ///< [OUT]支持的最大闪光次数:0-不支持;1~10支持的最大闪光次数
    uint8_t ficker;         ///< [OUT]是否支持频闪:0-不支持;1-支持
    uint8_t always;         ///< [OUT]是否支持白光灯常亮:0-不支持;1-支持
    uint8_t res[10];        ///< 预留字段
} IotAlertWhiteLightParam;

/// 警戒周界参数
typedef struct IotAlertPerimeter
{
    uint8_t scene_id;               ///< [IN]警戒场景编号,范围[0~3]
    uint8_t event_no;               ///< [IN]事件编号,默认0
    uint8_t sensitivity;            ///< [OUT]灵敏度:范围[0~100]
    uint8_t valid;                  ///< [OUT]事件检测是否有效:0-无效;1-有效
    uint8_t display_target;         ///< [OUT]目标框是否显示:0-不显示;1-显示
    uint8_t target_type_check;      ///< [OUT]目标类型:0-不区分;1-人;2-车;3-人和车
    uint8_t check_mode;             ///< [OUT]检测模式:0-不检测；1-入侵；2-离开；3-入侵+离开
    uint8_t res1;                   ///< 预留字段1
    IotVCADisplayParam display_info;///< [OUT]视频智能分析显示参数
    int min_distance;               ///< [OUT]最小距离
    int min_time;                   ///< [OUT]最短时间
    int direction_angle;            ///< [OUT]禁止方向角度
    int resort_time;                ///< [OUT]滞留时间:单位毫秒,默认0
    int track_time;                 ///< [OUT]跟踪时间:单位秒,默认300
    uint8_t direction_check;        ///< [OUT]方向限制:0-不限制;1-限制
    uint8_t min_size;               ///< [OUT]最小尺寸:范围[0~100],默认5
    uint8_t max_size;               ///< [OUT]最小尺寸:范围[0~100],默认30
    uint8_t res[17];                ///< 预留字段
} IotAlertPerimeter;

/// 警戒绊线参数
typedef struct IotAlertTripwire
{
    uint8_t scene_id;               ///< [IN]警戒场景编号，范围[0~3]
    uint8_t event_no;               ///< [IN]事件编号,默认0
    uint8_t sensitivity;            ///< [OUT]灵敏度:范围[0~100]
    uint8_t valid;                  ///< [OUT]事件检测是否有效:0-无效;1-有效
    uint8_t display_target;         ///< [OUT]目标框是否显示:0-不显示;1-显示
    uint8_t target_type_check;      ///< [OUT]目标类型:0-不区分;1-人;2-车;3-人和车
    uint8_t res1[2];                ///< 预留字段1
    IotVCADisplayParam display_info;///< [OUT]视频智能分析显示参数
    int min_distance;               ///< [OUT]最小距离
    int min_time;                   ///< [OUT]最短时间
    int tripwire_type;              ///< [OUT]穿越类型:0-单向;1-双向(默认双向)
    int tripwire_direction;         ///< [OUT]禁止穿越方向:范围[0~359]
    int track_time;                 ///< [OUT]跟踪时间:单位秒(默认300)
    uint8_t res[16];                ///< 预留字段
} IotAlertTripwire;

/// 联动声音参数
typedef struct IotLinkSoundParam
{
    int enable;                     ///< 是否启动
    int serial_no;                  ///< 声音序号
    uint8_t res[8];                 ///< 预留字段
} IotLinkSoundParam;

/// 联动输出参数
typedef struct IotLinkOutPortParam
{
    int num;                        ///< 有效通道个数
    int channels[IOT_MAX_CHAN_NUM]; ///< 输出通道集合，值代表具体通道号，从0开始
} IotLinkOutPortParam;

/// 联动录像参数
typedef struct IotLinkRecordParam
{
    int num;                        ///< 有效通道个数
    int channels[IOT_MAX_CHAN_NUM]; ///< 录像通道集合，值代表具体通道号，从0开始
} IotLinkRecordParam;

/// 联动抓拍参数
typedef struct IotLinkSnapParam
{
    int num;                        ///< 有效通道个数
    int channels[IOT_MAX_CHAN_NUM]; ///< 输出通道集合，值代表具体通道号，从0开始
} IotLinkSnapParam;

/// 联动电子邮件参数
typedef struct IotLinkEmailParam
{
    int enable;                     ///< 使能
    int attachment;                 ///< 附件（暂不支持）
} IotLinkEmailParam;

/// 联动白光参数
typedef struct IotLinkFlashingWhite
{
    int enable;                     ///< 使能：范围[0~2]
    int extern_info;                ///< 联动白光附加信息：1-闪一次，2-闪两次，3-闪三次，255-一直闪（对应上面的enable值为1时）；5-常亮（此时上面的enable值为2）
} IotLinkFlashingWhite;

/// 联动参数
typedef struct IotLinkParam 
{
    uint8_t alert_type;                     ///< [IN]警戒算法类型:0-周界警戒;1-绊线警戒
    uint8_t event_no;                       ///< [IN]事件编号,默认0
    uint8_t link_level;                     ///< [IN]联动级别:范围[0~2]
    uint8_t next_level;                     ///< [OUT]是否联动下一级警戒:0-不联动;1-联动
    uint8_t res[8];                         ///< 预留参数
    int retention_time;                     ///< [OUT]当前级别报警持续时间:单位毫秒
    int link_type;                          ///< [IN]联动类型:0-联动警戒音;2-联动端口输出;3-联动录像;5-联动抓拍;7-Email;10-联动白光闪烁
    union {
        IotLinkSoundParam sound;            ///< [OUT]声音
        IotLinkOutPortParam out_port;       ///< [OUT]联动输出
        IotLinkRecordParam record;          ///< [OUT]联动录像
        IotLinkSnapParam snap;              ///< [OUT]联动抓拍
        IotLinkEmailParam email;            ///< [OUT]EMail
        IotLinkFlashingWhite flashing_white;///< [OUT]白光
    };
} IotLinkParam;

/// 警戒报警联动参数
typedef struct IotAlertAlarmLink
{
    uint8_t scene_id;                       ///< [IN]警戒场景编号,范围[0~3]
    uint8_t link_count;                     ///< [IN/OUT]联动类型的数量
    uint8_t res[14];                        ///< 预留参数
    IotLinkParam link_param[IOT_MAX_ALARM_LINK_NUM];///< 联动类型参数
} IotAlertAlarmLink;

/// 警戒星期配置参数
typedef struct IotAlertAlarmSchedule
{
    uint8_t scene_id;           ///< [IN]警戒场景编号,范围[0~3]
    uint8_t chan_type;          ///< [IN]分析类型:0-本地通道;1-前端通道
    uint8_t alert_type;         ///< [IN]警戒算法类型:0-周界警戒;1-绊线警戒
    uint8_t event_no;           ///< [IN]事件编号,默认0
    uint8_t week_enable[7];     ///< [OUT]星期是否启用布防：下标表示(0-星期日;1-星期一;2-星期二;3-星期三;4-星期四;5-星期五;6-星期六);值表示使能状态(0-不使能;1-使能)
    uint8_t res[121];           ///< 预留参数
} IotAlertAlarmSchedule;

/// 视频智能分析高级参数
typedef struct IotVCAAdvanceParam
{
    uint8_t scene_id;           ///< [IN]场景号:最多支持16个场景,编号[0~15]
    uint8_t target_enable;      ///< [OUT]是否启用高级参数:0-不启用,1-启用
    uint8_t target_min_size;    ///< [OUT]目标最小像素数,范围[0~100]
    uint8_t target_max_size;    ///< [OUT]目标最大像素数,范围[0~100]
    uint8_t tar_check_sensitiv; ///< [OUT]目标检测灵敏度:范围[1~100],默认40
    uint8_t real_target_time;   ///< [OUT]目标确认帧数:范围[10~30],默认为16
    uint8_t res[10];            ///< 预留参数
} IotVCAAdvanceParam;

/// 警戒报警状态参数
typedef struct IotAlertAlarmState
{
    int state;                  ///< [IN]状态值
    uint8_t res[124];           ///< 预留参数
} IotAlertAlarmState;


#endif
