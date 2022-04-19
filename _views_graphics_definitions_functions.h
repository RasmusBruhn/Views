#ifndef VIEWS_GRAPHICS_DEFINITIONS_FUNCTIONS
#define VIEWS_GRAPHICS_DEFINITIONS_FUNCTIONS

#include "Views.h"
#include <stdio.h>
#include <stdint.h>

// Initialisation and cleanup

// Initialises a canvas
// Returns false on error
// View: The view to create the canvas for
bool _VIW_CreateCanvas(VIW_View *View);

// Updates the size of a canvas
// Returns false on error
// View: The view to update the canvas for
bool _VIW_UpdateCanvas(VIW_View *View);

// Destroys a canvas
// View: The view to destroy the canvas for
void _VIW_DestroyCanvas(VIW_View *View);

// Base functions

// Create a graphics base property
// Returns false on error
// View: The view to add the graphics for
bool _VIW_CreatePropertyGraphics(VIW_View *View);

// Creates a graphics base view
// Returns false on error
// Parent: The parent of the view
bool _VIW_CreateGraphicsView(VIW_View *Parent);

// Destroy a graphics base
// View: The view to remove the property for
void _VIW_DestroyPropertyGraphics(VIW_View *View);

// Draw the graphics for the base (run)
// View: The view to draw the graphics for
bool _VIW_RunPropertyGraphics(VIW_View *View);

// Update the graphics for the base
// Returns false on error
// View: The base view to update
bool _VIW_UpdatePropertyGraphics(VIW_View *View);

// Add graphics to a base list

// Remove graphics from a base list

// Update the prosition on a base list

// Struct initialisers

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructPropertyGraphics(VIW_PropertyGraphics *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructPropertyGraphicsBase(VIW_PropertyGraphicsBase *Struct);

#endif // VIEWS_GRAPHICS_DEFINITIONS_FUNCTIONS