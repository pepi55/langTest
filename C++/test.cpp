#include<iostream>
using namespace std;

bool running = 1;
int userInput = 0;
int playerPick[2]; //amount of player choices
int playerLocation = 0;

void titleFunc();
void newGame();

int main() {
	titleFunc();

  while (running) {
		if (playerLocation == 1)
		{
			cout << "\nYou are now placed inside a labyrinth and it is _your_ duty to get out alive!\n";
			cout << "you can only go forward right now\n";
			cout << " 1: Go forward\n 2: F*ck you I'm not obeying _you_ fatass!!!\n";

			cin >> userInput;

			if (userInput == 1) playerLocation = 2; //2 = forwardArea
			else if (userInput == 2) playerLocation = 3; // 3 = f*ck_youArea
		} else if (playerLocation == 2) {
			cout << "\nYou won!!\n";
			cout << "It was an easy labyrinth *deal with it*\n";
			cout << "Care for another game?\n";
			cout << " 1: Ye, sure\n 2: Nopenopenopenopenopenope\n";

			cin >> userInput;

			if (userInput == 1) playerLocation = 1; //location1 = play agaime
			else if (userInput == 2) playerLocation = 4;
		} else if (playerLocation == 3) {
			cout << "\nEach time you disobey a Chanisco gets b*tchslapped due to a DHL driving by...\n";
			cout << "Try again; there are still 2 options:\n";
			cout << " 1: Go forward\n 2: Nopenopenopenopenopenopenope\n";

			cin >> userInput;

			if (userInput == 1) playerLocation = 2; //2 = forwardArea
			else if (userInput == 2) playerLocation = 3; //for now its still f*ck_youArea
		} else if (playerLocation == 4) {
			cout << "\n GAME OVER \n";

			running = 0;
		}
  }

  return 0;
}

void newGame() {
	cout << "Welcome to Phantasee, where you can be as creative as you like.\n";
	cout << "Looks like we have a new guy here!\n";
	cout << "Why dont you tell me what kind of person you are?\n 1: Warrior\n 2: Archer\n Anything else quits\n";
	cin >> userInput;
	playerPick[0] = userInput;

	if (userInput != 1 || userInput != 2) {
		running = 0;
		playerLocation = 1;
	}

	cout << "Now tell me, are you a male or female?\n 1: Male\n 2: Female\n Anything else quits\n";
	cin >> userInput;
	playerPick[1] = userInput;

	if (userInput != 1 || userInput != 2) {
		running = 0;
	}

	//playerLocation = 1;

	return;
}

void titleFunc() {
	cout << "-----===={ Phantasee }====-----\n\n";
	cout << "	   1: Play!\n\n";
	cout << "-----====<<<<<[=]>>>>>====-----\n";

	cin >> userInput;

	if (userInput == 1) {
		newGame();
	} else {
		running = 0;
	}

	return;
}
