#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

vector<Point2f> srcPoints;
Mat image;

void onMouse(int event, int x, int y, int, void *) {
  if (event == EVENT_LBUTTONDOWN) {
    if (srcPoints.size() < 4) {
      srcPoints.push_back(Point2f(x, y));
      cout << "Ponto selecionado: (" << x << ", " << y << ")" << endl;
      circle(image, Point(x, y), 5, Scalar(0, 0, 255), -1); // Marca o ponto na imagem
      imshow("Selecione 4 pontos", image);
    }
  }
}

int main() {
  image = imread("../voltimetro.png");
  if (image.empty()) {
    cout << "Erro ao carregar imagem!" << endl;
    return -1;
  }

  namedWindow("Selecione 4 pontos", WINDOW_AUTOSIZE);
  setMouseCallback("Selecione 4 pontos", onMouse);

  cout << "Clique em 4 pontos na imagem na ordem: "
       << "superior-esquerdo, superior-direito, inferior-direito, inferior-esquerdo." << endl;

  imshow("Selecione 4 pontos", image);

  while (srcPoints.size() < 4) {
    waitKey(10);
  }

  int largura = max((int)norm(srcPoints[0] - srcPoints[1]),
                    (int)norm(srcPoints[2] - srcPoints[3]));
  int altura = max((int)norm(srcPoints[1] - srcPoints[2]),
                   (int)norm(srcPoints[3] - srcPoints[0]));

  vector<Point2f> dstPoints;
  dstPoints.push_back(Point2f(0, 0));
  dstPoints.push_back(Point2f(largura, 0));
  dstPoints.push_back(Point2f(largura, altura));
  dstPoints.push_back(Point2f(0, altura));

  Mat perspectiveMatrix = getPerspectiveTransform(srcPoints, dstPoints);

  Mat correctedImage;
  warpPerspective(image, correctedImage, perspectiveMatrix, Size(largura, altura));

  imshow("Imagem Original", image);
  imshow("Imagem Corrigida", correctedImage);
  imwrite("corrigida.png", correctedImage);
  waitKey(0);

  return 0;
}

