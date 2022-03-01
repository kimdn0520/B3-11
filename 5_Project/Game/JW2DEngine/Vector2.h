#pragma once

class Vector2
{
public:
	Vector2() : x(0), y(0) {};
	Vector2(float x, float y) : x(x), y(y) {}

	static Vector2 Zero;
	static Vector2 Up;
	static Vector2 Down;
	static Vector2 Left;
	static Vector2 Right;

public:
	Vector2 operator+(Vector2 vec);
	Vector2 operator-(Vector2 vec);
	Vector2 operator*(Vector2 vec);
	Vector2 operator/(Vector2 vec);
	Vector2 operator*(float f);
	Vector2 operator/(float f);

	// ∫§≈Õ¿« ≥ª¿˚ 
	float Dot(Vector2& vec1, Vector2& vec2);

	// ∫§≈Õ ªÁøµ(projection)
	Vector2 Projection(Vector2& vec);

	// ∫§≈Õ ±Ê¿Ã(magnitude)
	float Magnitude();

	// ∫§≈Õ ≥¢∏Æ¿« ∞≈∏Æ(Distance)
	float Distance(Vector2 vec1, Vector2 vec2);

	// ∫§≈Õ ¡§±‘»≠(normalize)
	Vector2 Normalized();

public:
	float x, y;

private:
};

