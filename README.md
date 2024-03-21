#  说明

阿里官方并未提供SwiftUI项目整合视频点播SDK示例，SDK是Object-C写的，要在SwiftUI中使用，需要做一些转化，该项目就是为解决整合过程中的一些坑而做的，希望给新手朋友一个参考(我也是一个新手:))

播放器文档：[https://help.aliyun.com/zh/vod/developer-reference/quick-integration?spm=a2c4g.11186623.0.0.796b265crmZRcH](https://help.aliyun.com/zh/vod/developer-reference/quick-integration?spm=a2c4g.11186623.0.0.796b265crmZRcH)

#  示例功能：
1、画中画

2、全屏播放切换

3、...（自定义播放器UI？）

![3DA0A8F4D8B0174E73DD2BFB933CBF5B](https://github.com/gzlboy/AliPlayerSwiftDemo/assets/1492060/70e12b42-fbb7-49a8-af04-5e2b0ad6e26a)


#  注意事项：
1、阿里云的播放器需要真机调试，虚拟机会报错；

2、更换自己bundle id；

3、按照文档更改SDK的签名证书和key；

3、项目使用的播放器sdk版本：6.10.0，Xcode版本：15.2
