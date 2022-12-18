#pragma once
#include "CVehicle.h"

class CCar : public CVehicle
{
private:
	int length;
	int height;
public:
	CCar();
	CCar(int x, int y);
	CCar(const CCar& car);
	int getLength() const;
	int getHeight() const;
	void Tell();
	void drawCar(ConsoleHandle& handle);
	vector<Point> getPointList() const;
};
