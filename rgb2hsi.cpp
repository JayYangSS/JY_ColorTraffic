#include "std_tlr.h"
#include "math_utils.h"

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

float	retrieve_luminance(unsigned int r, unsigned int g, unsigned int b)
{
	return (0.210f * r) + (0.715f * g) + (0.072f * b);
}


float	retrieve_saturation(unsigned int r, unsigned int g, unsigned int b)
{
	float saturation;
	unsigned int max = get_maximum(r, g, b);
	unsigned int min = get_minimum(r, g, b);

	saturation = max - min;

	return saturation;
}



float	retrieve_theta(unsigned int r, unsigned int g, unsigned int b)
{
	float theta;

	// The numerator part of equation
	float numerator = r - (g * 0.5) - (b * 0.5);

	// The denominator part of equation
	float denominator = (r * r) + (g * g) + (b * b) - (r * g) - (r * b) - (g * b);

	float temp = numerator / sqrtf(denominator);
	theta = acos(temp);

	return theta;
}


float	retrieve_normalised_hue(unsigned int r, unsigned int g, unsigned int b)
{
	float hue;
	if (b <= g)
	{
		hue = retrieve_theta(r, g, b);
	}
	else
	{
		hue = (2 * M_PI) - retrieve_theta(r, g, b);
	}

	return hue * 255 / (2 * M_PI);
}

Mat convert_rgb_to_ihls(Mat rgb_image)
{


	assert(rgb_image.channels() == 3);

	Mat ihls_image(rgb_image.rows, rgb_image.cols, CV_8UC3);

	for (int i = 0; i < rgb_image.rows; ++i)
	{
		const uchar* rgb_data = rgb_image.ptr<uchar> (i);
		uchar* ihls_data = ihls_image.ptr<uchar> (i);

		for (int j = 0; j < rgb_image.cols; ++j)
		{
			unsigned int b = *rgb_data++;
			unsigned int g = *rgb_data++;
			unsigned int r = *rgb_data++;
			*ihls_data++ = (uchar) retrieve_saturation(r, g, b);
			*ihls_data++ = (uchar) retrieve_luminance(r, g, b);
			*ihls_data++ = (uchar) retrieve_normalised_hue(r, g, b);
		}
	}

	return ihls_image;
}


Mat	convert_ihls_to_nhs(Mat ihls_image, int colour, int hue_max, int hue_min,int sat_min)
{
	if (colour == 2)//RED
	{
		if (hue_max > 255 || hue_max < 0 || hue_min > 255 || hue_min < 0
			|| sat_min > 255 || sat_min < 0)
		{
			hue_min = R_HUE_MIN;
			hue_max = R_HUE_MAX;
			sat_min = R_SAT_MIN;
		}
	}
	else if (colour == 1)//BLUE
	{
		hue_min = B_HUE_MIN;
		hue_max = B_HUE_MAX;
		sat_min = B_SAT_MIN;
	}
	else if(colour==0)//YELLOW
	{
		hue_min = Y_HUE_MIN;
		hue_max = Y_HUE_MAX;
		sat_min = Y_SAT_MIN;
	}

	else
	{
		hue_min = R_HUE_MIN;
		hue_max = R_HUE_MAX;
		sat_min = R_SAT_MIN;
	}

	assert(ihls_image.channels() == 3);

	Mat nhs_image(ihls_image.rows, ihls_image.cols, CV_8UC1);

	// I put the if before for loops, to make the process faster.
	// Otherwise for each pixel it had to check this condition.
	// Nicer implementation could be to separate these two for loops in
	// two different functions, one for red and one for blue.
	if (colour == 1)//blue
	{
		for (int i = 0; i < ihls_image.rows; ++i)
		{
			const uchar *ihls_data = ihls_image.ptr<uchar> (i);
			uchar *nhs_data = nhs_image.ptr<uchar> (i);
			for (int j = 0; j < ihls_image.cols; ++j)
			{
				uchar s = *ihls_data++;
				// Although l is not being used and we could have
				// replaced the next line with ihls_data++
				// but for the sake of readability, we left it as it it.
				uchar l = *ihls_data++;
				uchar h = *ihls_data++;

				*nhs_data++ = (B_CONDITION) ? 255 : 0;
			}
		}
	}
	else if (colour==0)//yellow
	{
		for (int i = 0; i < ihls_image.rows; ++i)
		{
			const uchar *ihls_data = ihls_image.ptr<uchar> (i);
			uchar *nhs_data = nhs_image.ptr<uchar> (i);
			for (int j = 0; j < ihls_image.cols; ++j)
			{
				uchar s = *ihls_data++;
				uchar l = *ihls_data++;
				uchar h = *ihls_data++;
				*nhs_data++ = (Y_CONDITION) ? 255 : 0;
			}
		}
	}
	else if(colour==3)//green
	{
		for (int i = 0; i < ihls_image.rows; ++i)
		{
			const uchar *ihls_data = ihls_image.ptr<uchar> (i);
			uchar *nhs_data = nhs_image.ptr<uchar> (i);
			for (int j = 0; j < ihls_image.cols; ++j)
			{
				uchar s = *ihls_data++;
				uchar l = *ihls_data++;
				uchar h = *ihls_data++;
				*nhs_data++ = (G_CONDITION) ? 255 : 0;
			}
		}
	}
	else    //red
	{
		for (int i = 0; i < ihls_image.rows; ++i)
		{
			const uchar *ihls_data = ihls_image.ptr<uchar> (i);
			uchar *nhs_data = nhs_image.ptr<uchar> (i);
			for (int j = 0; j < ihls_image.cols; ++j)
			{
				uchar s = *ihls_data++;
				uchar l = *ihls_data++;
				uchar h = *ihls_data++;
				*nhs_data++ = (R_CONDITION) ? 255 : 0;
			}
		}
	}
/*	cout<<"maxH:"<<maxH<<endl;
	cout<<"minH:"<<minH<<endl;
	cout<<"minS:"<<minS<<endl;*/

	return nhs_image;
}
