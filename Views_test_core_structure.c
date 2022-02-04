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

    printf(".flags = {.active = %u}, expected {.active = 1}\n", Root->flags.active);
    if (Root->flags.active != true)
        return 0;

    printf("._flags = {.active = %u, .totalActive = %u, .updateNextSibling = %u, .updateAllSiblings = %u}, expected {.active = 1, .totalActive = 1, .updateNextSibling = 0, .updateAllSiblings = 0}\n", Root->_flags.active, Root->_flags.totalActive, Root->_flags.updateNextSibling, Root->_flags.updateAllSiblings);
    if (Root->_flags.active != true || Root->_flags.totalActive != true || Root->_flags.updateNextSibling != false || Root->_flags.updateAllSiblings != false)
        return 0;

    printf("._window = {.window = %p, .renderer = %p, .ID = %u}, expected {.window = %p, .renderer = %p, .ID = %u}\n", Root->_window.window, Root->_window.renderer, Root->_window.ID, Window, Renderer, SDL_GetWindowID(Window));
    if (Root->_window.window != Window || Root->_window.renderer != Renderer || Root->_window.ID != SDL_GetWindowID(Window))
        return 0;

    printf("._parent = {.root = %p, .parent = %p}, expected {.root = %p, .parent = %p}\n", Root->_parent.root, Root->_parent.parent, Root, NULL);
    if (Root->_parent.root != Root || Root->_parent.parent != NULL)
        return 0;

    printf("._child = {.list = %p, .count = %u}, expected {.list = %p, .count = %u}\n", Root->_child.list.list, Root->_child.list.count, NULL, 0);
    if (Root->_child.list.list != NULL || Root->_child.list.count != 0)
        return 0;

    printf(".shapeData = {.type = %u}, expected {.type = %u}\n", Root->shapeData.type, VIW_ID_SHAPE_WINDOW);
    if (Root->shapeData.type != VIW_ID_SHAPE_WINDOW)
        return 0;

    printf(".property = {._type = %u, ._runType = %u, ._updateFunc = %p, ._runFunc = %p, ._destroyFunc = %p, ._nextBase = %p, .data._list.count = %u, .data._list.list = %p}, expected {._type = %u, ._runType = %u, ._updateFunc = %p, ._runFunc = %p, ._destroyFunc = %p, ._nextBase = %p, .data._list.count = %u, .data._list.list = %p}\n", Root->property._type, Root->property._runType, Root->property._updateFunc, Root->property._runFunc, Root->property._destroyFunc, Root->property._nextBase, ((VIW_PropertyBase *)Root->property.data)->_list.count, ((VIW_PropertyBase *)Root->property.data)->_list.list, _VIW_ID_PROPERTY_BASE, _VIW_ID_PROPERTY_NONE, NULL, NULL, &_VIW_DestroyPropertyBase, NULL, 0, NULL);
    if (Root->property._type != _VIW_ID_PROPERTY_BASE || Root->property._runType != _VIW_ID_PROPERTY_NONE || Root->property._updateFunc != NULL || Root->property._runFunc != NULL || Root->property._destroyFunc != &_VIW_DestroyPropertyBase || Root->property._nextBase != NULL || ((VIW_PropertyBase *)Root->property.data)->_list.count != 0 || ((VIW_PropertyBase *)Root->property.data)->_list.list != NULL)
        return 0;

    printf("\n");

    // Create a child
    VIW_View *Child = VIW_CreateView(Root);

    if (Child == NULL)
    {
        printf("Unable to create child: %s\n", VIW_GetError());
        return 0;
    }

    printf("Checking child data:\n");

    printf(".flags = {.active = %u}, expected {.active = %u}\n", Child->flags.active, true);
    if (Child->flags.active != true)
        return 0;

    printf("._flags = {.active = %u, .totalActive = %u, .updateNextSibling = %u, .updateAllSiblings = %u}, expected {.active = 1, .totalActive = 1, .updateNextSibling = 0, .updateAllSiblings = 0}\n", Child->_flags.active, Child->_flags.totalActive, Child->_flags.updateNextSibling, Child->_flags.updateAllSiblings);
    if (Child->_flags.active != true || Child->_flags.totalActive != true || Child->_flags.updateNextSibling != false || Child->_flags.updateAllSiblings != false)
        return 0;

    printf("._window = {.window = %p, .renderer = %p, .ID = %u}, expected {.window = %p, .renderer = %p, .ID = %u}\n", Child->_window.window, Child->_window.renderer, Child->_window.ID, Window, Renderer, SDL_GetWindowID(Window));
    if (Child->_window.window != Window || Child->_window.renderer != Renderer || Child->_window.ID != SDL_GetWindowID(Window))
        return 0;

    printf("._parent = {.Child = %p, .parent = %p}, expected {.Child = %p, .parent = %p}\n", Child->_parent.root, Child->_parent.parent, Root, Root);
    if (Child->_parent.root != Root || Child->_parent.parent != Root)
        return 0;

    printf("._child = {.list = %p, .count = %u}, expected {.list = %p, .count = %u}\n", Child->_child.list.list, Child->_child.list.count, NULL, 0);
    if (Child->_child.list.list != NULL || Child->_child.list.count != 0)
        return 0;

    printf(".shapeData = {.type = %u}, expected {.type = %u}\n", Child->shapeData.type, VIW_ID_SHAPE_NONE);
    if (Child->shapeData.type != VIW_ID_SHAPE_NONE)
        return 0;

    printf(".property = {._type = %u, ._runType = %u, ._updateFunc = %p, ._runFunc = %p, ._destroyFunc = %p, ._nextBase = %p, .order = %d, .data = %p}, expected {._type = %u, ._runType = %u, ._updateFunc = %p, ._runFunc = %p, ._destroyFunc = %p, ._nextBase = %p, .order = %u, .data = %p}\n", Child->property._type, Child->property._runType, Child->property._updateFunc, Child->property._runFunc, Child->property._destroyFunc, Child->property._nextBase, Child->property.order, Child->property.data, _VIW_ID_PROPERTY_NONE, _VIW_ID_PROPERTY_NONE, NULL, NULL, NULL, Root, 0, NULL);
    if (Child->property._type != _VIW_ID_PROPERTY_NONE || Child->property._runType != _VIW_ID_PROPERTY_NONE || Child->property._updateFunc != NULL || Child->property._runFunc != NULL || Child->property._destroyFunc != NULL || Child->property._nextBase != Root || Child->property.order != 0 || Child->property.data != NULL)
        return 0;

    printf("\n");

    // Use advanced shape
    if (!VIW_UseAdvancedShapeData(Child))
    {
        printf("Unable to use advanced shape on data: %s\n", VIW_GetError());
        return 0;
    }

    printf("Checking that shape data is good:\n");

    printf(".shapeData = {.type = %u}, expected {.type = %u}\n", Child->shapeData.type, VIW_ID_SHAPE_ADVANCED);
    if (Child->shapeData.type != VIW_ID_SHAPE_ADVANCED)
        return 0;

    printf("\n");

    // Create a child in front
    VIW_View *FrontChild = VIW_CreateViewWithPos(Root, 0);

    if (FrontChild == NULL)
    {
        printf("Unable to create FrontChild: %s\n", VIW_GetError());
        return 0;
    }
    
    // Add a reference to the previous child
    if (!VIW_AddRef(Child, &Child->shapeData.data.data->x.data.origin.pos.data.single.ref, VIW_ID_RELATION_SIBLING, 0))
    {
        printf("Unable to add a reference: %s\n", VIW_GetError());
        return 0;
    }

    printf("Checking the reference to earlier sibling and the _flags for the sibling:\n");

    printf("._flags = {.active = %u, .totalActive = %u, .updateNextSibling = %u, .updateAllSiblings = %u}, expected {.active = 1, .totalActive = 1, .updateNextSibling = 1, .updateAllSiblings = 0}\n", FrontChild->_flags.active, FrontChild->_flags.totalActive, FrontChild->_flags.updateNextSibling, FrontChild->_flags.updateAllSiblings);
    if (FrontChild->_flags.active != true || FrontChild->_flags.totalActive != true || FrontChild->_flags.updateNextSibling != true || FrontChild->_flags.updateAllSiblings != false)
        return 0;

    printf("Reference is [.view = %u, .ref = %p], expected [.view = %u, .ref = %p]\n", Child->shapeData.data.data->x.data.origin.pos.data.single.ref.view, Child->shapeData.data.data->x.data.origin.pos.data.single.ref.ref, VIW_ID_RELATION_SIBLING, NULL);
    if (Child->shapeData.data.data->x.data.origin.pos.data.single.ref.view != VIW_ID_RELATION_SIBLING || Child->shapeData.data.data->x.data.origin.pos.data.single.ref.ref != NULL)
        return 0;

    printf("\n");

    // Create a child in back
    VIW_View *BackChild = VIW_CreateView(Root);

    if (BackChild == NULL)
    {
        printf("Unable to create BackChild: %s\n", VIW_GetError());
        return 0;
    }

    // Check child pos and child list

    // Create a child in middle
    VIW_View *MiddleChild = VIW_CreateViewWithPos(Root, 1);

    if (MiddleChild == NULL)
    {
        printf("Unable to create MiddleChild: %s\n", VIW_GetError());
        return 0;
    }

    printf("Checking that flag carried on:\n");

    printf("._flags = {.active = %u, .totalActive = %u, .updateNextSibling = %u, .updateAllSiblings = %u}, expected {.active = 1, .totalActive = 1, .updateNextSibling = 1, .updateAllSiblings = 0}\n", MiddleChild->_flags.active, MiddleChild->_flags.totalActive, MiddleChild->_flags.updateNextSibling, MiddleChild->_flags.updateAllSiblings);
    if (MiddleChild->_flags.active != true || MiddleChild->_flags.totalActive != true || MiddleChild->_flags.updateNextSibling != true || MiddleChild->_flags.updateAllSiblings != false)
        return 0;

    printf("._flags for FrontChild = {.active = %u, .totalActive = %u, .updateNextSibling = %u, .updateAllSiblings = %u}, expected {.active = 1, .totalActive = 1, .updateNextSibling = 0, .updateAllSiblings = 0}\n", FrontChild->_flags.active, FrontChild->_flags.totalActive, FrontChild->_flags.updateNextSibling, FrontChild->_flags.updateAllSiblings);
    if (FrontChild->_flags.active != true || FrontChild->_flags.totalActive != true || FrontChild->_flags.updateNextSibling != false || FrontChild->_flags.updateAllSiblings != false)
        return 0;

    printf("\n");

    // Check child list
    printf("Checking the child list of Root:\n");

    printf("Number of children: %u, expected %u\n", Root->_child.list.count, 4);
    if (Root->_child.list.count != 4)
        return 0;

    printf("The children are [%p, %p, %p, %p], expected [%p, %p, %p, %p]\n", Root->_child.list.list[0], Root->_child.list.list[1], Root->_child.list.list[2], Root->_child.list.list[3], FrontChild, MiddleChild, Child, BackChild);
    if (Root->_child.list.list[0] != FrontChild || Root->_child.list.list[1] != MiddleChild || Root->_child.list.list[2] != Child || Root->_child.list.list[3] != BackChild)
        return 0;

    printf("\n");

    // Check child pos
    printf("Checking the child pos of all children:\n");

    printf("Child pos is [%u, %u, %u, %u], expected [%u, %u, %u, %u]\n", FrontChild->_parent.childPos, MiddleChild->_parent.childPos, Child->_parent.childPos, BackChild->_parent.childPos, 0, 1, 2, 3);
    if (FrontChild->_parent.childPos != 0 || MiddleChild->_parent.childPos != 1 || Child->_parent.childPos != 2 || BackChild->_parent.childPos != 3)
        return 0;

    printf("\n");

    // Create a child of a child
    VIW_View *GrandChild = VIW_CreateBaseView(Child);

    if (GrandChild == NULL)
    {
        printf("Unable to create GrandChild: %s\n", VIW_GetError());
        return 0;
    }

    // Check parent

    // Disable view
    if (!VIW_DeactivateView(Child))
    {
        printf("Unable to deactivate Child: %s\n", VIW_GetError());
        return 0;
    }

    // Enable grand child
    if (!VIW_ActivateView(GrandChild))
    {
        printf("Unable to activate GrandChild: %s\n", VIW_GetError());
        return 0;
    }

    // Create disabled child
    VIW_View *DisabledChild = VIW_CreateSubView(GrandChild);

    if (DisabledChild == NULL)
    {
        printf("Unable to create DisabledChild: %s\n", VIW_GetError());
        return 0;
    }

    // Check disable and disable of children

    // Disable root
    if (!VIW_ToggleView(Root))
    {
        printf("Unable to toggle root: %s\n", VIW_GetError());
        return 0;
    }

    // Enable view
    if (!VIW_ToggleView(Child))
    {
        printf("Unable to toggle Child: %s\n", VIW_GetError());
        return 0;
    }

    // Check enable and enable of children

    // Enable root
    if (!VIW_ActivateView(Root))
    {
        printf("Unable to activate Root: %s\n", VIW_GetError());
        return 0;
    }

    // Check enable of children

    // Destroy child
    VIW_DestroyView(Child);

    // Check child list
    printf("Checking the child list of Root after removing Child:\n");

    printf("Number of children: %u, expected %u\n", Root->_child.list.count, 3);
    if (Root->_child.list.count != 3)
        return 0;

    printf("The children are [%p, %p, %p], expected [%p, %p, %p]\n", Root->_child.list.list[0], Root->_child.list.list[1], Root->_child.list.list[2], FrontChild, MiddleChild, BackChild);
    if (Root->_child.list.list[0] != FrontChild || Root->_child.list.list[1] != MiddleChild || Root->_child.list.list[2] != BackChild)
        return 0;

    printf("\n");

    // Destroy root
    VIW_DestroyRoot(Root);

    // Check root list
    printf("Checking root list after removing Root:\n");

    printf("Found %u entries, expected %u\n", _VIW_RootList.count, 1);
    if (_VIW_RootList.count != 1)
        return 0;

    printf("Remaining root is %p, expected %p\n", _VIW_RootList.list[0], Root2);
    if (_VIW_RootList.list[0] != Root2)
        return 0;

    printf("\n");

    // Print errors
    printf("Errors:\n");

    char *String = NULL;
    while ((String = VIW_GetArchivedError()) != NULL)
        printf("%s\n", String);

    printf("\n");

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