#pragma once
#pragma once
#include "CGame.h"
#include "Point.h"
#include "vector"
#include "ConsoleHandle.h"

class TrafficLight {
private:
	string type;
	int time;
	int currentTime;
	Point pos;
public:
	TrafficLight()
	{
		this->pos.x = this->pos.y = 0;
		type = "Light-1.txt";
		time = (rand() % 10) + 30;
		currentTime = 0;
	}
	TrafficLight(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;
		type = "Light-1.txt";
		time = (rand() % 10) + 30;
		currentTime = 0;
	}
	void setTime(int currentTime, int time)
	{
		this->currentTime = currentTime;
		this->time = time;
	}
	void setType(int type)
	{
		if (type == 1)
			this->type = "Light-1.txt";
		else
			this->type = "Light-2.txt";
	}
	void setPos(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;
	}
	Point getPos()
	{
		return pos;
	}
	void drawLight(ConsoleHandle& handle)
	{
		if (type == "Light-1.txt")
		{
			handle.updateObstacle(pos.x, pos.y, type);
			handle.updateString(pos.x + 1, pos.y + 1, "___", 32);
		}
		else if (type == "Light-2.txt")
		{
			handle.updateObstacle(pos.x, pos.y, type);
			handle.updateString(pos.x + 1, pos.y + 2, "___", 64);
		}
	}
	void changeType(ConsoleHandle& handle)
	{
		currentTime++;
		handle.drawString(pos.x + 4, pos.y + 6, (time - currentTime) < 10 ? "0" + to_string(time - currentTime) : to_string(time - currentTime));
		if (currentTime == time) {
			if (type == "Light-1.txt")
				type = "Light-2.txt";
			else type = "Light-1.txt";
			currentTime = 0;
		}
	}
	int getTime()
	{
		return time;
	}
	int getCurrentTime()
	{
		return currentTime;
	}
	string getStatus()
	{
		return type;
	}
};