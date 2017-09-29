#include "kind.h"
#include <iostream>
#include <sstream>
#include <map>
using std::map;
using std::string;
using std::istringstream;

namespace
{
const string kindStrings[] = {
	"COMMA", "SEMI", "RBRACK", "ERR", "IF",
	"ELSE", "WHILE", "PRINTLN", "WAIN", "BECOMES",
	"INT", "EQ", "STAR", "ID", "NUM", "LPAREN", "AMP",
	"NULL", "WHITESPACE", "NE", "LT", "GT", "COMMENT",
	"ZERO", "NEW", "DELETE", "LBRACK", "RPAREN", "LBRACE",
	"RBRACE", "RETURN", "LE", "SLASH", "BANG", "GE", "PLUS",
	"MINUS", "PCT"};
};

WCMSP::Token::Token(WCMSP::Kind kind, string lexeme)
{
	if (kind == ID)
	{
		if (lexeme == "return")
		{
			this->kind = WCMSP::RETURN;
		}
		else if (lexeme == "if")
		{
			this->kind = WCMSP::IF;
		}
		else if (lexeme == "else")
		{
			this->kind = WCMSP::ELSE;
		}
		else if (lexeme == "while")
		{
			this->kind = WCMSP::WHILE;
		}
		else if (lexeme == "println")
		{
			this->kind = WCMSP::PRINTLN;
		}
		else if (lexeme == "wain")
		{
			this->kind = WCMSP::WAIN;
		}
		else if (lexeme == "int")
		{
			this->kind = WCMSP::INT;
		}
		else if (lexeme == "new")
		{
			this->kind = WCMSP::NEW;
		}
		else if (lexeme == "delete")
		{
			this->kind = WCMSP::DELETE;
		}
		else if (lexeme == "NULL")
		{
			this->kind = WCMSP::_NULL;
		}
		else
		{
			this->kind = kind;
		}
	}
	else
	{
		this->kind = kind;
	}
	this->lexeme = lexeme;
};

string WCMSP::Token::toString() const
{
	return ::kindStrings[kind];
};

string WCMSP::Token::getLexeme() const
{
	return lexeme;
};

WCMSP::Kind WCMSP::Token::getKind() const
{
	return kind;
};

std::ostream &WCMSP::operator<<(std::ostream &out, const WCMSP::Token &t)
{

	out << t.toString() << " " << t.getLexeme();
	return out;
};

WCMSP::Token *WCMSP::Token::makeToken(WCMSP::Kind kind, string lexeme)
{
	return new Token(kind, lexeme);
};
