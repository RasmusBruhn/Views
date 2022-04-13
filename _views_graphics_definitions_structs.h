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
    bool useCanvas;                 // True if it has the graphics stored in a texture
    SDL_Texture *canvas;            // The texture for the graphics of the view
    SDL_Renderer *canvasRender;     // The renderer for the canvas
};

struct __VIW_PropertyGraphicsBase
{
    VIW_ViewList elements;          // The different elements to draw on the canvas
};

#endif // VIEWS_GRAPHICS_DEFINITIONS_STRUCTS