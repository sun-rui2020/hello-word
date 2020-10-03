#include<opencv2/opencv.hpp>
#include<drawing.h>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char**argv) {
	Mat src = imread("E:/picture/bilateral.png");
	if (src.empty()) {
		std::cout << "image could not load ...\n";
		return -1;
	}
	imshow("¶ÁÈë´°¿Ú", src);
	
	
	Pixel_Demo qd;
	//qd.colorSpace_Demo(src);
	//qd.mat_creation(src);
	//qd.Pixel_visit_Demo(src);
	//qd.operators_Demo(src);
	//qd.track_bar_demo(src);
	//qd.key_demo(src);
	//qd.color_style_demo(src);
	//qd.bitwise_demo(src);
	//qd.channels_demo(src);
	//qd.inrange_demo(src);
	//qd.pixel_statistic_demo(src);
	//qd.drawing_demo(src);
	//qd.random_demo();
	//qd.polyline_drawing_demo();
	//qd.mouse_drawing_demo(src);
	//qd.norm_demo(src);
	//qd.resize_demo(src);
	//qd.flip_demo(src);
	//qd.rotate_demo(src);
	qd.video_demo(src);
	//qd.histogram_demo(src);
	//qd.histogram_2d_demo(src);
	//qd.histogram_eq_demo(src);
	//qd.blur_demo(src);
	//qd.calcbackproject_demo(src);
	//qd.gaussian_blur_demo(src);
	//qd.bifilter_demo(src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
