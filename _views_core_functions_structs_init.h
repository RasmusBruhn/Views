// Adds functions to initialise structs
#ifndef VIEWS_CORE_FUNCTIONS_STRUCTS_INIT_H_INCLUDED
#define VIEWS_CORE_FUNCTIONS_STRUCTS_INIT_H_INCLUDED

#include <Views.h>

void _VIW_InitStructViewList(VIW_ViewList *Struct)
{
    Struct->count = 0;
    Struct->list = NULL;
}

void _VIW_InitStructView(VIW_View *Struct)
{
    _VIW_InitStructParent(&Struct->_parent);
    _VIW_InitStructChild(&Struct->_child);
    _VIW_InitStructProperty(&Struct->property);
    _VIW_InitStructFlagsSet(&Struct->_flags);
    _VIW_InitStructFlags(&Struct->flags);
    _VIW_InitStructWindow(&Struct->_window);
    _VIW_InitStructShape(&Struct->_shape);
    _VIW_InitStructBounds(&Struct->_bounds);
    _VIW_InitStructShapeData(&Struct->shapeData);
}

void _VIW_InitStructParent(VIW_Parent *Struct)
{
    Struct->childPos = 0;
    Struct->parent = NULL;
    Struct->root = NULL;
}

void _VIW_InitStructChild(VIW_Child *Struct)
{
    _VIW_InitStructViewList(&Struct->list);
}

void _VIW_InitStructProperty(VIW_Property *Struct)
{
    Struct->data = NULL;
    Struct->order = 0;
    Struct->_type = _VIW_ID_PROPERTY_NONE;
    Struct->_updateFunc = NULL;
    Struct->_destroyFunc = NULL;
    Struct->_activateFunc = NULL;
    Struct->_deactivateFunc = NULL;
    Struct->_runType = _VIW_ID_PROPERTYTYPE_NONE;
    Struct->_nextBase = NULL;
}

void _VIW_InitStructFlagsSet(VIW_FlagsSet *Struct)
{
    Struct->active = true;
    Struct->totalActive = true;
    Struct->updateNextSibling = false;
    Struct->updateAllSiblings = false;
}

void _VIW_InitStructFlags(VIW_Flags *Struct)
{
    Struct->freezeShape = false;
    Struct->active = true;
}

void _VIW_InitStructWindow(VIW_Window *Struct)
{
    Struct->rend = NULL;
    Struct->window = NULL;
    Struct->ID = 0;
}

void _VIW_InitStructShape(VIW_Shape *Struct)
{
    OBJ_SetRect(Struct->boundRect, 0, 0, 0, 0);
    OBJ_SetRect(Struct->rect, 0, 0, 0, 0);
}

void _VIW_InitStructBounds(VIW_Bounds *Struct)
{
    OBJ_SetRect(Struct->rect, 0, 0, 0, 0);
}

void _VIW_InitStructShapeData(VIW_ShapeData *Struct)
{
    Struct->type = VIW_ID_SHAPE_NONE;
}

void _VIW_InitStructRect(VIW_Rect *Struct)
{
    _VIW_InitStructRectPart(&Struct->x);
    _VIW_InitStructRectPart(&Struct->y);
}

void _VIW_InitStructRectPart(VIW_RectPart *Struct)
{
    Struct->type = VIW_ID_RECT_NONE;
}

void _VIW_InitStructRectOrigin(VIW_RectOrigin *Struct)
{
    Struct->origin = VIW_ID_ANCHOR_NONE;
    _VIW_InitStructPos(&Struct->pos);
    _VIW_InitStructSize(&Struct->size);
}

void _VIW_InitStructRectStretch(VIW_RectStretch *Struct)
{
    _VIW_InitStructPos(&Struct->pos1);
    _VIW_InitStructPos(&Struct->pos2);
}

void _VIW_InitStructSize(VIW_Size *Struct)
{
    Struct->type = VIW_ID_SIZE_NONE;
    Struct->scale = 1;
}

void _VIW_InitStructSizeDiff(VIW_SizeDiff *Struct)
{
    _VIW_InitStructPos(&Struct->pos1);
    _VIW_InitStructPos(&Struct->pos2);
}

void _VIW_InitStructPos(VIW_Pos *Struct)
{
    Struct->type = VIW_ID_POS_NONE;
}

void _VIW_InitStructBiasAnchor(VIW_BiasAnchor *Struct)
{
    _VIW_InitStructAnchor(&Struct->anchor1);
    _VIW_InitStructAnchor(&Struct->anchor2);
    Struct->bias = 0.5;
}

void _VIW_InitStructAnchor(VIW_Anchor *Struct)
{
    Struct->anchorPoint = VIW_ID_ANCHOR_NONE;
    Struct->offset = 0;
    _VIW_InitStructReference(&Struct->ref);
}

void _VIW_InitStructReference(VIW_Reference *Struct)
{
    Struct->ref = NULL;
    Struct->view = VIW_ID_RELATION_NONE;
}

/*
void _VIW_InitStructEvent(VIW_Event *Struct)
{
    Struct->ID = 0;
    _VIW_InitStructViewList(&Struct->list);
}

void _VIW_InitStructEventList(VIW_EventList *Struct)
{
    Struct->count = 0;
    Struct->list = NULL;
}

void _VIW_InitStructScript(VIW_Script *Struct)
{
    Struct->view = NULL;
    Struct->time = -1;
    Struct->increase = 0;
}

void _VIW_InitStructScriptList(VIW_ScriptList *Struct)
{
    Struct->list = NULL;
    Struct->count = NULL;
}
*/

void _VIW_InitStructPropertyBase(VIW_PropertyBase *Struct)
{
    _VIW_InitStructViewList(&Struct->_list);
}

#endif // VIEWS_CORE_FUNCTIONS_STRUCTS_INIT_H_INCLUDED