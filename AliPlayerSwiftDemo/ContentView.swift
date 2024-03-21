//
//  ContentView.swift
//  AliPlayerSwiftDemo
//
//  Created by admin on 2024/3/21.
//

import SwiftUI
import AliyunPlayer

struct ContentView: View {
    
    // 从环境变量中取得场景委托
    @EnvironmentObject var sceneDelegate: SceneDelegate
    
    // 视频播放状态
    @State var isPlaying:Bool = true
    // 画中画播放状态，和isPlaying相反
    @State var isPipPaused:Bool = false
    // 阿里播放器实例
    @State var player:AliPlayer = AliPlayer()
    // 是否全屏
    @State var isFullScreen: Bool = false
    
    var body: some View {
        ZStack(alignment:.center) {
            
            Color.gray.frame(maxWidth: .infinity,maxHeight: .infinity).ignoresSafeArea()
            
            AliPlayerWrapper(aliPlayer: $player,videoUrl: "https://bitdash-a.akamaihd.net/content/sintel/hls/playlist.m3u8",isPlaying: $isPlaying,isPipPaused:$isPipPaused)
                .frame(maxWidth:isFullScreen ? .infinity : 375,maxHeight: isFullScreen ? .infinity : 200)
                .ignoresSafeArea()
            
            VStack {
                
                Button("\(isFullScreen ? "退出全屏" : "点击全屏")"){
                    
                    if isFullScreen {
                        OrientationController.shared.lockOrientation(to: .portrait, onWindow: sceneDelegate.window)
                    }else{
                        OrientationController.shared.lockOrientation(to: .landscapeLeft, onWindow: sceneDelegate.window)
                    }
                    isFullScreen.toggle()
                }
            }
            
        }
    }
}

#Preview {
    ContentView()
}
