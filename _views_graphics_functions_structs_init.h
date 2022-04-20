#ifndef VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT
#define VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT

#include "Views.h"
#include <stdio.h>
#include <stdint.h>

void _VIW_InitStructPropertyGraphics(VIW_PropertyGraphics *Struct)
{
    Struct->_useCanvas = false;
    Struct->saveWhileInactive = false;
    Struct->_canvas = NULL;
    Struct->_w = 0;
    Struct->_h = 0;
    Struct->colour = 0;
}

void _VIW_InitStructPropertyGraphicsBase(VIW_PropertyGraphicsBase *Struct)
{
    _VIW_InitStructViewList(&(Struct->_list));
}

#endif // VIEWS_GRAPHICS_FUNCTIONS_STRUCT_INIT