#pragma once

#include "helpers.h"
#include "fastsqrt.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <math.h>

#define MAX(x,y) (x < y? y : x)
#define MIN(x,y) (x > y? y : x)

class rectangle {
protected:
    int up;
    int down;
    int left;
    int right;

public:
    rectangle();
    rectangle(int u, int d, int l, int r);
    rectangle intersect(rectangle & other);
    bool is_valid();
    void print();
};

class drawable_rectangle : public rectangle {
private:
    ALLEGRO_BITMAP * horizontal;
    ALLEGRO_BITMAP * vertical;
    int max_width;
    int max_height;
    bool cleared;
public:
    drawable_rectangle();
    void set_values(int u, int d, int l, int r);
    void draw();
    void clear();

};

struct Vector2D {
    float x;
    float y;

    Vector2D(float x = 0, float y = 0): x(x), y(y) {}

    Vector2D& operator=(const Vector2D &p) {
        x = p.x;
        y = p.y;
        return *this;
    }

    inline bool operator==(const Vector2D &p) const {
        return (x == p.x) && (y == p.y);
    }

    inline Vector2D operator+=(const Vector2D &p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    inline Vector2D operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    inline Vector2D operator-() const {
        return Vector2D(-x, -y);
    }

    friend std::ostream& operator<< (std::ostream& stream, const Vector2D& v) {
        stream << "(" << v.x << ", " << v.y << ")";
        return stream;
    }
};

inline Vector2D rotate(const Vector2D &vect, radians angle) {
    float sine = sin(angle);
    float cosine = cos(angle);
    return Vector2D(vect.x * cosine - vect.y * sine,
                    vect.x * sine + vect.y * cosine);
}

inline Vector2D unit_vector(radians angle) {
    return Vector2D(sin(angle), cos(angle));
}

inline Vector2D perpendicular_vector(const Vector2D &v) {
    return Vector2D(v.y, -v.x);
}

/*
 * Scalar product for Vector2D
 */
inline Vector2D operator*(const Vector2D &p, float scalar) {
    return Vector2D(p.x * scalar, p.y * scalar);
}

inline Vector2D operator*(float scalar, const Vector2D &p) {
    return Vector2D(p.x * scalar, p.y * scalar);
}

inline Vector2D operator+(const Vector2D &p1, const Vector2D &p2) {
    return Vector2D(p1.x + p2.x, p1.y + p2.y);
}

inline Vector2D operator-(const Vector2D &p1, const Vector2D &p2) {
    return Vector2D(p1.x - p2.x, p1.y - p2.y);
}

inline float norm(const Vector2D &v) {
    return fastsqrt(v.x * v.x + v.y * v.y);
}

/*
 * Inner product
 */
inline float dot(const Vector2D &v1, const Vector2D &v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

/*
 * Computes the projection of vector a into vector b
 */
inline Vector2D projection(const Vector2D &a, const Vector2D &b) {
    return b * (dot(b, a) / dot(b, b));
}
