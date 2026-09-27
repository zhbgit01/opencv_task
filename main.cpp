#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // 1. 读取图片
    Mat image = imread("test.jpg");

    if (image.empty())
    {
        cout << "Failed to read image!" << endl;
        return -1;
    }

    // 2. 转为灰度图
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // 3. 二值化
    // 图片是白色背景，所以使用反向二值化
    Mat binary;
    threshold(gray, binary, 240, 255, THRESH_BINARY_INV);

    // 4. 检测轮廓
    vector<vector<Point>> contours;

    findContours(
        binary,
        contours,
        RETR_EXTERNAL,
        CHAIN_APPROX_SIMPLE
    );

    cout << "Contours: " << contours.size() << endl;

    // 5. 绘制轮廓
    Mat result = image.clone();

    drawContours(
        result,              // 在哪张图上画
        contours,            // 检测到的轮廓
        -1,                  // 绘制所有轮廓
        Scalar(0, 0, 255),   // 红色
        2                    // 线宽
    );

    // 6. 显示结果
    imshow("Original", image);
    imshow("Binary", binary);
    imshow("Contours", result);

    waitKey(0);

    return 0;
}