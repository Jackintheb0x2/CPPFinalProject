#include <iostream>//this library is for cout and cin
#include <cstdlib>//this library is for the random function
#include <string>//this library lets you use strings
#include <ctime>//lets the computer perform random functions, without it, the random function would not be as random
#include <vector>//lets me store the items in a master list and the players inventory
#include <cmath>
#include "Player.h"
#include "Store.h"

//namespace gets rid of adding 'std::' as part of cout and cin
using namespace std;


//this function connects to the getstat function and it applies the stat with one of the rolls
//it also returns the stat it added to and takes in the stat it's applying and the array of all your roles
int addPlayerStat(string stat, int arr[])
{
	
	//creates two variables: one for the players choice to choose which roll to use for the particular stat
	//and the added stat variable which applies the new stat to the stat
	int choice;
	int addStat = 0;

	//this while loop is in case you enter an incorrect index and it will ask you to enter a valid number
	do {
		//this check is for a goto
		//I know I'm suppose to avoid using this but I couldn't think of an easier way
	check:
		cout << stat << ": ";//displays the stat you are applying one of your rolls to
		cin >> choice;//takes in the user's choice for the roll it wants to apply
		choice--;//because the index starts at 0, subtracting one makes it choose the right index
		//if (arr[choice] !< 6 && arr[choice] !> 0) {
		//	cout << "\nThis is not an answer! choose from 1 - 6 to place the stat you want.\n";
		//	goto check;
		//}
		if (arr[choice] == 0)//this if is to check if the player has already chose that role
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto check;//if it does than this line is called and it gets sent back up to the top of the loop
		}
		addStat = arr[choice];//finally, if everything checks out, then the roll gets added to the stat
		arr[choice] = 0;//the chosen roll gets changed to a 0 signifying that it has been chosen already
	} while (choice < 0 || choice > 6);//this loop will only run while the choice is one of the elements of the array

	//this for loop displays the current array after it's been modified
	for (int i = 0; i < 6; i++) { cout << arr[i] << ", "; }
	cout << "\n\n";
	//returns the new stat that has been added
	return addStat;
}

//this function is called from the player class to get the stats for that character
//the arguments in this function just reference the stats from the player class
void getStats(int& Strength, int& Dexterity, int& Constitution, int& Intelligence, int& Wisdom, int& Charisma)
{
	
	//create an array to store all of the rolls
	int statID[6];
	//this for loop goes through 6 times and adds the roll to the array
	for (int i = 0; i < 6; i++)
	{
		//calls the function and stores the roll in the current index 
		statID[i] = rollDice(4, 6, 0, true);
	}
	cout << "\n\n\nThere are six stats: Strength, Dexterity, Constitution, Intelligence, Wisdom, and Charisma";
	cout << "\nPick which index (starting with 1) you want to put into your stat\n";
	//displays all of your rolls
	for (int i = 0; i < 6; i++) { cout << statID[i] << "  "; }
	cout << "\n\n";

	//calls the function to add the roll to each stat
	Strength = addPlayerStat("Strength", statID);
	Dexterity = addPlayerStat("Dexterity", statID);
	Constitution = addPlayerStat("Constitution", statID);
	Intelligence = addPlayerStat("Intelligence", statID);
	Wisdom = addPlayerStat("Wisdom", statID);
	Charisma = addPlayerStat("Charisma", statID);
	
}


//this roll dice function is for all of the roll dicing needs
//it takes in the number of dice, the number of sides for the dice, the modifier,
//and says if this is for player stats or not
int rollDice(int numOfDice, int numOfSides, int modifier, bool playerStats)
{

	//these two variables are for the total value, and the current die value
	int total = 0;
	int dieValue = 0;


	//rolling for player stats is special because you roll 4d6 and take the highest 3
	if (playerStats)
	{
		//stores the all 4 roles in an array
		int die[4];
		//these variables store the first second and third highest numbers in the array
		int firstHigh, secondHigh, thirdHigh;
		//initializes the three variables to the lowest value
		firstHigh = secondHigh = thirdHigh = INT_MIN;

		cout << "\nto roll, ";
		system("pause");

		//the for loop rolls 4 dice
		for (int i = 0; i < numOfDice; i++)
		{

			//this gets the value of the die and stores it into the array
			die[i] = (rand() % numOfSides) + 1;

			//it then checks to see if it is the highest, the second highest, or the third highest
			if (die[i] > firstHigh)
			{
				thirdHigh = secondHigh;
				secondHigh = firstHigh;
				firstHigh = die[i];
			}
			else if (die[i] > secondHigh)
			{
				thirdHigh = secondHigh;
				secondHigh = die[i];
			}
			else if (die[i] > thirdHigh)
			{
				thirdHigh = die[i];
			}
		}

		//after all 4 rolls are made, it adds them to the total value
		total = firstHigh + secondHigh + thirdHigh;
		//displays the total
		cout << "\nYou Rolled a total of " << total;

	}
	else//if it's not a regular roll
	{
		//it loops the amount of time there are number of dice
		for (int i = 0; i < numOfDice; i++)
		{
			cout << "\nto roll, ";
			system("pause");
			//this gets the value of the die
			dieValue = (rand() % numOfSides) + 1;
			cout << "\n * You rolled a " << dieValue << "! * \n\n";
			total += dieValue;//it adds the die value to the current total value
		}
	}

	//lastly, it adds the modifier to the total variable
	total += modifier;

	//it then returns the total
	return total;
}

//gets the username for the player
string GetUserName()
{
	//declares a string
	string UserName;
	cout << "Enter your character name :>";
	//getline is an input for the characters name
	getline(cin, UserName);
	//returns the user name
	return UserName;
}

//when the player gains a level this function is called to gain more health
//this function takes in the players constitution mod and returns the amount of health it gained
int getPlayerHealth(int mod)
{
	//creates a new variable that calls the roll dice function
	int health = rollDice(2, 10, mod, false);
	//returns the health it gained
	return health;
}


//this is the constructor that builds the player
Player::Player()
{
	//gets player name
	UserName = GetUserName();

	//gets the stats for the player
	cout << "\nRoll for your stats! ";
	system("pause");
	getStats(Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma);
	//calculates the modifier per stat
	StrMod = (Strength - 10) / 2;
	DexMod = (Dexterity - 10) / 2;
	ConMod = (Constitution - 10) / 2;
	IntMod = (Intelligence - 10) / 2;
	WisMod = (Wisdom - 10) / 2;
	ChaMod = (Charisma - 10) / 2;

	//gets player's health
	cout << "\nStarting at first level, you start with a base 10HP + your constitution modifier\n";
	Health = 10 + ConMod;

	ac = 10 + DexMod;

	//roll for how much money you start off with
	cout << "\nNow you are going to roll 4d4 to see how much money you start with\n";
	Money = rollDice(5, 4, 0, false);
	Money *= 10;



}
//adds item to player inventory
void Player::addItem(Item& inventoryItem)
{
	PlayerInventory.push_back(inventoryItem);
	switch (inventoryItem.id) {
	case 35:
		carrying_capacity += 20;
		break;
	case 36:
		carrying_capacity += 50;
		break;
	case 37:
		carrying_capacity += 100;
		break;
	}
}
//deletes item from player inventory
void Player::deleteItem(Item& inventoryItem)
{
	auto it = PlayerInventory.begin();
	int id = -1;//starts at the beginning of the index of the player inventory
	do
	{
		++id;
	} while (inventoryItem.name != PlayerInventory[id].name && it != PlayerInventory.end());//it keeps looping until it finds the item or until it makes it to the end of the array

	advance(it, id);
	PlayerInventory.erase(it);

	switch (inventoryItem.id) {
	case 35:
		carrying_capacity -= 20;
		break;
	case 36:
		carrying_capacity -= 50;
		break;
	case 37:
		carrying_capacity -= 100;
		break;
	}

}

void Player::showItem(Item& inventoryItem)
{
	cout << "\n\n----------------------------------\n";
	cout << inventoryItem.name;
	cout << "\nType: " << inventoryItem.type;
	cout << "\nDescription: " << inventoryItem.flavor_text;
	cout << "\nCost: " << inventoryItem.cost;
	cout << "\nWeight: " << inventoryItem.weight;
	cout << "\nProperty: " << inventoryItem.property;
	cout << "\nRequired Level: lvl " << inventoryItem.requirement_level;
	switch (inventoryItem.type)
	{
	case Weapon:
		cout << "\nDamage: 1d" << inventoryItem.effect;
		break;
	case Armor:
		cout << "\nArmor: +" << inventoryItem.effect;
		break;
	case Potion:
		cout << "\nPotion: +" << inventoryItem.effect;
		break;
	case Ring:
		cout << "\nRing: +" << inventoryItem.effect;
		break;
	case Misc_Item:
		cout << "\n+" << inventoryItem.effect << " Carrying Capacity";
		break;
	}
	cout << "\n----------------------------------\n";
}

int Player::searchPlayerItem(string name)
{
	
	//goes through a while loop to check if the name argument matches the item name
	int id = -1;
	do
	{
		++id;
	} while (name != PlayerInventory[id].name && id < PlayerInventory.size() - 1);

	//if there is a match, it returns the id from the inventory vector
	if (name == PlayerInventory[id].name)
	{
		return id;
	}//else it returns a -1 which will be used to see if it came back false and -1 is impossible to return from a vector

	return -1;


}

void Player::displayInventory()
{
	cout << "\n\n";
	int id = 0;//this stores the id of each item
	int NameSize = 0;//these two variables organize the store to make it look nice
	int format = 0;
	int x = round(PlayerInventory.size() / 2);
	cout << "\nPLAYER INVENTORY\n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < 19; i++)
	{
		
		for (int j = 0; j < 2; j++)
		{
			if (id >= PlayerInventory.size()) {
				break;
			}
			//this first part lists the name
			//20 characters
			NameSize = PlayerInventory[id].name.size();
			format = 21 - NameSize;
			cout << PlayerInventory[id].name;
			for (int space = 0; space < format; space++)
			{
				cout << " ";
			}
			//this part list the costs
			cout << " | Cost: " << PlayerInventory[id].cost;
			format = 5 - to_string(PlayerInventory[id].cost).size();
			for (int space = 0; space < format; space++)
			{
				cout << " ";
			}
			//this part lists the weight
			cout << " | Weight: " << PlayerInventory[id].weight;
			format = 5 - to_string(PlayerInventory[id].weight).size();
			for (int space = 0; space < format; space++)
			{
				cout << " ";
			}
			cout << " | ";
			//increases the id to keep track of the item listed
			id++;
		}
		cout << "\n";
	}
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	cout << "\n\n";
}
void Player::PlayerStats()
{
	//displays stats
	cout << "\n------------------------------";
	cout << "\nPLAYER STATS:";
	cout << "\nName: " << UserName;
	cout << "\nStrength:     " << Strength << " | StrMod: " << StrMod;
	cout << "\nDexterity:    " << Dexterity << " | DexMod: " << DexMod;
	cout << "\nConstitution: " << Constitution << " | ConMod: " << ConMod;
	cout << "\nIntelligence: " << Intelligence << " | IntMod: " << IntMod;
	cout << "\nWisdom:       " << Wisdom << " | WisMod: " << WisMod;
	cout << "\nCharisma:     " << Charisma << " | ChaMod: " << ChaMod;
	cout << "\nPlayer Health: " << Health;
	cout << "\nArmor Class: " << ac;
	cout << "\nPlayer Money: $" << Money;
	cout << "\nPlayer Carrying Capacity: " << carrying_capacity;
	cout << "\n------------------------------\n\n";
}
void Player::EquipItem() {

}