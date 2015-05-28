#include"std_tlr.h"


#if TEST
	FILE* tmpfp;
#endif


#define SIZE_FILTER 1
#define REGION_GROW_FILTER 1
#define RECT_FILTER 1

bool regionGrowA(int nSeedX,int nSeedY,BYTE * pUnchInput,int nWidth,int nHeight,
	             BYTE * pUnRegion,int nThreshold,int& color,CvRect &rect,int& pixelNum);

#if TEST
	IplImage* tmpRegion1;
	IplImage* tmpRegion2;
#endif



void componentExtraction(IplImage* inputImage,IplImage* srcImage,int* p)
{
    int r=0;int g=0;
	int iWidth = inputImage->width;
	int iHeight = inputImage->height;
	int iWidthStep = inputImage->widthStep;
	unsigned char* pImageData = (unsigned char*)inputImage->imageData;//imageData��ָ��ͼ�����������׵�ַ��ָ�룬����Ϊchar*������

	IplImage* imageGrayScale = cvCreateImage(cvSize(iWidth,iHeight),IPL_DEPTH_8U,1);
	if(!imageGrayScale)
		exit(EXIT_FAILURE);
	
	cvCvtColor(srcImage,imageGrayScale,CV_BGR2GRAY);
	//Mat src = cvarrToMat(srcImage), dst0 = cvarrToMat(imageGrayScale), dst = dst0;
	//cvtColor(src, dst, CV_BGR2GRAY, dst.channels());


	cvShowImage("gray",imageGrayScale);
	cvWaitKey(5);
#if TEST
	tmpRegion1 = cvCreateImage(cvSize(iWidth,iHeight),IPL_DEPTH_8U,1);
	if(!tmpRegion1)
		exit(EXIT_FAILURE);
	cvZero(tmpRegion1);
	tmpRegion2 = cvCreateImage(cvSize(iWidth,iHeight),IPL_DEPTH_8U,1);
	if(!tmpRegion2)
		exit(EXIT_FAILURE);
	cvZero(tmpRegion2);
#endif

	//thresholding for size of components
	const int thresholding = 4;

	int i=0,j=0;
	CvRect oRect;
	//CvRect ooRect;
	int rectNum = 0;
	int rectNum2 = 0;
	int pixelNum=0;
	int oColor=0;
	unsigned char* flag = new unsigned char[iWidth*iHeight];
	if(flag==NULL)
		return;
	memset(flag,0,iWidth*iHeight);//flag�����ʼ��Ϊ0
	for(i=0;i<iHeight;i++){
		for(j=0;j<iWidth;j++){

			if(pImageData[i*iWidthStep+j]!=0 && flag[i*iWidth+j]==0){     //ͼ������ֵ��Ϊ0��û�б������
					
				
				//����ۺ���������ص���Ӧ��־λ�ã���flag�洢������Ϊ255�����ӵ������ֵ���洢��oColor�У������ڵ����ص���Ŀ����pixelNum
				if(regionGrowA(j,i,pImageData,iWidth,iHeight,flag,thresholding,oColor,oRect,pixelNum)){

#if SIZE_FILTER
	
					//printf("%d,%d,%d,%d\n",oRect.x,oRect.y,oRect.width,oRect.height);
					//��ѡ�����������Χ��������Ҫ����һ�����������߱����Ʋ��ܱ�����
					if(sizeFiltering(oRect)){
						rectNum++;
#if (TEST)
						//FILE* tmpfp;
						tmpfp = fopen("tmpRectData.txt","a");
						if(tmpfp==NULL)
							return ;

						fprintf(tmpfp,"\n%2d:%5d %5d %5d %5d %5d",rectNum,oRect.x,oRect.y,oRect.width+1,oRect.height+1,pixelNum);
							if(oColor==GREEN_PIXEL_LABEL)
								fprintf(tmpfp,"    green\n");
							else if(oColor==RED_PIXEL_LABEL)
								fprintf(tmpfp,"    red\n");
							else
								fprintf(tmpfp,"    undefined\n");
#endif



#if 0		//�ߴ��˲��󣬾������
						if(oColor==GREEN_PIXEL_LABEL)
							cvRectangle(
							srcImage,
							cvPoint(oRect.x,oRect.y),
							cvPoint(oRect.x+oRect.width,oRect.y+oRect.height),
							cvScalar(0,255,0),
							2
							);

						else if(oColor==RED_PIXEL_LABEL)
							cvRectangle(
							srcImage,
							cvPoint(oRect.x,oRect.y),
							cvPoint(oRect.x+oRect.width,oRect.y+oRect.height),
							cvScalar(0,0,255),
							2
							);
#endif			//�ߴ��˲��󣬾������

#if REGION_GROW_FILTER
						//rectangleDetection(imageGrayScale,srcImage,oRect,oColor);
						CvRect ooRect;
						if( regionGrowFiltering(imageGrayScale,srcImage,oRect,ooRect) ){
							rectNum2++;




	///////////////////////////////////////////////////////////////////////////////////////
						///�˴�Ҫ�����жϾ��ο��ڰ�����ͨ�Ʊ߿���жϺ���///
	///////////////////////////////////////////////////////////////////////////////////////
	
							//printf("%d\n",rectNum2);
//
#if TEST
							fprintf(tmpfp,"rectNum:%d\n",rectNum2);
#endif


#if 0  //���������˲������Դ���Σ�oRect��
							if(oColor==GREEN_PIXEL_LABEL)
								cvRectangle(
								srcImage,
								cvPoint(oRect.x,oRect.y),
								cvPoint(oRect.x+oRect.width,oRect.y+oRect.height),
								cvScalar(0,255,0),
								2
								);

							else if(oColor==RED_PIXEL_LABEL)
								cvRectangle(
								srcImage,
								cvPoint(oRect.x,oRect.y),
								cvPoint(oRect.x+oRect.width,oRect.y+oRect.height),
								cvScalar(0,0,255),
								2
								);
#endif	//���������˲������Դ���Σ�oRect��


#if 0	//���������˲�������»�ȡ�ĵľ��Σ�ooRect��
							if(oColor==GREEN_PIXEL_LABEL)
								cvRectangle(
								srcImage,
								cvPoint(ooRect.x,ooRect.y),
								cvPoint(ooRect.x+ooRect.width,ooRect.y+ooRect.height),
								cvScalar(0,255,0),
								2
								);

							else if(oColor==RED_PIXEL_LABEL)
								cvRectangle(
								srcImage,
								cvPoint(ooRect.x,ooRect.y),
								cvPoint(ooRect.x+ooRect.width,ooRect.y+ooRect.height),
								cvScalar(0,0,255),
								2
								);
#endif   //���������˲�������»�ȡ�ĵľ��Σ�ooRect��

#if  RECT_FILTER
							rectangleDetection(imageGrayScale,srcImage,ooRect,oColor,&r,&g);
							//if(oColor==RED_PIXEL_LABEL)
							//	r=r+1;
							//if(oColor==GREEN_PIXEL_LABEL)
							//	g=g+1;
#endif	//RECT_FILTER

						} //regionGrowFiltering_if
#endif //REGION_GROW_FILTER

					} //sizeFiltering_if
#endif //SIZE_FILTER

				} //regionGrowA_if

			}

		}
	}
	if (r>=1)
		p[0]=1;//p[0]=1����ʾ��⵽���
	else p[0]=0;
	if(g>=1)
		p[1]=1;//p[1]=1����ʾ��⵽�̵�
	else p[1]=0;
#if TEST
	char* tmpRegion1Win = "temRegion1.jpg";
		cvNamedWindow(tmpRegion1Win);
		cvShowImage(tmpRegion1Win,tmpRegion1);

		char* tmpRegion2Win = "temRegion2.jpg";
		cvNamedWindow(tmpRegion2Win);
		cvShowImage(tmpRegion2Win,tmpRegion2);
		while(1)
		{
			char c = cvWaitKey(100);
			if(c==27)
				break;
		}
		
		//cvSaveImage("tmpRegion1_1027.jpg",tmpRegion1);
		//cvSaveImage("tmpRegion2_1027.jpg",tmpRegion2);

		cvReleaseImage(&tmpRegion1);
		cvDestroyWindow(tmpRegion1Win);

		cvReleaseImage(&tmpRegion2);
		cvDestroyWindow(tmpRegion2Win);

#endif
	//printf("Num of rect: %d\n",rectNum2);

	if(flag!=NULL){
		delete [] flag;
		flag = NULL;
	}

	cvReleaseImage(&imageGrayScale);

#if (TEST)

	fclose(tmpfp);
#endif

}



//���루nSeedX,nSeedY�����ص���ͬ�����������ҳ����������Ҫ����nThreshold*nThresholdʱ��������Χ�洢��rect��
//���ҵ��򷵻�true��û�ҵ�����false��������ۺ���������ص���Ӧ��־λ�ã���pUnRegion�洢������Ϊ255
bool regionGrowA(int nSeedX,int nSeedY,BYTE * pUnchInput,int nWidth,int nHeight,
	BYTE * pUnRegion,int nThreshold,int& color,CvRect &rect,int& pixelNum)
{


	 int nDx[] = {-1,1,0,0};
	 int nDy[] = {0,0,-1,1};
	 int nSaveWidth = (nWidth+7)/8*8;//���ϲ�ȫ����
	  
	 // �����ջ���洢����
	 int * pnGrowQueX ;
	 int * pnGrowQueY ;

	 // ����ռ�
	 pnGrowQueX = new int [nWidth*nHeight];
	 pnGrowQueY = new int [nWidth*nHeight];

	 // �����ջ�������յ�
	 // ��nStart=nEnd, ��ʾ��ջ��ֻ��һ����
	 int nStart ;
	 int nEnd ;

	 //��ʼ��
	 nStart = 0 ;
	 nEnd = 0 ;

	 // �����ӵ������ѹ��ջ
	 pnGrowQueX[nEnd] = nSeedX;
	 pnGrowQueY[nEnd] = nSeedY;

	 // ��ǰ���ڴ��������
	 int nCurrX ;
	 int nCurrY ;


	 int seedpointLabel = pUnchInput[nSeedY*nSaveWidth+nSeedX];
	 color = seedpointLabel;//��ͨ��ͼ�������ӵ�����ֵ
		


	 // ѭ�����Ʊ���
	 int k ;

	 // ͼ��ĺ�������,�����Ե�ǰ���ص�8������б���
	 int xx;
	 int yy;

	 while (nStart<=nEnd)//while�ⲿ�ֵ�ѭ�������ǰ������ӵ㣨nSeedX,nSeedY������ֵ��ͬ�����ص�����ȫ������pnGrowQueX[],pnGrowQueY[]��
	 {
		  // ��ǰ���ӵ������
		  nCurrX = pnGrowQueX[nStart];
		  nCurrY = pnGrowQueY[nStart];

		  // �Ե�ǰ���4������б���
		  for (k=0; k<4; k++) 
		  { 
			   // 4�������ص�����
			   xx = nCurrX+nDx[k];
			   yy = nCurrY+nDy[k];

			   // �ж�����(xx��yy) �Ƿ���ͼ���ڲ�
			   // �ж�����(xx��yy) �Ƿ��Ѿ������
			   // pUnRegion[yy*nWidth+xx]==0 ��ʾ��û�д���

			   // �����������ж�����(xx��yy)�͵�ǰ����(nCurrX,nCurrY) ����ֵ��ľ���ֵ
			   if ( (xx < nWidth) && (xx>=0) && (yy>=0) && (yy<nHeight) 
					&& (pUnRegion[yy*nWidth+xx]==0) && (pUnchInput[yy*nSaveWidth+xx]==seedpointLabel)) 
			   {
					// ��ջ��β��ָ�����һλ
					nEnd++;

					// ����(xx��yy) ѹ��ջ
					pnGrowQueX[nEnd] = xx;
					pnGrowQueY[nEnd] = yy;

					// ������(xx��yy)���ó��߼�1��255��
					// ͬʱҲ���������ش����
					pUnRegion[yy*nWidth+xx] = 255 ;
			   }
		  }
		  nStart++;
	 }
	    
	 
	 //�ҳ�����ķ�Χ
		int nMinx=pnGrowQueX[0], nMaxx=pnGrowQueX[0], nMiny=pnGrowQueY[0], nMaxy = pnGrowQueY[0];//�����ӵ�����ĺ������귶Χ�ҳ�
		for (k=0; k<nEnd; k++)
	 {
			if (pnGrowQueX[k] > nMaxx)
				 nMaxx = pnGrowQueX[k];
		   if (pnGrowQueX[k] < nMinx) 
				nMinx = pnGrowQueX[k];
		   if (pnGrowQueY[k] > nMaxy)
				nMaxy = pnGrowQueY[k];
		   if (pnGrowQueY[k] < nMiny) 
			   nMiny = pnGrowQueY[k];
	 }


	// �ͷ��ڴ�
#if(!TEST)
	 delete []pnGrowQueX;
	 delete []pnGrowQueY;
	 pnGrowQueX = NULL ;
	 pnGrowQueY = NULL ;
#endif

#if TEST
		 if((nMaxy-nMiny)>=1 && (nMaxx - nMinx)>=1){
		 rect.x=nMinx;
		 rect.y=nMiny;
		 rect.width=nMaxx-nMinx+1;
		 rect.height=nMaxy-nMiny+1;
		 pixelNum = nEnd;
		 if(sizeFiltering(rect)){
			for(int k=0;k<nEnd;k++)
			{
				tmpRegion1->imageData[(pnGrowQueY[k]*nSaveWidth+pnGrowQueX[k])] = 255;
			}

			delete []pnGrowQueX;
			delete []pnGrowQueY;
			pnGrowQueX = NULL ;
			pnGrowQueY = NULL ;

			return true;
		 }
	 }
#endif
//Ѱ�ҵ��߽�㣬����һ��nThreshold*nThreshold�ľ��βſ������
#if (!TEST)
	if((nMaxy-nMiny)>=nThreshold && (nMaxx - nMinx)>=nThreshold){
		rect.x=nMinx;
		rect.y=nMiny;
		rect.width=nMaxx-nMinx+1;
		rect.height=nMaxy-nMiny+1;
		pixelNum = nEnd;
		return true;
	}
#endif		
	 return false;

}