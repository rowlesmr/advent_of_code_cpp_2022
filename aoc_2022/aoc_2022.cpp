// aoc_2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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


int main()
{
	//std::cout << " 1 : " << one() << '\n';
	//std::cout << " 1x: " << one_2() << '\n';

	std::cout << " 2 : " << two() << '\n';
	std::cout << " 2x: " << two_2() << '\n';

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
