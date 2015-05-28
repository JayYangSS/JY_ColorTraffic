#include "std_tlr.h"

//bool detectBox(IplImage *GrayImage,CvRect iRect,int Color)

void detectBox(IplImage *InputImage,CvRect iRect)
{
	/*int X=iRect.x+iRect.width/2;
	int Y=iRect.y+iRect.height/2;
	unsigned char* pImageData = (unsigned char*)GrayImage->imageData;//imageData是指向图像数据区域首地址的指针，类型为char*！！！*/
	
	cvSetImageROI(InputImage,iRect);
	IplImage *ROI=cvCreateImage(cvGetSize(InputImage),InputImage->depth,InputImage->nChannels);
	cvCopy(InputImage,ROI,NULL);
	IplImage *GrayImage=cvCreateImage(cvGetSize(InputImage),InputImage->depth,1);
	
	cvCvtColor(InputImage,GrayImage,CV_RGB2GRAY);
	IplImage *X_gradient=cvCreateImage(cvGetSize(InputImage),InputImage->depth,1);
	IplImage *Y_gradient=cvCreateImage(cvGetSize(InputImage),InputImage->depth,1);
	IplImage *Ang=cvCreateImage(cvGetSize(InputImage),InputImage->depth,1);
	IplImage *Magnitude=cvCreateImage(cvGetSize(InputImage),InputImage->depth,1);
	//IplImage *GrayImage=cvCreateImage(cvGetSize(InputImage),InputImage->depth,1);
 

//	if(Color==GREEN_PIXEL_LABEL)
	//{
		//在x-2r，y-6r到x+2r到y+2r区域之间操作
		/*int Xstart=X-iRect.width;
		int Ystart=Y-3*iRect.height;
		int Xend=X+iRect.width;
		int Yend=Y+iRect.height;*/
		
		cvSobel(GrayImage,X_gradient,1,0,3);
		cvSobel(GrayImage,Y_gradient,0,1,3);
		//cvCartToPolar(X_gradient,Y_gradient,Magnitude,Ang);

		cvShowImage("X_gradient",X_gradient);
		cvShowImage("Y_gradient",Y_gradient);
//	}

	/*if(Color==RED_PIXEL_LABEL)
	{
		//在x-2r，y-2r到x+2r到y+6r区域之间操作
	}*/
	cvReleaseImage(&X_gradient);
	cvReleaseImage(&Y_gradient);
}