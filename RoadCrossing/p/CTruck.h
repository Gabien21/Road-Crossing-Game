#pragma once
#include "CVehicle.h"

class CTruck : public CVehicle
{
private:
	int length;
	int height;
public:
	CTruck();
	CTruck(int x, int y);
	CTruck(const CTruck& truck);
	int getLength() const;
	int getHeight() const;
	void Tell();
	void drawTruck(ConsoleHandle& handle);
	vector<Point> getPointList() const;
};