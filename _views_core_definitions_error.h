#ifndef VIEWS_STANDARD_DEFINITIONS_ERROR_H_INCLUDED
#define VIEWS_STANDARD_DEFINITIONS_ERROR_H_INCLUDED

#include "Views.h"

#define ERR_PREFIX VIW
#define ERR_MAXLENGTH 10000

#ifndef VIW_MAXARCHIVED
#define VIW_MAXARCHIVED 10
#endif

#define ERR_MAXARCHIVED VIW_MAXARCHIVED

#include "Error.h"


// Error type
enum VIW_ID_ErrorType
{
    VIW_ID_ERRORTYPE_NONE = 0,
    VIW_ID_ERRORTYPE_WARNING = 1,
    VIW_ID_ERRORTYPE_ERROR = 2,
    VIW_ID_ERRORTYPE_FATAL = 3
};

// Error id
enum _VIW_Core_ID_ErrorID
{
    _VIW_ID_ERRORID_GENERAL_NONE = 0x200000000,
    _VIW_ID_ERRORID_UPDATESHAPEADVANCED_X = 0x200010200,
    _VIW_ID_ERRORID_UPDATESHAPEADVANCED_Y = 0x200010201,
    _VIW_ID_ERRORID_UPDATESHAPEADVANCED_DATA = 0x200010202,
    _VIW_ID_ERRORID_UPDATESHAPECOORD_TYPE = 0x200020200,
    _VIW_ID_ERRORID_UPDATESHAPECOORD_STRETCH = 0x200020201,
    _VIW_ID_ERRORID_UPDATESHAPECOORD_ORIGIN = 0x200020202,
    _VIW_ID_ERRORID_UPDATESHAPECOORD_TYPENONE = 0x200020203,
    _VIW_ID_ERRORID_GETANCHORPOINT_ANCHORTYPE = 0x200030200,
    _VIW_ID_ERRORID_GETANCHORPOINT_TYPENONE = 0x200030201,
    _VIW_ID_ERRORID_GETANCHORPOINT_REF = 0x200030201,
    _VIW_ID_ERRORID_GETBIASANCHORPOINT_ANCHOR = 0x200040200,
    _VIW_ID_ERRORID_GETPOS_TYPE = 0x200050200,
    _VIW_ID_ERRORID_GETPOS_POINTER = 0x200050201,
    _VIW_ID_ERRORID_GETPOS_POINTERABS = 0x200050202,
    _VIW_ID_ERRORID_GETPOS_SINGLEANCHOR = 0x200050203,
    _VIW_ID_ERRORID_GETPOS_BIASANCHOR = 0x200050204,
    _VIW_ID_ERRORID_GETPOS_NONE = 0x200050205,
    _VIW_ID_ERRORID_GETSIZEDIFF_POS = 0x200060200,
    _VIW_ID_ERRORID_FINDREFVIEW_TYPE = 0x200070200,
    _VIW_ID_ERRORID_FINDREFVIEW_FIRSTCHILD = 0x200070201,
    _VIW_ID_ERRORID_FINDREFVIEW_NONE = 0x200070202,
    _VIW_ID_ERRORID_GETSIZECOPY_REF = 0x200080200,
    _VIW_ID_ERRORID_GETSIZECOPY_TYPE = 0x200080201,
    _VIW_ID_ERRORID_GETSIZE_TYPE = 0x200090200,
    _VIW_ID_ERRORID_GETSIZE_POINTER = 0x200090201,
    _VIW_ID_ERRORID_GETSIZE_DIFF = 0x200090202,
    _VIW_ID_ERRORID_GETSIZE_COPY = 0x200090203,
    _VIW_ID_ERRORID_GETSIZE_TYPENONE = 0x200090204,
    _VIW_ID_ERRORID_UPDATESHAPECOORDORIGIN_POS = 0x2000A0200,
    _VIW_ID_ERRORID_UPDATESHAPECOORDORIGIN_TYPE = 0x2000A0201,
    _VIW_ID_ERRORID_UPDATESHAPECOORDORIGIN_SIZE = 0x2000A0202,
    _VIW_ID_ERRORID_UPDATESHAPECOORDSTRETCH_POS = 0x2000B0200,
    _VIW_ID_ERRORID_ADDTOVIEWLIST_LIST = 0x2000C0200,
    _VIW_ID_ERRORID_REMOVEFROMVIEWLIST_WARNING = 0x2000D0100,
    _VIW_ID_ERRORID_REMOVEFROMVIEWLIST_ERROR = 0x2000D0201,
    _VIW_ID_ERRORID_CREATEROOT_MALLOC = 0x2000E0200,
    _VIW_ID_ERRORID_CREATEROOT_LIST = 0x2000E0201,
    _VIW_ID_ERRORID_CREATEROOT_PROPERTY = 0x2000E0202,
    _VIW_ID_ERRORID_CREATEROOT_WINDOWID = 0x2000E0203,
    _VIW_ID_ERRORID_UPDATESHAPE_CHILD = 0x2000F0200,
    _VIW_ID_ERRORID_UPDATESHAPE_TYPE = 0x2000F0201,
    _VIW_ID_ERRORID_UPDATESHAPE_PROPERTY = 0x2000F0202,
    _VIW_ID_ERRORID_UPDATESHAPE_SIBLING = 0x2000F0203,
    _VIW_ID_ERRORID_UPDATESHAPE_NEXTSIBLING = 0x2000F0204,
    _VIW_ID_ERRORID_UPDATESHAPE_WINDOW = 0x2000F0205,
    _VIW_ID_ERRORID_UPDATESHAPE_COPY = 0x2000F0206,
    _VIW_ID_ERRORID_UPDATESHAPE_ADVANCED = 0x2000F0207,
    _VIW_ID_ERRORID_UPDATESHAPE_TYPENONE = 0x2000F0208,
    _VIW_ID_ERRORID_CREATEPROPERTYBASE_MALLOC = 0x200100200,
    _VIW_ID_ERRORID_CREATEPROPERTYBASE_MALLOCLIST = 0x200100201,
    _VIW_ID_ERRORID_CREATEPROPERTYBASE_NEXTBASE = 0x200100202,
    _VIW_ID_ERRORID_CREATEPROPERTYBASE_MALLOCNEW = 0x200100203,
    _VIW_ID_ERRORID_CREATEVIEW_MALLOC = 0x200110200,
    _VIW_ID_ERRORID_CREATEVIEW_CHILDLIST = 0x200110201,
    _VIW_ID_ERRORID_ADDREF_REFNOTFOUND = 0x200120200,
    _VIW_ID_ERRORID_ADDREF_TYPE = 0x200120201,
    _VIW_ID_ERRORID_ADDREF_FIRSTCHILD = 0x200120202,
    _VIW_ID_ERRORID_USEADVANCEDSHAPEDATA_MALLOC = 0x200130200,
    _VIW_ID_ERRORID_USEADVANCEDSHAPEDATA_INIT = 0x200130101,
    _VIW_ID_ERRORID_UPDATESHAPECOPY_REF = 0x200140200,
    _VIW_ID_ERRORID_ADDTOLIST_POS = 0x200150200,
    _VIW_ID_ERRORID_ADDTOLIST_REALLOC = 0x200150301,
    _VIW_ID_ERRORID_REMOVEFROMLIST_LOCATE = 0x200160100,
    _VIW_ID_ERRORID_REMOVEFROMLIST_REALLOC = 0x200160301,
    _VIW_ID_ERRORID_CREATEBASEVIEW_VIEW = 0x200170200,
    _VIW_ID_ERRORID_CREATEBASEVIEW_PROPERTY = 0x200170201,
    _VIW_ID_ERRORID_CREATEBASEVIEW_ORDERSCRIPT = 0x200170202,
    _VIW_ID_ERRORID_CREATESUBVIEW_VIEW = 0x200180201,
    _VIW_ID_ERRORID_DESTROYVIEW_REMOVEFROMLIST = 0x200190100,
    _VIW_ID_ERRORID_UPDATEACTIVE_PROPERTY = 0x2001A0200,
    _VIW_ID_ERRORID_UPDATEACTIVE_CHILD = 0x2001A0201,
    _VIW_ID_ERRORID_CHANGEACTIVESET_UPDATE = 0x2001B0200,
    _VIW_ID_ERRORID_CHANGEACTIVE_UPDATE = 0x2001C0200,
    _VIW_ID_ERRORID_ADDTOBASELIST_ADD = 0x2001D0200,
    _VIW_ID_ERRORID_REMOVEFROMBASELIST = 0x2001E0200,
    _VIW_ID_ERRORID_UPDATEONBASELIST_EXIST = 0x2001F0200
};

// Error messages
// Type errors
#define _VIW_STRING_ERROR_TYPENONE "The type was \"None\""
#define _VIW_STRING_ERROR_UNKNOWNTYPE "Unknown type (%u)"
#define _VIW_STRING_ERROR_NOBASE "Neither the selected view or it's child has a \"Base\" property"

// Update errors
#define _VIW_STRING_ERROR_UPDATESHAPEWINDOW "Unable to update shape using window size"
#define _VIW_STRING_ERROR_UPDATESHAPECOPY "Unable to update shape by copying another shape"
#define _VIW_STRING_ERROR_UPDATESHAPEADVANCED "Unable to update shape using shape data"
#define _VIW_STRING_ERROR_UPDATEPROPERTY "Unable to update property"
#define _VIW_STRING_ERROR_UPDATECHILD "Unable to update child"
#define _VIW_STRING_ERROR_UPDATESIBLING "Unable to update siblings"
#define _VIW_STRING_ERROR_UPDATENEXTSIBLING "Unable to update next sibling"
#define _VIW_STRING_ERROR_UPDATEX "Unable not update x"
#define _VIW_STRING_ERROR_UPDATEY "Unable not update y"
#define _VIW_STRING_ERROR_SETSHAPESTRETCH "Unable to set shape using \"Stretch\" method"
#define _VIW_STRING_ERROR_SETSHAPEORIGIN "Unable to set shape using \"Origin\" method"
#define _VIW_STRING_ERROR_UPDATETIME "Unable to update time"
#define _VIW_STRING_ERROR_UPDATEACTIVE "Unable to update the total active status"

// Window errors
#define _VIW_ID_STRING_WINDOWID "Unable to get the window ID"

// Pointer/reference errors
#define _VIW_STRING_ERROR_NOREF "Unable to find reference view"
#define _VIW_STRING_ERROR_SHAPEDATA "No shape data is available"
#define _VIW_STRING_ERROR_NOPOINTER "No pointer has not been specified"

// Calculation error
#define _VIW_STRING_ERROR_CALCPOS "Unable to calculate the position"
#define _VIW_STRING_ERROR_CALCSIZE "Unable to calculate the size"
#define _VIW_STRING_ERROR_ANCHORERROR "The anchor point could not be found"

// Invalid errors
#define _VIW_STRING_ERROR_FIRSTCHILD "Reference to earlier sibling is invalid because this is the first child"
#define _VIW_STRING_ERROR_DATAINITIALIZED "Data is already initialized"
#define _VIW_STRING_ERROR_NOTEXISTINLIST "This element does not exist in the specified list"

// Create error
#define _VIW_STRING_ERROR_MALLOC "Unable to allocate memory"
#define _VIW_STRING_ERROR_REALLOC "Unable to reallocate memory"
#define _VIW_STRING_ERROR_MALLOCCOUNT "Unable to allocate memory for element %lu"
#define _VIW_STRING_ERROR_CREATEVIEW "Unable to create view"
#define _VIW_STRING_ERROR_CREATEBASE "Unable to create \"Base\" view"

// Perform error
#define _VIW_STRING_ERROR_ADDPROPERTY "Unable to add property"
#define _VIW_STRING_ERROR_ADDBASEPROPERTY "Unable to add \"Base\" property"
#define _VIW_STRING_ERROR_ADDROOTLIST "Unable to add root to list of roots"
#define _VIW_STRING_ERROR_ADDCHILDLIST "Unable to add view to child list"

#define _VIW_STRING_ERROR_LOCATEOBJECT "Unable to locate object"
#define _VIW_STRING_ERROR_UPDATESHAPE "Unable to update shape"
#define _VIW_STRING_ERROR_REMOVEROOTLIST "Unable to remove root from list of roots"
#define _VIW_STRING_ERROR_RANGE "The specified value is outside its allowed range"
#define _VIW_STRING_ERROR_DESTROYCHILD "Unable to destroy child"
#define _VIW_STRING_ERROR_REMOVECHILDLIST "Unable to remove from child list"
#define _VIW_STRING_ERROR_DESTROYVIEW "Unable to destroy view"
#define _VIW_STRING_ERROR_ILLIGALREF "This reference is not legal"
#define _VIW_STRING_ERROR_NULLFUNCTION "The function is NULL and cannot be used"
#define _VIW_STRING_ERROR_SCRIPT "Error when running script"
#define _VIW_STRING_ERROR_NEXTBASE "There were no direct ancestor with a \"base\" property"
#define _VIW_STRING_ERROR_ADDTOLIST "Unable to add object to list"
#define _VIW_STRING_ERROR_REMOVEFROMLIST "Unable to remove element from list"
#define _VIW_STRING_ERROR_SORTLIST "Unable to sort list"
#define _VIW_STRING_ERROR_NOSCRIPT "No script is defined"
#define _VIW_STRING_ERROR_ROOTNEXTBASE "A root has no next base"

#endif