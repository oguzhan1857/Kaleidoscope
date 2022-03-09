#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "macros.h"

class Renderer
{
public:
	static Renderer* instance();

	MAKE_GET(window_width, int, Renderer)
	MAKE_GET(window_height, int, Renderer)
	MAKE_GET_PTR(view_matrix, float*, Renderer)
	MAKE_GET_PTR(projection_matrix, float*, Renderer)

	void multiply_matrices(float* out, float* a, float* b);
	Vector2 world_to_screen(const Vector3& pos);
};