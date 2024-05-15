#ifndef ASSETS_C
#define ASSETS_C

#include "../raywrapper.h"
#include <stdio.h>

#define FONT_CODEPOINTS 300

// Binary files (incbin) {
#if !DEBUG
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX bin_
#include "../../incbin/incbin.h"

#define add_img(TO, NAME, PATH, FILETYPE)                                      \
    INCBIN(NAME, PATH);                                                        \
    Image NAME =                                                               \
        LoadImageFromMemory((FILETYPE), bin_##NAME##_data, bin_##NAME##_size); \
    (TO).img.NAME = LoadTextureFromImage(NAME);                                \
    UnloadImage(NAME);

#define add_font(TO, NAME, PATH, TYPE)                                         \
    INCBIN(NAME, PATH);                                                        \
    (TO).fonts.NAME =                                                          \
        LoadFontFromMemory((TYPE), bin_##NAME##_data, bin_##NAME##_size,       \
                           FONT_CODEPOINTS, NULL, 0);

#else
#define add_img(TO, NAME, PATH, _FILETYPE) (TO).img.NAME = LoadTexture(PATH);
#define add_font(TO, NAME, PATH, _TYPE)                                        \
    (TO).fonts.NAME = LoadFontEx(PATH, FONT_CODEPOINTS, NULL, 0);
#endif
// }

#define add_model(TO, NAME, MODEL_PATH, TEXTURE_PATH)                          \
    Texture _model_texture_##NAME = LoadTexture(TEXTURE_PATH);                 \
    (TO).models.NAME = (Object){_model_texture_##NAME, LoadModel(MODEL_PATH)}; \
    SetMaterialTexture(&((TO).models.NAME.model.materials[0]),                 \
                       MATERIAL_MAP_DIFFUSE, _model_texture_##NAME);

typedef struct {
    Font doomed;
} Fonts;

typedef struct {
    Texture stars;
} Images;

typedef struct {
    Texture texture;
    Model model;
} Object;

typedef struct {
    Object neptune;
} Models;

typedef struct {
    Images img;
    Models models;
    Fonts fonts;
} Assets;

Assets assets_load() {
    Assets assets;
    add_img(assets, stars, "assets/bg/stars.png", ".png");
    add_model(assets, neptune, "assets/models/neptune.obj",
              "assets/textures/2k_neptune.png");
    add_font(assets, doomed, "assets/fonts/doomed.ttf", ".TTF");
    return assets;
}

#define unload_obj(OBJ)                                                        \
    do {                                                                       \
        UnloadTexture(OBJ.texture);                                            \
        UnloadModel(OBJ.model);                                                \
    } while (0)

void assets_unload(Assets *assets) {
    UnloadTexture(assets->img.stars);
    unload_obj(assets->models.neptune);
    UnloadFont(assets->fonts.doomed);
}

#endif // ASSETS_C
