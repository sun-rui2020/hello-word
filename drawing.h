#pragma once
#include<opencv2/opencv.hpp>

using namespace cv;


class Pixel_Demo {

public:
	void colorSpace_Demo(Mat&image);
	void mat_creation(Mat&image);
	void Pixel_visit_Demo(Mat&image);
	void operators_Demo(Mat&image);
	void track_bar_demo(Mat&image);
	void key_demo(Mat&image);
	void color_style_demo(Mat&image);
	void bitwise_demo(Mat&image);
	void channels_demo(Mat&image);
	void  inrange_demo(Mat&image);
	void pixel_statistic_demo(Mat&image);
	void drawing_demo(Mat&iamge);
	void random_demo();
	void polyline_drawing_demo();
	void mouse_drawing_demo(Mat&image);
	void norm_demo(Mat&image);
	void resize_demo(Mat&image);
	void flip_demo(Mat&image);
	void rotate_demo(Mat&image);
	void video_demo(Mat&image);
	void histogram_demo(Mat&image);
	void histogram_2d_demo(Mat &image);
	void histogram_eq_demo(Mat&image);
	void calcbackproject_demo(Mat&image);
	void blur_demo(Mat&image);
	void gaussian_blur_demo(Mat&image);
	void bifilter_demo(Mat&image);


};

