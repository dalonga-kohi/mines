#include "game.h"

int main() 
{
	int rows, cols, bombs;
	int mode;
	std::cout << "------MINESWEEPER CREATOR------\n";
	std::cout << "1) Easy mode\n";
	std::cout << "2) Normal mode\n";
	std::cout << "3) Hard mode\n";
	std::cout << "4) Custom mode\n";
	std::cout << ":";
	std::cin >> mode;

	switch (mode)
	{
	case 2:
		rows = 18; cols = 20; bombs = 40;
		break;
	case 3:
		rows = 24; cols = 28; bombs = 120;
		break;
	case 4:
		std::cout << "\nEnter number of rows: ";
		std::cin >> rows;
		std::cout << "Enter number of columns: ";
		std::cin >> cols;
		std::cout << "Enter number of bombs: ";
		std::cin >> bombs;
		break;
	default:
		rows = 8; cols = 10; bombs = 10;
		break;
	}

	try
	{
		MinesGame gameController(cols, rows, 16, bombs, "MineSweeper");
		gameController.init();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}