//
//  AliPlayerWrapper.swift
//  AliPlayerSwiftDemo
//
//  Created by admin on 2024/3/21.
//

import SwiftUI
import AliyunPlayer

struct AliPlayerWrapper: UIViewRepresentable {
    @Binding var aliPlayer: AliPlayer // AliPlayer 对象
    @Binding var isPlaying: Bool
    var videoUrl: String
    
    @Binding var isPipPaused:Bool
    // 监听播放器当前的播放状态，通过监听播放事件状态变更newStatus回调设置
    private var currentPlayerStatus:AVPStatus?
    // 设置画中画控制器，在画中画即将启动的回调方法中设置，并需要在页面准备销毁时主动将其设置为nil，建议设置
    private weak var pipController:AVPictureInPictureController?
    // 监听播放器当前播放进度，currentPosition设置为监听视频当前播放位置回调中的position参数值
    private var currentPosition:Int64 = 0
    
    init(aliPlayer: Binding<AliPlayer>, videoUrl: String, isPlaying: Binding<Bool> , isPipPaused: Binding<Bool>) {
        _aliPlayer = aliPlayer
        _isPlaying = isPlaying
        self.videoUrl = videoUrl
        _isPipPaused = isPipPaused
        self.currentPlayerStatus = isPlaying.wrappedValue ? AVPStatusStarted : AVPStatusPrepared
        self.currentPosition = 0
    }
    
    func makeUIView(context: Context) -> UIView {
        aliPlayer.playerView = UIView() // 设置 AliPlayer 的 playerView
        aliPlayer.setUrlSource(AVPUrlSource().url(with: videoUrl))
        aliPlayer.isAutoPlay = true
        aliPlayer.prepare()
        aliPlayer.delegate = context.coordinator
        aliPlayer.setPictureinPictureDelegate(context.coordinator)
        
        return aliPlayer.playerView //直接返回这个视图就可以
    }
    
    func updateUIView(_ uiView: UIView, context: Context) {
        // 更新视图，如果需要的话
    }
    
    func makeCoordinator() -> Coordinator {
        Coordinator(self)
    }
    
    class Coordinator:NSObject,AVPDelegate,AliPlayerPictureInPictureDelegate {
        var parent: AliPlayerWrapper
        init(_ parent: AliPlayerWrapper) {
            self.parent = parent
        }
        
        //监听播放事件状态变更回调接口时，主动调用下述方法更新画中画控制器相关状态。
        func onPlayerStatusChanged(_ player: AliPlayer!,oldStatus: AVPStatus,newStatus: AVPStatus){
            if (newStatus == AVPStatusStarted) {
                self.parent.isPlaying = true
            } else {
                self.parent.isPlaying = false
            }
        }
        
        // 监听画中画即将启动回调
        func pictureInPictureControllerWillStartPicture(inPicture pictureInPictureController: AVPictureInPictureController?) {
            //MyLogger.debug("画中画即将启动回调")
            if (self.parent.pipController == nil) {
                self.parent.pipController = pictureInPictureController;
            }
            self.parent.isPipPaused = !self.parent.isPlaying;
            //MyLogger.debug("画中画即将启动回调,self.parent.isPipPaused:\(self.parent.isPipPaused)")
            if let pip = pictureInPictureController {
                pip.invalidatePlaybackState();
            }
        }
        
        // 监听画中画准备停止回调
        func pictureInPictureControllerWillStopPicture(inPicture pictureInPictureController: AVPictureInPictureController?) {
            self.parent.isPipPaused = false;
            if let pip = pictureInPictureController {
                pip.invalidatePlaybackState();
            }
        }
        
        // 监听画中画停止前告诉代理恢复用户回调
        func picture(_ pictureInPictureController: AVPictureInPictureController?, restoreUserInterfaceForPictureInPictureStopWithCompletionHandler completionHandler: ((Bool) -> Void)? = nil) {
            //MyLogger.debug("画中画停止前告诉代理恢复用户回调")
            if self.parent.pipController != nil {
                self.parent.pipController = nil
            }
            if let completionHandler = completionHandler {
                completionHandler(true)
            }
        }
        
        // 监听设置画中画当前可播放视频的时间范围回调
        func pictureInPictureControllerTimeRange(forPlayback pictureInPictureController: AVPictureInPictureController, layerTime: CMTime) -> CMTimeRange {
            let currentSeconds = CMTimeGetSeconds(layerTime)
                
            var start: Double
            var end: Double
                
            if self.parent.currentPosition <= self.parent.aliPlayer.duration {
                let curPosition = Double(self.parent.currentPosition) / 1000.0
                let duration = Double(self.parent.aliPlayer.duration) / 1000.0
                let interval = duration - curPosition
                start = currentSeconds - curPosition
                end = currentSeconds + interval
                let t1 = CMTimeMakeWithSeconds(start, preferredTimescale: layerTime.timescale)
                let t2 = CMTimeMakeWithSeconds(end, preferredTimescale: layerTime.timescale)
                return CMTimeRangeFromTimeToTime(start: t1, end: t2)
            } else {
                return CMTimeRangeMake(start: CMTime.negativeInfinity, duration: CMTime.positiveInfinity)
            }
        }
        
        // 监听设置画中画是否为暂停或播放状态回调
        func picture(inPictureControllerIsPlaybackPaused pictureInPictureController: AVPictureInPictureController) -> Bool {
            return self.parent.isPipPaused
        }
        
        // 监听画中画点击快进或快退按钮回调，同步播放器状态
        func picture(_ pictureInPictureController: AVPictureInPictureController, skipByInterval skipInterval: CMTime, completionHandler: @escaping () -> Void) {
            //MyLogger.debug("画中画前进后退回调")
            let skipTime = skipInterval.value / Int64(skipInterval.timescale)
            var skipPosition = self.parent.currentPosition + skipTime * 1000
            if skipPosition < 0 {
                skipPosition = 0
            } else if skipPosition > self.parent.aliPlayer.duration {
                skipPosition = self.parent.aliPlayer.duration
            }
            self.parent.aliPlayer.seek(toTime: skipPosition, seekMode: AVP_SEEKMODE_ACCURATE)
            pictureInPictureController.invalidatePlaybackState()
        }
        
        // 监听画中画点击暂停或播放按钮回调，需要执行的操作
        func picture(_ pictureInPictureController: AVPictureInPictureController, setPlaying playing: Bool) {
            //MyLogger.debug("画中画按钮点击回调,视频状态:\(playing)")
            if !playing {
                self.parent.aliPlayer.pause()
                self.parent.isPipPaused = true
            } else {
                // 如果画中画播放完成，需要重新播放
                if self.parent.currentPlayerStatus == AVPStatusCompletion {
                    self.parent.aliPlayer.seek(toTime: 0, seekMode: AVP_SEEKMODE_ACCURATE)
                }

                self.parent.aliPlayer.start()
                self.parent.isPipPaused = false
            }
            pictureInPictureController.invalidatePlaybackState()
        }
        
        func pictureInPictureControllerDidStartPicture(inPicture pictureInPictureController: AVPictureInPictureController?) {
            if let pip = pictureInPictureController {
                pip.invalidatePlaybackState();
            }
        }
        
        func pictureInPictureControllerDidStopPicture(inPicture pictureInPictureController: AVPictureInPictureController?) {
            //MyLogger.debug("画中画已经停止")
            if let pip = pictureInPictureController {
                pip.invalidatePlaybackState();
            }
            self.parent.isPipPaused = true
        }
        
        func picture(_ pictureInPictureController: AVPictureInPictureController?, failedToStartPictureInPictureWithError error: Error?) {
            //MyLogger.error("画中画启动失败")
        }
        
        func onPlayerEvent(_ player: AliPlayer!, eventType: AVPEventType) {
            
            switch eventType {
            case AVPEventPrepareDone:
                //MyLogger.debug("AVPEventPrepareDone")
                player.setPictureInPictureEnable(true) // 开启画中画
            case AVPEventCompletion:
                //print("AVPEventCompletion")
                if self.parent.pipController != nil {
                    self.parent.isPipPaused = true
                    self.parent.pipController?.invalidatePlaybackState()
                }
            case AVPEventSeekEnd:
                //MyLogger.debug("AVPEventSeekEnd")
                if self.parent.pipController != nil {
                    self.parent.isPipPaused = true
                    self.parent.pipController?.invalidatePlaybackState()
                }
            default:
                break
            }
            //print(eventType)
        }
        
        func onCurrentPositionUpdate(_ player: AliPlayer!, position: Int64) {
            self.parent.currentPosition = position
            //print("\(position)")
        }
        
    }
    
}
