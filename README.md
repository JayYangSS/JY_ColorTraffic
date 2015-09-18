#code description
1. In this code, we first use the HSV color space to segment the color, and get the candidate region of red and green.The
green ones will be marked as 255,the red ones will be marked as 128.This step can generate a gray-scale image.
2. use the color noise remove to filter the noise
3. Use the seed region grow algorithm to get the connected regions
4. apply the shape constraints on these connected regions and get the proper regions(That means these regions have the 
proper size and ratio of height and width. )
5. comebine the step 1's gray image,recognize the color of traffic light
6. use the HOG+SVM to determine wether the image in rectangle contains traffic lights
