#pragma once
#include <string>

class Myu
{
public:
	Myu();
	~Myu();

private:

	struct state
	{
		std::string name = "みゅーちゃん";
		int exp;
		int level;
		int hunger;
	};
};

