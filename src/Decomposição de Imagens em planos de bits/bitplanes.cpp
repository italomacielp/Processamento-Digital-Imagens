#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Uso: ./recupera esteganografia.png" << std::endl;
        return -1;
    }

    cv::Mat imagemEstego = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (imagemEstego.empty()) {
        std::cout << "Imagem não carregou corretamente" << std::endl;
        return -1;
    }

    int nbits = 3;
    cv::Mat imagemRecuperada = imagemEstego.clone();
    cv::Vec3b pixelEstego, pixelRecuperado;

    for (int i = 0; i < imagemEstego.rows; i++) {
        for (int j = 0; j < imagemEstego.cols; j++) {
            pixelEstego = imagemEstego.at<cv::Vec3b>(i, j);

            pixelRecuperado[0] = (pixelEstego[0] & ((1 << nbits) - 1)) << (8 - nbits);
            pixelRecuperado[1] = (pixelEstego[1] & ((1 << nbits) - 1)) << (8 - nbits);
            pixelRecuperado[2] = (pixelEstego[2] & ((1 << nbits) - 1)) << (8 - nbits);

            imagemRecuperada.at<cv::Vec3b>(i, j) = pixelRecuperado;
        }
    }

    cv::imwrite("imagem_recuperada.png", imagemRecuperada);
    std::cout << "Imagem recuperada salva como imagem_recuperada.png" << std::endl;

    return 0;
}
