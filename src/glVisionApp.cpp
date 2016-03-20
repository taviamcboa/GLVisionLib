#include "glVisionApp.h"
#include "glVisionUtility.h"


glVisionApp::glVisionApp()
{
    m_frameCount = 0;
    m_frameTime = 0;
    m_fps = 0;

    m_frameTime = m_startTime = GetCurrentTimeMillis();
}

glVisionApp::~glVisionApp()
{
	fprintf(stderr, "glVisionApp::~glVisionApp\n");
}

void glVisionApp::CalcFPS()
{
    m_frameCount++;

    long long time = GetCurrentTimeMillis();
    
    if (time - m_frameTime >= 1000) {
        m_frameTime = time;
        m_fps = m_frameCount;
        m_frameCount = 0;
    }
}

void glVisionApp::RenderFPS()
{
    char text[32];
    ZERO_MEM(text);        
    SNPRINTF(text, sizeof(text), "FPS: %d", m_fps);
}

float glVisionApp::GetRunningTime()
{
    float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;
    return RunningTime;
}
