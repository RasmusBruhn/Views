#ifndef VIEWS_H_INCLUDED
#define VIEWS_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <SDL2/SDL.h>
#include <Objects.h>

// Errors
#include "_views_core_definitions_error.h"
#include "_views_graphics_definitions_error.h"

// ID
#include "_views_core_definitions_id.h"
#include "_views_graphics_definitions_id.h"

// Structs
#include "_views_core_definitions_structs.h"
#include "_views_graphics_definitions_structs.h"

// Function definitions
#include "_views_core_definitions_functions.h"
#include "_views_graphics_definitions_functions.h"

// Global variables
#include "_views_core_globalvariables.h"
#include "_views_graphics_globalvariables.h"

// Macros
#include "_views_core_functions_macros.h"
#include "_views_graphics_functions_macros.h"

// Struct initialisation
#include "_views_core_functions_structs_init.h"
#include "_views_graphics_functions_structs_init.h"

// Functions
#include "_views_core_functions_shape.h"
#include "_views_core_functions_initclean.h"
#include "_views_graphics_functions_initclean.h"
#include "_views_graphics_functions_functions.h"

#endif // VIEWS_H_INCLUDED