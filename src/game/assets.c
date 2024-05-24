#ifndef ASSETS_C
#define ASSETS_C

#define ASSETS_MAX 64

#include "../raywrapper.h"
#include <stdio.h>

#define FONT_CODEPOINTS 300

// Binary files (incbin) {
#ifndef DEBUG
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX bin_
#define INCBIN_SILENCE_BITCODE_WARNING
#include "../../incbin/incbin.h"
#endif

Model load_obj(char* model_path, Texture texture) {
    Model model = LoadModel(model_path);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    return model;
}

///////////////////////////////////////////////////////////////////////////

static Texture textures[ASSETS_MAX];
enum {
    TXT_STARS,
    TXT_NEPTUNE_SURFACE,

    TXT_MAX,
};
static const char* texture_paths[] = {
    [TXT_STARS] = "assets/bg/stars.png",
    [TXT_NEPTUNE_SURFACE] = "assets/textures/2k_neptune.png",
};

static Font fonts[ASSETS_MAX];
enum {
    FNT_DOOMED,

    FNT_MAX,
};
static const char* font_paths[] = {
    [FNT_DOOMED] = "assets/fonts/doomed.ttf"
};

static Model objects[ASSETS_MAX];
enum {
    OBJ_NEPTUNE,

    OBJ_MAX,
};
static const char* object_paths[] = {
    [OBJ_NEPTUNE] = "assets/models/neptune.obj",
};

void load_assets() {
    int i;
    for (i = 0; i < TXT_MAX; i++) textures[i] = LoadTexture(texture_paths[i]);
    for (i = 0; i < FNT_MAX; i++) fonts[i] = LoadFontEx(font_paths[i], FONT_CODEPOINTS, NULL, FONT_CODEPOINTS);
    for (i = 0; i < OBJ_MAX; i++) objects[i] = load_obj(object_paths[i], textures[TXT_NEPTUNE_SURFACE]);
}

void unload_assets() {
    int i;
    for (i = 0; i < TXT_MAX; i++) UnloadTexture(textures[i]);
    for (i = 0; i < FNT_MAX; i++) UnloadFont(fonts[i]);
    for (i = 0; i < OBJ_MAX; i++) UnloadModel(objects[i]);
}

#endif // ASSETS_C
