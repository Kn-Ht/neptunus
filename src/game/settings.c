#ifndef SETTINGS_C
#define SETTINGS_C

#include <stdint.h>

typedef struct {
    /// 0..=100
    uint32_t volume;
    /// 0..=500
    uint32_t frame_limit;
} Settings;

Settings settings_default() {
    return (Settings) {
        .volume = 75,
        .frame_limit = 200
    };
}

#endif // SETTINGS_C