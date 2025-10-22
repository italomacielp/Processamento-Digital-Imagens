#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(int argc, char** argv){
  cv::Mat image, gray;

  if(argc != 2){
    std::cerr << "Uso: " << argv[0] << " <Image_Path>\n";
    return -1;
  }

  image = cv::imread(argv[1], cv::IMREAD_COLOR);

  if (!image.data) {
    std::cerr << "Nao abriu " << argv[1] << std::endl;
    return -1;
  }

  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  cv::Mat jet, hot, cool, ocean, magma;
  cv::applyColorMap(gray, jet,   cv::COLORMAP_JET);
  cv::applyColorMap(gray, hot,   cv::COLORMAP_HOT);
  cv::applyColorMap(gray, cool,  cv::COLORMAP_COOL);
  cv::applyColorMap(gray, ocean, cv::COLORMAP_OCEAN);
  cv::applyColorMap(gray, magma, cv::COLORMAP_MAGMA);

  cv::imshow("Original", image);
  cv::imshow("Gray", gray);
  cv::imshow("JET", jet);
  cv::imshow("HOT", hot);
  cv::imshow("COOL", cool);
  cv::imshow("OCEAN", ocean);
  cv::imshow("MAGMA", magma);

  cv::waitKey(0);
  return 0;
}

