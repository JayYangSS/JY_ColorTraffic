#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"

#define PI 3.1415

using namespace cv;
//#define PIC_NUM 8
int test_HSV(IplImage* inputImage,int *outH,int *outS,int *outI,int *B,int *G,int *R);
int min(int size,int *p);
int max(int size,int *p);
void rgb2hsi(int red, int green, int blue, int& hue, int& saturation, int& intensity );
int main()
{
	
	IplImage *src=cvLoadImage("D:\\JY\\JY_TrainingSamples\\negetive1\\0.jpg");
	int H[10000],S[10000],I[10000],B[10000],G[10000],R[10000];
	int num=0;
	int size=test_HSV(src,H,S,I,B,G,R);
	int maxH=max(size,H);
	int minH=min(size,H);
	printf("maxH=%d,minH=%d\n",maxH,minH);

	int maxS=max(size,S);
	int minS=min(size,S);
	printf("maxS=%d,minS=%d\n",maxS,minS);

	int maxI=max(size,I);
	int minI=min(size,I);
	printf("maxI=%d,minI=%d\n",maxI,minI);

	int maxG=max(size,G);
	int minG=min(size,G);
	printf("maxG=%d,minG=%d\n",maxG,minG);

	int maxR=max(size,R);
	int minR=min(size,R);
	printf("maxR=%d,minR=%d\n",maxR,minR);

	system("pause");
}


int min(int size,int *p)
{
	int min=10000;
	for(int i=0;i<size-1;i++)
	{
		if(min>p[i])
			min=p[i];
	}
	return min;
}

int max(int size,int *p)
{
	int max=0;
	for(int i=0;i<size-1;i++)
	{
		if(max<p[i])
			max=p[i];
	}
	return max;
}

int test_HSV(IplImage* inputImage,int *outH,int *outS,int *outI,int *B,int *G,int *R)

{
	int num=0;
	int colorB,colorG,colorR;
	int colorH,colorS,colorI;
	int iWidth = inputImage->width;
	int iHeight = inputImage->height;
	int iInWidthStep = inputImage->widthStep;
	//int *out = new (int);
	unsigned char* in;

	for(int j=0; j<iHeight; j++)
	{
		
		in = (unsigned char*)inputImage->imageData + j*iInWidthStep;
		//if(j<=ROIHeight)
			for(int i=0; i<iWidth; i++)
			{
				colorB = in[3*i];
				colorG = in[3*i+1];
				colorR = in[3*i+2];
				rgb2hsi(colorR,colorG,colorB,colorH,colorS,colorI);
				B[j*iWidth+i]=colorB;
				G[j*iWidth+i]=colorG;
				R[j*iWidth+i]=colorR;
				outH[j*iWidth+i]=colorH;
				outS[j*iWidth+i]=colorS;
				outI[j*iWidth+i]=colorI;
				num++;

			}
	}

	return num;
}


void rgb2hsi(int red, int green, int blue, int& hue, int& saturation, int& intensity )
{
	double r,g,b;
	double h,s,i;

	double sum;
	double minRGB,maxRGB;
	double theta;

	r = red/255.0;
	g = green/255.0;
	b = blue/255.0;

	minRGB = ((r<g)?(r):(g));
	minRGB = (minRGB<b)?(minRGB):(b);

	maxRGB = ((r>g)?(r):(g));
	maxRGB = (maxRGB>b)?(maxRGB):(b);

	sum = r+g+b;
	i = sum/3.0;

	if( i<0.001 || maxRGB-minRGB<0.001 )
	{
		//this is a black image or grayscale image
		//in this circumstance, hue is undefined, not zero
		h=0.0;
		s=0.0;
		//return ;
	}
	else
	{
		s = 1.0-3.0*minRGB/sum;
		theta = sqrt((r-g)*(r-g)+(r-b)*(g-b));
		theta = acos((r-g+r-b)*0.5/theta);
		if(b<=g)
			h = theta;
		else 
			h = 2*PI - theta;
		if(s<=0.01)
			h=0;
	}

	hue = (int)(h*180/PI);
	saturation = (int)(s*100);
	intensity = (int)(i*255);
}