#ifndef ASSETS_C
#define ASSETS_C

#include "../raywrapper.h"
#include "context.h"
#include <stdio.h>

#define FONT_CODEPOINTS 300

// Binary files (incbin) {
#ifndef DEBUG
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX bin_
#define INCBIN_SILENCE_BITCODE_WARNING
#include "../../incbin/incbin.h"
#endif

Model load_obj(const char* model_path, Texture texture) {
    Model model = LoadModel(model_path);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    return model;
}

///////////////////////////////////////////////////////////////////////////

static RenderTexture render_texture;

enum
{
    TXT_STARS = 0,
    TXT_NEPTUNE_SURFACE,
    TXT_MAX,

    FNT_DOOMED = 0,
    FNT_PIXELLARI,
    FNT_MAX,

    OBJ_NEPTUNE = 0,
    OBJ_MAX,

    SHD_PIXELATE = 0,
    SHD_LIGHTING,
    SHD_MAX,
};

static Texture textures[TXT_MAX];
static const char* texture_paths[] = {
    [TXT_STARS] = "assets/bg/stars.png",
    [TXT_NEPTUNE_SURFACE] = "assets/textures/2k_neptune.png",
};

static Font fonts[FNT_MAX];
static const char* font_paths[] = {
    [FNT_DOOMED] = "assets/fonts/doomed.ttf",
    [FNT_PIXELLARI] = "assets/fonts/Pixellari.ttf"
};

static Model objects[OBJ_MAX];
static const char* object_paths[] = {
    [OBJ_NEPTUNE] = "assets/models/neptune.obj",
};

static Shader shaders[SHD_MAX];
static const char* shader_paths[][2] = {
    [SHD_PIXELATE] = {0, "assets/shaders/pixelate.fs"},
    [SHD_LIGHTING] = {"assets/shaders/lighting.vs", "assets/shaders/lighting.fs"},
};

void load_assets() {
    int i;
    for (i = 0; i < TXT_MAX; i++) textures[i] = LoadTexture(texture_paths[i]);
    for (i = 0; i < FNT_MAX; i++) fonts[i] = LoadFontEx(font_paths[i], FONT_CODEPOINTS, NULL, FONT_CODEPOINTS);
    for (i = 0; i < OBJ_MAX; i++) objects[i] = load_obj(object_paths[i], textures[TXT_NEPTUNE_SURFACE]);
    for (i = 0; i < SHD_MAX; i++) shaders[i] = LoadShader(shader_paths[i][0], shader_paths[i][1]);
    render_texture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

void unload_assets() {
    int i;
    for (i = 0; i < TXT_MAX; i++) UnloadTexture(textures[i]);
    for (i = 0; i < FNT_MAX; i++) UnloadFont(fonts[i]);
    for (i = 0; i < OBJ_MAX; i++) UnloadModel(objects[i]);
    for (i = 0; i < SHD_MAX; i++) UnloadShader(shaders[i]);
    UnloadRenderTexture(render_texture);
}

#endif // ASSETS_C
