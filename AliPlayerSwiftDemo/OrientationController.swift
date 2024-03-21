//
//  OrientationController.swift
//  AliPlayerDemo
//
//  Created by admin on 2024/3/20.
//

import Foundation
import UIKit

class OrientationController {

    private init() {}

    static let shared = OrientationController()

    var currentOrientation: UIInterfaceOrientationMask = .portrait // 默认竖屏

    // 解锁屏幕方向
    func unlockOrientation(onWindow window: UIWindow?) {
        
        self.noticeController(to: .all, onWindow: window)
    }

    // 锁定屏幕方向
    func lockOrientation(to orientation: UIInterfaceOrientationMask, onWindow window: UIWindow?) {

        self.noticeController(to: orientation, onWindow: window)
        
    }
    
    private func noticeController(to orientation: UIInterfaceOrientationMask, onWindow window: UIWindow?){
        
        guard let w = window else {
            return
        }
        
        currentOrientation = orientation

        guard var topController = w.rootViewController else {
            return
        }
        // 找到最前面被呈现的视图控制器
        while let presentedViewController = topController.presentedViewController {
            topController = presentedViewController
        }
        // 通知控制器屏幕方向有改变
        topController.setNeedsUpdateOfSupportedInterfaceOrientations()
    }
}
