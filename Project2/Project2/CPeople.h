#pragma once
#include "CGame.h"
#include "CVehicle.h"
#include "Point.h"
#include "CAnimal.h"
#include<vector>
class CPeople
{
private:
	Point pos;
	bool mState;
	int length;
public:
	CPeople()
	{
		mState = true;
		pos.x = 0;
		pos.y = 0;
		length = 3;
		this->mState = true;
	}
	CPeople(int x, int y)
	{
		mState = true;
		pos.x = x;
		pos.y = y;
		length = 3;
		this->mState = true;
	}
	void setState(bool s)
	{
		this->mState = true;
	}
	Point getPos()
	{
		return pos;
	}
	void setPos(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;
	}
	void Up()
	{
		if (this->pos.y == 1)
			return;
		this->pos.y--;
		//tell();
	}
	void Down() {
		if (this->pos.y == 43)
			return;
		this->pos.y++;
		//tell();
	}
	void Left() {
		if (this->pos.x == 33)
			return;
		this->pos.x--;
		//tell();
	}
	void Right() {
		if (this->pos.x == 160)
			return;
		this->pos.x++;
		//tell();
	}
	bool isImpact(const vector<CCar>& obj)
	{
		vector<Point> y = getPoint();
		vector<Point> x = obj[0].getPointList();
		for (int k = 0; k < obj.size(); k++)
		{
			Point a = obj[k].getPos();
			for (int i = 0; i < y.size(); i++)
			{
				Point tmp1(y[i].x + pos.x, y[i].y + pos.y);
				for (int j = 0; j < x.size(); j++)
				{
					Point tmp2(x[j].x + a.x, x[j].y + a.y);
					if (tmp2.x == tmp1.x && tmp2.y == tmp1.y)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	bool isImpact(const vector<CTruck>& obj)
	{
		vector<Point> y = getPoint();
		vector<Point> x = obj[0].getPointList();
		for (int k = 0; k < obj.size(); k++)
		{
			Point a = obj[k].getPos();
			for (int i = 0; i < y.size(); i++)
			{
				Point tmp1(y[i].x + pos.x, y[i].y + pos.y);
				for (int j = 0; j < x.size(); j++)
				{
					Point tmp2(x[j].x + a.x, x[j].y + a.y);
					if (tmp2.x == tmp1.x && tmp2.y == tmp1.y)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool isImpact(const vector<CBird>& obj)
	{
		vector<Point> y = getPoint();
		vector<Point> x = obj[0].getPointList();
		for (int k = 0; k < obj.size(); k++)
		{
			Point a = obj[k].getPos();
			for (int i = 0; i < y.size(); i++)
			{
				Point tmp1(y[i].x + pos.x, y[i].y + pos.y);
				for (int j = 0; j < x.size(); j++)
				{
					Point tmp2(x[j].x + a.x, x[j].y + a.y);
					if (tmp2.x == tmp1.x && tmp2.y == tmp1.y)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	bool isImpact(const vector<CDinausor>& obj)
	{
		vector<Point> y = getPoint();
		vector<Point> x = obj[0].getPointList();
		for (int k = 0; k < obj.size(); k++)
		{
			Point a = obj[k].getPos();
			for (int i = 0; i < y.size(); i++)
			{
				Point tmp1(y[i].x + pos.x, y[i].y + pos.y);
				for (int j = 0; j < x.size(); j++)
				{
					Point tmp2(x[j].x + a.x, x[j].y + a.y);
					if (tmp2.x == tmp1.x && tmp2.y == tmp1.y)
					{
						return true;
					}
				}
			}
		}
		return false;
	}



	bool isFinish()
	{
		return pos.y == 2;
	}
	bool isDead()
	{
		return mState == 0;
	}
	void draw(ConsoleHandle& handle)
	{
		handle.updateObstacle(pos.x, pos.y, "HumanTexture.txt");
	}
	vector<Point> getPoint()
	{
		ifstream op;
		op.open("HumanTexture.txt");
		vector<string> line;
		string tmp;
		while (getline(op, tmp))
			line.push_back(tmp);
		op.close();
		vector<Point> x;
		for (int i = 0; i < line.size(); i++)
		{
			for (int j = 0; j < line[i].length(); j++)
			{
				if (line[i][j] != ' ')
				{
					Point tmp(j, i);
					x.push_back(tmp);
				}
			}
		}
		return x;
	}
	void erasePeople(ConsoleHandle& handle)
	{
		handle.eraseGraphic(pos.x, pos.y, 3, length);
	}
	void drawDeathEffect(ConsoleHandle& handle) {
		string filePrefixName = "HumanTextureDeath-0";
		for (int i = 1; i <= 2; i++) {
			string fileName = filePrefixName + char(i + 48) + ".txt";
			Sleep(500);
			handle.drawGraphic(pos.x, pos.y, fileName);
		}
		Sleep(1000);
		handle.eraseGraphic(pos.x, pos.y, 5, 9);
	}
	void tell()
	{
		PlaySound(TEXT("sound/moving.wav"), NULL, SND_FILENAME);
	}
};