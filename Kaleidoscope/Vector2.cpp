#include "pch.h"

Vector2::Vector2()
{
	x = y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	Vector2 result(this->x - v.x, this->y - v.y);
	return result;
}

ImVec2 Vector2::to_imvec()
{
	return ImVec2(this->x, this->y);
}