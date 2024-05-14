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
    (TO).img.NAME = LoadTextureFromImage(NAME); \
    UnloadImage(NAME);
#else
#  define add_img(TO, NAME, PATH, _FILETYPE) (TO).img.NAME = LoadTexture(PATH);
#endif
// }

#define add_model(TO, NAME, MODEL_PATH, TEXTURE_PATH) \
    Texture _model_texture_##NAME = LoadTexture(TEXTURE_PATH); \
    (TO).models.NAME = (Object){_model_texture_##NAME, LoadModel(MODEL_PATH)}; \
    SetMaterialTexture(&((TO).models.NAME.model.materials[0]), MATERIAL_MAP_DIFFUSE, _model_texture_##NAME);

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
} Assets;


Assets assets_load() {
    Assets assets;
    add_img(assets, stars, "assets/bg/stars.png", ".png");
    add_model(assets, neptune, "assets/models/neptune.obj", "assets/textures/2k_neptune.png");

    return assets;
}

#define unload_obj(OBJ) do {UnloadTexture(OBJ.texture); UnloadModel(OBJ.model);} while(0);

void assets_unload(Assets* assets) {
    UnloadTexture(assets->img.stars);
    unload_obj(assets->models.neptune);
}

#endif // ASSETS_C
