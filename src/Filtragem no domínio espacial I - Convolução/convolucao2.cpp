#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

void printmask(cv::Mat &m) {
  for (int i = 0; i < m.size().height; i++) {
    for (int j = 0; j < m.size().width; j++) {
      std::cout << m.at<float>(i, j) << ",";
    }
    std::cout << std::endl;
  }
}

int main(int argc, char** argv) {
  int filterSize = 3;
  if (argc > 1) {
        filterSize = std::atoi(argv[1]);
        if (filterSize % 2 == 0 || filterSize < 3) {
            std::cerr << "Tamanho do filtro deve ser ímpar e >= 3\n";
            return -1;
        }
    } else {
        std::cout << "Digite o tamanho do filtro (ímpar ≥ 3): ";
        std::cin >> filterSize;
        if (filterSize % 2 == 0 || filterSize < 3) {
            std::cerr << "Valor inválido!\n";
            return -1;
        }
    }

  cv::VideoCapture cap;
  int camera;
  float media[] = {0.1111, 0.1111, 0.1111, 0.1111, 0.1111,
                   0.1111, 0.1111, 0.1111, 0.1111};
  float gauss[] = {0.0625, 0.125,  0.0625, 0.125, 0.25,
                   0.125,  0.0625, 0.125,  0.0625};
  float horizontal[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
  float vertical[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
  float laplacian[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
  float boost[] = {0, -1, 0, -1, 5.2, -1, 0, -1, 0};

  cv::Mat frame, framegray, frame32f, frameFiltered;
  cv::Mat mask(filterSize, filterSize, CV_32F);
  cv::Mat result;
  double width, height;
  int absolut;
  char key;

  camera = cameraEnumerator();
  cap.open(camera);

  if (!cap.isOpened()) 
    return -1;

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  cv::namedWindow("filtroespacial", cv::WINDOW_NORMAL);
  cv::namedWindow("original", cv::WINDOW_NORMAL);

  mask = cv::Mat(filterSize, filterSize, CV_32F, media);

  absolut = 1;

  for (;;) {
    cap >> frame;
    cv::cvtColor(frame, framegray, cv::COLOR_BGR2GRAY);
    cv::flip(framegray, framegray, 1);
    cv::imshow("original", framegray);
    framegray.convertTo(frame32f, CV_32F);
    cv::filter2D(frame32f, frameFiltered, frame32f.depth(), mask, cv::Point(1, 1), cv::BORDER_REPLICATE);
    if (absolut) {
      frameFiltered = cv::abs(frameFiltered);
    }

    frameFiltered.convertTo(result, CV_8U);

    cv::imshow("filtroespacial", result);

    key = (char)cv::waitKey(10);
    if (key == 27) break;  // tecla ESC pressionada!
    switch (key) {
      case 'a':
        absolut = !absolut;
        break;
      case 'm':
        mask = cv::Mat(filterSize, filterSize, CV_32F, media);
        printmask(mask);
        break;
      case 'g':
        mask = cv::Mat(filterSize, filterSize, CV_32F, gauss);
        printmask(mask);
        break;
      case 'h':
        mask = cv::Mat(filterSize, filterSize, CV_32F, horizontal);
        printmask(mask);
        break;
      case 'v':
        mask = cv::Mat(filterSize, filterSize, CV_32F, vertical);
        printmask(mask);
        break;
      case 'l':
        mask = cv::Mat(filterSize, filterSize, CV_32F, laplacian);
        printmask(mask);
        break;
      case 'b':
        mask = cv::Mat(filterSize, filterSize, CV_32F, boost);
        break;
      default:
        break;
    }
  }
  return 0;
}
