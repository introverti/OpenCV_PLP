# OpenCV_PLP
 from 0 to ?
## version
 C++ 11
 visual studio 2019 community
 openCV 3.4.12 
### 安装与配置
[参考文章](https://www.jianshu.com/p/b47ce15a9642)
#### 下载win版 opencv并安装
    (https://opencv.org/releases/)
#### 添加至环境变量
    此电脑->属性->高级系统设置->高级->环境变量，
    在系统变量的path中添加opencv文件夹中“..\opencv\build\x64\vc14\bin”的完整地址
#### Visual studio 配置
    1.Debug属性改为x64
    2.打开视图->其他窗口->属性管理器，右键打开将属性管理器中“Debug|x64”的属性
    3.编辑VC++目录中的包含目录添加：“...\opencv\build\include”和“opencv\build\include\opencv2”的完整地址（！！！不要改变顺序）
    4.同理上编辑库目录，添加“...\opencv\build\x64\vc14\lib”的完整地址
    5.在链接器->输入->附加依赖项添加 “opencv_world3412d.lib” 此处对应修改opencv的不同版本号
    （！！！优先使用有带“d”后缀的lib）
    