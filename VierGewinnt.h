#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>

using namespace std;

class VierGewinnt
{

public:

	VierGewinnt();

	//Spieler Zug
	void playerMove();

	//Computer Zug
	void computerMove();


private:

	//Das 2D Spielfeld in dem alle Informationen als String gespeichert werden
	vector<vector<string>> gameField; //可能可以用char节省空间

	//Funktion welchen den Vektor mit den Startbedingungen fällt
	//根据初始条件计算向量的函数
	void fillVector();

	//Zeigt das Spielfeld auf der Konsole an
	//在控制台显示比赛场地
	void showGame();

	void printCellWithColor(const std::string& sym);

	//Checkt ob das Spiel zu ende ist
	//检查游戏是否结束
	bool checkIfGameOver(int row,int column,string sym);

	//Lasst die Steine herunterfallen
	//让棋子下落
	void updateGameField(int column, string sym, int& row, int& col);

	//Checkt ob der gewählte Zug erlaubt ist
	//检查输入是否合法
	bool checkIfValidMove(int column);

	//überprüft ob der Stein weiter fallen kann
	//检查棋子是否能继续下落
	bool checkIfCanFall(int i, int j);

	//Gibt den höchsten Score zurück
	//返回最高分数
	int countScore(string sym, int i, int j);

	//Wenn Gameover reset das Spiel
	//游戏重新开始
	void resetGame();

	bool simulateMove(int column, std::string sym, int& row);

	void undoMove(int row, int column);

	bool isBoardFull();

	int evaluatePosition(int column, int row, std::string sym);

	//Auswahl des Zuges für Spieler
	//玩家移动的选择
	void playerMoveLogic();
	
	
	//Vielleicht noch eine Funktion aus einer externen Datei 
	// den Spielstand auszulesen und zu Speichern?

	//void loadScore();
	
};
