#ifndef OGLDEV_ATB_H
#define	OGLDEV_ATB_H

#include "Keyboard.h"
#include "glVisionMath.h"

#include "ATB/AntTweakBar.h"

class glVisionAntTweakBar
{
protected:
	glVisionAntTweakBar();

	virtual ~glVisionAntTweakBar(); 
    
    bool Init();
    
    bool KeyboardCB(GLVISION_KEY OgldevKey);

    bool PassiveMouseCB(int x, int y);

    void RenderSceneCB();

    bool MouseCB(GLVISION_MOUSE Button, GLVISION_KEY_STATE State, int x, int y);

	void ResizeCB(int width, int height); 
    
};


extern TwType TW_TYPE_GLVISION_VECTOR3F;
extern TwType TW_TYPE_GLVISION_ATTENUATION;

#endif