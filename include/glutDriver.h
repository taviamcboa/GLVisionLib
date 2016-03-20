#ifndef GLVISION_GLUT_DRIVER_H
#define	GLVISION_GLUT_DRIVER_H

#include "glVisionTypes.h"
#include "AppInterface.h"

void initGLContext_GLUT(int argc, char** argv, bool WithDepth, bool WithStencil);

bool createWindow_GLUT(uint Width, uint Height, bool isFullScreen, const char* pTitle);

void run_GLUT(AppInterface* pAppInstance);

void swapBuffer_GLUT();

void leaveMainLoop_GLUT();

GLVISION_KEY GLUTKeyToGLVISIONKey(uint Key);

#endif	/* GLUT_BACKEND_H */

