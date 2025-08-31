#include "header/Ponto.h"
#include <iostream>
#include "header/ImageException.h"
#include <opencv2/opencv.hpp>

void getPixelSafe(const cv::Mat& img, Ponto p1, Ponto p2) {
    if (p1.getX() < 0 || p1.getY() < 0 
       || p2.getX() < 0 || p2.getY() < 0
       || p1.getX() >= img.rows || p2.getX() >= img.rows 
       || p1.getY() >= img.cols || p2.getY() >= img.cols) {
        throw ImageException("Coordenadas inválidas!");
    }
}

void negative_image(cv::Mat &image, Ponto p1, Ponto p2);

int main(int, char**) {
  cv::Mat image;
  Ponto p1;
  Ponto p2;
  int x1,x2,y1,y2;

  image = cv::imread("hp.jpg", cv::IMREAD_COLOR);
  if (!image.data) 
    throw std::runtime_error("Imagem hp.png não carregada");
  
  std::cout << "A imagem tem dimensão: " << image.rows << "x" << image.cols << std::endl;
  std::cout << "Insira as coordenadas para o ponto inicial." << std::endl;
  std::cin >> x1 >> y1;
  p1.setX(x1);
  p1.setY(y1);
  
  std::cout << "Insira as coordenadas para o ponto final." << std::endl;
  std::cin >> x2 >> y2;
  p2.setX(x2);
  p2.setY(y2);
  
  cv::namedWindow("Imagem", cv::WINDOW_AUTOSIZE);
  
  try {
    getPixelSafe(image, p1, p2);
  } catch (const ImageException& e) {
        std::cerr << "Erro de processamento de imagem: " << e.what() << std::endl;
        return 0;
  }
  
  negative_image(image, p1, p2);
  cv::imshow("Janela", image);
  cv::waitKey();
  return 0;
}

void negative_image(cv::Mat &image, Ponto p1, Ponto p2) {
  cv::Vec3b pixel;

  for (int i = p1.getX(); i <= p2.getX(); i++) {
    for (int j = p1.getY(); j <= p2.getY(); j++) {
      pixel = image.at<cv::Vec3b>(i, j);
      pixel[0] = 255 - pixel[0];
      pixel[1] = 255 - pixel[1];
      pixel[2] = 255 - pixel[2];
      image.at<cv::Vec3b>(i, j) = pixel;
    }
  }
}
