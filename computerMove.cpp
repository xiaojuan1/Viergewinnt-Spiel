#include"VierGewinnt.h"
#include <iostream>
#include <thread>
#include <chrono>



void VierGewinnt::computerMove() {
    int column = -1;
    cout << "Computer's turn...\n";

    // **1. 检查电脑是否可以获胜**
    for (int j = 1; j <= 7; ++j) {
        int row = -1;
        if (simulateMove(j, "O", row)) {
            if (checkIfGameOver(row, j, "O")) {
                column = j;
                undoMove(row, j);
                break;
            }
            undoMove(row, j);
        }
    }

    // **2. 检查玩家是否可以获胜并阻止**
    if (column == -1) {
        for (int j = 1; j <= 7; ++j) {
            int row = -1;
            if (simulateMove(j, "X", row)) {
                if (checkIfGameOver(row, j, "X")) {
                    column = j;
                    undoMove(row, j);
                    break;
                }
                undoMove(row, j);
            }
        }
    }

    // **3. 检测玩家可能形成多个获胜点**
    if (column == -1) {
        std::vector<int> threatColumns;
        for (int firstMove = 1; firstMove <= 7; ++firstMove) {
            if (!checkIfValidMove(firstMove)) continue;

            int row = -1;
            simulateMove(firstMove, "X", row);

            int winningPositions = 0;
            for (int j = 1; j <= 7; ++j) {
                int secondRow = -1;
                if (simulateMove(j, "X", secondRow)) {
                    if (checkIfGameOver(secondRow, j, "X")) {
                        winningPositions++;
                    }
                    undoMove(secondRow, j);
                }
            }

            undoMove(row, firstMove);
            if (winningPositions >= 2) {
                threatColumns.push_back(firstMove);
            }
        }

        if (!threatColumns.empty()) {
            column = threatColumns[0];  // 或选择最优列
        }
    }

    
    // **4. 选择对电脑最有利的列**
    if (column == -1) {
        int maxScore = -10000;  // 初始化为较低的分数
        for (int j = 1; j <= 7; ++j) {
            if (!checkIfValidMove(j)) {
                continue;
            }

            int row = -1;
            simulateMove(j, "O", row);

            // 检查如果电脑下这步棋，玩家是否会获胜
            bool playerWins = false;
            for (int k = 1; k <= 7; ++k) {
                int playerRow = -1;
                if (simulateMove(k, "X", playerRow)) {
                    if (checkIfGameOver(playerRow, k, "X")) {
                        playerWins = true;
                    }
                    undoMove(playerRow, k);
                }
            }

            int score = playerWins ? -10000 : evaluatePosition(j, row, "O");  // 如果玩家会获胜，则赋最低分
            undoMove(row, j);

            if (score > maxScore) {
                maxScore = score;
                column = j;
            }
        }
    }

    // **5. 执行落子**
    int row = 0;
    updateGameField(column, "O", row, column);
    showGame();

    // **6. 检查电脑是否获胜**
    if (checkIfGameOver(row, column, "O")) {
        cout << "Computer wins! Game over.\n";
        resetGame();
    }
    if (isBoardFull()) {
        std::cout << "The board is full. It's a draw." << std::endl;

        // 等待 5 秒钟
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::cout << "Resetting the board in 3 seconds..." << std::endl;

        // 等待 3 秒钟
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // 重置棋盘
        resetGame();
    }
}





