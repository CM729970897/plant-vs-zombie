《保卫花园》设计部分参考了市场上《植物大战僵尸》等攻防游戏，用于兴趣开发。在该游戏中，玩家使用各种“植物”抵御“僵尸”对花园的入侵，是一款集策略性和趣味性于一体的游戏。

本款应用整体设计主要包括6项功能模块，分别是用户管理、游戏设置、游戏模式、游戏商城、我的背包、图鉴。除此之外还有一些数据抓取等工作。

## 整体设计
+ 用户管理
	注册：对于新用户而言，可以创建一个新用户
	登录：从用户列表选择一个用户，读取用户进度，进入游戏
	
+ 游戏模式
	包括无尽模式和冒险模式。冒险模式：过关性质的模式，玩家每过一关都会获取相应的金币。冒险模式共有10关。无尽模式：僵尸无穷无尽，永远不会通关，只会累计分数，获取金币 

+ 游戏商城
	游戏道具的购买。道具包括：植物卡，道具卡等

+ 游戏图鉴
	对游戏中出现的植物、僵尸和道具的介绍

+ 我的背包
	包括自己拥有的金币和已经拥有的物品

+ 游戏设置
	主要是游戏音效的设置，用户的退出等


![](https://i.imgur.com/pg98diy.png)


+ 本系统用例图
	![](https://i.imgur.com/P9VZ2IM.png)

数据字典

+ 用户信息列表：

![](https://i.imgur.com/ds1kuZv.png)


+ 植物信息列表：

 ![](https://i.imgur.com/fK9iWiF.png)

	
+ 僵尸信息列表

 ![](https://i.imgur.com/hGBvpFi.png)


+ 玩家道具信息列表

![](https://i.imgur.com/rbnJeLs.png)



其他:
+ C++知识
+  数据库的设计（考虑用户量不大，游戏最终采用Json来存储用户信息）
+ 图形制作PS的使用（本项目中只做了了简单图形裁剪）+ 参考其他数据的抓取
+ VS2013



