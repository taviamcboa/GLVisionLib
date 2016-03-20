
#include <AntTweakBar.h>

#include "glVisionUtility.h"
#include "glVisionDriverBase.h"
#include "glfwDriver.h"
#include "glutDriver.h"


static GLVISION_DRIVER_TYPE sBackendType = GLVISION_DRIVER_TYPE_GLFW;

void initGLContext(GLVISION_DRIVER_TYPE BackendType, int argc, char** argv, bool WithDepth, bool WithStencil)
{
    sBackendType = BackendType;
    
    switch (BackendType) {
        case GLVISION_DRIVER_TYPE_GLUT:
			initGLContext_GLUT(argc, argv, WithDepth, WithStencil);
            break;
        case GLVISION_DRIVER_TYPE_GLFW:
			initGLContext_GLFW(argc, argv, WithDepth, WithStencil);
            break;
        default:
            assert(0);
    }   
}


void terminateGLContext()
{
    switch (sBackendType) {
        case GLVISION_DRIVER_TYPE_GLUT:
            // nothing to do here...
            break;
        case GLVISION_DRIVER_TYPE_GLFW:
            terminate_GLFW();
            break;
        default:
            assert(0);
    }
}


bool createWindow(uint Width, uint Height, bool isFullScreen, const char* pTitle)
{
    TwWindowSize(Width, Height);
    
    switch (sBackendType) {
        case GLVISION_DRIVER_TYPE_GLUT:
            return createWindow_GLUT(Width, Height, isFullScreen, pTitle);
        case GLVISION_DRIVER_TYPE_GLFW:
            return createWindow_GLFW(Width, Height, isFullScreen, pTitle);
        default:
            assert(0);
    }
    
   
	return false;
}


void run(AppInterface* pAppInstance)
{  
    switch (sBackendType) {
        case GLVISION_DRIVER_TYPE_GLUT:
            run_GLUT(pAppInstance);
            break;
        case GLVISION_DRIVER_TYPE_GLFW:
            run_GLFW(pAppInstance);
            break;
        default:
            assert(0);
    }    
}


void swapBuffers()
{
   TwDraw();
    
    switch (sBackendType) {
        case GLVISION_DRIVER_TYPE_GLUT:
            swapBuffer_GLUT();
            break;
        case GLVISION_DRIVER_TYPE_GLFW:
            swapBuffer_GLFW();
            break;
        default:
            assert(0);
    }    
}


void leaveMainLoop()
{
    switch (sBackendType) {
        case GLVISION_DRIVER_TYPE_GLUT:
            leaveMainLoop_GLUT();
            break;
        case GLVISION_DRIVER_TYPE_GLFW:
            leaveMainLoop_GLFW();
            break;
        default:
            assert(0);
    }
}


void setMousePos(uint x, uint y)
{
    switch (sBackendType) {
        case GLVISION_DRIVER_TYPE_GLUT:
           //GLUTBackendLeaveMainLoop();
            break;
        case GLVISION_DRIVER_TYPE_GLFW:
            setMousePos_GLFW(x, y);
            break;
        default:
            assert(0);
    }    
}