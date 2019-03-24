//#include <QCoreApplication>
#include<opencv4/opencv2/opencv.hpp>
#include<opencv4/opencv2/core.hpp>
#include<opencv4/opencv2/imgproc.hpp>
#include<opencv4/opencv2/highgui.hpp>
#include<opencv4/opencv2/videoio.hpp>
#include<opencv4/opencv2/video.hpp>
#include<opencv4/opencv2/objdetect.hpp>
#include<string>
#include<vector>

//face and other detection using haar cascade filters

int main(int argc, char *argv[])
{
   // QCoreApplication a(argc, argv);
    cv::VideoCapture cap(0);
    cv::Mat frame;
    cv::Mat frameGray;
    //cv::cuda::GpuMat frame2;
    //cv::cuda::DeviceInfo info = cv::cuda::getDevice();
    //std::cout << info.name() << std::endl;

    std::vector<cv::Rect> faceRects;



    //haarcascade_frontalcatface_extended
    //std::string faceCascadeXMLFile("haarcascade_frontalcatface_extended.xml");
    //std::string faceCascadeXMLFile("haarcascade_frontalface_default.xml");
    std::string faceCascadeXMLFile("haarcascade_frontalface_alt2.xml");
    //std::string faceCascadeXMLFile("haarcascade_smile.xml");
    //std::string faceCascadeXMLFile("haarcascade_eye_tree_eyeglasses.xml");
    //std::string faceCascadeXMLFile("haarcascade_mcs_nose.xml");
    //std::string faceCascadeXMLFile("haarcascade_frontalface_alt.xml");


    cv::CascadeClassifier cascClassify;
    if(!cascClassify.load(faceCascadeXMLFile))
    {
        std::cout<<"xml haar cascade not loaded."<<std::endl;
        return -1;
    }
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    char ch;
    cv::namedWindow("video",cv::WINDOW_NORMAL);
    cv::namedWindow("videoGray",cv::WINDOW_NORMAL);
    ch = '0';

    while(ch!=27)
    {
        cap >> frame;
        cv::cvtColor(frame,frameGray,cv::COLOR_BGR2GRAY);
        cv::equalizeHist(frameGray,frameGray);

       cascClassify.detectMultiScale(frameGray,faceRects);

        if(faceRects.size()>0)
        {
            for(auto face:faceRects)
            {
                cv::rectangle(frame,face,cv::Scalar(255,0,0),3,8,0);

            }
        }
        cv::imshow("videoGray",frameGray);
        //cv::waitKey(30);
        cv::imshow("video",frame);
        ch = cv::waitKey(30);
    }
    //return a.exec();
    return 0;
}
