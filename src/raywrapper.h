#ifndef RL_WRAPPER_H
#define RL_WRAPPER_H

#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "../raygui/src/raygui.h"

#ifdef DEBUG
#  define debug_fps() DrawFPS(0, 0)
#else
#  define debug_fps()
#endif

// Color from rgb
#define color_rgb(R, G, B) ((Color){(R), (G), (B), 255})

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;
typedef Rectangle Rect;

#define rect(X, Y, W, H) ((Rect){(float)(X), (float)(Y), (float)(W), (float)(H)})
#define vec2(X, Y) ((Vec2){(float)(X), (float)(Y)})
#define vec3(X, Y, Z) ((Vec3){(float)(X), (float)(Y), (float)(Z)})
#define vec4 rect

#endif // RL_WRAPPER_H
