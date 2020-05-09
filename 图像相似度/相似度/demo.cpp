#include<opencv2/opencv.hpp>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;
using namespace cv;


//计算两幅图像的峰值信噪比PSNR，越小表示两幅图像越相似，等于0则表示两幅图像完全相同
//基于每个像素误差，得出的结果可能和人眼视觉有较大差异
double getPSNR(const Mat& I1, const Mat& I2)
{
    Mat s1;
    absdiff(I1, I2, s1);       // 计算两幅图像差值的绝对值|I1 - I2|
    s1.convertTo(s1, CV_32F);  // 在进行平方操作之前先加深图像深度
    s1 = s1.mul(s1);           //对差值绝对值进行求平方 |I1 - I2|^2
    Scalar s = sum(s1);        // 对每个通道的像素值求和
    double sse = s.val[0] + s.val[1] + s.val[2]; // 三通道的总像素值
    if (sse <= 1e-10)           //如果两幅图像差值绝对值的平方三通道总和很小，则无差别
        return 0;
    else
    {
        double mse = sse / (double)(I1.channels() * I1.total());            //均方误差 = 差值平方和 / 总像素数
        double psnr = 10.0 * log10((255.0 * 255.0) / mse);          //峰值信噪比
        return psnr;
    }
}


//计算两幅图像的平均结构相似性，返回三通道的0~1的相似度度量，越接近1表示越相似
//从图像结构上进行计算相似度，更符合人眼视觉观感
Scalar getMSSIM(const Mat& i1, const Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    int d = CV_32F;
    Mat I1, I2;
    i1.convertTo(I1, d);            
    i2.convertTo(I2, d);
    Mat I2_2 = I2.mul(I2);        // I2^2
    Mat I1_2 = I1.mul(I1);        // I1^2
    Mat I1_I2 = I1.mul(I2);        // I1 * I2
    Mat mu1, mu2;                   
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);
    Mat mu1_2 = mu1.mul(mu1);
    Mat mu2_2 = mu2.mul(mu2);
    Mat mu1_mu2 = mu1.mul(mu2);
    Mat sigma1_2, sigma2_2, sigma12;
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;
    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;
    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;
    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);                 // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);                 // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
    Mat ssim_map;
    divide(t3, t1, ssim_map);        // ssim_map =  t3./t1;
    Scalar mssim = mean(ssim_map);   // mssim是ssim的平均值
    return mssim;
}


int main()
{
    vector<string>path;
    glob("C:\\Users\\QXB\\Desktop\\Product_information_detection\\Printing detection\\test\\uncompleted_issue\\miss_patch_issue\\", path);
    //glob("C:\\Users\\QXB\\Desktop\\Product_information_detection\\Printing detection\\test\\uncompleted_issue\\single_char_issue\\", path);
    //glob("C:\\Users\\QXB\\Desktop\\Product_information_detection\\Printing detection\\test\\illumination_issue\\", path);
    //glob("C:\\Users\\QXB\\Desktop\\Product_information_detection\\Printing detection\\test\\color_issue\\", path);
    //glob("C:\\Users\\QXB\\Desktop\\Product_information_detection\\Printing detection\\test\\bold_issue\\", path);

    Mat tem_image = imread("C:\\Users\\QXB\\Desktop\\Product_information_detection\\Printing detection\\template\\true_texts.png");
    //提取色调H和饱和度S通道，忽视亮度V通道的影响
    cvtColor(tem_image, tem_image, COLOR_BGR2HSV);
    vector<Mat>tem_hsv;
    split(tem_image, tem_hsv);
    vector<Mat>tem_hs;
    tem_hs.push_back(tem_hsv[0]);
    tem_hs.push_back(tem_hsv[1]);
    Mat tem_image_hs;
    merge(tem_hs, tem_image_hs);

    for (int i = 0; i < path.size(); i++)
    {
        Mat test_image = imread(path[i]);
        cvtColor(test_image, test_image, COLOR_BGR2HSV);
        vector<Mat>test_hsv;
        split(test_image, test_hsv);
        vector<Mat>test_hs;
        test_hs.push_back(test_hsv[0]);
        test_hs.push_back(test_hsv[1]);
        Mat test_image_hs;
        merge(test_hs, test_image_hs);

        //在对视频流进行相似度检测时，由于峰值信噪比PSNR的计算量比较小，所以可以对每帧图像进行PSNR比较，当PSNR小于阈值时，再通过平均结构相似性MSSIM进行比较。
        double PSNR = getPSNR(tem_image_hs, test_image_hs);
        if (PSNR < 20)
        {
            Scalar MSSIM = getMSSIM(tem_image_hs, test_image_hs);
            if (MSSIM[0] > 0.995 && MSSIM[1] > 0.995)
            {
                cout << "测试图像" << i << "：PSNR=" << PSNR << "\tMSSIM=" << MSSIM << endl;
            }
        }
        else
        {
            cout << "测试图像" << i << "：PSNR=" << PSNR << endl;
        }

        //Scalar MSSIM = getMSSIM(tem_image_hs, test_image_hs);
        //cout << "测试图像" << i << "：PSNR=" << PSNR << "\tMSSIM=" << MSSIM << endl;
    }
   

    cv::waitKey(0);
    return 0;
}