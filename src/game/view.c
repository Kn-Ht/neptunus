#ifndef VIEW_C
#define VIEW_C

#include "../game.c"

void update_view(Camera3D* camera) {
    // Calculate new rotation angles
    static float pitch = 0.0f;
    static float yaw = 0.0f;
    static float sens = 0.0f;

    sens = settings.sensitivity * 0.1;

    yaw += ctx.mouse_delta.x * sens;
    pitch -= ctx.mouse_delta.y * sens; // Invert pitch change

    // Clamp pitch to avoid flipping
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Calculate the new forward vector
    Vector3 forward = {
        .x = cosf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch),
        .y = sinf(DEG2RAD * pitch),
        .z = sinf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch),
    };

    camera->target = Vector3Add(camera->position, forward);
}

#endif // VIEW_C