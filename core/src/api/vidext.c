/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-core - api/vidext.c                                       *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2009 Richard Goedeken                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       * 
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
                       
/* This file contains the Core video extension functions which will be exported
 * outside of the core library.
 */

#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include "m64p_types.h"
#include "callbacks.h"

/* local variables */
static m64p_video_extension_functions l_ExternalVideoFuncTable = {9, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
static int l_VideoExtensionActive = 0;
static int l_VideoOutputActive = 0;
static int l_Fullscreen = 0;
static SDL_Surface *l_pScreen = NULL;

/* global function for use by frontend.c */
m64p_error OverrideVideoFunctions(m64p_video_extension_functions *VideoFunctionStruct)
{
    /* check input data */
    if (VideoFunctionStruct == NULL)
        return M64ERR_INPUT_ASSERT;
    if (VideoFunctionStruct->Functions < 9)
        return M64ERR_INPUT_INVALID;

    /* disable video extension if any of the function pointers are NULL */
    if (VideoFunctionStruct->VidExtFuncInit == NULL ||
        VideoFunctionStruct->VidExtFuncQuit == NULL ||
        VideoFunctionStruct->VidExtFuncListModes == NULL ||
        VideoFunctionStruct->VidExtFuncSetMode == NULL ||
        VideoFunctionStruct->VidExtFuncGLGetProc == NULL ||
        VideoFunctionStruct->VidExtFuncGLSetAttr == NULL ||
        VideoFunctionStruct->VidExtFuncGLSwapBuf == NULL ||
        VideoFunctionStruct->VidExtFuncSetCaption == NULL ||
        VideoFunctionStruct->VidExtFuncToggleFS == NULL)
    {
        l_ExternalVideoFuncTable.Functions = 9;
        memset(&l_ExternalVideoFuncTable.VidExtFuncInit, 0, 9 * sizeof(void *));
        l_VideoExtensionActive = 0;
        return M64ERR_SUCCESS;
    }

    /* otherwise copy in the override function pointers */
    memcpy(&l_ExternalVideoFuncTable, VideoFunctionStruct, sizeof(m64p_video_extension_functions));
    l_VideoExtensionActive = 1;
    return M64ERR_SUCCESS;
}

int VidExt_InFullscreenMode(void)
{
    return l_Fullscreen;
}

int VidExt_VideoRunning(void)
{
    return l_VideoOutputActive;
}

/* video extension functions to be called by the video plugin */
EXPORT m64p_error CALL VidExt_Init(void)
{
    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
        return (*l_ExternalVideoFuncTable.VidExtFuncInit)();

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == -1)
    {
        DebugMessage(M64MSG_ERROR, "SDL video subsystem init failed: %s", SDL_GetError());
        return M64ERR_SYSTEM_FAIL;
    }

    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_Quit(void)
{
    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
    {
        m64p_error rval = (*l_ExternalVideoFuncTable.VidExtFuncQuit)();
        if (rval == M64ERR_SUCCESS)
        {
            l_VideoOutputActive = 0;
            StateChanged(M64CORE_VIDEO_MODE, M64VIDEO_NONE);
        }
        return rval;
    }

    SDL_ShowCursor(SDL_ENABLE);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    l_pScreen = NULL;
    l_VideoOutputActive = 0;
    StateChanged(M64CORE_VIDEO_MODE, M64VIDEO_NONE);

    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_ListFullscreenModes(m64p_2d_size *SizeArray, int *NumSizes)
{
    const SDL_VideoInfo *videoInfo;

    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
        return (*l_ExternalVideoFuncTable.VidExtFuncListModes)(SizeArray, NumSizes);

    /* get a list of SDL video modes */
    unsigned int videoFlags = SDL_OPENGL | SDL_FULLSCREEN;

    if ((videoInfo = SDL_GetVideoInfo()) == NULL)
    {
        DebugMessage(M64MSG_ERROR, "SDL_GetVideoInfo query failed: %s", SDL_GetError());
        return M64ERR_SYSTEM_FAIL;
    }

    if(videoInfo->hw_available)
        videoFlags |= SDL_HWSURFACE;
    else
        videoFlags |= SDL_SWSURFACE;

    SDL_Rect **modes;
    modes = SDL_ListModes(NULL, videoFlags);

    if (modes == (SDL_Rect **) 0 || modes == (SDL_Rect **) -1)
    {
        DebugMessage(M64MSG_WARNING, "No fullscreen SDL video modes available");
        *NumSizes = 0;
        return M64ERR_SUCCESS;
    }

    int i = 0;
    while (i < *NumSizes && modes[i] != NULL)
    {
        SizeArray[i].uiWidth  = modes[i]->w;
        SizeArray[i].uiHeight = modes[i]->h;
        i++;
    }

    *NumSizes = i;

    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_SetVideoMode(int Width, int Height, int BitsPerPixel, m64p_video_mode ScreenMode)
{
    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
    {
        m64p_error rval = (*l_ExternalVideoFuncTable.VidExtFuncSetMode)(Width, Height, BitsPerPixel, ScreenMode);
        l_Fullscreen = (rval == M64ERR_SUCCESS && ScreenMode == M64VIDEO_FULLSCREEN);
        l_VideoOutputActive = (rval == M64ERR_SUCCESS);
        if (l_VideoOutputActive)
            StateChanged(M64CORE_VIDEO_MODE, ScreenMode);
        return rval;
    }

    /* Get SDL video flags to use */
    const SDL_VideoInfo *videoInfo;
    int videoFlags = 0;
    if (ScreenMode == M64VIDEO_WINDOWED)
        videoFlags = SDL_OPENGL;
    else if (ScreenMode == M64VIDEO_FULLSCREEN)
        videoFlags = SDL_OPENGL | SDL_FULLSCREEN;
    else
        return M64ERR_INPUT_INVALID;

    if ((videoInfo = SDL_GetVideoInfo()) == NULL)
    {
        DebugMessage(M64MSG_ERROR, "SDL_GetVideoInfo query failed: %s", SDL_GetError());
        return M64ERR_SYSTEM_FAIL;
    }
    if (videoInfo->hw_available)
        videoFlags |= SDL_HWSURFACE;
    else
        videoFlags |= SDL_SWSURFACE;

    /* set the mode */
    if (BitsPerPixel > 0)
        DebugMessage(M64MSG_INFO, "Setting %i-bit video mode: %ix%i", BitsPerPixel, Width, Height);
    else
        DebugMessage(M64MSG_INFO, "Setting video mode: %ix%i", Width, Height);

    l_pScreen = SDL_SetVideoMode(Width, Height, BitsPerPixel, videoFlags);
    if (l_pScreen == NULL)
    {
        DebugMessage(M64MSG_ERROR, "SDL_SetVideoMode failed: %s", SDL_GetError());
        return M64ERR_SYSTEM_FAIL;
    }

    SDL_ShowCursor(SDL_DISABLE);

    l_Fullscreen = (ScreenMode == M64VIDEO_FULLSCREEN);
    l_VideoOutputActive = 1;
    StateChanged(M64CORE_VIDEO_MODE, ScreenMode);
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_SetCaption(const char *Title)
{
    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
        return (*l_ExternalVideoFuncTable.VidExtFuncSetCaption)(Title);

    SDL_WM_SetCaption(Title, "M64+ Video");

    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_ToggleFullScreen(void)
{
    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
    {
        m64p_error rval = (*l_ExternalVideoFuncTable.VidExtFuncToggleFS)();
        if (rval == M64ERR_SUCCESS)
        {
            l_Fullscreen = !l_Fullscreen;
            StateChanged(M64CORE_VIDEO_MODE, l_Fullscreen ? M64VIDEO_FULLSCREEN : M64VIDEO_WINDOWED);
        }
        return rval;
    }

    if (SDL_WM_ToggleFullScreen(l_pScreen) == 1)
    {
        l_Fullscreen = !l_Fullscreen;
        StateChanged(M64CORE_VIDEO_MODE, l_Fullscreen ? M64VIDEO_FULLSCREEN : M64VIDEO_WINDOWED);
        return M64ERR_SUCCESS;
    }

    return M64ERR_SYSTEM_FAIL;
}

EXPORT void * CALL VidExt_GL_GetProcAddress(const char* Proc)
{
    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
        return (*l_ExternalVideoFuncTable.VidExtFuncGLGetProc)(Proc);

    return SDL_GL_GetProcAddress(Proc);
}

typedef struct {
    m64p_GLattr m64Attr;
    SDL_GLattr sdlAttr;
} GLAttrMapNode;

EXPORT m64p_error CALL VidExt_GL_SetAttribute(m64p_GLattr Attr, int Value)
{
    GLAttrMapNode GLAttrMap[] = {
        { M64P_GL_DOUBLEBUFFER, SDL_GL_DOUBLEBUFFER },
        { M64P_GL_BUFFER_SIZE,  SDL_GL_BUFFER_SIZE },
        { M64P_GL_DEPTH_SIZE,   SDL_GL_DEPTH_SIZE },
        { M64P_GL_RED_SIZE,     SDL_GL_RED_SIZE },
        { M64P_GL_GREEN_SIZE,   SDL_GL_GREEN_SIZE },
        { M64P_GL_BLUE_SIZE,    SDL_GL_BLUE_SIZE },
        { M64P_GL_ALPHA_SIZE,   SDL_GL_ALPHA_SIZE },
        { M64P_GL_SWAP_CONTROL, SDL_GL_SWAP_CONTROL } };
    const int mapSize = sizeof(GLAttrMap) / sizeof(GLAttrMapNode);
    int i;

    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
        return (*l_ExternalVideoFuncTable.VidExtFuncGLSetAttr)(Attr, Value);

    for (i = 0; i < mapSize; i++)
    {
        if (GLAttrMap[i].m64Attr == Attr)
        {
            if (SDL_GL_SetAttribute(GLAttrMap[i].sdlAttr, Value) != 0)
                return M64ERR_SYSTEM_FAIL;
            else
                return M64ERR_SUCCESS;
        }
    }

    return M64ERR_INPUT_INVALID;
}

EXPORT m64p_error CALL VidExt_GL_SwapBuffers(void)
{
    /* call video extension override if necessary */
    if (l_VideoExtensionActive)
        return (*l_ExternalVideoFuncTable.VidExtFuncGLSwapBuf)();

    SDL_GL_SwapBuffers();
    return M64ERR_SUCCESS;
}


