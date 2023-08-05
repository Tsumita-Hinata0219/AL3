#include <Function.h>
#include <assert.h>




// 加算
Vector3 Add(const Vector3 v1, const Vector3 v2) {
	Vector3 result = {};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}


// 減算
Vector3 Subtract(const Vector3 v1, const Vector3 v2) {
	Vector3 result = {};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}


// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
	                 m1.m[0][3] * m2.m[3][0];

	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
	                 m1.m[0][3] * m2.m[3][1];

	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
	                 m1.m[0][3] * m2.m[3][2];

	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
	                 m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
	                 m1.m[1][3] * m2.m[3][0];

	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
	                 m1.m[1][3] * m2.m[3][1];

	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
	                 m1.m[1][3] * m2.m[3][2];

	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
	                 m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
	                 m1.m[2][3] * m2.m[3][0];

	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
	                 m1.m[2][3] * m2.m[3][1];

	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
	                 m1.m[2][3] * m2.m[3][2];

	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
	                 m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
	                 m1.m[3][3] * m2.m[3][0];

	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
	                 m1.m[3][3] * m2.m[3][1];

	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
	                 m1.m[3][3] * m2.m[3][2];

	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
	                 m1.m[3][3] * m2.m[3][3];

	return result;
}


// 拡大縮小行列 (S)
Matrix4x4 MakeScaleMatrix(const Vector3 scale) {
	Matrix4x4 result = {};

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}


// 拡大縮小行列 (S)
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0;
	result.m[0][2] = -std::sin(radian);
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}


// 各軸の合成回転行列 (R)
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ) {
	Matrix4x4 result = {};

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(radianX);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(radianY);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(radianZ);

	result = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	return result;
}


// 並行移動行列 (T)
Matrix4x4 MakeTranslateMatrix(const Vector3 translate) {
	Matrix4x4 result = {};

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
}


// 座標変換
Vector3 Transform(Vector3 vector, Matrix4x4 matrix) {
	Vector3 result = {};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
	           1.0f * matrix.m[3][0];

	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
	           1.0f * matrix.m[3][1];

	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
	           1.0f * matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
	          1.0f * matrix.m[3][3];

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}


// 3次元アフィン変換行列 (W = SRT)
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = {};

	// Scale
	Matrix4x4 scaleMatrix;
	scaleMatrix = MakeScaleMatrix(scale);

	// Rotate
	Matrix4x4 rotateMatrix;
	rotateMatrix = MakeRotateXYZMatrix(rotate.x, rotate.y, rotate.z);

	// Translate
	Matrix4x4 translateMatrix;
	translateMatrix = MakeTranslateMatrix(translate);

	result = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));

	return result;
}


// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {

	/*Vector3 result = {};

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];

	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];

	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];

	return result;*/

	/*Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};
	return result;*/


	 Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};
	return result;
}



float Dot(const Vector3& v1, const Vector3& v2) {
	float result{};
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}
float Length(const Vector3& v) {
	float result{};
	result = sqrt(Dot(v, v));
	return result;
}

// 正規化
Vector3 Normalize(const Vector3& v) {

	/*Vector3 result = {};

	float length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

	result.x = v.x;
	result.y = v.y;
	result.z = v.z;

	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}

	return result;*/


	  Vector3 result{};
	float length = Length(v);
	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;

}


// 2オブジェクト間の距離を求める
float ClacDistance(const Vector3& posA, const Vector3& posB) {

	float dist = 
		(posB.x - posA.x) * (posB.x - posA.x) + 
		(posB.y - posA.y) * (posB.y - posA.y) +
		(posB.z - posA.z) * (posB.z - posA.z);

	return dist;
}


// Matrix4x4の逆行列計算
Matrix4x4 Inverse(const Matrix4x4 m) {
	/*float MatrixFormula;
	MatrixFormula = +(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
	                (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
	                (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])

	                - (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
	                (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
	                (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])

	                - (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
	                (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
	                (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])

	                + (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
	                (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
	                (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])

	                + (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
	                (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
	                (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])

	                - (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
	                (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
	                (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])

	                - (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
	                (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
	                (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])

	                + (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
	                (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
	                (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	Matrix4x4 result = {};

	result.m[0][0] = (1 / MatrixFormula) *
	                 (+(m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) +
	                  (m.m[1][3] * m.m[2][1] * m.m[3][2]) - (m.m[1][3] * m.m[2][2] * m.m[3][1]) -
	                  (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2]));

	result.m[0][1] = (1 / MatrixFormula) *
	                 (-(m.m[0][2] * m.m[2][3] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) -
	                  (m.m[0][3] * m.m[2][1] * m.m[3][2]) + (m.m[0][3] * m.m[2][2] * m.m[0][2]) +
	                  (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2]));

	result.m[0][2] = (1 / MatrixFormula) *
	                 (+(m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) +
	                  (m.m[0][3] * m.m[1][1] * m.m[3][2]) - (m.m[0][3] * m.m[1][2] * m.m[3][1]) -
	                  (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2]));

	result.m[0][3] = (1 / MatrixFormula) *
	                 (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) -
	                  (m.m[0][3] * m.m[1][1] * m.m[2][2]) + (m.m[0][3] * m.m[1][2] * m.m[2][1]) +
	                  (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2]));

	result.m[1][0] = (1 / MatrixFormula) *
	                 (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) -
	                  (m.m[1][3] * m.m[2][0] * m.m[3][2]) + (m.m[1][3] * m.m[2][2] * m.m[3][0]) +
	                  (m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2]));

	result.m[1][1] = (1 / MatrixFormula) *
	                 (+(m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) +
	                  (m.m[0][3] * m.m[2][0] * m.m[3][2]) - (m.m[0][3] * m.m[2][2] * m.m[3][0]) -
	                  (m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2]));

	result.m[1][2] = (1 / MatrixFormula) *
	                 (-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) -
	                  (m.m[0][3] * m.m[1][0] * m.m[3][2]) + (m.m[0][3] * m.m[1][2] * m.m[3][0]) +
	                  (m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2]));

	result.m[1][3] = (1 / MatrixFormula) *
	                 (+(m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) +
	                  (m.m[0][3] * m.m[1][0] * m.m[2][2]) - (m.m[0][3] * m.m[1][2] * m.m[2][0]) -
	                  (m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2]));

	result.m[2][0] = (1 / MatrixFormula) *
	                 (+(m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) +
	                  (m.m[1][3] * m.m[2][0] * m.m[3][1]) - (m.m[1][3] * m.m[2][1] * m.m[3][0]) -
	                  (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1]));

	result.m[2][1] = (1 / MatrixFormula) *
	                 (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) -
	                  (m.m[0][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[2][1] * m.m[3][0]) +
	                  (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1]));

	result.m[2][2] = (1 / MatrixFormula) *
	                 (+(m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) +
	                  (m.m[0][3] * m.m[1][0] * m.m[3][1]) - (m.m[0][3] * m.m[1][1] * m.m[3][0]) -
	                  (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1]));

	result.m[2][3] = (1 / MatrixFormula) *
	                 (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) -
	                  (m.m[0][3] * m.m[1][0] * m.m[2][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0]) +
	                  (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1]));

	result.m[3][0] = (1 / MatrixFormula) *
	                 (-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) -
	                  (m.m[1][2] * m.m[2][0] * m.m[3][1]) + (m.m[1][2] * m.m[2][1] * m.m[3][0]) +
	                  (m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1]));

	result.m[3][1] = (1 / MatrixFormula) *
	                 (+(m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) +
	                  (m.m[0][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[2][1] * m.m[3][0]) -
	                  (m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1]));

	result.m[3][2] = (1 / MatrixFormula) *
	                 (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) -
	                  (m.m[0][2] * m.m[1][0] * m.m[3][1]) + (m.m[0][2] * m.m[1][1] * m.m[3][0]) +
	                  (m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1]));

	result.m[3][3] = (1 / MatrixFormula) *
	                 (+(m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) +
	                  (m.m[0][2] * m.m[1][0] * m.m[2][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0]) -
	                  (m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1]));

	return result;*/


Matrix4x4 result{};
	float as = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
	           m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
	           m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -

	           m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
	           m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
	           m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -

	           m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
	           m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
	           m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +

	           m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
	           m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
	           m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +

	           m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
	           m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
	           m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -

	           m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
	           m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
	           m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -

	           m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
	           m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
	           m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +

	           m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
	           m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
	           m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	assert(as != 0.0f);
	float determinantRecp = 1.0f / as;

	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
	                  m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
	                  m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]

	                  ) *
	                 determinantRecp;
	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
	                  m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
	                  m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) *
	                 determinantRecp;

	result.m[0][2] = (

	                     m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
	                     m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
	                     m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) *
	                 determinantRecp;

	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
	                  m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
	                  m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) *
	                 determinantRecp;
	// 二行目

	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
	                  m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
	                  m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]

	                  ) *
	                 determinantRecp;
	result.m[1][1] = (

	                     m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
	                     m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
	                     m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) *
	                 determinantRecp;

	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
	                  m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
	                  m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) *
	                 determinantRecp;

	result.m[1][3] = (

	                     m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
	                     m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
	                     m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) *
	                 determinantRecp;
	// 三行目

	result.m[2][0] = (

	                     m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
	                     m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
	                     m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]

	                     ) *
	                 determinantRecp;
	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
	                  m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
	                  m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) *
	                 determinantRecp;

	result.m[2][2] = (

	                     m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
	                     m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
	                     m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) *
	                 determinantRecp;

	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
	                  m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
	                  m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) *
	                 determinantRecp;
	// 四行目

	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
	                  m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
	                  m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]

	                  ) *
	                 determinantRecp;
	result.m[3][1] = (

	                     m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
	                     m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
	                     m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) *
	                 determinantRecp;

	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
	                  m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
	                  m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) *
	                 determinantRecp;

	result.m[3][3] = (

	                     m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
	                     m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
	                     m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) *
	                 determinantRecp;

	return result;






}


// perspectiveFovMatrix
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspecrRatio, float nearClip, float farClip) {

	Matrix4x4 result{};

	result.m[0][0] = (1 / aspecrRatio) * 1 / std::tan(fovY / 2);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1 / std::tan(fovY / 2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0.0f;

	return result;
}


// orthographicMatrix
Matrix4x4 MakeOrthographicMatrix(
    float left, float top, float right, float bottom, float nearClip, float farClip) {

	assert(left != right);
	assert(top != bottom);

	Matrix4x4 result{};

	result.m[0][0] = 2 / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2 / (top - bottom);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[2][3] = 0.0f;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	return result;
}

// viewportMatrix
Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth) {

	Matrix4x4 result{};

	result.m[0][0] = width / 2;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height / 2;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}


