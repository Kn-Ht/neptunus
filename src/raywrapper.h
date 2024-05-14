#ifndef RL_WRAPPER_H
#define RL_WRAPPER_H

#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"

#ifdef DEBUG
#  define debug_fps() DrawFPS(0, 0)
#else
#  define debug_fps()
#endif

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;
typedef Rectangle Rect;

#define rect(X, Y, W, H) ((Rect){(X), (Y), (W), (H)})
#define vec2(X, Y) ((Vec2){(X), (Y)})
#define vec3(X, Y, Z) ((Vec3){(X), (Y), (Z)})

#endif // RL_WRAPPER_H