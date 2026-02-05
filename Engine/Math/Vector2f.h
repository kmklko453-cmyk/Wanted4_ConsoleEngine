namespace Wanted
{
    struct Vector2f
    {
        float x = 0.0f;
        float y = 0.0f;

        Vector2f() = default;
        Vector2f(float x_, float y_) : x(x_), y(y_) {}

        Vector2f& operator+=(const Vector2f& r) { x += r.x; y += r.y; return *this; }
        Vector2f& operator-=(const Vector2f& r) { x -= r.x; y -= r.y; return *this; }
        Vector2f& operator*=(float s) { x *= s; y *= s; return *this; }
        Vector2f& operator/=(float s) { x /= s; y /= s; return *this; }

        // 단항 - (부호 반전)
        Vector2f operator-() const { return Vector2f(-x, -y); }

        // 이항 - (빼기)
        Vector2f operator-(const Vector2f& r) const { return Vector2f(x - r.x, y - r.y); }
    };
}
