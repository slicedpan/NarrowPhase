#pragma once

#include <svl\SVL.h>

inline Mat4 qGetTransform(Vec4& quat)
{
	float a = quat[0];
	float b = quat[1];
	float c = quat[2];
	float d = quat[3];
	float m00 = pow(a, 2) + pow(b, 2) - pow(c, 2) - pow(d, 2);
	float m10 = 2 * b *c - 2 * a * d;
	float m20 = 2 * b * d + 2 * a * c;
	float m30 = 0.0f;
	float m01 = 2 * b * c + 2 * a * d;
	float m11 = pow(a, 2) - pow(b, 2) + pow(c, 2) - pow(d, 2);
	float m21 = 2 * c * d - 2 * a * b;
	float m31 = 0.0f;
	float m02 = 2 * b * d - 2 * a * c;
	float m12 = 2 * c * d + 2 * a * b;
	float m22 = pow(a, 2) - pow(b, 2) - pow(c, 2) + pow(d, 2);
	float m32 = 0.0f;
	float m03 = 0.0f;
	float m13 = 0.0f;
	float m23 = 0.0f;
	float m33 = 1.0f;
	return Mat4(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
}

inline Vec4 qMultiply(Vec4 q1, Vec4 q2)
{
	Vec4 retVec;
	retVec[0] = q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3];
	retVec[1] = q1[0] * q2[1] - q1[1] * q2[0] + q1[2] * q2[3] - q1[3] * q2[2];
	retVec[2] = q1[0] * q2[2] - q1[1] * q2[3] + q1[2] * q2[0] + q1[3] * q2[1];
	retVec[3] = q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1] + q1[3] * q2[0];
	return retVec;
}