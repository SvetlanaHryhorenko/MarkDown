#include "stdafx.h"
#include <string>
#include <fstream>
#include "Converter.h"


Converter::Converter()
{
}

Converter::Converter(std::string s):
	file(s)
{
	
}


Converter::~Converter()
{
	global.append("</p>\n");
	file << global;
	file.close();
}


void Converter::convert(std::string s)
{
	current = s;
	if (headings()) return;
	bullet_list();
	numbered_list();
		if (!bullet && !numbered)
		{
			if (s.empty()) global_to_file();
			global.append(current);
		}
		else
		{
			if (s.empty()) return;
			if (bullet || numbered)
			{
				current_to_file();
			}
			else
			{
				global.append(current);
			}
		}

}


void Converter::global_to_file()
{
	bold(global);
	italic(global);
	global.append("</p>\n ");
	file << global;
	global = "<p>";
}

void Converter::current_to_file()
{
	bold(current);
	italic(current);
	
	file << current;
	
}


int Converter::count_headings()
{
	if (current[0] != '#') return 0;
	for (int i =1; i < 7; i++)
	{
		if (current[i] != '#') return i;
	}
	return 0;
}

bool Converter::headings()
{
	int headings = count_headings();
	if (headings > 0)
	{
		current.erase(current.begin(), current.begin() + headings);
		current.insert(0, "<h");
		current.insert(2, std::to_string(headings));
		current.insert(3, ">");
		current.append("</h");
		current.append(std::to_string(headings));
		current.append(">");
		current_to_file();
		return true;
	}
	return false;
}


void Converter::bold( std::string &str)
{
	int start = -1;
	for (int i = 0; i < str.size()-1; i++)
	{
		if ((str[i]=='*')&& (str[i+1] == '*'))
		{
			if (start==-1)
			{
				start = i;
			}
			else
			{
				str.erase(str.begin() + start, str.begin() + start + 2);
				str.erase(str.begin() + i - 2, str.begin() + i );
				str.insert(i - 2, "</strong>");
				str.insert(start, "<strong>");
				start = -1;
			}
		}
	}
}


void Converter::italic(std::string &str)
{
	int start = -1;
	for (int i = 0; i < str.size() - 1; i++)
	{
		if ((str[i] == '*'))
		{
			if (start == -1)
			{
				start = i;
			}
			else
			{
				str.erase(str.begin() + start);
				str.erase(str.begin() + i - 1);
				str.insert(i - 1, "</em>");
				str.insert(start, "<em>");
				start = -1;
			}
		}
	}
}
/*
void Converter::links()
{
	std::string name;
	std::string link;
	for (int i = 0; i < global.size() - 5; i++)
	{
		if ((global[i] == '['))
		{
			i++;
			while (global[i] != ']')
			{
				name.push_back(global[i]);
				i++;
			}
			i++;
			if (global[i]!='(')
			{
				name.clear();
				continue;
			}
			else
			{
				i++;
				while (global[i] != ')')
				{
					link.push_back(global[i]);
					i++;
				}
			}
		}
	}
}
*/

void Converter::bullet_list()
{
	if (current.empty()) return;
	if ((current[0] == '*') && (current[1] == ' '))
	{
		if (!bullet) file<<"<ul>";
		bullet = true;
		current.erase(current.begin(), current.begin()+1);
		current.insert(0, "<li>");
		current.append("</li>\n");
	}
	else
	{
		if(bullet) file << "</ul>";
		bullet = false;
	}
}


void Converter::numbered_list()
{
	if (isdigit(current[0]) && (current[1] == '.') && (current[2] == ' '))
	{
		if (!numbered) file << "<ol>";
		numbered = true;
		current.erase(current.begin(), current.begin() + 2);
		current.insert(0, "<li>");
		current.append("</li>\n");
	}
	else
	{
		if (numbered) file << "</ol>";
		numbered = false;
	}
}
