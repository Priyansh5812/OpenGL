#include "GetTime.h"


std::chrono::high_resolution_clock::time_point GetTime::currTime = std :: chrono :: high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point GetTime::lastTime = std :: chrono :: high_resolution_clock::now();
bool GetTime::canCalc = false;
float GetTime::deltaTime = 0.0f;


void GetTime::StartCalculateDeltaTime()
{	
	canCalc = true;
	lastTime = std::chrono::high_resolution_clock::now();
	std :: thread t1 (CalculateDeltaTime);
	t1.detach();
}

 void GetTime::CalculateDeltaTime()
{	
	 
	 while (canCalc)
	 {	 
		 //std::cout << deltaTime << std::endl;
		 currTime = std::chrono::high_resolution_clock::now();
		 deltaTime = std::chrono::duration<float>(currTime - lastTime).count();
		 lastTime = currTime;
	 }
}

 void GetTime::StopCalculateDeltaTime()
 {
	 canCalc = false;
 }