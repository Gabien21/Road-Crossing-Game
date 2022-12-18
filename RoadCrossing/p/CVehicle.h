#pragma once
#include"CTrafficLight.h"

class CVehicle
{
protected:
	Point pos;
	bool direction;
public:
	CVehicle();
	CVehicle(int x, int y);
	Point getPos() const;
	void setPos(int x, int y);
	bool getDirection() const;
	void setDirection(bool direc);
	void Move(TrafficLight lightList);
	void deleteVehicle(ConsoleHandle& handle, TrafficLight lightList);
	virtual void Tell() = 0;
	virtual int getLength() const = 0;
	virtual int getHeight() const = 0;
	virtual vector<Point> getPointList() const = 0;
};