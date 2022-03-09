#pragma once
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z = 0);

	std::string get_string();

	bool  is_valid() const;
	float distance_to(const Vector3 v) const;
	float distance_to_3d(const Vector3 v) const;
	float in_range(const Vector3 v, float range);

	bool operator==(Vector3 const& other) const;
	bool operator!=(Vector3 const& other) const;

	bool is_zero(float tolerance = 0.01f) const;

	Vector3& switch_yz();
	Vector3& negate();

	Vector2 to_screen();
	Vector2 to_minimap();
};