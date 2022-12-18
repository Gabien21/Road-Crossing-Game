#include "CVehicle.h"

CVehicle::CVehicle()
{
	pos.x = 0;
	pos.y = 0;
	direction = 1;
}
CVehicle::CVehicle(int x, int y)
{
	pos.x = x;
	pos.y = y;
	direction = 1;
}
Point CVehicle::getPos() const
{
	return pos;
}
void CVehicle::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}
bool CVehicle::getDirection() const
{
	return direction;
}
void CVehicle::setDirection(bool direc)
{
	this->direction = direc;
}
void CVehicle::Move(TrafficLight lightList)
{
	if (lightList.getStatus() == "Light-2.txt")
		return;
	pos.x++;
}
void CVehicle::deleteVehicle(ConsoleHandle& handle, TrafficLight lightList)
{
	if (pos.x == 162)
	{
		handle.eraseGraphic(pos.x - 1, pos.y, getHeight(), getLength() + 1, 0, 32, 162);
		return;
	}
	handle.eraseGraphic(pos.x - 1, pos.y, getHeight(), 1, 0, 33, 162);
}