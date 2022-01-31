#ifndef VIEWS_STANDARD_FUNCTIONS_MACROS_H_INCLUDED
#define VIEWS_STANDARD_FUNCTIONS_MACROS_H_INCLUDED

#include "Views.h"

// Updates the shape of a view
// Returns true on success, false on error
// View: The view to be updated
#define VIW_UpdateShape(View) _VIW_UpdateShape(View, true)

// Creates a new view and puts it at the end of the child list
// Returns the view, NULL on error
// Parent: The parent view it is created within
#define VIW_CreateView(Parent) VIW_CreateViewWithPos(Parent, (Parent)->_child.list.count)

// Activates a view
// Returns total active
// View: The view to activate
#define VIW_ActivateView(View) ((View)->data._flags.totalActive = ((View)->data._flags.active & ((View)->data.flags.active = true)))

// Deactivates a view
// Returns total active
// View: The view to deactivate
#define VIW_DeactivateView(View) ((View)->data._flags.totalActive = ((View)->data._flags.active & ((View)->data.flags.active = false)))

// Toggles a view (If it is active then deactivate it, if it is deactive then activate it)
// Returns total active
// View: The view to toggle
#define VIW_ToggleView(View) ((View)->data._flags.totalActive = ((View)->data._flags.active & ((View)->data.flags.active = ~(View)->data.flags.active)))

// Adds a view to the view list at the end
// Returns true on success and false on error
// List: The list to add a view to
// View: The view to add to the list
#define _VIW_AddToViewList(List, View) _VIW_AddToViewListWithPos(List, View, (List)->count)

// Activates a view (the hidden activation)
// Returns total active
// View: The view to activate
#define _VIW_ActivateView(View) ((View)->data._flags.totalActive = ((View)->data.flags.active & ((View)->data._flags.active = true)))

// Deactivates a view (the hidden activation)
// Returns total active
// View: The view to deactivate
#define _VIW_DeactivateView(View) ((View)->data._flags.totalActive = ((View)->data.flags.active & ((View)->data._flags.active = false)))

// Toggles a view (If it is active then deactivate it, if it is deactive then activate it) (the hidden activation)
// Returns total active
// View: The view to toggle
#define _VIW_ToggleView(View) ((View)->data._flags.totalActive = ((View)->data.flags.active & ((View)->data._flags.active = ~(View)->data._flags.active)))

#endif