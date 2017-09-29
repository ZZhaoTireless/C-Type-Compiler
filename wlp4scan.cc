#include "lexer.h"
#include "kind.h"
#include <iostream>
#include <string>
#include <vector>

using WCMSP::Token;
using WCMSP::Lexer;
using std::vector;
using std::string;

int main(int argc, char *argv[])
{

	vector<vector<Token *>> tokLines;

	try
	{
		Lexer Sample;

		string line;

		vector<vector<Token *>>::iterator v1;

		vector<Token *>::iterator v2;

		while (getline(std::cin, line))
			tokLines.push_back(Sample.scan(line));

		for (v1 = tokLines.begin(); v1 != tokLines.end(); ++v1)
		{

			for (v2 = (*v1).begin(); v2 != (*v1).end(); ++v2)
			{

				std::cout << *(*v2) << std::endl;
			}
		}
	}
	catch (string err)
	{
		std::cerr << err << std::endl;
	}

	vector<vector<Token *>>::iterator it;
	for (it = tokLines.begin(); it != tokLines.end(); ++it)
	{
		vector<Token *>::iterator it2;
		for (it2 = it->begin(); it2 != it->end(); ++it2)
		{
			delete *it2;
		}
	}
}
