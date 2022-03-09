#pragma once

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4()
	{
		x = y = z = w = 0.0f;
	}

	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};