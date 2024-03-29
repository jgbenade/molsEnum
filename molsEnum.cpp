#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <time.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

typedef list<int> permutation ;
typedef list<permutation> lsquare;
int main(int argc,char *argv[]);

class MOLS {
public:
	typedef list<int> permutation ;
	typedef list<permutation> lsquare;
	MOLS(int n, int k) ;
	MOLS( std::string filename);
	~MOLS();
	int enumerateMOLS(void);
	struct My
	{
	    static bool permutationComparator    (permutation p1, permutation    p2);
	};






private:
	int n;
	int k;
	vector<lsquare> partMOLS;
	vector<lsquare> tempMOLS;
	vector<vector<vector<int> > > currLS;
	list<permutation> cycleStructureReps;
	//list<vector <lsquare> > completedMOLS;
	vector<vector<vector<vector<int> > > > symbSqRC;
	int currSquare;
	int count_MOLS;
	vector<int> branchCount_  ;
	bool printOut;
	list<permutation> possibleShuffles;
	vector<int> currentCS;
	string filename;

	int printUniversals(lsquare &);
	void printPerm(permutation );
	void printLS(lsquare &l);
	void printMOLSPerms( vector<lsquare> mols   );
	void printMOLS( vector<lsquare> mols  );
	bool isOrthogonal(permutation perm);
	permutation composition(permutation p1, permutation p2);
	permutation inverse(permutation p);
	permutation copyPerm(permutation p);
	permutation rcs(permutation p1, permutation p2);
	void permuteSymbols(vector<lsquare> partMOLS , vector<lsquare> &newMOLS );
	void permuteMOLS(vector<lsquare> partMOLS , permutation rowPerm, permutation colPerm, vector<lsquare> &newMOLS );
	void permuteMOLSRCS(vector<lsquare> partMOLS , permutation rowPerm, permutation colPerm, vector<lsquare> newMOLS );
	void testpermuteMOLS(vector<lsquare> partMOLS , permutation rowPerm, permutation colPerm, vector<lsquare> newMOLS , vector<lsquare> newpMOLS);
	void printOA(vector<vector<int> > OA);
	bool  comparePartialMOLS(vector<lsquare> partMOLS1, vector<lsquare> partMOLS2);
	void  MOLStoOA(vector<lsquare> partMOLS , vector<vector<int> > OA) ;
	void  OAtoMOLS(vector<vector<int> > OA , vector<lsquare> newMOLS  ) ;
	void  permuteOA(vector<vector<int> > OA , int p[],vector<vector<int> > OANew ) ;
	void  getSmallest(vector<lsquare> partMOLS, vector<lsquare> newMOLS ) ;
	void  transposeMOLS(vector<lsquare> partMOLS, vector<lsquare> &newMOLS) ;
	permutation  CSToPerm(vector<int> curr) ;
	void  genCRS(vector<int> curr , int ctr, int rem) ;
	void  getCycleStructure(permutation p, vector<int>  &nofCycles, map<int, list<list<int> > > &cycleLength_cycles_map ) ;
	list<permutation>  genRelevantPermutations(permutation p ) ;
	bool  isIdentity(permutation p) ;
//	bool  isSmallestPermSymbols(lsquare ls, int nofPerms) ;
	void  changeOrder(vector<lsquare> partMOLS, vector<int> order , vector<lsquare> &newMOLS) ;
	void  changeOrder(vector<lsquare> partMOLS, int first, int second , vector<lsquare> &newMOLS) ;
	void  rollUp(vector<lsquare> partMOLS,  int pos,  permutation origP, vector<lsquare> &newMOLS) ;
	void  standardForm(vector<lsquare> partMOLS, int rowUp, int pos ,permutation origP, vector<lsquare> &newMOLS) ;
	vector<int>  rowMeets(permutation p1, permutation p2) ;
	int  compareCS(permutation p , vector<int> targetCS) ;
	list<permutation>  getShuffles(permutation pOrig, permutation pNow) ;
	bool  noSmallerRCS(permutation smallestRCS ) ;
	bool  noSmallerRCS(permutation smallestRCS, vector<lsquare> pMOLS ) ;
	bool  isSmallest5(vector<lsquare> partMOLS,vector<lsquare> origMOLS, list<permutation> &testPerm) ;
	bool  isSmallest4() ;
	bool  isSmallestConjugateMOLS(vector<lsquare> partMOLS) ;
	bool  checkFit( permutation p) ;
	bool  checkOrthogonal(permutation P) ;
	bool  checkRCS(permutation P) ;
	void  printDots(int cursquare, int size, int k) ;
	void  printDots(int num) ;
	void  buildPossibleSquare( vector<vector<int> > &square ) ;
	void  generatePossiblePermsToInsertRec(vector<vector<int> > &square, permutation p, int row,  list<permutation> &possiblePermList ) ;
	void  generatePossiblePermsToInsert(  list<permutation> &possiblePermList ) ;
	void  findMOLS4() ;
	void buildCurrentLS();
	list<vector<int> >  getSmallRelCS( vector<lsquare> pMOLS, list<permutation> &listP);
	void removeUniversal(permutation p	);
	void addUniversal(permutation p	);
	void removeFromLS(permutation p);
	void addToLS();
	void generatePossiblePermsLSRec(permutation p, int row,  list<permutation> &possiblePermList );
	std::vector<std::string> & split(const std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<std::string>   split(const std::string &s, char delim );
	permutation  strtoPerm(string s);
	void updateLS();

} ;

bool MOLS::My::permutationComparator    (permutation p1, permutation    p2) { return p1.front() < p2.front(); }

MOLS::~MOLS(){}

MOLS::MOLS( int n, int k){
	printOut = true;
	this->n = n;
	this->k = k;
	currSquare = 0;
 	count_MOLS = 0;
	branchCount_.resize(n*k, 0);
	currentCS.resize(n+1, 0);

	//partMOLS(k, list<permutation>(n, list<int>(n, sizeof(int))));
	//tempMOLS(k, list<permutation>(n, list<int>(n, sizeof(int))));

	int i,j, ii ;
	for (i =0; i<k; i++){
		lsquare l1, l2;
		partMOLS.push_back(l1);
		tempMOLS.push_back(l2);
	}
	//Get cycle structure representatives for U_0^1
	vector<int> cycles(n+1, 0);
	cycles[1] =1;
	genCRS(cycles, 2, n-1);
	list<permutation>::const_iterator CSRit;

	if (printOut){
		cout << "u0^1 list has "<< cycleStructureReps.size()<< " universals - ";
		for (CSRit=cycleStructureReps.begin(); CSRit!= cycleStructureReps.end(); ++CSRit){
			printPerm(*CSRit);
		}
		cout<<endl;
	}

	//Initialize currLS
	currLS.resize(k, vector<vector<int> > (n , vector<int>(n, this->n)));

	//Initialise symbSqRC
	symbSqRC.resize(n, vector<vector<vector<int> > >(k, vector<vector<int> >(n, vector<int>(n, 1))));
	//completedMOLS.clear();


	return;
}

std::vector<std::string> & MOLS::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> MOLS::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

permutation MOLS::strtoPerm(string s){
	int i;
	permutation p;
	for(i=0; i<s.length(); i++){
		p.push_back(  s[i]-'0');
	}
	return p;
}

MOLS::MOLS( string filename){
	cout<< "Enter"<<endl;
	//this->filename = filename;
	printOut = true;
	/*this->n = 5;
	this->k = 3;
	currSquare = 0;
	count_MOLS = 0;
	branchCount_[100] = {0} ;*/
	cout<< "setrandvar"<<endl;
	int i;
	string s;
	ifstream infile;
	infile.open(filename.c_str(), ios::in );
	cout<< "fileopening"<<endl;

	 if (infile.is_open())
	  {
		 if  ( infile.good() ){
			 getline (infile,s);
			 vector<string> vec = split(s,' ');
			 n =  vec[0][0]- '0';
			 k = vec[1][0] - '0';
			 int i,j, ii ;
			 	for (i =0; i<k; i++){
			 		lsquare l1, l2;
			 		partMOLS.push_back(l1);
			 		tempMOLS.push_back(l2);
			 	}
		 }

		 cout<< "fileopen"<<endl;
	    while ( infile.good() )
	    {
	      getline (infile,s);
	      vector<string> vec = split(s,' ');
	      int numUni = vec.size();
	      if (numUni>0){
	    	  for (i=0; i< numUni; i++){
	    		  partMOLS[i].push_back(strtoPerm(vec[i]));
	    	  }
	    	  currSquare = numUni%k;
	      }

	    }
	    infile.close();
	  }
	 else
		 cout<< "File not found"<<endl;

	printMOLSPerms(partMOLS);

	count_MOLS = 0;
	branchCount_.resize(n*k, 0);
	currentCS.resize(n+1, 0);

	//Get cycle structure representatives for U_0^1
	vector<int> cycles(n+1, 0);
	cycles[1] =1;
	genCRS(cycles, 2, n-1);
	list<permutation>::const_iterator CSRit;
	if (printOut){
		cout << "u0^1 list has "<< cycleStructureReps.size()<< " universals - ";
		for (CSRit=cycleStructureReps.begin(); CSRit!= cycleStructureReps.end(); ++CSRit){
			printPerm(*CSRit);
		}
		cout<<endl;
	}

	//Initialize currLS
	//currLS.resize(k, vector<vector<int> > (n , vector<int>(n, -1)));
	updateLS();

	//Initialise symbSqRC
	symbSqRC.resize(n, vector<vector<vector<int> > >(k, vector<vector<int> >(n, vector<int>(n, 1))));
	//completedMOLS.clear();




	return;
}

void MOLS::updateLS(){
	currLS.resize(k, vector<vector<int> > (n , vector<int>(n, n)));

	list<list<int> >::iterator universalIt; //iterates over universals
	list<int>::iterator perm_it; //iterates over permutation
	int uni_ctr=0, row_ctr=0, i;
	for (i=0; i<k; i++){
		uni_ctr=0;
		for(universalIt=partMOLS[i].begin(); universalIt != partMOLS[i].end(); ++universalIt){
			for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
				currLS[i][row_ctr][*perm_it] = uni_ctr;
				row_ctr++;
			}
			row_ctr=0;
			uni_ctr++;
		}
	}

}

int MOLS::enumerateMOLS(void	){
/*	string outfile = filename+ ".out.txt";
	std::ofstream out(outfile);
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf());*/

	clock_t t;
	t = clock();
	cout<<   k << " MOLS of order "<< n<<endl;

	int i;
	count_MOLS =0;

	if (partMOLS[0].size()==0){
		permutation ss;
		for (i=0;i<n; i++){
			ss.push_back(i);
		}
		addUniversal(copyPerm(ss));
		currSquare++;
	}
	else{
		if (partMOLS[1].size()>0){
			map<int, list<list<int> > > dummy_cycles_map;
			getCycleStructure(partMOLS[1].front(),  currentCS, dummy_cycles_map );
		}
	}

	findMOLS4();

	cout<< count_MOLS << " MOLS found"<<endl;

	for (i=0; i<n*k;i++)
		cout<<branchCount_[i]<<" ";
	cout<<endl;
	for (i=0; i< n; i++){
		cout<< branchCount_[k-1 +i*k] <<" takke op vlak "<<i<<endl;
	}

	t = clock() - t;
	cout<<  t/1000000.0 << " seconds"<< endl;

	return count_MOLS;

}

int MOLS::printUniversals(lsquare& l){
	list<list<int> >::iterator universalIt; //iterates over universals
	list<int>::iterator perm_it; //iterates over permutation

	for(universalIt=l.begin(); universalIt != l.end(); ++universalIt){

		//list<int>& universalIt = *i;
		cout<<"< ";
		for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){

			cout<<*perm_it;
		}
		cout<<" >";
	}
	 return 0;
}

void MOLS::printPerm(permutation p){
	list<int>::iterator perm_it; //iterates over permutation
	cout<<" ";
	for(perm_it=p.begin(); perm_it != p.end(); ++perm_it){
		cout<<*perm_it;
	}
	cout<<" ";
}

void MOLS::printLS(list<list<int> >& l){
	//int n = l.front().size();
	vector<vector<int> >  L(n, vector<int>(n,0));
	int uni_ctr = 0, row_ctr = 0;
	int i,j;
	for ( i =0; i<n; i++){
		for ( j=0; j<n; j++){
			L[i][j]=-1;
		}
	}

	list<list<int> >::iterator universalIt; //iterates over universals
	list<int>::iterator perm_it; //iterates over permutation
	uni_ctr=0;
	for(universalIt=l.begin(); universalIt != l.end(); ++universalIt){
		for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
			L[row_ctr][*perm_it] = uni_ctr;
			row_ctr++;
		}
		row_ctr=0;
		uni_ctr++;
	}
	uni_ctr = 0;
	//int i,j;
	for ( i =0; i<n; i++){
		for ( j=0; j<n; j++){
			if (L[i][j]>= 0)
				//cout <<  L[i][j]   <<" "<< (j==n-1? "\\\\" : "& ");
				cout <<  L[i][j]   <<" ";
			else
				cout <<    "- ";
				//cout <<    "- "<< (j==n-1? "\\\\" : "& ");
		}
		cout<< endl;
	}
	cout<< endl;

}

void MOLS::printMOLSPerms( vector<lsquare> mols  ){
	//int k = mols;
	int m =0;
	cout << endl;
	//int n = mols[0].front().size();
	stringstream outp[k][n];
	for (m=0; m<k; m++){
		//if (mols[m].size()>0){

			vector<vector<int> >  L(n, vector<int>(n,0));
			int uni_ctr = 0, row_ctr = 0;
			int i,j;
			for ( i =0; i<n; i++){
				for ( j=0; j<n; j++){
					L[i][j]=-1;
				}
			}

			list<list<int> >::iterator universalIt; //iterates over universals
			list<int>::iterator perm_it; //iterates over permutation
			uni_ctr=0;
			for(universalIt=mols[m].begin(); universalIt != mols[m].end(); ++universalIt){
				for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
					//L[row_ctr][*perm_it] = uni_ctr;
					//row_ctr++;
					outp[m][uni_ctr] << *perm_it;
				}
				row_ctr=0;
				uni_ctr++;
			}

		//}
		//else cout<< "Empty"<< endl;
	}
	int i=0, j=0;
	for ( i =0; i<n; i++){
		for ( j =0; j<k; j++){
			cout<<outp[j][i].str()<<"\t";
		}
		cout<<endl;
	}
}

void MOLS::printMOLS( vector<lsquare> mols  ){
	int m;stringstream outp[k][n];
	for (m=0; m<k; m++){
			//if (mols[m].size()>0){

				int i,j;
				for ( i =0; i<n; i++){
					for ( j=0; j<n; j++){
						if (currLS[m][i][j]>=  0 )
							//cout <<  L[i][j]   <<" "<< (j==n-1? "\\\\" : "& ");
							outp[m][i]<<currLS[m][i][j]<<" ";
						else
							outp[m][i]<<  "- ";
						//cout <<    "- "<< (j==n-1? "\\\\" : "& ");
					}

				}
			//}
			//else cout<< "Empty"<< endl;
		}
		int i=0, j=0;
		for ( i =0; i<n; i++){
			for ( j =0; j<k; j++){
				cout<<outp[j][i].str()<<"\t";
			}
			cout<<endl;
		}


		//////////

	/*//int k = mols;
	int m =0;
	cout << endl;
	//int n = mols[0].front().size();
	stringstream outp[k][n];
	for (m=0; m<k; m++){
		//if (mols[m].size()>0){

			int L[n][n];
			int uni_ctr = 0, row_ctr = 0;
			int i,j;
			for ( i =0; i<n; i++){
				for ( j=0; j<n; j++){
					L[i][j]=-1;
				}
			}

			list<list<int> >::iterator universalIt; //iterates over universals
			list<int>::iterator perm_it; //iterates over permutation
			uni_ctr=0;
			for(universalIt=mols[m].begin(); universalIt != mols[m].end(); ++universalIt){
				for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
					L[row_ctr][*perm_it] = uni_ctr;
					row_ctr++;
				}
				row_ctr=0;
				uni_ctr++;
			}
			uni_ctr = 0;
			//int i,j;
			for ( i =0; i<n; i++){
				for ( j=0; j<n; j++){
					if (L[i][j]>=  0 )
						//cout <<  L[i][j]   <<" "<< (j==n-1? "\\\\" : "& ");
						outp[m][i]<<L[i][j]<<" ";
					else
						outp[m][i]<<  "- ";
					//cout <<    "- "<< (j==n-1? "\\\\" : "& ");
				}

			}
		//}
		//else cout<< "Empty"<< endl;
	}
	int i=0, j=0;
	for ( i =0; i<n; i++){
		for ( j =0; j<k; j++){
			cout<<outp[j][i].str()<<"\t";
		}
		cout<<endl;
	}*/
}

/*is Orthogonal accepts a relative cycle structure in the form of
 * a permutation and checks wheter the two original permutations
 * are orthonal, ie, whether the rcs has exactly one fixed point.
 * Input: perm - the permutation of the relative cycle structure to be checked
 * Output: true if orthogonal (only one fixed point)
 */
 bool MOLS::isOrthogonal(permutation perm){
	list<int>::iterator perm_it; //iterates over permutation
	int row_ctr=0,fixed_ctr = 0;
	for(perm_it=perm.begin(); perm_it != perm.end(); ++perm_it){
		if (*perm_it == row_ctr) fixed_ctr++;
		row_ctr++;
	}

	if (fixed_ctr==1)
		return true;
	else
		return false;
}

permutation MOLS::composition(permutation p1, permutation p2){
//TODO test whether permutations are of same length

	list<int>::iterator perm1_it; //iterates over p1
	list<int>::iterator perm2_it; //iterates over p2

	perm1_it = p1.begin();
	perm2_it = p2.begin();

	//int n = p1.size();
	int p1arr[n];
	int permarr[n];

	int current = 0;
	for(perm1_it=p1.begin(); perm1_it != p1.end(); ++perm1_it){
		p1arr[current] = *perm1_it;
		current++;
	}

	permutation composite ; //= {0,0,0,0};

	for(perm2_it=p2.begin(); perm2_it != p2.end(); ++perm2_it){
		composite.push_back(p1arr[*perm2_it]);
	}

//	int ctr = 0;
//	for (perm2_it=composite.begin(); perm2_it != composite.end(); ++perm2_it){
//		cout<<*perm2_it<<" "<<ctr++<< endl;
//	}

	return composite;
}

permutation MOLS::inverse(permutation p){
	int perm[p.size()];

	list<int>::iterator perm_it; //iterates over p1
	int ctr = 0;
	for (perm_it=p.begin(); perm_it != p.end(); ++perm_it){
		perm[*perm_it] = ctr++;
	}

	permutation inverse;
	int i=0;
	for (i=0; i<p.size(); i++){
		inverse.push_back(perm[i]);
	}
	//return arrToPerm(perm);
	return inverse;
}
permutation MOLS::copyPerm(permutation p){
	permutation::iterator pIt;
	permutation pNew ;
	for (pIt = p.begin(); pIt!=p.end(); ++pIt){
		pNew.push_back(*pIt);
	}

	return pNew;
}

permutation MOLS::rcs(permutation p1, permutation p2){
//TODO test whether permutations are of same length
	// actually just write the two permutations above each other and sort. has to be faster. although..nlogn
	return composition(p2, inverse(p1));
}

void MOLS::permuteSymbols(vector<lsquare> partMOLS, vector<lsquare> &newMOLS){
	int i;
	for (i =0;i<k;i++){
		newMOLS[i].clear();
		if (partMOLS[i].size()>0){ //if the square is still empty it cant be permuted

			lsquare::iterator permIt ;
			for (permIt = partMOLS[i].begin(); permIt != partMOLS[i].end(); ++permIt){
				newMOLS[i].push_back(*permIt);
				//TODO this was taken out in an attempt to make it slightly faster.
				//newMOLS[i].push_back(copyPerm(*permIt));
			}
			newMOLS[i].sort(My::permutationComparator);
		}
	}
	//TODO shuffle squares
}


void MOLS::permuteMOLS(vector<lsquare> pMOLS, permutation rowPerm, permutation colPerm, vector<lsquare> &newMOLS){

//void permuteMOLS(lsquare partMOLS[], permutation rowPerm, permutation colPerm){
	//int k=2;
	//lsquare* newList = (lsquare*)malloc(k*sizeof(lsquare));
	//newList[0] =
	int i=0;

	//permuteMOLS<2>()
	for (i=0; i<k; i++	){
		newMOLS[i].clear();
		if (pMOLS[i].size()>0){ //if the square is not empty (otherwise it cant be permuted)
			list<list<int> >::iterator universalIt; //iterates over universals
			list<int>::iterator perm_it; //iterates over permutation

			for(universalIt=pMOLS[i].begin(); universalIt != pMOLS[i].end(); ++universalIt){
				permutation p;
				//list<int>& universalIt = *i;
				for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
					p.push_back(*perm_it);
				}
				//newList[i].push_back(p);

				newMOLS[i].push_back(composition(composition(colPerm, p), inverse(rowPerm)) );
			}
		}
	}
	//permuteSymbols<k>(finalMOLS, newMOLS);

//	std::list<int> third (second.begin(),second.end());  // iterating through second
}

void MOLS::permuteMOLSRCS(vector<lsquare> partMOLS, permutation rowPerm, permutation colPerm, vector<lsquare> newMOLS){
//void permuteMOLS(lsquare partMOLS[], permutation rowPerm, permutation colPerm){
	//int k=2;
	//lsquare* newList = (lsquare*)malloc(k*sizeof(lsquare));
	//newList[0] =
	int i=0;
	lsquare finalMOLS[k];
	//permuteMOLS<2>()
	for (i=0; i<k; i++	){
		if (partMOLS[i].size()>0){ //if the square is not empty (otherwise it cant be permuted)

			list<list<int> >::iterator universalIt; //iterates over universals
			list<int>::iterator perm_it; //iterates over permutation

			for(universalIt=partMOLS[i].begin(); universalIt != partMOLS[i].end(); ++universalIt){
				permutation p;
				//list<int>& universalIt = *i;
				for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
					p.push_back(*perm_it);
				}
				//newList[i].push_back(p);
				newMOLS[i].push_back(composition(composition(colPerm, p), inverse(rowPerm)) );
			}
		}
	}

	/*cout<<"Before relabelling";
		printMOLS(finalMOLS, k);
		permuteSymbols<k>(finalMOLS, newMOLS);*/

//	std::list<int> third (second.begin(),second.end());  // iterating through second
}

void MOLS::testpermuteMOLS(vector<lsquare> partMOLS, permutation rowPerm, permutation colPerm, vector<lsquare> newMOLS, vector<lsquare> newpMOLS){
//void permuteMOLS(lsquare partMOLS[], permutation rowPerm, permutation colPerm){

	int i=0; permutation p1;
	lsquare finalMOLS[k];
	for (i=0; i<k; i++	){
		if (partMOLS[i].size()>0){ //if the square is not empty (otherwise it cant be permuted)

			list<list<int> >::iterator universalIt; //iterates over universals
			list<int>::iterator perm_it; //iterates over permutation
			p1 = partMOLS[i].back(); //only goind to permute the last one

			permutation p;
		//	printPerm(p1);

			for(perm_it=(p1).begin(); perm_it != (p1).end(); ++perm_it){
				p.push_back(*perm_it);
			}

		//	printPerm(p);
			newMOLS[i].push_back(p);
			newpMOLS[i].push_back(composition(colPerm, composition(p, inverse(rowPerm))) );

		}
	}
}



/*this is a working copy of permutesymbols before starting to permute only the last symbol
 * template<int k>
void permuteMOLS(lsquare partMOLS[k], permutation rowPerm, permutation colPerm, lsquare newMOLS[k]){
//void permuteMOLS(lsquare partMOLS[], permutation rowPerm, permutation colPerm){
	//int k=2;
	//lsquare* newList = (lsquare*)malloc(k*sizeof(lsquare));
	//newList[0] =
	int i=0;
	lsquare finalMOLS[k];
	//permuteMOLS<2>()
	for (i=0; i<k; i++	){
		if (partMOLS[i].size()>0){ //if the square is still empty it cant be permuted

			list<list<int> >::iterator universalIt; //iterates over universals
			list<int>::iterator perm_it; //iterates over permutation

			for(universalIt=partMOLS[i].begin(); universalIt != partMOLS[i].end(); ++universalIt){
				permutation p;
				//list<int>& universalIt = *i;
				for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
					p.push_back(*perm_it);
				}
				//newList[i].push_back(p);
				finalMOLS[i].push_back(composition(colPerm, composition(p, inverse(rowPerm))) );
			}
		}
	}

	permuteSymbols<k>(finalMOLS, newMOLS);

//	std::list<int> third (second.begin(),second.end());  // iterating through second
}*/

void MOLS::printOA(vector<vector<int> > OA){
	int i; int j; int w = n*n;
	cout << "ORTHOGONAL ARRAY"<< endl;
		for (i=0; i<k+2; i++){
			for (j=0; j<w; j++){
					cout<<	OA[i][j] << " ";
			}
			cout<< endl;
		}
}

//true if first is smaller or equal (weak ordering)
// this function has been tested and works with 1-mols and 2mols
//at the very least.  2 mols means by extension also with kmols
// 1 < 2 - TRUE
// 1 = 2 - TRUE
// 1 > 2 - FALSE
bool MOLS::comparePartialMOLS(vector<lsquare> partMOLS1, vector<lsquare> partMOLS2){
	lsquare::iterator permIt1[k];//arrays of iterators
	lsquare::iterator permIt2[k];
	int doneArr[k];
	int i=0;

	//doneArr keeps track of when the end of each array is reached to prevent the iterator from enumerating an array which is already on its end.
	for (i=0; i<k; i++){
		doneArr[i]=0;
	}

	int currSquare = 0;  //the number of the square currently being compared.
	for (currSquare =0; currSquare<k; currSquare++){
		//if the square is empty the iterator obv wont function properly
		//Assume for now that if one doesnt have anythiong in a square neither does the other, as they are permutations
		if (partMOLS1[currSquare].size()>0){
			permIt1[currSquare] = partMOLS1[currSquare].begin();
			permIt2[currSquare] = partMOLS2[currSquare].begin();
		}
		else {
			doneArr[currSquare] = 1;
		}

	}

	for (currSquare =0; currSquare<k; currSquare=(currSquare+1)%k){//this goes on forever, break on when iterato reaches end
		 //printPerm(*permIt1[currSquare]);
		 //printPerm(*permIt2[currSquare]);
		//cout<< lexicographical_compare((*permIt1[currSquare]).begin(), (*permIt1[currSquare]).end(), (*permIt2[currSquare]).begin(), (*permIt2[currSquare]).end() )<<endl;

		if ( lexicographical_compare((*permIt1[currSquare]).begin(), (*permIt1[currSquare]).end(), (*permIt2[currSquare]).begin(), (*permIt2[currSquare]).end() ))
			return true;
		else if ( lexicographical_compare((*permIt2[currSquare]).begin(), (*permIt2[currSquare]).end(), (*permIt1[currSquare]).begin(), (*permIt1[currSquare]).end() ))
			return false;

		//if we havent returned anything by now the elements compared are equivalent, move on to next.

		permIt1[currSquare]++;
		permIt2[currSquare]++;

		//if (permIt1[currSquare]== partMOLS1[currSquare].end() ){
		if ( (permIt1[currSquare]== partMOLS1[currSquare].end() || permIt2[currSquare]== partMOLS2[currSquare].end())
			|| doneArr[(currSquare-1+k)%k]==1){
			// so if we can move along on this square lets move along
			// remember k cycles between the squares
			doneArr[currSquare] = 1;
			int prod = 1;
			for (i=0; i<k; i++){
				prod=prod*doneArr[i];
			}
			if (prod==1)//then all permutation in all the squares have been enumerated, still equal
				return true;
		}

	}

	return true;

	//lexicographical_compare(partMOLS[0].front(), partMOLS[0].back(), ))
}

void MOLS::MOLStoOA(vector<lsquare> partMOLS, vector<vector<int> > OA){
	//int n = partMOLS[0].front().size();
	int i=0;
	int j=0;
	int w = n*n;
	for (i=0; i<w; i++){
		OA[0][i] = i / n;
		OA[1][i] = (j++) %n;
	}

	int uni_ctr=0, row_ctr=0;

	/*for (i=0; i<k; i++){
			for    (j=0; j<w; j++){
				OA[i+2][j] = k-1;
			}
		}*/


	for (i=0; i<k; i++){
		uni_ctr = 0;
		lsquare::iterator universalIt; //iterates over universals
		permutation::iterator perm_it; //iterates over permutation

		for(universalIt=partMOLS[i].begin(); universalIt != partMOLS[i].end(); ++universalIt){
			row_ctr=0;
			for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
				OA[i+2][n*row_ctr + (*perm_it)] = uni_ctr;
				row_ctr++;
			}
			uni_ctr++;
		}
	}
	uni_ctr = 0; row_ctr = 0;
	//printOA<k,n>(OA);

return;

}

void MOLS::OAtoMOLS(vector<vector<int> > OA, vector<lsquare> newMOLS ){

	map<int, int> pos_to_colidx;
	int i=0;
	int w=n*n;
	permutation parr[k][n];
	lsquare tempMOLS[k];

	for (i=0;i<k; i++){
				newMOLS[i].clear();
		}

	for (i=0; i<w; i++){
		pos_to_colidx[OA[0][i]*n + OA[1][i]] = i ;
		//map.insert(std::make_pair(OA[0][i]*n + OA[1][i], i));
	}

	int j;
	for (i=0;i<w; i++){
		for (j=0; j<k; j++){
			int col = pos_to_colidx[i];
			//cout << col<< " , "<< OA[j+2][col] << " , "<< OA[1][col]<< " " ;cout.flush();
			parr[j][ OA[j+2][col] ].push_back( OA[1][col] );
		}

	}

	for (i=0;i<k; i++){
		for (j=0; j<n; j++){
			newMOLS[i].push_back(parr[i][j]);
		}
	}

	//newMOLS=tempMOLS;
	return;
}

void MOLS::permuteOA(vector<vector<int> > OA, int p[],vector<vector<int> > OANew){
	int i=0;
	int j=0;
	int w = n*n;
	for (i=0; i<k+2; i++){
		for (j=0; j<w; j++){
			OANew[p[i]][j]	= OA[i][j];
		}
	}
	return;
}

void MOLS::getSmallest(vector<lsquare> partMOLS, vector<lsquare> newMOLS){


	permutation colPerm;
	permutation rowPerm;

	//lsquare tempMOLS[2];
int x;
	int i=0;
	for (i=0; i<n; i++){
		rowPerm.push_back(i);
		colPerm.push_back(i);
	}

	while(next_permutation(rowPerm.begin(), rowPerm.end())){
		while(next_permutation(colPerm.begin(), colPerm.end())){
			lsquare tempMOLS[k];

			//lsquare l1; lsquare l2; tempMOLS[0] = l1; tempMOLS[1] = l2;
			//printPerm(rowPerm) ;printPerm(colPerm);

			//transposeMOLS<2>(partMOLS, transpMOLS);
			permuteMOLS(partMOLS, rowPerm, colPerm, newMOLS);
			//tempmols has the postpermutation, first make this even smaller by permutin symbols


			//permuteSymbols<2>(tempMOLS, newMOLS);

			if (!comparePartialMOLS(partMOLS, newMOLS) ){// if  part > final
				return;
			}
			else{
				for (x=0; x<k; x++)
					newMOLS[x].clear();
			}


		}
	}

	for (x=0; x<k; x++)
		newMOLS[x]=partMOLS[x];

	return ;
}



void MOLS::transposeMOLS(vector<lsquare> partMOLS, vector<lsquare> &newMOLS){
	int i;
	for (i =0;i<k;i++){
		newMOLS[i].clear();
		lsquare::iterator permIt ;
		permutation::iterator universalIt;
		for (permIt = partMOLS[i].begin(); permIt != partMOLS[i].end(); ++permIt){
			int j=0;
			int arr[(*permIt).size()];

			for (universalIt = (*permIt).begin(); universalIt != (*permIt).end(); ++universalIt){
				arr[*universalIt] = j++;
			}
			permutation p (arr, arr + sizeof(arr) / sizeof(int) );
			newMOLS[i].push_back(p);
		}
	}
	//TODO shuffle squares
}


permutation MOLS::CSToPerm(vector<int> curr ){
	int i,j, currCycleLen;
	int ctr =0;
	int cycleStart;
	permutation p;

	for (i=0; i<n+1; i++){
		int j=curr[i]; //j = number of cycles of length i

		while (j-- > 0){ //while there is another cycle remaining of lenght i
			currCycleLen = i;
			cycleStart = ctr;

			while (currCycleLen>0){ //while we are still in this cycle
				p.push_back((currCycleLen==1? cycleStart: ctr+1	 ));
				currCycleLen--;
				ctr++;
			}
		}
	}

	return p;
}

void MOLS::genCRS(vector<int> curr, int ctr, int rem ){
	if (ctr==0){
		genCRS(curr, ctr+1, rem );
		return;
	}
	if (rem==0){
		cycleStructureReps.push_back( CSToPerm(curr) );
		return;
	}

	if (ctr<= rem){
		//first we select it and see what we get
		curr[ctr]++;
		rem = rem- ctr;
		genCRS(curr, ctr, rem );
		//then we dont
		curr[ctr]--;
		rem = rem+ctr;
		genCRS(curr, ctr+1, rem );

	}
	return;

}

void MOLS::getCycleStructure(permutation p, vector<int> &nofCycles, map<int, list<list<int> > > &cycleLength_cycles_map ){
	//bool visited[n+1] ={0};
	vector<bool> visited (n+1, false);
	permutation::iterator permIt;
	vector<int> permArr(n+1, 0);
	//int permArr[n]={0};
	int i=0;



	for (permIt = p.begin(); permIt != p.end(); ++permIt){
			permArr[i++] = *permIt;
	}
	for (i=0; i<n; i++){
		if (i==permArr[i]){
			nofCycles[1]++;
			list<int> thisCycle;
			thisCycle.push_back(i);
			cycleLength_cycles_map[thisCycle.size()].push_back(thisCycle);
		}
		else
		{
			if (!visited[i]){

				list<int> thisCycle;
				int j=i;
				while (thisCycle.front() !=j){
					thisCycle.push_back(j);
					visited[j] = true;
					j = permArr[j];
				}
				nofCycles[thisCycle.size()]++;
				cycleLength_cycles_map[thisCycle.size()].push_back(thisCycle);
			}
		}
	}

	//for (i=0; i<n+1; i++)
	//	cout<< nofCycles[i]<< " ";


}

list<permutation> MOLS::genRelevantPermutations(permutation p){
	list<permutation> result;
	int i;
	vector<int> nofCycles(n+1, 0);
	//int nofCycles[n+1] ={0};
	map<int, list<list<int> > > cycleLength_cycles_map;

	/*for (i=0; i<n+1; i++){
		list<list<int> > l;
		cycleLength_cycles_map[i] = l;
	}*/
	getCycleStructure(p, nofCycles, cycleLength_cycles_map);

	//for some reason this doesnt work if there are more than  one cycle length 1
	//TODO fis, for now just return empty list
	if (nofCycles[1]>1)
		return result ;

	int nofCycleLengths = 0;
	for (i=0; i<n+1; i++)
		if (nofCycles[i] >0)
			nofCycleLengths++	;

	list<permutation> arrPossPerLength[nofCycleLengths];

/*	list<permutation> l;
	for (i=0; i<nofCycleLengths; i++){
		arrPossPerLength[i]=l;
	}*/

	int length=0;
	int ctr =0;
	for (length = 1; length<n+1; length++){
		list<permutation> arrPossibilities[nofCycles[length]];

		if (nofCycles[length]>0){

			int ind=0;
			//list<permutation> arrPossibilities[nofCycles[length]];

			list<list<int> >::iterator cycleIt;
			permutation::iterator permIt;
			//all cycles of this length
			//cout<< "Cycles of length "<< length <<": "<<endl;
			for (cycleIt = cycleLength_cycles_map[length].begin(); cycleIt !=  cycleLength_cycles_map[length].end(); ++cycleIt){
					int a=0;
 					for (permIt = (*cycleIt).begin(); a<length; ++permIt){
						std::rotate((*cycleIt).begin(), permIt, (*cycleIt).end()) ;
						// printPerm(*cycleIt);
						arrPossibilities[ind].push_back(copyPerm(*cycleIt)			);
						if (a++>0)
							--permIt;
					}
					ind++;
			}//cout<<endl;

			/*for (ind=0; ind<nofCycles[length]; ind++){
				cout<< ind<<endl;
				for (cycleIt = arrPossibilities[ind].begin(); cycleIt != arrPossibilities[ind].end(); ++cycleIt){
					printPerm(*cycleIt);
				}
			}*/

			//list<permutation> l;
			//arrPossPerLength[ctr] = l;

			if (nofCycles[length] == 1){ //no need to worry about shuffling permutations, there is only one

				for (cycleIt = arrPossibilities[0].begin(); cycleIt != arrPossibilities[0].end(); ++cycleIt){

				//	printPerm(copyPerm(*cycleIt));
				//	cout<< "s:"<<arrPossPerLength[ctr].size();
					arrPossPerLength[ctr].push_back(copyPerm(*cycleIt));

				}
				ctr++;

			}
			else{ //now we need to both shuffle and select

				vector<int> orderOfCycle;

				for (int i=0; i<nofCycles[length]; i++)
					orderOfCycle.push_back(i);

				map<int, list<permutation> > cperm_to_possibilities_map;
				int pno = 0;

				do{
					/*cout<<"start perm"<<endl;
					for (int i=0; i<nofCycles[length]; i++)
							cout<<orderOfCycle[i]<<"-";
					cout<<"end perm"<<endl;*/

					list<permutation> templ;
					list<permutation> templ2;

					for (ind=0; ind<nofCycles[length]; ind++){
						//blist<permutation> templ;
						if (ind==0){
							for (cycleIt = arrPossibilities[orderOfCycle[ind]].begin(); cycleIt != arrPossibilities[orderOfCycle[ind]].end(); ++cycleIt){
								permutation a = copyPerm(*cycleIt);
								templ.push_back(a);
								//printPerm(a);
							}
						}
						else{
							//cout<<endl<< "W"<< cperm_to_possibilities_map[pno-1].size();

							list<list<int> >::iterator partialpermIt;
							//while nextpermutation
 							for (partialpermIt = templ.begin(); partialpermIt != templ.end(); ++partialpermIt){

								for (cycleIt = arrPossibilities[orderOfCycle[ind]].begin(); cycleIt != arrPossibilities[orderOfCycle[ind]].end(); ++cycleIt){
									permutation a = copyPerm(*partialpermIt);
								 	a.insert(a.end(), (*cycleIt).begin(), (*cycleIt).end());
									templ2.push_back(a);
 								}


							}

							templ.clear();
							templ.assign(templ2.begin(), templ2.end());
							templ2.clear();


						}//end else

					}
					cperm_to_possibilities_map[pno++].assign(templ.begin(), templ.end());
				}
				while (next_permutation(orderOfCycle.begin(), orderOfCycle.end()	));

				//merge all the different list , one for each permutation, into one list
				int y;
				for (y=0; y<pno; y++	)
					arrPossPerLength[ctr].insert(arrPossPerLength[ctr].end(),cperm_to_possibilities_map[y].begin(), cperm_to_possibilities_map[y].end());

				ctr++;

			}

			//now create options for this length and every other length
			// options[length]
			//then pick one of the options per lenght

		} //end if there are cycles of this length


	} //end for every length

	/*now we assume we have all the combinations of every length in an array, for example
	 * <0> 	| <1234> 	| <567>
	 * 		| <1243>	| <675>
	 * 		| <2134>	| <756>
	 * 		| <2143>
	 * 		| <3412>
	 * 		| <4312>
	 * 		| <3421>
	 * 		| <4321>
	 *
	 * 	Select one from each column of arrposperlength
	 */

/*	int ind = 0;
	while (ind<nofCycleLengths){
		cout<<ind<<endl;
		list<list<int> >::iterator cycleIt;

		for (cycleIt = arrPossPerLength[ind].begin(); cycleIt != arrPossPerLength[ind].end(); ++cycleIt){

			printPerm(*cycleIt);
		}

		ind++;
	}*/

	////endprint
	//cout<<"==========";

	list<permutation> tempres;
	permutation b;
	result.push_back(b);

	list<list<int> >::iterator partialpermIt;
	list<list<int> >::iterator cycleIt;
	list<permutation> temp;
	int ind = 0;
	while (ind<nofCycleLengths){
		temp.clear();
		for (partialpermIt = result.begin(); partialpermIt != result.end(); ++partialpermIt){

			for (cycleIt = arrPossPerLength[ind].begin(); cycleIt != arrPossPerLength[ind].end(); ++cycleIt){
				permutation a = copyPerm(*partialpermIt);
				a.insert(a.end(), (*cycleIt).begin(), (*cycleIt).end());
				temp.push_back(a);
				//printPerm(a);
			}
		}
		ind++;
		result = temp;
	}
	//possibleShuffles = result;
	return result;


}

bool MOLS::isIdentity(permutation p){
	int n = p.size();
	permutation::iterator permIt ;

	int checkValue = 0;
	for (permIt = p.begin(); permIt != p.end(); ++permIt){
		if (checkValue++ != *permIt)
			return false;
	}
	cout<< "ID TRUE";
	return true;

}

/*bool MOLS::isSmallestPermSymbols(lsquare ls, int nofPerms){
	//return true;
	lsquare::iterator permIt ;
	lsquare lsSorted;
	for (permIt = ls.begin(); permIt != ls.end(); ++permIt){
		//TODO taken out to speed up, won seconds on 58 seconds.
		//lsSorted.push_back(copyPerm(*permIt));
		lsSorted.push_back(*permIt);
	}
	lsSorted.sort(My::permutationComparator);
	if (lexicographical_compare(ls.begin(), ls.end(), lsSorted.begin(), lsSorted.end())){
		printUniversals(ls);
		cout<<lexicographical_compare(ls.begin(), ls.end(), lsSorted.begin(), lsSorted.end()) <<"&"<< lexicographical_compare(lsSorted.begin(), lsSorted.end(), ls.begin(), ls.end());
		printUniversals(lsSorted);cout<<"=========="<<endl;
	}else{
		printUniversals(ls);cout<<lexicographical_compare(ls.begin(), ls.end(), lsSorted.begin(), lsSorted.end()) <<"&"<< lexicographical_compare(lsSorted.begin(), lsSorted.end(), ls.begin(), ls.end());
		printUniversals(lsSorted);
		cout<<"=========="<<endl;
	}
	return !lexicographical_compare(ls.begin(), ls.end(), lsSorted.begin(), lsSorted.end()) && !lexicographical_compare(lsSorted.begin(), lsSorted.end(), ls.begin(), ls.end());// true if the original was smallest

}*/

void MOLS::changeOrder(vector<lsquare> partMOLS , vector<int> order , vector<lsquare> &newMOLS){
	int i;
	for (i=0; i<k; i++){
		newMOLS[i]= partMOLS[order[i]];
	}
}

void MOLS::changeOrder(vector<lsquare> partMOLS , int first, int second , vector<lsquare> &newMOLS){
	newMOLS[0]=partMOLS[first];
	newMOLS[1]= partMOLS[second];
	int i=0;
	int j=2;
	for (i=0; i<k; i++){
		if (i!=first && i!=second)
			 newMOLS[j++]= partMOLS[i];
	}
}

void MOLS::rollUp(vector<lsquare> pMOLS ,  int pos,  permutation origP, vector<lsquare> &newMOLS ){
	/*int arrPerm[n];
	int i;
	permutation id;
	for (i=0;i<n;i++){
		//arrPerm[i]= (rowUp+i+n)%n;
		id.push_back(i);
	}
	//permutation p (arrPerm, arrPerm + sizeof(arrPerm) / sizeof(int) );
	printPerm(origP);
	//printMOLS(partMOLS, k);
	permuteMOLSRCS<k>(partMOLS,  origP,id,  newMOLS);
	//permuteMOLS<k>(partMOLS, id,inverse(p),  newMOLS);//TODO this is wrong
	//printMOLS(newMOLS, k);*/

	//printPerm(origP);
	list<permutation >::iterator cycleIt;
	permutation::iterator permIt;
	//permutation p1;
	int i;
	for (i=0; i<k; i++){
		newMOLS[i].clear();
		for (cycleIt = pMOLS[i].begin(); cycleIt !=   pMOLS[i].end(); ++cycleIt){
			/*int a=0;
		permIt = (*cycleIt).begin();
		for (i=0;i<pos; i++)
			++permIt;*/
			permutation p;
			for (permIt = (*cycleIt).begin(); permIt!=(*cycleIt).end(); ++permIt){
				//std::rotate((*cycleIt).begin(), permIt, (*cycleIt).end()) ;
				//bprintPerm(*cycleIt);
				p.push_back((*permIt-pos+n)%n);
			}
			newMOLS[i].push_back(p);
			//ind++;
		}
	}
	//cout<<"Rotate";
	//printMOLS(newMOLS, k);

	return;
}


void MOLS::standardForm(vector<lsquare> pMOLS , int rowUp, int pos ,permutation origP, vector<lsquare> &newMOLS ){
	vector<lsquare> ruMOLS(k, lsquare(n , permutation(n, n))) , sfMOLS(k, lsquare(n , permutation(n, n)))  ;
	rollUp(pMOLS, pos, origP, ruMOLS);


	int i;
	permutation id;
	for (i=0;i<n;i++){
			//arrPerm[i]= (rowUp+i+n)%n;
			id.push_back(i);
		}
	permutation p ;
	permutation::iterator permIt;
	//for (permIt = ruMOLS[0].front().begin(); permIt!=( ruMOLS[0].front()).end(); ++permIt){
	for (permIt = origP.begin(); permIt!=(origP).end(); ++permIt){
		p.push_back((*permIt-pos+n)%n);
	}

	/*lsquare nMOLS[k];
	permuteMOLS<k>(ruMOLS, p,id,  nMOLS);
	permuteSymbols<k>(nMOLS, newMOLS	);*/

	if (!( rowUp ==0 && pos==0)){
 		vector<lsquare> nMOLS(k, lsquare(n , permutation(n, n)));
		permuteMOLS(ruMOLS, p,id,  nMOLS);

		permuteSymbols(nMOLS, newMOLS);
	}
	else{
 		permuteMOLS(ruMOLS, p,id,  newMOLS);

	}


}

vector<int> MOLS::rowMeets(permutation p1, permutation p2){
	permutation::iterator permIt1;
	permutation::iterator permIt2;
	permIt2 = p2.begin();
		int i=0;
	vector<int>	res;
	res.assign(2,0);
	for (permIt1 = p1.begin(); permIt1 != p1.end(); ++permIt1) {
		if (*permIt1==*permIt2){
			res[0] = i; //row
			res[1] = *permIt1;
			return res;
		}
		permIt2++;
		i++;
	}
	return res;
}

/*
 * accept  a permutation p, of which the cycle structure is to be found and comparded to
 * another cycle structure in the form of an integer arrayu where
 * the number stored at index i is the number of cycles of length i
 * Returns 0 if the same number of cycles of every length
 *
 * Returns <0 if p < target
 * Returns >0 if p> target
 */
int MOLS::compareCS(permutation p , vector<int>	 targetCS){
	//int n = p.size();

	//int thisCS[n+1] ={0};
	vector<int> thisCS(n+1, 0);
	map<int, list<list<int> > > dummy_cycles_map;
	getCycleStructure(p, thisCS ,dummy_cycles_map );

	int i;
	/*cout<<endl;printPerm(p);
	for(j=0; j<n;j++){
		cout<<thisCS[j]<<" ";}
	cout<<endl;
	for(j=0; j<n;j++){
			cout<<targetCS[j]<<" ";}
	cout<<endl;*/

	for (i=0; i<n; i++){
		//cout<<targetCS[i]<<"<>" <<thisCS[i];
		if (! (targetCS[i] == thisCS[i])	)
			return targetCS[i]-thisCS[i];
	}

	return 0; //the same

}

list<vector<int> > MOLS::getSmallRelCS( vector<lsquare> pMOLS, list<permutation> &listP){
	permutation targetRCS = copyPerm(pMOLS[1].front());

	int i,j;
	//int n = partMOLS[0].front().size();
	//cout<<"enter getSmallRCS"<<endl;
	//int targetCS[n+1] ={0};
	/*vector<int> targetCS(n+1, 0);
	map<int, list<list<int> > > dummy_cycles_map;
	getCycleStructure(targetRCS, targetCS, dummy_cycles_map );*/

	list<vector<int> > squares;

	//printMOLS(partMOLS,3);
	list<permutation>::iterator permIt1;
	list<permutation>::iterator permIt2;
	//TODO should do it both ways around, or x,y == y,x??
	for(i=0; i<k-1; i++){
		for(j=i+1; j<k; j++){

			for (permIt1 = pMOLS[i].begin(); permIt1 != pMOLS[i].end(); ++permIt1) {
				for (permIt2 = pMOLS[j].begin(); permIt2 != pMOLS[j].end(); ++permIt2) {

					permutation rcsV = rcs((*permIt1), (*permIt2));

					//if this rcs is equal to smallest store in list
					//if (!lexicographical_compare(rcsV.begin(), rcsV.end(), targetRCS.begin(), targetRCS.end())
					//		and !lexicographical_compare(targetRCS.begin(), targetRCS.end(), rcsV.begin(), rcsV.end())){
					if (compareCS(rcsV, currentCS)==0){
					// if (true){
						vector<int> data ;
						data.assign(4, 0);
						data[0]=i;
						data[1] =j;
						vector<int> dataPos = rowMeets(*permIt1, *permIt2);
						data[2] = dataPos[0];
						data[3] = dataPos[1];
						//if (!(data[0]==0&&data[1]==1&&data[2]==0) ){
							listP.push_back(*permIt1);
							//cout<<  data[0]<<" "<<data[1]<<" "<<data[2]<<" "<<data[3]<< " perm "; printPerm(*permIt1);cout<<", "; printPerm(*permIt2); cout<<endl;
							squares.push_back(data);
						//}
					}

					//and in reverse
					rcsV = rcs((*permIt2),(*permIt1));
					//if this rcs is equal to smallest store in list
					//if (!lexicographical_compare(rcsV.begin(), rcsV.end(), targetRCS.begin(), targetRCS.end())
					//		and !lexicographical_compare(targetRCS.begin(), targetRCS.end(), rcsV.begin(), rcsV.end())){
					if (compareCS(rcsV, currentCS)==0){
					// if(true){
						vector<int> data1 ;
						data1.assign(4, 0);
						data1[0]=j;
						data1[1] =i;
						vector<int> dataPos = rowMeets(*permIt2,*permIt1);
						data1[2] = dataPos[0];
						data1[3] = dataPos[1];
						// if (!(data1[0]==0&&data1[1]==1&&data1[2]==0) ){
							listP.push_back(*permIt2);
							//cout<<  data1[0]<<" "<<data1[1]<<" "<<data1[2]<<" "<<data1[3]<< " perm "; printPerm(*permIt2);cout<<", "; printPerm(*permIt1); cout<<endl;

							squares.push_back(data1);
						// }
					}

				}
			}


		}
	}
	return squares;
}

list<permutation> MOLS::getShuffles(permutation pOrig, permutation pNow){

	list<permutation> listShuffles ;
	listShuffles=genRelevantPermutations(pNow);
	list<permutation> listtemp;

	list<permutation>::iterator pi;

	for (pi=listShuffles.begin(); pi!=listShuffles.end(); ++pi){

		listtemp.push_back( composition(pOrig,inverse(*pi)));
		//printPerm(*pi); cout<<" | "; printPerm(inverse(*pi)) ;cout<<" | ";printPerm(composition(inverse(*pi), pOrig)) ;cout<<" | ";printPerm(composition( pOrig,inverse(*pi))) ;cout<<endl;
	}

	return listtemp;
}

bool MOLS::noSmallerRCS(permutation smallestRCS, vector<lsquare> pMOLS){

	//permutation targetP =copyPerm(partMOLS[1].front());
	//permutation smallestRCS = partMOLS[1].front();
	list<permutation> listPerms;
	//so relCS has the data about where the relative cs are, and listperms the actual permutation in the square going first
	list <vector<int> > relCS = getSmallRelCS(pMOLS, listPerms);
	list< vector<int> >::const_iterator testRel;
	list< permutation >::iterator testPermsit;
	testPermsit= listPerms.begin();

	//printMOLSPerms(pMOLS);
	list<permutation>::iterator permIt;int i;
	//cout<<"RELCS"<<relCS.size();
	/*for (i=0; i<k; i++){
			printPerm(partMOLS[i].back());cout<<" ";}*/
	for (testRel=relCS.begin(); testRel!=relCS.end(); testRel++){
		//cout<<endl<<" "<<(*testRel)[0]<<" "<<(*testRel)[1]<<" "<<(*testRel)[2]<<" "<<(*testRel)[3] <<endl;
		vector<lsquare> roMOLS(k, lsquare(n , permutation(n, n)));
		vector<lsquare> sfMOLS(k, lsquare(n , permutation(n, n)));
		/*cout<<"Before";
		printMOLS(partMOLS );
		printMOLSPerms(partMOLS );*/
		changeOrder(pMOLS, (*testRel)[0],(*testRel)[1], roMOLS);

		standardForm(roMOLS, (*testRel)[2],(*testRel)[3], *testPermsit, sfMOLS);

		/*cout<<"STD Form";
		printMOLS(sfMOLS);
		printMOLSPerms(sfMOLS);*/
		permutation currPerm = sfMOLS[1].front();
		list<permutation> allShuffles = getShuffles( smallestRCS, currPerm);

		// printPerm(rcs2);
		//cout << " Test shuffles";
		for (permIt = allShuffles.begin(); permIt != allShuffles.end(); ++permIt) {
			vector<lsquare> tMOLS(k, lsquare(n , permutation(n, n))), ttMOLS(k, lsquare(n , permutation(n, n)));
			//permutation realShuffle = composition(inverse( *permIt),targetP );

			//printPerm( *permIt);

			permuteMOLS(sfMOLS, *permIt, *permIt, tMOLS);
			permuteSymbols(tMOLS, ttMOLS);
			 //printMOLSPerms(ttMOLS);
			if (!comparePartialMOLS(partMOLS, ttMOLS) )// if  part > temp
			{
				/*for (i=0; i<k; i++){
					printPerm(partMOLS[i].front());cout<<" ";}*/

				//cout<< "rel CS smaller.."<< (*testRel)[0]<<" "<<(*testRel)[1]<<" "<<(*testRel)[2]<<" "<<(*testRel)[3]<< " perm "; printPerm(*permIt);cout<<endl;
				//printMOLS(tMOLS, k);
				return false;
			}
		}
		testPermsit++;
	}


	//==================\
	//TRANSPOSES??
	vector<lsquare> transpMOLS(k, lsquare(n , permutation(n, n)));
	transposeMOLS(pMOLS, transpMOLS);
	list<permutation> listPerms1;
	list <vector<int> > relCS1 = getSmallRelCS(transpMOLS, listPerms1);
	list< vector<int> >::const_iterator testRel1;
	list< permutation >::iterator testPermsit1;
	testPermsit1= listPerms1.begin();
	//list<permutation>::iterator permIt;int i;

	for (testRel1=relCS1.begin(); testRel1!=relCS1.end(); testRel1++){
		vector<lsquare> roMOLS(k, lsquare(n , permutation(n, n))), sfMOLS(k, lsquare(n , permutation(n, n)));

		changeOrder(transpMOLS, (*testRel1)[0],(*testRel1)[1], roMOLS);
		standardForm(roMOLS, (*testRel1)[2],(*testRel1)[3], *testPermsit1, sfMOLS);

		permutation currPerm = sfMOLS[1].front();
		list<permutation> allShuffles = getShuffles( smallestRCS, currPerm);

		for (permIt = allShuffles.begin(); permIt != allShuffles.end(); ++permIt) {
			vector<lsquare> tMOLS(k, lsquare(n , permutation(n, n))) , ttMOLS(k, lsquare(n , permutation(n, n))) ;
			permuteMOLS(sfMOLS, *permIt, *permIt, tMOLS);
			permuteSymbols(tMOLS, ttMOLS);

			if (!comparePartialMOLS(partMOLS, ttMOLS) )// if  part > temp
			{
				/*for (i=0; i<k; i++){
					printPerm(compMOLS[i].back());cout<<" ";}*/

				//cout<< "Initial";printMOLSPerms(compMOLS, k);
				//cout<< "New after transpose";
				//printMOLSPerms(tMOLS, k);
				//cout<< "rel CS smaller after transpose.."<< (*testRel1)[0]<<" "<<(*testRel1)[1]<<" "<<(*testRel1)[2]<<" "<<(*testRel1)[3]<< " perm "; printPerm(*permIt);cout<<endl;
								//printMOLS(tMOLS, k);
				return false;
			}
		}
		testPermsit1++;
	}

	return true;
}

bool MOLS::noSmallerRCS(permutation smallestRCS){
	return noSmallerRCS(smallestRCS, partMOLS);
}

bool MOLS::isSmallest5(vector<lsquare> partMOLS,vector<lsquare> origMOLS, list<permutation> &testPerm){
	if ( testPerm.size()==0)
		return true;

	if (partMOLS[k-1].size() > 2 && partMOLS[k-1].size()<n)
				return true;
	int i;
	list<permutation>::iterator permIt;

	for (permIt = testPerm.begin(); permIt != testPerm.end(); ++permIt)
	//while (next_permutation(testPerm.front().begin(), testPerm.front().end()))
	{
		vector<lsquare> tempMOLS ;
		//lsquare finalMOLS[k];

		permuteMOLS(partMOLS, *permIt, *permIt, tempMOLS);
		//printPerm(*permIt);cout<<"-> "; printPerm(tempMOLS[k-1].front());
		if (!comparePartialMOLS(origMOLS, tempMOLS) )// if  part > temp
		{
		/*
			for (i=0; i<k; i++){
				printPerm(origMOLS[i].back());cout<<"\t";}
			cout<< "smaller.. perm "; printPerm(*permIt);cout<<endl;*/
			return false;
		}
	}

	if (partMOLS[0].size()==partMOLS[k-1].size())
	{
		vector<lsquare> transpMOLS;
		transposeMOLS(partMOLS, transpMOLS);
		vector<lsquare> transpTempMOLS;
		list<permutation> allPermTest = getShuffles(copyPerm(origMOLS[1].front()),copyPerm(transpMOLS[1].front()));
		//genRelevantPermutations<(int)n>(transpMOLS[1].front(), allPermTest );

		for (permIt = allPermTest.begin(); permIt != allPermTest.end(); ++permIt)	{		//permuteMOLSS<k>(partMOLS, *permIt, *permIt, transpMOLS);
			permuteMOLS(transpMOLS, *permIt,*permIt, transpTempMOLS);

			if (!comparePartialMOLS(origMOLS, transpTempMOLS)){// if  part > transp
				/*for (i=0; i<k; i++){
					printPerm(origMOLS[i].back());cout<<"\t";}
				cout<< "transpose smaller.. perm "; printPerm(*permIt);cout<<endl;*/
				return false;
			}
		}

	}
	return true;

}

bool MOLS::isSmallest4( ){
	int i;

	vector<lsquare> t1MOLS (k, list<permutation>(n, list<int>(n, sizeof(int))));
	for (i=0; i<k; i++)
		t1MOLS[i] = partMOLS[i];

	if (!noSmallerRCS(copyPerm(t1MOLS[1].front()))){
		/*for (i=0; i<k; i++)
				printPerm(partMOLS[i].back());
		cout << "smaller cs"<<endl;*/
			return false;
		}
	return true;

}


bool MOLS::isSmallestConjugateMOLS(vector<lsquare> partMOLS ){
	return true;
 	int i;
 	vector<lsquare> smallestMOLS ;
	for (i=0; i<k; i++){
		smallestMOLS[i] = partMOLS[i];
	}

	list<permutation> allCSR; //list of all smalle s u0^1 cycle structures
	//int cycles[n+1];
	vector<int> cycles(n+1, 0);
	/*for (i=0; i<=n+1; i++)
		cycles[i]=0;*/
	cycles[1] =1;
	genCRS(cycles, 2, n-1); //we may only have one overlap

	list<permutation>::iterator CSRit;

	permutation smallestRCS = partMOLS[1].front();
	vector<lsquare> t1MOLS , newMOLS;

    //First check for normal permutations and transpose
    /*if (!noSmallerRCS(smallestRCS, partMOLS)){
    		for (i=0; i<k; i++)
    				printPerm(partMOLS[i].back());
    		cout << "smaller cs"<<endl;
    			return false;
    }*/

	/*lsquare l1; lsquare l2;
	tempMOLS[0] = l1; tempMOLS[1]=l2;*/

	//int n = partMOLS[0].front().size();
    vector<vector<int> > oa (k+2, vector<int>(n*n)	);
    vector<vector<int> > oanew(k+2, vector<int>(n*n));

   	MOLStoOA(partMOLS, oa);
	//printOA<k,n>(oa);
	//int rowls[] = {0,1,2,3,4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
	permutation p[3] ;//(rowls, rowls + n / sizeof(int) );

	for (i=0;i<k+2; i++){
			p[0].push_back(i);
			p[1].push_back(i);
			p[2].push_back(i);
	}
	p[0].remove(0);	p[0].push_back(0);p[0].remove(2);	p[0].push_front(2);
	p[1].remove(1); p[1].push_back(1);
	p[2].remove(0); p[2].remove(1); 	p[2].push_back(0); p[2].push_back(1);



	int parr[k+2];
	int perm_ctr = 0;

	while(perm_ctr<3 ){
		i=0;

		permutation::iterator permIt;
		for (permIt = p[perm_ctr].begin(); permIt !=  p[perm_ctr].end(); ++permIt){
			parr[i++] =  *permIt;
		}

		permuteOA(oa, parr, oanew);
		//cout<< "  -  oanew "; cout.flush();
		//printOA<k,n>(oanew);
		OAtoMOLS(oanew, t1MOLS);
		//cout<< "  -  t1MOLS "; cout.flush();
		//OAtoMOLS<k,n>(oanew, (flag1? t2MOLS : t1MOLS));
		//printMOLS(t1MOLS, k);

		//getSmallest<k,n>(t1MOLS, newMOLS);
		//newmols comes bac empty
		//list<permutation> testPs =
		//if (!isSmallest5(t1MOLS, partMOLS, testPs)){
		//if( !noSmallerRCS<k,n>(smallestRCS, partMOLS, partMOLS){
		for (CSRit=allCSR.begin(); CSRit!= allCSR.end(); ++CSRit){
			//printPerm(*CSRit); cout.flush();
			if (!noSmallerRCS(copyPerm(*CSRit), t1MOLS )){
				/*for (i=0; i<k; i++)
		    				printPerm(partMOLS[i].back());
		    		cout << "smaller cs"<<endl;*/
				cout <<"Not smallest conjugate";
				return false;
			}

		}
		int x;//if this wasnt smalleer, wip the mols so that a new one may be tried
		for (x=0; x<k; x++)
			t1MOLS[x].clear();

		/*if (!comparePartialMOLS<k>(partMOLS, t1MOLS)){

			cout<< "Compare"<<endl;
			printMOLS(partMOLS, k);
			cout<< "and"<<endl;
			printMOLS(newMOLS, k);
			cout <<"Not smallest conjugate";

			return false;
		}
		else
		{ //if this wasnt smalleer, wip the mols so that a new one may be tried
			int x;
			for (x=0; x<k; x++)
				newMOLS[x].clear();
		}*/
		perm_ctr++;
	}

	return true;
}

void MOLS::buildCurrentLS(){
		//currLS[]
		int x, y;
		for(x = 0; x < n; x ++) {
		    for(y = 0; y < n; y ++)
				currLS[currSquare][x][y] = -1;
		}

		int i= 0; //row
		int j =0;
		list<permutation >::iterator universalIt; //iterates over universals
		permutation::iterator perm_it; //iterates over permutation

		for(universalIt=partMOLS[currSquare].begin(); universalIt != partMOLS[currSquare].end(); ++universalIt){
			for(perm_it=(*universalIt).begin(); perm_it != (*universalIt).end(); ++perm_it){
				currLS[currSquare][i++][*perm_it] = j;
			}
			i=0;
			j++;//update universal being filled in
		}
}


bool MOLS::checkFit( permutation p){
	if (n==0) return true;
	int i= 0; //row

	list<permutation >::iterator universalIt; //iterates over universals
	permutation::iterator perm_it; //iterates over permutation

	i=0;
//	printMOLS(partMOLS); cout<<"Try to fit perm "; printPerm(p);cout<<endl;
	for(perm_it=p.begin(); perm_it != p.end(); ++perm_it){
		if (currLS[currSquare][i++][*perm_it] < n)
			return false; //if the cell is already filled
	}
	return true;

}

bool MOLS::checkOrthogonal(permutation P){

	int i =0;
	for (i=0; i<k; i++){
		if (i!=currSquare){ //for every square except the current one
			lsquare::iterator perm_it;
			for(perm_it=partMOLS[i].begin(); perm_it != partMOLS[i].end(); ++perm_it){
					if(!isOrthogonal(rcs(*perm_it, P))) //check that it is orthogonal
						return false;
				}
		}
	}
	return true;
}

bool MOLS::checkRCS( permutation P){

	if (k<2) return true;
	/*if (partMOLS[1].size()<1) // ie if this is where we insert u_0^(0)
		return true;//return isCSR(P);*/

	//int targetCS[n+1]={0};
	vector<int> targetCS(n+1, 0);
	map<int, list<list<int> > > dummy_cycles_map;
	getCycleStructure(partMOLS[1].front(), targetCS,dummy_cycles_map );

	int i=0;
	for (i=0; i<k; i++){
		lsquare::iterator permIt1;
		for (permIt1=partMOLS[i].begin(); permIt1!= partMOLS[i].end(); ++permIt1){
			permutation tempPerm = rcs(*permIt1, P);
			int test =compareCS(tempPerm,targetCS);
			//cout<<test<<endl;

			if (test<0 ){
				//cout << "Rel cycle structure of ";printPerm(*permIt1);cout<< " and ";printPerm(P);cout<< "is "; printPerm(tempPerm); cout <<"Smaller";
				return false;
			}
		}
	}
	return true;
}



void MOLS::printDots(int cursquare, int size, int k){
	int p = size*k+cursquare;
	int i=0;
	for (i=0;i<p; i++)
		cout<<".";
}
void MOLS::printDots(int num){
	int i=0;
	for (i=0;i<num; i++)
		cout<<".";
}

void MOLS::buildPossibleSquare( vector<vector<int> > &square ){
	int r,c;
	//square = {{1}};

		for (c=0;c<n;c++){
			square[0][c]=0;
		}


	square[0][partMOLS[currSquare].size()]=1;
	list<permutation>::iterator permIt;
	permutation::iterator pit;

	for (permIt=partMOLS[currSquare].begin(); permIt!= partMOLS[currSquare].end(); ++permIt){
		r=0;
		for (pit=(*permIt).begin(); pit != (*permIt).end(); ++pit){

			square[r++][*pit] = 0;
		}
	}

/*	int q,w;
	for (q=0;q<n;q++)	{
			for (w=0;w<n;w++){
				cout<< square[q][w]<<" ";
			}
			cout<<endl;
		}*/
}


void MOLS::generatePossiblePermsToInsertRec(vector<vector<int> > &square, permutation p, int row,  list<permutation> &possiblePermList ){

	if (row==n){
		possiblePermList.push_back(copyPerm(p));
		//printPerm(p);
		return;
	}

	int i,j;
	for (i=0; i<n; i++){
		if (square[row][i] ==1){
			p.push_back(i);
			for(j=0; j<n; j++){
				if (square[j][i]==1)
					square[j][i]=-row;
			}

			generatePossiblePermsToInsertRec(square, p, row+1,   possiblePermList	);
			p.pop_back();
			for(j=0; j<n; j++){
				if (square[j][i]==-row)
					square[j][i]=1;
			}
		}
	}
	return;
}

void MOLS::generatePossiblePermsLSRec(permutation p, int row,  list<permutation> &possiblePermList ){
	if (row==n){
		possiblePermList.push_back(copyPerm(p));
		//printPerm(p);
		return;
	}

	//cout<< endl<< row<<endl; printPerm(p);cout<<endl;
	int q,w;
		/*for (q=0;q<n;q++)	{
			for (w=0;w<n;w++){
				cout<< currLS[currSquare][q][w]<<" ";
			}
			cout<<endl;
		}*/

	int i,j;
	for (i=0; i<n; i++){
		if (currLS[currSquare][row][i] == n){
			p.push_back(i);
			for(j=0; j<n; j++){
				if (currLS[currSquare][j][i]==n)
					currLS[currSquare][j][i]= (-row-1);
			}

			generatePossiblePermsLSRec( p, row+1,   possiblePermList	);
			p.pop_back();
			for(j=0; j<n; j++){
				if (currLS[currSquare][j][i]== (-row-1) )
					currLS[currSquare][j][i]=n;
			}
		}
	}
	return;
}


void MOLS::generatePossiblePermsToInsert( list<permutation> &possiblePermList ){
	int i; permutation p;
	int j=partMOLS[currSquare].size();
	p.push_back(j); // because i in the first row is always in the ith position
	for(i=0; i<n; i++){
		if (currLS[currSquare][i][j]==n)
			currLS[currSquare][i][j]=-1;
	}
	generatePossiblePermsLSRec( p, 1,   possiblePermList	) ;
	for(i=0; i<n; i++){
		if (currLS[currSquare][i][j]==-1)
			currLS[currSquare][i][j]=n;
	}
	//cout<< "Size"<<possiblePermList.size()<<endl;

	return;

	/*//cout<<"Enter genPossPerms";cout.flush();
	vector<vector<int> > square(n, vector<int>(n, 1));

	buildPossibleSquare(square);

	int q,w;
	for (q=0;q<n;q++)	{
		for (w=0;w<n;w++){
			cout<< square[q][w]<<" ";
		}
		cout<<endl;
	}


	generatePossiblePermsToInsertRec(square, p, 0,   possiblePermList	) ;
	return;*/

}


void addToCompletedMOLS(){

}

void MOLS::addToLS(){
	//cout<<"enter add LS"; cout.flush();
	//list<permutation>::iterator permIt;

	permutation::const_iterator pit;
	//cout<<partMOLS[currSquare].size(); cout.flush();
	//printPerm(partMOLS[currSquare].back()); cout.flush();

	int r=0;
	for (pit=partMOLS[currSquare].back().begin(); pit != partMOLS[currSquare].back().end(); ++pit){
		currLS[currSquare][r++][*pit] = partMOLS[currSquare].size()-1;
	}
	//cout<<"exit add LS"; cout.flush();
}

void MOLS::removeFromLS(permutation p){
	permutation::iterator pit;

	int r=0;
	for (pit=p.begin(); pit != p.end(); ++pit){
		currLS[currSquare][r++][*pit] = n;
	}
}

void MOLS::addUniversal(permutation p){
	//cout<<"enter add"; cout.flush();
	//printPerm(p);
	//cout<< currSquare; cout.flush();

	partMOLS[currSquare].push_back(p);

	//cout<< partMOLS[currSquare].size(); cout.flush();
	addToLS();
	//cout<<"universal added"; cout.flush();


}

void MOLS::removeUniversal(permutation p	){
	removeFromLS(p);
	partMOLS[currSquare].pop_back();



}

void MOLS::findMOLS4(){
	branchCount_[(partMOLS[currSquare].size())*k+currSquare-1]++;

	int i=0;

	if (currSquare==0){
		//updatePossible
		if (partMOLS[0].size()>0){

			printDots(2*partMOLS[0].size());
			cout<<branchCount_[partMOLS[currSquare].size()*k+currSquare-1];
			printDots(4);

			for (i=0; i<k; i++){
				printPerm(partMOLS[i].back()	);
				cout<<" ";
			}
			cout<<endl;
		}
	}
	//printMOLS(partMOLS)	;
	//printMOLSPerms(partMOLS);

	/*if (partMOLS[k-1].size()==1&& currSquare==0) //if the first row is filled in completely
	{
		printMOLS(partMOLS, k);
		return count_MOLS +1 ;
	}*/


	if (partMOLS[k-1].size()==n) //if the last square is filled in completely, contains n permutations
	{
		//bcout<< count_MOLS<<"&"<<endl;

		if (isSmallestConjugateMOLS(partMOLS)){
			//if (isSmallest2<k>(partMOLS)){
				printMOLS(partMOLS);
				count_MOLS++;
				//addToCompletedMOLS();
				return;
			//}
		}
		else	return;

	}
	//buildCurrentLS();
	permutation P, p1;

	//list<permutation> allPermTest;

	for (i=0; i<n; i++){
		P.push_back(i);
		p1.push_back(i);
	}
	p1.remove(partMOLS[currSquare].size());
	p1.push_front(partMOLS[currSquare].size());

	//if this is the first universal iln the second square we look at the class representatives
	if(currSquare==1&& partMOLS[currSquare].size()==0	){

		list<permutation>::iterator CSRit;

		int j=1;
		for (CSRit=cycleStructureReps.begin(); CSRit!= cycleStructureReps.end(); ++CSRit){

			if (printOut){
				cout << j++ << ". u0^1 = ";
				printPerm(*CSRit);
				cout<<endl;

			}

			//No need for any of the checks, as this is only the first perm in the second square.
			//Automatically orthog, will fit (empty), forced to be RCS..


			//partMOLS[currSquare].push_back(*CSRit);
			map<int, list<list<int> > > dummy_cycles_map;
			//currentCS.clear(); currentCS.resize(n+1, 0);
			getCycleStructure(*CSRit,  currentCS, dummy_cycles_map );
			list<permutation> allPermTest;

			addUniversal(*CSRit);
			possibleShuffles = genRelevantPermutations(partMOLS[currSquare].front());
			currSquare = (currSquare+1)%k;

			findMOLS4( );

			currSquare = (currSquare-1+k)%k;
			removeUniversal(P);

			currentCS.clear(); currentCS.resize(n+1, 0);
			//partMOLS[currSquare].pop_back();

		}

	}
	else{ //not u_0^(1)

		if (partMOLS[currSquare].size()==0 ){


		//	if (!testPerms.size()==0){
				//cout << " sq "<< (currSquare+1)<< ", "<< testPerms.size()<<endl;
				do{
					if (P.front()<1){
						if (checkFit(P)){
							if (checkOrthogonal(  P)){
								//printDots(currSquare, partMOLS[currSquare].size(), k); printPerm(P);
								if (checkRCS(P)){
									addUniversal(P);
									//partMOLS[currSquare].push_back(P);

									//if (currSquare==k-1){
									if (isSmallest4()){

										currSquare = (currSquare+1)%k;
										findMOLS4( );
										currSquare = (currSquare-1+k)%k;
									}
									removeUniversal(P);
									//partMOLS[currSquare].pop_back();


								}
								/*else{

									for (i=0; i<currSquare; i++){
										printPerm(partMOLS[i].back());cout<<" ";}
									printPerm(P);
									cout<< "checkrcs "; cout<<endl;
								}*/
							}
							/*else{

								for (i=0; i<currSquare; i++){
									printPerm(partMOLS[i].back());cout<<" ";}
								printPerm(P);
								cout<< "orthog "; cout<<endl;
							}*/
						}
						/*else{

							for (i=0; i<currSquare; i++){
								printPerm(partMOLS[i].back());cout<<" ";}
							printPerm(P);
							cout<< "checkfit "; cout<<endl;
						}*/
					}
				}while(next_permutation(P.begin(), P.end()));

			}

		//}
		else{//in general
			//cout<< "Size"<< testPerms.size();
			list<permutation> possiblePermList;
			//cout<< "Call gen poss perms"; cout.flush();
			generatePossiblePermsToInsert(  possiblePermList );
			//cout<< "Size"<< possiblePermList.size();cout.flush();
			//cout<< possiblePermList.size(); cout.flush();
			list<permutation>::iterator possPermIt;
			/*cout<< "Possible permutations to insert"<<currSquare;
			for (possPermIt=possiblePermList.begin(); possPermIt!= possiblePermList.end(); ++possPermIt){
				printPerm(*possPermIt);
			}cout<< endl;*/

			for (possPermIt=possiblePermList.begin(); possPermIt!= possiblePermList.end(); ++possPermIt){
			//	cout<<"startchecks"<<endl	;
				if (checkOrthogonal((*possPermIt))){
					//printDots(currSquare, partMOLS[currSquare].size(), k);  printPerm((*possPermIt));
					if (checkRCS( (*possPermIt))){

						addUniversal(*possPermIt);
						//partMOLS[currSquare].push_back(P);

						if (isSmallest4()){
							currSquare = (currSquare+1)%k;
							findMOLS4( );
							currSquare = (currSquare-1+k)%k;
						}
						removeUniversal(*possPermIt);
						//partMOLS[currSquare].pop_back();
					}
					/*else{

												for (i=0; i<currSquare; i++){
													printPerm(partMOLS[i].back());cout<<"\t";}
												printPerm((*possPermIt));
												cout<< "checkrcs "; cout<<endl;
											}*/
				}
				/*else{

					for (i=0; i<currSquare; i++){
						printPerm(partMOLS[i].back());cout<<"\t";}
					printPerm((*possPermIt));
					cout<< "orthog "; cout<<endl;
				}*/

			}

		}
	}
	return ;

}

int main(int argc,char *argv[])
{
	//MOLS threemols(7,3);
	string filename = argv[1];

	string outfile = "out."+filename;
	std::ofstream out(outfile.c_str());
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf());

	MOLS threemols(filename);
	threemols.enumerateMOLS();
	std::cout.rdbuf(coutbuf); //reset to standard output again

}
