# OpenCV_PLP
 from 0 to ?
## version
 C++ 11
 visual studio 2019 community
 openCV 3.4.12
### 检测QRcode并解码
使用了OpenCV库的内置函数 [cv::QRCodeDetector Class](https://docs.opencv.org/master/de/dc3/classcv_1_1QRCodeDetector.html)
detectAndDecode 会返回包含有QRCode的灰度图像，一个包含了QRCode四个顶点坐标的一行四列的矩阵和进过矫正(正方形化)二进制化的QR码.  
Mat 内元素类型可以用 对象.()检测，但是返回的是一个INT,需要对照下表：  
+--------+----+----+----+----+------+------+------+------+  
|        | C1 | C2 | C3 | C4 | C(5) | C(6) | C(7) | C(8) |  
+--------+----+----+----+----+------+------+------+------+  
| CV_8U  |  0 |  8 | 16 | 24 |   32 |   40 |   48 |   56 |  
| CV_8S  |  1 |  9 | 17 | 25 |   33 |   41 |   49 |   57 |  
| CV_16U |  2 | 10 | 18 | 26 |   34 |   42 |   50 |   58 |  
| CV_16S |  3 | 11 | 19 | 27 |   35 |   43 |   51 |   59 |  
| CV_32S |  4 | 12 | 20 | 28 |   36 |   44 |   52 |   60 |  
| CV_32F |  5 | 13 | 21 | 29 |   37 |   45 |   53 |   61 |  
| CV_64F |  6 | 14 | 22 | 30 |   38 |   46 |   54 |   62 |  
+--------+----+----+----+----+------+------+------+------+  
我们程序里的Mat bbox 返回值为13，即C2 CV_32F型，C2说明它是双通道数 32F说明是32float.  
注意应为OPENCV的rows和cols是反过来的，所以对应Mat.at<float>(y,x)，小括号内是数据的地址！！！（rows，cols).  
对应双通道数，应该使用Mat.at<vec2f>(y,x)来读取数据.  
虽然我们获得的bbox是一个1行4列的矩阵，但是其中存储了8个float数，因为每个元素是一个双通道的vector.

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
