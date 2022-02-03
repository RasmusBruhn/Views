// Adds initialisation and cleanup functions
#ifndef VIEWS_CORE_FUNCTIONS_INITCLEAN_H_INCLUDED
#define VIEWS_CORE_FUNCTIONS_INITCLEAN_H_INCLUDED

#include "Views.h"

VIW_View *VIW_CreateRoot(SDL_Window *Window, SDL_Renderer *Rend)
{
    // Create the new view
    VIW_View *Root = (VIW_View *)malloc(sizeof(VIW_View));

    if (Root == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEROOT_MALLOC, strerror(errno), _VIW_STRING_ERROR_MALLOC);
        return NULL;
    }

    // Initialize
    _VIW_InitStructView(Root);

    // Set parent data
    Root->_parent.root = Root;

    // Set window data
    Root->_window.window = Window;
    Root->_window.rend = Rend;
    Root->_window.ID = SDL_GetWindowID(Window);

    // Make sure there were no error
    if (Root->_window.ID == 0)
    {
        free(Root);
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEROOT_WINDOWID, SDL_GetError(), _VIW_ID_STRING_WINDOWID);
        return NULL;
    }
    
    // Set shape data
    Root->shapeData.type = VIW_ID_SHAPE_WINDOW;

    // Add to list of roots
    extern VIW_ViewList _VIW_RootList;

    if (!_VIW_AddToViewList(&_VIW_RootList, Root))
    {
        free(Root);
        _VIW_AddError(_VIW_ID_ERRORID_CREATEROOT_LIST, _VIW_STRING_ERROR_ADDROOTLIST);
        return NULL;
    }

    // Add Base property
    if (!VIW_CreatePropertyBase(Root))
    {
        _VIW_RemoveFromViewList(&_VIW_RootList, Root);
        free(Root);
        _VIW_AddError(_VIW_ID_ERRORID_CREATEROOT_PROPERTY, _VIW_STRING_ERROR_ADDBASEPROPERTY);
        return NULL;
    }

    return Root;
}

void VIW_DestroyRoot(VIW_View *Root)
{
    extern VIW_ViewList _VIW_RootList;

    // Remove it from root list
    _VIW_RemoveFromViewList(&_VIW_RootList, Root);
    
    // Destroy the view
    VIW_DestroyView(Root);
}

VIW_View *VIW_CreateViewWithPos(VIW_View *Parent, uint32_t ChildPos)
{
    // Get memory for the view
    VIW_View *View = (VIW_View *)malloc(sizeof(VIW_View));

    if (View == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEVIEW_MALLOC, strerror(errno), _VIW_STRING_ERROR_MALLOC);
        return NULL;
    }

    // Initialize
    _VIW_InitStructView(View);

    // Get the next base
    if (Parent->property._type == _VIW_ID_PROPERTY_BASE)
        View->property._nextBase = Parent;

    else
        View->property._nextBase = Parent->property._nextBase;

    // Set window data
    View->_window.window = Parent->_window.window;
    View->_window.rend = Parent->_window.rend;
    View->_window.ID = Parent->_window.ID;
    
    // Add it to list of children
    if (!_VIW_AddToViewListWithPos(&Parent->_child.list, View, ChildPos))
    {
        free(View);
        _VIW_AddError(_VIW_ID_ERRORID_CREATEVIEW_CHILDLIST, _VIW_STRING_ERROR_ADDCHILDLIST);
        return NULL;
    }

    // Fix childPos for siblings
    for (VIW_View **EndList = Parent->_child.list.list + Parent->_child.list.count, **ViewList = Parent->_child.list.list + ChildPos + 1; ViewList < EndList; ++ViewList)
        ++(*ViewList)->_parent.childPos;

    // Set update priorities
    if (ChildPos != 0)
    {
        if (Parent->_child.list.list[ChildPos - 1]->_flags.updateNextSibling)
            View->_flags.updateNextSibling = true;

        Parent->_child.list.list[ChildPos - 1]->_flags.updateNextSibling = false;
    }

    // Set parent data
    View->_parent.parent = Parent;
    View->_parent.root = Parent->_parent.root;
    View->_parent.childPos = ChildPos;

    return View;
}

void VIW_DestroyView(VIW_View *View)
{
    // Destroy the property
    if (View->property._destroyFunc != NULL)
        View->property._destroyFunc(View);

    // Destroy the shape data
    if (View->shapeData.type == VIW_ID_SHAPE_ADVANCED && View->shapeData.data.data != NULL)
        free(View->shapeData.data.data);

    // Destroy the children
    for (VIW_View **EndList = View->_child.list.list, **ViewList = EndList + View->_child.list.count; ViewList > EndList;)
        VIW_DestroyView(*(--ViewList));

    if (View->_child.list.list != NULL)
        free(View->_child.list.list);

    // Remove it from the child list
    if (View->_parent.parent != NULL)
    {
        // Remove it from list
        if (!_VIW_RemoveFromViewList(&View->_parent.parent->_child.list, View))
            _VIW_AddError(_VIW_ID_ERRORID_DESTROYVIEW_REMOVEFROMLIST, _VIW_STRING_ERROR_REMOVEFROMLIST);

        // Update the siblings childPos
        else
            for (VIW_View **EndList = View->_parent.parent->_child.list.list + View->_parent.parent->_child.list.count, **ViewList = View->_parent.parent->_child.list.list + View->_parent.childPos; ViewList < EndList; ++ViewList)
                --(*ViewList)->_parent.childPos;
    }

    // Free the view
    free(View);
}

void VIW_Quit(void)
{
    // Go through all roots and remove them
    extern VIW_ViewList _VIW_RootList;

    for (VIW_View **EndList = _VIW_RootList.list, **ViewList = EndList + _VIW_RootList.count - 1; ViewList >= EndList; --ViewList)
        VIW_DestroyRoot(*ViewList);
}

VIW_View *VIW_CreateSubView(VIW_View *Parent)
{
    // Create the view
    VIW_View *View = VIW_CreateView(Parent);

    if (View == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_CREATESUBVIEW_VIEW, _VIW_STRING_ERROR_CREATEVIEW);
        return NULL;
    }

    // Add the shape data
    View->shapeData.type = VIW_ID_SHAPE_COPY;
    View->shapeData.data.ref.view = VIW_ID_RELATION_PARENT;

    return View;
}

VIW_View *VIW_CreateBaseView(VIW_View *Parent)
{
    // Create view
    VIW_View *View = VIW_CreateView(Parent);

    if (View == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_CREATEBASEVIEW_VIEW, _VIW_STRING_ERROR_CREATEVIEW);
        return NULL;
    }

    // Create property
    if (!VIW_CreatePropertyBase(View))
    {
        VIW_DestroyView(View);
        _VIW_AddError(_VIW_ID_ERRORID_CREATEBASEVIEW_PROPERTY, _VIW_STRING_ERROR_ADDBASEPROPERTY);
        return NULL;
    }

    return View;
}

bool VIW_UseAdvancedShapeData(VIW_View *View)
{
    // Check if it is already initialized
    if (View->shapeData.type == VIW_ID_SHAPE_ADVANCED)
    {
        _VIW_SetError(_VIW_ID_ERRORID_USEADVANCEDSHAPEDATA_INIT, _VIW_STRING_ERROR_DATAINITIALIZED);
        return true;
    }

    // If it is not initialized, get memory
    View->shapeData.data.data = (VIW_Rect *)malloc(sizeof(VIW_Rect));

    if (View->shapeData.data.data == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_USEADVANCEDSHAPEDATA_MALLOC, strerror(errno), _VIW_STRING_ERROR_MALLOC);
        return false;
    }

    // Set type
    View->shapeData.type = VIW_ID_SHAPE_ADVANCED;

    // Initialize the shape data
    _VIW_InitStructRect(View->shapeData.data.data);

    return true;
}

bool VIW_AddRef(VIW_View *View, VIW_Reference *Ref, enum VIW_ID_Relation type, VIW_View *ID)
{
    Ref->ref = NULL;
    VIW_View *Relation = View;
    VIW_View **SiblingRelation;

    // Find the correct type
    switch (type)
    {
        case (VIW_ID_RELATION_NONE):
            break;

        case (VIW_ID_RELATION_PARENT):
            break;

        case (VIW_ID_RELATION_ROOT):
            break;

        case (VIW_ID_RELATION_SIBLING):
            // Error if it is the first child
            if (View->_parent.childPos == 0)
            {
                _VIW_SetError(_VIW_ID_ERRORID_ADDREF_FIRSTCHILD, _VIW_STRING_ERROR_FIRSTCHILD);
                return false;
            }

            // Set sibling to update
            View->_parent.parent->_child.list.list[View->_parent.childPos - 1]->_flags.updateNextSibling = true;
            break;

        case (VIW_ID_RELATION_ID):
            // Find the relation
            do
            {
                if (Relation == Relation->_parent.root)
                {
                    _VIW_SetError(_VIW_ID_ERRORID_ADDREF_REFNOTFOUND, _VIW_STRING_ERROR_ILLIGALREF);
                    return false;
                }

                for (SiblingRelation = Relation->_parent.parent->_child.list.list + Relation->_parent.childPos - 1; SiblingRelation >= Relation->_parent.parent->_child.list.list; --SiblingRelation)
                    if (*SiblingRelation == ID)
                    {
                        ID->_flags.updateAllSiblings = true;
                        break;
                    }

                if (SiblingRelation >= Relation->_parent.parent->_child.list.list)
                    break;
            } while ((Relation = Relation->_parent.parent) != ID);

            Ref->ref = ID;
            break;

        default:
            _VIW_SetError(_VIW_ID_ERRORID_ADDREF_TYPE, _VIW_STRING_ERROR_UNKNOWNTYPE);
            return false;
    }

    // Set the type
    Ref->view = type;

    return true;
}

bool VIW_CreatePropertyBase(VIW_View *View)
{
    // Get memory for property
    VIW_PropertyBase *Property = (VIW_PropertyBase *)malloc(sizeof(VIW_PropertyBase));

    if (Property == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEPROPERTYBASE_MALLOC, strerror(errno), _VIW_STRING_ERROR_MALLOC);
        return false;
    }

    // Initialize
    _VIW_InitStructPropertyBase(Property);

    extern VIW_View *(**_VIW_BaseFuncList)(VIW_View * BaseView);
    extern size_t _VIW_BaseFuncCount;
    
    Property->_list.count = _VIW_BaseFuncCount;
    Property->_list.list = (VIW_View **)malloc(sizeof(VIW_View *) * _VIW_BaseFuncCount);

    if (Property->_list.list == NULL)
    {
        free(Property);
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEPROPERTYBASE_MALLOCLIST, strerror(errno), _VIW_STRING_ERROR_MALLOC);
        return false;
    }

    for (VIW_View **List = Property->_list.list, **EndList = Property->_list.list + _VIW_BaseFuncCount; List < EndList; ++List)
        *List = NULL;

    // Set functions and property
    View->property.data = Property;
    View->property._type = _VIW_ID_PROPERTY_BASE;
    View->property._destroyFunc = &_VIW_DestroyPropertyBase;
    View->property._updateFunc = NULL;
    View->property._runFunc = NULL;

    // Add to the list
    for (size_t Count = 0; Count < _VIW_BaseFuncCount; ++Count)
    {
        // Create the new view
        VIW_View *NewView = _VIW_BaseFuncList[Count](View);

        // Make sure everything is ok
        if (NewView == NULL)
        {
            for (VIW_View **ViewList = Property->_list.list + Count - 1, **ViewListEnd = Property->_list.list; ViewList >= ViewListEnd; --ViewList)
                VIW_DestroyView(*ViewList);

            free(Property->_list.list);
            free(Property);
            _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEPROPERTYBASE_MALLOCNEW, strerror(errno), _VIW_STRING_ERROR_MALLOCCOUNT, Count);
            return false;
        }

        // Change the next base
        NewView->property._nextBase = View->property._nextBase;

        // Add to the list
        Property->_list.list[Count] = NewView;
    }
        
    return true;
}

void _VIW_DestroyPropertyBase(VIW_View *View)
{ 
    // Free the list
    free(((VIW_PropertyBase *)View->property.data)->_list.list);

    // Free the property
    free(View->property.data);
}

void *_VIW_AddToListWithPos(void **List, uint32_t Length, void *Object, uint32_t Pos)
{
    // Make sure Pos is within the list
    if (Pos > Length)
    {
        _VIW_SetError(_VIW_ID_ERRORID_ADDTOLIST_POS, _VIW_STRING_ERROR_RANGE);
        return NULL;
    }

    // make list longer
    void **NewList = (void **)realloc(List, sizeof(void *) * (Length + 1));

    // Error if realloc failed
    if (NewList == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_ADDTOLIST_REALLOC, strerror(errno), _VIW_STRING_ERROR_REALLOC);
        return NULL;
    }

    // Add object
    for (void **VarList = NewList + Length, **EndList = NewList + Pos; VarList > EndList; --VarList)
        *VarList = *(VarList - 1);

    NewList[Pos] = Object;

    return NewList;
}

void *_VIW_RemoveFromList(void **List, uint32_t Length, void *Object)
{
    // Find object in the list
    void **VarList, **EndList;

    for (VarList = List, EndList = List + Length; VarList < EndList; ++VarList)
        if (*VarList == Object)
            break;

    // Make sure it actually found the element
    if (VarList == EndList)
    {
        _VIW_SetError(_VIW_ID_ERRORID_REMOVEFROMLIST_LOCATE, _VIW_STRING_ERROR_LOCATEOBJECT);
        return NULL;
    }

    // Remove the element
    for (++VarList; VarList < EndList; ++VarList)
        *(VarList - 1) = *VarList;

    // Reallocate list
    void **NewList = (void **)realloc(List, sizeof(void *) * (Length - 1));

    if (NewList == NULL && Length > 1)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_REMOVEFROMLIST_REALLOC, strerror(errno), _VIW_STRING_ERROR_REALLOC);
        return NULL;
    }

    return NewList;
}

bool _VIW_AddToViewListWithPos(VIW_ViewList *List, VIW_View *View, uint32_t Pos)
{
    // Add view to list
    VIW_View **NewList = (VIW_View **)_VIW_AddToListWithPos((void **)List->list, List->count, View, Pos);

    if (NewList == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_ADDTOVIEWLIST_LIST, _VIW_STRING_ERROR_ADDTOLIST);
        return false;
    }

    // Set new list
    List->list = NewList;

    // Update count
    ++List->count;

    return true;
}

bool _VIW_RemoveFromViewList(VIW_ViewList *List, VIW_View *View)
{
    extern uint32_t VIW_ErrorType;

    // Remove object
    VIW_View **NewList = (VIW_View **)_VIW_RemoveFromList((void **)List->list, List->count, View);

    if (NewList == NULL && List->count > 1)
    {
        if (VIW_ErrorType <= 1)
            _VIW_AddError(_VIW_ID_ERRORID_REMOVEFROMVIEWLIST_WARNING, _VIW_STRING_ERROR_REMOVEFROMLIST);

        else
            _VIW_AddError(_VIW_ID_ERRORID_REMOVEFROMVIEWLIST_ERROR, _VIW_STRING_ERROR_REMOVEFROMLIST);

        return false;
    }

    // Set new list
    List->list = NewList;

    // Update count
    --List->count;

    return true;
}

/*
VIW_View *VIW_CreateScriptView(VIW_View *Parent, uint64_t Time, uint64_t Increase, uint32_t Order)
{
    DBG_SessionStart("VIW_CreateScriptView");

    // Find the base
    VIW_View *NextBase = _VIW_FindBase(Parent);

    if (NextBase == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_CREATESCRIPTVIEW_NEXTBASE, _VIW_STRING_ERROR_NOBASE);
        DBG_SessionEnd();
        return NULL;
    }

    // Create view
    VIW_View *View = VIW_CreateViewWithPos(NextBase, ((VIW_PropertyBase *)NextBase->property.data)->_firstSubView);

    if (View == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_CREATESCRIPTVIEW_CREATEVIEW, _VIW_STRING_ERROR_CREATEVIEW);
        DBG_SessionEnd();
        return NULL;
    }

    // Create property
    if (!VIW_CreatePropertyScript(View))
    {
        VIW_DestroyView(View);
        _VIW_AddError(_VIW_ID_ERRORID_CREATESCRIPTVIEW_PROPERTY, _VIW_STRING_ERROR_ADDSCRIPTPROPERTY);
        DBG_SessionEnd();
        return NULL;
    }

    ++((VIW_PropertyBase *)NextBase->property.data)->_firstSubView;

    // Set property data
    if (!VIW_UpdateScriptTime(View, Time))
    {
        VIW_DestroyView(View);
        _VIW_AddError(_VIW_ID_ERRORID_CREATESCRIPTVIEW_TIME, _VIW_STRING_ERROR_UPDATETIME);
        DBG_SessionEnd();
        return NULL;
    }

    View->property._ownScript->increase = Increase;

    // Update the order
    if (!VIW_UpdateScriptOrder(View, Order))
    {
        VIW_DestroyView(View);
        _VIW_AddError(_VIW_ID_ERRORID_CREATESCRIPTVIEW_ORDER, _VIW_STRING_ERROR_UPDATESCRIPTORDER);
        DBG_SessionEnd();
        return NULL;
    }

    DBG_SessionEnd();
    return View;
}

bool VIW_CreatePropertyScript(VIW_View *View)
{
    // Find next base
    VIW_View *NextBase = _VIW_FindNextBase(View);

    if (NextBase == NULL)
    {
        _VIW_AddError(_VIW_ID_ERRORID_CREATEPROPERTYSCRIPT_NEXTBASE, _VIW_STRING_ERROR_NEXTBASE);
        return false;
    }

    // Get memory for own script
    VIW_Script *OwnScript = (VIW_Script *)DBG_Malloc(sizeof(VIW_Script));

    if (OwnScript == NULL)
    {
        _VIW_AddErrorForeign(_VIW_ID_ERRORID_CREATEPROPERTYSCRIPT_MALLOC, strerror(errno), _VIW_STRING_ERROR_MALLOC);
        return false;
    }

    // Initialize
    _VIW_InitStructScript(OwnScript);
    OwnScript->view = View;

    // Add own script to list of scripts in the next base
    if (!_VIW_AddToScriptList(&((VIW_PropertyBase *)NextBase->property.data)->_script, OwnScript))
    {
        DBG_Free(OwnScript);
        _VIW_AddError(_VIW_ID_ERRORID_CREATEPROPERTYSCRIPT_ADDTOLIST, _VIW_STRING_ERROR_ADDTOSCRIPTLIST);
        return false;
    }

    // Set property data
    View->property._type = VIW_ID_PROPERTY_SCRIPT;
    View->property._destroyFunc = &_VIW_DestroyPropertyScript;
    View->property._ownScript = OwnScript;
    View->property._nextBase = NextBase;

    return true;
}

void _VIW_DestroyPropertyScript(VIW_View *View)
{
    bool Return = true;

    // Remove it from the script list
    _VIW_RemoveFromScriptList(&((VIW_PropertyBase *)View->property._nextBase->property.data)->_script, View->property._ownScript);

    // Free the own script
    DBG_Free(View->property._ownScript);

    // Reinitialize
    _VIW_InitStructProperty(&View->property);

    return Return;
}

bool _VIW_AddToScriptList(VIW_ScriptList *List, VIW_Script *Script)
{
    extern uint32_t VIW_ErrorType;

    // Add it to the end of the script list
    VIW_Script **NewList = (VIW_Script **)_VIW_AddToListWithPos(List->list, List->count, Script, List->count);

    if (NewList == NULL)
    {
        if (VIW_ErrorType < 2)
            _VIW_AddError(_VIW_ID_ERRORID_ADDTOSCRIPTLIST_LISTWARNING, _VIW_STRING_ERROR_ADDTOLIST);

        else
            _VIW_AddError(_VIW_ID_ERRORID_ADDTOSCRIPTLIST_LISTERROR, _VIW_STRING_ERROR_ADDTOLIST);

        return false;
    }

    // Set new list
    List->list = NewList;

    // Update count
    ++List->count;

    // Set correct position
    if (!_VIW_UpdateScriptList(List, Script))
    {
        _VIW_AddError(_VIW_ID_ERRORID_ADDTOSCRIPTLIST_SORT, _VIW_STRING_ERROR_SORTLIST);
        return false;
    }

    return true;
}

void _VIW_RemoveFromScriptList(VIW_ScriptList *List, VIW_Script *Script)
{
    extern uint32_t VIW_ErrorType;

    // Remove object
    VIW_Script **NewList = (VIW_Script **)_VIW_RemoveFromList(List->list, List->count, Script);

    if (NewList == NULL && List->count > 1)
    {
        if (VIW_ErrorType < 2)
            _VIW_AddError(_VIW_ID_ERRORID_REMOVEFROMSCRIPTLIST_WARNING, _VIW_STRING_ERROR_REMOVEFROMLIST);

        else
            _VIW_AddError(_VIW_ID_ERRORID_REMOVEFROMSCRIPTLIST_ERROR, _VIW_STRING_ERROR_REMOVEFROMLIST);

        return false;
    }

    // Set new list
    List->list = NewList;

    // Update count
    --List->count;

    return true;
}

void _VIW_CleanScriptList(VIW_ScriptList *List)
{
    // If there is a list, free it
    if (List->list != NULL)
        DBG_Free(List->list);

    // Initialize
    _VIW_InitStructScriptList(List);
}
*/

#endif // VIEWS_CORE_FUNCTIONS_INITCLEAN_H_INCLUDED