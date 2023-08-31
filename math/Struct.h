#pragma once
#include <vector>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4x4.h>


// サウンド
struct Sound {
	uint32_t game;
	uint32_t over;
	uint32_t clear;
	uint32_t boss;
	uint32_t decision;
	uint32_t eneDie;
	uint32_t plaDie;
	uint32_t plaDamage;
	uint32_t shoot1;
};


// 球
struct Sphere {
	Vector3 center;
	float radius;
};

// 直線
struct Line {
	Vector3 origin; // !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};

// 半直線
struct Ray {
	Vector3 origin; // !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};

// 線分
struct Segment {
	Vector3 origin; // !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};

// 平面
struct Plane {
	Vector3 normal; // !< 法線
	float distance; // !< 距離
};

// 三角形
struct Triangle {
	Vector3 vertices[3]; // !< 頂点
};

struct AABB {
	Vector3 min; // !< 最少点
	Vector3 max; // !< 最大点
};

