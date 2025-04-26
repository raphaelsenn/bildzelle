/* 
* Author: Raphael Senn
*/


#include <gtest/gtest.h>

#include "./IMatrix.h"


TEST(IMatrixEqualOperator, IMatrix) {
    IMatrix<int> img1("lena.pgm");
    IMatrix<int> img2("lena.pgm");
    ASSERT_EQ(img1, img2);
}

