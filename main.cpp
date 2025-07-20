#include <iostream>
#include <unistd.h>
#include "include/SudokuBoard.hpp"
#include "include/GameLogic.hpp"

void test()
{
    // Test board printing
    const std::vector<std::vector<int>> completedBoard = {
        {6, 3, 9, 5, 7, 4, 1, 8, 2},
        {5, 4, 1, 8, 2, 9, 3, 6, 7}, 
        {2, 8, 7, 1, 3, 6, 4, 9, 5},
        {9, 5, 8, 7, 6, 1, 2, 3, 4},
        {3, 1, 4, 2, 9, 8, 7, 5, 6},
        {7, 6, 2, 4, 5, 3, 9, 1, 8},
        {1, 9, 6, 3, 4, 2, 8, 7, 5},
        {4, 2, 5, 9, 8, 7, 6, 3, 1},
        {8, 7, 3, 6, 1, 5, 2, 4, 9}
    };

    const std::vector<std::vector<int>> testOnePieceMissing = {
        {6, 3, 9, 5, 7, 4, 1, 8, 2},
        {0, 4, 1, 8, 2, 9, 3, 6, 7}, 
        {2, 8, 7, 1, 3, 6, 4, 9, 5},
        {9, 5, 8, 7, 6, 1, 2, 3, 4},
        {3, 1, 4, 2, 9, 8, 7, 5, 6},
        {7, 6, 2, 4, 5, 3, 9, 1, 8},
        {1, 9, 6, 3, 4, 2, 8, 7, 5},
        {4, 2, 5, 9, 8, 7, 6, 3, 1},
        {8, 7, 3, 6, 1, 5, 2, 4, 9}
    };

    SudokuBoard* board = new SudokuBoard(testOnePieceMissing);

    board->displayBoard();
    
    std::cout << board->getCell(8, 8) << '\n';
    if (board->setCell(1, 0, 5)) {
        std::cout << "Value 5 placed at (2,1)\n";
    }

    board->displayBoard();

    (board->isInitialCell(0, 0)) ? std::cout << "(0,0) intial\n" : std::cout << "(0,0) user";
    (board->isInitialCell(1, 0)) ? std::cout << "(1,0) intial\n" : std::cout << "(1,0) user";

    board->resetBoard();
    board->displayBoard();

}

int main()
{
    // test();

    std::vector<std::vector<int>> testOnePieceMissing = {
        {6, 3, 9, 5, 7, 4, 1, 8, 2},
        {0, 4, 1, 8, 2, 9, 3, 6, 7}, 
        {2, 8, 7, 1, 3, 6, 4, 9, 5},
        {9, 5, 8, 7, 6, 1, 2, 3, 4},
        {3, 1, 4, 2, 9, 8, 7, 5, 6},
        {7, 6, 2, 4, 5, 3, 9, 1, 8},
        {1, 9, 6, 3, 4, 2, 8, 7, 5},
        {4, 2, 5, 9, 8, 7, 6, 3, 1},
        {8, 7, 3, 6, 1, 5, 2, 4, 9}
    };

    SudokuBoard* board = new SudokuBoard(GameLogic::getPredefinedPuzzle());
    GameLogic* game = new GameLogic(*board);

    do {
        game->board.displayBoard();
        int inputValue;
        std::cout << "Choose value to insert: ";
        std::cin >> inputValue;
        
        if (! game->isValueValid(inputValue)) {
            std::cout << "Please enter a value between 1-9." << '\n';
            sleep(2);
            continue;
        }
        
        // NOTE: user sees 1-based index, code uses 0-based index
        int inputRow, inputCol;

        std::cout << "Enter the row number: ";
        std::cin >> inputRow;
        std::cout << "Enter the column number: ";
        std::cin >> inputCol;
        inputRow--;
        inputCol--;

        if (! game->isValidMove(inputRow, inputCol, inputValue)) {
            std::cout << "Not a valid move, please try again!";
            continue;
        }
        game->board.setCell(inputRow, inputCol, inputValue);
        game->board.displayBoard();

        if (game->isSolved()) {
            std::cout << "Congratulations, the board is complete!\n";
            std::cout << "Thank you for playing.\n";
            break;
        }
    } while (! game->isSolved());

    return 0;
}