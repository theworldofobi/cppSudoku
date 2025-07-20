#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "SudokuBoard.hpp"
#include <vector>

class GameLogic {
    private:

        bool isRowValid(int row, int value) const 
        {
            return (row >= 1 && row <= BOARD_SIZE) && (value >= 1 && value <= BOARD_SIZE);
        }
        
        bool isColValid(int col, int value) const
        {
            return (col >= 1 && col <= BOARD_SIZE) && (value >= 1 && value <= BOARD_SIZE);
        }
        
        bool isBoxValid(int row, int col, int value) const
        {
            return isRowValid(row, value) && isColValid(col, value);
        }
        
        bool checkAllCellsFilled() const
        {
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (! this->board.getCell(i, j)) return false;
                }
            }
            return true;
        }
    
    public:
        SudokuBoard& board;

        /**
        * @brief Overloaded constructor for GameLogic.
        * Takes a SudokuBoard object to interact with.
        * @param board_ref A reference to the SudokuBoard object.
        */
        GameLogic(SudokuBoard& board_ref) : board(board_ref)
        {
        }

        /** 
        * @brief Completes tasks necessary to undo, or reject, a move by setting
        * the cell equal to EMPTY_CELL
        * @param row The row index (0-8).
        * @param col The column index (0-8).
        */
        bool rejectMove(int row, int col) const {
            this->board.setCell(row, col, EMPTY_CELL);
            return false;
        }

        bool isValueValid(int value) const {
            return (value >= 1 && value <= 9);
        }

        /**
        * @brief Checks if a given value is valid for a specific cell according to Sudoku rules.
        * This checks the row, column, and 3x3 subgrid.
        * @param row The row index (0-8).
        * @param col The column index (0-8).
        * @param value The value to check (1-9).
        * @return True if the value is valid for the cell, false otherwise.
        */
        bool isValidMove(int row, int col, int value) const
        {
            // First check if the value is valid (1-9)
            if (!this->isValueValid(value)) {
                return false;
            }

            // Check if the cell is already filled (assuming 0 means empty)
            if (this->board.getCell(row, col) != EMPTY_CELL) {
                return false;
            }

            // Check row for duplicate values
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (this->board.getCell(row, j) == value) {
                    return false;
                }
            }

            // Check column for duplicate values
            for (int i = 0; i < BOARD_SIZE; ++i) {
                if (this->board.getCell(i, col) == value) {
                    return false;
                }
            }

            // Check 3x3 box for duplicate values
            int boxStartRow = (row / 3) * 3;
            int boxStartCol = (col / 3) * 3;

            for (int i = boxStartRow; i < boxStartRow + 3; ++i) {
                for (int j = boxStartCol; j < boxStartCol + 3; ++j) {
                    if (this->board.getCell(i, j) == value) {
                        return false;
                    }
                }
            }
            
            return true;
        }

        /**
        * @brief Checks if the entire Sudoku board is currently solved.
        * This involves checking every row, column, and 3x3 subgrid for unique numbers 1-9.
        * @return True if the board is solved, false otherwise.
        */
        bool isSolved() const
        {
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (this->board.getCell(i, j) == EMPTY_CELL) {
                        return false;
                    }
                }
            }
            return true;
        }

        /**
        * @brief Generates a new Sudoku puzzle.
        * This is an advanced feature. You can start with a fixed puzzle for simplicity
        * and implement generation later.
        * A basic implementation might involve starting with a solved board and removing
        * cells while ensuring uniqueness of the solution.
        */
        void generateNewPuzzle();

        /**
        * @brief Gets a predefined Sudoku puzzle.
        * This can be used to load a puzzle for testing or as a starting point before
        * implementing a full puzzle generator.
        * @return A 2D vector representing a Sudoku puzzle.
        */
        static std::vector<std::vector<int>> getPredefinedPuzzle()
        {
            std::vector<std::vector<int>> completedBoard = {
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

            // ALL MISSING TEST VALUES ARE 5

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

            std::vector<std::vector<int>> testFivePiecesMissing = {
                {6, 3, 9, 5, 7, 4, 1, 8, 2},
                {0, 4, 1, 8, 2, 9, 3, 6, 7}, 
                {2, 8, 7, 1, 3, 6, 4, 9, 0},
                {9, 0, 8, 7, 6, 1, 2, 3, 4},
                {3, 1, 4, 2, 9, 8, 7, 5, 6},
                {7, 6, 2, 4, 0, 3, 9, 1, 8},
                {1, 9, 6, 3, 4, 2, 8, 7, 5},
                {4, 2, 5, 9, 8, 7, 6, 3, 1},
                {8, 7, 3, 6, 1, 0, 2, 4, 9}
            };
            
            std::vector<std::vector<int>> playingModeBoard = {
                {6, 0, 9, 0, 7, 0, 1, 0, 2},
                {0, 4, 0, 8, 0, 9, 0, 6, 0}, 
                {2, 0, 7, 0, 3, 0, 4, 0, 5},
                {0, 5, 0, 7, 0, 1, 0, 3, 0},
                {3, 0, 4, 0, 9, 0, 7, 0, 6},
                {0, 6, 0, 4, 0, 3, 0, 1, 0},
                {5, 0, 6, 0, 4, 0, 8, 0, 9},
                {0, 2, 0, 9, 0, 7, 0, 3, 0},
                {8, 0, 3, 0, 1, 0, 2, 0, 4}
            };

            return testOnePieceMissing;
            // return testFivePiecesMissing;
            // return playingModeBoard;
        }
};

#endif // GAME_LOGIC_H