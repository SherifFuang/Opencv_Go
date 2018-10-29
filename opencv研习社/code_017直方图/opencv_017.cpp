//ֱ��ͼ��ʹ��

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const int bins = 256;
Mat src;
const char* winTitle = "input image";//����һ��ָ���ַ�������ָ��
void showHistogram();
int main(int argc, char** argv) {// char **Ϊ����ָ��
	src = imread("D:/vcprojects/images/flower.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return 0;
	}
	namedWindow(winTitle, WINDOW_AUTOSIZE);
	imshow(winTitle, src);
	showHistogram();
	waitKey(0);
	return 0;
}


void showHistogram() {
	// ��ͨ������
	vector<Mat> bgr_plane;//vector���������ݽṹ���൱��һ����̬���飬�����ǵ���������һ��Mat����
	split(src, bgr_plane);//split��ͨ�����뺯����bgr_plane��Mat������׵�ַ
	// �����������
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };//ֱ��bins={256}�����ˣ�Ϊɶ��Ҫ�Ӹ�[1] ��bins�������ĸ���
	float hranges[2] = { 0,255 };//����ΪʲôҪ��[2]
	const float* ranges[1] = { hranges };//ɶ��˼��
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// ����Blue, Green, Redͨ����ֱ��ͼ
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);//&bgr_plane[0]Ϊ����ͼ���ָ�룬[0]��0��Ӧ��ɫͨ��������1��Ӧ��ɫ��2��Ӧ��ɫ��
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	// ��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);//cvRound������ȡ��
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	// ��һ��ֱ��ͼ����-----------------��һ������Ҫ����Ҫ��������ݾ��������ͨ��ĳ���㷨������������Ҫ��һ����Χ��
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	// ����ֱ��ͼ����
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	// ��ʾֱ��ͼ
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}

