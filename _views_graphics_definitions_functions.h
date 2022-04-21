#ifndef VIEWS_GRAPHICS_DEFINITIONS_FUNCTIONS
#define VIEWS_GRAPHICS_DEFINITIONS_FUNCTIONS

#include "Views.h"
#include <stdio.h>
#include <stdint.h>

// Initialisation and cleanup

// Creates or updates size of a canvas
// Returns true on success and false on error
// View: The view to create the canvas for
bool _VIW_CreateCanvas(VIW_View *View);

// Destroys a canvas
// View: The view to destroy the canvas for
void _VIW_DestroyCanvas(VIW_View *View);

// Base functions

// Create a graphics base property
// Returns true on success and false on error
// View: The view to add the graphics for
bool VIW_CreatePropertyGraphicsBase(VIW_View *View);

// Creates a graphics base view
// Returns true on success and false on error
// Parent: The parent of the view
VIW_View *VIW_CreateGraphicsBaseView(VIW_View *Parent);

// Destroy a graphics base property
// View: The view to remove the property for
void _VIW_DestroyPropertyGraphicsBase(VIW_View *View);

// Run the graphics base property (Draw the graphics)
// Returns true on success and false on error
// View: The view to draw the graphics for
bool _VIW_RunPropertyGraphicsBase(VIW_View *View);

// Update the graphics base property
// Returns true on success and false on error
// View: The base view to update
bool _VIW_UpdatePropertyGraphicsBase(VIW_View *View);

// Create a graphics base property
// Returns true on success and false on error
// View: The view to add the graphics for
bool VIW_CreatePropertyGraphics(VIW_View *View);

// Destroy a graphics base property
// View: The view to remove the property for
void _VIW_DestroyPropertyGraphics(VIW_View *View);

// Run the graphics base property (Draw the graphics)
// Returns true on success and false on error
// View: The view to draw the graphics for
bool _VIW_RunPropertyGraphics(VIW_View *View);

// Update the graphics base property
// Returns true on success and false on error
// View: The base view to update
bool _VIW_UpdatePropertyGraphics(VIW_View *View);

// Activates the canvas for a graphics view
// Returns true on success and false on error
// View: The view to activate the canvas for
bool VIW_ActivateCanvas(VIW_View *View);

// Deactivates the canvas for a graphics view
// Returns true on success and false on error
// View: The view to deactivate the canvas for
bool VIW_DeactivateCanvas(VIW_View *View);

// Add graphics to a base list

// Remove graphics from a base list

// Update the prosition on a base list

// Struct initialisers

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructColour32(VIW_Colour32 *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructPropertyGraphics(VIW_PropertyGraphics *Struct);

// Initializes the structure
// Returns nothing
// Struct: The structure to initialize
void _VIW_InitStructPropertyGraphicsBase(VIW_PropertyGraphicsBase *Struct);

#endif // VIEWS_GRAPHICS_DEFINITIONS_FUNCTIONS