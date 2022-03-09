#include "pch.h"

Vector3::Vector3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

std::string Vector3::get_string()
{
	char buffer[255];
	sprintf_s(buffer, 255, "(%f, %f, %f)", x, y, z);
	return std::string(buffer);
}

bool Vector3::is_valid() const
{
	return this->x != 0 && this->y != 0;
}

float Vector3::distance_to(const Vector3 v) const
{
	return (float)sqrt(pow(v.x - x, 2) + pow(v.z - z, 2));
}

float Vector3::distance_to_3d(const Vector3 v) const
{
	return (float)sqrt(pow(v.x - x, 2) + pow(v.z - z, 2) + pow(v.y - y, 2));
}

float Vector3::in_range(const Vector3 v, float range)
{
	return this->distance_to(v) <= range;
}

bool Vector3::operator==(Vector3 const& other) const
{
	return other.x == this->x && other.y == this->y;
}

bool Vector3::operator!=(Vector3 const& other) const
{
	return other.x == this->x && other.y == this->y;
}

bool Vector3::is_zero(float tolerance) const
{
	return this->x > -tolerance && this->x < tolerance&&
		this->y > -tolerance && this->y < tolerance;
}

Vector3& Vector3::switch_yz()
{
	const auto temp = this->y;

	this->y = this->z;
	this->z = temp;
	return *this;
}

Vector3& Vector3::negate()
{
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;

	return *this;
}

Vector2 Vector3::to_screen()
{
	auto screen_pos = Renderer::instance()->world_to_screen(*this);
	return Vector2(screen_pos.x, screen_pos.y);
}

Vector2 Vector3::to_minimap()
{
	float x, y;
	MenuGUI::instance()->get_tactical_map()->world_to_minimap(this, &x, &y);
	return Vector2(x, y);
}