#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
// Drawing shapes
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
 string path = "linn-photobooth-logo.png"; //It works best if the input image is losslessly compress like png so that there will be more compression artifacts
 Mat img = imread(path,IMREAD_COLOR);

 Mat redcircle = img.clone();
 Mat bluecircle = img.clone();

 Point p1(img.cols/2-50,img.rows/2-50);
 Point p2(img.cols/2+50,img.rows/2+50);

 //If the circle is close enough to the border of the cropped area there will be some diffs
 //int radius = 48;
 int radius =40;
 //With Lenna.jpg 512x512 radius must be >=48 to have some diffs, but with other background image or other shapes (in particular sharp corners)
 // it may reveal leak info more than 10 pixel inside the border

 Point p1s(img.cols/2-radius,img.rows/2-radius);
 Point p2s(img.cols/2+radius,img.rows/2+radius);

 circle(redcircle, Point(img.cols/2,img.rows/2),radius, Scalar(0,0,255),FILLED, 8,0);
 circle(bluecircle, Point(img.cols/2,img.rows/2),radius, Scalar(255,0,0),FILLED, 8,0);

//We can draw rectangle instead of circles
 //rectangle(redcircle,p1s, p2s,Vec3b(0,0,255), cv::FILLED);
 //rectangle(bluecircle,p1s, p2s,Vec3b(255,0,0), cv::FILLED);

 imwrite("redcircle.jpg",redcircle); //Compress as jpg
 imwrite("bluecircle.jpg",bluecircle);

 Mat redcirclejpg = imread("redcircle.jpg", IMREAD_COLOR);
 Mat bluecirclejpg = imread("bluecircle.jpg", IMREAD_COLOR);

//Cropping an image that has been jpg compressed (or any other lossy compressed format) leaks some info !!!
Mat croppedred = redcirclejpg.clone();
rectangle(croppedred,p1, p2,Vec3b(0,0,0), cv::FILLED);

Mat croppedblue = bluecirclejpg.clone();
rectangle(croppedblue,p1, p2,Vec3b(0,0,0), cv::FILLED);

Mat diff=Mat::zeros(redcirclejpg.size(), CV_8UC1);

  for( int i = 0 ; i < redcirclejpg.rows ; i++)
        for( int j = 0 ; j < redcirclejpg.cols ; j++)
            for( int k = 0 ; k < 3 ; k++)
                if( croppedred.at<Vec3b>(i, j)[k]!=croppedblue.at<Vec3b>(i, j)[k])
                    diff.at<uchar>(i,j)=255;

    
imwrite("diff.png",diff);
imwrite("croppedred.png",croppedred);
imwrite("croppedblue.png",croppedblue);

imshow("croppedred",croppedred);
imshow("croppedblue",croppedblue);
imshow("redcircle.jpg",redcirclejpg);
imshow("bluecircle.jpg",bluecirclejpg);
imshow("diff.jpg",diff);
waitKey(0);

}
