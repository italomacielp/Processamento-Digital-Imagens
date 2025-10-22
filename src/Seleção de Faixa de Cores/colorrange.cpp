#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

cv::Mat image, imgShow;
bool drawingAdd = false;
bool drawingRemove = false;
std::vector<cv::Vec3b> selectedPixels;

cv::Scalar meanColor(0,0,0);
cv::Scalar stdColor(0,0,0);

void updateStats() {
    if (selectedPixels.empty()) return;
    cv::Mat data(selectedPixels.size(), 1, CV_8UC3, selectedPixels.data());
    cv::meanStdDev(data, meanColor, stdColor);
    std::cout << "Média: " << meanColor << " | Desvio: " << stdColor << std::endl;
}

void onMouse(int event, int x, int y, int, void*) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        drawingAdd = true;
    } 
    else if (event == cv::EVENT_RBUTTONDOWN) {
        drawingRemove = true;
    } 
    else if (event == cv::EVENT_LBUTTONUP) {
        drawingAdd = false;
        updateStats();
    } 
    else if (event == cv::EVENT_RBUTTONUP) {
        drawingRemove = false;
        updateStats();
    }
    
    if (drawingAdd || drawingRemove) {
        if (x >= 0 && y >= 0 && x < image.cols && y < image.rows) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            if (drawingAdd) {
                selectedPixels.push_back(pixel);
                cv::circle(imgShow, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), -1); // verde = inclusão
            }
            else if (drawingRemove && !selectedPixels.empty()) {
                for (auto it = selectedPixels.begin(); it != selectedPixels.end(); ++it) {
                    if (cv::norm(*it - pixel) < 10) {
                        selectedPixels.erase(it);
                        break;
                    }
                }
                cv::circle(imgShow, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), -1); // vermelho = remoção
            }
            cv::imshow("Seleção", imgShow);
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Uso: " << argv[0] << " <imagem>\n";
        return -1;
    }

    image = cv::imread(argv[1]);
    if (image.empty()) {
        std::cerr << "Erro ao abrir imagem\n";
        return -1;
    }

    imgShow = image.clone();

    cv::namedWindow("Selecao", cv::WINDOW_NORMAL);
    cv::namedWindow("Mascara", cv::WINDOW_NORMAL);

    cv::imshow("Selecao", imgShow);

    cv::setMouseCallback("Selecao", onMouse, 0);

    while (true) {
        cv::imshow("Selecao", imgShow);
        char key = cv::waitKey(10);
        if (key == 27) break; // ESC
    }
    return 0;
}

