#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "Views.h"

int main(int argc, char **argv)
{
    
    // Take care of SDL
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Unable to initialise SDL: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *Window = SDL_CreateWindow("Testing view structure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);

    if (Window == NULL)
    {
        printf("Unable to create window: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (Renderer == NULL)
    {
        printf("Unable to create renderer: %s\n", SDL_GetError());
        return 0;
    }

    // Create the root
    VIW_View *Root = VIW_CreateRoot(Window, Renderer);

    if (Root == NULL)
    {
        printf("Unable to create root: %s\n", VIW_GetError());
        return 0;
    }

    // Origin, Anchor Error
    VIW_View *AnchorError = VIW_CreateView(Root);

    if (AnchorError == NULL)
    {
        printf("Unable to create AnchorError: %s\n", VIW_GetError());
        return 0;
    }

    if (!VIW_UseAdvancedShapeData(AnchorError))
    {
        printf("Unable to use advanced shape data: %s\n", VIW_GetError());
        return 0;
    }

    AnchorError->shapeData.type = VIW_ID_SHAPE_ADVANCED;

    // Origin, Pos Error

    // Origin, Size Error

    // Origin, Neg, Rigid Pos, Rigid Size

    // Origin, Center, Pointer Pos, Pointer Size

    // Origin, Pos, Single Pos, Single Size

    // Origin, Center, Bias Pos, Bias Size

    // Stretch, Single Pos, Single Pos

    // Copy shape

    printf("Finished without errors\n");

    VIW_Quit();
    SDL_Quit();
}