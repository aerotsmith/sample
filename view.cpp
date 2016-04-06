#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void show_mat(const cv::Mat &image, std::string const &win_name);
cv::Mat& invert_mat(cv::Mat &mat);

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: Opencv_Test <Image_Path> <Output_Path>\n");
        return -1;
    }

    Mat image;
    image = imread(argv[1], 1);

    if (!image.data) {
        printf("No image data (warning: OpenCV recognize files by extensions)\n");
        return -1;
    }

    show_mat(image, "Input");

    image = invert_mat(image);

    show_mat(image, "Output");

    imwrite(argv[2], image);

    return 0;
}

cv::Mat& invert_mat(cv::Mat &mat) {
    // accept only char type matrices
    CV_Assert(mat.depth() == CV_8U);

    const int channels = mat.channels();
    switch (channels) {
        case 1: {
//            gray scale image
            MatIterator_<uchar> it, end;
            for (it = mat.begin<uchar>(), end = mat.end<uchar>(); it != end; ++it)
                *it = ~*it;
            break;
        }
        case 3: {
//            RGB image
            MatIterator_<Vec3b> it, end;
            for (it = mat.begin<Vec3b>(), end = mat.end<Vec3b>(); it != end; ++it) {
                (*it)[0] = ~(*it)[0];
                (*it)[1] = ~(*it)[1];
                (*it)[2] = ~(*it)[2];
            }
        }
    }

    return mat;
}

void show_mat(const cv::Mat &image, std::string const &win_name) {
    namedWindow(win_name, WINDOW_AUTOSIZE);
    imshow(win_name, image);
    waitKey(0);
}
