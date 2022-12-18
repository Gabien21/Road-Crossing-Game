#include "CGame.h"

ConsoleHandle handle;
CGame* cg;

int main()
{
	CGame* cg = new CGame();
	cg->gameMenu(handle);
	return 0;
}