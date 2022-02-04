#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "Views.h"

int main(int argc, char **argv)
{
    // Attempt to quit without opening anything
    VIW_Quit();

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

    // Create another root
    VIW_View *Root2 = VIW_CreateRoot(Window, Renderer);

    if (Root2 == NULL)
    {
        printf("Unable to create root: %s\n", VIW_GetError());
        return 0;
    }

    // Check root list
    extern VIW_ViewList _VIW_RootList;
    
    printf("Checking root list:\n");
    
    printf("Found %u entries, expected 2\n", _VIW_RootList.count);
    if (_VIW_RootList.count != 2)
        return 0;

    printf("First root is %p, expected %p\n", _VIW_RootList.list[0], Root);
    if (_VIW_RootList.list[0] != Root)
        return 0;

    printf("First root is %p, expected %p\n", _VIW_RootList.list[1], Root2);
    if (_VIW_RootList.list[1] != Root2)
        return 0;

    printf("\n");

    // Check root structure
    printf("Checking root structure:\n");

    printf(".flags = {.active = %u}, expected {.active = 1}", Root->flags.active);
    if (Root->flags.active != true)
        return 0;

    printf("._flags");

    // Create a child

    // Create a child in front

    // Create a child in back

    // Create a child in middle

    // Create a child of a child

    // Clean up
    VIW_Quit();
    SDL_Quit();

    // Cheking root list again
    printf("Checking root list after quit:\n");

    printf("Found %u entries, expected 0\n", _VIW_RootList.count);
    if (_VIW_RootList.count != 0)
        return 0;

    printf("List pointer is %p, expected %p\n", _VIW_RootList.list, NULL);
    if (_VIW_RootList.list != NULL)
        return 0;

    printf("\n");

    printf("Finished without errors\n");

    return 0;
}