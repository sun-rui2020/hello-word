#include<drawing.h>


//*1、图像颜色转变**/
void Pixel_Demo::colorSpace_Demo(Mat&image) {
	Mat gray, hsv;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	cvtColor(image, hsv, COLOR_BGR2HSV);
	namedWindow("灰度", WINDOW_NORMAL);//可调整窗口大小
	namedWindow("hsv", WINDOW_NORMAL);
	imshow("灰度", gray);
	imshow("hsv", hsv);
	//imwrite("E:/picture/hsv.jpg", gray);
	//imwrite("E:/picture/hsv.jpg", hsv);
}
//*2、创建图片*/
void Pixel_Demo::mat_creation(Mat&image) {
	Mat m1, m2;
	m1 = image.clone();
	image.copyTo(m2);

	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC3);
	std::cout << "width:" << m3.cols << "  hight:" << m3.rows << "  channel:" << m3.channels() << std::endl;
	m3 = Scalar(0, 225, 0);
	imshow("新创图片", m3);
}
//*3、图像像素读取/**/
void Pixel_Demo::Pixel_visit_Demo(Mat&image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	/**数组遍历
	for (int row = 0; row < h; row++){
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//灰度图像
				int pv = image.at<uchar>(row, col);
				image.at<uchar>(row, col) = 255 - pv;

			}
			if (dims == 3) {//彩色图像
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];


			}
		}

}*/

/**指针遍历**/
	for (int row = 0; row < h; row++) {
		uchar* current_row = image.ptr(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//灰度图像
				int pv = *current_row;
				*current_row++ = 255 - pv;

			}
			if (dims == 3) {//彩色图像
				*current_row++ = 255 - *current_row;//++运算符优先级大于指针？？
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;


			}
		}

		imshow("像素读写演示", image);
	}
}

//4、图像像数算术操作*/
void Pixel_Demo::operators_Demo(Mat&image) {
	Mat dst1 = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(50, 50, 50);
	/**
	//dst1 = image + Scalar(50, 50, 50);  //可进行加减除操作
	//dst1 = image - Scalar(100, 100, 100);
	dst1 = image / Scalar(2, 2, 2);
	//dst1 = image * Scalar(1.1, 1.1, 1.1);//没实现
	//imshow("加法操作",dst1);
	//imshow("减法操作",dst1);
	imshow("除法操作", dst1);
	//imshow("乘法操作", dst1);
	*/
	/**用函数实现加减乘除*/
	//add(image, m, dst1);
	//subtract(image, m, dst1);
	//multiply(image, m, dst1);
	divide(image, m, dst1);
	imshow("算术运算结果", dst1);
}
//5、滚动条操作亮度的回调函数*/
static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst1 = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0, b, dst1);
	imshow("亮度与对比度调整", dst1);
}
static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst1 = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst1);  //对比度调整，就是把每个点像数乘以一个相同值，俩个点的像素差值逐渐扩大
	imshow("亮度与对比度调整", dst1);				//而亮度调整，是每个像素点都加上一个相同的值，要亮每个点都亮
}
//5、滚动条操作亮度*/
void Pixel_Demo::track_bar_demo(Mat&image) {
	namedWindow("亮度与对比度调整", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_vaule = 100;

	createTrackbar("Value Bar", "亮度与对比度调整", &lightness, max_value, on_lightness, (void*)(&image));
	//第一个参数是trackbar调节窗口里滚动条的名称，第二个是要调整图像窗口的名称，第三个是要通过
	//trackbar来改变的初始值位置，第四个是改变的最大值,第五个响应滚动条操作，回调函数:回调函数：通过函数指针调用的函数。把函数的指针（地址）作为参数传递给另一个函数，当这个指针被用来调用其所指向的函数时，就称其为回调函数。
	//第六个参数：用户给回调函数的数据
	createTrackbar("Contrast Bar", "亮度与对比度调整", &contrast_vaule, 200, on_contrast, (void*)(&image));
	on_contrast(50, &image);
}
/*6、键盘响应**/
void Pixel_Demo::key_demo(Mat&image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {
		int  c = waitKey(100);
		if (c == 27) {//key#esc
			break;
		}
		if (c == 49) {//key#1
			std::cout << "you enter #1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);

		}
		if (c == 50) {//key#2
			std::cout << "you enter #2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		if (c == 51) {//key#3
			std::cout << "you enter #3" << std::endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
		}
		imshow("转化为灰度", dst);
		std::cout << c << std::endl;


	}

}
/*7、颜色表显示不同滤镜后效果**/
void Pixel_Demo::color_style_demo(Mat&image) {
	int colormap[] = {
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_CIVIDIS,
		COLORMAP_COOL,
		COLORMAP_DEEPGREEN,
		COLORMAP_HOT,
		COLORMAP_HSV,
		COLORMAP_INFERNO,
		COLORMAP_INFERNO,
		COLORMAP_JET,
		COLORMAP_MAGMA,
		COLORMAP_OCEAN,
		COLORMAP_PARULA,
		COLORMAP_PINK,
		COLORMAP_PLASMA,
		COLORMAP_RAINBOW,
		COLORMAP_SPRING,
		COLORMAP_SUMMER,
		COLORMAP_TURBO,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED,
		COLORMAP_VIRIDIS,
		COLORMAP_VIRIDIS,
		COLORMAP_WINTER
	};
	Mat dst;
	int index = 0;
	while (true) {
		int c = waitKey(2000);
		if (c == 27) {
			break;
		}
		applyColorMap(image, dst, colormap[index % 19]);
		index++;
		namedWindow("颜色风格", WINDOW_NORMAL);
		imshow("颜色风格", dst);
	}
	{

	}
}
/*8、像素逻辑操作（图片上绘制矩形）**/
void Pixel_Demo::bitwise_demo(Mat&image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);//第四个参数大于0，绘制，小于0填充
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst;
	//bitwise_and(m1,m2, dst);
	//bitwise_not(image, dst);   //可直接执行 Mat dst = ~image
	bitwise_xor(m1, m2, dst);
	imshow("逻辑操作", dst);
}
/*9、通道分离合并*/
void Pixel_Demo::channels_demo(Mat&image) {

	//通道分离
	std::vector<Mat> mv;//创建一个名为mv的vector对象，mv中存储类型为Mat
	split(image, mv);   //分离出的值放在mv中，相当与初始化了mv

	Mat dst;
	/**蓝色
	mv[1] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("蓝色",dst);
	**/
	/**绿色
	mv[0] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("绿色", dst);
	**/
	/**关掉第一个通道
	mv[0] = 0;
	merge(mv, dst);
	imshow("关掉第一个通道", dst);
	**/

	mv[0] = 0;
	mv[1] = 0;
	merge(mv, dst);
	imshow("红色", dst);

	int from_to[] = { 0,2,1,1,2,0 };// 通道互相交换，0-2,1-1,2-0
	int from_to1[] = { 0,1,1,0,2,2 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	mixChannels(&image, 1, &image, 1, from_to1, 3);
	imshow("通道相互操作", dst);
	imshow("通道相互操作1", image);
}
/*10、图像背景切换*/
void Pixel_Demo::inrange_demo(Mat&image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//mask作为二值图像灰白（黑色也是灰色）
	//通俗的来讲，这个函数就是判断hsv中每一个像素是否在[lowerb，upperb]之间，注意集合的开闭。
	//如果结果为是，那么在hsv相应像素位置填上255，(即颜色为白色)反之则是0（即颜色为黑色）。一般我们把hsv当作一个mask来用，
	//inrange函数用来割掉绿色，凡是绿色都变为白色，其他为黑色

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(0, 0, 255);
	bitwise_not(mask, mask);//把想要的颜色变为白色
	imshow("mask", mask);
	image.copyTo(redback, mask);//把原图复制到redback上，但是黑色部分不要，因为此时的mask图片上只有黑白两色，且有人处为白色
	imshow("红色背景", redback);

}
/*11、图像像素统计*/
void Pixel_Demo::pixel_statistic_demo(Mat&image) {
	double minv, maxv;  //像素最大值，最小值
	Point minloc, maxloc;//最大值位置，最小值位置
	std::vector<Mat>mv;
	split(image, mv);
	Mat mean, stddev;
	for (int i = 0; i < mv.size(); i++) {

		minMaxLoc(mv[i], &minv, &maxv, &minloc, &maxloc);//函数要求是单通道，计算像素最大值最小值
		std::cout << "No.channels#" << i << " min value:  " << minv << " max value:  " << maxv << std::endl;
		meanStdDev(mv[i], mean, stddev);//计算像素均值和标准方差
		std::cout << "No.channels#" << i << "means: " << mean << "stddev: " << stddev << std::endl;
		std::cout << "\n\n";
	}
	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200);
	meanStdDev(redback, mean, stddev);
	imshow("redback", redback);
	std::cout << "means: " << mean << std::endl;
	std::cout << "stddev: " << stddev << std::endl;

}
/*12、图形绘制*/
void Pixel_Demo::drawing_demo(Mat &image) {
	Rect rect;
	rect.x = 160;
	rect.y = 150;
	rect.width = 150;
	rect.height = 150;
	Mat bg = Mat::zeros(image.size(), image.type());
	//rectangle(bg, rect, Scalar(0, 0, 255), 2, 8, 0);
	rectangle(bg, rect, Scalar(0, 0, 255), 2, 8, 0);//thickness参数调整填充或描边>0描边；<0填充,大于0时，值越大县越宽
	circle(bg, Point(310, 300), 20,Scalar(0,255,0), 2, 8, 0);
	line(bg, Point(160, 150), Point(310, 300), Scalar(0, 255, 0), 2, LINE_AA, 0);//LINE_AA反锯齿
	RotatedRect rrt;
	rrt.center = Point(200, 200);
	rrt.size = Size(100, 200);
	rrt.angle = 0.0;
	ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8 );
	Mat dst;
	addWeighted(image, 0.3, bg, 0.7, 0, dst);//图像按比例叠加
	
	imshow("绘制演示",dst);


}
/*13、随机数产生和随机绘制图形*/
void Pixel_Demo::random_demo() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3); //创建一张画布
	int w = canvas.cols;
	int h = canvas.rows;
	RNG rng(12345);				//产生随机数的种子
	while (true) {
		int c = waitKey(10);
		if (c == 27) {
			break;
		}					//一定设置一种方法推出死 循环，这是通过按键esc退出循环

		int x1 = rng.uniform(0, w);//随机产生0~w之间的数，w为画布的宽度，x1为将要随机画线的起点横坐标
		int y1 = rng.uniform(0, h);//随机产生0~h之间的数，h为画布的高度，y1为将要随机画线的起点纵坐标
		int x2 = rng.uniform(0, w);//随机产生0~w之间的数，w为画布的宽度，x2为将要随机画线的终点横坐标
		int y2 = rng.uniform(0, h);//随机产生0~h之间的数，w为画布的高度，x2为将要随机画线的终点纵坐标
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		canvas = Scalar(0, 0, 0);//可每次画完一条线后颜色置0，也就是变为黑色，和初始画布颜色一致
		//line(canvas, Point(x1,y1), Point(x2,y2), Scalar(b,g,r), 2, 8, 0);
		//rectangle(canvas, Point(x1,y1), Point(x2,y2), Scalar(b,g,r), 2, 8, 0);
		circle(canvas, Point(x1,y1), rng.uniform(0,512), Scalar(b, g, r), 2, 8, 0);
		imshow("随机绘制演示",canvas);

	}
	
}
/*14、绘制多边形并填充*/
void Pixel_Demo::polyline_drawing_demo() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(100, 100);
	Point p2(350, 100);
	Point p3(450, 280);
	Point p4(320, 480);
	Point p5(80, 400);

	Point p12(109, 109);
	Point p22(359, 109);
	Point p32(459, 289);
	Point p42(329, 489);
	Point p52(89, 409);

	Point p6(100, 100);
	Point p7(100, 200);
	Point p8(200, 100);

	std::vector<Point>pts1(5);//如果想要通过数组方式赋值，必须要加(5);
	pts1[0] = p1;
	pts1[1] = p2;
	pts1[2] = p3;
	pts1[3] = p4;
	pts1[4] = p5;
	/*
	std::vector<Point>pts1;
	pts1.push_back(p1);
	pts1.push_back(p2);
	pts1.push_back(p3);
	pts1.push_back(p4);
	pts1.push_back(p5);
	*/

	std::vector<Point>pts2(5);//如果想要通过数组方式赋值，必须要加(5);
	pts2[0] = p12;
	pts2[1] = p22;
	pts2[2] = p32;
	pts2[3] = p42;
	pts2[4] = p52;

	std::vector<Point>pts3(3);
	pts3[0] = p6;
	pts3[1] = p7;
	pts3[2] = p8;

	//fillPoly(canvas, pts1, Scalar(255, 255, 0), 8, 0);//  填充
	//polylines(canvas, pts1, true, Scalar(0, 0, 255), 2, LINE_AA, 0);  //此函数不可以填充，也就是不可以直接把2（参数thickness）改成负数
	std::vector<std::vector<Point>>contours(3);
	contours[0] = pts1;
	contours[1] = pts2;
	contours[2] = pts3;
	for (int i = 0; i < contours.size(); i++) {
	drawContours(canvas, contours, i, Scalar(150, 0, 0), -1,8);//此函数可直接填充
     imshow("多边形绘制", canvas);
	}
	
}
/*15、鼠标响应绘制矩形，并提取矩形内容*/
Point sp(-1, -1);//鼠标初始位置
Point ep(-1, -1);//鼠标结束位置
Point center(-1,-1);
int  radius = 0;
Mat temp; 
Mat temp2;
static void  on_draw(int event, int x, int y, int flags, void*userdata) {
	Mat image = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN) {
		sp.x = x;
		sp.y = y;
		std::cout << " start point" << sp << std::endl;
	}
	else if (event == EVENT_LBUTTONUP) {
		ep.x = x;
		ep.y = y;
		
		int dx = ep.x - sp.y;
		int dy = ep.y - sp.y;
		if(dx > 0 && dy > 0){
			Rect box(sp.x, sp.y, dx, dy);
			
			rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
			/*
			center.x = (sp.x < ep.x ? sp.x + abs(ep.x - sp.x) : ep.x + abs(ep.x - sp.x));
			center.y = (sp.y < ep.y ? ep.y + abs(ep.y - sp.y) : ep.y + abs(ep.y - sp.y));
			radius = std::sqrt((ep.x - sp.y)*(ep.x - sp.x) + (ep.y - sp.y)*(ep.y - ep.y)) / 2;
			circle(image, Point(center.x, center.y),radius,Scalar(0,0,255), 1, LINE_AA, 0);
			*/
			temp.copyTo(image);//擦除移动痕迹，用原图覆盖
			imshow("鼠标绘制", image);
			imshow("RIO", image(box));
			temp2 = image(box);
			//为下一次绘制做好准备
			sp.x = -1;
			sp.y = -1;
		}
		
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.y;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0) {
				Rect box(sp.x, sp.y, dx, dy);
				temp.copyTo(image);//擦除移动痕迹，用原图覆盖
				/*
				center.x = (sp.x < ep.x ? sp.x + abs(ep.x - sp.x) : ep.x + abs(ep.x - sp.x));
				center.y = (sp.y < ep.y ? ep.y + abs(ep.y - sp.y) : ep.y + abs(ep.y - sp.y));
				radius = std::sqrt((ep.x - sp.y)*(ep.x - sp.x) + (ep.y - sp.y)*(ep.y - ep.y)) / 2;
				circle(image, Point(center.x, center.y), radius, Scalar(0, 0, 255), 2, 8, 0);
				*/
				rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
				imshow("鼠标绘制", image);
			}
		}
	}
}
void Pixel_Demo::mouse_drawing_demo(Mat &image) {
	namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
	setMouseCallback("鼠标绘制", on_draw,(void*)(&image));
	imshow("鼠标绘制", image);
	temp = image.clone();
	
}/*16、图像数据类型转化，归一化*/

void Pixel_Demo::norm_demo(Mat&image) {
	Mat dst;
	
	std::cout << image.type() << std::endl;
    image.convertTo(image, CV_32F);//converTo(目的，类型，比例因子，添加值)
	//src.convertTo(dst, type, scale, shift)  dst(i)=src(i)xscale+(shift,shift,...)
	std::cout << image.type() << std::endl;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);//归一化
	std::cout << dst.type() << std::endl;
	//imshow("图像数据归一化", dst);
	dst.convertTo(dst, CV_8UC3, 255);
	std::cout << dst.type() << std::endl;
	imshow("图像数据归一化", dst);
}
/*17、图像缩放*/
void Pixel_Demo::resize_demo(Mat&image) {
	Mat zoomin, zoomout1,zoomout2,zoomout3;
	int h = image.rows;
	int w = image.cols;
	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);//双线性插值
	resize(image, zoomout1, Size(w*1.5, h*1.5), 0, 0, INTER_NEAREST);//最邻近插值
	resize(image, zoomout2, Size(w * 1.5, h * 1.5), 0, 0, INTER_LINEAR);//双线性插值
	resize(image, zoomout3, Size(w * 1.5, h * 1.5), 0, 0, INTER_CUBIC);//双立方（三次卷积）性插值
	
	//imshow("zoomin", zoomin);
	imshow("zoomout1", zoomout1);
	imshow("zoomout2", zoomout2);
	imshow("zoomout3", zoomout3);
}
/*18、图像镜像*/
void Pixel_Demo::flip_demo(Mat&image) {
	Mat dst;
	flip(image, dst, 0);//0上下翻转
	//flip(image, dst, 1);//左右翻转
	//flip(image, dst, -1);//对角翻转，旋转180
	imshow("图像垂直镜像", dst);

}
/*19、/图像旋转*/
void Pixel_Demo::rotate_demo(Mat&image) {
	Mat dst, M;
	int w = image.rows;
	int h = image.cols;
	//M 是用来旋转变换相乘的矩阵
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);//Point2f原图像的中心，旋转角度，缩放比例
	/*
	M= [cosa  sina 0]
	   [-sina cosa 0]
 	*/
	//如果已知原图和目标图可各取三点，用函数getAffineTransform( srcTri, dstTri )求仿射变换矩阵M
	std::cout << M << std::endl;

	double cos = abs(M.at<double>(0, 0));
	double sin= abs(M.at<double>(0, 1));
	int nw = cos*w + sin * h;//新画布的宽
	int nh = sin * w + cos * h;//新画布的高
	M.at<double>(0, 2) += (nw / 2 - w / 2);//将图像移到中心
	M.at<double>(1, 2) += (nh / 2 - h / 2);

	warpAffine(image, dst, M,Size(nw,nh),INTER_LINEAR,0,Scalar(255,255,255));
	
	imshow("旋转图像", dst);
}
/*20、摄像头（视频读）入**视频本质是图像，能对图像的操作同样适用于视频*/
void Pixel_Demo::video_demo(Mat&image) {
	VideoCapture capture(0);//0为摄像头
	//VideoCapture capture("E:/picture/normal-angle.mp4");
    int  frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//宽
	int  frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);//高
	int  count = capture.get(CAP_PROP_FRAME_COUNT);//总帧数
	double fps = capture.get(CAP_PROP_FPS);//一秒播放的帧数
	int fourcc = capture.get(CAP_PROP_FOURCC);//视频编码
	std::cout << "frame width: " << frame_width << std::endl;
	std::cout << "frame height: " << frame_height << std::endl;
	std::cout << "fps: " << fps << std::endl;
	std::cout << "number of frame: " << count << std::endl;
	VideoWriter writer("E:/picture/test.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height),true);
	
	Mat frame;
	
	//_sleep(1000);
	while (true)
	{
		capture.read(frame);
		if (frame.empty()) {
		std::cout << "could not load video";
		break;
	     }
		flip(frame, frame, 1);//如果直接加载内置摄像头，需要翻转成镜像

		//colorSpace_Demo(frame);//调用之前函数改变视频的颜色
		//color_style_demo(frame);//调用函数循环改变颜色,视频没播放？？？
		//writer.write(frame);
		namedWindow("frame", WINDOW_NORMAL);
		imshow("frame", frame);
		int c = waitKey(30);
		if (c == 27) {
			break;
		}

	}
	capture.release();//解除摄像头占用
	writer.release();
	
}
//21、绘制一维直方图
void Pixel_Demo::histogram_demo(Mat &image) {
	// 三通道分离
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	// 定义参数变量
	const int channels[1] = { 0 };//需要计算图像的哪个通道（bgr空间需要确定计算 b或g或r空间）
	const int bins[1] = { 256 };//直方图的每一个维度的 柱条的数目（就是将灰度级分组）
	float hranges[2] = { 0,255 };//定义一个变量用来存储 单个维度 的数值的取值范围
	const float* ranges[1] = { hranges };//确定每个维度的取值范围，
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// 计算Blue, Green, Red通道的直方图
	/*&rgb_planes[0]: 输入数组(或数组集)
	1: 输入数组的个数 (这里我们使用了一个单通道图像，我们也可以输入数组集 )
	0: 需要统计的通道 (dim)索引 ，这里我们只是统计了灰度 (且每个数组都是单通道)所以只要写 0 就行了。
	Mat(): 掩码( 0 表示忽略该像素)， 如果未定义，则不使用掩码
	r_hist: 储存直方图的矩阵
	1: 直方图维数
	histSize: 每个维度的bin数目
	histRange: 每个维度的取值范围
	uniform 和 accumulate: bin大小相同，清楚直方图痕迹*/
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	std::cout << "b_hist" << b_hist << std::endl;//b_hist存储的是每个像素值的个数
	// 显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);//cvRound四舍五入取整，直方图的等级，画布宽度除以bins（灰度等级）总数
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	// 归一化直方图数据
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());//0,histImage是归一化的上下限，为了绘制的直方图不超过画布的宽
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	// 绘制直方图曲线
	//bin_w是每个像素的区间，一个点占的横坐标刻度值，第几个点的横坐标就是第几个点减一乘以每个点占的区间即表达式：
	//(i-1)*bin_w,而纵坐标是，首先取出之前存入直方图的坐标点b_hist.at<float>(i-1),但是直方图坐标轴向下为正
	//所以要用画布高度减去这个值
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	// 显示直方图
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}
//22、绘制二维直方图
void Pixel_Demo::histogram_2d_demo(Mat &image) {
	// 2D 直方图
	//【1】载入原图,转化为HSV颜色模型
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	//【2】参数准备
	//将色调量化为30个等级，将饱和度量化为32个等级
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins, sbins };
	//定义变化范围
	float h_range[] = { 0, 179 };//定义色调的变化范围为0-179
	float s_range[] = { 0, 255 };//定义饱和度的变化范围为0-255
	const float* hs_ranges[] = { h_range, s_range };

	int hs_channels[] = { 0, 1 };//calcHist函数中将计算第0通道和第1通道的直方图
	//输入数组，数组个数为1，通道索引，不使用掩模，输出目标直方图，需要计算的直方图维度为2，存放每个维度的直方图尺寸的数组，每一维数组的取值范围数组，指示直方图均匀，直方图在配置阶段会被清零
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	//【4】绘制直方图准备参数
	double maxVal = 0;//最大值
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);//查找数组和子数组的全局最大值存入maxValue中
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins*scale, hbins * scale, CV_8UC3);
	for (int h = 0; h < hbins; h++) {
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);//统计个数的值缩放到[0,255]范围，增强可视化
			//绘制32*30个10*10???大小的矩阵小块，矩形小块的灰度值代表统计个数
			rectangle(hist2d_image, Point(h*scale, s*scale),
				Point((h + 1)*scale-1 , (s + 1)*scale-1 ),
				Scalar::all(intensity),
				-1);
			//Scalar::all(intensity)给每个通道都赋intensity
		}
	}
	applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);
	imshow("H-S Histogram", hist2d_image);
	imwrite("D:/hist_2d.png", hist2d_image);
}
//23、直方图均衡化
void Pixel_Demo::histogram_eq_demo(Mat&image) {
	//单通道直方图均衡化
	/*
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("灰度", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("直方图均衡化",dst);
*/
	//彩色直方图均衡化
	std::vector<Mat>bgr_plane(3);
	split(image, bgr_plane);
	std::vector<Mat>dst_bgr(3);
	equalizeHist(bgr_plane[0], dst_bgr[0]);
	equalizeHist(bgr_plane[1], dst_bgr[1]);
	equalizeHist(bgr_plane[2], dst_bgr[2]);
	Mat dst = Mat::zeros(bgr_plane[0].size(), CV_8UC3);
	merge(dst_bgr, dst);
	imshow("彩色图像均衡化",dst);
 }

//24、直方图反向投影，车牌识别
void Pixel_Demo::calcbackproject_demo(Mat&image) {
	Mat testImage = imread("E:/picture/recognition.jpg");
	
	if (testImage.empty()) {
		std::cout << "colud not load test iamge \n";
		return ;
	}
	imshow("测试图片", testImage);
	std::cout << "宽" << testImage.cols << "  高" << testImage.rows << std::endl;
	Mat hand_feature;
	hand_feature = testImage(Rect(115, 155, 335, 150)).clone();//从加载图像中提取感兴趣（ROI）部分作为特征图像，用作以后的匹配
	
	imshow("hand_feature", hand_feature);
	
	
	std::cout << "11\n";
	std::vector<Mat>bgr_plane;
	split(hand_feature, bgr_plane);
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float*ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat h_hist;

	calcHist(&bgr_plane[0], 1,0, Mat(), b_hist, 1, bins, ranges);//计算蓝色通道直方图
	normalize(b_hist, b_hist, 1.0, 0);
	
	
	//反向投影
	std::vector<Mat>bgr;
	split(testImage, bgr);
	Mat result;
	calcBackProject(&bgr[0], 1, channels, b_hist, result, ranges, 255);//输出的目标result是单通道图像
	//将结果进行阈值化
	threshold(result, result, 255 * 0.1, 255, THRESH_BINARY);//二值化
	imshow("histogram Back Project Result", result);
	//imwrite("E:/picture/recognition.jpg", result);

}
//25、图像卷积模糊
void Pixel_Demo::blur_demo(Mat&image) {
	Mat dst;
	blur(image, dst, Size(5, 5), Point(-1, -1));//Point代表卷集核替换重叠像素中的那个位置，Point（-1，-1）指用卷集核代替中心位置
	imshow("卷积模糊图像", dst);
}
//26、高斯模糊
void Pixel_Demo::gaussian_blur_demo(Mat&image) {
	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 15);//Size(0,0)也可以模糊，必须是奇数，但窗口不是0，是通过通过sigma反计算（Size也可以计算sigma的值），越大模糊程度更明显
	//sigmaX表示高斯方程中的x方向的标准差，当sigmaX=sigmaY时可设置一个参数
	imshow("高斯模糊", dst);
}
//27、高斯双边模糊(空间邻近度和像素值相似度的一种折中处理)
void Pixel_Demo::bifilter_demo(Mat&image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	//表示在过滤过程中每个像素邻域的直径范围。如果这个值是非正数，则函数会从第五个参数sigmaSpace计算该值 
	//double sigmaColor：颜色空间过滤器的sigma值，这个参数的值月大，表明该像素邻域内有月宽广的颜色会被混合到一起，产生较大的半相等颜色区域 
	//double sigmaSpace：坐标空间中滤波器的sigma值，如果该较大，则意味着颜色相近的较远的像素将相互影响，从而使更大的区域中足够相似的颜色获取相同的颜色。当d > 0时，d指定了邻域大小且与sigmaSpace五官，否则d正比于sigmaSpace。
	imshow("双边模糊", dst);
}