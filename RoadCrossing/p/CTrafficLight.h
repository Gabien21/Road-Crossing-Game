#pragma once
#include "Point.h"
#include "ConsoleHandle.h"

class TrafficLight {
private:
	string type;
	int time;
	int currentTime;
	Point pos;
public:
	TrafficLight();
	TrafficLight(int x, int y);
	void setTime(int currentTime, int time);
	void setType(int type);
	void setPos(int x, int y);
	Point getPos();
	void drawLight(ConsoleHandle& handle);
	void changeType(ConsoleHandle& handle);
	int getTime();
	int getCurrentTime();
	string getStatus();
};