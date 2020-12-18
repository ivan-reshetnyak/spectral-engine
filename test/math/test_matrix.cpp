#include <cstdlib>

#include <CppUnitTest.h>

#include "def.h"
#include "math/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace spectral {
namespace test {

static const int GremlinTestSize = 10000;

TEST_CLASS(test_matrix) {
private:
  matrix M1, M2;
public:
  test_matrix() : M1( 0,  1,  2,  3,
                      4,  5,  6,  7,
                      8,  9, 10, 11,
                     12, 13, 14, 15),
                  M2( 0,  4,  8, 12,
                      1,  5,  9, 13,
                      2,  6, 10, 14,
                      3,  7, 11, 15) {
  }

  TEST_METHOD(TestComparisonTrue) {
    matrix M1C = M1;
    Assert::IsTrue(M1 == M1C);
  }


  TEST_METHOD(TestComparisonFalse) {
    Assert::IsFalse(M1 == M2);
  }


  TEST_METHOD(TestMatrixMultiplication1) {
    Assert::IsTrue(M1 * M2 == matrix(14, 38, 62, 86,
                                     38, 126, 214, 302,
                                     62, 214, 366, 518,
                                     86, 302, 518, 734));
  }


  TEST_METHOD(TestMatrixMultiplication2) {
    matrix M(1, 2, 3, 4,
             5, 6, 7, 8,
             9, 10, 11, 12,
             13, 14, 15, 16);
    Assert::IsTrue(M1 * M == matrix(62, 68, 74, 80,
                                    174, 196, 218, 240,
                                    286, 324, 362, 400,
                                    398, 452, 506, 560));
  }


  TEST_METHOD(TestTranspose) {
    matrix M1T(M1);
    Assert::IsTrue(M1T.Transpose() == M2);
  }


  TEST_METHOD(TestTransposed) {
    matrix M1T(M1);
    Assert::IsTrue(M1T.Transposed() == M2);
  }


  TEST_METHOD(TestInverse) {
    matrix M = matrix(1, 0, 2, 4,
                      0, 1, 2, 3,
                      0, 0, 1, 0,
                      0, 0, 0, 1).Inverse();
    matrix MI = matrix(1, 0, -2, -4,
                       0, 1, -2, -3,
                       0, 0,  1,  0,
                       0, 0,  0,  1);
    Assert::IsTrue(M == MI);
  }
};

} // End of 'test' namespace
} // End of 'spectral' namespace
