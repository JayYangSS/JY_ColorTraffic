
#include "std_tlr.h"
#include "math_utils.h"

Size Win_vertical(15,30),block_vertical(5,10),blockStride_vertical(5,5),cell_vertical(5,5);
HOGDescriptor myHOG_vertical(Win_vertical,block_vertical,blockStride_vertical,cell_vertical,9,1,-1.0,0,0.2,true,64);
HOGDescriptor myHOG_horz(Size(36,12),Size(12,6),Size(6,6),Size(6,6),9,1,-1.0,0,0.2,true,64);
vector<Rect> found_filtered;
bool TRAIN=false;
bool HORZ=false;
int Frame_pos;//��ǰ֡λ��
CvCapture *capture = NULL;
void On_Change(int n)
{
	cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,n);
}
void nhsSpaceTest();

int main()
{
	CvFont font; 
	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, .5, .5, 0, 1, 8);
	if(HORZ)
		hogSVMTrain(myHOG_horz,TRAIN,HORZ);
	else
		hogSVMTrain(myHOG_vertical,TRAIN,HORZ);
   
#ifdef IMG_PR0CESS
	
	int s=0;int i=0; int r=0;int g=0;int a[2]={0,0};
	int fc=0;float  tj=0; 
//	char c;

	IplImage *frame = NULL,*imageSeg=NULL,*imageNoiseRem =NULL;
	IplImage *tophat,*fix;
	CvSize cv_size;
	cv_size.height=480;
	cv_size.width=640;
	IplImage *resize_tmp=cvCreateImage(cv_size,8,3);
	cvNamedWindow("frame");
	char buff[100];
	//while(frame)
	for(int i=5200;i<6500;i++)
	{
		
		found_filtered.clear();
		int Start=cvGetTickCount();
		sprintf(buff,"D:\\JY\\JY_TrainingSamples\\Traffic Light Benchmark\\Lara_UrbanSeq1_JPG\\Lara3D_UrbanSeq1_JPG\\%d.jpg",i);
		frame=cvLoadImage(buff);
		cvResize(frame,resize_tmp);
		imageSeg = colorSegmentation(resize_tmp);
		imageNoiseRem = noiseRemoval(imageSeg);
		componentExtraction(imageNoiseRem,resize_tmp,a);
		cvShowImage("frame", resize_tmp);
		cvWaitKey(20);
		cvShowImage("NoiseRem",imageNoiseRem);
		cvWaitKey(20);
		cvReleaseImage(&imageSeg);//�����ں���colorSegmentation�л᲻ͣ��createImage�����ÿһ֡��Ҫ�ͷţ���Ȼ���ڴ�й¶
		cvReleaseImage(&imageNoiseRem);//�����ں���noiseRemoval�л᲻ͣ��createImage�����ÿһ֡��Ҫ�ͷţ���Ȼ���ڴ�й¶
		cvReleaseImage(&frame); //ʹ��cvLoadImageҲҪÿһ֡�ͷţ���Ȼ�ڴ�й¶��Ӧ����cvLoadImage����Ҳ�ڲ�ͣ��createImage�ɣ�
		cout << "Frame Grabbed." << endl;
		int End=cvGetTickCount();
		float time=(float)(End-Start)/(cvGetTickFrequency()*1000000);
		cout<<"ʱ�䣺"<<time<<endl;
	}
   
 //  cvReleaseCapture(&capture);
   cvReleaseImage(&resize_tmp);
   system("pause");

#else
	/*IplImage *frame = NULL,*imageSeg=NULL,*imageNoiseRem =NULL;
	IplImage *resize_tmp=cvCreateImage(Size(800,600),8,3);
	CvVideoWriter *writer=NULL;
	int isColor=1;
	int fps=10;
	int a[2]={0,0};
 
	
	writer=cvCreateVideoWriter("out3.avi",CV_FOURCC('X','V','I','D'),fps,Size(800,600),isColor);
	capture = cvCreateFileCapture("D:\\JY\\JY_TrainingSamples\\camera_clip1.avi");
	int frameFPS=cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
	int frameNUM=cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
	char Info[200];
	cvNamedWindow("resize_frame");
	cvCreateTrackbar("frame","resize_frame",&Frame_pos,frameNUM,On_Change);

	while (1)
	{
		int Start=cvGetTickCount();
		frame = cvQueryFrame(capture);
		if(!frame)break;


		found_filtered.clear();
		cvResize(frame,resize_tmp);
		imageSeg = colorSegmentation(resize_tmp);
		cvShowImage("imgseg",imageSeg);
		cvWaitKey(5);
		imageNoiseRem=noiseRemoval(imageSeg);
		componentExtraction(imageSeg,resize_tmp,a);

		int currentFrame=cvGetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES);
		sprintf(Info,"Total frames:%d,current frame:%d",frameNUM,currentFrame);
		cvRectangle(resize_tmp,Point(0,0),Point(resize_tmp->width,25),Scalar(0,0,0),CV_FILLED);
		cvPutText(resize_tmp,Info,Point(25,17),&font,Scalar(255,255,255));


		cvShowImage("resize_frame",resize_tmp);
		cvWaitKey(5);
		cvWriteFrame(writer,resize_tmp);
		cvReleaseImage(&imageSeg);
		cvReleaseImage(&imageNoiseRem);
		cout << "Frame Grabbed." << endl;
		int End=cvGetTickCount();
		float time=(float)(End-Start)/(cvGetTickFrequency()*1000000);
		cout<<"Time��"<<time<<endl;
		

	}
	cvDestroyAllWindows();
	cvReleaseCapture(&capture);
	cvReleaseImage(&resize_tmp);
	cvReleaseVideoWriter(&writer);*/
	nhsSpaceTest();
#endif
   return 0;
}

//����ɫ��ȡ���ֻ�Ϊʹ��nhs��ɫ�ռ䣬�������Ժͱ�־��ʹ��ͬ������ɫ�ռ䣬���ϵ�һ��
void nhsSpaceTest()
{
	Mat src,re_src;
	VideoCapture capture; 
	//capture.open("D:\\JY\\JY_TrainingSamples\\TrafficSignVideo\\trafficSign6.avi");
	capture.open("D:\\JY\\JY_TrainingSamples\\r+g.mp4");
	while(capture.read(src))
	{
		resize(src,re_src,Size(640,480));
		Mat ihls_image = convert_rgb_to_ihls(re_src);
		imshow("re_src",re_src);
		waitKey(5);
		//�Բ�ͬ��ɫ����NHS��ɫ�ռ�Ķ�ֵͼ���ȡ
		for (int mode=0;mode<4;mode++)
		{

			Mat nhs_image = convert_ihls_to_nhs(ihls_image,mode);//0:yellow,1:blue,2:red
			Mat noiseremove;
			//�ֱ���ʾ������ɫ��nhs��ֵͼ�� 
			stringstream ss;
			string index;
			ss<<mode;
			ss>>index;
			string tmp="nhs_image"+index;
			//�˲�
			medianBlur(nhs_image,noiseremove,3);
			imshow(tmp,noiseremove);
			waitKey(5);
		}
	}
}