#include "CGame.h"

ConsoleHandle handle;
CGame* cg;

int main()
{
	CGame* cg = new CGame(handle);
	cg->gameMenu();
	return 0;
}