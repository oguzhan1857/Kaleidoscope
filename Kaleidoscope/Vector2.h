#pragma once
#include "imgui/imgui.h"

class Vector2
{
public:
	float x;
	float y;
	Vector2();
	Vector2(float x, float y);

	Vector2 operator-(const Vector2& v) const;

	ImVec2 to_imvec();
};