#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat img = imread("H:\\Screen\\3.png");
	imshow("ÃÈÃÃ×Ó", img);
	waitKey(0);//ÔİÍ£ÆÁÄ» K´óĞ´
	return 0;
}