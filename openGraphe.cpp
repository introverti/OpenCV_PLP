#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat img = imread("H:\\Screen\\3.png");
	imshow("������", img);
	waitKey(0);//��ͣ��Ļ K��д
	return 0;
}