#ifndef VIEWS_CORE_FUNCTIONS_SHAPE_H_INCLUDED
#define VIEWS_CORE_FUNCTIONS_SHAPE_H_INCLUDED

#include "Views.h"

bool VIW_SetBaseOrigin(VIW_View *View, int32_t x, int32_t y)
{
    if (View->property._type != _VIW_ID_PROPERTY_BASE)
    {
        _VIW_SetError(_VIW_ID_ERRORID_SETBASEORIGIN_BASE, _VIW_STRING_ERROR_BASE);
        return false;
    }

    VIW_PropertyBase *Property = (VIW_PropertyBase *)View->property.data;
    
    Property->_rect.x = x;
    Property->_rect.y = y;

    return true;
}

bool VIW_AddBaseOrigin(VIW_View *View, int32_t x, int32_t y)
{
    if (View->property._type != _VIW_ID_PROPERTY_BASE)
    {
        _VIW_SetError(_VIW_ID_ERRORID_ADDBASEORIGIN_BASE, _VIW_STRING_ERROR_BASE);
        return false;
    }

    VIW_PropertyBase *Property = (VIW_PropertyBase *)View->property.data;

    Property->_rect.x += x;
    Property->_rect.y += y;

    return true;
}

bool _VIW_Update(VIW_View *View, bool AllowSiblingUpdate)
{
    // Stop if it is inactive
    if (!View->_flags.totalActive)
        return true;

    // Find the correct way to update the shape
    switch (View->shapeData.type)
    {
        // No shape is defined
        case (VIW_ID_SHAPE_NONE):
            // Give warning
            _VIW_SetError(_VIW_ID_ERRORID_UPDATE_TYPENONE, _VIW_STRING_ERROR_TYPENONE);
            break;

        // The window shape should be used
        case (VIW_ID_SHAPE_WINDOW):
            if (!_VIW_UpdateShapeWindow(View))
            {
                _VIW_AddError(_VIW_ID_ERRORID_UPDATE_WINDOW, _VIW_STRING_ERROR_UPDATESHAPEWINDOW);
                return false;
            }
            break;

        // A shape should be copied
        case (VIW_ID_SHAPE_COPY):
            if (!_VIW_UpdateShapeCopy(View))
            {
                _VIW_AddError(_VIW_ID_ERRORID_UPDATE_COPY, _VIW_STRING_ERROR_UPDATESHAPECOPY);
                return false;
            }
            break;

        case (VIW_ID_SHAPE_ADVANCED):
            if (!_VIW_UpdateShapeAdvanced(View))
            {
                _VIW_AddError(_VIW_ID_ERRORID_UPDATE_ADVANCED, _VIW_STRING_ERROR_UPDATESHAPEADVANCED);
                return false;
            }
            break;

        default:
            _VIW_SetError(_VIW_ID_ERRORID_UPDATE_TYPE, _VIW_STRING_ERROR_UNKNOWNTYPE, View->shapeData.type);
            return false;
    }

    // Update the children
    for (VIW_View **ViewList = View->_child.list.list, **EndList = ViewList + View->_child.list.count; ViewList < EndList; ++ViewList)
        if ((*ViewList)->_flags.totalActive)
            if (!_VIW_Update(*ViewList, false))
            {
                _VIW_AddError(_VIW_ID_ERRORID_UPDATE_CHILD, _VIW_STRING_ERROR_UPDATECHILD);
                return false;
            }

    // Update siblings
    if (AllowSiblingUpdate && View->_parent.parent != NULL)
    {
        // Update all later siblings
        if (View->_flags.updateAllSiblings)
        {
            for (VIW_View **ViewList = View->_parent.parent->_child.list.list + View->_parent.childPos + 1, **EndList = View->_parent.parent->_child.list.list + View->_parent.parent->_child.list.count; ViewList < EndList; ++ViewList)
                if ((*ViewList)->_flags.totalActive)
                    if (!_VIW_Update(*ViewList, false))
                    {
                        _VIW_AddError(_VIW_ID_ERRORID_UPDATE_SIBLING, _VIW_STRING_ERROR_UPDATESIBLING);
                        return false;
                    }
        }

        // Update the next sibling
        else if (View->_flags.updateNextSibling)
            if (View->_parent.childPos < View->_parent.parent->_child.list.count - 1 && View->_parent.parent->_child.list.list[View->_parent.childPos + 1]->_flags.totalActive)
                if (!_VIW_Update(View->_parent.parent->_child.list.list[View->_parent.childPos + 1], true))
                {
                    _VIW_AddError(_VIW_ID_ERRORID_UPDATE_NEXTSIBLING, _VIW_STRING_ERROR_UPDATENEXTSIBLING);
                    return false;
                }
    }

    // Update property
    if (View->property._updateFunc != NULL)
        if (!View->property._updateFunc(View))
        {
            _VIW_AddError(_VIW_ID_ERRORID_UPDATE_PROPERTY, _VIW_STRING_ERROR_UPDATEPROPERTY);
            return false;
        }

    if (View->property._updateSuperFunc != NULL)
        if (!View->property._updateSuperFunc(View))
        {
            _VIW_AddError(_VIW_ID_ERRORID_UPDATE_SUPERPROPERTY, _VIW_STRING_ERROR_UPDATEPROPERTY);
            return false;
        }

    return true;
}

bool _VIW_UpdateShapeCopy(VIW_View *View)
{
    // Get the view to copy from
    SDL_Rect *RefRect = _VIW_FindRefView(View, &View->shapeData.data.ref);

    if (RefRect == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_UPDATESHAPECOPY_REF, _VIW_STRING_ERROR_NOREF);
        return false;
    }

    // Copy the shape of the reference
    OBJ_CopyRect(View->_shape.rect, *RefRect);

    return true;
}

bool _VIW_UpdateShapeWindow(VIW_View *View)
{
    // Copy from the window if it is a base
    if (View->_parent.root == View)
    {
        // Set the position to (0,0)
        OBJ_SetPoint(View->_shape.rect, 0, 0);

        // Get window shape
        SDL_GetWindowSize(View->_window.window, &View->_shape.rect.w, &View->_shape.rect.h);
    }

    // Copy from parent which is not a base
    else if (View->_parent.parent != View->property._nextBase)
    {
        OBJ_CopyRect(View->_shape.rect, View->_parent.parent->_shape.rect);
    }

    // Copy from base
    else
    {
        VIW_PropertyBase *Property = (VIW_PropertyBase *)View->property._nextBase->property.data;
        OBJ_CopyRect(View->_shape.rect, Property->_rect);
    }

    return true;
}

bool _VIW_UpdateShapeAdvanced(VIW_View *View)
{
    // Make sure there are shape data
    if (View->shapeData.data.data == NULL)
    {
        _VIW_SetError(_VIW_ID_ERRORID_UPDATESHAPEADVANCED_DATA, _VIW_STRING_ERROR_SHAPEDATA);
        return false;
    }

    // Update the x-coordinate
    if (!_VIW_UpdateShapeCoord(View, &View->shapeData.data.data->x, &_VIW_GetX, &_VIW_GetW))
    {
        _VIW_AddError(_VIW_ID_ERRORID_UPDATESHAPEADVANCED_X, _VIW_STRING_ERROR_UPDATEX);
        return false;
    }

    // Update the y-coordinate
    if (!_VIW_UpdateShapeCoord(View, &View->shapeData.data.data->y, &_VIW_GetY, &_VIW_GetH))
    {
        _VIW_AddError(_VIW_ID_ERRORID_UPDATESHAPEADVANCED_Y, _VIW_STRING_ERROR_UPDATEY);
        return false;
    }

    return true;
}

bool _VIW_UpdateShapeCoord(VIW_View *View, VIW_RectPart *Coord, int32_t *(*GetPos)(SDL_Rect *Rect), int32_t *(*GetSize)(SDL_Rect *Rect))
{
    switch (Coord->type)
    {
        // If method is None
        case (VIW_ID_RECT_NONE):
            // Give warning
            _VIW_SetError(_VIW_ID_ERRORID_UPDATESHAPECOORD_TYPENONE, _VIW_STRING_ERROR_TYPENONE);
            break;

        // Use stretch method if needed
        case (VIW_ID_RECT_STRETCH):
            if (!_VIW_UpdateShapeCoordStretch(View, &Coord->data.stretch, GetPos, GetSize))
            {
                _VIW_AddError(_VIW_ID_ERRORID_UPDATESHAPECOORD_STRETCH, _VIW_STRING_ERROR_SETSHAPESTRETCH);
                return false;
            }

            break;

        // Use origin method if needed
        case (VIW_ID_RECT_ORIGIN):
            if (!_VIW_UpdateShapeCoordOrigin(View, &Coord->data.origin, GetPos, GetSize))
            {
                _VIW_AddError(_VIW_ID_ERRORID_UPDATESHAPECOORD_ORIGIN, _VIW_STRING_ERROR_SETSHAPEORIGIN);
                return false;
            }

            break;

        // Unknown method, cast error
        default:
            _VIW_SetError(_VIW_ID_ERRORID_UPDATESHAPECOORD_TYPE, _VIW_STRING_ERROR_UNKNOWNTYPE, Coord->type);
            return false;
    }

    return true;
}

bool _VIW_UpdateShapeCoordStretch(VIW_View *View, VIW_RectStretch *Coord, int32_t *(*GetPos)(SDL_Rect *Rect), int32_t *(*GetSize)(SDL_Rect *Rect))
{
    // Get positions
    int32_t Pos1 = _VIW_GetPos(View, &Coord->pos1, GetPos, GetSize);
    int32_t Pos2 = _VIW_GetPos(View, &Coord->pos2, GetPos, GetSize);

    if (Pos1 == VIW_ID_RETURNERROR_INT32_T || Pos2 == VIW_ID_RETURNERROR_INT32_T)
    {
        _VIW_AddError(_VIW_ID_ERRORID_UPDATESHAPECOORDSTRETCH_POS, _VIW_STRING_ERROR_CALCPOS);
        return false;
    }

    // Calculate the size
    int32_t Size = Pos2 - Pos1 + 1;

    // Reverse if size < 0
    if (Size < 0)
    {
        Pos1 = Pos2;
        Size *= -1;
    }

    // Set position and size
    *GetPos(View) = Pos1;
    *GetSize(View) = Size;

    return true;
}

bool _VIW_UpdateShapeCoordOrigin(VIW_View *View, VIW_RectOrigin *Coord, int32_t *(*GetPos)(SDL_Rect *Rect), int32_t *(*GetSize)(SDL_Rect *Rect))
{
    // Get position
    int32_t Pos = _VIW_GetPos(View, &Coord->pos, GetPos, GetSize);

    if (Pos == VIW_ID_RETURNERROR_INT32_T)
    {
        _VIW_AddError(_VIW_ID_ERRORID_UPDATESHAPECOORDORIGIN_POS, _VIW_STRING_ERROR_CALCPOS);
        return false;
    }

    // Get size
    int32_t Size = _VIW_GetSize(View, &Coord->size, GetPos, GetSize);

    if (Size == VIW_ID_RETURNERROR_INT32_T)
    {
        _VIW_AddError(_VIW_ID_ERRORID_UPDATESHAPECOORDORIGIN_SIZE, _VIW_STRING_ERROR_CALCSIZE);
        return false;
    }

    // Reverse size if it is negative
    if (Size < 0)
        Size *= -1;

    // Add origin
    switch (Coord->origin)
    {
        // It is the center of the shape
        case (VIW_ID_ANCHOR_CENTER):
            Pos -= Size / 2;
            break;

        // It is the positive side
        case (VIW_ID_ANCHOR_POS):
            Pos -= Size - 1;
            break;

        // It is the negative side
        case (VIW_ID_ANCHOR_NEG):
            break;

        // Unknown type
        default:
            _VIW_SetError(_VIW_ID_ERRORID_UPDATESHAPECOORDORIGIN_TYPE, _VIW_STRING_ERROR_UNKNOWNTYPE, Coord->origin);
            return false;
    }

    // Set the position and size
    *GetPos(View) = Pos;
    *GetSize(View) = Size;

    return true;
}

int32_t _VIW_GetSize(VIW_View *View, VIW_Size *SizeData, int32_t *(*GetPos)(SDL_Rect *Rect), int32_t *(*GetSize)(SDL_Rect *Rect))
{
    int32_t Size;

    // Figure out what method to use
    switch (SizeData->type)
    {
        // If it is not specified
        case (VIW_ID_SIZE_NONE):
            _VIW_SetError(_VIW_ID_ERRORID_GETSIZE_TYPENONE, _VIW_STRING_ERROR_TYPENONE);
            return VIW_ID_RETURNERROR_INT32_T;

        // Use a static size
        case (VIW_ID_SIZE_RIGID):
            Size = SizeData->data.rigid;
            break;

        // Use a value from a pointer
        case (VIW_ID_SIZE_POINTER):
            // Make sure the pointer is not NULL
            if (SizeData->data.pointer == NULL)
            {
                _VIW_SetError(_VIW_ID_ERRORID_GETSIZE_POINTER, _VIW_STRING_ERROR_NOPOINTER);
                return VIW_ID_RETURNERROR_INT32_T;
            }

            Size = *SizeData->data.pointer;
            break;

        // Use the difference between 2 positions
        case (VIW_ID_SIZE_DIFF):
            Size = _VIW_GetSizeDiff(View, &SizeData->data.diff, GetPos, GetSize);

            if (Size == VIW_ID_RETURNERROR_INT32_T)
            {
                _VIW_AddError(_VIW_ID_ERRORID_GETSIZE_DIFF, _VIW_STRING_ERROR_CALCSIZE);
                return VIW_ID_RETURNERROR_INT32_T;
            }

            break;

        // Copy the size from another view
        case (VIW_ID_SIZE_COPY):
            Size = _VIW_GetSizeCopy(View, &SizeData->data.copy, GetSize);

            if (Size == VIW_ID_RETURNERROR_INT32_T)
            {
                _VIW_AddError(_VIW_ID_ERRORID_GETSIZE_COPY, _VIW_STRING_ERROR_CALCSIZE);
                return VIW_ID_RETURNERROR_INT32_T;
            }

            break;

        // Unknown type
        default:
            _VIW_SetError(_VIW_ID_ERRORID_GETSIZE_TYPE, _VIW_STRING_ERROR_UNKNOWNTYPE, SizeData->type);
            return VIW_ID_RETURNERROR_INT32_T;
    }

    // Modify the size
    Size = (int32_t)((double)Size * SizeData->scale) + SizeData->offset;

    return Size;
}

int32_t _VIW_GetSizeCopy(VIW_View *View, VIW_Reference *CopyRef, int32_t *(*GetSize)(SDL_Rect *Rect))
{
    // Get the reference view
    SDL_Rect *RefRect = _VIW_FindRefView(View, CopyRef);

    if (RefRect == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_GETSIZECOPY_REF, _VIW_STRING_ERROR_NOREF);
        return VIW_ID_RETURNERROR_INT32_T;
    }

    // Get the size
    return *GetSize(RefRect);
}

int32_t _VIW_GetSizeDiff(VIW_View *View, VIW_SizeDiff *SizeData, int32_t *(*GetPos)(SDL_Rect *Rect), int32_t *(*GetSize)(SDL_Rect *Rect))
{
    // Find the 2 positions
    int32_t Pos1 = _VIW_GetPos(View, &SizeData->pos1, GetPos, GetSize);
    int32_t Pos2 = _VIW_GetPos(View, &SizeData->pos2, GetPos, GetSize);

    // Make sure no error has occured
    if (Pos1 == VIW_ID_RETURNERROR_INT32_T || Pos2 == VIW_ID_RETURNERROR_INT32_T)
    {
        _VIW_AddError(_VIW_ID_ERRORID_GETSIZEDIFF_POS, _VIW_STRING_ERROR_CALCPOS);
        return VIW_ID_RETURNERROR_INT32_T;
    }

    return Pos2 - Pos1;
}

int32_t _VIW_GetPos(VIW_View *View, VIW_Pos *PosData, int32_t *(*GetPos)(SDL_Rect *Rect), int32_t *(*GetSize)(SDL_Rect *Rect))
{
    int32_t Pos;

    // Figure out what method to use
    switch (PosData->type)
    {
        // No type specified
        case (VIW_ID_POS_NONE):
            _VIW_SetError(_VIW_ID_ERRORID_GETPOS_NONE, _VIW_STRING_ERROR_TYPENONE);
            return VIW_ID_RETURNERROR_INT32_T;

        // Use a defined value relative to the parent
        case (VIW_ID_POS_RIGID):
            Pos = *GetPos(View->_parent.parent) + PosData->data.rigid;
            break;

        // Use a defined value in absolute coordinates
        case (VIW_ID_POS_RIGID_ABS):
            Pos = PosData->data.rigid;
            break;

        // Use a value from a pointer relative to parent
        case (VIW_ID_POS_POINTER):
            // Make sure pointer is specified
            if (PosData->data.pointer == NULL)
            {
                _VIW_SetError(_VIW_ID_ERRORID_GETPOS_POINTER, _VIW_STRING_ERROR_NOPOINTER);
                return VIW_ID_RETURNERROR_INT32_T;
            }

            Pos = *GetPos(View->_parent.parent) + *PosData->data.pointer;
            break;

        // Use a value from a pointer in absolute coordinates
        case (VIW_ID_POS_POINTER_ABS):
            // Make sure pointer is specified
            if (PosData->data.pointer == NULL)
            {
                _VIW_SetError(_VIW_ID_ERRORID_GETPOS_POINTERABS, _VIW_STRING_ERROR_NOPOINTER);
                return VIW_ID_RETURNERROR_INT32_T;
            }

            Pos = *PosData->data.pointer;
            break;

        // Use a single anchor point
        case (VIW_ID_POS_SINGLE):
            Pos = _VIW_GetAnchorPoint(View, &PosData->data.single, GetPos, GetSize);

            // Make sure no error occured
            if (Pos == VIW_ID_RETURNERROR_INT32_T)
            {
                _VIW_AddError(_VIW_ID_ERRORID_GETPOS_SINGLEANCHOR, _VIW_STRING_ERROR_ANCHORERROR);
                return VIW_ID_RETURNERROR_INT32_T;
            }

            break;

        // Use a biased anchor point
        case (VIW_ID_POS_BIAS):
            Pos = _VIW_GetBiasAnchorPoint(View, &PosData->data.bias, GetPos, GetSize);

            // Make sure no error occured
            if (Pos == VIW_ID_RETURNERROR_INT32_T)
            {
                _VIW_AddError(_VIW_ID_ERRORID_GETPOS_BIASANCHOR, _VIW_STRING_ERROR_ANCHORERROR);
                return VIW_ID_RETURNERROR_INT32_T;
            }

            break;

        // The type is unknown
        default:
            _VIW_SetError(_VIW_ID_ERRORID_GETPOS_TYPE, _VIW_STRING_ERROR_UNKNOWNTYPE, PosData->type);
            return VIW_ID_RETURNERROR_INT32_T;
    }

    return Pos;
}

int32_t _VIW_GetBiasAnchorPoint(VIW_View *View, VIW_BiasAnchor *Anchor, int32_t *(*GetPos)(SDL_Rect *Rect), int32_t *(*GetSize)(SDL_Rect *Rect))
{
    // Get the 2 anchor points
    int32_t AnchorPoint1 = _VIW_GetAnchorPoint(View, &Anchor->anchor1, GetPos, GetSize);
    int32_t AnchorPoint2 = _VIW_GetAnchorPoint(View, &Anchor->anchor2, GetPos, GetSize);

    // Make sure no error occured
    if (AnchorPoint1 == VIW_ID_RETURNERROR_INT32_T || AnchorPoint2 == VIW_ID_RETURNERROR_INT32_T)
    {
        _VIW_AddError(_VIW_ID_ERRORID_GETBIASANCHORPOINT_ANCHOR, _VIW_STRING_ERROR_ANCHORERROR);
        return VIW_ID_RETURNERROR_INT32_T;
    }

    return AnchorPoint1 + (int32_t)((double)(AnchorPoint2 - AnchorPoint1) * Anchor->bias);
}

int32_t _VIW_GetAnchorPoint(VIW_View *View, VIW_Anchor *Anchor, int32_t *(*GetPos)(SDL_Rect *Rect), int32_t *(*GetSize)(SDL_Rect *Rect))
{
    // Get the reference view
    SDL_Rect *AnchorRect = _VIW_FindRefView(View, &Anchor->ref);

    if (AnchorRect == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_GETANCHORPOINT_REF, _VIW_STRING_ERROR_NOREF);
        return VIW_ID_RETURNERROR_INT32_T;
    }

    // Get position and size
    int32_t Pos = *GetPos(AnchorRect);
    int32_t Size = *GetSize(AnchorRect);

    // Calculate the anchor point
    int32_t AnchorPoint;

    switch (Anchor->anchorPoint)
    {
        // nothing is specified
        case (VIW_ID_ANCHOR_NONE):
            _VIW_SetError(_VIW_ID_ERRORID_GETANCHORPOINT_TYPENONE, _VIW_STRING_ERROR_TYPENONE);
            return VIW_ID_RETURNERROR_INT32_T;

        // The anchor point is the center of the shape
        case (VIW_ID_ANCHOR_CENTER):
            AnchorPoint = Pos + Size / 2;
            break;

        // The anchor point is the positive side of the shape
        case (VIW_ID_ANCHOR_POS):
            AnchorPoint = Pos + Size - 1;
            break;

        // The anchor point is the negative side of the shape
        case (VIW_ID_ANCHOR_NEG):
            AnchorPoint = Pos;
            break;
        
        // Unknown id
        default:
            _VIW_SetError(_VIW_ID_ERRORID_GETANCHORPOINT_ANCHORTYPE, _VIW_STRING_ERROR_UNKNOWNTYPE, Anchor->anchorPoint);
            return VIW_ID_RETURNERROR_INT32_T;
    }

    return AnchorPoint + Anchor->offset;
}

SDL_Rect *_VIW_FindRefView(VIW_View *View, VIW_Reference *Ref)
{
    SDL_Rect *RefRect;

    // Find the view
    switch (Ref->view)
    {
        // There is no root
        case (VIW_ID_RELATION_NONE):
            _VIW_SetError(_VIW_ID_ERRORID_FINDREFVIEW_NONE, _VIW_STRING_ERROR_TYPENONE);
            return NULL;

        // It is anchored to it's base
        case (VIW_ID_RELATION_BASE):
            RefRect = &((VIW_PropertyBase *)View->property._nextBase->property.data)->_rect;
            break;

        // It is anchored to the sibling above it in the children list
        case (VIW_ID_RELATION_SIBLING):
            // If it is the first active child then there is an error
            if (View->_parent.childPos == 0)
            {
                _VIW_SetError(_VIW_ID_ERRORID_FINDREFVIEW_FIRSTCHILD, _VIW_STRING_ERROR_FIRSTCHILD);
                return NULL;
            }

            RefRect = &View->_parent.parent->_child.list.list[View->_parent.childPos - 1]->_shape.rect;
            break;

        // It is anchored to something by ID
        case (VIW_ID_RELATION_ID):
            // Make sure it is an earlier sibling
            if (Ref->ref->_parent.parent != View->_parent.parent)
            {
                _VIW_SetError(_VIW_ID_ERRORID_FINDREFVIEW_SAMEPARENT, _VIW_STRING_ERROR_SAMEPARENT);
                return NULL;
            }

            if (Ref->ref->_parent.childPos >= View->_parent.childPos)
            {
                _VIW_SetError(_VIW_ID_ERRORID_FINDREFVIEW_CHILDPOS, _VIW_STRING_ERROR_EARLYCHILD);
                return NULL;
            }

            RefRect = &Ref->ref->_shape.rect;
            break;

        // The view type is unknown
        default:
            _VIW_SetError(_VIW_ID_ERRORID_FINDREFVIEW_TYPE, _VIW_STRING_ERROR_UNKNOWNTYPE, Ref->view);
            return NULL;
    }

    return RefRect;
}

int32_t *_VIW_GetX(SDL_Rect *Rect)
{
    return &Rect->x;
}

int32_t *_VIW_GetY(SDL_Rect *Rect)
{
    return &Rect->y;
}

int32_t *_VIW_GetW(SDL_Rect *Rect)
{
    return &Rect->w;
}

int32_t *_VIW_GetH(SDL_Rect *Rect)
{
    return &Rect->h;
}

#endif // VIEWS_CORE_FUNCTIONS_SHAPE_H_INCLUDED