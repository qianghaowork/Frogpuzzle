// FrogsAndToads.cpp : Defines the entry point for the console application.

/*----------------------Frog and Toad Puzzle----------------------------*/
/* Algorithm Description                                                */
/* For a valid input containing M 'F'('f') and N 'T'('t') and only 
   one '_', destination string is 'N('T')_M('F')'. The goal is to get the 
   minimum jumps from input to destination string and each jump can only
   move one step or two steps respectively for 'F' and 'T' in their directions.
   The problem can be regarded as a tree and to find the depth from root
   to a certain leaf. Therefore, a BFS algorithm is applied. A queue including
   available strings and empty stone positions is maintained and this iterative
   method ss better than recursive one. If the destination string is acheived,
   return the number of depths which is the minimum jumps.

/* Test cases
/* (1) FrogsAndToads.exe 
       Need an input.
    (2) FrogsAndToads.exe FG_F a314
	   Too many inputs.
    (3) FrogsAndToads.exe FTF_F_T
	   Input is not valid.
	(4) FrogsAndToads.exe F_T
	   3
	(5) FrogsAndToads.exe _FFT
	   Not solvable
	(6) FrogsAndToads.exe FF_TT
	   8
	(7) For M 'F' and M 'T', if 'F' at the leftmost and 'T' at the rightmost,
	the minium jumps is (M+1)^2-1
	(8) There could be only 'F' or 'T', program could also return minimum jumps
	   FrogsAndToads.exe FF_
	   1
	   FrogsAndToads.exe T_T
	   1
	(8) If 'T' are at rightmost and 'F' at the leftmost, no jump 
	   FrogsAndToads.exe TT_FF
	   0
/*----------------------------------------------------------------------*/

#include "stdafx.h"
#include <vector>
#include <string> 
#include <queue>
#include <iostream>
#include <algorithm> 

using namespace std;

class FrogPuzzle{
	int frog; // number of frogs
	int toad; // number of toads
	int emptypos;  // empty stone position
	int len;  // total stone numbers = frog+toad+1
	string start; // Input string
	string end;   // Destination string

	vector<pair<string,int> > findpath(const pair<string,int> &node); // function to find all possible move paths of current instance 

public: 
	FrogPuzzle (const char* s) {
		start = s;
		frog = 0;
		toad = 0;
		emptypos = -1;
		len = start.length();
		end = "";
	}
	bool isValidInput();
	int findminjumps();
};

vector<pair<string,int> > FrogPuzzle::findpath(const pair<string,int> &node){
	vector<pair<string,int> > res;  // return all possible move paths of a certain node

	string str = node.first;
	int pos = node.second;
	
	string nstr = str;
	if (pos>0 && str[pos-1]=='F') {
		nstr[pos] = 'F';
		nstr[pos-1] = '_';
		res.push_back( pair<string,int>(nstr, pos-1) );
	}

	nstr = str;
	if (pos<len-1 && str[pos+1]=='T') {
		nstr[pos] = 'T';
		nstr[pos+1] = '_';
		res.push_back( pair<string,int>(nstr, pos+1) );
	}

	nstr = str;
	if (pos>1 && str[pos-2] =='F') {
		nstr[pos] = 'F';
		nstr[pos-2] = '_';
		res.push_back( pair<string,int>(nstr, pos-2) );
	}

	nstr = str;
	if (pos<len-2 && str[pos+2]=='T') {
		nstr[pos] = 'T';
		nstr[pos+2] = '_';
		res.push_back( pair<string,int>(nstr, pos+2) );
	}
	
	return res;
};

bool FrogPuzzle::isValidInput(){
	transform(start.begin(), start.end(), start.begin(), toupper);
	emptypos = start.find('_');

	frog = count(start.begin(), start.end(), 'F');
	toad = count(start.begin(), start.end(), 'T');

	end = string( toad, 'T') + '_' + string(frog, 'F');

    return len==frog+toad+1;
}

/*bool FrogPuzzle::isValidInput(){
	for(int i=0; i<len; i++)
	{
		if (start[i]=='F' || start[i]=='f') 
		{
			frog++;
			start[i] = 'F';
		}
		else if (start[i]=='T' || start[i]=='t')
		{
			toad++;
			start[i] = 'T';
		}
		else if (start[i]=='_')
		{
			if (emptypos==-1)
				emptypos = i;
			else
				return false;
		}
		else
			return false;
	}

	end = string( toad, 'T') + '_' + string(frog, 'F');

	return true;
}*/

int FrogPuzzle::findminjumps(){
	int jumps = 0;

	if (start==end)
		return 0;

	queue<pair<string,int> > goodnode;  // store all valid strings and empty stone positions.
	goodnode.push(pair<string,int>(start,emptypos) ); 
	int curnum = 1;  // curnum denotes numbers of nodes in current level
	int nextnum = 0;  // nextnum denotes numbers of nodes in next level
	
	while(!goodnode.empty()) {
		while ( curnum>0 ) {
	        pair<string,int> curnode = goodnode.front();
	        goodnode.pop();
			
			vector< pair<string,int> > possiblenodes = findpath(curnode);
			for(auto it=possiblenodes.begin(); it!=possiblenodes.end(); it++) 
			{
				if ( it->first == end)
					return jumps+1;

				goodnode.push(*it);
				nextnum++;
			}			   
			curnum--;
		}

		if(curnum==0 && nextnum>0){
			curnum = nextnum;
			nextnum = 0;
			jumps++;
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	if (argc==1) {
		cout << "Need an input." << endl;
	}
	else if (argc>2) {
		cout << "Too many inputs." << endl;
	}
	else
	{
		FrogPuzzle puzzle(argv[1]);
		if ( !puzzle.isValidInput() )
			cout << "Input is not valid." << endl;
		else
		{
			int minjumps = puzzle.findminjumps();
			if (minjumps>=0)
				cout << minjumps << endl;
			else
				cout << "Not solvable" << endl;
		}
	}

//	getchar();
	return 0;
}

