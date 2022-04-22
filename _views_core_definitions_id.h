#ifndef VIEWS_CORE_DEFINITIONS_ID_H_INCLUDED
#define VIEWS_CORE_DEFINITIONS_ID_H_INCLUDED

// Anchor id, what part of a rectangle we are refering to
enum VIW_ID_Anchor
{
    VIW_ID_ANCHOR_NONE,
    VIW_ID_ANCHOR_CENTER,
    VIW_ID_ANCHOR_POS,
    VIW_ID_ANCHOR_NEG
};

// Relation id
enum VIW_ID_Relation
{
    VIW_ID_RELATION_NONE,
    VIW_ID_RELATION_BASE,    // Its base
    VIW_ID_RELATION_SIBLING, // The previous sibling
    VIW_ID_RELATION_ID       // By ID (This can be any of its earlier siblings, ancestors or ancestor siblings)
};

// Position type id
enum VIW_ID_Pos
{
    VIW_ID_POS_NONE,
    VIW_ID_POS_RIGID,       // Define the position using a number relative to bounding box
    VIW_ID_POS_RIGID_ABS,   // Defines the position using a number relative to window
    VIW_ID_POS_POINTER,     // Defines the position using a number from a pointer relative to bounding box
    VIW_ID_POS_POINTER_ABS, // Defines the position using a number from a pointer relative to window
    VIW_ID_POS_SINGLE,      // Defines the position from a single object
    VIW_ID_POS_BIAS         // Defines the position using 2 objects
};

// Size type id
enum VIW_ID_Size
{
    VIW_ID_SIZE_NONE,
    VIW_ID_SIZE_RIGID,   // A set number
    VIW_ID_SIZE_POINTER, // A pointer to a number
    VIW_ID_SIZE_DIFF,    // A difference between to objects
    VIW_ID_SIZE_COPY     // Copy the size from somewhere else
};

// Rect type id
enum VIW_ID_Rect
{
    VIW_ID_RECT_NONE,
    VIW_ID_RECT_STRETCH, // Stretch between 2 objects
    VIW_ID_RECT_ORIGIN   // Define an origin and a size
};

// Shape type id, how to get the shape
enum VIW_ID_Shape
{
    VIW_ID_SHAPE_NONE,
    VIW_ID_SHAPE_COPY,     // Copy shape from reference
    VIW_ID_SHAPE_ADVANCED, // Define shape using data
    VIW_ID_SHAPE_WINDOW    // Copy shape from window (used for the roots mostly)
};

// Property id
enum _VIW_ID_Property
{
    _VIW_ID_PROPERTY_NONE,
    _VIW_ID_PROPERTY_BASE,
    _VIW_ID_PROPERTY_SCRIPT,
    _VIW_ID_PROPERTY_EVENT,
    _VIW_ID_PROPERTY_GRAPHICSFILL,
    _VIW_ID_PROPERTY_GRAPHICSIMAGE,
    _VIW_ID_PROPERTY_GRAPHICSTEXT
};

// General property type
enum _VIW_ID_PropertyType
{
    _VIW_ID_PROPERTYTYPE_NONE,
    _VIW_ID_PROPERTYTYPE_EVENT,
    _VIW_ID_PROPERTYTYPE_GRAPHICS,
    _VIW_ID_PROPERTYTYPE_SCRIPT
};

// Positions of base subtype views
enum _VIW_ID_PropertyTypePos
{
    _VIW_ID_PROPERTYTYPEPOS_GRAPHICS = 0
};

// Return values for error
#define VIW_ID_RETURNERROR_POINTER (NULL)
#define VIW_ID_RETURNERROR_INT32_T (-2147483648)

#endif // VIEWS_CORE_DEFINITIONS_ID_H_INCLUDED