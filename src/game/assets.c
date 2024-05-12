#ifndef ASSETS_C
#define ASSETS_C

#include "../raywrapper.h"

typedef struct {
    Texture stars_bg;
} Assets;

Assets assets_load() {
    Assets assets;

    return assets;
}

void assets_unload(Assets* assets) {
    UnloadTexture(assets->stars_bg);
}

#endif // ASSETS_C
