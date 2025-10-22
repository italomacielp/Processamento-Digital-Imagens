#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::VideoCapture cap;
  double width, height;
  cv::Mat frame, grayFrame;
  int counter;

  cap.open(argv[1]);
  if(!cap.isOpened()) {
    std::cerr << "Erro ao abrir o vídeo.\n";
    return -1;
  }

  width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
  std::cout << "largura = " << width << "\n";
  std::cout << "altura  = " << height << "\n";

  cv::Size frameSize(static_cast<int>(width), static_cast<int>(height));
  double fps = cap.get(cv::CAP_PROP_FPS);

  int codec = cv::VideoWriter::fourcc('M','J','P','G');
  cv::VideoWriter out("output_gray.avi", codec, fps, frameSize, false);

  for(counter = 0; cap.read(frame); counter++){
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    
    out << grayFrame;
    cv::imshow("Frame em tons de cinza", grayFrame);
    if(cv::waitKey(30) >= 0) break;
  }

  std::cout << "Número de frames: " << counter << "\n";
  return 0;
}
