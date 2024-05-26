#ifndef SETTINGS_C
#define SETTINGS_C

#include <stdint.h>

enum
{
    VOLUME_MIN = 0,
    VOLUME_DEF = 75,
    VOLUME_MAX = 100,
    FPS_MIN = 30,
    FPS_DEF = 200,
    FPS_MAX = 500,
    SENS_MIN = 1,
    SENS_DEF = 1,
    SENS_MAX = 10,
    FOV_MIN = 30,
    FOV_DEF = 80,
    FOV_MAX = 120,
};

typedef struct {
    float volume;
    uint32_t frame_limit;
    bool antialiasing;
    uint32_t sensitivity;
} Settings;

static Settings settings = {
    .volume = VOLUME_DEF,
    .frame_limit = FPS_DEF,
    .antialiasing = false,
    .sensitivity = SENS_DEF,
};

Settings settings_default() {
    return (Settings) {
        .volume = VOLUME_DEF,
        .frame_limit = FPS_DEF,
        .antialiasing = false,
        .sensitivity = SENS_DEF,
    };
}

/// Apply the fields from `settings`
void apply_settings() {
    SetMasterVolume(settings.volume);
    SetTargetFPS(settings.frame_limit);
    if (settings.antialiasing) SetWindowState(FLAG_MSAA_4X_HINT);
    else ClearWindowState(FLAG_MSAA_4X_HINT);
}


#endif // SETTINGS_C