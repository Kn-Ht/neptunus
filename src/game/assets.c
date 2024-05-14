#ifndef ASSETS_C
#define ASSETS_C

#include "../raywrapper.h"

// Binary files (incbin) {
#if !DEBUG
#  define INCBIN_STYLE INCBIN_STYLE_SNAKE
#  define INCBIN_PREFIX bin_
#  include "../../incbin/incbin.h"

#  define add_img(TO, NAME, PATH, FILETYPE) \
    INCBIN(NAME, PATH); \
    Image NAME = LoadImageFromMemory((FILETYPE), bin_##NAME##_data, bin_##NAME##_size); \
    (TO).NAME = LoadTextureFromImage(NAME); \
    UnloadImage(NAME);
#else
#  define add_img(TO, NAME, PATH, _FILETYPE) \
    Image NAME = LoadImage(PATH); \
    (TO).NAME = LoadTextureFromImage(NAME); \
    UnloadImage(NAME);

#endif
// }

typedef struct {
    Texture bg_stars;
} Assets;


Assets assets_load() {
    Assets assets;

    add_img(assets, bg_stars, "assets/bg/stars.png", ".png");

    return assets;
}

void assets_unload(Assets* assets) {
    UnloadTexture(assets->bg_stars);
}

#endif // ASSETS_C
