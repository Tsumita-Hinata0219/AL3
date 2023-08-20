#pragma once

#include "Struct.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "imgui.h"




///// 3次元ベクトル
// 加算
Vector3 Add(const Vector3 v1, const Vector3 v2);


// 減算
 Vector3 Subtract(const Vector3 v1, const Vector3 v2);


// スカラー倍
Vector3 Multiply(float scalar, const Vector3 v);


///// 行列4x4
// 加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);


// 減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);


// 乗算
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);


// 内積
float Dot(const Vector3 v1, const Vector3 v2);


// 2オブジェクト間の距離を求める
float CalcDistance(const Vector3& posA, const Vector3& posB);


// 長さ
float Length(const Vector3 v);


// 正規化
Vector3 Normalize(const Vector3 v);


// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);


// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);


// 単位行列の作成
Matrix4x4 MakeIdentity4x4();


// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);


// 座標変換
Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix);


// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);


// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3 scele);


// 回転行列(X,Y,Z)
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);


// 回転行列(all)
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);


// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);


// 3次元アフィン変換行列 (W = SRT)
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);


// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspecrRatio, float nearClip, float farClip);


// 正射影行列
Matrix4x4 MakeOrthographicMatrix(
    float left, float top, float right, float bottom, float nearClip, float farClip);


// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);


// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);


// 正射影ベクトル
Vector3 Project(const Vector3 v1, const Vector3 v2);


// 最近接点
Vector3 ClosestPoint(const Vector3 point, const Segment segment);


// 垂直計算
Vector3 Perpendicular(const Vector3& vector);


// 球面線形補間関数
Vector3 sLerp(Vector3& start, Vector3& end, float t);


// 球と球の当たり判定
namespace SphereSphere {

    bool onCollision(const Sphere& s1, const Sphere& s2);
}


// 球と面の当たり判定
namespace SpherePlane {

    bool onCollision(const Sphere& s1, const Plane& p1);
}


// 線と平面の衝突判定
namespace LinePlane {

    bool onCollision(const Segment& s1, const Plane& p1);
}


// 三角形と線の当たり判定
namespace TriangleLine {

	bool onCollision(const Triangle& t1, const Segment& s1);
}


// AABBとAABBの当たり判定
namespace AABBAABB {

	bool onCollision(const AABB& aabb1, const AABB& aabb2);
}


// AABBと球の当たり判定
namespace AABBSphere {

	bool onCollision(const AABB& aabb1, const Sphere& s1);
}