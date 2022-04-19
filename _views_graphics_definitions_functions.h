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

// Functionality

// Update the graphics for the base
// Returns false on error
// View: The base view to update
bool _VIW_UpdateGraphicsBase(VIW_View *View);

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