#include "DPmat.h"
#include "string.h"
#include "algorithm"

////////////////////////// A   T   G   C
int scoring_mat[4][4] = {{ 5, -1, -2, -1},
						 {-1,  5, -2, -2},
						 {-2, -2,  5, -3},
						 {-1, -2, -3,  5}};

DPmat::DPmat(){}
DPmat::DPmat(char* input_x, char* input_y)
{
	int i;

	LEN_OF_X = strlen(input_x);
	LEN_OF_Y = strlen(input_y);

	x = new int[LEN_OF_X];
	for(i = 0; i < LEN_OF_X; i++){
		x[i] = chr2int(input_x[i]);
	}

	y = new int[LEN_OF_Y];
	z = new int[LEN_OF_Y];
	for(i = 0; i < LEN_OF_Y; i++){
		y[i] = chr2int(input_y[i]);
		z[i] = 0;
	}

	mat = new Cell* [LEN_OF_X+1];
	for (i = 0; i < LEN_OF_X+1; i++){
		mat[i] = new Cell[LEN_OF_Y+1];
	}

}

int DPmat::chr2int(char chr)
{
	if      ((chr == 'A')||(chr == 'a')) return 1;
	else if ((chr == 'T')||(chr == 't')) return 2;
	else if ((chr == 'G')||(chr == 'g')) return 3;
	else if ((chr == 'C')||(chr == 'c')) return 4;
	else
	{
		cout << "Input Error! NOT valid character(A,T,G,C)" << endl;
		exit(0);
	}
}
char DPmat::int2chr(int num)
{
	if      (num == 0) return '-';
	else if (num == 1) return 'A';
	else if (num == 2) return 'T';
	else if (num == 3) return 'G';
	else if (num == 4) return 'C';
	else
	{
		cout << "Output Error! NOT valid number(0,1,2,3,4)" << endl;
		exit(0);
	}

}
void DPmat::print_z_chr()
{
    // print z (A, T, G, C, -)
    // print score of mat[LEN_OF_X][LEN_OF_Y]

	char output_z[LEN_OF_Y];
	for(int i = 0; i < LEN_OF_Y; i++){
		output_z[i] = int2chr(z[i]);
	}
	output_z[LEN_OF_Y] = '\0';
	cout<<"z: "<<output_z<<"\t"<<"Score : "<<mat[LEN_OF_X][LEN_OF_Y].obtain_score()<<endl;
}

void DPmat::print_mat()
{
	cout << "<< score & flag of matrix>>"<< endl;
	int score;
	bool* flg;
	for(int i=0;i<LEN_OF_X+1;i++){
		for(int j=0;j<LEN_OF_Y+1;j++){
			score = mat[i][j].obtain_score();
			flg = mat[i][j].obtain_flag();
			cout << "[";
			for (int k=0; k<3; k++)
			{
				cout << flg[k] <<" ";
			}
			cout << score <<"]"<<"\t";
		}
		cout << "\n";
	}
	cout << endl;

}

void DPmat::fill_in_DPmat()
{

	// Initialize the first row and the first column of DPmat and fill in the remaining cells of DPmat with a score(S(i,j)) and a direction(flg(i,j))
	// To get a score(S(i,j)) and a direction(flg(i,j)) of a cell[i,j], perform following steps
	// 1st step: calculate three scores(S(i-1, j-1) + s(i,j), S(i-1,j)-6, S(i,j-1)-6)
	// 2nd step: compare three scores and take the highest one
	// 3rd step: save the highest score as score(S(i,j)) and its direction
	int score[3];
	bool find;
	int max_index;
	bool temp[3] = {0,0,1};

	for (int i=1;i<LEN_OF_X+1;i++){
		mat[i][0].set_scoreflag(-6*i, temp);
	}
	temp[0] = 1;
	temp[2] = 0;
	for (int j=1;j<LEN_OF_Y+1;j++){
		mat[0][j].set_scoreflag(-6*j, temp);
	}

	for (int i=1;i<LEN_OF_X+1;i++){
		for (int j=1;j<LEN_OF_Y+1;j++){
			bool temp[3] = {0,0,0};

			score[0] = mat[i][j-1].obtain_score()-6;
			score[1] = mat[i-1][j-1].obtain_score() + scoring_mat[x[i-1]-1][y[j-1]-1];
			score[2] = mat[i-1][j].obtain_score()-6;

			if(score[0]>=score[1] && score[0]>=score[2]){
				temp[0]=true; 
				max_index = 0;}
			if(score[1]>=score[0] && score[1]>=score[2]){
				temp[1]=true; 
				max_index = 1;}
			if(score[2]>=score[0] && score[2]>=score[1]){
				temp[2]=true; 
				max_index = 2;}
			mat[i][j].set_scoreflag(score[max_index],temp);
		}
	}
}

void DPmat::trace_back(int trace_back_i, int trace_back_j, int trace_back_cnt)
{

	// trace back the direction from mat[LEN_OF_X][LEN_OF_Y] by recursive process
	// modify z while tracing
	// print z and score of mat[LEN_OF_X][LEN_OF_Y] at the end of tracing using function 'DPmat::print_z_chr()'
	if(trace_back_cnt==-1){
		print_z_chr();
		return;
	}

	bool* current_flag = mat[trace_back_i][trace_back_j].obtain_flag();
	if(current_flag[0]){ 
		z[trace_back_cnt] = 0;
		trace_back(trace_back_i,trace_back_j-1,trace_back_cnt-1);
	}
	if(current_flag[1]){
		z[trace_back_cnt] = x[trace_back_i-1];
		trace_back(trace_back_i-1,trace_back_j-1,trace_back_cnt-1);
	}
	if(current_flag[2]){
		z[trace_back_cnt] = 0;
		trace_back(trace_back_i-1,trace_back_j,trace_back_cnt-1);
	}
}

DPmat::~DPmat()
{
	delete [] x;
	delete [] y;
	delete [] z;

	for(int i = 0; i<LEN_OF_X+1; i++) {
		delete [] mat[i];
	}
	delete [] mat;

}



