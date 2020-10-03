#include<drawing.h>


//*1��ͼ����ɫת��**/
void Pixel_Demo::colorSpace_Demo(Mat&image) {
	Mat gray, hsv;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	cvtColor(image, hsv, COLOR_BGR2HSV);
	namedWindow("�Ҷ�", WINDOW_NORMAL);//�ɵ������ڴ�С
	namedWindow("hsv", WINDOW_NORMAL);
	imshow("�Ҷ�", gray);
	imshow("hsv", hsv);
	//imwrite("E:/picture/hsv.jpg", gray);
	//imwrite("E:/picture/hsv.jpg", hsv);
}
//*2������ͼƬ*/
void Pixel_Demo::mat_creation(Mat&image) {
	Mat m1, m2;
	m1 = image.clone();
	image.copyTo(m2);

	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC3);
	std::cout << "width:" << m3.cols << "  hight:" << m3.rows << "  channel:" << m3.channels() << std::endl;
	m3 = Scalar(0, 225, 0);
	imshow("�´�ͼƬ", m3);
}
//*3��ͼ�����ض�ȡ/**/
void Pixel_Demo::Pixel_visit_Demo(Mat&image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	/**�������
	for (int row = 0; row < h; row++){
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//�Ҷ�ͼ��
				int pv = image.at<uchar>(row, col);
				image.at<uchar>(row, col) = 255 - pv;

			}
			if (dims == 3) {//��ɫͼ��
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];


			}
		}

}*/

/**ָ�����**/
	for (int row = 0; row < h; row++) {
		uchar* current_row = image.ptr(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//�Ҷ�ͼ��
				int pv = *current_row;
				*current_row++ = 255 - pv;

			}
			if (dims == 3) {//��ɫͼ��
				*current_row++ = 255 - *current_row;//++��������ȼ�����ָ�룿��
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;


			}
		}

		imshow("���ض�д��ʾ", image);
	}
}

//4��ͼ��������������*/
void Pixel_Demo::operators_Demo(Mat&image) {
	Mat dst1 = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(50, 50, 50);
	/**
	//dst1 = image + Scalar(50, 50, 50);  //�ɽ��мӼ�������
	//dst1 = image - Scalar(100, 100, 100);
	dst1 = image / Scalar(2, 2, 2);
	//dst1 = image * Scalar(1.1, 1.1, 1.1);//ûʵ��
	//imshow("�ӷ�����",dst1);
	//imshow("��������",dst1);
	imshow("��������", dst1);
	//imshow("�˷�����", dst1);
	*/
	/**�ú���ʵ�ּӼ��˳�*/
	//add(image, m, dst1);
	//subtract(image, m, dst1);
	//multiply(image, m, dst1);
	divide(image, m, dst1);
	imshow("����������", dst1);
}
//5���������������ȵĻص�����*/
static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst1 = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0, b, dst1);
	imshow("������Աȶȵ���", dst1);
}
static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst1 = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst1);  //�Աȶȵ��������ǰ�ÿ������������һ����ֵͬ������������ز�ֵ������
	imshow("������Աȶȵ���", dst1);				//�����ȵ�������ÿ�����ص㶼����һ����ͬ��ֵ��Ҫ��ÿ���㶼��
}
//5����������������*/
void Pixel_Demo::track_bar_demo(Mat&image) {
	namedWindow("������Աȶȵ���", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_vaule = 100;

	createTrackbar("Value Bar", "������Աȶȵ���", &lightness, max_value, on_lightness, (void*)(&image));
	//��һ��������trackbar���ڴ���������������ƣ��ڶ�����Ҫ����ͼ�񴰿ڵ����ƣ���������Ҫͨ��
	//trackbar���ı�ĳ�ʼֵλ�ã����ĸ��Ǹı�����ֵ,�������Ӧ�������������ص�����:�ص�������ͨ������ָ����õĺ������Ѻ�����ָ�루��ַ����Ϊ�������ݸ���һ�������������ָ�뱻������������ָ��ĺ���ʱ���ͳ���Ϊ�ص�������
	//�������������û����ص�����������
	createTrackbar("Contrast Bar", "������Աȶȵ���", &contrast_vaule, 200, on_contrast, (void*)(&image));
	on_contrast(50, &image);
}
/*6��������Ӧ**/
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
		imshow("ת��Ϊ�Ҷ�", dst);
		std::cout << c << std::endl;


	}

}
/*7����ɫ����ʾ��ͬ�˾���Ч��**/
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
		namedWindow("��ɫ���", WINDOW_NORMAL);
		imshow("��ɫ���", dst);
	}
	{

	}
}
/*8�������߼�������ͼƬ�ϻ��ƾ��Σ�**/
void Pixel_Demo::bitwise_demo(Mat&image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);//���ĸ���������0�����ƣ�С��0���
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst;
	//bitwise_and(m1,m2, dst);
	//bitwise_not(image, dst);   //��ֱ��ִ�� Mat dst = ~image
	bitwise_xor(m1, m2, dst);
	imshow("�߼�����", dst);
}
/*9��ͨ������ϲ�*/
void Pixel_Demo::channels_demo(Mat&image) {

	//ͨ������
	std::vector<Mat> mv;//����һ����Ϊmv��vector����mv�д洢����ΪMat
	split(image, mv);   //�������ֵ����mv�У��൱���ʼ����mv

	Mat dst;
	/**��ɫ
	mv[1] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("��ɫ",dst);
	**/
	/**��ɫ
	mv[0] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("��ɫ", dst);
	**/
	/**�ص���һ��ͨ��
	mv[0] = 0;
	merge(mv, dst);
	imshow("�ص���һ��ͨ��", dst);
	**/

	mv[0] = 0;
	mv[1] = 0;
	merge(mv, dst);
	imshow("��ɫ", dst);

	int from_to[] = { 0,2,1,1,2,0 };// ͨ�����ཻ����0-2,1-1,2-0
	int from_to1[] = { 0,1,1,0,2,2 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	mixChannels(&image, 1, &image, 1, from_to1, 3);
	imshow("ͨ���໥����", dst);
	imshow("ͨ���໥����1", image);
}
/*10��ͼ�񱳾��л�*/
void Pixel_Demo::inrange_demo(Mat&image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);//mask��Ϊ��ֵͼ��Ұף���ɫҲ�ǻ�ɫ��
	//ͨ�׵�������������������ж�hsv��ÿһ�������Ƿ���[lowerb��upperb]֮�䣬ע�⼯�ϵĿ��ա�
	//������Ϊ�ǣ���ô��hsv��Ӧ����λ������255��(����ɫΪ��ɫ)��֮����0������ɫΪ��ɫ����һ�����ǰ�hsv����һ��mask���ã�
	//inrange�������������ɫ��������ɫ����Ϊ��ɫ������Ϊ��ɫ

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(0, 0, 255);
	bitwise_not(mask, mask);//����Ҫ����ɫ��Ϊ��ɫ
	imshow("mask", mask);
	image.copyTo(redback, mask);//��ԭͼ���Ƶ�redback�ϣ����Ǻ�ɫ���ֲ�Ҫ����Ϊ��ʱ��maskͼƬ��ֻ�кڰ���ɫ�������˴�Ϊ��ɫ
	imshow("��ɫ����", redback);

}
/*11��ͼ������ͳ��*/
void Pixel_Demo::pixel_statistic_demo(Mat&image) {
	double minv, maxv;  //�������ֵ����Сֵ
	Point minloc, maxloc;//���ֵλ�ã���Сֵλ��
	std::vector<Mat>mv;
	split(image, mv);
	Mat mean, stddev;
	for (int i = 0; i < mv.size(); i++) {

		minMaxLoc(mv[i], &minv, &maxv, &minloc, &maxloc);//����Ҫ���ǵ�ͨ���������������ֵ��Сֵ
		std::cout << "No.channels#" << i << " min value:  " << minv << " max value:  " << maxv << std::endl;
		meanStdDev(mv[i], mean, stddev);//�������ؾ�ֵ�ͱ�׼����
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
/*12��ͼ�λ���*/
void Pixel_Demo::drawing_demo(Mat &image) {
	Rect rect;
	rect.x = 160;
	rect.y = 150;
	rect.width = 150;
	rect.height = 150;
	Mat bg = Mat::zeros(image.size(), image.type());
	//rectangle(bg, rect, Scalar(0, 0, 255), 2, 8, 0);
	rectangle(bg, rect, Scalar(0, 0, 255), 2, 8, 0);//thickness���������������>0��ߣ�<0���,����0ʱ��ֵԽ����Խ��
	circle(bg, Point(310, 300), 20,Scalar(0,255,0), 2, 8, 0);
	line(bg, Point(160, 150), Point(310, 300), Scalar(0, 255, 0), 2, LINE_AA, 0);//LINE_AA�����
	RotatedRect rrt;
	rrt.center = Point(200, 200);
	rrt.size = Size(100, 200);
	rrt.angle = 0.0;
	ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8 );
	Mat dst;
	addWeighted(image, 0.3, bg, 0.7, 0, dst);//ͼ�񰴱�������
	
	imshow("������ʾ",dst);


}
/*13��������������������ͼ��*/
void Pixel_Demo::random_demo() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3); //����һ�Ż���
	int w = canvas.cols;
	int h = canvas.rows;
	RNG rng(12345);				//���������������
	while (true) {
		int c = waitKey(10);
		if (c == 27) {
			break;
		}					//һ������һ�ַ����Ƴ��� ѭ��������ͨ������esc�˳�ѭ��

		int x1 = rng.uniform(0, w);//�������0~w֮�������wΪ�����Ŀ�ȣ�x1Ϊ��Ҫ������ߵ���������
		int y1 = rng.uniform(0, h);//�������0~h֮�������hΪ�����ĸ߶ȣ�y1Ϊ��Ҫ������ߵ����������
		int x2 = rng.uniform(0, w);//�������0~w֮�������wΪ�����Ŀ�ȣ�x2Ϊ��Ҫ������ߵ��յ������
		int y2 = rng.uniform(0, h);//�������0~h֮�������wΪ�����ĸ߶ȣ�x2Ϊ��Ҫ������ߵ��յ�������
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		canvas = Scalar(0, 0, 0);//��ÿ�λ���һ���ߺ���ɫ��0��Ҳ���Ǳ�Ϊ��ɫ���ͳ�ʼ������ɫһ��
		//line(canvas, Point(x1,y1), Point(x2,y2), Scalar(b,g,r), 2, 8, 0);
		//rectangle(canvas, Point(x1,y1), Point(x2,y2), Scalar(b,g,r), 2, 8, 0);
		circle(canvas, Point(x1,y1), rng.uniform(0,512), Scalar(b, g, r), 2, 8, 0);
		imshow("���������ʾ",canvas);

	}
	
}
/*14�����ƶ���β����*/
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

	std::vector<Point>pts1(5);//�����Ҫͨ�����鷽ʽ��ֵ������Ҫ��(5);
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

	std::vector<Point>pts2(5);//�����Ҫͨ�����鷽ʽ��ֵ������Ҫ��(5);
	pts2[0] = p12;
	pts2[1] = p22;
	pts2[2] = p32;
	pts2[3] = p42;
	pts2[4] = p52;

	std::vector<Point>pts3(3);
	pts3[0] = p6;
	pts3[1] = p7;
	pts3[2] = p8;

	//fillPoly(canvas, pts1, Scalar(255, 255, 0), 8, 0);//  ���
	//polylines(canvas, pts1, true, Scalar(0, 0, 255), 2, LINE_AA, 0);  //�˺�����������䣬Ҳ���ǲ�����ֱ�Ӱ�2������thickness���ĳɸ���
	std::vector<std::vector<Point>>contours(3);
	contours[0] = pts1;
	contours[1] = pts2;
	contours[2] = pts3;
	for (int i = 0; i < contours.size(); i++) {
	drawContours(canvas, contours, i, Scalar(150, 0, 0), -1,8);//�˺�����ֱ�����
     imshow("����λ���", canvas);
	}
	
}
/*15�������Ӧ���ƾ��Σ�����ȡ��������*/
Point sp(-1, -1);//����ʼλ��
Point ep(-1, -1);//������λ��
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
			temp.copyTo(image);//�����ƶ��ۼ�����ԭͼ����
			imshow("������", image);
			imshow("RIO", image(box));
			temp2 = image(box);
			//Ϊ��һ�λ�������׼��
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
				temp.copyTo(image);//�����ƶ��ۼ�����ԭͼ����
				/*
				center.x = (sp.x < ep.x ? sp.x + abs(ep.x - sp.x) : ep.x + abs(ep.x - sp.x));
				center.y = (sp.y < ep.y ? ep.y + abs(ep.y - sp.y) : ep.y + abs(ep.y - sp.y));
				radius = std::sqrt((ep.x - sp.y)*(ep.x - sp.x) + (ep.y - sp.y)*(ep.y - ep.y)) / 2;
				circle(image, Point(center.x, center.y), radius, Scalar(0, 0, 255), 2, 8, 0);
				*/
				rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
				imshow("������", image);
			}
		}
	}
}
void Pixel_Demo::mouse_drawing_demo(Mat &image) {
	namedWindow("������", WINDOW_AUTOSIZE);
	setMouseCallback("������", on_draw,(void*)(&image));
	imshow("������", image);
	temp = image.clone();
	
}/*16��ͼ����������ת������һ��*/

void Pixel_Demo::norm_demo(Mat&image) {
	Mat dst;
	
	std::cout << image.type() << std::endl;
    image.convertTo(image, CV_32F);//converTo(Ŀ�ģ����ͣ��������ӣ����ֵ)
	//src.convertTo(dst, type, scale, shift)  dst(i)=src(i)xscale+(shift,shift,...)
	std::cout << image.type() << std::endl;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);//��һ��
	std::cout << dst.type() << std::endl;
	//imshow("ͼ�����ݹ�һ��", dst);
	dst.convertTo(dst, CV_8UC3, 255);
	std::cout << dst.type() << std::endl;
	imshow("ͼ�����ݹ�һ��", dst);
}
/*17��ͼ������*/
void Pixel_Demo::resize_demo(Mat&image) {
	Mat zoomin, zoomout1,zoomout2,zoomout3;
	int h = image.rows;
	int w = image.cols;
	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);//˫���Բ�ֵ
	resize(image, zoomout1, Size(w*1.5, h*1.5), 0, 0, INTER_NEAREST);//���ڽ���ֵ
	resize(image, zoomout2, Size(w * 1.5, h * 1.5), 0, 0, INTER_LINEAR);//˫���Բ�ֵ
	resize(image, zoomout3, Size(w * 1.5, h * 1.5), 0, 0, INTER_CUBIC);//˫���������ξ�����Բ�ֵ
	
	//imshow("zoomin", zoomin);
	imshow("zoomout1", zoomout1);
	imshow("zoomout2", zoomout2);
	imshow("zoomout3", zoomout3);
}
/*18��ͼ����*/
void Pixel_Demo::flip_demo(Mat&image) {
	Mat dst;
	flip(image, dst, 0);//0���·�ת
	//flip(image, dst, 1);//���ҷ�ת
	//flip(image, dst, -1);//�ԽǷ�ת����ת180
	imshow("ͼ��ֱ����", dst);

}
/*19��/ͼ����ת*/
void Pixel_Demo::rotate_demo(Mat&image) {
	Mat dst, M;
	int w = image.rows;
	int h = image.cols;
	//M ��������ת�任��˵ľ���
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);//Point2fԭͼ������ģ���ת�Ƕȣ����ű���
	/*
	M= [cosa  sina 0]
	   [-sina cosa 0]
 	*/
	//�����֪ԭͼ��Ŀ��ͼ�ɸ�ȡ���㣬�ú���getAffineTransform( srcTri, dstTri )�����任����M
	std::cout << M << std::endl;

	double cos = abs(M.at<double>(0, 0));
	double sin= abs(M.at<double>(0, 1));
	int nw = cos*w + sin * h;//�»����Ŀ�
	int nh = sin * w + cos * h;//�»����ĸ�
	M.at<double>(0, 2) += (nw / 2 - w / 2);//��ͼ���Ƶ�����
	M.at<double>(1, 2) += (nh / 2 - h / 2);

	warpAffine(image, dst, M,Size(nw,nh),INTER_LINEAR,0,Scalar(255,255,255));
	
	imshow("��תͼ��", dst);
}
/*20������ͷ����Ƶ������**��Ƶ������ͼ���ܶ�ͼ��Ĳ���ͬ����������Ƶ*/
void Pixel_Demo::video_demo(Mat&image) {
	VideoCapture capture(0);//0Ϊ����ͷ
	//VideoCapture capture("E:/picture/normal-angle.mp4");
    int  frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//��
	int  frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);//��
	int  count = capture.get(CAP_PROP_FRAME_COUNT);//��֡��
	double fps = capture.get(CAP_PROP_FPS);//һ�벥�ŵ�֡��
	int fourcc = capture.get(CAP_PROP_FOURCC);//��Ƶ����
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
		flip(frame, frame, 1);//���ֱ�Ӽ�����������ͷ����Ҫ��ת�ɾ���

		//colorSpace_Demo(frame);//����֮ǰ�����ı���Ƶ����ɫ
		//color_style_demo(frame);//���ú���ѭ���ı���ɫ,��Ƶû���ţ�����
		//writer.write(frame);
		namedWindow("frame", WINDOW_NORMAL);
		imshow("frame", frame);
		int c = waitKey(30);
		if (c == 27) {
			break;
		}

	}
	capture.release();//�������ͷռ��
	writer.release();
	
}
//21������һάֱ��ͼ
void Pixel_Demo::histogram_demo(Mat &image) {
	// ��ͨ������
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	// �����������
	const int channels[1] = { 0 };//��Ҫ����ͼ����ĸ�ͨ����bgr�ռ���Ҫȷ������ b��g��r�ռ䣩
	const int bins[1] = { 256 };//ֱ��ͼ��ÿһ��ά�ȵ� ��������Ŀ�����ǽ��Ҷȼ����飩
	float hranges[2] = { 0,255 };//����һ�����������洢 ����ά�� ����ֵ��ȡֵ��Χ
	const float* ranges[1] = { hranges };//ȷ��ÿ��ά�ȵ�ȡֵ��Χ��
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// ����Blue, Green, Redͨ����ֱ��ͼ
	/*&rgb_planes[0]: ��������(�����鼯)
	1: ��������ĸ��� (��������ʹ����һ����ͨ��ͼ������Ҳ�����������鼯 )
	0: ��Ҫͳ�Ƶ�ͨ�� (dim)���� ����������ֻ��ͳ���˻Ҷ� (��ÿ�����鶼�ǵ�ͨ��)����ֻҪд 0 �����ˡ�
	Mat(): ����( 0 ��ʾ���Ը�����)�� ���δ���壬��ʹ������
	r_hist: ����ֱ��ͼ�ľ���
	1: ֱ��ͼά��
	histSize: ÿ��ά�ȵ�bin��Ŀ
	histRange: ÿ��ά�ȵ�ȡֵ��Χ
	uniform �� accumulate: bin��С��ͬ�����ֱ��ͼ�ۼ�*/
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	std::cout << "b_hist" << b_hist << std::endl;//b_hist�洢����ÿ������ֵ�ĸ���
	// ��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);//cvRound��������ȡ����ֱ��ͼ�ĵȼ���������ȳ���bins���Ҷȵȼ�������
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	// ��һ��ֱ��ͼ����
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());//0,histImage�ǹ�һ���������ޣ�Ϊ�˻��Ƶ�ֱ��ͼ�����������Ŀ�
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	// ����ֱ��ͼ����
	//bin_w��ÿ�����ص����䣬һ����ռ�ĺ�����̶�ֵ���ڼ�����ĺ�������ǵڼ������һ����ÿ����ռ�����伴���ʽ��
	//(i-1)*bin_w,���������ǣ�����ȡ��֮ǰ����ֱ��ͼ�������b_hist.at<float>(i-1),����ֱ��ͼ����������Ϊ��
	//����Ҫ�û����߶ȼ�ȥ���ֵ
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
//22�����ƶ�άֱ��ͼ
void Pixel_Demo::histogram_2d_demo(Mat &image) {
	// 2D ֱ��ͼ
	//��1������ԭͼ,ת��ΪHSV��ɫģ��
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	//��2������׼��
	//��ɫ������Ϊ30���ȼ��������Ͷ�����Ϊ32���ȼ�
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins, sbins };
	//����仯��Χ
	float h_range[] = { 0, 179 };//����ɫ���ı仯��ΧΪ0-179
	float s_range[] = { 0, 255 };//���履�Ͷȵı仯��ΧΪ0-255
	const float* hs_ranges[] = { h_range, s_range };

	int hs_channels[] = { 0, 1 };//calcHist�����н������0ͨ���͵�1ͨ����ֱ��ͼ
	//�������飬�������Ϊ1��ͨ����������ʹ����ģ�����Ŀ��ֱ��ͼ����Ҫ�����ֱ��ͼά��Ϊ2�����ÿ��ά�ȵ�ֱ��ͼ�ߴ�����飬ÿһά�����ȡֵ��Χ���飬ָʾֱ��ͼ���ȣ�ֱ��ͼ�����ý׶λᱻ����
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	//��4������ֱ��ͼ׼������
	double maxVal = 0;//���ֵ
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);//����������������ȫ�����ֵ����maxValue��
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins*scale, hbins * scale, CV_8UC3);
	for (int h = 0; h < hbins; h++) {
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);//ͳ�Ƹ�����ֵ���ŵ�[0,255]��Χ����ǿ���ӻ�
			//����32*30��10*10???��С�ľ���С�飬����С��ĻҶ�ֵ����ͳ�Ƹ���
			rectangle(hist2d_image, Point(h*scale, s*scale),
				Point((h + 1)*scale-1 , (s + 1)*scale-1 ),
				Scalar::all(intensity),
				-1);
			//Scalar::all(intensity)��ÿ��ͨ������intensity
		}
	}
	applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);
	imshow("H-S Histogram", hist2d_image);
	imwrite("D:/hist_2d.png", hist2d_image);
}
//23��ֱ��ͼ���⻯
void Pixel_Demo::histogram_eq_demo(Mat&image) {
	//��ͨ��ֱ��ͼ���⻯
	/*
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("�Ҷ�", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("ֱ��ͼ���⻯",dst);
*/
	//��ɫֱ��ͼ���⻯
	std::vector<Mat>bgr_plane(3);
	split(image, bgr_plane);
	std::vector<Mat>dst_bgr(3);
	equalizeHist(bgr_plane[0], dst_bgr[0]);
	equalizeHist(bgr_plane[1], dst_bgr[1]);
	equalizeHist(bgr_plane[2], dst_bgr[2]);
	Mat dst = Mat::zeros(bgr_plane[0].size(), CV_8UC3);
	merge(dst_bgr, dst);
	imshow("��ɫͼ����⻯",dst);
 }

//24��ֱ��ͼ����ͶӰ������ʶ��
void Pixel_Demo::calcbackproject_demo(Mat&image) {
	Mat testImage = imread("E:/picture/recognition.jpg");
	
	if (testImage.empty()) {
		std::cout << "colud not load test iamge \n";
		return ;
	}
	imshow("����ͼƬ", testImage);
	std::cout << "��" << testImage.cols << "  ��" << testImage.rows << std::endl;
	Mat hand_feature;
	hand_feature = testImage(Rect(115, 155, 335, 150)).clone();//�Ӽ���ͼ������ȡ����Ȥ��ROI��������Ϊ����ͼ�������Ժ��ƥ��
	
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

	calcHist(&bgr_plane[0], 1,0, Mat(), b_hist, 1, bins, ranges);//������ɫͨ��ֱ��ͼ
	normalize(b_hist, b_hist, 1.0, 0);
	
	
	//����ͶӰ
	std::vector<Mat>bgr;
	split(testImage, bgr);
	Mat result;
	calcBackProject(&bgr[0], 1, channels, b_hist, result, ranges, 255);//�����Ŀ��result�ǵ�ͨ��ͼ��
	//�����������ֵ��
	threshold(result, result, 255 * 0.1, 255, THRESH_BINARY);//��ֵ��
	imshow("histogram Back Project Result", result);
	//imwrite("E:/picture/recognition.jpg", result);

}
//25��ͼ����ģ��
void Pixel_Demo::blur_demo(Mat&image) {
	Mat dst;
	blur(image, dst, Size(5, 5), Point(-1, -1));//Point��������滻�ص������е��Ǹ�λ�ã�Point��-1��-1��ָ�þ��˴�������λ��
	imshow("���ģ��ͼ��", dst);
}
//26����˹ģ��
void Pixel_Demo::gaussian_blur_demo(Mat&image) {
	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 15);//Size(0,0)Ҳ����ģ���������������������ڲ���0����ͨ��ͨ��sigma�����㣨SizeҲ���Լ���sigma��ֵ����Խ��ģ���̶ȸ�����
	//sigmaX��ʾ��˹�����е�x����ı�׼���sigmaX=sigmaYʱ������һ������
	imshow("��˹ģ��", dst);
}
//27����˹˫��ģ��(�ռ��ڽ��Ⱥ�����ֵ���ƶȵ�һ�����д���)
void Pixel_Demo::bifilter_demo(Mat&image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	//��ʾ�ڹ��˹�����ÿ�����������ֱ����Χ��������ֵ�Ƿ�������������ӵ��������sigmaSpace�����ֵ 
	//double sigmaColor����ɫ�ռ��������sigmaֵ�����������ֵ�´󣬱������������������¿�����ɫ�ᱻ��ϵ�һ�𣬲����ϴ�İ������ɫ���� 
	//double sigmaSpace������ռ����˲�����sigmaֵ������ýϴ�����ζ����ɫ����Ľ�Զ�����ؽ��໥Ӱ�죬�Ӷ�ʹ������������㹻���Ƶ���ɫ��ȡ��ͬ����ɫ����d > 0ʱ��dָ���������С����sigmaSpace��٣�����d������sigmaSpace��
	imshow("˫��ģ��", dst);
}