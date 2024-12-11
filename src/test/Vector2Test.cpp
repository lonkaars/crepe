#include <gtest/gtest.h>

#include <crepe/api/Vector2.h>

using namespace crepe;

class Vector2Test : public ::testing::Test {
public:
	Vector2<int> int_vec1;
	Vector2<int> int_vec2;
	Vector2<double> double_vec1;
	Vector2<double> double_vec2;
	Vector2<long> long_vec1;
	Vector2<long> long_vec2;
	Vector2<float> float_vec1;
	Vector2<float> float_vec2;

	void SetUp() override {
		int_vec1 = {1, 2};
		int_vec2 = {3, 4};
		double_vec1 = {1.0, 2.0};
		double_vec2 = {3.0, 4.0};
		long_vec1 = {1, 2};
		long_vec2 = {3, 4};
		float_vec1 = {1.0f, 2.0f};
		float_vec2 = {3.0f, 4.0f};
	}
};

TEST_F(Vector2Test, Subtract) {
	Vector2<int> result = int_vec1 - int_vec2;
	EXPECT_EQ(result.x, -2);
	EXPECT_EQ(result.y, -2);

	Vector2<double> result2 = double_vec1 - double_vec2;
	EXPECT_FLOAT_EQ(result2.x, -2.0);
	EXPECT_FLOAT_EQ(result2.y, -2.0);

	Vector2<long> result3 = long_vec1 - long_vec2;
	EXPECT_EQ(result3.x, -2);
	EXPECT_EQ(result3.y, -2);

	Vector2<float> result4 = float_vec1 - float_vec2;
	EXPECT_FLOAT_EQ(result4.x, -2.0f);
	EXPECT_FLOAT_EQ(result4.y, -2.0f);
}

TEST_F(Vector2Test, SubtractScalar) {
	Vector2<int> result = int_vec1 - 1;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);

	Vector2<double> result2 = double_vec1 - 1.0;
	EXPECT_FLOAT_EQ(result2.x, 0.0);
	EXPECT_FLOAT_EQ(result2.y, 1.0);

	Vector2<long> result3 = long_vec1 - 1;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 1);

	Vector2<float> result4 = float_vec1 - 1.0f;
	EXPECT_FLOAT_EQ(result4.x, 0.0f);
	EXPECT_FLOAT_EQ(result4.y, 1.0f);
}

TEST_F(Vector2Test, Add) {
	Vector2<int> result = int_vec1 + int_vec2;
	EXPECT_EQ(result.x, 4);
	EXPECT_EQ(result.y, 6);

	Vector2<double> result2 = double_vec1 + double_vec2;
	EXPECT_FLOAT_EQ(result2.x, 4.0);
	EXPECT_FLOAT_EQ(result2.y, 6.0);

	Vector2<long> result3 = long_vec1 + long_vec2;
	EXPECT_EQ(result3.x, 4);
	EXPECT_EQ(result3.y, 6);

	Vector2<float> result4 = float_vec1 + float_vec2;
	EXPECT_FLOAT_EQ(result4.x, 4.0f);
	EXPECT_FLOAT_EQ(result4.y, 6.0f);
}

TEST_F(Vector2Test, AddScalar) {
	Vector2<int> result = int_vec1 + 1;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 3);

	Vector2<double> result2 = double_vec1 + 1.0;
	EXPECT_FLOAT_EQ(result2.x, 2.0);
	EXPECT_FLOAT_EQ(result2.y, 3.0);

	Vector2<long> result3 = long_vec1 + 1;
	EXPECT_EQ(result3.x, 2);
	EXPECT_EQ(result3.y, 3);

	Vector2<float> result4 = float_vec1 + 1.0f;
	EXPECT_FLOAT_EQ(result4.x, 2.0f);
	EXPECT_FLOAT_EQ(result4.y, 3.0f);
}

TEST_F(Vector2Test, Multiply) {
	Vector2<int> result = int_vec1 * int_vec2;
	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 8);

	Vector2<double> result2 = double_vec1 * double_vec2;
	EXPECT_FLOAT_EQ(result2.x, 3.0);
	EXPECT_FLOAT_EQ(result2.y, 8.0);

	Vector2<long> result3 = long_vec1 * long_vec2;
	EXPECT_EQ(result3.x, 3);
	EXPECT_EQ(result3.y, 8);

	Vector2<float> result4 = float_vec1 * float_vec2;
	EXPECT_FLOAT_EQ(result4.x, 3.0f);
	EXPECT_FLOAT_EQ(result4.y, 8.0f);
}

TEST_F(Vector2Test, MultiplyScalar) {
	Vector2<int> result = int_vec1 * 2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 4);

	Vector2<double> result2 = double_vec1 * 2.0;
	EXPECT_FLOAT_EQ(result2.x, 2.0);
	EXPECT_FLOAT_EQ(result2.y, 4.0);

	Vector2<long> result3 = long_vec1 * 2;
	EXPECT_EQ(result3.x, 2);
	EXPECT_EQ(result3.y, 4);

	Vector2<float> result4 = float_vec1 * 2.0f;
	EXPECT_FLOAT_EQ(result4.x, 2.0f);
	EXPECT_FLOAT_EQ(result4.y, 4.0f);
}

TEST_F(Vector2Test, Divide) {
	Vector2<int> result = int_vec1 / int_vec2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 0);

	Vector2<double> result2 = double_vec1 / double_vec2;
	EXPECT_FLOAT_EQ(result2.x, 0.33333333333333331);
	EXPECT_FLOAT_EQ(result2.y, 0.5);

	Vector2<long> result3 = long_vec1 / long_vec2;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 0);

	Vector2<float> result4 = float_vec1 / float_vec2;
	EXPECT_FLOAT_EQ(result4.x, 0.333333343f);
	EXPECT_FLOAT_EQ(result4.y, 0.5f);
}

TEST_F(Vector2Test, DivideScalar) {
	Vector2<int> result = int_vec1 / 2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);

	Vector2<double> result2 = double_vec1 / 2.0;
	EXPECT_FLOAT_EQ(result2.x, 0.5);
	EXPECT_FLOAT_EQ(result2.y, 1.0);

	Vector2<long> result3 = long_vec1 / 2;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 1);

	Vector2<float> result4 = float_vec1 / 2.0f;
	EXPECT_FLOAT_EQ(result4.x, 0.5f);
	EXPECT_FLOAT_EQ(result4.y, 1.0f);
}

TEST_F(Vector2Test, AddChain) {
	Vector2<int> result = int_vec1;
	result += int_vec2;
	EXPECT_EQ(result.x, 4);
	EXPECT_EQ(result.y, 6);

	Vector2<double> result2 = double_vec1;
	result2 += double_vec2;
	EXPECT_FLOAT_EQ(result2.x, 4.0);
	EXPECT_FLOAT_EQ(result2.y, 6.0);

	Vector2<long> result3 = long_vec1;
	result3 += long_vec2;
	EXPECT_EQ(result3.x, 4);
	EXPECT_EQ(result3.y, 6);

	Vector2<float> result4 = float_vec1;
	result4 += float_vec2;
	EXPECT_FLOAT_EQ(result4.x, 4.0f);
	EXPECT_FLOAT_EQ(result4.y, 6.0f);
}

TEST_F(Vector2Test, AddScalarChain) {
	Vector2<int> result = int_vec1;
	result += 1;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 3);

	Vector2<double> result2 = double_vec1;
	result2 += 1.0;
	EXPECT_FLOAT_EQ(result2.x, 2.0);
	EXPECT_FLOAT_EQ(result2.y, 3.0);

	Vector2<long> result3 = long_vec1;
	result3 += 1;
	EXPECT_EQ(result3.x, 2);
	EXPECT_EQ(result3.y, 3);

	Vector2<float> result4 = float_vec1;
	result4 += 1.0f;
	EXPECT_FLOAT_EQ(result4.x, 2.0f);
	EXPECT_FLOAT_EQ(result4.y, 3.0f);
}

TEST_F(Vector2Test, SubtractChain) {
	Vector2<int> result = int_vec1;
	result -= int_vec2;
	EXPECT_EQ(result.x, -2);
	EXPECT_EQ(result.y, -2);

	Vector2<double> result2 = double_vec1;
	result2 -= double_vec2;
	EXPECT_FLOAT_EQ(result2.x, -2.0);
	EXPECT_FLOAT_EQ(result2.y, -2.0);

	Vector2<long> result3 = long_vec1;
	result3 -= long_vec2;
	EXPECT_EQ(result3.x, -2);
	EXPECT_EQ(result3.y, -2);

	Vector2<float> result4 = float_vec1;
	result4 -= float_vec2;
	EXPECT_FLOAT_EQ(result4.x, -2.0f);
	EXPECT_FLOAT_EQ(result4.y, -2.0f);
}

TEST_F(Vector2Test, SubtractScalarChain) {
	Vector2<int> result = int_vec1;
	result -= 1;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);

	Vector2<double> result2 = double_vec1;
	result2 -= 1.0;
	EXPECT_FLOAT_EQ(result2.x, 0.0);
	EXPECT_FLOAT_EQ(result2.y, 1.0);

	Vector2<long> result3 = long_vec1;
	result3 -= 1;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 1);

	Vector2<float> result4 = float_vec1;
	result4 -= 1.0f;
	EXPECT_FLOAT_EQ(result4.x, 0.0f);
	EXPECT_FLOAT_EQ(result4.y, 1.0f);
}

TEST_F(Vector2Test, MultiplyChain) {
	Vector2<int> result = int_vec1;
	result *= int_vec2;
	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 8);

	Vector2<double> result2 = double_vec1;
	result2 *= double_vec2;
	EXPECT_FLOAT_EQ(result2.x, 3.0);
	EXPECT_FLOAT_EQ(result2.y, 8.0);

	Vector2<long> result3 = long_vec1;
	result3 *= long_vec2;
	EXPECT_EQ(result3.x, 3);
	EXPECT_EQ(result3.y, 8);

	Vector2<float> result4 = float_vec1;
	result4 *= float_vec2;
	EXPECT_FLOAT_EQ(result4.x, 3.0f);
	EXPECT_FLOAT_EQ(result4.y, 8.0f);
}

TEST_F(Vector2Test, MultiplyScalarChain) {
	Vector2<int> result = int_vec1;
	result *= 2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 4);

	Vector2<double> result2 = double_vec1;
	result2 *= 2.0;
	EXPECT_FLOAT_EQ(result2.x, 2.0);
	EXPECT_FLOAT_EQ(result2.y, 4.0);

	Vector2<long> result3 = long_vec1;
	result3 *= 2;
	EXPECT_EQ(result3.x, 2);
	EXPECT_EQ(result3.y, 4);

	Vector2<float> result4 = float_vec1;
	result4 *= 2.0f;
	EXPECT_FLOAT_EQ(result4.x, 2.0f);
	EXPECT_FLOAT_EQ(result4.y, 4.0f);
}

TEST_F(Vector2Test, DivideChain) {
	Vector2<int> result = int_vec1;
	result /= int_vec2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 0);

	Vector2<double> result2 = double_vec1;
	result2 /= double_vec2;
	EXPECT_FLOAT_EQ(result2.x, 0.33333333333333331);
	EXPECT_FLOAT_EQ(result2.y, 0.5);

	Vector2<long> result3 = long_vec1;
	result3 /= long_vec2;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 0);

	Vector2<float> result4 = float_vec1;
	result4 /= float_vec2;
	EXPECT_FLOAT_EQ(result4.x, 0.333333343f);
	EXPECT_FLOAT_EQ(result4.y, 0.5f);
}

TEST_F(Vector2Test, DivideScalarChain) {
	Vector2<int> result = int_vec1;
	result /= 2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);

	Vector2<double> result2 = double_vec1;
	result2 /= 2.0;
	EXPECT_FLOAT_EQ(result2.x, 0.5);
	EXPECT_FLOAT_EQ(result2.y, 1.0);

	Vector2<long> result3 = long_vec1;
	result3 /= 2;
	EXPECT_EQ(result3.x, 0);
	EXPECT_EQ(result3.y, 1);

	Vector2<float> result4 = float_vec1;
	result4 /= 2.0f;
	EXPECT_FLOAT_EQ(result4.x, 0.5f);
	EXPECT_FLOAT_EQ(result4.y, 1.0f);
}

TEST_F(Vector2Test, Negatation) {
	Vector2<int> result = -int_vec1;
	EXPECT_EQ(result.x, -1);
	EXPECT_EQ(result.y, -2);

	Vector2<double> result2 = -double_vec1;
	EXPECT_FLOAT_EQ(result2.x, -1.0);
	EXPECT_FLOAT_EQ(result2.y, -2.0);

	Vector2<long> result3 = -long_vec1;
	EXPECT_EQ(result3.x, -1);
	EXPECT_EQ(result3.y, -2);

	Vector2<float> result4 = -float_vec1;
	EXPECT_FLOAT_EQ(result4.x, -1.0f);
	EXPECT_FLOAT_EQ(result4.y, -2.0f);
}

TEST_F(Vector2Test, Equals) {
	EXPECT_TRUE(int_vec1 == int_vec1);
	EXPECT_FALSE(int_vec1 == int_vec2);
	EXPECT_TRUE(double_vec1 == double_vec1);
	EXPECT_FALSE(double_vec1 == double_vec2);
	EXPECT_TRUE(long_vec1 == long_vec1);
	EXPECT_FALSE(long_vec1 == long_vec2);
}

TEST_F(Vector2Test, NotEquals) {
	EXPECT_FALSE(int_vec1 != int_vec1);
	EXPECT_TRUE(int_vec1 != int_vec2);
	EXPECT_FALSE(double_vec1 != double_vec1);
	EXPECT_TRUE(double_vec1 != double_vec2);
	EXPECT_FALSE(long_vec1 != long_vec1);
	EXPECT_TRUE(long_vec1 != long_vec2);
}

TEST_F(Vector2Test, Truncate) {
	Vector2<int> vec = {3, 4};
	vec.truncate(3);
	EXPECT_EQ(vec.x, 0);
	EXPECT_EQ(vec.y, 0);

	Vector2<double> vec2 = {3.0, 4.0};
	vec2.truncate(3.0);
	EXPECT_FLOAT_EQ(vec2.x, 1.8);
	EXPECT_FLOAT_EQ(vec2.y, 2.4);

	Vector2<long> vec3 = {3, 4};
	vec3.truncate(3);
	EXPECT_EQ(vec3.x, 0);
	EXPECT_EQ(vec3.y, 0);

	Vector2<float> vec4 = {3.0f, 4.0f};
	vec4.truncate(3.0f);
	EXPECT_FLOAT_EQ(vec4.x, 1.8f);
	EXPECT_FLOAT_EQ(vec4.y, 2.4f);
}

TEST_F(Vector2Test, Normalize) {
	Vector2<int> vec = {3, 4};
	vec.normalize();
	EXPECT_EQ(vec.x, 0);
	EXPECT_EQ(vec.y, 0);

	Vector2<double> vec2 = {3.0, 4.0};
	vec2.normalize();
	EXPECT_FLOAT_EQ(vec2.x, 0.6);
	EXPECT_FLOAT_EQ(vec2.y, 0.8);

	Vector2<long> vec3 = {3, 4};
	vec3.normalize();
	EXPECT_EQ(vec3.x, 0);
	EXPECT_EQ(vec3.y, 0);

	Vector2<float> vec4 = {3.0f, 4.0f};
	vec4.normalize();
	EXPECT_FLOAT_EQ(vec4.x, 0.6f);
	EXPECT_FLOAT_EQ(vec4.y, 0.8f);
}

TEST_F(Vector2Test, Length) {
	Vector2<int> vec = {3, 4};
	EXPECT_EQ(vec.length(), 5);

	Vector2<double> vec2 = {3.0, 4.0};
	EXPECT_FLOAT_EQ(vec2.length(), 5.0);

	Vector2<long> vec3 = {3, 4};
	EXPECT_EQ(vec3.length(), 5);

	Vector2<float> vec4 = {3.0f, 4.0f};
	EXPECT_FLOAT_EQ(vec4.length(), 5.0f);
}

TEST_F(Vector2Test, LengthSquared) {
	Vector2<int> vec = {3, 4};
	EXPECT_EQ(vec.length_squared(), 25);

	Vector2<double> vec2 = {3.0, 4.0};
	EXPECT_FLOAT_EQ(vec2.length_squared(), 25.0);

	Vector2<long> vec3 = {3, 4};
	EXPECT_EQ(vec3.length_squared(), 25);

	Vector2<float> vec4 = {3.0f, 4.0f};
	EXPECT_FLOAT_EQ(vec4.length_squared(), 25.0f);
}

TEST_F(Vector2Test, Dot) {
	Vector2<int> vec1 = {3, 4};
	Vector2<int> vec2 = {5, 6};
	EXPECT_EQ(vec1.dot(vec2), 39);

	Vector2<double> vec3 = {3.0, 4.0};
	Vector2<double> vec4 = {5.0, 6.0};
	EXPECT_FLOAT_EQ(vec3.dot(vec4), 39.0);

	Vector2<long> vec5 = {3, 4};
	Vector2<long> vec6 = {5, 6};
	EXPECT_EQ(vec5.dot(vec6), 39);

	Vector2<float> vec7 = {3.0f, 4.0f};
	Vector2<float> vec8 = {5.0f, 6.0f};
	EXPECT_FLOAT_EQ(vec7.dot(vec8), 39.0f);
}

TEST_F(Vector2Test, Distance) {
	Vector2<int> vec1 = {1, 1};
	Vector2<int> vec2 = {4, 5};
	EXPECT_EQ(vec1.distance(vec2), 5);

	Vector2<double> vec3 = {1.0, 1.0};
	Vector2<double> vec4 = {4.0, 5.0};
	EXPECT_FLOAT_EQ(vec3.distance(vec4), 5.0);

	Vector2<long> vec5 = {1, 1};
	Vector2<long> vec6 = {4, 5};
	EXPECT_EQ(vec5.distance(vec6), 5);

	Vector2<float> vec7 = {1.0f, 1.0f};
	Vector2<float> vec8 = {4.0f, 5.0f};
	EXPECT_FLOAT_EQ(vec7.distance(vec8), 5.0f);
}

TEST_F(Vector2Test, DistanceSquared) {
	Vector2<int> vec1 = {3, 4};
	Vector2<int> vec2 = {5, 6};
	EXPECT_EQ(vec1.distance_squared(vec2), 8);

	Vector2<double> vec3 = {3.0, 4.0};
	Vector2<double> vec4 = {5.0, 6.0};
	EXPECT_FLOAT_EQ(vec3.distance_squared(vec4), 8.0);

	Vector2<long> vec5 = {3, 4};
	Vector2<long> vec6 = {5, 6};
	EXPECT_EQ(vec5.distance_squared(vec6), 8);

	Vector2<float> vec7 = {3.0f, 4.0f};
	Vector2<float> vec8 = {5.0f, 6.0f};
	EXPECT_FLOAT_EQ(vec7.distance_squared(vec8), 8.0f);
}

TEST_F(Vector2Test, Perpendicular) {
	Vector2<int> vec = {3, 4};
	Vector2<int> result = vec.perpendicular();
	EXPECT_EQ(result.x, -4);
	EXPECT_EQ(result.y, 3);

	Vector2<double> vec2 = {3.0, 4.0};
	Vector2<double> result2 = vec2.perpendicular();
	EXPECT_FLOAT_EQ(result2.x, -4.0);
	EXPECT_FLOAT_EQ(result2.y, 3.0);

	Vector2<long> vec3 = {3, 4};
	Vector2<long> result3 = vec3.perpendicular();
	EXPECT_EQ(result3.x, -4);
	EXPECT_EQ(result3.y, 3);

	Vector2<float> vec4 = {3.0f, 4.0f};
	Vector2<float> result4 = vec4.perpendicular();
	EXPECT_FLOAT_EQ(result4.x, -4.0f);
	EXPECT_FLOAT_EQ(result4.y, 3.0f);
}
