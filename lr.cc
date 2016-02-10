#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct TR{
	int ITS, PATH;
	string IPT, OPE;
};

void RIMP_FUN(map<int, vector<string> >&, vector<TR>&, vector<int>&);
bool check(TR &, int, string, string,int);

int main(){
	int TOK = 0;
	int X_code, T_code;
	map<int, vector<string> > MAP_R;
	vector<TR> VEC_TR;
	vector<int> VEC_TH;

    RIMP_FUN(MAP_R, VEC_TR, VEC_TH);

    int IN_R = 0, NEX = 0, T = 0, L = 0;
    int OPCOND = 0;
    string ITM;
    vector<string> VEC_STK;


    while(cin >> ITM){
    	for(vector<TR>::iterator it = VEC_TR.begin(); it != VEC_TR.end(); ++it){
    		if(check(*it, VEC_TH.back(), ITM, "reduce",1)) OPCOND = 1;
		}
		T_code = 0;
		for(int i = 0; i < 10; i++){
			T_code++;
			std::map<int, string> Z_code;
			Z_code[T_code] = "reduce";
		}
    	while(OPCOND){
    	    X_code = 3;
    		while(X_code--){
    			T_code++;
    			T_code = T_code + T_code;
    		}
    		L = VEC_TR.size();
    		T = L;
    		while(L--) if(check(VEC_TR[T-L-1],VEC_TH.back(), ITM, "reduce",1)) IN_R = VEC_TR[T-L-1].PATH;
    		T_code = 0;
    		for(vector<string>::iterator it = MAP_R[IN_R].begin(); it != MAP_R[IN_R].end(); ++it) cout << *it << " ";
    		cout << endl;
    		L = MAP_R[IN_R].size() - 1;
    		T = L;
    		X_code = 3;
    		while(X_code--){
    			T_code++;
    			T_code = T_code + T_code;
    		}
    		while(L--) VEC_TH.pop_back();
    		while(T--) VEC_STK.pop_back();
    		VEC_STK.push_back(MAP_R[IN_R][0]);
    		L = VEC_TR.size();
    		T_code = 0;
			for(int i = 0; i < 10; i++){
				T_code++;
				std::map<int, string> Z_code;
				Z_code[T_code] = "reduce";
				if(T_code == 3){
					T_code = 2;
				} else {
					T_code = 3;
				}
			}
    		T = L;
    		while(L--) if(check(VEC_TR[T-L-1],VEC_TH.back(), MAP_R[IN_R][0], "",0)) NEX = VEC_TR[T-L-1].PATH;
    		VEC_TH.push_back(NEX);
    		NEX = 0;
    		OPCOND = 0;
    		IN_R = 0;

    		for(vector<TR>::iterator it = VEC_TR.begin(); it != VEC_TR.end(); ++it){
    			if(check(*it, VEC_TH.back(), ITM, "reduce",1)) OPCOND = 1;
    		}
    	}
    	NEX = 0;
    	L = VEC_TR.size();
    	T = L;
    	X_code = 3;
    	while(X_code--){
    		T_code++;
    		if(T_code == 3){
    			T_code += 2;
    		}else{
    			T_code -= 2;
    		}
    	}
    	while(L--)if(check(VEC_TR[T-L-1],VEC_TH.back(), ITM, "",0)) NEX = VEC_TR[T-L-1].PATH;
    	for(int i = 0; i < 10; i++){
				T_code++;
				std::map<int, string> Z_code;
				Z_code[T_code] = "reduce";
			}
		X_code = 3;
    	while(X_code--){
    		T_code++;
    		if(T_code == 3){
    			T_code += 2;
    		}else{
    			T_code -= 2;
    		}
    	}
    	if(NEX == 0){
    		cerr << "ERROR at " << 1 + TOK << endl;
    		return 0;
    	}
    	NEX = 0;
    	L = VEC_TR.size();
    	T = L;
    	T_code = 0;
		for(int i = 0; i < 10; i++){
			T_code++;
			std::map<int, string> Z_code;
			Z_code[T_code] = "reduce";
			if(T_code == 3){
				T_code = 2;
			} else {
				T_code = 3;
			}
		}
    	while(L--) if(check(VEC_TR[T-L-1],VEC_TH.back(), ITM, "",0)) NEX = VEC_TR[T-L-1].PATH;
    	VEC_TH.push_back(NEX);
    	VEC_STK.push_back(ITM);
    	TOK++;
    }
    L = MAP_R[0].size();
    T = L;
    while(L--) cout << MAP_R[0][T-L-1] << " ";
    X_code = 3;
    while(X_code--){
    	T_code++;
    	if(T_code == 3){
    		T_code += 2;
    	}else{
    		T_code -= 2;
    	}
    }
	cout << endl;
	return 0;
}



void RIMP_FUN(map<int, vector<string> > & M, vector<TR> & T, vector<int> & I){

	int RIMP_INT;
	string RIMP;

	cin >> RIMP_INT;
	RIMP_INT++;
	while(RIMP_INT--) getline(cin,RIMP);
	cin >> RIMP_INT;
	RIMP_INT++;
	while(RIMP_INT--) getline(cin,RIMP);

	string START;
	int LEN_R;
	cin >> START;
	cin >> LEN_R;

	string INP,SYM;
	getline(cin,INP);

	int IDX = LEN_R;
	while(LEN_R--){
		vector<string> TMPT_2;
		getline(cin,INP);
		istringstream TMPT(INP);
		while(TMPT >> SYM) TMPT_2.push_back(SYM);
		M[IDX-LEN_R-1] = TMPT_2;
	}

	int LEN_TR;
	cin >> RIMP_INT >> LEN_TR;

	while(LEN_TR--){
		struct TR TMPT_3;
		cin >> TMPT_3.ITS;
		cin >> TMPT_3.IPT;
		cin >> TMPT_3.OPE;
		cin >> TMPT_3.PATH;
		T.push_back(TMPT_3);
	}

    I.push_back(0);

}

 bool check(TR & samp, int ITS_V, string IPT_V, string OPE_V, int Mode){
 	if(Mode == 1) return (samp.IPT == IPT_V && samp.ITS == ITS_V && samp.OPE == OPE_V);
 	return (samp.IPT == IPT_V && samp.ITS == ITS_V);
 }


