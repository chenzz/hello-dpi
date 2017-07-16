---
title: "HelloDpi使用说明"
list_number: false
date: 2017-02-17 14:26:14
categories: mac
tags: [小工具, macOS, mac, 分辨率]
description: "一个调节mac显示器HiDpi分辨率的工具"
---

HelloDpi 用来设置屏幕[HiDpi](http://www.jianshu.com/p/0ba2777f38fc)。
当Mac外接高分辨率的屏幕（大于1080P）时，设置HiDpi可以使得画面更加细腻。

### 一、使用步骤

#### 0、关闭系统SIP
macOS 10.10及以下略过该步骤哦！
* 重启电脑，按住`Command+R`直到出现苹果Logo。
  这样进入了**recovery mode**
* 点击`实用工具`，进入终端Terminal
* 在终端里输入`csrutil disable`关闭SIP
* 正常重启电脑
#### 1、添加自定义的分辨率

打开HelloDpi，添加自定义分辨率。

如我的屏幕是2560x1440分辨率，添加1600x900的HiDpi分辨率。

<img src="http://oa5m4nrwd.bkt.clouddn.com/2017-03-18-080316.jpg" width="70%" height="70%">

#### 2、重启系统

#### 3、切换分辨率

* 下载[RDM](http://avi.alkalay.net/software/RDM/RDM-2.2.pkg)
* 安装RDM

右键点击『RDM-2.2.pkg』- 打开

* 使用RDM切换分辨率

<img src="https://cloud.githubusercontent.com/assets/3484242/7100316/255a7d74-dff0-11e4-9bf9-16e726336e29.png" width="70%" height="70%">


Done!

### 二、最新版本

[v1.0.0下载](https://raw.githubusercontent.com/czzshr/static-resource/master/HelloDpi_v1.0.0.zip)