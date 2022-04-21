#ifndef VIEWS_CORE_GLOBALVARIABLES_H_INCLUDED
#define VIEWS_CORE_GLOBALVARIABLES_H_INCLUDED

#include "Views.h"

// List of all the roots
static VIW_ViewList _VIW_RootList = {.count = 0, .list = NULL};

// List of all functions for initialising the base property, they all must have the form [VIW_View *Func(VIW_View *BaseView)]
VIW_View *(*_VIW_BaseFuncList[])(VIW_View *BaseView) = {&VIW_CreateGraphicsBaseView};
size_t _VIW_BaseFuncCount = 1;

#endif // VIEWS_CORE_GLOBALVARIABLES_H_INCLUDED