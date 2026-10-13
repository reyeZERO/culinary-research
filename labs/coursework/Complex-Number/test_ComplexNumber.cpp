#include <gtest/gtest.h>
#include "ComplexNumber.h"

TEST(ComplexNumberTest, ConstructorAndGetters) {
    ComplexNumber num(3.0, 4.0);
    EXPECT_FLOAT_EQ(num.getReal(), 3.0);
    EXPECT_FLOAT_EQ(num.getImaginary(), 4.0);
}

TEST(ComplexNumberTest, Addition) {
    ComplexNumber num1(5.0, 7.0);
    ComplexNumber num2(2.5, 3.1);
    ComplexNumber result = num1.add(num2);
    EXPECT_FLOAT_EQ(result.getReal(), 7.5);
    EXPECT_FLOAT_EQ(result.getImaginary(), 10.1);
}

TEST(ComplexNumberTest, Subtraction) {
    ComplexNumber num1(5.0, 7.0);
    ComplexNumber num2(2.5, 3.1);
    ComplexNumber result = num1.subtract(num2);
    EXPECT_FLOAT_EQ(result.getReal(), 2.5);
    EXPECT_FLOAT_EQ(result.getImaginary(), 3.9);
}

TEST(ComplexNumberTest, Multiplication) {
    ComplexNumber num1(2.0, 3.0);
    ComplexNumber num2(4.0, -5.0);
    ComplexNumber result = num1.multiply(num2);
    EXPECT_FLOAT_EQ(result.getReal(), 23.0);
    EXPECT_FLOAT_EQ(result.getImaginary(), 2.0);
}

TEST(ComplexNumberTest, Division) {
    ComplexNumber num1(4.0, 6.0);
    ComplexNumber num2(2.0, 1.0);
    ComplexNumber result = num1.divide(num2);
    EXPECT_FLOAT_EQ(result.getReal(), 3.2);
    EXPECT_FLOAT_EQ(result.getImaginary(), 0.8);
}

TEST(ComplexNumberTest, Negation) {
    ComplexNumber num(3.0, -4.0);
    ComplexNumber result = num.negate();
    EXPECT_FLOAT_EQ(result.getReal(), -3.0);
    EXPECT_FLOAT_EQ(result.getImaginary(), 4.0);
}

TEST(ComplexNumberTest, Conjugation) {
    ComplexNumber num(3.0, -4.0);
    ComplexNumber result = num.conjugate();
    EXPECT_FLOAT_EQ(result.getReal(), 3.0);
    EXPECT_FLOAT_EQ(result.getImaginary(), 4.0);
}

TEST(ComplexNumberTest, Magnitude) {
    ComplexNumber num(3.0, 4.0);
    EXPECT_FLOAT_EQ(num.magnitude(), 5.0);
}

TEST(ComplexNumberTest, Phase) {
    ComplexNumber num(1.0, 1.0);
    EXPECT_FLOAT_EQ(num.phase(), std::atan2(1.0, 1.0));
}

TEST(ComplexNumberTest, PrettyPrint) {
    ComplexNumber num(3.0, -4.0);
    testing::internal::CaptureStdout();
    num.prettyPrint();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "3 + -4i\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
