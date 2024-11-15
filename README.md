该项目为heu 信息安全综合课程设计实验 blowfish算法实现（MFC框架）  
# 功能包括：  
1.blowfish加解密算法实现  
2.mfc友好页面  
3.文件操作、对话框操作  
4.密钥随机生成、清空内容、关于  

# blowfish算法：  
Tested on OSX (32bit/64bit)  
ECB mode only  
The key length must be a multiple of 8bit  
// Input/Output length must be a multiple of the block length (64bit)  

# 环境部署   
本系统的开发环境为Win11、Visio Studio 2022 Enterprise  
在win7以上windows系统均可使用  

# 使用说明  
## 编辑框操作  
1、将单选（radio）控件设置为编辑框操作（默认）  
2、输入密钥或点击随机生成按钮  
3、输入明文或密文  
4、点击加密或解密按钮  
**注：项目使用unicode字符集、编辑框中一个字符占两个字节。加密按字节流处理**  
## 文件操作  
1、将单选（radio）控件设置为文件操作  
2、输入密钥或点击随机生成按钮  
3、点击加密或解密按钮  

本项目部分参考：https://github.com/ddokkaebi/Blowfish.git  
在此做出感谢  
