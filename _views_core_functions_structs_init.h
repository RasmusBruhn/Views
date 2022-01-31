// Adds functions to initialise structs
#ifndef VIEWS_CORE_FUNCTIONS_STRUCTS_INIT_H_INCLUDED
#define VIEWS_CORE_FUNCTIONS_STRUCTS_INIT_H_INCLUDED

#include <Views.h>
// MISSING
void _VIW_InitStructViewList(VIW_ViewList *Struct)
{
    Struct->count = 0;
    Struct->list = NULL;
}
// MISSING
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
// MISSING
void _VIW_InitStructParent(VIW_Parent *Struct)
{
    Struct->childPos = 0;
    Struct->parent = NULL;
    Struct->root = NULL;
}
// MISSING
void _VIW_InitStructChild(VIW_Child *Struct)
{
    _VIW_InitStructViewList(&Struct->list);
}
// MISSING
void _VIW_InitStructProperty(VIW_Property *Struct)
{
    Struct->data = NULL;
    Struct->_destroyFunc = NULL;
    Struct->_updateFunc = NULL;
    Struct->_runEventFunc = NULL;
    Struct->_runScriptFunc = NULL;
    Struct->_drawGraphicsFunc = NULL;
    Struct->_type = VIW_ID_PROPERTY_NONE;
    Struct->_nextBase = NULL;
    Struct->_orderEvent = 0;
    Struct->_orderScript = 0;
    Struct->_orderGraphics = 0;
    Struct->_ownScript = NULL;
    Struct->_ownEventID = NULL;
}
// MISSING
void _VIW_InitStructFlagsSet(VIW_FlagsSet *Struct)
{
    Struct->active = true;
    Struct->totalActive = true;
    Struct->updateNextSibling = false;
    Struct->updateAllSiblings = false;
}
// MISSING
void _VIW_InitStructFlags(VIW_Flags *Struct)
{
    Struct->freezeShape = false;
    Struct->active = true;
}
// MISSING
void _VIW_InitStructWindow(VIW_Window *Struct)
{
    Struct->rend = NULL;
    Struct->window = NULL;
    Struct->ID = 0;
}
// MISSING
void _VIW_InitStructShape(VIW_Shape *Struct)
{
    OBJ_SetRect(Struct->boundRect, 0, 0, 0, 0);
    OBJ_SetRect(Struct->rect, 0, 0, 0, 0);
}
// MISSING
void _VIW_InitStructBounds(VIW_Bounds *Struct)
{
    OBJ_SetRect(Struct->rect, 0, 0, 0, 0);
}
// MISSING
void _VIW_InitStructShapeData(VIW_ShapeData *Struct)
{
    Struct->type = VIW_ID_SHAPE_COPY;
    Struct->ref._view = VIW_ID_RELATION_PARENT;
    Struct->ref._ref = NULL;
    Struct->data = NULL;
}
// MISSING
void _VIW_InitStructRect(VIW_Rect *Struct)
{
    _VIW_InitStructRectPart(&Struct->x);
    _VIW_InitStructRectPart(&Struct->y);
}
// MISSING
void _VIW_InitStructRectPart(VIW_RectPart *Struct)
{
    Struct->type = VIW_ID_RECT_NONE;
}
// MISSING
void _VIW_InitStructRectOrigin(VIW_RectOrigin *Struct)
{
    Struct->origin = VIW_ID_ANCHOR_CENTER;
    _VIW_InitStructPos(&Struct->pos);
    _VIW_InitStructSize(&Struct->size);
}
// MISSING
void _VIW_InitStructRectStretch(VIW_RectStretch *Struct)
{
    _VIW_InitStructPos(&Struct->pos1);
    _VIW_InitStructPos(&Struct->pos2);
}
// MISSING
void _VIW_InitStructSize(VIW_Size *Struct)
{
    Struct->type = VIW_ID_SIZE_NONE;
}
// MISSING
void _VIW_InitStructSizeCopy(VIW_SizeCopy *Struct)
{
    _VIW_InitStructReference(&Struct->ref);
    Struct->scale = 1.;
    Struct->type = VIW_ID_RELATION_NONE;
}
// MISSING
void _VIW_InitStructSizeDiff(VIW_SizeDiff *Struct)
{
    _VIW_InitStructPos(&Struct->pos1);
    _VIW_InitStructPos(&Struct->pos2);
    Struct->scale = 1.;
}
// MISSING
void _VIW_InitStructPos(VIW_Pos *Struct)
{
    Struct->type = VIW_ID_POS_NONE;
}
// MISSING
void _VIW_InitStructBiasAnchor(VIW_BiasAnchor *Struct)
{
    _VIW_InitStructAnchor(&Struct->anchor1);
    _VIW_InitStructAnchor(&Struct->anchor2);
    Struct->bias = 0.5;
}
// MISSING
void _VIW_InitStructAnchor(VIW_Anchor *Struct)
{
    Struct->anchorPoint = VIW_ID_ANCHOR_CENTER;
    Struct->offset = 0;
    _VIW_InitStructReference(&Struct->ref);
}
// MISSING
void _VIW_InitStructReference(VIW_Reference *Struct)
{
    Struct->_ref = NULL;
    Struct->_view = VIW_ID_RELATION_NONE;
}
// MISSING
void _VIW_InitStructEvent(VIW_Event *Struct)
{
    Struct->ID = 0;
    _VIW_InitStructViewList(&Struct->list);
}
// MISSING
void _VIW_InitStructEventList(VIW_EventList *Struct)
{
    Struct->count = 0;
    Struct->list = NULL;
}
// MISSING
void _VIW_InitStructScript(VIW_Script *Struct)
{
    Struct->view = NULL;
    Struct->time = -1;
    Struct->increase = 0;
}
// MISSING
void _VIW_InitStructScriptList(VIW_ScriptList *Struct)
{
    Struct->list = NULL;
    Struct->count = NULL;
}
// MISSING
void _VIW_InitStructPropertyBase(VIW_PropertyBase *Struct)
{
    _VIW_InitStructScriptList(&Struct->_script);
    _VIW_InitStructViewList(&Struct->_graphics);
    _VIW_InitStructEventList(&Struct->_event);
    Struct->_texture = NULL;
    Struct->useTexture = false;
    Struct->_firstSubView = 0;
}

#endif // VIEWS_CORE_FUNCTIONS_STRUCTS_INIT_H_INCLUDED