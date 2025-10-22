#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Mat createCustomColormap() {
    Mat customLUT(1, 256, CV_8UC3);
    for(int i = 0; i < 256; i++){
        customLUT.at<Vec3b>(0, i) = Vec3b(i, 255 - i, (i % 64) * 4);
    }
    return customLUT;
}

int main(int argc, char** argv){
    if(argc != 2){
        cerr << "Uso: " << argv[0] << " <caminho da imagem>\n";
        return -1;
    }

    Mat image = imread(argv[1], IMREAD_COLOR);
    if(!image.data){
        cerr << "Erro ao abrir imagem " << argv[1] << endl;
        return -1;
    }

    imshow("Imagem Original", image);

    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV_FULL);
    vector<Mat> hsv_planes;
    split(hsv, hsv_planes);

    Mat baseChannel = hsv_planes[0];

    normalize(baseChannel, baseChannel, 0, 255, NORM_MINMAX);

    vector<int> colormaps = {
        COLORMAP_JET, COLORMAP_TURBO, COLORMAP_OCEAN, 
        COLORMAP_HOT, COLORMAP_PARULA
    };

    for(size_t i = 0; i < colormaps.size(); i++){
        Mat colored;
        applyColorMap(baseChannel, colored, colormaps[i]);
        imshow("Colormap " + to_string(i + 1), colored);
    }

    Mat customLUT = createCustomColormap();
    Mat customColor;
    LUT(baseChannel, customLUT, customColor);
    imshow("Colormap Personalizado", customColor);

    waitKey(0);
    return 0;
}

