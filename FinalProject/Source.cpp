#include <iostream>//this library is for cout and cin
#include <cstdlib>//this library is for the random function
#include <string>//this library lets you use strings
#include <ctime>//lets the computer perform random functions, without it, the random function would not be as random
#include <vector>//lets me store the items in a master list and the players inventory
#include <cmath>
#include "Player.h"
#include "Store.h"
#include "Commands.h"

//namespace gets rid of adding 'std::' as part of cout and cin
using namespace std;

//PROTOTYPE FUNCTIONS
void Introduction();//just dialog explaining the game
string answer(Player& player, vector<Item>& Items, bool storeEnabled);
void Decision(vector<string>& decision);//enter a string of different options and will print out a menu
void Tavern(Player& player, vector<Item>& Items);
//created prototype of master item list



//this is the main function where everything gets run here first

int main()
{
	//all of the variables
	bool storeEnabled = true;
	string answer;
	//this lets rolls be randomized
	srand(static_cast<unsigned int>(time(nullptr)));

	cout << "\n\n\t\tWELCOME TO DUNGEON CRAWLER\n\n";

	Introduction();
	//this creates a new instance of the player class
	Player player;
	player.Money += 10000;
	player.PlayerStats();


	vector<Item> Items = createItems();
	

	cout << "Welcome " << player.UserName << "!\ntype '/help' to see the list of commands available\nor you can continue with the story.\n\n\n";
	
	while (true) {
		getline(cin, answer);
		if (answer.find('/') == 0)
		{
			Commands(answer, player, Items, storeEnabled);
		}
	}


	//Tavern(player, Items);

	return 0;
}

string answer(Player& player, vector<Item>& Items, bool storeEnabled) {
	string answer;
	cin >> answer;
	getline(cin, answer);
	if (answer.find('/') == 0)
	{
		Commands(answer, player, Items, storeEnabled);
	}
	else {
		return answer;
	}
}

//this function displays the menu for a number of options
void Decision(vector<string>& decision)
{
	cout << "\nMENU:";
	cout << "\n----------\n";
	for (int i = 0; i < decision.size(); i++)//for loop displays each decision
	{
		cout << i + 1 << ". " << decision[i] << "\n";
	}
	
}

//introduction dialog
void Introduction()
{
	cout << "Welcome player!\nThis is Dungeon Crawler, a text-based \ninteractive story game where you \ntry to defeat a dungeon!\n\n";
	cout << "\n\nBefore we begin, we need to create your character!\n";
	system("pause");
}

void Tavern(Player& player, vector<Item>& Items) {
	vector<string> choices;
	string userAnswer;
	cout << "Your story starts in a tavern where you are minding your own business and a rugged looking guy stumbles in.\n";
	cout << "'Hello? Anyone! You've got to help me! A dungeon was just discovered and it's crawling with monsters!'\n";
	cout << "What will you do?\n";
	
	choices.push_back("Approach");
	choices.push_back("Ignore");
	Decision(choices);
	choices.clear();
	userAnswer = answer(player, Items, false);
}