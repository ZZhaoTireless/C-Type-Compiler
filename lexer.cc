#include "kind.h"
#include "lexer.h"
#include <string>
using std::string;
using std::vector;

const string whitespace = " \t\n\r";
const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string digits  = "0123456789";
const string oneToNine = "123456789";

const string tmpt = "012";

namespace {

	WCMSP::Kind stateKinds[] = {
		WCMSP::GT, WCMSP::GE, WCMSP::LBRACK, WCMSP::SLASH, 
		WCMSP::PLUS, WCMSP::MINUS, WCMSP::LE, WCMSP::SEMI,
		WCMSP::RBRACK, WCMSP::AMP, WCMSP::WHITESPACE,
		WCMSP::WHITESPACE, WCMSP::ERR, WCMSP::ERR, WCMSP::NUM, 
		WCMSP::NUM, WCMSP::LPAREN, WCMSP::RPAREN, WCMSP::NE,  
		WCMSP::LBRACE, WCMSP::RBRACE,WCMSP::BECOMES,WCMSP::ID, 
		WCMSP::PCT, WCMSP::COMMA, WCMSP::EQ,
		WCMSP::ERR, WCMSP::LT, WCMSP::STAR, WCMSP::ERR
  	};
}; 

WCMSP::Lexer::Lexer() {
	

	for (int i = 0; i < maxStates; ++i) {
		for (int j=0; j < maxTrans; ++j) {
			delta[i][j] = SEC_ERR;
		}
	}
	
	setTrans(SEC_START, whitespace, SEC_WHITESPACE);
	setTrans(SEC_START, letters,	SEC_ID);
	setTrans(SEC_START, oneToNine, SEC_NUM);
	setTrans(SEC_START, "0", SEC_ZERO);
	setTrans(SEC_ZERO, letters+digits, SEC_DEB);
	setTrans(SEC_START, "+", SEC_PLUS);
    setTrans(SEC_START, "-", SEC_MINUS);
    setTrans(SEC_START, "*", SEC_STAR);
    setTrans(SEC_START, "/", SEC_SLASH);
    setTrans(SEC_START, "%", SEC_PCT);
    setTrans(SEC_START, ",", SEC_COMMA);
    setTrans(SEC_START, ";", SEC_SEMI);
    setTrans(SEC_START, "&", SEC_AMP);
    setTrans(SEC_START, "(", SEC_LPAREN);
    setTrans(SEC_START, ")", SEC_RPAREN);
    setTrans(SEC_START, "{", SEC_LBRACE);
    setTrans(SEC_START, "}", SEC_RBRACE);
    setTrans(SEC_START, "[", SEC_LBRACK);
    setTrans(SEC_START, "]", SEC_RBRACK);
    setTrans(SEC_START, "=", SEC_BECOMES);
    setTrans(SEC_START, "<", SEC_LT);
    setTrans(SEC_START, ">", SEC_GT);
    setTrans(SEC_START, "!", SEC_BANG);
	setTrans(SEC_ID, letters+digits, SEC_ID);
	setTrans(SEC_NUM, digits, SEC_NUM	);
	setTrans(SEC_WHITESPACE, whitespace, SEC_WHITESPACE);
    setTrans(SEC_BECOMES, "=", SEC_EQ);
    setTrans(SEC_SLASH, "/", SEC_COMMENT);
    setTrans(SEC_BANG, "=", SEC_NE);
    setTrans(SEC_LT, "=", SEC_LE);
    setTrans(SEC_GT, "=", SEC_GE);

    for (int j=0; j < maxTrans; j++) {delta[SEC_COMMENT][j] = SEC_COMMENT;};

}  


void WCMSP::Lexer::setTrans(WCMSP::State from, const string& chars, WCMSP::State to) {

	for (string::const_iterator it = chars.begin(); it != chars.end(); ++it) {
		delta[from][static_cast<unsigned int>(*it)] = to;

	}
}

vector<WCMSP::Token*> WCMSP::Lexer::scan(const string& line) {

	vector<Token*> ret;

	if (line.size() == 0) return ret;

	State Now_ST = SEC_START;

	string::const_iterator startIter = line.begin();

	string::const_iterator it = line.begin();

	while(true) {
		
		State nextState = SEC_ERR;

		if (it != line.end()) nextState = delta[Now_ST][static_cast<unsigned int>(*it)];
		
		if (nextState == SEC_ERR && Now_ST != SEC_DEB) {

			Kind currKind = stateKinds[Now_ST]; 

			if (currKind == ERR) {

				vector<Token*>::iterator vit;

				for(vit = ret.begin(); vit != ret.end(); ++vit) delete *vit;

				throw "ERROR: " + string(line.begin(),it);
			};
			
			if(currKind != WHITESPACE) ret.push_back(Token::makeToken(currKind, string(startIter, it)));
			
			startIter = it;
			
			Now_ST = SEC_START;

			if (it == line.end()) break;

		} else {

			Now_ST = nextState;

			++it;
		};
	};

	return ret;
};


