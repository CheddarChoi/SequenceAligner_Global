#include "Cell.h"

Cell::Cell()
{
	score = 0;
	for (int i=0;i<3;i++){
		flg[i] = false;
	}
}

void Cell::set_scoreflag(int s, bool* f)
{
	score = s;
	for (int i=0;i<3;i++){
		flg[i] = f[i];
	}
}

int Cell::obtain_score()
{
	return score;
}

bool* Cell::obtain_flag()
{
	return flg;
}


