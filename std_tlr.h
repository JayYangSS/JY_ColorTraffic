#ifndef STD_TLR_H
#define STD_TLR_H


//#pragma comment(lib,"cxcore")
//#pragma comment(lib,"cv")
//#pragma comment(lib,"ml")
//#pragma comment(lib,"cvaux")
//#pragma comment(lib,"highgui")

//#pragma comment(lib,"FlyCapture2")
//#pragma comment(lib,"FlyCapture2GUI")
//#pragma comment(lib,"FlyCapture2GUId")
#pragma comment(lib,"ws2_32.lib")



//#pragma warning(once:4819)
#pragma warning(disable:4819)

#include<WinSock2.h>//放最前面
//#include<cv.h>
//#include<highgui.h>

//#include <FlyCapture2.h>
#include<opencv2\opencv.hpp>
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include <time.h>

#include <tchar.h>

#include <string>


#define TEST 0

#define PI 3.1415

#define GREEN_PIXEL_LABEL 255
#define RED_PIXEL_LABEL 128
#define NON_BLOB_PIXEL_LABEL 0

//#define ROIHeight	140  //only image (image.y<ROIHeight) is processed in color segmentation
//#define ROIWidth	140  //only image (image.x>ROIHeight) is processed in color segmentation
#define ROIHeight 500
#define	ROIWidth 0


//int* test_HSV(IplImage* inputImage);
//void detectBox(IplImage *GrayImage);
void rgb2hsi(int red, int green, int blue, int& hue, int& saturation, int& intensity );
//IplImage* HistoEqualize(IplImage* InputImg);
IplImage* HSV_view(IplImage* inputImage,int flagHSV);
//IplImage* Gauss_colorSeg(IplImage* inputImage);
IplImage* colorSegmentation(IplImage* inputImage);
//void colorSegmentation(IplImage* inputImage,IplImage *imageSeg);
IplImage* topHatExtraction(IplImage* inputImage);
IplImage* noiseRemoval(IplImage* inputImage);
IplImage* noiseRemoval2(IplImage* inputImage);
IplImage* fixImage(IplImage* colorseg,IplImage* tophat);
void componentExtraction(IplImage* inputImage, IplImage* srcImage,int* p);
bool sizeFiltering(CvRect rect);
bool regionGrowFiltering(IplImage* inputImage,IplImage*colorSeg,CvRect iRect,CvRect& oRect);
bool rectangleDetection(IplImage* inputImage,IplImage* srcImage,CvRect iRect,int iColor,int* p1,int* p2);

using namespace std;
using namespace cv;

#define PosSamNO    523 //正样本个数
#define HORZ_PosSamNO    36 //正样本个数
#define NegSamNO 2574   //负样本个数
#define HORZ_NegSamNO 2416
#define HardExampleNO 334
#define HORZ_HardExampleNO 23
void hogSVMTrain(HOGDescriptor &myHOG,bool TRAIN,bool HORZ);
bool BoxDetect(Mat src_test,HOGDescriptor &myHOG,vector<Rect> &found_filtered,bool HORZ);

class MySVM : public CvSVM
{
public:
	//获得SVM的决策函数中的alpha数组
	double * get_alpha_vector()
	{
		return this->decision_func->alpha;
	}

	//获得SVM的决策函数中的rho参数,即偏移量
	float get_rho()
	{
		return this->decision_func->rho;
	}
};



#endif