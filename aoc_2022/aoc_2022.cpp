// aoc_2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

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









int main()
{
	std::cout << " 1: " << one() << '\n';


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
