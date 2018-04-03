#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;


void thresholdIntegral(cv::Mat &inputMat, cv::Mat &outputMat)
{
    // accept only char type matrices
    CV_Assert(!inputMat.empty());
    CV_Assert(inputMat.depth() == CV_8U);
    CV_Assert(inputMat.channels() == 1);
    CV_Assert(!outputMat.empty());
    CV_Assert(outputMat.depth() == CV_8U);
    CV_Assert(outputMat.channels() == 1);

    // rows -> height -> y
    int nRows = inputMat.rows;
    // cols -> width -> x
    int nCols = inputMat.cols;

    // create the integral image
    cv::Mat sumMat;
    cv::integral(inputMat, sumMat);

    CV_Assert(sumMat.depth() == CV_32S);
    CV_Assert(sizeof(int) == 4);

    int S = MAX(nRows, nCols)/8;
    double T = 0.15;

    // perform thresholding
    int s2 = S/2;
    int x1, y1, x2, y2, count, sum;

    // CV_Assert(sizeof(int) == 4);
    int *p_y1, *p_y2;
    uchar *p_inputMat, *p_outputMat;

    for( int i = 0; i < nRows; ++i)
    {
        y1 = i-s2;
        y2 = i+s2;

        if (y1 < 0){
            y1 = 0;
        }
        if (y2 >= nRows) {
            y2 = nRows-1;
        }

        p_y1 = sumMat.ptr<int>(y1);
        p_y2 = sumMat.ptr<int>(y2);
        p_inputMat = inputMat.ptr<uchar>(i);
        p_outputMat = outputMat.ptr<uchar>(i);

        for ( int j = 0; j < nCols; ++j)
        {
            // set the SxS region
            x1 = j-s2;
            x2 = j+s2;

            if (x1 < 0) {
                x1 = 0;
            }
            if (x2 >= nCols) {
                x2 = nCols-1;
            }

            count = (x2-x1)*(y2-y1);

            // I(x,y)=s(x2,y2)-s(x1,y2)-s(x2,y1)+s(x1,x1)
            sum = p_y2[x2] - p_y1[x2] - p_y2[x1] + p_y1[x1];

            if ((int)(p_inputMat[j] * count) < (int)(sum*(1.0-T)))
                p_outputMat[j] = 0;
            else
                p_outputMat[j] = 255;
        }
    }
}


int main(int argc, char *argv[])
{
    printf("Adaptive Integral Threshold.\n");
    if (argc < 3)
    {
        printf("Usage: aithreshold image_in image_out\n");
        return 0;
    }
//! [load_image]
    // Load the image
    cv::Mat src = cv::imread(argv[1]);

    // Check if image is loaded fine
    if(src.empty()) {
        cerr << "Problem loading image!!!" << endl;
        return -1;
    }

    // Show source image
//    cv::imshow("src", src);
//! [load_image]

//! [gray]
    // Transform source image to gray if it is not
    cv::Mat gray;

    if (src.channels() == 3)
    {
        cv::cvtColor(src, gray, CV_BGR2GRAY);
        // Show gray image
//        cv::imshow("gray", gray);
    }
    else
    {
        gray = src;
    }

//    cout << "TEST" << endl;

//! [gray] 

//! [bin_1]
//    cv::Mat bw1;
//    cv::adaptiveThreshold(gray, bw1, 255, CV_ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 15, -2);

    // Show binary image
//    cv::imshow("binary opencv", bw1);
//! [bin_1] 


//! [bin_2]
    cv::Mat bw2 = cv::Mat::zeros(gray.size(), CV_8UC1);
    thresholdIntegral(gray, bw2);
    printf("%s -> %s\n", argv[1], argv[2]);

    // Show binary image
//    cv::imshow("binary integral", bw2);
//! [bin_2] 

//    cv::waitKey(0);
    cv::imwrite(argv[2],bw2);
    return 0;
}
