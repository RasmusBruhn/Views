#ifndef VIEWS_GRAPHICS_DEFINITIONS_ERROR
#define VIEWS_GRAPHICS_DEFINITIONS_ERROR

enum _VIW_Graphics_ID_ErrorID
{
    _VIW_ID_ERRORID_CREATECANVAS_CANVAS = 0x201010200,
    _VIW_ID_ERRORID_DESTROYCANVAS_INIT = 0x201020100,
    _VIW_ID_ERRORID_CREATEPROPERTYGRAPHICS_MALLOC = 0x201030200
};

// Error strings
// Type errors
#define _VIW_STRING_ERROR_TYPE "Wrong type (%u)"

// Initialisation errors
#define _VIW_STRING_ERROR_ALREADYINIT "Struct has already been initialised"
#define _VIW_STRING_ERROR_NOTINIT "Struct has not been initialised"
#define _VIW_STRING_ERROR_TEXTURE "Unable to create texture"


#endif // VIEWS_GRAPHICS_DEFINITIONS_ERROR