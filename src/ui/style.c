//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// StyleAsCode exporter v2.0 - Style data exported as a values array //
//                                                                              //
// USAGE: On init call: GuiLoadStyleDark();                                   //
//                                                                              //
// more info and bugs-report:  github.com/raysan5/raygui // feedback and
// support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2024 raylib technologies (@raylibtech) //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#include "../raywrapper.h"
#include "../game/assets.c"

#define DARK_STYLE_PROPS_COUNT 23

// Custom style name: Dark
static const GuiStyleProp darkStyleProps[DARK_STYLE_PROPS_COUNT] = {
    {0, 0, 0x878787ff},  // DEFAULT_BORDER_COLOR_NORMAL
    {0, 1, 0x2c2c2cff},  // DEFAULT_BASE_COLOR_NORMAL
    {0, 2, 0xc3c3c3ff},  // DEFAULT_TEXT_COLOR_NORMAL
    {0, 3, 0xe1e1e1ff},  // DEFAULT_BORDER_COLOR_FOCUSED
    {0, 4, 0x848484ff},  // DEFAULT_BASE_COLOR_FOCUSED
    {0, 5, 0x181818ff},  // DEFAULT_TEXT_COLOR_FOCUSED
    {0, 6, 0x000000ff},  // DEFAULT_BORDER_COLOR_PRESSED
    {0, 7, 0xefefefff},  // DEFAULT_BASE_COLOR_PRESSED
    {0, 8, 0x202020ff},  // DEFAULT_TEXT_COLOR_PRESSED
    {0, 9, 0x6a6a6aff},  // DEFAULT_BORDER_COLOR_DISABLED
    {0, 10, 0x818181ff}, // DEFAULT_BASE_COLOR_DISABLED
    {0, 11, 0x606060ff}, // DEFAULT_TEXT_COLOR_DISABLED
    {0, 16, 0x00000020}, // DEFAULT_TEXT_SIZE
    {0, 17, 0x00000000}, // DEFAULT_TEXT_SPACING
    {0, 18, 0x9d9d9dff}, // DEFAULT_LINE_COLOR
    {0, 19, 0x111111ff}, // DEFAULT_BACKGROUND_COLOR
    {0, 20, 0x00000018}, // DEFAULT_TEXT_LINE_SPACING
    {1, 5, 0xf7f7f7ff},  // LABEL_TEXT_COLOR_FOCUSED
    {1, 8, 0x898989ff},  // LABEL_TEXT_COLOR_PRESSED
    {4, 5, 0xb0b0b0ff},  // SLIDER_TEXT_COLOR_FOCUSED
    {5, 5, 0x848484ff},  // PROGRESSBAR_TEXT_COLOR_FOCUSED
    {9, 5, 0xf5f5f5ff},  // TEXTBOX_TEXT_COLOR_FOCUSED
    {10, 5, 0xf6f6f6ff}, // VALUEBOX_TEXT_COLOR_FOCUSED
};

// WARNING: This style uses a custom font: "PixelOperator.ttf" (size: 16,
// spacing: 0)

#define DARK_STYLE_FONT_ATLAS_COMP_SIZE 2126

// Style loading function: Dark
static void GuiLoadStyleDark(void) {
    // Load style properties provided
    // NOTE: Default properties are propagated
    for (int i = 0; i < DARK_STYLE_PROPS_COUNT; i++) {
        GuiSetStyle(darkStyleProps[i].controlId, darkStyleProps[i].propertyId,
                    darkStyleProps[i].propertyValue);
    }

    // Custom font loading
    Font font = fonts[FNT_PIXELLARI];

    GuiSetFont(font);

    // Setup a white rectangle on the font to be used on shapes drawing,
    // it makes possible to draw shapes and text (full UI) in a single draw call
    Rectangle fontWhiteRec = { 896, 896, 0, 1 };
    SetShapesTexture(font.texture, fontWhiteRec);

    //-----------------------------------------------------------------

    // TODO: Custom user style setup: Set specific properties here (if required)
    // i.e. Controls specific BORDER_WIDTH, TEXT_PADDING, TEXT_ALIGNMENT
}