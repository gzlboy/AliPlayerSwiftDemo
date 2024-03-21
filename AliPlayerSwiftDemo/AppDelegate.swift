//
//  AppDelegate.swift
//  AliPlayerDemo
//
//  Created by admin on 2024/3/20.
//

import Foundation
import UIKit

// 参考：https://dev.classmethod.jp/articles/swiftui-update-rotation-ios16/
class AppDelegate: UIResponder, UIApplicationDelegate {

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        return true
    }

    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        let configuration = UISceneConfiguration(name: nil, sessionRole: connectingSceneSession.role)
        if connectingSceneSession.role == .windowApplication {
            // 根据配置来创建场景，并将相应的委托类实例化并放入环境变量中。
            configuration.delegateClass = SceneDelegate.self
        }
        return configuration
    }
    
    func application(_ application: UIApplication, supportedInterfaceOrientationsFor window: UIWindow?) -> UIInterfaceOrientationMask {
        return OrientationController.shared.currentOrientation
    }
    
}

class SceneDelegate: NSObject, ObservableObject, UIWindowSceneDelegate {
    var window: UIWindow?

    // 在应用程序的场景连接时，获取主窗口对象并保存到window属性中，以便后续对窗口的操作和管理
    func scene(_ scene: UIScene, willConnectTo session: UISceneSession, options connectionOptions: UIScene.ConnectionOptions) {
        guard let windowScene = scene as? UIWindowScene else { return }
        self.window = windowScene.keyWindow
    }
}
