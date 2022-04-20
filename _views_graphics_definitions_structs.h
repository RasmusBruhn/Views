#ifndef VIEWS_GRAPHICS_DEFINITIONS_STRUCTS
#define VIEWS_GRAPHICS_DEFINITIONS_STRUCTS

#include "Views.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct __VIW_PropertyGraphics VIW_PropertyGraphics;
typedef struct __VIW_PropertyGraphicsBase VIW_PropertyGraphicsBase;

struct __VIW_PropertyGraphics
{
    bool _useCanvas;                // True if it has the graphics stored in a texture
    bool saveWhileInactive;         // True if it should save the canvas while the view is inactive
    SDL_Texture *_canvas;           // The texture for the graphics of the view
    int32_t _w;                     // The width of the canvas
    int32_t _h;                     // The height of the canvas
    uint32_t colour;                // The colour of the background in AABBGGRR mode
};

struct __VIW_PropertyGraphicsBase
{
    VIW_ViewList _list;          // The different elements to draw on the canvas
};

#endif // VIEWS_GRAPHICS_DEFINITIONS_STRUCTS