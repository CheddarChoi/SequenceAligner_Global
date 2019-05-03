#include <iostream>
#include <stdlib.h>

using namespace std;

#ifndef __CELL_H__
#define __CELL_H__

class Cell
{
public:
	Cell();
	void set_scoreflag(int s, bool* f);
	int obtain_score();
	bool* obtain_flag();

private:
	int score;
	bool flg[3];

};

#endif

