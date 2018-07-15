#pragma once
class Converter
{
public:
	Converter();
	Converter(std::string  );
	~Converter();

	
	void convert(std::string );
private:
	std::ofstream file;
	std::string current;
	std::string global = "<p>";
	bool bullet = false;
	bool numbered = false;

	void global_to_file();
	void current_to_file();
	//void list_to_file();
	int count_headings();
	bool headings();
	void bold(std::string &);
	void italic(std::string &);
	//void links(std::string);
	void bullet_list();
	void numbered_list();
	//bool count_list();
};

