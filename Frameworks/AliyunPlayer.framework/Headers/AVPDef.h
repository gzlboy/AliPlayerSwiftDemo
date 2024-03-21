//
//  AVPDef.h
//  AVPSDK
//
//  Created by shiping.csp on 2018/11/16.
//  Copyright © 2018 com.alibaba.AliyunPlayer. All rights reserved.
//

#ifndef AVPDef_h
#define AVPDef_h

#import <Foundation/Foundation.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#define AVPView NSView
#define AVPImage NSImage
#elif TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#define AVPView UIView
#define AVPImage UIImage
#endif // TARGET_OS_OSX

#import "AVPErrorCode.h"

/**
 * Convert playback URL before playback.
 *
 * For vid playback, try to convert the playback URL before playback
 *
 * @param   srcURL  [in]  input URL.
 * @param   srcFormat [in]  input format. should be "m3u8" "mp4", or "" if unknown.
 * @param   destURL [out] output URL, convertURL function will malloc the memory, and user of PlayURLConverCallback need free it outside.
 *
 * @return  true if success.
 */
typedef bool (*PlayURLConverCallback)(const char* srcURL, const char* srcFormat, char** destURL);


typedef enum AVPStatus: NSUInteger {
    /** @brief 空转，闲时，静态 */
    /**** @brief Idle */
    AVPStatusIdle = 0,
    /** @brief 初始化完成 */
    /**** @brief Initialized */
    AVPStatusInitialzed,
    /** @brief 准备完成 */
    /**** @brief Prepared */
    AVPStatusPrepared,
    /** @brief 正在播放 */
    /**** @brief Playing */
    AVPStatusStarted,
    /** @brief 播放暂停 */
    /**** @brief Paused */
    AVPStatusPaused,
    /** @brief 播放停止 */
    /**** @brief Stopped */
    AVPStatusStopped,
    /** @brief 播放完成 */
    /**** @brief Completed */
    AVPStatusCompletion,
    /** @brief 播放错误 */
    /**** @brief Error */
    AVPStatusError
} AVPStatus;

 /**@brief 跳转模式，是否为精准跳转*/
 /****@brief Seeking mode: accurate seeking or inaccurate seeking.*/
typedef enum AVPSeekMode: NSUInteger {
    AVP_SEEKMODE_ACCURATE = 0x01,
    AVP_SEEKMODE_INACCURATE = 0x10,
} AVPSeekMode;

 /**@brief 渲染显示模式*/
 /****@brief Zoom mode*/
typedef enum AVPScalingMode: NSUInteger {
    /**@brief 不保持比例平铺*/
    /****@brief Auto stretch to fit.*/
    AVP_SCALINGMODE_SCALETOFILL,
    /**@brief 保持比例，黑边*/
    /****@brief Keep aspect ratio and add black borders.*/
    AVP_SCALINGMODE_SCALEASPECTFIT,
    /**@brief 保持比例填充，需裁剪*/
    /****@brief Keep aspect ratio and crop.*/
    AVP_SCALINGMODE_SCALEASPECTFILL,
} AVPScalingMode;

/**@brief 旋转模式*/
/****@brief Rotate mode*/
typedef enum AVPRotateMode: NSUInteger {
    AVP_ROTATE_0 = 0,
    AVP_ROTATE_90 = 90,
    AVP_ROTATE_180 = 180,
    AVP_ROTATE_270 = 270
} AVPRotateMode;

/**@brief 镜像模式*/
/****@brief Mirroring mode*/
typedef enum AVPMirrorMode: NSUInteger {
    AVP_MIRRORMODE_NONE,
    AVP_MIRRORMODE_HORIZONTAL,
    AVP_MIRRORMODE_VERTICAL,
} AVPMirrorMode;

/**@brief Alpha渲染模式*/
/****@brief Rendring mode*/
typedef enum AVPAlphaRenderMode: NSUInteger {
    AVP_RENDERMODE_ALPHA_NONE = 0,
    AVP_RENDERMODE_ALPHA_AT_RIGHT = 1,
    AVP_RENDERMODE_ALPHA_AT_LEFT = 2,
    AVP_RENDERMODE_ALPHA_AT_TOP = 3,
    AVP_RENDERMODE_ALPHA_AT_BOTTOM = 4,
} AVPAlphaRenderMode;

/**@brief 音频输出声道*/
/****@brief Output audio channel*/
typedef enum AVPOutputAudioChannel:NSUInteger {
    /**@brief 不指定声道，默认值*/
    /****@brief Not specified, default value*/
    AVP_AUDIO_CHANNEL_NONE = 0,
    /**@brief 左声道*/
    /****@brief Left audio channel*/
    AVP_AUDIO_CHANNEL_LEFT = 1,
    /**@brief 右声道*/
    /****@brief Right audio channel*/
    AVP_AUDIO_CHANNEL_RIGHT = 2
} AVPOutputAudioChannel;

/**@brief 播放器事件类型*/
/****@brief Player event type*/
typedef enum AVPEventType: NSUInteger {
    /**@brief 准备完成事件*/
    /****@brief Preparation completion event*/
    AVPEventPrepareDone,
    /**@brief 自动启播事件*/
    /****@brief Autoplay start event*/
    AVPEventAutoPlayStart,
    /**@brief 首帧显示事件*/
    /****@brief First frame display event*/
    AVPEventFirstRenderedStart,
    /**@brief 播放完成事件*/
    /****@brief Playback completion event*/
    AVPEventCompletion,
    /**@brief 缓冲开始事件*/
    /****@brief Buffer start event*/
    AVPEventLoadingStart,
    /**@brief 缓冲完成事件*/
    /****@brief Buffer completion event*/
    AVPEventLoadingEnd,
    /**@brief 跳转完成事件*/
    /****@brief Seeking completion event*/
    AVPEventSeekEnd,
    /**@brief 循环播放开始事件*/
    /****@brief Loop playback start event*/
    AVPEventLoopingStart,
} AVPEventType;

/**@brief 获取信息播放器的key*/
/****@brief The key to get property*/
typedef enum AVPPropertyKey: NSUInteger {
    /**@brief Http的response信息
     * 返回的字符串是JSON数组，每个对象带response和type字段。type字段可以是url/video/audio/subtitle，根据流是否有相应Track返回。
     * 例如：[{"response":"response string","type":"url"},{"response":"","type":"video"}]
     */
    /****@brief Http response info
     * Return with JSON array，each object item include 'response'/'type' filed。'type' could be  url/video/audio/subtitle, depend on the stream whether have the tracks。
     * For example: [{"response":"response string","type":"url"},{"response":"","type":"video"}]
     */
    AVP_KEY_RESPONSE_INFO = 0,

    /**@brief 主URL的连接信息
     * 返回的字符串是JSON对象，带url/ip/eagleID/cdnVia/cdncip/cdnsip等字段（如果解析不到则不添加）
     * 例如：{"url":"http://xxx","openCost":23,"ip":"11.111.111.11","cdnVia":"xxx","cdncip":"22.222.222.22","cdnsip":"xxx"}
     */
    /****@brief Major URL connect information
     * Return with JSON object，include sub fileds such as url/ip/eagleID/cdnVia/cdncip/cdnsip.
     * For example: {"url":"http://xxx","openCost":23,"ip":"11.111.111.11","cdnVia":"xxx","cdncip":"22.222.222.22","cdnsip":"xxx"}
     */
    AVP_KEY_CONNECT_INFO  = 1,
} AVPPropertyKey;

/**@brief IP 解析类型*/
/**@brief IP resolve type*/
typedef enum AVPIpResolveType: NSUInteger {
    AVPIpResolveWhatEver,
    AVPIpResolveV4,
    AVPIpResolveV6,
} AVPIpResolveType;

typedef enum AVPOption : NSUInteger {
    /**
     * @brief 渲染的fps。类型为Float
     */
    /****
     * @brief render fps. Return value type is Float
     */
    AVP_OPTION_RENDER_FPS = 0,

    /**
     * 当前的网络下行码率。类型为Float
     */
    /****
     * current download bitrate. Return value type is Float
     */
    AVP_OPTION_DOWNLOAD_BITRATE = 1,

    /**
     * 当前播放的视频码率。类型为Float
     */
    /****
     * current playback video bitrate. Return value type is Float
     */
    AVP_OPTION_VIDEO_BITRATE = 2,

    /**
     * 当前播放的音频码率。类型为Float
     */
    /****
     * current playback audio bitrate. Return value type is Float
     */
    AVP_OPTION_AUDIO_BITRATE = 3,
} AVPOption;

/**
 * 策略类型
 */
/****
 * strategy type
 */
typedef enum AVPStrategyType : NSUInteger {
    /**
     * 动态预加载时长策略
     */
    /****
     * dynamic preload duration strategy.
     */
    AVP_STRATEGY_DYNAMIC_PRELOAD = 1,
} AVPStrategyType;

/**
 * 场景类型
 */
/****
 * scene type
 */
typedef enum AVPSceneType : NSInteger {
    /**
     * 场景：无
     */
    /****
     * scene none
     */
    AVP_SCENE_NONE = -1,
    /**
     * 超短视频场景：适用于30s以下
     */
    /****
     * very short scene: apply to less 30s
     */
    AVP_VERY_SHOR_VIDEO = 0,
    /**
     * 短视频场景：适用于30s-5min
     */
    /****
     * short scene: apply to 30-5min
     */
    AVP_SHORT_VIDEO = 1,
    /**
     * 中视频场景：适用于5min-30min
     */
    /****
     * middle scene: apply to 5min-30min
     */
    AVP_MIDDLE_VIDEO = 2,
    /**
     * 长视频场景：适用于30min以上
     */
    /****
     * long scene: apply to more than 30min
     */
    AVP_LONG_VIDEO = 3,
} AVPSceneType;


/**
 * 画中画显示模式
 */
/****
 * picture in picture show mode
 */
typedef enum AVPPIPShowMode : NSUInteger {
    /**
     * 默认模式：正常显示所有画中画按钮
     */
    /****
     * default mode: show all picture in picture button
     */
    AVP_SHOW_MODE_DEFAULT = 0,
    /**
     * 隐藏快进快退模式
     */
    /****
     * hide fast forward and fast rewind mode
     */
    AVP_SHOW_MODE_HIDE_FAST_FORWARD_REWIND = 1,
} AVPPIPShowMode;

/**
 @brief AVPErrorModel为播放错误信息描述
 */
/****
 @brief AVPErrorModel represents playback error descriptions.
 */
OBJC_EXPORT
@interface AVPErrorModel : NSObject

/**
 @brief code为播放错误信息code
 */
/****
 @brief code represents a playback error code.
 */
@property (nonatomic, assign) AVPErrorCode code;

/**
 @brief message为播放错误信息描述
 */
/****
 @brief message represents a playback error message.
 */
@property (nonatomic, copy) NSString *message;

/**
 @brief extra为播放错误信息描述的附加信息
 */
/****
 @brief extra represents an additional playback error message.
 */
@property (nonatomic, copy) NSString *extra;

/**
 @brief requestId为播放错误信息requestID
 */
/****
 @brief requestId represents the request ID of a playback error.
 */
@property (nonatomic, copy) NSString *requestId;

/**
 @brief videoId为播放错误发生的videoID
 */
/****
 @brief videoId represents the VID of the video that has a playback error.
 */
@property (nonatomic, copy) NSString *videoId;

@end


/**
 @brief AVPTimeShiftModel直播时移描述
 */
/****
 @brief AVPTimeShiftModel represents broadcasting timeshift descriptions.
 */
OBJC_EXPORT
@interface AVPTimeShiftModel : NSObject

/**
 @brief startTime直播时移开始时间
 */
/****
 @brief startTime represents the start of the time range for broadcasting timeshift.
 */
@property (nonatomic, assign) NSTimeInterval startTime;

/**
 @brief endTime直播时移结束时间
 */
/****
 @brief endTime represents the end of the time range for broadcasting timeshift.
 */
@property (nonatomic, assign) NSTimeInterval endTime;

/**
 @brief currentTime直播时移当前时间
 */
/****
 @brief currentTime represents the time that broadcasting timeshift seeks to.
 */
@property (nonatomic, assign) NSTimeInterval currentTime;
@end

/**
 @brief logLevel
 */
typedef enum AVPLogLevel: NSUInteger {
    LOG_LEVEL_NONE    = 0,
    LOG_LEVEL_FATAL   = 8,
    LOG_LEVEL_ERROR   = 16,
    LOG_LEVEL_WARNING = 24,
    LOG_LEVEL_INFO    = 32,
    LOG_LEVEL_DEBUG   = 48,
    LOG_LEVEL_TRACE   = 56,
} AVPLogLevel;

typedef enum _AVPStsStatus {
  Valid,
  Invalid,
  Pending } AVPStsStatus;

typedef struct _AVPStsInfo {
    NSString *accId;
    NSString *accSecret;
    NSString *token;
    NSString *region;
    NSString *formats;
} AVPStsInfo;

/**
 @brief 是否支持的功能的类型
 */
/****
 @brief The type of the feature.
*/
typedef enum _SupportFeatureType : NSUInteger {
    /**
     * 硬件是否支持杜比音频
    */
    /****
     * whether the device support Dolby Audio.
    */
    FeatureDolbyAudio
} SupportFeatureType;

/**
 @brief GlobalSettings的特定功能选项
 */
/****
 @brief specified option on GlobalSettings
*/
typedef enum GlobalOption: NSUInteger {
    SET_PRE_CONNECT = 0,
    SET_DNS_PRIORITY_LOCAL_FIRST = 1,
    SET_EXTRA_DATA = 3,
} GlobalOption;

/**
 @brief AliPlayer的特定功能选项
 */
/****
 @brief specified option on AliPlayer
*/
typedef enum PlayerOption: NSUInteger {
    SET_MEDIA_TYPE = 0,
} PlayerOption;


#endif /* AVPDef_h */
