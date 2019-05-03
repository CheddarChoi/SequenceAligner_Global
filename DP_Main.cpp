#include "Cell.h"
#include "DPmat.h"

int main()
{
	//char seq_x[] = "TGCTCA";
	//char seq_y[] = "TGCTCGTA";
	//char seq_x[] = "TTCCG";
	//char seq_y[] = "TAACTCG";
	char seq_y[] = "ATGACCGTAATAGGT";
	char seq_x[] = "AACCTTGTCT";

	DPmat SA(seq_x,seq_y);
	SA.fill_in_DPmat();

	SA.print_mat();
	cout<<"y: "<<seq_y<<endl;
    cout<<"x: "<<seq_x<<endl<<endl;

	SA.trace_back(SA.get_LEN_X(), SA.get_LEN_Y(), SA.get_LEN_Y()-1);
	return 0;
}




