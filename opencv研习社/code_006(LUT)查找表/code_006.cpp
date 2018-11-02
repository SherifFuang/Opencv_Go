//���ұ�ο����ͣ�https://blog.csdn.net/jameshater/article/details/50759650
//���ҵ������ǣ�ͨ�����ұ������Ϊӳ�亯��������һ�ֶ�Ӧ��ϵ��������������䡣 ����ԭͼ�лҶ�Ϊ0-100�Ķ����Ϊ��ͼ�лҶ�0�� 100-200���1��200���ϱ��2.  ������ͼֻ�������Ҷȼ���
//Ҳ������ô˵�����ұ��Ǽ򵥵Ĳ�ѯ�����滻����ʱ��������飬��ͼ�����У����ұ�����ΪLUT�����ǽ������������ֵ������ϵ����ɫ����Ϊһ����ͨ�� LUT ������ȷ���ض�ͼ����Ҫ��ʾ����ɫ��ǿ�ȡ�
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void customColorMap(Mat &image);
int main(int argc, const char *argv[])
{
	Mat src = imread("C:\\Users\\admin\\Documents\\Visual Studio 2015\\Projects\\Testphoto\\daopian.png");
	if (src.empty())
	{
		printf("could not load image...\n");
		return -1;
	}
	Mat gray, dst;
	// ʹ��LUT
	applyColorMap(src, dst, COLORMAP_SUMMER);
	// ��ʾ���
	imshow("colorMap", dst);

	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	customColorMap(gray);

	waitKey(0);
	return 0;
}

void customColorMap(Mat &image) {
	int lut[256];
	for (int i = 0; i < 256; i++) {
		if (i < 127)
			lut[i] = 0;
		else
			lut[i] = 255;
	}

	int h = image.rows;
	int w = image.cols;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			int pv = image.at<uchar>(row, col);
			image.at<uchar>(row, col) = lut[pv];
		}
	}
	imshow("lut demo", image);
}

