# include <iostream>
# include <map>
# include <sstream>
# include <string>
# include <vector>
# include <fstream>
# include <utility>

using namespace std;


struct paraTree { 

	paraTree(){};
	~paraTree() {
		for(vector<paraTree*>::iterator it=subTR_vec.begin(); it!=subTR_vec.end(); it++) delete *it;
	};
	string Rl_str;
	vector<string> Rl_vec;
	vector<paraTree*> subTR_vec;
};

map<string, map<string, pair <string, int> > > SYM_ST_map;

string Terminate_ST[35];

int if_N_Ter(string &str);

paraTree* creat_TR();

int offset = 0;

int LPNUM = 0;

int CONDNUM = 0;

int DETE = 0;

int VAL = 0;

void dcl(paraTree* TR_POT, string PRO_Key, string &TY);

string re_type(paraTree* TR_POT);

string ret_para_TY(paraTree* TR_POT, string PRO_Key, int BO);

void crt_TBL(paraTree* TR_POT);

void prt_TBL();

void lis_w(int reg, int Lab_MIP, string lab, int sel);

void r_ty(int res, int in1, int in2, int sel);

void be_eq(int com1, int com2, string lab, int order, int sel);

void mip_fun(paraTree* TR_POT);

string getTY_check(paraTree * , string);

int main() {
	fstream TERM;
	TERM.open("wlp4T");
	string INP;
	for(int i = 0; i < 35; i++){
		TERM >> INP;
		Terminate_ST[i] = INP;
	}
	TERM.close();
	try{
		paraTree* TR_POT = creat_TR();
		crt_TBL(TR_POT);
		mip_fun(TR_POT);
		delete TR_POT;
	} catch(string msg) {
		cerr << msg << endl;
	}
	return 0;
}

string PR_str = "procedure INT ID LPAREN params RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE";


int if_N_Ter(string &str) {
  for(int i = 0; i < 35; i++) if(str == Terminate_ST[i]) return 0;
  return 1;
}

string BO = "";

vector<string> PRO_vec; 
map< string, pair <string , int> > PRO_ST_map; 

void prt_TBL() {
	int len = 0;
	for (vector<string>::iterator it1 = PRO_vec.begin(); it1 != PRO_vec.end(); it1++) len++;
	for (vector<string>::iterator it1 = PRO_vec.begin(); it1 != PRO_vec.end(); it1++) {
		cerr << *it1 << endl;
		for (map<string, pair<string,int> >::iterator it4 = SYM_ST_map[*it1].begin(); it4 != SYM_ST_map[*it1].end(); it4++) 
		    cerr << it4->first << " " << (it4->second).first << endl;
			if(len == 1) continue;
			cerr << endl;
			len--;
	}
}


paraTree* creat_TR() {
	string error = "ERROR3";
	paraTree* TR_POT = new paraTree();
	string line;
	string IPT;
	getline(cin, line);
	if(cin.fail()) throw error;
    stringstream ss(line);
    TR_POT->Rl_str = line;
    while(ss >> IPT) TR_POT->Rl_vec.push_back(IPT);
    if (if_N_Ter(BO)) {
    	int len = TR_POT->Rl_vec.size();
    	for (int i=1; i < len; ++i) {
    		BO = TR_POT->Rl_vec[i];
    		TR_POT->subTR_vec.push_back(creat_TR());
    	}
    }
    return TR_POT;
};

void dcl(paraTree* TR_POT, string PRO_Key, string &TY){
	string error = "ERROR2";
	string DUP_str;
	TY = re_type(TR_POT);
	DUP_str = TR_POT->subTR_vec[1]->Rl_vec[1];
	bool if_eq = SYM_ST_map[PRO_Key].find(DUP_str) == SYM_ST_map[PRO_Key].end();
	if (!if_eq) throw error;
	else {
		SYM_ST_map[PRO_Key][DUP_str] = make_pair(TY, offset);
		offset -= 4;
	}
}

string re_type(paraTree* TR_POT){
	string TY;
	string start = TR_POT->subTR_vec[0]->Rl_vec.back();
	if (start == "INT") TY = "int";
	else TY = "int*";
	return TY;
}

string ret_para_TY(paraTree* TR_POT, string PRO_Key, int BO) {
	string TY;
	string TY_Ptwo;
	int len = TR_POT->subTR_vec.size();
	if(BO == 0){
		bool DCL_BO = TR_POT->Rl_str != "dcl type ID";
		if (DCL_BO) {
			for (int i = 0; i < len; ++i){
				TY_Ptwo = ret_para_TY(TR_POT->subTR_vec[i], PRO_Key, BO);
				TY = TY +" "+ TY_Ptwo;
			}
		} else {
			dcl(TR_POT, PRO_Key, TY);
		}
	} 
	if(BO == 1){
		TY = re_type(TR_POT);
}
	return TY;
};

void crt_Pro_TBL(paraTree* TR_POT, string PRO_Key) {
	string error = "ERROR1";
	bool DCL_BO = TR_POT->Rl_str != "dcl type ID";
	if (!DCL_BO) {
		string TY;
		dcl(TR_POT, PRO_Key, TY);
	} else {
		string front = TR_POT->Rl_vec.front();
		string back = TR_POT->Rl_vec.back();
		bool dup = SYM_ST_map[PRO_Key].find(back) == SYM_ST_map[PRO_Key].end();
		if ((front == "ID") && dup){
			bool dup = true;
			string item = TR_POT->Rl_vec.back();
			vector<string>::iterator it;
			for(it = PRO_vec.begin(); it != PRO_vec.end(); it++) if(*it == item) dup = false;
			if(dup) throw error;
		}
	}
	int len = TR_POT->subTR_vec.size();
	for (int i = 0; i < len; ++i) crt_Pro_TBL(TR_POT->subTR_vec[i], PRO_Key);
};


void crt_TBL(paraTree* TR_POT) {
	string T1,T2;
	string error = "ERROR0";
	string PRO_Key;
	string pre_str;
	bool dup = true;
	bool if_p = TR_POT->Rl_str == PR_str;
	bool if_w = TR_POT->Rl_str == "procedures main";
	if (if_w) {
		pre_str = ret_para_TY(TR_POT->subTR_vec[0]->subTR_vec[3],"" ,1) + " " +
		 		  ret_para_TY(TR_POT->subTR_vec[0]->subTR_vec[5],"", 1); 
		PRO_Key = "wain";
	}
	if (if_p) {
		PRO_Key = TR_POT->subTR_vec[1]->Rl_vec[1];
		pre_str = ret_para_TY(TR_POT->subTR_vec[3], PRO_Key, 0);
		dup = PRO_ST_map.find(PRO_Key) == PRO_ST_map.end();

	} 
	if(if_p||if_w)PRO_vec.push_back(PRO_Key);

	if(dup) {
		string new_str = "";
		string IPT;
		if(pre_str!=""){
			stringstream ss(pre_str);
			while(ss >> IPT) new_str = new_str + " " + IPT;
		}
		PRO_ST_map[PRO_Key] = make_pair(new_str, offset);
	} else throw error;
	int arr[3] = {6,7,9};
	if(if_p) {
		for(int i = 0; i < 3; i++) crt_Pro_TBL(TR_POT->subTR_vec[arr[i]], PRO_Key);
	}
	if(if_w) crt_Pro_TBL(TR_POT->subTR_vec[0], "wain");

	int len = TR_POT->subTR_vec.size();
	for (int i=0; i < len; ++i) crt_TBL(TR_POT->subTR_vec[i]);
}


void lis_w(int reg, int Lab_MIP, string lab, int sel){
	if( sel == 0){
		cout << "lis $" << reg << endl;
		cout << ".word "<< Lab_MIP << endl;
	}
	if (sel == 1){
		cout << "lis $" << reg << endl;
		cout << ".word "<< lab << endl;
	}
}

void r_ty(int res, int in1, int in2, int sel){
	if(sel == 0){ 
		cout << "add $"<< res <<", $"<< in1 <<", $"<< in2 << endl;
	}

	if(sel == 1){
		cout << "sub $"<< res <<", $"<< in1 <<", $"<< in2 << endl;
	}

	if(sel == 2){
		cout << "lw $"<< res <<", "<< in1 <<"($"<< in2 <<")" << endl;
	}

	if(sel == 3){
		cout << "sw $"<< res <<", "<< in1 <<"($"<< in2 <<")" << endl;
	}

	if(sel == 4){
		cout << "slt $"<< res <<", $"<< in1 <<", $"<< in2 << endl;
	}

	if(sel == 5){
		cout << "bne $"<< res <<", $"<< in1 <<", "<< in2 << endl;
	}

}

void be_eq(int com1, int com2, string lab, int order, int sel){
	if(sel == 0) {
		cout << "beq $"<< com1 << ", $"<< com2 <<", "<< lab << order << endl;
	}

	if(sel == 1) {
		cout << "beq $"<< com1 << ", $"<< com2 <<", "<< lab << endl;
	}
}

void mul_div(int fir, int sec, int sel){
	if(sel == 0) cout <<"mult $"<< fir <<", $"<< sec << endl;
	if(sel == 1) cout <<"div $"<< fir <<", $"<< sec << endl;
	if(sel == 2) cout <<"mfhi $"<< fir << endl;
	if(sel == 3) cout <<"mflo $"<< fir << endl;
}

void mip_fun(paraTree* TR_POT){
	stringstream ss(TR_POT->Rl_str);
	string first_w, second_w, third_w, fourth_w, fif_w;
	ss >> first_w >> second_w >> third_w >> fourth_w >> fif_w;

	if(first_w == "start") mip_fun(TR_POT->subTR_vec[1]);

	if(second_w == "main"){
			string check = getTY_check(TR_POT->subTR_vec[0]->subTR_vec[3], "wain");
			cout << ".import print" << endl;
			cout << ".import new" << endl;
			cout << ".import delete" << endl;
			cout << ".import init" << endl;
			lis_w(4,4,"",0);
			lis_w(11,1,"",0);
			r_ty(29,30,4,1);
			r_ty(1,-4,30,3);
			r_ty(30,30,4,1);
			r_ty(2,-4,30,3);
			r_ty(30,30,4,1);
			r_ty(31,-4,30,3);
			r_ty(30,30,4,1);
			if(check == "int"){
				r_ty(2,0,0,0);
			}
			lis_w(5,0,"init",1);
			cout << "jalr $5" << endl;
			r_ty(30,30,4,0);
			r_ty(31,-4,30,2);
			mip_fun(TR_POT->subTR_vec[0]);
			r_ty(30,29,4,0);
			cout << "jr $31" << endl;
		}
	if(first_w == "main"){
			mip_fun(TR_POT->subTR_vec[8]);
			mip_fun(TR_POT->subTR_vec[9]);
			mip_fun(TR_POT->subTR_vec[11]);
		}

	if(first_w == "dcls"){

		if(fif_w == "NUM"){
			mip_fun(TR_POT->subTR_vec[0]);
			string Lab_MIP = TR_POT->subTR_vec[3]->Rl_vec[1];
			string PRE_POS = TR_POT->subTR_vec[1]->subTR_vec[1]->Rl_vec[1];
			int offset = SYM_ST_map["wain"][PRE_POS].second;
			lis_w(5,0,Lab_MIP,1);
			r_ty(5,offset,29,3);
			r_ty(30,30,4,1);
		}

		if(fif_w == "NULL"){
			mip_fun(TR_POT->subTR_vec[0]);
			r_ty(3,0,11,0);
		}
	}

	if(first_w == "expr"){
			
		if(third_w == "") mip_fun(TR_POT->subTR_vec[0]);
		
		if(third_w == "PLUS"){
			bool TY_1 = (getTY_check(TR_POT->subTR_vec[0], "wain") == "int");
			bool TY_2 = (getTY_check(TR_POT->subTR_vec[2], "wain") == "int");
			if(TY_1 && TY_2){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,5,3,0);
			} else if((!TY_1) && TY_2){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(3,3,3,0);
				r_ty(3,3,3,0);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,5,3,0);
			} else if(TY_1 && (!TY_2)){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,3,3,0);
				r_ty(3,3,3,0);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,5,3,0);
			}
		}
		if(third_w == "MINUS"){
			bool TY_1 = (getTY_check(TR_POT->subTR_vec[0], "wain") == "int");
			bool TY_2 = (getTY_check(TR_POT->subTR_vec[2], "wain") == "int");
			if(TY_1 && TY_2){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,5,3,1);
			} else if ((!TY_1) && TY_2) {
				VAL = 0;
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(3,3,3,0);
				r_ty(3,3,3,0);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,5,3,1);
			} else if(!(TY_1||TY_2)){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,5,3,1);
				cout<<"div $3,$4"<<endl;
      			cout<<"mflo $3"<<endl;
			}

		}
	}

	if(first_w == "statement"){

			if(second_w == "lvalue"){
				mip_fun(TR_POT->subTR_vec[2]);
				mip_fun(TR_POT->subTR_vec[0]);
			}

			if(second_w == "PRINTLN"){
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(1,3,0,0);
				r_ty(31,-4,30,3);
				r_ty(30,30,4,1);
				lis_w(5,0,"print",1);
				cout << "jalr $5" << endl;
				r_ty(30,30,4,0);
				r_ty(31,-4,30,2);
			}

			if(second_w == "WHILE"){
				int x = LPNUM;
				LPNUM++;
				cout << "start" << x << ":" << endl;
				mip_fun(TR_POT->subTR_vec[2]);
				be_eq(3,0,"ends",x,0);
				mip_fun(TR_POT->subTR_vec[5]);
				be_eq(0,0,"start",x,0);
				cout << "ends" << x << ":" << endl;
			}

			if(second_w == "IF"){
				int x = CONDNUM;
				CONDNUM++;
				mip_fun(TR_POT->subTR_vec[2]);
				be_eq(3,0,"goto",x,0);
				mip_fun(TR_POT->subTR_vec[5]);
				be_eq(0,0,"fi",x,0);
				cout << "goto" << x << ":" << endl;
				mip_fun(TR_POT->subTR_vec[9]);
				cout << "fi" << x << ":" << endl;
			}

			if(second_w == "DELETE"){
				int De = DETE;
				De += 1;
				mip_fun(TR_POT->subTR_vec[3]);
				be_eq(3,11,"dover",De,0);
				r_ty(1,3,0,0);
				r_ty(31,-4,30,3);
				r_ty(30,30,4,1);
				lis_w(5,0,"delete",1);
				cout << "jalr $5" << endl;
				r_ty(30,30,4,0);
				r_ty(31,-4,30,2);
				cout << "dover" << De << ":" << endl;
			}

		}
		
	if(first_w == "lvalue"){
			if(second_w == "ID"){
				string PRE_POS = TR_POT->subTR_vec[0]->Rl_vec[1];
				int offset = SYM_ST_map["wain"][PRE_POS].second;
				if(VAL == 0){
					r_ty(3,offset,29,3);
					r_ty(30,30,4,1);
				} else if(VAL == 1){
					lis_w(3,offset,"",0);
					r_ty(3,29,3,0);
					VAL = 0;
				}
			}
			if(second_w == "LPAREN"){
				mip_fun(TR_POT->subTR_vec[1]);
			}

			if(second_w == "STAR"){
				if(VAL == 0){}
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[1]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(5,0,3,3);
			}
		}
	if(first_w == "term"){

			if(third_w == "") mip_fun(TR_POT->subTR_vec[0]);

			if(third_w == "PCT"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				mul_div(5,3,1);
				mul_div(3,0,2);
			}
			if(third_w == "STAR"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				mul_div(5,3,0);
				mul_div(3,0,3);
			}
			if(third_w == "SLASH"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				mul_div(5,3,1);
				mul_div(3,0,3);
			}
	}
	if(first_w == "statements"){
			if(second_w == "statements"){
				mip_fun(TR_POT->subTR_vec[0]);
				mip_fun(TR_POT->subTR_vec[1]);
			}
		}
	if(first_w == "test"){
			if(third_w == "EQ"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(6,3,5,4);
				r_ty(7,5,3,4);
				r_ty(3,6,7,0);
				r_ty(3,11,3,1);
			}
			if(third_w == "NE"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(6,3,5,4);
				r_ty(7,5,3,4);
				r_ty(3,6,7,0);
			}
			if(third_w == "LE"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,3,5,4);
				r_ty(3,11,3,1);
			}

			if ( third_w == "LT"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,5,3,4);
			}

			if(third_w == "GE"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,5,3,4);
				r_ty(3,11,3,1);
			}
			if(third_w == "GT"){
				mip_fun(TR_POT->subTR_vec[0]);
				r_ty(3,-4,30,3);
				r_ty(30,30,4,1);
				mip_fun(TR_POT->subTR_vec[2]);
				r_ty(30,30,4,0);
				r_ty(5,-4,30,2);
				r_ty(3,3,5,4);
			}
		}

	if(first_w == "factor"){
		
			if(second_w == "ID"){
				string PRE_POS = TR_POT->subTR_vec[0]->Rl_vec[1];
				int offset = SYM_ST_map["wain"][PRE_POS].second;
				r_ty(3,offset,29,2);
			} 
			if(second_w == "LPAREN") {
				mip_fun(TR_POT->subTR_vec[1]);
			}

			if(second_w == "NUM"){
				string num_str = TR_POT->subTR_vec[0]->Rl_vec[1];
				lis_w(3,0,num_str,1);
			}

			if(second_w == "NULL"){
				r_ty(3,0,11,0);
			}

			if(second_w == "STAR"){
				mip_fun(TR_POT->subTR_vec[1]);
				r_ty(3,0,3,2);
			}

			if(second_w == "AMP"){
				VAL = 1;
				mip_fun(TR_POT->subTR_vec[1]);
			}

			if(second_w == "NEW"){
				mip_fun(TR_POT->subTR_vec[3]);
				r_ty(1,3,0,0);
				r_ty(31,-4,30,3);
				r_ty(30,30,4,1);
				lis_w(5,0,"new",1);
				cout << "jalr $5" << endl;
				r_ty(30,30,4,0);
				r_ty(31,-4,30,2);
				r_ty(0,3,1,5);
				r_ty(3,11,0,0);
			}
	}		
}

string getTY_check(paraTree * TR_POT, string PRO_Key){

  stringstream ss(TR_POT->Rl_str);
  string first_w, second_w, third_w, fourth_w, fif_w, TY_check;
  ss >> first_w >> second_w >> third_w >> fourth_w >> fif_w;
  string err = "ERROR";
  
  if(first_w == "type"){
    if(second_w == "INT") TY_check = "int";
    if(third_w == "STAR") TY_check = "int*";
  } else if(first_w == "dcl"){
  	TY_check = getTY_check(TR_POT->subTR_vec[0],PRO_Key);
  } else if(first_w == "term"){
    if(second_w == "factor"){
      TY_check = getTY_check(TR_POT->subTR_vec[0],PRO_Key);
    } else if(third_w == "STAR" || third_w == "SLASH" || third_w == "PCT"){
      bool PRO_K2 = (getTY_check(TR_POT->subTR_vec[0],PRO_Key) == "int");
      bool PRO_K3 = (getTY_check(TR_POT->subTR_vec[2],PRO_Key) == "int");
      if(PRO_K2 && PRO_K3) TY_check = "int";
      else throw err;
    }
  } else if( first_w == "factor"){
    if(second_w == "ID"){
      string idx = TR_POT->subTR_vec[0]->Rl_vec[1];
      TY_check = SYM_ST_map[PRO_Key][idx].first;
      } else if(second_w == "NULL"){
         TY_check = "int*";
      } else if(second_w == "STAR"){
        string inv1 = getTY_check(TR_POT->subTR_vec[1],PRO_Key);
         if(inv1 == "int*"){
          TY_check = "int";
         } else throw err;
      } else if(second_w == "LPAREN"){
         TY_check = getTY_check(TR_POT->subTR_vec[1],PRO_Key);
      } else if(second_w == "NUM"){ 
         TY_check = "int";
      } else if(second_w == "AMP"){
         string inv0 = getTY_check(TR_POT->subTR_vec[1],PRO_Key);
         if(inv0 == "int"){
          TY_check = "int*";
         } else throw err;
      } else if(second_w == "NEW"){
        string inv2 = getTY_check(TR_POT->subTR_vec[3],PRO_Key);
         if(inv2 == "int"){
          TY_check = "int*";
         } else throw err;
      }
  } else if(first_w == "lvalue"){
    if(second_w == "ID"){
        string PRO_K0 = TR_POT->subTR_vec[0]->Rl_vec[1];
        if(SYM_ST_map[PRO_Key].count(PRO_K0) == 0) {
          throw err;
        } else {
          map<string, pair <string, int> >::iterator it = SYM_ST_map[PRO_Key].find(PRO_K0);
          TY_check = ((*it).second).first;
        }
    } else if( second_w == "STAR"){
        string PRO_K1 = getTY_check(TR_POT->subTR_vec[1],PRO_Key);
        if(PRO_K1 == "int*") {
          TY_check = "int";
        } else {
          throw err;
        }
    } else if(second_w == "LPAREN"){
      TY_check = getTY_check(TR_POT->subTR_vec[1],PRO_Key);
    }
  } else if(first_w == "expr"){
    if(second_w == "term"){
      TY_check = getTY_check(TR_POT->subTR_vec[0],PRO_Key);
    } else if(third_w == "MINUS"){
      bool PRO_K2 = (getTY_check(TR_POT->subTR_vec[0],PRO_Key) == "int");
      bool PRO_K3 = (getTY_check(TR_POT->subTR_vec[2],PRO_Key) == "int");
      if(PRO_K2 && PRO_K3) TY_check = "int";
      else if (!(PRO_K2 || PRO_K3)) TY_check = "int";
      else if (PRO_K3 || (!PRO_K2)) TY_check = "int*";
      else throw err; 
    } else if(third_w == "PLUS"){
      bool PRO_K2 = (getTY_check(TR_POT->subTR_vec[0],PRO_Key) == "int");
      bool PRO_K3 = (getTY_check(TR_POT->subTR_vec[2],PRO_Key) == "int");
      if(PRO_K2 && PRO_K3) TY_check = "int";
      else if (PRO_K2 || PRO_K3) TY_check = "int*";
      else throw err; 
    }
  }

  return TY_check;
} 



