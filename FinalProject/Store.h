#pragma once
#include <iostream>//this library is for cout and cin
#include <cstdlib>//this library is for the random function
#include <string>//this library lets you use strings
#include <ctime>//lets the computer perform random functions, without it, the random function would not be as random
#include <vector>//lets me store the items in a master list and the players inventory
#include <cmath>


//namespace gets rid of adding 'std::' as part of cout and cin
using namespace std;



//this data type is to categorize different items
enum itemType
{
	Armor,
	Potion,
	Ring,
	Weapon,
	Misc_Item
};


//this class creates all of the items the game will use
struct Item
{
	//id
	//name
	//flavor text
	//type
	//cost
	//weight
	//properties
	//requirement
	int id;
	string name;
	itemType type;
	string flavor_text;
	int cost;
	int weight;
	string property;
	int requirement_level;
	int effect;

	//creates a constructor of the class so everytime it is called, it creates a new item with its own set of properties
	Item(int Id, string Name, itemType Type, string Flavor_text, int Cost, int Weight, string Property, int Requirement, int Effect)
	{
		id = Id;
		name = Name;
		type = Type;
		flavor_text = Flavor_text;
		cost = Cost;
		weight = Weight;
		property = Property;
		requirement_level = Requirement;
		effect = Effect;
	}
};


vector<Item> createItems();
void Store(vector<Item>& list);
int SearchStoreItem(vector<Item> StoreItem, string ItemName);
void showStoreItem(Item& inventoryItem);