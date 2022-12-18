#include "CTruck.h"

CTruck::CTruck() : CVehicle(0, 0) {
	this->height = 4;
	this->length = 19;
}
CTruck::CTruck(int x, int y) : CVehicle(x, y)
{
	this->height = 4;
	this->length = 19;
}
CTruck::CTruck(const CTruck& truck)
{
	this->height = 4;
	this->length = 19;
	this->pos = truck.pos;
	this->direction = truck.direction;
}
int CTruck::getLength() const
{
	return length;
}
int CTruck::getHeight() const
{
	return height;
}
void CTruck::Tell()
{
	PlaySound(TEXT("sound/truck.wav"), NULL, SND_FILENAME);
}
void CTruck::drawTruck(ConsoleHandle& handle)
{
	handle.updateObstacle(pos.x, pos.y, "TruckTexture.txt", 2, 33, 162);
}
vector<Point> CTruck::getPointList() const
{
	ifstream op;
	op.open("TruckTexture.txt");
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