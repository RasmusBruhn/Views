#ifndef VIEWS_STANDARD_FUNCTIONS_BASE_H_INCLUDED
#define VIEWS_STANDARD_FUNCTIONS_BASE_H_INCLUDED

#include "Views.h"

bool VIW_RunScript(VIW_View *View, uint64_t Time)
{
    extern uint32_t VIW_ErrorType;
    bool Return = true;

    // Find the correct view to use
    View = _VIW_FindBase(View);

    if (View == NULL)
    {
        _VIW_SetError(_VIW_ID_ERRORID_RUNSCRIPT_TYPE, _VIW_STRING_ERROR_NOBASE);
        return false;
    }

    // Get the properties
    VIW_PropertyBase *Property = (VIW_PropertyBase *)View->property.data;

    // Make sure it has anything to run
    if (View->property._ownScript->time > Time)
        return true;

    // Go through all views and run them
    uint64_t NextTime = -1;

    for (VIW_Script **EndList = Property->_script.list + Property->_script.count, **ScriptList = Property->_script.list; ScriptList < EndList; ++ScriptList)
    {
        // Run script if needed
        if (Time > (*ScriptList)->time)
        {
            // Return error if there are no function
            if ((*ScriptList)->view->property._runScriptFunc == NULL)
            {
                _VIW_SetError(_VIW_ID_ERRORID_RUNSCRIPT_FUNCTION, _VIW_STRING_ERROR_NULLFUNCTION);
                Return = false;
            }

            // Run script
            else if (!(*ScriptList)->view->property._runScriptFunc((*ScriptList)->view, Time))
            {
                // Send warning
                if (VIW_ErrorType < 2)
                {
                    _VIW_AddError(_VIW_ID_ERRORID_RUNSCRIPT_RUNWARNING, _VIW_STRING_ERROR_SCRIPT);
                    Return = false;
                }

                // Send error
                else
                {
                    _VIW_AddError(_VIW_ID_ERRORID_RUNSCRIPT_RUNERROR, _VIW_STRING_ERROR_SCRIPT);
                    return false;
                }
            }

            // Increment timer
            (*ScriptList)->time += (*ScriptList)->increase; 
        }

        // Get lowest time
        NextTime = OBJ_Min(NextTime, (*ScriptList)->time);
    }

    // Set the lowest time
    VIW_UpdateScriptTime(View, NextTime);

    return Return;
}

bool VIW_RunEvent(VIW_View *View, uint32_t EventID, int32_t MouseX, int32_t MouseY)
{
    return true;
}

bool VIW_DrawGraphics(VIW_View *View, SDL_Renderer *Rend)
{
    return true;
}

bool VIW_UpdateEventOrder(VIW_View *View, uint32_t Order)
{
}

bool VIW_UpdateScriptOrder(VIW_View *View, uint32_t Order)
{
    // Set new order value for script
    View->property._orderScript = Order;

    // Update the list
    if (!_VIW_UpdateScriptList(&((VIW_PropertyBase *)View->property._nextBase->property.data)->_script, View->property._ownScript))
    {
        _VIW_AddError(_VIW_ID_ERRORID_UPDATESCRIPTORDER_UPDATELIST, _VIW_STRING_ERROR_SORTLIST);
        return false;
    }

    return true;
}

bool VIW_UpdateGraphicsOrder(VIW_View *View, uint32_t Order)
{
}

bool VIW_UpdateScriptTime(VIW_View *View, uint64_t Time)
{
    // Set the time
    if (View->property._ownScript == NULL)
    {
        _VIW_SetError(_VIW_ID_ERRORID_UPDATESCRIPTTIME_OWNSCRIPT, _VIW_STRING_ERROR_NOSCRIPT);
        return false;
    }

    View->property._ownScript->time = Time;

    if (View->property._nextBase != NULL)
        View->property._nextBase->property._ownScript->time = OBJ_Min(View->property._nextBase->property._ownScript->time, Time);

    return true;
}

bool _VIW_UpdatePropertyBase(VIW_View *View)
{
    // Nothing here yet, need to update texture if shape changes and texture is used
    return true;
}

bool _VIW_UpdateScriptList(VIW_ScriptList *List, VIW_Script *Script)
{
    // Find the script
    VIW_Script **ScriptPos;

    for (ScriptPos = List->list + List->count - 1; ScriptPos + 1 > List->list; --ScriptPos)
        if (*ScriptPos == Script)
            break;

    // Make sure it found the script
    if (ScriptPos + 1 == List->list)
    {
        _VIW_SetError(_VIW_ID_ERRORID_UPDATESCRIPTLIST_LOCATE, _VIW_STRING_ERROR_LOCATEOBJECT);
        return false;
    }

    // Find the new position
    VIW_Script **Var;

    // If it needs to move down
    while (ScriptPos > List->list && Script->view->property._orderScript < (*(ScriptPos - 1))->view->property._orderScript)
        *ScriptPos = *(--ScriptPos);

    // If it need to move up
    while (ScriptPos < List->list + List->count - 1 && Script->view->property._orderScript > (*(ScriptPos + 1))->view->property._orderScript)
        *ScriptPos = *(++ScriptPos);

    // Set csript to it's new position
    *ScriptPos = ScriptPos;

    return true;
}

bool _VIW_UpdateGraphicsList(VIW_ViewList *List, VIW_View *View)
{
}

VIW_View *VIW_FindNextBase(VIW_View *View)
{
    // Check if it is a root
    if (View->_parent.root == View)
    {
        _VIW_SetError(_VIW_ID_ERRORID_FINDNEXTBASE_ROOT, _VIW_STRING_ERROR_ROOTNEXTBASE);
        return NULL;
    }

    // Find the next base
    VIW_View *NextBase;

    for (NextBase = View->_parent.parent; NextBase->property._type != VIW_ID_PROPERTY_BASE; NextBase = NextBase->_parent.parent)
        if (NextBase == NextBase->_parent.root)
        {
            _VIW_SetError(_VIW_ID_ERRORID_FINDNEXTBASE_NOBASE, _VIW_STRING_ERROR_NEXTBASE);
            return NULL;
        }

    return NextBase;
}

VIW_View *_VIW_FindBase(VIW_View *View)
{
    // If view is base itself, return view
    if (View->property._type == VIW_ID_PROPERTY_BASE)
        return View;

    // If first child is base, return child
    if (View->_child.list.count > 0 && (*View->_child.list.list)->property._type == VIW_ID_PROPERTY_BASE)
        return (*View->_child.list.list);

    // No base was found
    _VIW_SetError(_VIW_ID_ERRORID_FINDBASE_NOBASE, _VIW_STRING_ERROR_NOBASE);
    return NULL;
}

#endif