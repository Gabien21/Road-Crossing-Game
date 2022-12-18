#include "CDinausor.h"

CDinausor::CDinausor() : CAnimal(0, 0) {
	this->height = 6;
	this->length = 18;
}
CDinausor::CDinausor(int x, int y) : CAnimal(x, y)
{
	this->height = 6;
	this->length = 18;
}
CDinausor::CDinausor(const CDinausor& truck)
{
	this->height = 6;
	this->length = 18;
	this->pos = truck.pos;
	this->direction = truck.direction;
}
int CDinausor::getLength() const
{
	return length;
}
int CDinausor::getHeight() const
{
	return height;
}
void CDinausor::Tell()
{
	PlaySound(TEXT("sound/dinausor.wav"), NULL, SND_FILENAME);
}
void CDinausor::drawDinausor(ConsoleHandle& handle)
{
	handle.updateObstacle(pos.x, pos.y, "DinausorTexture.txt", 5, 33, 162);
}
vector<Point> CDinausor::getPointList() const
{
	ifstream op;
	op.open("DinausorTexture.txt");
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