#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>

const int BOARD_SIZE = 9;
const int EMPTY_CELL = 0;

class SudokuBoard {
    private:
    std::vector<std::vector<int>> currentBoard;
    std::vector<std::vector<int>> initialBoard;
    
    public:
        /**
        * @brief Constructor for SudokuBoard.
        * Initializes an empty Sudoku board or a board from a given puzzle.
        */
        SudokuBoard();

        /**
        * @brief Overloaded constructor to initialize the board with a given 2D vector.
        * @param initialBoard A 2D vector representing the initial state of the Sudoku puzzle.
        * '0' should represent empty cells.
        */
        
        SudokuBoard(const std::vector<std::vector<int>>& initialBoard) {
            this->initialBoard = initialBoard;
            this->currentBoard = initialBoard;
        }

        /** 
        * @brief Helper function for displayBoard() for the loop that prints
        * each of the board's rows
        * @param row An int representing the row to be printed
        */
        void printRow(int row) const
        {
            if (row == 0) {
                std::cout << "     1   2   3   4   5   6   7   8   9  \n";
                std::cout << "   ┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓\n";
            }
            
            std::cout << " " << row + 1 << " ┃ ";
            for (int col = 0; col < BOARD_SIZE; ++col) {
                int num = this->getCell(row, col);
                if (num == EMPTY_CELL) {
                    ((col + 1) % 3) ? std::cout << " " << " │ " : std::cout << " " << " ┃ ";
                } else {
                    ((col + 1) % 3) ? std::cout << num << " │ " : std::cout << num << " ┃ ";
                }
            }
            std::cout << '\n';

            if (row == BOARD_SIZE - 1) {
                std::cout << "   ┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛\n";
            } else if ((row + 1) % 3) {
                std::cout << "   ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨\n";
            } else {
                std::cout << "   ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫\n";
            }
        }

        void displayTitleInstructions() const
        {
            std::cout << "  _____ _____ ____  _____ _____ _____ \n";
            std::cout << " |   __|  |  |    \\|     |  |  |  |  |\n";
            std::cout << " |__   |  |  |  |  |  |  |    -|  |  |\n";
            std::cout << " |_____|_____|____/|_____|__|__|_____|\n";

            std::cout << "\nWelcome to Sudoku!\n";
            std::cout << "Enter numbers 1-9 in the missing tiles so that each row,\n";
            std::cout << "column, and 3x3 grid (bolded below) have a unique number.\n";
            std::cout << "Good luck!\n";
        }

        /**
        * @brief Displays the current state of the Sudoku board to the console.
        * Should format the board clearly with separators for 3x3 blocks.
        */
        void displayBoard() const
        {
            system("clear");
            displayTitleInstructions();
            std::cout << "\nCurrent Board:\n" << '\n';
            for (int row = 0; row < BOARD_SIZE; ++row) {
                printRow(row);
            }
        }

        /**
        * @brief Sets the value of a specific cell on the board.
        * This function should not perform validation beyond bounds checking.
        * @param row The row index (0-8).
        * @param col The column index (0-8).
        * @param value The value to set (1-9 or 0 for empty).
        * @return True if the cell was set successfully, false if out of bounds.
        */
        bool setCell(int row, int col, int value) 
        {
            if (value < 1 || value > 9) return false;

            try {
                this->currentBoard.at(row).at(col) = value;
            } catch (const std::out_of_range& e) {
                return false;
            }
            return true;
        }

        /**
        * @brief Gets the value of a specific cell on the board.
        * @param row The row index (0-8).
        * @param col The column index (0-8).
        * @return The value of the cell, or -1 if out of bounds.
        */
        int getCell(int row, int col) const
        {
            try {
                return this->currentBoard.at(row).at(col);
            } catch (const std::out_of_range& e) {
                return -1;
            }
        }

        /**
        * @brief Checks if a given cell is part of the initial puzzle (i.e., not an empty cell
        * that the user is allowed to change).
        * This requires storing the initial state separately or marking cells.
        * @param row The row index (0-8).
        * @param col The column index (0-8).
        * @return True if the cell was part of the initial puzzle, false otherwise.
        */
        bool isInitialCell(int row, int col) const
        {
            return this->currentBoard[row][col] == this->initialBoard[row][col];
        }

        /**
        * @brief Resets the board to its initial puzzle state.
        * All user-entered values should be cleared.
        */
        void resetBoard()
        {
            this->currentBoard = this->initialBoard;
        }
};

#endif // SUDOKU_BOARD_H