#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::VideoCapture cap;
  double width, height;
  cv::Mat frame, negativeFrame;
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
  cv::VideoWriter out("output_negative.avi", codec, fps, frameSize, true);

  for(counter = 0; cap.read(frame); counter++){
    cv::bitwise_not(frame, negativeFrame);
    
    out << negativeFrame;
    cv::imshow("Frame Negativo", negativeFrame);
    if(cv::waitKey(30) >= 0) break;
  }

  std::cout << "Número de frames: " << counter << "\n";
  return 0;
}
