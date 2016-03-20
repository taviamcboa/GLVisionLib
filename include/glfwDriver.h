#ifndef GLVISION_GLFW_BACKEND_H
#define	GLVISION_GLFW_BACKEND_H

#include "glVisionTypes.h"
#include "AppInterface.h"

void initGLContext_GLFW(int argc, char** argv, bool WithDepth, bool WithStencil);

void terminate_GLFW();

bool createWindow_GLFW(uint Width, uint Height, bool isFullScreen, const char* pTitle);

void run_GLFW(AppInterface* pAppInstance);

void swapBuffer_GLFW();

void leaveMainLoop_GLFW();

void setMousePos_GLFW(uint x, uint y);

#endif
