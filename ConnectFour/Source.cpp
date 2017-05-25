#include<iostream>
#include <SFML/Audio.hpp>
using namespace std;

//Prototypes
void display();
bool check(int a, int b);
int drop(int b, char player);
char place[6][7];//available for whole program  


int main() 
{
	//load and play Welcome sound fx
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Welcome.wav"));
	sf::Sound effect1;
	effect1.setBuffer(buffer);
	effect1.play();

	//load Drop sound fx
	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("Coin.wav"));
	sf::Sound effect2;

	//load Win sound fx
	sf::SoundBuffer buffer3;
	if (!buffer3.loadFromFile("Win.wav"));
	sf::Sound effect3;

	//load Win sound fx
	sf::SoundBuffer buffer4;
	if (!buffer4.loadFromFile("Tie.wav"));
	sf::Sound effect4;

	//load Goodbye sound fx
	sf::SoundBuffer buffer5;
	if (!buffer5.loadFromFile("Goodbye.wav"));
	sf::Sound effect5;



	//fill place with whitespace
	for (int a = 0; a <= 5; a++) 
	{		
		for (int b = 0; b <= 6; b++)
			place[a][b] = ' ';		
	}							

	display();//Displays for first time so players can see the board
	int hold;//Will house user row choice
	int hold2 = 0;//will hold drop value
	int charsPlaced = 0;//Number of pieces dropped so can end game if a draw
	bool gamewon = false;//Will be changed to true when game is won and will exit while loop
	char player = 43;//start as player 2 will change back 2 player 1
	char answer;

	while (!gamewon) //while game is not won
	{
		if (hold2 != -1) //check if there was a error in the last drop
		{
			if (player == 43) //if player 2 last dropped a piece so its player 1s turn
			{
				cout << "Player 1 drop where?";
				player = 254;//char of player 1 piece
			}
			else 
			{
				cout << "Player 2 drop where?";
				player = 43;//char of player 2 piece
			}
		}

		while (true) //will run until 'break;'
		{
			if (charsPlaced == 42) break;//if true, it's a draw

			cin >> hold;//get user input
			hold--;//take off 1 to account for arrays starting at 0 not 1

			if (hold <= 6 && hold >= 0) break;//if within valid range stop loop

			else cout << "\nplease enter a value between 1 and 7 :";//ask for input and loop again
			
			//Catch a non number
			if (cin.fail())
			{
				cin.clear(); //Stops cin trying to put its value in to hold
				char c;	//Try entering a non number without this, 2 see what this does
				cin >> c;
			}

		}

		if (charsPlaced == 42)
		{
			//play Goodbye sound fx
			effect4.setBuffer(buffer4);
			effect4.play();

			break;//if true, it's a draw
		}
		hold2 = drop(hold, player);//drop the player store the row in hold2

		
		if (hold2 == -1)	cout << "Column is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
		else 
		{
			gamewon = check(hold2, hold);//check if game is run
			charsPlaced++;//another character has been succesfully placed
			system("cls");//This clears the screen works with windows, not nesscery to run game
			display();//displayed updated board

			//play Drop sound fx
			effect2.setBuffer(buffer2);
			effect2.play();
		}

	}

	//TIE
	if (charsPlaced == 42)
	{
		cout << "\n\nNo winner, Game is a draw\n";
		cout << "Play again? (y/n)" << endl;
		cin >> answer;
		if (answer == 'y' || answer == 'Y') //Restart
		{
			system("cls");
			main();
			cin.clear();
		}
		else //Exit
		{
			//play Goodbye sound fx
			effect5.setBuffer(buffer5);
			effect5.play();

			system("pause");
			return 0;//Exit
		}

		//system("pause");
		//return 0;
	}

	//WINNER
	if (charsPlaced != 42)
	{
		if (player == 43)//if won by player 2
			cout << "Game Won by Player 2!\n\n";
		else cout << "Game Won by Player 1!\n\n";//Else won by player 1

		//play Win sound fx
		effect3.setBuffer(buffer3);
		effect3.play();

		cout << "Play again? (y/n)" << endl;
		cin >> answer;
		if (answer == 'y' || answer == 'Y') //Restart
		{
			system("cls");
			main();
			cin.clear();
		}
		else //Exit
		{
			//play Goodbye sound fx
			effect5.setBuffer(buffer5);
			effect5.play();

			system("pause");
			return 0;//Exit
		}
	}
}

//Display Board
void display() 
{
	cout << "Welcome to Connect Five!\nBy Casey Aitken\n\n";
	cout << " 1   2   3   4   5   6   7\n";
	for (int a = 0; a <= 5; a++)
	{
		for (int b = 0; b <= 6; b++) cout << char(218) << char(196) << char(191) << " ";
		cout << '\n';
		for (int b = 0; b <= 6; b++) cout << char(179) << place[a][b] << char(179) << " ";
		cout << '\n';
		for (int b = 0; b <= 6; b++) cout << char(192) << char(196) << char(217) << " ";
		cout << '\n';
	}
}

//Check for a winner
bool check(int a, int b) 
{
	int vertical = 1;//(|)
	int horizontal = 1;//(-)
	int diagonal1 = 1;//(\)
	int diagonal2 = 1;//(/)
	char player = place[a][b];
	int i;//vertical
	int ii;//horizontal

	//check for vertical(|)
	for (i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);//Check down
	for (i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);//Check up
	if (vertical >= 5)return true;

	//check for horizontal(-)
	for (ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);//Check left
	for (ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);//Check right
	if (horizontal >= 5) return true;

	//check for diagonal 1 (\)
	for (i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);//up and left
	for (i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);//down and right
	if (diagonal1 >= 5) return true;

	//check for diagonal 2(/)
	for (i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);//up and right
	for (i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);//up and left
	if (diagonal2 >= 5) return true;


	return false; //false = no winner
}

//Drop piece
int drop(int b, char player) 
{
	if (b >= 0 && b <= 6)
	{
		if (place[0][b] == ' ') 
		{
			int i;
			for (i = 0; place[i][b] == ' '; i++)
				if (i == 5) 
				{
					place[i][b] = player;
					return i;
				}
			i--;
			place[i][b] = player;
			return i;
		}
		else 
		{
			return -1;
		}
	}
	else 
	{
		return -1;
	}

}
