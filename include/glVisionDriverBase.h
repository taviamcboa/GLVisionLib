#ifndef GLVISIONDRIVERBASE_H
#define GLVISIONDRIVERBASE_H

#include "glVisionTypes.h"
#include "AppInterface.h"

enum GLVISION_DRIVER_TYPE {
	GLVISION_DRIVER_TYPE_GLUT,
	GLVISION_DRIVER_TYPE_GLFW
};

void initGLContext(GLVISION_DRIVER_TYPE osdriver, int argc, char** argv, bool WithDepth, bool WithStencil);

void terminateGLContext();

bool createWindow(uint Width, uint Height, bool isFullScreen, const char* pTitle);

void run(AppInterface* pAppInstance);

void leaveMainLoop();

void swapBuffers();

void setMousePos(uint x, uint y);


#endif