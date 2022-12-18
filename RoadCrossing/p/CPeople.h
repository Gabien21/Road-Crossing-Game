#pragma once
#include "CCar.h"
#include "CTruck.h"
#include "CDinausor.h"
#include "CBird.h"

class CPeople
{
private:
	Point pos;
	bool mState;
	int length;
public:
	CPeople();
	CPeople(int x, int y);
	void setState(bool s);
	Point getPos();
	void setPos(int x, int y);
	void Up();
	void Down();
	void Left();
	void Right();
	bool isImpact(const vector<CCar>& obj);
	bool isImpact(const vector<CTruck>& obj);
	bool isImpact(const vector<CBird>& obj);
	bool isImpact(const vector<CDinausor>& obj);
	bool isFinish();
	bool isDead();
	void draw(ConsoleHandle& handle);
	vector<Point> getPoint();
	void erasePeople(ConsoleHandle& handle);
	void drawDeathEffect(ConsoleHandle& handle);
};