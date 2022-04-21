#ifndef VIEWS_GRAPHICS_FUNCTIONS_INITCLEAN
#define VIEWS_GRAPHICS_FUNCTIONS_INITCLEAN

#include "Views.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>


// Check if it needs a new canvas
// Create new canvas
// Destroy old canvas if needed
bool _VIW_CreateCanvas(VIW_View *View)
{
    // Get the data
    VIW_PropertyGraphics *SuperData = (VIW_PropertyGraphics *)View->property.superData;

    // Abort if it does not need to be added
    if (SuperData->_canvas != NULL && SuperData->_w == View->_shape.rect.w && SuperData->_h == View->_shape.rect.h)
        return true;

    // Create the new canvas
    SDL_Texture *Canvas = SDL_CreateTexture(View->_window.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, View->_shape.rect.w, View->_shape.rect.h);

    if (Canvas == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATECANVAS_CANVAS, SDL_GetError(), _VIW_STRING_ERROR_TEXTURE);
        return false;
    }

    // Remove old canvas if it is there
    if (SuperData->_canvas != NULL)
        SDL_DestroyTexture(SuperData->_canvas);

    // Set canvas
    SuperData->_canvas = Canvas;

    return true;
}

// Check that there is a canvas
// Destroy canvas
void _VIW_DestroyCanvas(VIW_View *View)
{
    // Check that it has a canvas
    VIW_PropertyGraphics *SuperData = (VIW_PropertyGraphics *)View->property.superData;

    if (SuperData->_canvas != NULL)
    {
        _VIW_SetError(_VIW_ID_ERRORID_DESTROYCANVAS_INIT, _VIW_STRING_ERROR_NOTINIT);
        return;
    }

    // Destroy it
    SDL_DestroyTexture(SuperData->_canvas);
}

bool _VIW_CreatePropertyGraphics(VIW_View *View)
{
    // Allocate memory
    VIW_PropertyGraphics *Property = (VIW_PropertyGraphics *)malloc(sizeof(VIW_PropertyGraphics));

    if (Property == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEPROPERTYGRAPHICS_MALLOC, strerror(errno), _VIW_STRING_ERROR_MALLOC);
        return false;
    }

    // Add to list in next base
    View->property.

    // Set property
    View->property.superData = Property;
    View->property._superType = _VIW_ID_PROPERTYTYPE_GRAPHICS;
    
    // Set functions
    View->property._destroySuperFunc = _VIW_DestroyPropertyGraphics;
    View->property._updateSuperFunc = _VIW_UpdatePropertyGraphics;
    View->property._runSuperFunc = _VIW_RunPropertyGraphics;
}

void _VIW_DestroyPropertyGraphics(VIW_View *View)
{

}

bool _VIW_RunPropertyGraphics(VIW_View *View)
{

}

bool _VIW_UpdatePropertyGraphics(VIW_View *View)
{

}

#endif // VIEWS_GRAPHICS_FUNCTIONS_INITCLEAN