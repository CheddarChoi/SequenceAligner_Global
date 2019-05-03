#include <iostream>
#include <stdlib.h>
#include "Cell.h"

using namespace std;

#ifndef __DPMAT_H__
#define __DPMAT_H__

class DPmat
{
public:
	DPmat();
	DPmat(char* input_x, char* input_y);
	void print_z_chr();
	void fill_in_DPmat();
	void print_mat();
	void trace_back(int trace_back_i, int trace_back_j, int trace_back_cnt);
	int chr2int(char chr);
	char int2chr(int num);

	int get_LEN_X(){ return LEN_OF_X; }
	int get_LEN_Y(){ return LEN_OF_Y; }

	~DPmat();

private:
	int* x;
	int* y;
	int* z;

	int LEN_OF_X;
	int LEN_OF_Y;

	Cell** mat;

};

#endif

