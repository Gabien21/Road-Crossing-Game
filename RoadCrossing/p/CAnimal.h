#pragma once
#include "Point.h"
#include "ConsoleHandle.h"

class CAnimal
{
protected:
	Point pos;
	bool direction;
public:
	CAnimal();
	CAnimal(int x, int y);
	Point getPos() const;
	void setPos(int x, int y);
	bool getDirection() const;
	void setDirection(bool direction);
	void Move();
	void deleteAnimal(ConsoleHandle& handle);
	virtual void Tell() = 0;
	virtual int getLength() const = 0;
	virtual int getHeight() const = 0;
	virtual vector<Point> getPointList() const = 0;
};