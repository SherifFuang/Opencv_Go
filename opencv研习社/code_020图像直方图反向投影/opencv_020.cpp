//ͼ��ֱ��ͼ����ͶӰ��ͨ������ָ��ģ��ͼ��Ķ�άֱ��ͼ�ռ���Ŀ��Ķ�άֱ��ͼ�ռ䣬����ֱ��ͼ���ݹ�һ��֮�� ���б��ʲ���
//�����еõ�������ֵ�����ɲ��ұ��ԭͼ���������ӳ��֮���ٽ���ͼ��ģ������Ľ����
//ֱ��ͼ����ͶӰ���̣�
//- ����ֱ��ͼ
//- �������r
//- lut���ұ�
//- ���ģ��
//- ��һ�����
//
//���api
//- calcbackproject
//����ʲô�ط��أ�ģʽƥ�䡢����ʶ����Ƶ����  ��ô�ã�ʵ��ͼ��ָ�����������룬����֪����λ�ý��ж�λ
//OpenCV�о����㷨֮һCAMeanShift���ǻ��ڷ���ͶӰʵ�ֶ���֪�����λ�ò������ǡ��Ӷ��ﵽ��������
//�������ӣ�https://blog.csdn.net/jia20003/article/details/73136986
//https://blog.csdn.net/keith_bb/article/details/70154219

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const int bins = 256;
Mat src;
const char* winTitle = "input image";
void backProjection_demo(Mat &image, Mat &model);
int main(int argc, char** argv) {
	Mat src = imread("C:/Users/admin/Documents/Visual Studio 2015/Projects/Testphoto/target.png");
	Mat model = imread("C:/Users/admin/Documents/Visual Studio 2015/Projects/Testphoto/sample.png");
	//�ж�ͼ���Ƿ���سɹ�
	if (src.empty() || model.empty()) {
		printf("could not load image...\n");
		return 0;
	}
	namedWindow(winTitle, WINDOW_AUTOSIZE);
	imshow(winTitle, src);
	imshow("model", model);

	backProjection_demo(src, model);
	waitKey(0);
	return 0;
}

void backProjection_demo(Mat &image, Mat &model) {
	//��ͼ��תΪHSVͼ��
	Mat model_hsv, image_hsv;
	cvtColor(model, model_hsv, COLOR_BGR2HSV);
	cvtColor(image, image_hsv, COLOR_BGR2HSV);

	// ����ֱ��ͼ����������
	int h_bins = 32; int s_bins = 32;
	int histSize[] = { h_bins, s_bins };
	// hue varies from 0 to 179, saturation from 0 to 255
	float h_ranges[] = { 0, 180 };//��ʼ�����飬��������������Ԫ��
	float s_ranges[] = { 0, 256 };
	const float* ranges[] = { h_ranges, s_ranges };//ֱ��ͼ��ÿ��ά��bin��ȡֵ��Χ 
	int channels[] = { 0, 1 };
	Mat roiHist;
	//����ͼ��ֱ��ͼ����һ������
	calcHist(&model_hsv, 1, channels, Mat(), roiHist, 2, histSize, ranges, true, false);
	normalize(roiHist, roiHist, 0, 255, NORM_MINMAX, -1, Mat());
	
	//��ȡ����ͶӰ
	MatND backproj;
	calcBackProject(&image_hsv, 1, channels, roiHist, backproj, ranges, 1.0);
	//�������ͶӰ
	imshow("BackProj", backproj);
	
	////����ͼ��ֱ��ͼ
	//int w = 400;
	//int h = 400;
	//int bin_w = cvRound((double)w/histSize[1]);
	//Mat histImage = Mat::zeros(w, h, CV_8UC3);
	//for (int i = 0; i < 30; i++)
	//{
	//	rectangle(histImage, Point(i*bin_w, h), Point((i + 1)*bin_w, h - cvRound(roiHist.at<float>(i)*h / 255.0)), Scalar(0, 0, 255), -1);
	//}
	//imshow("HistImage", histImage);

}