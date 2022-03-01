#include "pch.h"
#include "Vector2.h"

Vector2 Vector2::Zero = Vector2(0, 0);
Vector2 Vector2::Up = Vector2(0, -1);
Vector2 Vector2::Down = Vector2(0, 1);
Vector2 Vector2::Left = Vector2(-1, 0);
Vector2 Vector2::Right = Vector2(1, 0);

Vector2 Vector2::operator+(Vector2 vec)
{
	Vector2 r;
	r.x = this->x + vec.x;
	r.y = this->y + vec.y;
	return r;
}

Vector2 Vector2::operator-(Vector2 vec)
{
	Vector2 r;
	r.x = this->x - vec.x;
	r.y = this->y - vec.y;
	return r;
}

Vector2 Vector2::operator*(Vector2 vec)
{
	Vector2 r;
	r.x = this->x * vec.x;
	r.y = this->y * vec.y;
	return r;
}

Vector2 Vector2::operator/(Vector2 vec)
{
	Vector2 r;
	r.x = this->x / vec.x;
	r.y = this->y / vec.y;
	return r;
}

Vector2 Vector2::operator*(float f)
{
	Vector2 r;
	r.x = this->x * f;
	r.y = this->y * f;
	return r;
}

Vector2 Vector2::operator/(float f)
{
	Vector2 r;
	r.x = this->x / f;
	r.y = this->y / f;
	return r;
}
float Vector2::Dot(Vector2& vec1, Vector2& vec2)
{
	return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

/// <summary>
/// vec에 사영한 결과를 반환
/// </summary>
Vector2 Vector2::Projection(Vector2& vec)
{
	Vector2 vecNormal = vec.Normalized();
	float projSclar = Dot(vecNormal, *this);

	Vector2 result;
	result.x = vecNormal.x * projSclar;
	result.y = vecNormal.y * projSclar;

	return result;
}

float Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

float Vector2::Distance(Vector2 vec1, Vector2 vec2)
{
	return (vec1 - vec2).Magnitude();
}

Vector2 Vector2::Normalized()
{
	Vector2 r;

	float len = this->Magnitude();
	r = *this / len;

	if(len == 0) { return Vector2(0, 0); }

	return r;
}
