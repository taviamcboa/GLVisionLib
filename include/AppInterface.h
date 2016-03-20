#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include "Keyboard.h"

class AppInterface
{
public:

    virtual void KeyboardCB(GLVISION_KEY key, GLVISION_KEY_STATE keystate = GLVISION_KEY_STATE_PRESS) {};
    
    virtual void PassiveMouseCB(int x, int y) {};

    virtual void RenderSceneCB() {};

    virtual void MouseCB(GLVISION_MOUSE Button, GLVISION_KEY_STATE State, int x, int y) {};

	virtual void ResizeCB(int width, int height) {}; 
};


#endif