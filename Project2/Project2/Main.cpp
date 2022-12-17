#include "CGame.h"

ConsoleHandle handle;
CGame *cg;
char MOVING;



int main()
{	
	CGame* cg = new CGame();
	cg->gameMenu(handle);
    return 0;
}