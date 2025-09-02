/**
* File: patchugo_lite.cpp
* Created on: 2025-09-01 at 21:36
* Author: Andrea Rantin
* Description: Implementation file for patchugo_lite.h
*/

#include "patchugo_lite.h"

PatchugoStatusCode PatchugoLite::Init(void) {
    ioManager.Init();

    //Initialize bluetooth management part of the library
    PatchugoStatusCode checkError = btManager.Init();
    if(checkError != OK) return checkError;

    return OK;
}