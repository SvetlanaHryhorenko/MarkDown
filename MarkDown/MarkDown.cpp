// MarkDown.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include "Converter.h"





int main()
{
	std::string s, mys = "1.txt";
	std::ifstream myfile(mys);
	//std::ofstream myfile1(news);
	//myfile1.close();
	Converter c("1.html");
	while (getline(myfile, s))
	{
		c.convert(s);
	}

	

    return 0;
}

