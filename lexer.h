# ifndef __LEXER_H__
# define __LEXER_H__
# include <string>
# include <vector>

namespace WCMSP{

	enum State {
		SEC_GT,SEC_GE,SEC_LBRACK,SEC_SLASH,SEC_PLUS,
		SEC_MINUS, SEC_LE,SEC_SEMI,SEC_RBRACK,SEC_AMP,
		SEC_WHITESPACE,SEC_COMMENT,SEC_ERR,SEC_START,
		SEC_ZERO,SEC_NUM,SEC_LPAREN,SEC_RPAREN,SEC_NE,  
		SEC_LBRACE,SEC_RBRACE,SEC_BECOMES,SEC_ID,SEC_PCT,
		SEC_COMMA,SEC_EQ,SEC_BANG,SEC_LT,SEC_STAR, SEC_DEB
	};

	class Token;

	class Lexer {
		static const int maxStates = 71; 
		static const int maxTrans = 256;
		State delta[maxStates][maxTrans];
		void setTrans(State from, const std::string& chars, State to);
	public:
		Lexer();
		std::vector<Token*> scan(const std::string& line);

	};

}

# endif 