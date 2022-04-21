#ifndef VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT
#define VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT

#include "Views.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void _VIW_InitStructColour32(VIW_Colour32 *Struct)
{
    Struct->r = 0;
    Struct->g = 0;
    Struct->b = 0;
    Struct->a = 0;
}

void _VIW_InitStructPropertyGraphics(VIW_PropertyGraphics *Struct)
{
    Struct->_useCanvas = false;
    Struct->saveWhileInactive = false;
    Struct->_canvas = NULL;
    Struct->_w = 0;
    Struct->_h = 0;
    _VIW_InitStructColour32(&Struct->colour);
}

void _VIW_InitStructPropertyGraphicsBase(VIW_PropertyGraphicsBase *Struct)
{
    _VIW_InitStructViewList(&(Struct->_list));
}

#endif // VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT