#include <stdio.h>
#include "player.h"

void PrintPlayer(Player Selected)
{
	PrintKata(Selected.name);
	printf("'s Turn\n");
	printf("Cash: %dG | Income : %dG | Upkeep: %dG\n", Selected.gold, Selected.income, Selected.upkeep);
}