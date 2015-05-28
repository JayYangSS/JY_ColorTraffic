
#include "std_tlr.h"

//
// function "topHatExtraction":
// applying the tophat morphology on the source image to extract the blob pixels 
//
IplImage* topHatExtraction(IplImage* inputImage)
{
	int iWidth = inputImage->width;
	int iHeight = inputImage->height;

	IplImage* imageGrayScale = cvCreateImage(cvSize(iWidth,iHeight),IPL_DEPTH_8U,1);
	if(!imageGrayScale)
		exit(EXIT_FAILURE);

	cvCvtColor(inputImage,imageGrayScale,CV_BGR2GRAY);
	cvShowImage("Gray",imageGrayScale);
	cvWaitKey(2);
	IplImage* imageTopHat = cvCreateImage(cvSize(iWidth,iHeight),IPL_DEPTH_8U,1);
	if(!imageTopHat)
		exit(EXIT_FAILURE);

	IplConvKernel* structureEle =cvCreateStructuringElementEx(
		11,
		11,
		5,
		5,
		CV_SHAPE_ELLIPSE,
		0);

	cvMorphologyEx(imageGrayScale,imageTopHat,NULL,structureEle,CV_MOP_TOPHAT,1);
	
	//applying thresholding to extract binary image, in which 255 represents the blob pixels
	cvThreshold(imageTopHat,imageTopHat,128,255,CV_THRESH_BINARY);

	cvReleaseStructuringElement(&structureEle);

	cvReleaseImage(&imageGrayScale);

	return imageTopHat; 
}