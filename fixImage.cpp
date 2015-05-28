#include "std_tlr.h"
IplImage* fixImage(IplImage* colorseg,IplImage* tophat)
{
	unsigned char *in1,*in2,*out;
	int iwidth=colorseg->width;
	int iheight=colorseg->height;
	int tophat_width=tophat->width;
	int tophat_height=tophat->height;
	int iwidthStep=colorseg->widthStep;
	
	if((iwidth!=tophat_width)&&(iheight!=tophat_width))
		cout<<"colorSeg and Tophat don't match!"<<endl;
	IplImage *fixImg=cvCreateImage(cvSize(iwidth,iheight),IPL_DEPTH_8U,1);//存储修tophat加颜色分割联合处理后的图像

	int OutWidthStep=fixImg->widthStep;
	for(int i=0;i<ROIHeight;i++)
	{
		in1 = (unsigned char*)colorseg->imageData + i*iwidthStep;
		in2 = (unsigned char*)tophat->imageData + i*iwidthStep;
		out = (unsigned char*)fixImg->imageData + i*OutWidthStep;
		for(int j=0;j<iwidth;j++)
		{
			if(in1[j]+in2[j]==2*GREEN_PIXEL_LABEL)
				out[j]= GREEN_PIXEL_LABEL;
			else if(in1[j]+in2[j]==GREEN_PIXEL_LABEL+RED_PIXEL_LABEL)
				out[j]= RED_PIXEL_LABEL;
			else
				out[j]=NON_BLOB_PIXEL_LABEL;
		}
	}

	return fixImg;
	

}