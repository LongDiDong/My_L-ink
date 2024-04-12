# My_L-ink

硬件：神秘藏宝室UP版本  
软件：修改自群友分享的源码  
固件功能：  
         兼容稚辉君APP传图：传图需按住电源键和波轮开关并将线圈贴近手机NFC线圈处等待传输完成  
         两张图缓存：在源码中存入两张位图数据，按住电源按一下用户按键则切换一张，共两张（按下后LED会闪烁然后显示图片，图片显示需要等待3s期间需要一直按着电源键）  
         粗略电量显示：在按了两下后再按第三下则显示当前电量，按第四下则切换为第一张图片  
         拷贝NFC：需要自行购买UID芯片（大小为5x8）焊接到相应位置，拷贝卡参考1中有教程  
墨水瓶版本：微雪1.54寸V2版  
注：电子DIY明明，神秘藏宝室等版本基本HEX程序基本互通，而源码应该最多修改一两处（他们并没有公开源码自己从网上找源码开搞）,按键使用外部中断触在切换图片时可能发会生失灵的情况，解决办法是松开电源键再次按下以重启程序。  

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

感谢前辈们的辛勤探索！


