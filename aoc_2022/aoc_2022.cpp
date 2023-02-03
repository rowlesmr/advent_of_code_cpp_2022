// aoc_2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>
#include <unordered_map>
#include <cmath>
#include <unordered_set>
#include <functional>


#if 0

std::vector<std::string> split(const std::string& s)
{
	std::stringstream ss{ s };
	std::vector<std::string> words;
	for (std::string w; ss >> w; )
	{
		std::cout << w << '\n';
		words.push_back(w);
	}
	return words;
}


int one()
{
	int elf{ 1 };
	int tot_calories{ 0 };

	int most_elf{ 0 };
	int most_calories{ 0 };

	std::ifstream file_in("1.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;
	while (std::getline(file_in, line))
	{
		std::istringstream iss(line);
		std::string val{};

		iss >> val;

		if (val.empty())
		{
			if (tot_calories > most_calories)
			{
				most_calories = tot_calories;
				most_elf = elf;
			}
			elf++;
			tot_calories = 0;
		}
		else
		{
			tot_calories += std::stoi(val);
		}
	}

	//std::cout << "Elf " << most_elf << " has " << most_calories << " calories.\n";

	return most_calories;
}

int one_2()
{
	int tot_calories{ 0 };
	std::vector<int> elf_load{};

	std::ifstream file_in("1.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;
	while (std::getline(file_in, line))
	{
		std::istringstream iss(line);
		std::string val{};

		iss >> val;

		if (val.empty())
		{
			elf_load.push_back(tot_calories);
			tot_calories = 0;
		}
		else
		{
			tot_calories += std::stoi(val);
		}
	}

	std::sort(elf_load.begin(), elf_load.end(), std::greater<int>());
	int most_calories{ 0 };
	for (size_t i{ 0 }; i < 3 && i < elf_load.size(); ++i)
	{
		most_calories += elf_load[i];
	}


	return most_calories;
}



int two_outcome(const char them, const char me)
{
	int win{ 6 };
	int lose{ 0 };
	int draw{ 3 };


	if (them == 'A') //rock
	{
		if (me == 'X') // rock
			return draw;
		if (me == 'Y') //paper
			return win;
		if (me == 'Z') //scissors
			return lose;
	}

	if (them == 'B') //paper
	{
		if (me == 'X') // rock
			return lose;
		if (me == 'Y') //paper
			return draw;
		if (me == 'Z') //scissors
			return win;
	}

	if (them == 'C') //scissors
	{
		if (me == 'X') // rock
			return win;
		if (me == 'Y') //paper
			return lose;
		if (me == 'Z') //scissors
			return draw;
	}

	return -1;
}

int two_shape(const char me)
{
	if (me == 'X') // rock
		return 1;
	if (me == 'Y') //paper
		return 2;
	if (me == 'Z') //scissors
		return 3;
	return -1;
}

int two()
{
	int total_score{ 0 };

	std::ifstream file_in("2.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;
	while (std::getline(file_in, line))
	{
		std::istringstream iss(line);
		char them{};
		char me{};

		iss >> them >> me;

		total_score += two_outcome(them, me) + two_shape(me);
	}

	return total_score;
}

char two_convert(const char them, const char me)
{
	if (them == 'A') //rock
	{
		if (me == 'X') // lose
			return 'Z';
		if (me == 'Y') //draw
			return 'X';
		if (me == 'Z') //win
			return 'Y';
	}

	if (them == 'B') //paper
	{
		if (me == 'X') // 
			return 'X';
		if (me == 'Y') //
			return 'Y';
		if (me == 'Z') //
			return 'Z';
	}

	if (them == 'C') //scissors
	{
		if (me == 'X') // 
			return 'Y';
		if (me == 'Y') //
			return 'Z';
		if (me == 'Z') //
			return 'X';
	}

	return 'Q';
}

int two_2()
{
	int total_score{ 0 };

	std::ifstream file_in("2.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;
	while (std::getline(file_in, line))
	{
		std::istringstream iss(line);
		char them{};
		char me{};

		iss >> them >> me;

		total_score += two_outcome(them, two_convert(them, me)) + two_shape(two_convert(them, me));
	}

	return total_score;
}




int three_char_to_priority(const char in)
{
	int val = in + 0;

	if (val < 91)
		return val - 65 + 27;
	if (val < 123)
		return val - 97 + 1;

	return 0;
}

int three_get_duplicate_priority(std::string& input)
{
	/*
	* The string is guaranteed to be even in length
	* sort the first half and the second half independently
	* then find the common character between the two halves.
	*/
	auto it{ input.begin() };
	std::advance(it, input.size() / 2);
	std::sort(input.begin(), it);
	std::sort(it, input.end());

	auto first1{ input.begin() };
	auto first2{ it };

	while (first1 != it && first2 != input.end())
	{
		if (*first1 < *first2)
			++first1;
		else
		{
			if (!(*first2 < *first1))
				return three_char_to_priority(*first1++); // *first1 and *first2 are equivalent.
			++first2;
		}
	}

	return 0;
}


int three()
{
	int total_priority{ 0 };

	std::ifstream file_in("3.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;
	while (std::getline(file_in, line))
	{
		std::istringstream iss(line);
		std::string rucksack{};

		iss >> rucksack;

		total_priority += three_get_duplicate_priority(rucksack);
	}

	return total_priority;

}


int three_find_duplicate(const std::string& in1, const std::string& in2, const std::string& in3)
{
	/*
	* The string is guaranteed to be even in length
	* sort the first half and the second half independently
	* then find the common character between the two halves.
	*/
	std::string dup{};
	for (size_t i{ 0 }; i < in1.length(); ++i)
	{
		char c1 = in1[i];
		for (size_t j{ 0 }; j < in2.length(); ++j)
		{
			char c2 = in2[j];
			if (c1 == c2)
			{
				dup += c2;
			}
		}
	}

	for (size_t i{ 0 }; i < dup.length(); ++i)
	{
		char c1 = dup[i];
		for (size_t j{ 0 }; j < in3.length(); ++j)
		{
			char c2 = in3[j];
			if (c1 == c2)
			{
				return three_char_to_priority(c2);
			}
		}
	}

	return 0;
}

int three_2()
{
	int total_priority{ 0 };

	std::ifstream file_in("3.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;
	int count{ 0 };
	std::array<std::string, 3> rucksacks;

	while (std::getline(file_in, line))
	{
		std::istringstream iss(line);
		std::string rucksack{};

		iss >> rucksack;
		rucksacks[count++] = rucksack;

		if (count == 3)
		{
			total_priority += three_find_duplicate(rucksacks[0], rucksacks[1], rucksacks[2]);
			count = 0;
		}
	}

	return total_priority;

}


int four()
{
	int total_overlaps{ 0 };

	std::ifstream file_in("4.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;
	int count{ 0 };
	std::array<int, 4> sections;

	while (std::getline(file_in, line))
	{
		size_t prev{ 0 };
		size_t pos{};
		size_t i{ 0 };
		while ((pos = line.find_first_of("-,", prev)) != std::string::npos)
		{
			if (pos > prev)
				sections[i++] = std::stoi(line.substr(prev, pos - prev));
			prev = pos + 1;
		}
		sections[i++] = std::stoi(line.substr(prev, line.length() - prev));

		if ((sections[0] <= sections[2] && sections[1] >= sections[3]) || (sections[0] >= sections[2] && sections[1] <= sections[3]))
		{
			++total_overlaps;
		}
	}

	return total_overlaps;
}

int four_2()
{
	int total_overlaps{ 0 };

	std::ifstream file_in("4.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;
	int count{ 0 };
	std::array<int, 4> sections;

	while (std::getline(file_in, line))
	{
		size_t prev{ 0 };
		size_t pos{};
		size_t i{ 0 };
		while ((pos = line.find_first_of("-,", prev)) != std::string::npos)
		{
			if (pos > prev)
				sections[i++] = std::stoi(line.substr(prev, pos - prev));
			prev = pos + 1;
		}
		sections[i++] = std::stoi(line.substr(prev, line.length() - prev));

		if ((sections[2] <= sections[1] && sections[3] >= sections[0]) || (sections[2] >= sections[1] && sections[3] <= sections[0]))
		{
			++total_overlaps;
		}
	}

	return total_overlaps;
}

char five_get_box(const std::string& line, const size_t stack_num)
{
	return line[4 * stack_num + 1];
}


std::string five()
{
	std::ifstream file_in("5.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return "-1";
	}

	std::string line;


	size_t num_stacks{ 0 };
	std::vector<std::vector<char>> stacks{};
	bool firstLine{ true };
	bool readStacks{ true };
	bool readMoves{ false };
	while (std::getline(file_in, line))
	{
		if (firstLine)
		{
			num_stacks = (line.length() + 1) / 4;
			stacks.resize(num_stacks);
			for (size_t i{ 0 }; i < num_stacks; ++i)
			{
				stacks[i] = {};
			}
			firstLine = false;
		}
		if (line.empty() || line[1] == '1')
			readStacks = false;
		if (line[0] == 'm')
			readMoves = true;

		if (readStacks)
		{
			for (size_t i{ 0 }; i < num_stacks; ++i)
			{
				char addMe = five_get_box(line, i);
				if (addMe != ' ')
				{
					stacks[i].insert(stacks[i].begin(), addMe);
				}

			}
		}

		if (readMoves)
		{
			size_t boxes{ 0 };
			size_t from{ 0 };
			size_t to{ 0 };
			std::string tmp{};

			std::istringstream iss(line);
			iss >> tmp >> boxes >> tmp >> from >> tmp >> to;

			for (size_t i{ 0 }; i < boxes; ++i)
			{
				int move_me = stacks[from - 1][stacks[from - 1].size() - 1];
				stacks[from - 1].pop_back();
				stacks[to - 1].push_back(move_me);
			}

		}
	}

	std::string answer{};
	for (size_t i{ 0 }; i < num_stacks; ++i)
	{
		answer += stacks[i][stacks[i].size() - 1];
	}

	return answer;
}


std::string five_2()
{
	std::ifstream file_in("5.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return "-1";
	}

	std::string line;


	size_t num_stacks{ 0 };
	std::vector<std::vector<char>> stacks{};
	bool firstLine{ true };
	bool readStacks{ true };
	bool readMoves{ false };
	while (std::getline(file_in, line))
	{
		if (firstLine)
		{
			num_stacks = (line.length() + 1) / 4;
			stacks.resize(num_stacks);
			for (size_t i{ 0 }; i < num_stacks; ++i)
			{
				stacks[i] = {};
			}
			firstLine = false;
		}
		if (line.empty() || line[1] == '1')
			readStacks = false;
		if (line[0] == 'm')
			readMoves = true;

		if (readStacks)
		{
			for (size_t i{ 0 }; i < num_stacks; ++i)
			{
				char addMe = five_get_box(line, i);
				if (addMe != ' ')
				{
					stacks[i].insert(stacks[i].begin(), addMe);
				}

			}
		}

		if (readMoves)
		{
			size_t boxes{ 0 };
			size_t from{ 0 };
			size_t to{ 0 };
			std::string tmp{};

			std::istringstream iss(line);
			iss >> tmp >> boxes >> tmp >> from >> tmp >> to;

			for (size_t i{ 0 }; i < boxes; ++i)
			{
				int move_me = stacks[from - 1][stacks[from - 1].size() - boxes + i];
				stacks[to - 1].push_back(move_me);
			}
			for (size_t i{ 0 }; i < boxes; ++i)
			{
				stacks[from - 1].pop_back();
			}

		}
	}

	std::string answer{};
	for (size_t i{ 0 }; i < num_stacks; ++i)
	{
		answer += stacks[i][stacks[i].size() - 1];
	}

	return answer;
}



template<class Container>
bool six_are_all_unique(Container input)
{
	for (size_t i{ 0 }; i < input.size(); ++i)
	{
		for (size_t j{ i + 1 }; j < input.size(); ++j)
		{
			if (input[i] == input[j])
				return false;
		}
	}
	return true;
}


int six()
{
	std::ifstream file_in("6.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;

	const int MAGIC_NUM{ 4 };
	std::array<char, MAGIC_NUM> chars;
	size_t ic{ 0 };
	char ch;
	int char_num{ 1 };
	while (file_in.get(ch))
	{
		chars[ic++] = ch;

		if (char_num >= MAGIC_NUM && six_are_all_unique(chars))
		{
			return char_num;
		}


		if (ic == MAGIC_NUM)
			ic = 0;
		++char_num;
	}


	return 0;
}

int six_2()
{
	std::ifstream file_in("6.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;

	const int MAGIC_NUM{ 14 };
	std::array<char, MAGIC_NUM> chars;
	size_t ic{ 0 };
	char ch;
	int char_num{ 1 };
	while (file_in.get(ch))
	{
		chars[ic++] = ch;

		if (char_num >= MAGIC_NUM && six_are_all_unique(chars))
		{
			return char_num;
		}


		if (ic == MAGIC_NUM)
			ic = 0;
		++char_num;
	}


	return 0;
}




struct Node
{
	Node* parent{ nullptr };
	int size{ 0 }; //represents the file size or the total size of the directory and all subdirs/files.
	bool isDir{ true };
	std::string name{};
	std::list<Node> children; //std::list maintains pointer validity - no resize. std::vector invalidates pointers to elements upon reallocation.

	Node* Parent()
	{
		if (parent == nullptr)
		{
			return this; // can't ever get a nullptr returned. If we go to the parent of the root, we get the root.
		}
		return parent;
	}

	int calculate_total_size() //of everything contained within this node
	{
		if (size > 0)
			return size;
		//otherwise
		for (Node& c : children)
		{
			size += c.calculate_total_size(); //this updates the size of directories
		}
		return size;
	}

	int get_total_sizes_LT_100k()
	{
		int size = 0;
		if (isDir && this->size < 100000)
			size += this->size;

		for (Node& c : children)
		{
			size += c.get_total_sizes_LT_100k();
		}
		return size;
	}

	void get_all_directory_sizes(std::vector<int>& sizes)
	{
		if (isDir)
		{
			sizes.push_back(this->size);
		}
		for (Node& c : children)
		{
			c.get_all_directory_sizes(sizes);
		}
	}


};



int seven()
{
	std::ifstream file_in("7.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}


	// Create the tree root
	Node tree{ nullptr, 0, true, "/" };
	// Pointer to our current directory
	Node* currentDir = &tree;

	bool commandMode = true;

	while (file_in)
	{
		//if we're in the mode where we're issuing commands to the computer
		if (commandMode)
		{
			char dollar;
			std::string command;
			std::string arg;
			file_in >> dollar >> command; //dollar is just there to consume a token. We don't need to do anything with it.

			if (command == "cd")
			{
				file_in >> arg;
				if (arg == "/")
				{//going to root
					currentDir = &tree;
				}
				else if (arg == "..")
				{//going up a level
					currentDir = currentDir->Parent();
				}
				else
				{ // going into a directory
					for (Node& n : currentDir->children)
					{
						if (n.name == arg)
						{
							currentDir = &n;
							break;
						}
					}
				}


			}
			else if (command == "ls")
			{
				commandMode = false;
			}
		}
		else //otherwise, we're listing files.
		{
			std::string command;
			file_in >> command;
			if (!file_in) break;

			//if this is true, then we've stopped listing files and have issued a command
			if (command == "$")
			{
				file_in.seekg(-2, std::ios::cur); //from the current position, go back 2; ie, the ' ' and the '$'
				commandMode = true; // we're now issuing commands
			}
			else if (command == "dir") //we need to add a directory to the children list
			{
				std::string name;
				file_in >> name;
				currentDir->children.push_back({ currentDir, 0, true, name });
			}
			else //it starts with a number, and is therefore, a file.
			{
				int size{ std::stoi(command) };
				std::string name;
				file_in >> name;
				currentDir->children.push_back({ currentDir, size, false, name });
			}
		}
	}//end of file

	tree.calculate_total_size();

	int part_1 = tree.get_total_sizes_LT_100k();


	std::vector<int> sizes;
	tree.get_all_directory_sizes(sizes);
	std::sort(sizes.begin(), sizes.end());

	// Calculate how much space needs to be freed
	auto unused = 70000000 - tree.size;
	auto needed = 30000000 - unused;



	for (int size : sizes)
	{
		if (size >= needed)
		{
			return size;
		}
	}

	return 0;


}



bool isVisible(const std::vector<std::vector<int>>& forest, int m, int n)
{
	int val = forest[m][n];

	bool up{ true };
	bool down{ true };
	bool left{ true };
	bool right{ true };

	for (int i{ m - 1 }; i >= 0; --i)
	{
		if (val <= forest[i][n])
		{
			up = false;
			break;
		}
	}
	for (int i{ m + 1 }; i < forest.size(); ++i)
	{
		if (val <= forest[i][n])
		{
			down = false;
			break;
		}
	}
	for (int i{ n - 1 }; i >= 0; --i)
	{
		if (val <= forest[m][i])
		{
			left = false;
			break;
		}
	}
	for (int i{ n + 1 }; i < forest[m].size(); ++i)
	{
		if (val <= forest[m][i])
		{
			right = false;
			break;
		}
	}
	return  up || down || left || right;
}


int eight()
{
	std::ifstream file_in("8.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;


	std::vector<std::vector<int>> forest{};
	size_t row{ 0 };
	while (std::getline(file_in, line))
	{
		forest.emplace_back();
		for (size_t i{ 0 }; i < line.size(); ++i)
		{
			forest[row].push_back(line[i] - '0');
		}
		++row;
	}

	size_t visible{ 2 * forest.size() + 2 * forest[0].size() - 4 };

	for (size_t i{ 1 }; i < forest.size() - 1; ++i)
	{
		for (size_t j{ 1 }; j < forest[i].size() - 1; ++j)
		{
			if (isVisible(forest, i, j))
			{
				++visible;
			}
		}
	}



	return visible;
}



int scenicScore(const std::vector<std::vector<int>>& forest, int m, int n)
{
	int val = forest[m][n];

	int up{ 0 };
	int down{ 0 };
	int left{ 0 };
	int right{ 0 };

	for (int i{ m - 1 }; i >= 0; --i)
	{
		++up;
		if (val <= forest[i][n])
		{
			break;
		}
	}
	for (int i{ m + 1 }; i < forest.size(); ++i)
	{
		++down;
		if (val <= forest[i][n])
		{
			break;
		}
	}
	for (int i{ n - 1 }; i >= 0; --i)
	{
		++left;
		if (val <= forest[m][i])
		{
			break;
		}
	}
	for (int i{ n + 1 }; i < forest[m].size(); ++i)
	{
		++right;
		if (val <= forest[m][i])
		{
			break;
		}
	}

	return up * down * left * right;
}



int eight_2()
{
	std::ifstream file_in("8.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string line;


	std::vector<std::vector<int>> forest{};
	size_t row{ 0 };
	while (std::getline(file_in, line))
	{
		forest.emplace_back();
		for (size_t i{ 0 }; i < line.size(); ++i)
		{
			forest[row].push_back(line[i] - '0');
		}
		++row;
	}

	int maxScore{ 0 };
	int tmp;
	for (size_t i{ 1 }; i < forest.size() - 1; ++i)
	{
		for (size_t j{ 1 }; j < forest[i].size() - 1; ++j)
		{
			if ((tmp = scenicScore(forest, i, j)) > maxScore)
			{
				maxScore = tmp;
			}
		}
	}

	return maxScore;
}
#endif

int sign(int val)
{
	if (val > 0) return 1;
	if (val == 0) return 0;
	return -1;
}


struct Point
{
	int x{ 12 };
	int y{ 6 };

	void up()
	{
		++y;
	}

	void down()
	{
		--y;
	}

	void left()
	{
		--x;
	}

	void right()
	{
		++x;
	}

	void move(const char direction)
	{
		if (direction == 'R')
		{
			right();
		}
		else if (direction == 'L')
		{
			left();
		}
		else if (direction == 'U')
		{
			up();
		}
		else if (direction == 'D')
		{
			down();
		}
	}

	[[nodiscard]] bool isCloseTo(const Point other) const
	{
		return (std::abs(this->x - other.x) <= 1 && std::abs(this->y - other.y) <= 1);
	}

	void makeCloseTo(const Point other)
	{
		if (isCloseTo(other))
			return;

		if (this->x == other.x && this->y != other.y)
		{
			int y_diff{ this->y - other.y };
			this->y = other.y + sign(y_diff);
		}
		else if (this->x != other.x && this->y == other.y)
		{
			int x_diff{ this->x - other.x };
			this->x = other.x + sign(x_diff);
		}
		else //different in both dimension
		{
			//the point moves diagonally to catch up
			int x_diff{ sign(other.x - this->x) };
			int y_diff{ sign(other.y - this->y) };

			this->x += x_diff;
			this->y += y_diff;
		}
	}
};


std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << '(' << p.x << ',' << p.y << ')';
	return os;
}

bool operator==(const Point& left, const Point& other)
{
	return (left.x == other.x) && (left.y == other.y);
}


struct Point_Hash
{
	inline size_t operator() (const Point& point) const
	{
		return point.x ^ point.y;
	}
};

void drawPoints(Point head, Point tail, int i = 6, int j = 5)
{
	std::cout << "\n";
	for (int jj = j; jj >= 1; --jj)
	{
		for (int ii = 1; ii <= i; ++ii)
		{
			Point tmp{ ii, jj };
			if (tmp == head)
				std::cout << 'H';
			else if (tmp == tail)
				std::cout << 'T';
			else
			{
				if (ii == 1 && jj == 1)
					std::cout << 's';
				else
					std::cout << '.';
			}
		}
		std::cout << '\n';
	}
	std::cout << "\n";
}

template<typename Container>
void drawPoints(Container knots, int i = 26, int j = 21)
{
	std::cout << "\n";
	for (int jj = j; jj >= 1; --jj)
	{
		for (int ii = 1; ii <= i; ++ii)
		{
			bool matched{ false };
			Point tmp{ ii, jj };
			for (int k{ 0 }; k < knots.size(); ++k)
			{
				if (tmp == knots[k])
				{
					matched = true;
					if (k == 0)
						std::cout << 'H';
					else
						std::cout << k;
					break;
				}
			}
			if (!matched)
			{
				if (ii == 12 && jj == 6)
					std::cout << 's';
				else
					std::cout << '.';
			}
		}
		std::cout << '\n';
	}
	std::cout << "\n";
}


int nine()
{
	std::ifstream file_in("9.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	char direction;
	int distance;

	Point head{};
	Point tail{};

	std::unordered_set<Point, Point_Hash> tails{ tail };
	while (file_in)
	{
		file_in >> direction >> distance;

		if (!file_in) break;
		for (int i{ 0 }; i < distance; ++i)
		{
			head.move(direction);
			tail.makeCloseTo(head);
			tails.emplace(tail);
		}
	}//end of file


	return tails.size();
}


int nine_2()
{
	std::ifstream file_in("9.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	char direction;
	int distance;

	const int KNOTS{ 10 };
	std::array<Point, KNOTS> knots{};

	std::unordered_set<Point, Point_Hash> tails{ knots[KNOTS - 1] };
	//drawPoints(knots);
	while (file_in)
	{
		file_in >> direction >> distance;
		//std::cout << direction << distance << '\n';
		if (!file_in) break;
		for (int i{ 0 }; i < distance; ++i)
		{
			knots[0].move(direction);

			for (int k = 1; k < KNOTS; ++k)
			{
				knots[k].makeCloseTo(knots[k - 1]);
			}
			tails.emplace(knots[KNOTS - 1]);
		}
		//drawPoints(knots);
	}//end of file


	return tails.size();
}



int ten()
{
	std::ifstream file_in("10_test.txt");
	if (!file_in)
	{
		std::cout << "Couldn't open file.\n";
		return -1;
	}

	std::string operation{};
	int value{ 0 };
	int cycle{ 0 };
	int tot_value{ 1 };

	while (file_in)
	{
		++cycle;
		file_in >> operation;
		if (operation == "addx"){
			file_in >> value;

			if(cycle == 20 || (cycle-20)/40 == 0){
				std::cout << cycle << " : " << tot_value << '\n';
			}

			tot_value += value;
			++cycle;
		}
		// do things for the noop

		


		
	}//end of file


	return tot_value;
}



int main()
{
	//std::cout << " 1 : " << one() << '\n';
	//std::cout << " 1x: " << one_2() << '\n';
	//
	//std::cout << " 2 : " << two() << '\n';
	//std::cout << " 2x: " << two_2() << '\n';
	//
	//std::cout << " 3 : " << three() << '\n';
	//std::cout << " 3x: " << three_2() << '\n';

	//std::cout << " 4 : " << four() << '\n';
	//std::cout << " 4x: " << four_2() << '\n';

	//std::cout << " 5 : " << five() << '\n';
	//std::cout << " 5x: " << five_2() << '\n';

	//std::cout << " 6 : " << six() << '\n';
	//std::cout << " 6x: " << six_2() << '\n';

	//std::cout << " 7 : " << seven() << '\n';

	//std::cout << " 8 : " << eight() << '\n';
	//std::cout << " 8x: " << eight_2() << '\n';

	//std::cout << " 9 : " << nine() << '\n';
	//std::cout << " 9 : " << nine_2() << '\n';

	std::cout << "10 : " << ten() << '\n';

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
