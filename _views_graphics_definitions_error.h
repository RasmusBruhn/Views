#ifndef VIEWS_GRAPHICS_DEFINITIONS_ERROR
#define VIEWS_GRAPHICS_DEFINITIONS_ERROR

enum _VIW_Graphics_ID_ErrorID
{
    _VIW_ID_ERRORID_CREATECANVAS_CANVAS = 0x201010200,
    _VIW_ID_ERRORID_DESTROYCANVAS_INIT = 0x201020100,
    _VIW_ID_ERRORID_CREATEPROPERTYGRAPHICS_MALLOC = 0x201030200,
    _VIW_ID_ERRORID_CREATEPROPERTYGRAPHICS_BASLIST = 0x201030201,
    _VIW_ID_ERRORID_DESTROYPROPERTYGRAPHICS_LIST = 0x201040300,
    _VIW_ID_ERRORID_RUNPROPERTYGRAPHICS_COPY = 0x201050200,
    _VIW_ID_ERRORID_RUNPROPERTYGRAPHICS_RUNEXIST = 0x201050101,
    _VIW_ID_ERRORID_RUNPROPERTYGRAPHICS_RUN = 0x201050202,
    _VIW_ID_ERRORID_ACTIVATECANVAS_UPDATE = 0x201060200,
    _VIW_ID_ERRORID_ACTIVATECANVAS_UPDATEFUNC = 0x201060201,
    _VIW_ID_ERRORID_DEACTIVATECANVAS_UPDATE = 0x201070200,
    _VIW_ID_ERRORID_DEACTIVATECANVAS_UPDATEFUNC = 0x201070201,
    _VIW_ID_ERRORID_DEACTIVATECANVAS_BASE = 0x201070202,
    _VIW_ID_ERRORID_UPDATEPROPERTYGRAPHICS_CREATECANVAS = 0x201080200,
    _VIW_ID_ERRORID_UPDATEPROPERTYGRAPHICS_RENDERTARGET = 0x201080201,
    _VIW_ID_ERRORID_UPDATEPROPERTYGRAPHICS_DRAW = 0x201080202,
    _VIW_ID_ERRORID_UPDATEPROPERTYGRAPHICS_RENDERCOLOUR = 0x201080203,
    _VIW_ID_ERRORID_UPDATEPROPERTYGRAPHICS_RENDERFILL = 0x201080204,
    _VIW_ID_ERRORID_CREATEPROPERTYGRAPHICSBASE_EXISTS = 0x201090200,
    _VIW_ID_ERRORID_CREATEPROPERTYGRAPHICSBASE_CHILDREN = 0x201090101,
    _VIW_ID_ERRORID_CREATEPROPERTYGRAPHICSBASE_MEMORY = 0x201090202,
    _VIW_ID_ERRORID_CREATEPROPERTYGRAPHICSBASE_SUPER = 0x201090203,
    _VIW_ID_ERRORID_REATEPROPERTYGRAPHISBASE_CANVAS = 0x201090204,
    _VIW_ID_ERRORID_CREATEGRAPHICSBASEVIEW_VIEW = 0x2010A0200,
    _VIW_ID_ERRORID_CREATEGRAPHICSBASEVIEW_PROPERTY = 0x2010A0201,
    _VIW_ID_ERRORID_RUNPROPERTYGRAPHICSBASE_VIEWPORT = 0x2010B0200,
    _VIW_ID_ERRORID_RUNPROPERTYGRAPHICSBASE_RENDER = 0x2010B0201
};

// Error strings
// Type errors
#define _VIW_STRING_ERROR_TYPE "Wrong type (%u)"

// Initialisation errors
#define _VIW_STRING_ERROR_ALREADYINIT "Struct has already been initialised"
#define _VIW_STRING_ERROR_NOTINIT "Struct has not been initialised"
#define _VIW_STRING_ERROR_TEXTURE "Unable to create texture"

// Create errors
#define _VIW_STRING_ERROR_CREATECANVAS "Unable to create canvas"
#define _VIW_STRING_ERROR_CREATESUPER "Unable to reate super property"

// Render errors
#define _VIW_STRING_ERROR_COPYTEXTURE "Unable to copy texture onto renderer"
#define _VIW_STRING_ERROR_RENDER "Unable to render view"
#define _VIW_STRING_ERROR_RENDERTARGET "Unable to set render target"
#define _VIW_STRING_ERROR_SETVIEWPORT "Unable to set viewport"
#define _VIW_STRING_ERROR_RENDERCOLOUR "Unable to set render draw colour"
#define _VIW_STRING_ERROR_RENDERFILL "Unable to fill rectangle"

// Invalid errors
#define _VIW_STRING_ERROR_BASECANVAS "A base view must have a canvas"

#endif // VIEWS_GRAPHICS_DEFINITIONS_ERROR