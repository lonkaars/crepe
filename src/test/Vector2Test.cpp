#include <gtest/gtest.h>

#include <crepe/api/Vector2.h>

using namespace crepe;

class Vector2Test : public ::testing::Test {
public:
	Vector2<int> intVec1;
	Vector2<int> intVec2;
	Vector2<double> doubleVec1;
	Vector2<double> doubleVec2;
	Vector2<long> longVec1;
	Vector2<long> longVec2;
	Vector2<float> floatVec1;
	Vector2<float> floatVec2;

	void SetUp() override {
		intVec1 = {1, 2};
		intVec2 = {3, 4};
		doubleVec1 = {1.0, 2.0};
		doubleVec2 = {3.0, 4.0};
		longVec1 = {1, 2};
		longVec2 = {3, 4};
		floatVec1 = {1.0f, 2.0f};
		floatVec2 = {3.0f, 4.0f};
	}
};

TEST_F(Vector2Test, Subtract) {
	Vector2<int> result = intVec1 - intVec2;
	EXPECT_EQ(result.x, -2);
	EXPECT_EQ(result.y, -2);

	Vector2<double> result2 = doubleVec1 - doubleVec2;
	EXPECT_EQ(result2.x, -2.0);
	EXPECT_EQ(result2.y, -2.0);

	Vector2<long> result3 = longVec1 - longVec2;
	EXPECT_EQ(result3.x, -2);
	EXPECT_EQ(result3.y, -2);

	Vector2<float> result4 = floatVec1 - floatVec2;
	EXPECT_EQ(result4.x, -2.0f);
	EXPECT_EQ(result4.y, -2.0f);
}

TEST_F(Vector2Test, SubtractScalar) {
	Vector2<int> result = intVec1 - 1;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);

	Vector2<double> result2 = doubleVec1 - 1.0;
	EXPECT_EQ(result2.x, 0.0);
	EXPECT_EQ(result2.y, 1.0);

	Vector2<long> result3 = longVec1 - 1;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 1);

	Vector2<float> result4 = floatVec1 - 1.0f;
	EXPECT_EQ(result4.x, 0.0f);
	EXPECT_EQ(result4.y, 1.0f);
}

TEST_F(Vector2Test, Add) {
	Vector2<int> result = intVec1 + intVec2;
	EXPECT_EQ(result.x, 4);
	EXPECT_EQ(result.y, 6);

	Vector2<double> result2 = doubleVec1 + doubleVec2;
	EXPECT_EQ(result2.x, 4.0);
	EXPECT_EQ(result2.y, 6.0);

	Vector2<long> result3 = longVec1 + longVec2;
	EXPECT_EQ(result3.x, 4);
	EXPECT_EQ(result3.y, 6);

	Vector2<float> result4 = floatVec1 + floatVec2;
	EXPECT_EQ(result4.x, 4.0f);
	EXPECT_EQ(result4.y, 6.0f);
}

TEST_F(Vector2Test, AddScalar) {
	Vector2<int> result = intVec1 + 1;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 3);

	Vector2<double> result2 = doubleVec1 + 1.0;
	EXPECT_EQ(result2.x, 2.0);
	EXPECT_EQ(result2.y, 3.0);

	Vector2<long> result3 = longVec1 + 1;
	EXPECT_EQ(result3.x, 2);
	EXPECT_EQ(result3.y, 3);

	Vector2<float> result4 = floatVec1 + 1.0f;
	EXPECT_EQ(result4.x, 2.0f);
	EXPECT_EQ(result4.y, 3.0f);
}

TEST_F(Vector2Test, Multiply) {
	Vector2<int> result = intVec1 * intVec2;
	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 8);

	Vector2<double> result2 = doubleVec1 * doubleVec2;
	EXPECT_EQ(result2.x, 3.0);
	EXPECT_EQ(result2.y, 8.0);

	Vector2<long> result3 = longVec1 * longVec2;
	EXPECT_EQ(result3.x, 3);
	EXPECT_EQ(result3.y, 8);

	Vector2<float> result4 = floatVec1 * floatVec2;
	EXPECT_EQ(result4.x, 3.0f);
	EXPECT_EQ(result4.y, 8.0f);
}

TEST_F(Vector2Test, MultiplyScalar) {
	Vector2<int> result = intVec1 * 2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 4);

	Vector2<double> result2 = doubleVec1 * 2.0;
	EXPECT_EQ(result2.x, 2.0);
	EXPECT_EQ(result2.y, 4.0);

	Vector2<long> result3 = longVec1 * 2;
	EXPECT_EQ(result3.x, 2);
	EXPECT_EQ(result3.y, 4);

	Vector2<float> result4 = floatVec1 * 2.0f;
	EXPECT_EQ(result4.x, 2.0f);
	EXPECT_EQ(result4.y, 4.0f);
}

TEST_F(Vector2Test, Divide) {
	Vector2<int> result = intVec1 / intVec2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 0);

	Vector2<double> result2 = doubleVec1 / doubleVec2;
	EXPECT_EQ(result2.x, 0.33333333333333331);
	EXPECT_EQ(result2.y, 0.5);

	Vector2<long> result3 = longVec1 / longVec2;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 0);

	Vector2<float> result4 = floatVec1 / floatVec2;
	EXPECT_EQ(result4.x, 0.333333343f);
	EXPECT_EQ(result4.y, 0.5f);
}

TEST_F(Vector2Test, DivideScalar) {
	Vector2<int> result = intVec1 / 2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);

	Vector2<double> result2 = doubleVec1 / 2.0;
	EXPECT_EQ(result2.x, 0.5);
	EXPECT_EQ(result2.y, 1.0);

	Vector2<long> result3 = longVec1 / 2;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 1);

	Vector2<float> result4 = floatVec1 / 2.0f;
	EXPECT_EQ(result4.x, 0.5f);
	EXPECT_EQ(result4.y, 1.0f);
}

TEST_F(Vector2Test, AddChain) {
	Vector2<int> result = intVec1;
	result += intVec2;
	EXPECT_EQ(result.x, 4);
	EXPECT_EQ(result.y, 6);

	Vector2<double> result2 = doubleVec1;
	result2 += doubleVec2;
	EXPECT_EQ(result2.x, 4.0);
	EXPECT_EQ(result2.y, 6.0);

	Vector2<long> result3 = longVec1;
	result3 += longVec2;
	EXPECT_EQ(result3.x, 4);
	EXPECT_EQ(result3.y, 6);

	Vector2<float> result4 = floatVec1;
	result4 += floatVec2;
	EXPECT_EQ(result4.x, 4.0f);
	EXPECT_EQ(result4.y, 6.0f);
}

TEST_F(Vector2Test, AddScalarChain) {
	Vector2<int> result = intVec1;
	result += 1;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 3);

	Vector2<double> result2 = doubleVec1;
	result2 += 1.0;
	EXPECT_EQ(result2.x, 2.0);
	EXPECT_EQ(result2.y, 3.0);

	Vector2<long> result3 = longVec1;
	result3 += 1;
	EXPECT_EQ(result3.x, 2);
	EXPECT_EQ(result3.y, 3);

	Vector2<float> result4 = floatVec1;
	result4 += 1.0f;
	EXPECT_EQ(result4.x, 2.0f);
	EXPECT_EQ(result4.y, 3.0f);
}

TEST_F(Vector2Test, SubtractChain) {
	Vector2<int> result = intVec1;
	result -= intVec2;
	EXPECT_EQ(result.x, -2);
	EXPECT_EQ(result.y, -2);

	Vector2<double> result2 = doubleVec1;
	result2 -= doubleVec2;
	EXPECT_EQ(result2.x, -2.0);
	EXPECT_EQ(result2.y, -2.0);

	Vector2<long> result3 = longVec1;
	result3 -= longVec2;
	EXPECT_EQ(result3.x, -2);
	EXPECT_EQ(result3.y, -2);

	Vector2<float> result4 = floatVec1;
	result4 -= floatVec2;
	EXPECT_EQ(result4.x, -2.0f);
	EXPECT_EQ(result4.y, -2.0f);
}

TEST_F(Vector2Test, SubtractScalarChain) {
	Vector2<int> result = intVec1;
	result -= 1;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);

	Vector2<double> result2 = doubleVec1;
	result2 -= 1.0;
	EXPECT_EQ(result2.x, 0.0);
	EXPECT_EQ(result2.y, 1.0);

	Vector2<long> result3 = longVec1;
	result3 -= 1;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 1);

	Vector2<float> result4 = floatVec1;
	result4 -= 1.0f;
	EXPECT_EQ(result4.x, 0.0f);
	EXPECT_EQ(result4.y, 1.0f);
}

TEST_F(Vector2Test, MultiplyChain) {
	Vector2<int> result = intVec1;
	result *= intVec2;
	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 8);

	Vector2<double> result2 = doubleVec1;
	result2 *= doubleVec2;
	EXPECT_EQ(result2.x, 3.0);
	EXPECT_EQ(result2.y, 8.0);

	Vector2<long> result3 = longVec1;
	result3 *= longVec2;
	EXPECT_EQ(result3.x, 3);
	EXPECT_EQ(result3.y, 8);

	Vector2<float> result4 = floatVec1;
	result4 *= floatVec2;
	EXPECT_EQ(result4.x, 3.0f);
	EXPECT_EQ(result4.y, 8.0f);
}

TEST_F(Vector2Test, MultiplyScalarChain) {
	Vector2<int> result = intVec1;
	result *= 2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 4);

	Vector2<double> result2 = doubleVec1;
	result2 *= 2.0;
	EXPECT_EQ(result2.x, 2.0);
	EXPECT_EQ(result2.y, 4.0);

	Vector2<long> result3 = longVec1;
	result3 *= 2;
	EXPECT_EQ(result3.x, 2);
	EXPECT_EQ(result3.y, 4);

	Vector2<float> result4 = floatVec1;
	result4 *= 2.0f;
	EXPECT_EQ(result4.x, 2.0f);
	EXPECT_EQ(result4.y, 4.0f);
}

TEST_F(Vector2Test, DivideChain) {
	Vector2<int> result = intVec1;
	result /= intVec2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 0);

	Vector2<double> result2 = doubleVec1;
	result2 /= doubleVec2;
	EXPECT_EQ(result2.x, 0.33333333333333331);
	EXPECT_EQ(result2.y, 0.5);

	Vector2<long> result3 = longVec1;
	result3 /= longVec2;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 0);

	Vector2<float> result4 = floatVec1;
	result4 /= floatVec2;
	EXPECT_EQ(result4.x, 0.333333343f);
	EXPECT_EQ(result4.y, 0.5f);
}

TEST_F(Vector2Test, DivideScalarChain) {
	Vector2<int> result = intVec1;
	result /= 2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);

	Vector2<double> result2 = doubleVec1;
	result2 /= 2.0;
	EXPECT_EQ(result2.x, 0.5);
	EXPECT_EQ(result2.y, 1.0);

	Vector2<long> result3 = longVec1;
	result3 /= 2;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 1);

	Vector2<float> result4 = floatVec1;
	result4 /= 2.0f;
	EXPECT_EQ(result4.x, 0.5f);
	EXPECT_EQ(result4.y, 1.0f);
}

TEST_F(Vector2Test, Negatation) {
	Vector2<int> result = -intVec1;
	EXPECT_EQ(result.x, -1);
	EXPECT_EQ(result.y, -2);

	Vector2<double> result2 = -doubleVec1;
	EXPECT_EQ(result2.x, -1.0);
	EXPECT_EQ(result2.y, -2.0);

	Vector2<long> result3 = -longVec1;
	EXPECT_EQ(result3.x, -1);
	EXPECT_EQ(result3.y, -2);

	Vector2<float> result4 = -floatVec1;
	EXPECT_EQ(result4.x, -1.0f);
	EXPECT_EQ(result4.y, -2.0f);
}

TEST_F(Vector2Test, Equals) {
	EXPECT_TRUE(intVec1 == intVec1);
	EXPECT_FALSE(intVec1 == intVec2);
	EXPECT_TRUE(doubleVec1 == doubleVec1);
	EXPECT_FALSE(doubleVec1 == doubleVec2);
	EXPECT_TRUE(longVec1 == longVec1);
	EXPECT_FALSE(longVec1 == longVec2);
}

TEST_F(Vector2Test, NotEquals) {
	EXPECT_FALSE(intVec1 != intVec1);
	EXPECT_TRUE(intVec1 != intVec2);
	EXPECT_FALSE(doubleVec1 != doubleVec1);
	EXPECT_TRUE(doubleVec1 != doubleVec2);
	EXPECT_FALSE(longVec1 != longVec1);
	EXPECT_TRUE(longVec1 != longVec2);
}