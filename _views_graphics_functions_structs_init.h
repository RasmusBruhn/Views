#ifndef VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT
#define VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT

#include "Views.h"
#include <stdio.h>
#include <stdint.h>

void _VIW_InitStructPropertyGraphics(VIW_PropertyGraphics *Struct)
{
    Struct->useCanvas = false;
    Struct->canvas = NULL;
    Struct->canvasRender = NULL;
}

void _VIW_InitStructPropertyGraphicsBase(VIW_PropertyGraphicsBase *Struct)
{
    _VIW_InitStructViewList(&(Struct->elements));
}

#endif // VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT