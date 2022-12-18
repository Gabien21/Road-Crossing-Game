#pragma once
#include "CAnimal.h"

class CBird : public CAnimal
{
private:
	int length;
	int height;
public:
	CBird();
	CBird(int x, int y);
	CBird(const CBird& car);
	int getLength() const;
	int getHeight() const;
	void Tell();
	void drawBird(ConsoleHandle& handle);
	vector<Point> getPointList() const;
};