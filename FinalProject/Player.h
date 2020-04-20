#pragma once
#include <iostream>//this library is for cout and cin
#include <cstdlib>//this library is for the random function
#include <string>//this library lets you use strings
#include <ctime>//lets the computer perform random functions, without it, the random function would not be as random
#include <vector>//lets me store the items in a master list and the players inventory
#include <cmath>
#include "Store.h"

//namespace gets rid of adding 'std::' as part of cout and cin
using namespace std;

int getPlayerHealth(int mod);//this gets the player health
string GetUserName();//gets the username
int addPlayerStat(string stat, int arr[]);//adds the rolled stat to the player
void getStats(int& Strength, int& Dexterity, int& Constitution, int& Intelligence, int& Wisdom, int& Charisma);//this gets the stats of the player
int rollDice(int numOfDice, int numOfSides, int modifier, bool playerStats);//this rolls a certain number of dice



class Player
{
public:

	//the amount of money your character has
	int Money = 0;

	//armor class is the chance you can evade incoming attacks
	int ac = 0;

	//name
	string UserName;

	//stats
	int Strength;
	int Dexterity;
	int Constitution;
	int Intelligence;
	int Wisdom;
	int Charisma;

	//modifiers
	int StrMod;
	int DexMod;
	int ConMod;
	int IntMod;
	int WisMod;
	int ChaMod;

	//health
	int Health;

	//player inventory
	vector<Item> PlayerInventory;
	int carrying_capacity = 20;

	//this is the constructor that builds the player
	Player();
	//adds item to player inventory
	void addItem(Item& inventoryItem);
	//deletes item from player inventory
	void deleteItem(Item& inventoryItem);

	void showItem(Item& inventoryItem);

	int searchPlayerItem(string name);

	void displayInventory();

	void PlayerStats();

	void EquipItem();
};