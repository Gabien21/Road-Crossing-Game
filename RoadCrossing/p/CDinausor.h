#pragma once
#include"CAnimal.h"

class CDinausor : public CAnimal
{
private:
	int length;
	int height;
public:
	CDinausor();
	CDinausor(int x, int y);
	CDinausor(const CDinausor& truck);
	int getLength() const;
	int getHeight() const;
	void Tell();
	void drawDinausor(ConsoleHandle& handle);
	vector<Point> getPointList() const;
};