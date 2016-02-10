# ifndef __KIND_H__
# define __KIND_H__
# include <iostream>
# include <string>

namespace WCMSP{
	
	
	enum Kind {
		COMMA, SEMI, RBRACK, ERR, IF, 
		ELSE, WHILE, PRINTLN, WAIN, BECOMES, 
		INT, EQ, STAR, ID, NUM, LPAREN, AMP, 
		_NULL, WHITESPACE, NE, LT, GT, COMMENT,  
		ZERO, NEW, DELETE, LBRACK,RPAREN, LBRACE, 
		RBRACE, RETURN, LE, SLASH, BANG,GE,PLUS, 
		MINUS, PCT
	};

	class Token{
	protected:
		
		Kind kind;
		std::string lexeme;	
	public: 
    	static Token* makeToken(Kind kind, std::string lexeme);
    	Token(Kind kind, std::string lexeme);
    	std::string toString() const;
    	std::string getLexeme() const;
    	Kind getKind() const;
	};

  	std::ostream& operator<<(std::ostream& out, const Token& t);
}


# endif
