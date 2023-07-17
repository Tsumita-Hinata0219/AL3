#pragma once

#include <Matrix4x4.h>
#include <Vector3.h>
#include <assert.h>
#include <cmath>



// 加算
Vector3 Add(const Vector3 v1, const Vector3 v2);


// 減算
Vector3 Subtract(const Vector3 v1, const Vector3 v2);


//　行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);


// 拡大縮小行列 (S)
Matrix4x4 MakeScaleMatrix(const Vector3 scale);


// 各軸の回転行列 (X,Y,Z)
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);


// 各軸の合成回転行列 (R)
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);


// 並行移動行列 (T)
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);


// 座標変換
Vector3 Transform(Vector3 vector, Matrix4x4 matrix);


// 3次元アフィン変換行列 (W = SRT)
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);


// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);


// 正規化
Vector3 Normalize(const Vector3& v);