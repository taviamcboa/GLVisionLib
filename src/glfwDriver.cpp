

#ifdef WIN32
#include <Windows.h>
#endif
#include <stdio.h>
#include <GL/glew.h>
//#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "glVisionUtility.h"
#include "glfwDriver.h"

// Points to the object implementing the ICallbacks interface which was delivered to
// GLUTBackendRun(). All events are forwarded to this object.
static AppInterface* sAppInstance = NULL;

static bool sWithDepth = false;
static bool sWithStencil = false;
static GLFWwindow* s_pWindow = NULL;


static GLVISION_KEY GLFWKeyToGLVISIONKey(uint Key)
{
    if (Key >= GLFW_KEY_SPACE && Key <= GLFW_KEY_RIGHT_BRACKET) {
        return (GLVISION_KEY)Key;
    }
    
    switch (Key) {
        case GLFW_KEY_ESCAPE:            
            return GLVISION_KEY_ESCAPE;
        case GLFW_KEY_ENTER:         
            return GLVISION_KEY_ENTER;
        case GLFW_KEY_TAB:          
            return GLVISION_KEY_TAB;
        case GLFW_KEY_BACKSPACE:  
            return GLVISION_KEY_BACKSPACE;
        case GLFW_KEY_INSERT:         
            return GLVISION_KEY_INSERT;
        case GLFW_KEY_DELETE:        
            return GLVISION_KEY_DELETE;
        case GLFW_KEY_RIGHT:         
            return GLVISION_KEY_RIGHT;
        case GLFW_KEY_LEFT:         
            return GLVISION_KEY_LEFT;
        case GLFW_KEY_DOWN:        
            return GLVISION_KEY_DOWN;            
        case GLFW_KEY_UP:         
            return GLVISION_KEY_UP;
        case GLFW_KEY_PAGE_UP:   
            return GLVISION_KEY_PAGE_UP;
        case GLFW_KEY_PAGE_DOWN:      
            return GLVISION_KEY_PAGE_DOWN;
        case GLFW_KEY_HOME:    
            return GLVISION_KEY_HOME;
        case GLFW_KEY_END:     
            return GLVISION_KEY_END;
        case GLFW_KEY_F1:        
            return GLVISION_KEY_F1;
        case GLFW_KEY_F2:        
            return GLVISION_KEY_F2;
        case GLFW_KEY_F3:       
            return GLVISION_KEY_F3;
        case GLFW_KEY_F4:   
            return GLVISION_KEY_F4;
        case GLFW_KEY_F5:      
            return GLVISION_KEY_F5;
        case GLFW_KEY_F6:     
            return GLVISION_KEY_F6;
        case GLFW_KEY_F7:     
            return GLVISION_KEY_F7;
        case GLFW_KEY_F8:     
            return GLVISION_KEY_F8;
        case GLFW_KEY_F9:     
            return GLVISION_KEY_F9;
        case GLFW_KEY_F10:    
            return GLVISION_KEY_F10;
        case GLFW_KEY_F11:   
            return GLVISION_KEY_F11;
        case GLFW_KEY_F12:    
            return GLVISION_KEY_F12;
        default:
            GLVISION_ERROR("Unimplemented GLVISION key");
    }
    
    return GLVISION_KEY_UNDEFINED;
}

static GLVISION_MOUSE GLFWMouseToGLVISIONMouse(uint Button)
{
	switch (Button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		return GLVISION_MOUSE_BUTTON_LEFT;
	case GLFW_MOUSE_BUTTON_RIGHT:
		return GLVISION_MOUSE_BUTTON_RIGHT;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		return GLVISION_MOUSE_BUTTON_MIDDLE;
	default:
		GLVISION_ERROR("Unimplemented GLVISION mouse button");
	}

	return GLVISION_MOUSE_UNDEFINED;
}

static void KeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{   
    GLVISION_KEY GLVISIONKey = GLFWKeyToGLVISIONKey(key);   
    GLVISION_KEY_STATE GLVISIONKeyState = (action == GLFW_PRESS) ? GLVISION_KEY_STATE_PRESS : GLVISION_KEY_STATE_RELEASE;
	sAppInstance->KeyboardCB(GLVISIONKey, GLVISIONKeyState);
}


static void CursorPosCallback(GLFWwindow* pWindow, double x, double y)
{
	sAppInstance->PassiveMouseCB((int)x, (int)y);
}


static void MouseButtonCallback(GLFWwindow* pWindow, int Button, int Action, int Mode)
{
    GLVISION_MOUSE GLVISIONMouse = GLFWMouseToGLVISIONMouse(Button);

    GLVISION_KEY_STATE State = (Action == GLFW_PRESS) ? GLVISION_KEY_STATE_PRESS : GLVISION_KEY_STATE_RELEASE;

    double x, y;

    glfwGetCursorPos(pWindow, &x, &y);

	sAppInstance->MouseCB(GLVISIONMouse, State, (int)x, (int)y);
}

static void ResizeWindowCallback(GLFWwindow* pWindow, int width, int height)
{
	sAppInstance->ResizeCB(width, height);
}

static void InitCallbacks()
{
    glfwSetKeyCallback(s_pWindow, KeyCallback);
    glfwSetCursorPosCallback(s_pWindow, CursorPosCallback);
    glfwSetMouseButtonCallback(s_pWindow, MouseButtonCallback);
	glfwSetFramebufferSizeCallback(s_pWindow, ResizeWindowCallback);
}

void GLFWErrorCallback(int error, const char* description)
{
#ifdef WIN32
    char msg[1000];
    _snprintf_s(msg, sizeof(msg), "GLFW error %d - %s", error, description);
    MessageBoxA(NULL, msg, NULL, 0);
#else
    fprintf(stderr, "GLFW error %d - %s", error, description);
#endif    
    exit(0);
}


void initGLContext_GLFW(int argc, char** argv, bool WithDepth, bool WithStencil)
{
    sWithDepth = WithDepth;
    sWithStencil = WithStencil;

    glfwSetErrorCallback(GLFWErrorCallback);    
    
    if (glfwInit() != 1) {
        GLVISION_ERROR("Error initializing GLFW");
        exit(1);
    }
    
    int Major, Minor, Rev;
    
	glfwGetVersion(&Major, &Minor, &Rev);
    
    printf("GLFW %d.%d.%d initialized\n", Major, Minor, Rev);       
}


void terminate_GLFW()
{
    glfwDestroyWindow(s_pWindow);
    glfwTerminate();
}


bool createWindow_GLFW(uint Width, uint Height, bool isFullScreen, const char* pTitle)
{
    GLFWmonitor* pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;

    s_pWindow = glfwCreateWindow(Width, Height, pTitle, pMonitor, NULL);

    if (!s_pWindow) {
        GLVISION_ERROR("error creating window");
        exit(1);
    }
    
    glfwMakeContextCurrent(s_pWindow);
    
    // Must be done after glfw is initialized!
    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        GLVISION_ERROR((const char*)glewGetErrorString(res));
        exit(1);
    }    
    
    return (s_pWindow != NULL);
}

void run_GLFW(AppInterface* pAppInstance)
{
    if (!pAppInstance) {
        GLVISION_ERROR("callbacks not specified");
        exit(1);
    }

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    if (sWithDepth) {
        glEnable(GL_DEPTH_TEST);
    }
	sAppInstance = pAppInstance;
    InitCallbacks();

    while (!glfwWindowShouldClose(s_pWindow)) {
		sAppInstance->RenderSceneCB();
        glfwSwapBuffers(s_pWindow);
        glfwPollEvents();
    }
}


void swapBuffer_GLFW()
{
    // Nothing to do here
}


void leaveMainLoop_GLFW()
{
    glfwSetWindowShouldClose(s_pWindow, 1);
}


void setMousePos_GLFW(uint x, uint y)
{
    glfwSetCursorPos(s_pWindow, (double)x, (double)y);
}