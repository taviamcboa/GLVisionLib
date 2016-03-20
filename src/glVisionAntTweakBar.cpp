

#include "glVisionAntTweakBar.h"
#include "LightModel.h"



TwType TW_TYPE_GLVISION_VECTOR3F;
TwType TW_TYPE_GLVISION_ATTENUATION;



glVisionAntTweakBar::glVisionAntTweakBar()
{
    
}
glVisionAntTweakBar::~glVisionAntTweakBar()
{
	fprintf(stderr, "glVisionAntTweakBar::~glVisionAntTweakBar\n"); 
}

bool glVisionAntTweakBar::Init()
{
    bool ret = false;
    
    if (TwInit(TW_OPENGL_CORE, NULL) == 1)
    {
        TwStructMember Vector3fMembers[] = {
            { "x", TW_TYPE_FLOAT, offsetof(Vector3f, x), "" },
            { "y", TW_TYPE_FLOAT, offsetof(Vector3f, y), "" },
            { "z", TW_TYPE_FLOAT, offsetof(Vector3f, z), "" }
        };
        
		TW_TYPE_GLVISION_VECTOR3F = TwDefineStruct("Vector3f", Vector3fMembers, 3, sizeof(Vector3f), NULL, NULL);

        TwStructMember AttenuationMembers[] = {
            { "Const", TW_TYPE_FLOAT, offsetof(LightAttenuation, Constant), "" },
            { "Linear", TW_TYPE_FLOAT, offsetof(LightAttenuation, Linear), "" },
            { "Exp", TW_TYPE_FLOAT, offsetof(LightAttenuation, Exp), "" }
        };
        
        TW_TYPE_GLVISION_ATTENUATION = TwDefineStruct("Attenuation", AttenuationMembers, 3, sizeof(LightAttenuation), NULL, NULL);
        
        ret = true;
    }
    
    return ret;
}


static int GLVISIONKeyToATBKey(GLVISION_KEY GLVISIONKey)
{
    if (GLVISIONKey >= GLVISION_KEY_SPACE && GLVISIONKey <= GLVISION_KEY_RIGHT_BRACKET) {
        return GLVISIONKey;
    }

    switch(GLVISIONKey) {

        case GLVISION_KEY_BACKSPACE:
            return TW_KEY_BACKSPACE;
        case GLVISION_KEY_TAB:
            return TW_KEY_TAB;
//            return TW_KEY_CLEAR;
        case GLVISION_KEY_ENTER:
            return TW_KEY_RETURN;
            
            //return TW_KEY_PAUSE;
        case GLVISION_KEY_ESCAPE:
            return TW_KEY_ESCAPE;
        case GLVISION_KEY_DELETE:
            return TW_KEY_DELETE;
        case GLVISION_KEY_UP:
            return TW_KEY_UP;
        case GLVISION_KEY_DOWN:
            return TW_KEY_DOWN;
        case GLVISION_KEY_RIGHT:
            return TW_KEY_RIGHT;
        case GLVISION_KEY_LEFT:
            return TW_KEY_LEFT;
        case GLVISION_KEY_INSERT:
            return TW_KEY_INSERT;
        case GLVISION_KEY_HOME:
            return TW_KEY_HOME;
        case GLVISION_KEY_END:
            return TW_KEY_END;
        case GLVISION_KEY_PAGE_UP:
            return TW_KEY_PAGE_UP;
        case GLVISION_KEY_PAGE_DOWN:
            return TW_KEY_PAGE_DOWN;
        case GLVISION_KEY_F1:
            return TW_KEY_F1;
        case GLVISION_KEY_F2:            
            return TW_KEY_F2;
        case GLVISION_KEY_F3:
            return TW_KEY_F3;
        case GLVISION_KEY_F4:
            return TW_KEY_F4;
        case GLVISION_KEY_F5:
            return TW_KEY_F5;
        case GLVISION_KEY_F6:
            return TW_KEY_F6;
        case GLVISION_KEY_F7:
            return TW_KEY_F7;
        case GLVISION_KEY_F8:
            return TW_KEY_F8;
        case GLVISION_KEY_F9:
            return TW_KEY_F9;
        case GLVISION_KEY_F10:
            return TW_KEY_F10;
        case GLVISION_KEY_F11:
            return TW_KEY_F11;
        case GLVISION_KEY_F12:
            return TW_KEY_F12;
        default:
            GLVISION_ERROR("Unimplemented GLVISION to ATB key");
    }
    
    return TW_KEY_LAST;
}

bool glVisionAntTweakBar::KeyboardCB(GLVISION_KEY GLVISIONKey)
{
    int ATBKey = GLVISIONKeyToATBKey(GLVISIONKey);
    
    if (ATBKey == TW_KEY_LAST) {
        return false;
    }
    
    return (TwKeyPressed(ATBKey, TW_KMOD_NONE) == 1);
}


bool glVisionAntTweakBar::PassiveMouseCB(int x, int y)
{
    return (TwMouseMotion(x, y) == 1);
}

void glVisionAntTweakBar::RenderSceneCB()
{

}

bool glVisionAntTweakBar::MouseCB(GLVISION_MOUSE Button, GLVISION_KEY_STATE State, int x, int y)
{    
    TwMouseButtonID btn = (Button == GLVISION_MOUSE_BUTTON_LEFT) ? TW_MOUSE_LEFT : TW_MOUSE_RIGHT;
    TwMouseAction ma = (State == GLVISION_KEY_STATE_PRESS) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
    
    return (TwMouseButton(ma, btn) == 1);
}

void glVisionAntTweakBar::ResizeCB(int width, int height)
{
	TwWindowSize(width, height);
}