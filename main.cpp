#include "./IMatrix.h"
#include <string>

int main() {

    IMatrix<int> image;
    image.readImage("lena.pgm");
    image.writeImage("lena_copy.pgm");
}
