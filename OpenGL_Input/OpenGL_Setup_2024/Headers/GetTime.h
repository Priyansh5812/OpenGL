#include <iostream>
#include<chrono>
#include<thread>
#pragma once

class GetTime
{
public:
	 static std::chrono::high_resolution_clock::time_point currTime;
	 static std::chrono::high_resolution_clock::time_point lastTime;
	 static bool canCalc;
	 static float deltaTime;
	 static void StartCalculateDeltaTime();
	 static void CalculateDeltaTime();
	 static void StopCalculateDeltaTime();
};

