# My_L-ink

硬件：神秘藏宝室UP版本  
固件功能：兼容稚辉君APP传图  
软件：修改自群友分享的源码  
固件功能：兼容稚辉君APP传图：传图需按住电源键和波轮开关  
         两张图缓存：在源码中存入两张位图数据，按住电源按一下用户按键LED闪烁后墨水屏切换下一张图片，共两张  
         粗略电量显示：在按了两下后再按第三下则显示当前电量，按第四下则切换为第一张图片  
         拷贝NFC：需要自行购买UID芯片（大小为5x8）焊接到相应位置，拷贝卡参考1中有教程  
墨水瓶版本：微雪1.54寸V2版  
注：电子DIY明明，神秘藏宝室等版本基本HEX程序基本互通，而源码应该最多修改一两处（他们并没有公开源码自己从网上找源码开搞）  
   由于用户按键采用外部中断方式触发在切换图片时会出现失灵的情况，所以在切换时等待几秒，若无反应则松开电源键再次按下来重启程序。  
参考：
1、神秘藏宝室UP项目说明
https://www.bilibili.com/video/BV1oe411u7Q3?p=9&vd_source=b567447237dcfa732a3045ea99c6ec3d

2、微雪V2屏资料
hrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://www.waveshare.net/w/upload/e/e5/1.54inch_e-paper_V2_Datasheet.pdf

3、画面旋转参考
https://blog.csdn.net/lymacadam/article/details/136049743

4、神秘藏宝室QQ群
537081371

5、电子DIY明明QQ群
290035529
