// Defines the structs and unions
#ifndef VIEWS_CORE_DEFINITIONS_STRUCTS_H_INCLUDED
#define VIEWS_CORE_DEFINITIONS_STRUCTS_H_INCLUDED

#include "Views.h"
#include <stdinc.h>
#include <SDL2/SDL.h>
#include <Objects.h>

// Structures
typedef struct __VIW_View VIW_View;
typedef struct __VIW_Reference VIW_Reference;
typedef struct __VIW_Anchor VIW_Anchor;
typedef struct __VIW_BiasAnchor VIW_BiasAnchor;
typedef union ___VIW_Pos _VIW_Pos;
typedef struct __VIW_Pos VIW_Pos;
typedef struct __VIW_SizeDiff VIW_SizeDiff;
typedef union ___VIW_Size _VIW_Size;
typedef struct __VIW_Size VIW_Size;
typedef struct __VIW_RectStretch VIW_RectStretch;
typedef struct __VIW_RectOrigin VIW_RectOrigin;
typedef union ___VIW_RectPart _VIW_RectPart;
typedef struct __VIW_RectPart VIW_RectPart;
typedef struct __VIW_Rect VIW_Rect;
typedef union ___VIW_ShapeData _VIW_ShapeData;
typedef struct __VIW_ShapeData VIW_ShapeData;
typedef struct __VIW_Bounds VIW_Bounds;
typedef struct __VIW_Shape VIW_Shape;
typedef struct __VIW_Window VIW_Window;
typedef struct __VIW_Flags VIW_Flags;
typedef struct __VIW_FlagsSet VIW_FlagsSet;
typedef struct __VIW_Property VIW_Property;
typedef struct __VIW_Child VIW_Child;
typedef struct __VIW_Parent VIW_Parent;
typedef struct __VIW_ViewList VIW_ViewList;
typedef struct __VIW_Event VIW_Event;
typedef struct __VIW_EventList VIW_EventList;
typedef struct __VIW_Script VIW_Script;
typedef struct __VIW_ScriptList VIW_ScriptList;
typedef struct __VIW_PropertyBase VIW_PropertyBase;

// List of views with count
struct __VIW_ViewList
{
    VIW_View **list;
    uint32_t count;
};

// Structure to determine a reference to a view
struct __VIW_Reference
{
    enum VIW_ID_Relation view; // The view it is anchored to, VIW_ID_Relation
    VIW_View *ref;             // If it is anchored to view by id then this is the id
};

// Anchor, how something is anchored
struct __VIW_Anchor
{
    VIW_Reference ref;              // The data to determine the anchor view
    enum VIW_ID_Anchor anchorPoint; // The position it is anchored to on that view, VIW_ID_Anchor
    int32_t offset;                 // The offset from the anchor point where it is anchored
};

// Biased anchor, an anchor point determined from 2 anchors
struct __VIW_BiasAnchor
{
    VIW_Anchor anchor1; // The first anchor point
    VIW_Anchor anchor2; // The second anchor point
    double bias;        // The bias between the anchor points (0 is anchor1 and 1 is anchor2, linear scaling, can be outside this range)
};

// Position union
union ___VIW_Pos
{
    int32_t rigid;       // When a set value is used
    int32_t *pointer;    // When a pointer to a value is used
    VIW_Anchor single;   // When a single anchor is used
    VIW_BiasAnchor bias; // When a biased anchor is used
};

// Position, includes data to find a position, like x or y
struct __VIW_Pos
{
    enum VIW_ID_Pos type; // How the position is to be determined, VIW_ID_Pos
    _VIW_Pos data;        // The data to determine the position
};

// Data to find the distance between 2 points
struct __VIW_SizeDiff
{
    VIW_Pos pos1; // The first position
    VIW_Pos pos2; // The second position
};

// Size union
union ___VIW_Size
{
    int32_t rigid;      // When a set value is used
    int32_t *pointer;   // When a pointer to a value is used
    VIW_SizeDiff diff;  // When a difference between 2 positions is used
    VIW_Reference copy; // When a size is copied from another view
};

// Data to calculate a size
struct __VIW_Size
{
    enum VIW_ID_Size type; // How the size is determined, VIW_ID_Size
    _VIW_Size data;        // The data to determine the size
    double scale;          // How much to scale the size
};

// Definition of rectangle (one coordinate) by setting the position of both sides of the rectangle
struct __VIW_RectStretch
{
    VIW_Pos pos1; // The position of the negative side
    VIW_Pos pos2; // The position of the positive side
};

// Definition of rectangle (one coordinate) by setting the origin and size
struct __VIW_RectOrigin
{
    enum VIW_ID_Anchor origin; // The origin on the rectangle (the point on the rectangle defined as the origin), VIW_ID_Anchor
    VIW_Pos pos;               // The position of the origin
    VIW_Size size;             // The size of the rectangle
};

// Union for one coordinate of rectangle
union ___VIW_RectPart
{
    VIW_RectStretch stretch; // If stretch is used
    VIW_RectOrigin origin;   // If origin is used
};

// Data to calculate one coordinate of a rectangle
struct __VIW_RectPart
{
    enum VIW_ID_Rect type; // How the rectangle is determined, VIW_ID_Rect
    _VIW_RectPart data;    // The data to determine the coordinate of the rectangle
};

// Definition of rectangle
struct __VIW_Rect
{
    VIW_RectPart x; // The x coordinate
    VIW_RectPart y; // The y coordinate
};

// Union for shape data
union ___VIW_ShapeData
{
    VIW_Reference ref; // Reference used if it should copy the data
    VIW_Rect *data;    // Data for when it is on advanced mode
};

// The shape data of a view
struct __VIW_ShapeData
{
    enum VIW_ID_Shape type; // The method for getting the shape
    _VIW_ShapeData data;    // The data
};

// bounds data, contains information on the size and position bounds
struct __VIW_Bounds
{
    SDL_Rect rect; // The rectangle the view must be within in absolute coordinates
};

// shape data, contains information on the shape
struct __VIW_Shape
{
    SDL_Rect rect;      // The rect defining the view, this is in absolute coordinates
    SDL_Rect boundRect; // The part of rect within the bounds
};

// Window data, information on the window in which the view is located
struct __VIW_Window
{
    SDL_Window *window; // Pointer to the window it is located in
    SDL_Renderer *rend; // Pointer to the renderer of the window
    uint32_t ID;        // The window ID
};

// Flags, all flags for the view which can be changed by user
struct __VIW_Flags
{
    bool freezeShape : 1;    // If true then the shape will not update
    bool active : 1;         // If false then the view won't be updated or visible by other views
};

// Set flags, all flags for the view which should not be changed
struct __VIW_FlagsSet
{
    bool active : 1;            // If false then the view won't be updated or visible by other views
    bool totalActive : 1;       // Only true if both active is true
    bool updateNextSibling : 1; // If true then when this view is updated it will update the next sibling
    bool updateAllSiblings : 1; // If true then when this view is updated it will update all siblings after this
};
// QUESTIONABLE
// View properties, the special properties for a view
struct __VIW_Property
{
    uint32_t _type;                                                                          // The type of view property
    void *data;                                                                              // The property data
    bool (*_updateFunc)(VIW_View *View);                                                     // The function when the view has updated its shape
    void (*_destroyFunc)(VIW_View *View);                                                    // The function which destroys the property
    bool (*_runEventFunc)(VIW_View *View, uint32_t EventID, int32_t MouseX, int32_t MouseY); // The function to run when event is run
    bool (*_runScriptFunc)(VIW_View *View, uint64_t Time);                                   // The function to run when script is run
    bool (*_drawGraphicsFunc)(VIW_View *View, SDL_Renderer *Rend);                           // The function to run when graphics need to be drawn
    uint32_t _orderEvent;                                                                    // The order value for running events, lower order means that it will be run before other views
    uint32_t _orderScript;                                                                   // The order value for running scripts, lower order means that it will be run before other views
    uint32_t _orderGraphics;                                                                 // The order value for drawing graphics, lower order means that it will be run before other views
    VIW_View *_nextBase;                                                                     // The base up next in the hierarchy
    VIW_Script *_ownScript;                                                                  // Pointer to it's own script data in the next base
    uint32_t *_ownEventID;                                                                   // Pointer to it's own event data in the next base

    // enum _VIW_ID_Property _type;                 // The type of view property
    // void *data;                                  // The property data
    // bool (*_updateFunc)(VIW_View *View);         // The function when the view has updated its shape
    // void (*_destroyFunc)(VIW_View *View);        // The function which destroys the property
    // bool (*_runFunc)(VIW_View *View);            // The function to run when the view is activated
    // uint32_t order;                              // The order in which it should use the run function, lowest order view runs first
    // enum _VIW_ID_PropertyType _runType;         // The type of run function that it uses (and the type the order is)
};

// Children
struct __VIW_Child
{
    VIW_ViewList list; // A list of pointers to all the children of the view
};

// Parent
struct __VIW_Parent
{
    VIW_View *parent;  // A pointer to the parent view
    uint32_t childPos; // The position in the child list from the parent it is located
    VIW_View *root;    // The view within which all other views are
};

// View structure
struct __VIW_View
{
    VIW_Bounds _bounds;      // The bounds enharitet from it's parent
    VIW_Shape _shape;        // The shape of the view
    VIW_Window _window;      // The window and information about it
    VIW_Child _child;        // All information on children views
    VIW_Parent _parent;      // All information on the parent
    VIW_FlagsSet _flags;     // The flags which should only be changed in the native functions
    VIW_Flags flags;         // The flags which should be changed by programmer
    VIW_ShapeData shapeData; // The data to use to determine the shape
    VIW_Property property;   // The special properties for this view, button, graphics ect.
};

// This is all questionable, probably needs to be removed and added in some expansion instead
// MISSING
// Event types with associated views
struct __VIW_Event
{
    uint32_t ID;       // The ID of the event
    VIW_ViewList list; // The list of views using this event
};
// MISSING
// List of events
struct __VIW_EventList
{
    VIW_Event **list; // The list of events
    uint32_t count;   // The number of events in the list
};
// MISSING
// Script views and when to activate them
struct __VIW_Script
{
    VIW_View *view;    // The view which holds the script
    uint64_t time;     // The time (clock_t, returned by clock_t) that this script should be activated in clock ticks
    uint64_t increase; // The amount of time to increate the timer with after each activation
};
// MISSING
// List of sripts
struct __VIW_ScriptList
{
    VIW_Script **list; // The list of scripts
    uint32_t count;    // The number of scripts in the list
};
// MISSING
// Base property structure
struct __VIW_PropertyBase
{
    VIW_ScriptList _script; // The list of scripts
    VIW_EventList _event;   // The list of events
    VIW_ViewList _graphics; // The list of graphics
    SDL_Texture *_texture;  // The texture for drawing
    bool useTexture : 1;   // True if it should use the texture
    uint32_t _firstSubView; // The position of the first sub view in the child list, all view behind this is property views
};

#endif // VIEWS_CORE_DEFINITIONS_STRUCTS_H_INCLUDED