#ifndef VIEWS_GRAPHICS_FUNCTIONS_FUNCTIONS
#define VIEWS_GRAPHICS_FUNCTIONS_FUNCTIONS

#include "Views.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool _VIW_CreateCanvas(VIW_View *View)
{
    // Check that the property type is correct
    if (View->property._superType != _VIW_ID_PROPERTYTYPE_GRAPHICS)
    {
        _VIW_SetError(_VIW_ID_ERRORID_CREATECANVAS_TYPE, _VIW_STRING_ERROR_TYPE, View->property._superType);
        return false;
    }

    // Check that it does not already have a canvas
    VIW_PropertyGraphics *SuperData = (VIW_PropertyGraphics *)View->property.superData;

    if (SuperData->_useCanvas)
    {
        _VIW_SetError(_VIW_ID_ERRORID_CREATECANVAS_INIT, _VIW_STRING_ERROR_ALREADYINIT);
        return _VIW_UpdateCanvas(View);
    }

    // Create the texture if it is active
    SDL_Texture *Canvas = SDL_CreateTexture(View->_window.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, View->_shape.rect.w, View->_shape.rect.h);

    if (Canvas == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATECANVAS_CANVAS, SDL_GetError(), _VIW_STRING_ERROR_TEXTURE);
        return false;
    }

    // Set values
    SuperData->_canvas = Canvas;
    SuperData->_useCanvas = true;

    return true;
}

bool _VIW_UpdateCanvas(VIW_View *View)
{
    // Check that the property type is correct
    if (View->property._superType != _VIW_ID_PROPERTYTYPE_GRAPHICS)
    {
        _VIW_SetError(_VIW_ID_ERRORID_UPDATECANVAS_TYPE, _VIW_STRING_ERROR_TYPE, View->property._superType);
        return false;
    }

    // Check that it does already have a canvas
    VIW_PropertyGraphics *SuperData = (VIW_PropertyGraphics *)View->property.superData;

    if (!SuperData->_useCanvas)
    {
        _VIW_SetError(_VIW_ID_ERRORID_UPDATECANVAS_INIT, _VIW_STRING_ERROR_NOTINIT);
        return _VIW_UpdateCanvas(View);
    }

    // Create a new texture
    SDL_Texture *Canvas = SDL_CreateTexture(View->_window.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, View->_shape.rect.w, View->_shape.rect.h);

    if (Canvas == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_UPDATECANVAS_CANVAS, SDL_GetError(), _VIW_STRING_ERROR_TEXTURE);
        return false;
    }

    // Destroy the old canvas
    SDL_DestroyTexture(SuperData->_canvas);

    // Insert the new canvas
    SuperData->_canvas = Canvas;

    return true;
}

void _VIW_DestroyCanvas(VIW_View *View)
{
    // Check that the property type is correct
    if (View->property._superType != _VIW_ID_PROPERTYTYPE_GRAPHICS)
    {
        _VIW_SetError(_VIW_ID_ERRORID_DESTROYCANVAS_TYPE, _VIW_STRING_ERROR_TYPE, View->property._superType);
        return;
    }

    // Check that it has a canvas
    VIW_PropertyGraphics *SuperData = (VIW_PropertyGraphics *)View->property.superData;

    if (SuperData->_canvas != NULL)
    {
        _VIW_SetError(_VIW_ID_ERRORID_DESTROYCANVAS_INIT, _VIW_STRING_ERROR_NOTINIT);
        return;
    }

    // Destroy it
    SDL_DestroyTexture(SuperData->_canvas);
    SuperData->_canvas = NULL;
    SuperData->_useCanvas = false;
}

#endif // VIEWS_GRAPHICS_FUNCTIONS_FUNCTIONS