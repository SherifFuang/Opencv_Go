
//ͼ��ֱ��ͼ���⻯
//ͼ����ǿ��������ͼ�����ֱ��ͼ���⻯�������������������׼ȷ��
//��OpenCV�������Ĵ�����ʾ���Ѿ��ܳ����������ҽѧӰ��ͼ��������ң��ͼ��Ҳ����ͨ��ֱ��ͼ���⻯������ͼ��������
//API��equalizeHist

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("C:/Users/admin/Documents/Visual Studio 2015/Projects/Testphoto/flower.png");

	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	Mat gray, dst;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("input", gray);
	equalizeHist(gray, dst);
	imshow("eq", dst);

	waitKey(0);
	return 0;
}



