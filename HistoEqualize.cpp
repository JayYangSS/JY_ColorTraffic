#include "std_tlr.h"
IplImage* HistoEqualize(IplImage* InputImg)
{
	const int Max_chanel=4;
	IplImage *pEqualImg=cvCreateImage(cvGetSize(InputImg),InputImg->depth,3);
	IplImage *pImgchanel[Max_chanel]={NULL};
	
	for(int i=0;i<InputImg->nChannels;i++)
		pImgchanel[i]=cvCreateImage(cvGetSize(InputImg),InputImg->depth,1);

	cvSplit(InputImg,pImgchanel[0],pImgchanel[1],pImgchanel[2],pImgchanel[3]);

	 for (int i = 0; i < InputImg->nChannels; i++)  
        cvEqualizeHist(pImgchanel[i], pImgchanel[i]); 

	 cvMerge(pImgchanel[0],pImgchanel[1],pImgchanel[2],pImgchanel[3],pEqualImg);

	  for (int i = 0; i < InputImg->nChannels; i++)  
        cvReleaseImage(&pImgchanel[i]);  

	 return pEqualImg;
}