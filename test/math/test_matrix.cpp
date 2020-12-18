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


  TEST_METHOD(TestTranspose) {
    matrix M1T(M1);
    Assert::IsTrue(M1T.Transpose() == M2);
  }
};

} // End of 'test' namespace
} // End of 'spectral' namespace
