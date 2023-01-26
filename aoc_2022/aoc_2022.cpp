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




int main()
{
	//std::cout << " 1 : " << one() << '\n';
	//std::cout << " 1x: " << one_2() << '\n';
	//
	//std::cout << " 2 : " << two() << '\n';
	//std::cout << " 2x: " << two_2() << '\n';
	//
	std::cout << " 3 : " << three() << '\n';
	std::cout << " 3x: " << three_2() << '\n';

	

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
