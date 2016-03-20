#ifndef GLVISION_APP_H
#define GLVISION_APP_H

class glVisionApp
{
protected:
	glVisionApp();

	virtual ~glVisionApp();

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();

protected:
private:
	long long m_frameTime;
	long long m_startTime;
	int m_frameCount;
    int m_fps;
};


#endif