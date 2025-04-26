#include<windows.h>
#include<ctime>

#include"VierGewinnt.h"

// Für die Abgabe sollte an der main Funktion nichts verändert werden
int main() {

	srand(time(NULL));

	VierGewinnt myGame = VierGewinnt();
	while (true) {

		myGame.playerMove();

		myGame.computerMove();

	}


	system("pause");
	return 0;
}
