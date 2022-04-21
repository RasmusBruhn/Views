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

// Allocate memory
// Add to graphics base list
// Set property data
// Set functions
bool _VIW_CreatePropertyGraphics(VIW_View *View)
{
    // Allocate memory
    VIW_PropertyGraphics *Property = (VIW_PropertyGraphics *)malloc(sizeof(VIW_PropertyGraphics));

    if (Property == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEPROPERTYGRAPHICS_MALLOC, strerror(errno), _VIW_STRING_ERROR_MALLOC);
        return false;
    }

    _VIW_InitStructPropertyGraphics(Property);

    // Add to list in next base
    VIW_ViewList *BaseList = &((VIW_PropertyGraphicsBase *)((VIW_PropertyBase *)View->property._nextBase->property.data)->_list.list[_VIW_ID_PROPERTYTYPEPOS_GRAPHICS]->property.data)->_list;
    
    if (!_VIW_AddToBaseList(BaseList, View))
    {
        free(Property);
        _VIW_AddError(_VIW_ID_ERRORID_CREATEPROPERTYGRAPHICS_BASLIST, _VIW_STRING_ERROR_ADDTOLIST);
        return false;
    }

    View->property._orderList = BaseList;

    // Set property
    View->property.superData = Property;
    View->property._superType = _VIW_ID_PROPERTYTYPE_GRAPHICS;

    // Set functions
    View->property._destroySuperFunc = _VIW_DestroyPropertyGraphics;
    View->property._updateSuperFunc = _VIW_UpdatePropertyGraphics;
    View->property._runSuperFunc = _VIW_RunPropertyGraphics;

    return true;
}

// Remove from base list
// Free canvas
// Reset property values
void _VIW_DestroyPropertyGraphics(VIW_View *View)
{
    // Remove it from the base list
    if (!_VIW_RemoveFromBaseList(View->property._orderList, View))
        _VIW_AddError(_VIW_ID_ERRORID_DESTROYPROPERTYGRAPHICS_LIST, _VIW_STRING_ERROR_REMOVEFROMLIST);

    // Destroy the canvas
    VIW_PropertyGraphics *Property = (VIW_PropertyGraphics *)View->property.superData;
    
    if (Property->_canvas != NULL)
        SDL_DestroyTexture(Property->_canvas);

    // Free the property
    free(Property);

    // Reset values
    View->property.superData = NULL;
    View->property._destroySuperFunc = NULL;
    View->property._orderList = NULL;
    View->property._runSuperFunc = NULL;
    View->property._superType = _VIW_ID_PROPERTYTYPE_NONE;
    View->property._updateSuperFunc = NULL;
}

// Render canvas if available
// Render directly otherwise
bool _VIW_RunPropertyGraphics(VIW_View *View)
{
    // Copy canvas onto the renderer if it exists
    VIW_PropertyGraphics *Property = (VIW_PropertyGraphics *)View->property.superData;

    if (Property->_canvas != NULL)
    {
        // Get rect to copy from
        SDL_Rect Src;
        
        Src.x = View->_shape.boundRect.x - View->_shape.rect.x;
        Src.y = View->_shape.boundRect.y - View->_shape.rect.y;
        Src.w = View->_shape.boundRect.w;
        Src.h = View->_shape.boundRect.h;

        // Copy canvas
        if (SDL_RenderCopy(View->_window.renderer, Property->_canvas, &Src, &View->_shape.boundRect) != 0)
        {
            _VIW_AddErrorForeign(_VIW_ID_ERRORID_RUNPROPERTYGRAPHICS_COPY, SDL_GetError(), _VIW_STRING_ERROR_COPYTEXTURE);
            return false;
        }
    }

    // Draw without canvas
    else
    {
        // Check that a run function has been specified
        if (View->property._runFunc == NULL)
        {
            _VIW_SetError(_VIW_ID_ERRORID_RUNPROPERTYGRAPHICS_RUNEXIST, _VIW_STRING_ERROR_NULLFUNCTION);
            return true;
        }

        // Draw
        if (!View->property._runFunc(View))
        {
            _VIW_AddError(_VIW_ID_ERRORID_RUNPROPERTYGRAPHICS_RUN, _VIW_STRING_ERROR_RENDER);
        }
    }

    return true;
}

bool _VIW_UpdatePropertyGraphics(VIW_View *View)
{

}

#endif // VIEWS_GRAPHICS_FUNCTIONS_INITCLEAN