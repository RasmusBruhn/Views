#ifndef VIEWS_STANDARD_DEFINITIONS_FUNCTIONS_H_INCLUDED
#define VIEWS_STANDARD_DEFINITIONS_FUNCTIONS_H_INCLUDED

#include "Views.h"

// External functions

// Initialization and cleanup

// Creates a new root
// Returns the root, NULL on error
// Window: The window the root is located in
// Rend: The renderer for the window
VIW_View *VIW_CreateRoot(SDL_Window *Window, SDL_Renderer *Rend);

// Destroys a root and all its children
// Returns true on success and false on error
// Root: The root to destroy
void VIW_DestroyRoot(VIW_View *Root);

// Creates a new view and puts it in the specified location in the child list
// Returns the view, NULL on error
// Parent: The parent view it is created within
// ChildPos: The position of the new view in the child list
VIW_View *VIW_CreateViewWithPos(VIW_View *Parent, uint32_t ChildPos);

// Destroys a view and all it's children
// Returns true on success and false on error
// View: The view to destroy
void VIW_DestroyView(VIW_View *View);

// Cleans up all views and other data
// Returns nothing
void VIW_Quit(void);

// Creates a new empty view with a child with base property
// Returns the view, NULL on error
// Parent: If this view is a "base" then it is the parent, if it has a "base" child then that is the parent, but one must be a "base"
// OrderScript: The order to determine location in script list
// OrderEvent: The order to determine location in event list
// OrderGraphics: The order to determine location in graphics list
VIW_View *VIW_CreateSubView(VIW_View *Parent, uint32_t OrderScript, uint32_t OrderEvent, uint32_t OrderGraphics);

// Creates a view with a base property
// Returns the view on success and NULL on error
// Parent: The parent of the view
// OrderScript: The order to determine location in script list
// OrderEvent: The order to determine location in event list
// OrderGraphics: The order to determine location in graphics list
VIW_View *VIW_CreateBaseView(VIW_View *Parent, uint32_t OrderScript, uint32_t OrderEvent, uint32_t OrderGraphics);

// Creates a view with a script property
// Returns the view on success and NULL on error
// Parent: If this view is a "base" then it is the parent, if it has a "base" child then that is the parent, but one must be a "base"
// Time: The next time when the script should activate
// Increase: The amount of time to increase Time with on every activation
// Order: The order to determine location in script list
VIW_View *VIW_CreateScriptView(VIW_View *Parent, uint64_t Time, uint64_t Increase, uint32_t Order);

// Initializes the advanced shape data for a view, allowing it to be used
// Returns true on success and false on error
// View: The view for which to add shape data
bool VIW_UseAdvancedShapeData(VIW_View *View);

// Adds a reference to a view, and makes sure this view will be updated properly when ref is updated
// Returns true on success and false on error
// View: The view for which the ref is added
// Ref: The reference structure in the view
// Type: The type of reference
// ID: If typse is ID then this is the view pointer
bool VIW_AddRef(VIW_View *View, VIW_Reference *Ref, enum VIW_ID_Relation type, VIW_View *ID);

// Creates the base property for a view
// Returns true on success and false on error
// View: The view for which to add the peroperty
bool VIW_CreatePropertyBase(VIW_View *View);

// Creates the script property for a view
// Returns true on success and false on error
// View: The view for which to add the peroperty
bool VIW_CreatePropertyScript(VIW_View *View);

// Run

// Run a script (functions) from view (if it has a script property), distribute script activation (if it has a base property)
// Returns true on success and false on error
// View: The view to run script from
bool VIW_RunScript(VIW_View *View, uint64_t Time);

// Run an event from the view (if it has an event property), distribute event activation (if it has a base property)
// Returns true on success and false on error
// View: The view to run event from
// EventID: The ID of the event
// MouseX: The x position of the mouse relative to parent view
// MouseY: The y position of the mouse relative to parent view
bool VIW_RunEvent(VIW_View *View, uint32_t EventID, int32_t MouseX, int32_t MouseY);

// Draw the graphics from this view (if it has a graphics property), distribute graphics activation (if it has a base property)
// Returns true on success and false on error
// View: The view to draw
// Rend: The renderer to draw to
bool VIW_DrawGraphics(VIW_View *View, SDL_Renderer *Rend);

// Updates the event order
// Returns true on success and false on error
// View: The view to update the order for
// Order: The new event order value for the view
bool VIW_UpdateEventOrder(VIW_View *View, uint32_t Order);

// Updates the sript order
// Returns true on success and false on error
// View: The view to update the order for
// Order: The new script order value for the view
bool VIW_UpdateScriptOrder(VIW_View *View, uint32_t Order);

// Updates the graphics draw order
// Returns true on success and false on error
// View: The view to update the order for
// Order: The new graphics draw order value for the view
bool VIW_UpdateGraphicsOrder(VIW_View *View, uint32_t Order);

// Updates the time before next sript activation for a view
// Returns true on success and false on error
// View: The view to update time for
// Time: The new time
bool VIW_UpdateScriptTime(VIW_View *View, uint64_t Time);

// Finds the next base view
// Returns the base view on success and NULL on error
// View: The view for which to find the next ancestor which is a base
VIW_View *VIW_FindNextBase(VIW_View *View);

// Internal functions

// Set shape

// Updates the shape of a view
// Returns true on success, false on error
// View: The view to be updated
// AllowSiblingUpdate: if true then it can update its siblings, if false it cannot
bool _VIW_UpdateShape(VIW_View *View, bool AllowSiblingUpdate);

// Updates the shape of a view by copying it from another view
// Returns true on success and false on error
// View: The view to be updated
bool _VIW_UpdateShapeCopy(VIW_View *View);

// Updates the shape using it's window
// Returns true on success and false on error
// View: The view to be updated
bool _VIW_UpdateShapeWindow(VIW_View *View);

// Updates the shape of a view using anchors
// Returns true on success, false on error
// View: The view to be updated
bool _VIW_UpdateShapeAdvanced(VIW_View *View);

// Updates one coordinate of the shape of a view
// Returns true on success, false on error
// View: The view which should have it's shape changed
// Coord: The RectPart structure of the coordinate to update
// GetPos: A function to retrieve a pointer to the position of (x or y) of the shape of a view
// GetSize: A function to retrieve a pointer to the position of (w or h) of the shape of a view
bool _VIW_UpdateShapeCoord(VIW_View *View, VIW_RectPart *Coord, int32_t *(*GetPos)(VIW_View *View), int32_t *(*GetSize)(VIW_View *View));

// Updates one coordinate of the shape of a view by the method of Stretch (shape is stretched between 2 points)
// Returns true on success, false on error
// View: The view which should have it's shape changed
// Coord: The RectStretch structure of the coordinate to update
// GetPos: A function to retrieve a pointer to the position of (x or y) of the shape of a view
// GetSize: A function to retrieve a pointer to the position of (w or h) of the shape of a view
bool _VIW_UpdateShapeCoordStretch(VIW_View *View, VIW_RectStretch *Coord, int32_t *(*GetPos)(VIW_View *View), int32_t *(*GetSize)(VIW_View *View));

// Updates one coordinate of the shape of a view by the method of Origin (the origin of the shape is set by 1 point and the size of the shape is set by 1 size)
// Returns true on success, false on error
// View: The view which should have it's shape changed
// Coord: The RectOrigin structure of the coordinate to update
// GetPos: A function to retrieve a pointer to the position of (x or y) of the shape of a view
// GetSize: A function to retrieve a pointer to the position of (w or h) of the shape of a view
bool _VIW_UpdateShapeCoordOrigin(VIW_View *View, VIW_RectOrigin *Coord, int32_t *(*GetPos)(VIW_View *View), int32_t *(*GetSize)(VIW_View *View));

// Gets a size by using a specific method
// Returns the size and VIW_ID_RETURNERROR_INT32_T on error
// View: The view which should have a size calculated
// SizeData: The Size structure containing data to calculate the size
// GetPos: A function to retrieve a pointer to the position of (x or y) of the shape of a view
// GetSize: A function to retrieve a pointer to the position of (w or h) of the shape of a view
int32_t _VIW_GetSize(VIW_View *View, VIW_Size *SizeData, int32_t *(*GetPos)(VIW_View *View), int32_t *(*GetSize)(VIW_View *View));

// Copies the size from another view
// Returns the size, VIW_ID_RETURNERROR_INT32_T on error
// View: The view for which to calculate the size
// SizeData: The SizeCopy structure to get the size
int32_t _VIW_GetSizeCopy(VIW_View *View, VIW_SizeCopy *SizeData);

// Gets a size by finding the difference between 2 positions
// Returns the size and VIW_ID_RETURNERROR_INT32_T on error
// View: The view which should have a size calculated
// SizeData: The SizeDiff structure containing data to calculate the size
// GetPos: A function to retrieve a pointer to the position of (x or y) of the shape of a view
// GetSize: A function to retrieve a pointer to the position of (w or h) of the shape of a view
int32_t _VIW_GetSizeDiff(VIW_View *View, VIW_SizeDiff *SizeData, int32_t *(*GetPos)(VIW_View *View), int32_t *(*GetSize)(VIW_View *View));

// Gets a position by use of a specified method
// Returns the position and VIW_ID_RETURNERROR_INT32_T on error
// View: The view which should have a position calculated
// PosData: The Pos structure containing data to calculate the position
// GetPos: A function to retrieve a pointer to the position of (x or y) of the shape of a view
// GetSize: A function to retrieve a pointer to the position of (w or h) of the shape of a view
int32_t _VIW_GetPos(VIW_View *View, VIW_Pos *PosData, int32_t *(*GetPos)(VIW_View *View), int32_t *(*GetSize)(VIW_View *View));

// Gets the position anchored to with the given biased anchor
// Returns the anchor point and VIW_ID_RETURNERROR_INT32_T on error
// View: The view for which this anchor belongs
// Anchor: The data to get the biased anchor point
// GetPos: A function to retrieve a pointer to the position of (x or y) of the shape of a view
// GetSize: A function to retrieve a pointer to the position of (w or h) of the shape of a view
int32_t _VIW_GetBiasAnchorPoint(VIW_View *View, VIW_BiasAnchor *Anchor, int32_t *(*GetPos)(VIW_View *View), int32_t *(*GetSize)(VIW_View *View));

// Gets the position anchored to with the given anchor
// Returns the anchor point and VIW_ID_RETURNERROR_INT32_T on error
// View: The view for which this anchor belongs
// Anchor: The data to get the anchor point
// GetPos: A function to retrieve a pointer to the position of (x or y) of the shape of a view
// GetSize: A function to retrieve a pointer to the position of (w or h) of the shape of a view
int32_t _VIW_GetAnchorPoint(VIW_View *View, VIW_Anchor *Anchor, int32_t *(*GetPos)(VIW_View *View), int32_t *(*GetSize)(VIW_View *View));

// Finds the view which there is a reference to
// Returns a pointer to the view, NULL on error
// View: The view for which the reference is calculated
// Ref: The data for the reference
VIW_View *_VIW_FindRefView(VIW_View *View, VIW_Reference *Ref);

// Retrieves a pointer to the x of the shape of a view
// Returns a pointer to the coordinate
// View: The view for which to retrieve the coordinate
int32_t *_VIW_GetX(VIW_View *View);

// Retrieves a pointer to the y of the shape of a view
// Returns a pointer to the coordinate
// View: The view for which to retrieve the coordinate
int32_t *_VIW_GetY(VIW_View *View);

// Retrieves a pointer to the w of the shape of a view
// Returns a pointer to the size
// View: The view for which to retrieve the size
int32_t *_VIW_GetW(VIW_View *View);

// Retrieves a pointer to the h of the shape of a view
// Returns a pointer to the size
// View: The view for which to retrieve the size
int32_t *_VIW_GetH(VIW_View *View);

// Initialization and cleanup

// Destroys the base property for a view
// Returns true on success and false on error
// View: The view to remove property for
void _VIW_DestroyPropertyBase(VIW_View *View);

// Destroys the script property for a view
// Returns true on success and false on error
// View: The view to destroy the property for
void _VIW_DestroyPropertyScript(VIW_View *View);

// Adds an object to a list at a specific position
// Returns a pointer to the new list, NULL on error
// List: The list to add the object to
// Length: The length of the list
// Object: The object to add to the list
// Pos: The position to add the object at
void *_VIW_AddToListWithPos(void **List, uint32_t Length, void *Object, uint32_t Pos);

// Removes an object from a list
// Returns a pointer to the new list, NULL on error or if the last object is removed
// List: The list to remove the object from
// Length: The length of the list
// Object: The object to remove from the list
void *_VIW_RemoveFromList(void **List, uint32_t Length, void *Object);

// Adds a view to the view list at a specific position
// Returns true on success and false on error
// List: The list to add a view to
// View: The view to add to the list
// Pos: The position to add the view
bool _VIW_AddToViewListWithPos(VIW_ViewList *List, VIW_View *View, uint32_t Pos);

// Removes a view from a list
// Returns true on success and false on error
// List: The list to remove a view from
// View: The view to remove from the list
void _VIW_RemoveFromViewList(VIW_ViewList *List, VIW_View *View);

// Cleans up a list, removes all views and initializes all
// Returns nothing
// List: The list to clean
void _VIW_CleanViewList(VIW_ViewList *List);

// Adds an event to the event list
// Returns true on success and false on error
// List: The list to add an event to
// Event: The event to add to the list
bool _VIW_AddToEventList(VIW_EventList *List, VIW_Event *Event);

// Removes an event from a list
// Returns true on success and false on error
// List: The list to remove an event from
// Event: The event to remove from the list
void _VIW_RemoveFromEventList(VIW_EventList *List, VIW_Event *Event);

// Cleans up a list, removes all events and initializes all
// Returns nothing
// List: The list to clean
void _VIW_CleanEventList(VIW_EventList *List);

// Adds a script to the sript list
// Returns true on success and false on error
// List: The list to add a script to
// Script: The script to add to the list
bool _VIW_AddToScriptList(VIW_ScriptList *List, VIW_Script *Script);

// Removes a script from a list
// Returns true on success and false on error
// List: The list to remove a script from
// Script: The script to remove from the list
void _VIW_RemoveFromScriptList(VIW_ScriptList *List, VIW_Script *Script);

// Cleans up a list, removes all scripts and initializes all
// Returns nothing
// List: The list to clean
void _VIW_CleanScriptList(VIW_ScriptList *List);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructViewList(VIW_ViewList *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructView(VIW_View *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructParent(VIW_Parent *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructChild(VIW_Child *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructProperty(VIW_Property *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructFlagsSet(VIW_FlagsSet *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructFlags(VIW_Flags *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructWindow(VIW_Window *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructShape(VIW_Shape *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructBounds(VIW_Bounds *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructShapeData(VIW_ShapeData *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructRect(VIW_Rect *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructRectPart(VIW_RectPart *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructRectOrigin(VIW_RectOrigin *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructRectStretch(VIW_RectStretch *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructSize(VIW_Size *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructSizeCopy(VIW_SizeCopy *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructSizeDiff(VIW_SizeDiff *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructPos(VIW_Pos *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructBiasAnchor(VIW_BiasAnchor *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructAnchor(VIW_Anchor *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructReference(VIW_Reference *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructEvent(VIW_Event *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructEventList(VIW_EventList *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructScript(VIW_Script *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructScriptList(VIW_ScriptList *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructPropertyBase(VIW_PropertyBase *Struct);

// Run

// Updates the property "base"
// Returns true on success and false on error
// View: The view which holds the property
bool _VIW_UpdatePropertyBase(VIW_View *View);

// Updates the order of one script in a script list
// Returns true on success and false on error
// List: The list to update
// Script: The script to change the position of
bool _VIW_UpdateScriptList(VIW_ScriptList *List, VIW_Script *Script);

// Updates the order of one graphic view in a graphics list
// Returns true on success and false on error
// List: The list to update
// View: The view to change the position of
bool _VIW_UpdateGraphicsList(VIW_ViewList *List, VIW_View *View);

// Finds the base view, either the view itself or it's child
// Returns the base view, NULL on error
// View: The view to find base at
VIW_View *_VIW_FindBase(VIW_View *View);

#endif