#ifndef WIN32
#include <unistd.h>
#endif
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "glVisionUtility.h"
#include "glVisionDriverBase.h"

// Points to the object implementing the ICallbacks interface which was delivered to
// GLUTBackendRun(). All events are forwarded to this object.
static AppInterface* s_appInstance = NULL;

static bool sWithDepth = false;
static bool sWithStencil = false;

GLVISION_KEY GLUTKeyToGLVISIONKey(uint Key)
{
    switch (Key) {
		case GLUT_KEY_F1:        
			return GLVISION_KEY_F1;
		case GLUT_KEY_F2:        
			return GLVISION_KEY_F2;
		case GLUT_KEY_F3:       
			return GLVISION_KEY_F3;
		case GLUT_KEY_F4:   
			return GLVISION_KEY_F4;
		case GLUT_KEY_F5:      
			return GLVISION_KEY_F5;
		case GLUT_KEY_F6:     
			return GLVISION_KEY_F6;
		case GLUT_KEY_F7:     
			return GLVISION_KEY_F7;
		case GLUT_KEY_F8:     
			return GLVISION_KEY_F8;
		case GLUT_KEY_F9:     
			return GLVISION_KEY_F9;
		case GLUT_KEY_F10:    
			return GLVISION_KEY_F10;
		case GLUT_KEY_F11:   
			return GLVISION_KEY_F11;
		case GLUT_KEY_F12:    
			return GLVISION_KEY_F12;
		case GLUT_KEY_LEFT:         
			return GLVISION_KEY_LEFT;
		case GLUT_KEY_UP:         
			return GLVISION_KEY_UP;
		case GLUT_KEY_RIGHT:         
			return GLVISION_KEY_RIGHT;
		case GLUT_KEY_DOWN:        
			return GLVISION_KEY_DOWN;            
		case GLUT_KEY_PAGE_UP:   
			return GLVISION_KEY_PAGE_UP;
		case GLUT_KEY_PAGE_DOWN:      
			return GLVISION_KEY_PAGE_DOWN;
		case GLUT_KEY_HOME:    
			return GLVISION_KEY_HOME;
		case GLUT_KEY_END:     
			return GLVISION_KEY_END;	
		case GLUT_KEY_INSERT:         
            return GLVISION_KEY_INSERT;
        case GLUT_KEY_DELETE:        
            return GLVISION_KEY_DELETE;
        default:
            GLVISION_ERROR("Unimplemented GLUT key");
            exit(1);
    }
    
    return GLVISION_KEY_UNDEFINED;
}


static GLVISION_MOUSE GLUTMouseToGLVISIONMouse(uint Button)
{
    switch (Button) {
    case GLUT_LEFT_BUTTON:
            return GLVISION_MOUSE_BUTTON_LEFT;
    case GLUT_RIGHT_BUTTON:
            return GLVISION_MOUSE_BUTTON_RIGHT;
    case GLUT_MIDDLE_BUTTON:
            return GLVISION_MOUSE_BUTTON_MIDDLE;
    default:
		;
          //  GLVISION_ERROR("Unimplemented GLUT mouse button");
    }

    return GLVISION_MOUSE_UNDEFINED;
}


static void SpecialKeyboardCB(int Key, int x, int y)
{
    GLVISION_KEY GLVISIONKey = GLUTKeyToGLVISIONKey(Key);
	s_appInstance->KeyboardCB(GLVISIONKey);
}


static void KeyboardCB(unsigned char Key, int x, int y)
{
    

		GLVISION_KEY GLVISIONKey = (GLVISION_KEY)Key;
		s_appInstance->KeyboardCB(GLVISIONKey);

}


static void PassiveMouseCB(int x, int y)
{
	s_appInstance->PassiveMouseCB(x, y);
}


static void RenderSceneCB()
{
	s_appInstance->RenderSceneCB();
}


static void IdleCB()
{
	s_appInstance->RenderSceneCB();
}

static void ResizeCB(int width, int height)
{
	s_appInstance->ResizeCB(width, height); 
}

static void MouseCB(int Button, int State, int x, int y)
{
	GLVISION_MOUSE GLVISIONMouse = GLUTMouseToGLVISIONMouse(Button);
	GLVISION_KEY_STATE GLVISIONKeyState = (State == GLUT_DOWN) ? GLVISION_KEY_STATE_PRESS : GLVISION_KEY_STATE_RELEASE;

	s_appInstance->MouseCB(GLVISIONMouse, GLVISIONKeyState, x, y);
}


static void InitCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(IdleCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutPassiveMotionFunc(PassiveMouseCB);
    glutKeyboardFunc(KeyboardCB);
    glutMouseFunc(MouseCB);
	glutReshapeFunc(ResizeCB);
}


void initGLContext_GLUT(int argc, char** argv, bool WithDepth, bool WithStencil)
{
    sWithDepth = WithDepth;
    sWithStencil = WithStencil;

    glutInit(&argc, argv);
	
    uint DisplayMode = GLUT_DOUBLE|GLUT_RGBA;

    if (WithDepth) {
        DisplayMode |= GLUT_DEPTH;
    }

    if (WithStencil) {
        DisplayMode |= GLUT_STENCIL;
    }

    glutInitDisplayMode(DisplayMode);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}


bool createWindow_GLUT(unsigned int Width, unsigned int Height, bool isFullScreen, const char* pTitle)
{
    if (isFullScreen) {
        char ModeString[64] = { 0 };
        int bpp = 32;
        SNPRINTF(ModeString, sizeof(ModeString), "%dx%d:%d@60", Width, Height, bpp);
        glutGameModeString(ModeString);
        glutEnterGameMode();
    }
    else {
        glutInitWindowSize(Width, Height);
        glutCreateWindow(pTitle);
    }

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return false;
    }

    return true;
}

void run_GLUT(AppInterface* pAppInstance)
{
    if (!pAppInstance) {
        fprintf(stderr, "%s : callbacks not specified!\n", __FUNCTION__);
        return;
    }

    glClearColor(0.f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    if (sWithDepth) {
        glEnable(GL_DEPTH_TEST);
    }

	s_appInstance = pAppInstance;
    InitCallbacks();
    glutMainLoop();
}


void swapBuffer_GLUT()
{
    glutSwapBuffers();
}

void leaveMainLoop_GLUT()
{
    glutLeaveMainLoop();
}