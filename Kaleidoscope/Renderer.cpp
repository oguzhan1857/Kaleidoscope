#include "pch.h"

Renderer* Renderer::instance()
{
	return *reinterpret_cast<Renderer**>(Patchables::renderer);
}

void Renderer::multiply_matrices(float* out, float* a, float* b)
{
	int size = 4 * 4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.f;
			for (int k = 0; k < 4; k++)
				sum = sum + a[i * 4 + k] * b[k * 4 + j];
			out[i * 4 + j] = sum;
		}
	}
}

Vector2 Renderer::world_to_screen(const Vector3& pos)
{
	float viewProjMatrix[16];
	this->multiply_matrices(viewProjMatrix, get_view_matrix(), get_projection_matrix());
	Vector2 screen = { (float)get_window_width(), (float)get_window_height() };
	static Vector4 clipCoords;
	clipCoords.x = pos.x * viewProjMatrix[0] + pos.y * viewProjMatrix[4] + pos.z * viewProjMatrix[8] + viewProjMatrix[12];
	clipCoords.y = pos.x * viewProjMatrix[1] + pos.y * viewProjMatrix[5] + pos.z * viewProjMatrix[9] + viewProjMatrix[13];
	clipCoords.z = pos.x * viewProjMatrix[2] + pos.y * viewProjMatrix[6] + pos.z * viewProjMatrix[10] + viewProjMatrix[14];
	clipCoords.w = pos.x * viewProjMatrix[3] + pos.y * viewProjMatrix[7] + pos.z * viewProjMatrix[11] + viewProjMatrix[15];
	if (clipCoords.w < 1.0f)
		clipCoords.w = 1.f;
	Vector3 M;
	M.x = clipCoords.x / clipCoords.w;
	M.y = clipCoords.y / clipCoords.w;
	M.z = clipCoords.z / clipCoords.w;
	return Vector2((screen.x / 2.f * M.x) + (M.x + screen.x / 2.f), -(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f));
}