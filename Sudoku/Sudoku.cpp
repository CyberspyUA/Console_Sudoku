// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <cstdlib>

using matrix = std::vector <std::vector<int>>;
using namespace std::chrono_literals;

bool isSafe(const matrix& sudoku_field, const int& rowind, const int& columnind, const int& num, const int& width, const int& height);
matrix AllocateSudokuField(const int& width, const int& height);
void RevealRandomValue(matrix& sudoku_field, const int& width, const int& height, int&& reveal_numbers_count);

matrix AllocateSudokuField(const int& width,const int& height)
{
    matrix sudoku_field(width, std::vector<int>(height));
    RevealRandomValue(sudoku_field, width, height, rand() % 10 + 30);
    return sudoku_field;
}
void RevealRandomValue(matrix& sudoku_field, const int& width, const int& height, int&& reveal_numbers_count)
{
    
    while(reveal_numbers_count != 0)
    {
        auto random_row_ind = rand() % 8;
        auto random_column_ind = rand() % 8;
        auto random_number = rand() % 8 + 1;
	    if(isSafe(sudoku_field, random_row_ind, random_column_ind, random_number, width, height))
	    {
                sudoku_field.at(random_row_ind).at(random_column_ind) = random_number;
                reveal_numbers_count--;
	    }
    }

}
bool isSafe(const matrix& sudoku_field,const int& rowind, const int& columnind, const int& num, const int& width, const int& height) {
    // Check if 'num' is already in the same row
    for (int i = 0; i < width; i++)
        if (sudoku_field.at(rowind).at(i) == num)
            return false;

    // Check if 'num' is already in the same column
    for (int i = 0; i < height; i++)
        if (sudoku_field.at(i).at(columnind) == num)
            return false;

    // Check if 'num' is already in the same 3x3 box
    const int box_row_start = rowind - rowind % 3;
    const int box_col_start = columnind - columnind % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (sudoku_field[i + box_row_start][j + box_col_start] == num)
                return false;

    return true;
}
bool IsGameFinished(const matrix& sudoku_field)
{
    for (unsigned int rowind = 0; rowind < 9; rowind++)
        for (unsigned int columnind = 0; columnind < 9; columnind++)
            if (sudoku_field.at(rowind).at(columnind) == 0)
                return false;
    return true;
}
int main()
{
    auto sudoku_field = AllocateSudokuField(9, 9);
    auto rand_reveal_num = rand() % 10 + 25;
    bool game_finished = false;
	while (!game_finished)
	{
		std::cout << "\tSudoku Field:" << std::endl;
		for (int rowind = 0; rowind < 9; rowind++)
		{
			for (int columnind = 0; columnind < 9; columnind++)
			{
				std::cout << sudoku_field.at(rowind).at(columnind) << " ";
				if (columnind == 8)
					std::cout << std::endl;
			}
		}
		unsigned int input_row_ind = 0;
		unsigned int input_column_ind = 0;
		unsigned int choice = 0;
		std::cout << "Options:\n (1)Input value;\n (2)Quit game.\n";
		std::cout << "Input choice: " << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			std::cout << "Input row index from 1 to 9: ";
			std::cin >> input_row_ind;
			std::cout << std::endl;
			std::cout << "Input column index from 1 to 9: ";
			std::cin >> input_column_ind;
			std::cout << std::endl;
			if (input_row_ind == 0 || input_row_ind > 9)
			{
				std::cout << "Input row index is not valid. Try again!" << std::endl;
			}
			else if (input_column_ind == 0 || input_column_ind > 9)
			{
				std::cout << "Input column index is not valid. Try again!" << std::endl;
			}
			else
			{
				if (IsGameFinished(sudoku_field))
				{
					game_finished = IsGameFinished(sudoku_field);
				}
				else
				{
					unsigned int input_value = 0;
					std::cout << "What number you want to input? (from 1 to 9)" << std::endl;
					std::cin >> input_value;
					if (input_value == 0 || input_value > 9)
					{
						std::cout << "Input value is not valid. Try again." << std::endl;
					}
					else
					{
						if (isSafe(sudoku_field, input_row_ind - 1, input_column_ind - 1, input_value, 9, 9))
							sudoku_field.at(input_row_ind - 1).at(input_column_ind - 1) = input_value;
						else
							std::cout << "Value is already input. Value:" << sudoku_field.at(input_row_ind - 1).at(input_column_ind - 1) << std::endl;
					}
				}
			}
			std::this_thread::sleep_for(2000ms);
			system("cls");
			break;
		}
		case 2:
		{
			game_finished = true;
			break;
		}
		default:
		{
			std::cout << "Invalid input. Try again." << std::endl;
			system("cls");
			break;
		}
		}
		
	}
	return 0;
}

