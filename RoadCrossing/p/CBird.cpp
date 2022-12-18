#include "CBird.h"

CBird::CBird() : CAnimal(0, 0) {
	this->length = 12;
	this->height = 6;
}
CBird::CBird(int x, int y) : CAnimal(x, y)
{
	this->height = 6;
	this->length = 12;
}
CBird::CBird(const CBird& car)
{
	this->height = 6;
	this->length = 12;
	this->pos = car.pos;
	this->direction = car.direction;
}
int CBird::getLength() const
{
	return length;
}
int CBird::getHeight() const
{
	return height;
}
void CBird::Tell()
{
	PlaySound(TEXT("sound/bird.wav"), NULL, SND_FILENAME);
}
void CBird::drawBird(ConsoleHandle& handle)
{
	handle.updateObstacle(pos.x, pos.y, "BirdTexture.txt", 6, 33, 162);
}
vector<Point> CBird::getPointList() const
{
	ifstream op;
	op.open("BirdTexture.txt");
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