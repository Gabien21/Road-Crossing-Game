#include "CCar.h"

CCar::CCar() : CVehicle(0, 0)
{
	this->length = 21;
	this->height = 4;
	direction = 1;
}
CCar::CCar(int x, int y) : CVehicle(x, y)
{
	this->height = 4;
	this->length = 21;
	direction = 1;
}
CCar::CCar(const CCar& car)
{
	this->height = 4;
	this->length = 21;
	this->pos = car.pos;
	this->direction = car.direction;
}
int CCar::getLength() const
{
	return length;
}
int CCar::getHeight() const
{
	return height;
}
void CCar::Tell()
{
	PlaySound(TEXT("sound/bird.wav"), NULL, SND_FILENAME);
}
void CCar::drawCar(ConsoleHandle& handle)
{
	handle.updateObstacle(pos.x, pos.y, "CarTexture.txt", 1, 33, 162);
}
vector<Point> CCar::getPointList() const
{
	ifstream op;
	op.open("CarTexture.txt");
	vector<string> line;
	string tmp;
	while (getline(op, tmp))
		line.push_back(tmp);
	op.close();
	vector<Point> x;
	for (int i = 0; i < line.size(); i++)
		for (int j = 0; j < line[i].length(); j++)
		{
			if (i == 0 || i == line.size() - 1)
			{
				if (line[i][j] != ' ')
				{
					Point tmp(j, i);
					x.push_back(tmp);
				}
			}
			else if (line[i][j] != ' ')
			{
				int k = line[i].size() - 1;
				for (; k > j; k--)
					if (line[i][j] != ' ')
						break;
				for (int t = j; t <= k; t++)
				{
					Point tmp1(t, i);
					x.push_back(tmp1);
				}
				break;
			}
		}
	return x;
}