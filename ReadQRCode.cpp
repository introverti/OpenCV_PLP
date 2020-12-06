#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using std::string;
using namespace cv;

/*Fonction
input:Image original and the quadrangle containing the code stored in type Mat
output;rien
use;draw and show blue frame around deteced QRCode
*/
void display(Mat& im, Mat& bbox)
{	
	
	//drawing rectangle with four fixed points
	//Point2i class containe a vector of two <int> type member
	//OpenCV stores the data in row-major order in memory <row,col>
	rectangle(im, Point2i(bbox.at<Vec2f>(0, 0)[0], bbox.at<Vec2f>(0, 0)[1]), Point2i(bbox.at<Vec2f>(0, 2)[0], bbox.at<Vec2f>(0, 2)[1]), Scalar(255, 0, 0), 3);
	//line(im, Point2i(bbox.at<float>(0,i), bbox.at<float>()),Point2i(bbox.at<float>((i + 1) % n, 0), bbox.at<float>((i + 1) % n, 1)), Scalar(255, 0, 0), 3);
	//Scalar decide the RGB color and the last number is the pixel of line 
	
	imshow("Result", im);//show the QRCode detected with the name "Result"
}

int main()
{
	// Read image (the address complet of image) use"\\" to seperate folder
	Mat inputImage = imread("E:\\GITHUB\\OpenCV_PLP\\myGit.png");

	//Detector typedef
	QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();

	//coordonne frame
	Mat bbox, rectifiedImage;

	//Detect QR code
	string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);

	//Get the link coded inside
	if (data.length() > 0)
	{
		cout << "Decoded Data : " << data << endl;
		display(inputImage, bbox);
		//CV_8UC3 is an 8-bit unsigned integer matrix/image with 3 channels £¨RGB£©
		rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
		//show the QRCode
		imshow("Rectified QRCode", rectifiedImage);

		waitKey(0);//wait for any keyboard input to end
	}
	else
	{
		cout << "QR Code not detected" << endl;
	}
	return 0;
}