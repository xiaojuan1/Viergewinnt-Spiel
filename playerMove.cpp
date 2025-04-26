#include"VierGewinnt.h"
#include <thread>   // 引入线程库
#include <chrono>   // 引入时间库，用于指定等待时间
// Nehme eine Eingabe über die Konsole des Spielers an, in welche Spalte der Zug
// gemacht werden soll.
// Bei unklaren Eingaben soll er zu einer erneuten Eingabe aufgefordert werden.
// Die Programmlogik darf durch falsche Eingaben nicht gestört werden,
// insbesondere darf euer Programm nicht dadurch abstürzen.
// Prüfe, ob der Zug valide ist und führe danach ein Update des Spielfeldes aus.
// Zeige danach das Spielfeld und ggf. das Spielergebnis.
// 接受来自玩家控制台的输入，以确定应该在哪一列进行移动。
// 如果输入不清楚，应该提示用户重新输入。
// 程序逻辑不能因错误输入而被破坏，特别是不能因此导致程序崩溃。
// 检查移动是否有效，然后更新棋盘。
// 然后显示比赛场地，如果适用，还显示比赛结果。
void VierGewinnt::playerMoveLogic() {
    int column;  // 玩家输入的列号
    bool validMove = false;

    // 循环直到玩家输入有效的列号
    while (!validMove) {
        cout << "Player, please enter the column (1-7): ";
        cin >> column;

        // 检查输入是否有效
        if (cin.fail() || column < 1 || column > 7) {
            cin.clear();  // 清除错误标记
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 丢弃无效输入
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }

        // 检查列是否可用
        if (!checkIfValidMove(column)) {
            cout << "Column " << column << " is full. Please choose another column.\n";
        }
        else {
            validMove = true;  // 输入有效
        }
    }
    // 棋子落下逻辑
    int row = 0;  // 用来存储落子所在行
    int col = 0;  // 用来存储落子所在列
    updateGameField(column, "X", row, col);  // 玩家符号为 "X"
    // 调用棋子落下的逻辑，将玩家的棋子放到指定的列中

    showGame();  // 显示更新后的棋盘


    // 判断游戏是否结束
    if (checkIfGameOver(row,column,"X")) {
        cout << "Player wins! Game over.\n";
        std::this_thread::sleep_for(std::chrono::seconds(5)); // 等待 5 秒
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

    



void VierGewinnt::playerMove()
{
	cout << "Player's turn:\n";
	playerMoveLogic();  // 调用玩家逻辑函数
}
