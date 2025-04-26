#include"VierGewinnt.h"
#include <windows.h>  // Windows 下使用 SetConsoleTextAttribute

VierGewinnt::VierGewinnt()
{

    fillVector();

    showGame();

    //Load game stats?


}

void VierGewinnt::fillVector() {

    this->gameField = {
             {"|", " ","|", " ","|"," ","|"," ","|"," ","|"," ","|"," ","|"},//row0
             {"|", " ","|", " ","|"," ","|"," ","|"," ","|"," ","|"," ","|"},//row1
             {"|", " ","|", " ","|"," ","|"," ","|"," ","|"," ","|"," ","|"},//row2
             {"|", " ","|", " ","|"," ","|"," ","|"," ","|"," ","|"," ","|"},//row3
             {"|", " ","|", " ","|"," ","|"," ","|"," ","|"," ","|"," ","|"},//row4
             {"|", " ","|", " ","|"," ","|"," ","|"," ","|"," ","|"," ","|"},//row5
    };

}

// Drucke das gameField in die Konsole und gebe dem Spieler eine Auswahl von 1 bis 6,
// um die Spalte zu wählen, in die der neue Stein fallen soll
// 将 gameField 打印到控制台并让玩家从 1 到 6 中进行选择，
// 选择新棋子应该落入的列
void VierGewinnt::showGame() {
    system("cls");  // 清屏，确保显示的是最新的棋盘
    // 打印顶部列号
    std::cout << "   1   2   3   4   5   6   7  \n";
    std::cout << "  ============================\n";
    for (const auto& row : gameField) {
        std::cout << "  ";  // 每行开始的缩进
        for (const auto& cell : row) {
            if (cell == "|") {
                std::cout << cell;  // 打印分隔符
            }
            else {
                printCellWithColor(cell);  // 打印带颜色的单元格
            }
        }
        std::cout << "\n";  // 换行显示每一行
    }
    std::cout << "  ============================\n";
    std::cout << "   1   2   3   4   5   6   7  \n";  // 再次打印列号
}




void VierGewinnt::printCellWithColor(const std::string& sym) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (sym == "X") {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);  // 红色
        std::cout << " X ";
    }
    else if (sym == "O") {
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // 蓝色
        std::cout << " O ";
    }
    else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // 默认白色
        std::cout << "   ";
    }

    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


// Funktion soll true sein wenn entweder der Computer oder der Spieler gewonnen hat,
// also vier eigene zusammenhängende Steine hat.
// Ebenso soll das Spiel enden, wenn alle Felder des Spielfeldes mit Steinen belegt sind
// Sollte das Spiel zu ende sein, drucke den Gewinner in die Konsole (oder ein unentschieden)
// 如果计算机或玩家获胜，则函数应为真，
// 所以它有四块自己相连的石​​头。
// 当比赛场地上的所有区域都被石头占据时，游戏也应该结束
// 如果游戏结束，则将获胜者打印到控制台（或平局）
bool VierGewinnt::checkIfGameOver(int row, int column, string sym) {
    

    // 定义方向向量，分别代表水平、垂直、对角线两个方向
    int directions[4][2] = {
        {0, 1},  // 水平 (右)
        {1, 0},  // 垂直 (下)
        {1, 1},  // 对角线 (右下)
        {1, -1}  // 对角线 (右上)
    };

    for (int d = 0; d < 4; ++d) {  // 遍历四个方向
        int count = 1;  // 包括当前点本身
        int dr = directions[d][0];  // 行方向增量
        int dc = directions[d][1];  // 列方向增量

        // 向正方向扩展
        for (int step = 1; step < 4; ++step) {
            int r = row + step * dr;
            int c = 2 * column - 1 + step * dc * 2;  // 列对应棋盘的奇数索引
            if (r < 0 || r >= 6 || c < 1 || c >= 15 || gameField[r][c] != sym)
                break;
            count++;
        }

        // 向反方向扩展
        for (int step = 1; step < 4; ++step) {
            int r = row - step * dr;
            int c = 2*column-1 - step * dc*2 ;  // 列对应棋盘的奇数索引
            if (r < 0 || r >= 6 || c < 1 || c >= 15 || gameField[r][c] != sym)
                break;
            count++;
        }

        // 检查是否形成四连珠
        if (count >= 4) {
            cout << sym << " wins in direction (" << dr << ", " << dc << ")!\n";
            return true;
        }
    }

    // 如果没有胜利，返回 false
    return false;
}



// lasse die Steine zu Boden fallen
// 让棋子掉下来
void VierGewinnt::updateGameField(int column, string sym, int& row, int& col) {
    int colIndex = 2 * column - 1;  // 将列号转换为棋盘的奇数列索引

    // 从底部开始检查，找到第一个空位放置棋子
    for (int i = 5; i >= 0; --i) {
        if (gameField[i][colIndex] == " ") {
            gameField[i][colIndex] = sym;  // 放置棋子
            row = i;  // 更新行号
            col = column;  // 更新列号
            return;  // 退出函数
        }
    }

    // 如果列满，返回无效位置
    row = -1;
    col = -1;
}






// prüfe, dass der Stein noch in der Spalte column in das Spielfeld passt
// 检查棋子仍然适合比赛场地的列

bool VierGewinnt::checkIfValidMove(int column) {
    // 检查列号是否有效（1 到 7）
    if (column < 1 || column > 7) {
        return false;
    }

    // 检查该列的最上面一行是否为空
    int colIndex = 2 * column - 1;  // 将列号转换为奇数列索引
    return gameField[0][colIndex] == " ";
}

// return true, wenn unter dem Stein an der Koordinate (i, j) noch Luft ist
//如果坐标(i, j) 处的石头下方仍有空气，则返回 true
bool VierGewinnt::checkIfCanFall(int i, int j) {
    // 当前单元格必须为空
    if (gameField[i][j] != " ") {
        return false;
    }

    // 如果是底部单元格，可以落下
    if (i == 5) {
        return true;
    }

    // 如果下方单元格被占据，可以落下
    if (gameField[i + 1][j] != " ") {
        return true;
    }

    // 否则不能落下
    return false;
}



// zähle wie lang die Ketten des Steins sym an der Position (i, j) sind
// gibt die Länge der längsten Kette zurück
// 计算棋子 sym 在位置 (i, j) 的链条长度
// 返回最长链的长度
int VierGewinnt::countScore(string sym, int i, int j)
{

    return 0;
}

// setze gameField auf den Start zurück und drucke es auf die Konsole
// 重置 gameField 以开始并将其打印到控制台
void VierGewinnt::resetGame()
{
    fillVector();
    showGame();
}

bool VierGewinnt::simulateMove(int column, std::string sym, int& row) {
    for (int i = 5; i >= 0; --i) {
        if (gameField[i][2 * (column - 1) + 1] == " ") {
            row = i;
            gameField[row][2 * (column - 1) + 1] = sym;
            return true;
        }
    }
    return false;
}

void VierGewinnt::undoMove(int row, int column) {
    gameField[row][2 * (column - 1) + 1] = " ";
}


// 检查棋盘是否已满
bool VierGewinnt::isBoardFull() {
    for (int j = 1; j <= 7; ++j) {
        if (checkIfValidMove(j)) {
            return false;  // 如果还有有效列，说明棋盘未满
        }
    }
    return true;  // 没有有效列，说明棋盘已满
}

// 在棋盘满后处理逻辑

int VierGewinnt::evaluatePosition(int column, int row, std::string sym) {
    int score = 0;

    // 检查水平、垂直和两个对角线方向的连珠情况
    int directions[4][2] = {
        {0, 1},  // 水平
        {1, 0},  // 垂直
        {1, 1},  // 对角线（右下）
        {1, -1}  // 对角线（右上）
    };

    for (int d = 0; d < 4; ++d) {
        int dr = directions[d][0];
        int dc = directions[d][1];

        int count = 1;  // 包括当前棋子

        // 向正方向扩展
        for (int step = 1; step < 4; ++step) {
            int r = row + step * dr;
            int c = 2 * (column - 1) + 1 + step * dc * 2;
            if (r < 0 || r >= 6 || c < 1 || c >= 15 || gameField[r][c] != sym) {
                break;
            }
            count++;
        }

        // 向反方向扩展
        for (int step = 1; step < 4; ++step) {
            int r = row - step * dr;
            int c = 2 * (column - 1) + 1 - step * dc * 2;
            if (r < 0 || r >= 6 || c < 1 || c >= 15 || gameField[r][c] != sym) {
                break;
            }
            count++;
        }

        // 根据连珠长度增加评分
        if (count == 2) score += 10;
        if (count == 3) score += 50;
        if (count >= 4) score += 1000;  // 直接获胜
    }

    return score;
}
