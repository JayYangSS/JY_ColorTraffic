#include "std_tlr.h"

#define SPECIAL_CASE 1 // "SPECIAL_CASE=0" means dealing with the lara video sequence


//
// function "colorSegmentation":
// color segmentatin using the hsi color model on the source image to extract the blob pixels 
//
IplImage* HSV_view(IplImage* inputImage,int flagHSV)
{

	int colorB,colorG,colorR;
	int colorH,colorS,colorI;
	int iWidth = inputImage->width;
	int iHeight = inputImage->height;
	int iInWidthStep = inputImage->widthStep;

	IplImage* imageSeg = cvCreateImage(cvSize(iWidth,iHeight),IPL_DEPTH_8U,1);
	//IplImage* imageSeg2 = cvCreateImage(cvSize(iWidth,iHeight),IPL_DEPTH_8U,1);

	if(!imageSeg)
		exit(EXIT_FAILURE);
	int iOutWidthStep = imageSeg->widthStep;//widthStep 表示存储一行像素所需的字节数

	unsigned char* in = (unsigned char*)inputImage->imageData;
	unsigned char* out =  (unsigned char*)imageSeg->imageData;

	for(int j=0; j<iHeight; j++){
		in = (unsigned char*)inputImage->imageData + j*iInWidthStep;
		out = (unsigned char*)imageSeg->imageData + j*iOutWidthStep;
		if(j<=ROIHeight)
			for(int i=0; i<iWidth; i++){
				colorB = in[3*i];
				colorG = in[3*i+1];
				colorR = in[3*i+2];
				rgb2hsi(colorR,colorG,colorB,colorH,colorS,colorI);
			if(flagHSV==1)
				out[i]=colorH;
			if(flagHSV==2)
				out[i]=colorS;
			if(flagHSV==3)
				out[i]=colorI;
			}
	}

	return imageSeg;
}




