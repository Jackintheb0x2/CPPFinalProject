
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



//handles all of the commands
void Commands(string command, Player& player, vector<Item>& StoreItems, bool store)
{
	//displays all of the commands if the command is /help
	if (command == "/help")
	{
		cout << "\nthese are all of the commands you can do\n";
		cout << "/help  | /inventory          | /storeitem\n";
		cout << "/stats | /drop (item name)   | /playeritem (name)\n";
		cout << "/quit  | /buy (in store only)| /sell (in store only)\n";
		cout << "/store | /equip (item name)  | /gearEquipped\n";
	}
	else if (command == "/stats")
	{
		//gets the player stats
		player.PlayerStats();
	}
	else if (command == "/inventory")
	{
		//gets the player's inventory
		if (player.PlayerInventory.empty())
		{
			cout << "\nYou have no items!\n";
		}
		else
		{
			player.displayInventory();
		}
	}
	else if (command == "/store")
	{
		if (store)
		{
			//displays all of the items you can buy
			Store(StoreItems);
		}
		else
		{
			cout << "\nThe store command is disabled, you have to be in the store to call this command\n";
		}

	}
	//command.find is for if you need to input anything extra like an item
	else if (command.find("/buy") == 0)
	{
		if (store)
		{
			//finds the name of the item you want to buy
			string itemName = command.substr(5, command.length() - 5);
			int ItemID = SearchStoreItem(StoreItems, itemName);


			if (ItemID == -1)
			{
				//did not find the item
				cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
			}
			else
			{
				//if you have enough money AND you can carry it
				if (player.Money >= StoreItems[ItemID].cost && player.carrying_capacity >= StoreItems[ItemID].weight)
				{
					player.Money -= StoreItems[ItemID].cost;
					player.carrying_capacity -= StoreItems[ItemID].weight;
					player.addItem(StoreItems[ItemID]);
					cout << "Item Bought!\n";
				}
				else
				{
					cout << "\nYou do not have enough Money and/or Space \nin your inventory. Try buying a bag to \nincrease your carrying capacity.\n";
				}
			}

		}
		else
		{
			cout << "\nThe store command is disabled, you have to be in the store to call this command\n";
		}
	}
	//command.find is for if you need to input anything extra like an item
	else if (command.find("/sell") == 0)
	{
		if (store)
		{
			if (player.PlayerInventory.empty()) {
				cout << "\nYou have no items!\n";
			}
			else
			{
				//finds the name of the item you want to drop
				string itemName = command.substr(6, (command.length() - 6));
				//convert string name to item id
				int id = player.searchPlayerItem(itemName);
				if (id == -1)
				{
					//did not find the item
					cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
				}
				else {
					player.Money += (player.PlayerInventory[id].cost / 2);
					player.carrying_capacity += player.PlayerInventory[id].weight;
					//calls the delete item function in player
					player.deleteItem(player.PlayerInventory[id]);
					cout << "Item Sold!\n";
				}
			}
		}
		else
		{
			cout << "\nThe store command is disabled, you have to be in the store to call this command\n";
		}
	}
	//command.find is for if you need to input anything extra like an item
	else if (command.find("/drop") == 0)
	{
		if (player.PlayerInventory.empty()) {
			cout << "\nYou have no items!\n";
		} 
		else
		{
			//finds the name of the item you want to drop
			string itemName = command.substr(6, (command.length() - 6));
			//convert string name to item id
			int id = player.searchPlayerItem(itemName);
			if (id == -1)
			{
				//did not find the item
				cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
			}
			else {
				//calls the delete item function in player
				player.carrying_capacity += player.PlayerInventory[id].weight;
				player.deleteItem(player.PlayerInventory[id]);
				cout << "Item Dropped. You cannot get this back!\n";
			}
		}
	}
	//command.find is for if you need to input anything extra like an item
	else if (command.find("/playeritem") == 0) {
		if (player.PlayerInventory.empty()) {
			cout << "\nYou have no items!\n";
		}
		else
		{
			string itemName = command.substr(12, (command.length() - 12));
			int id = player.searchPlayerItem(itemName);
			if (id == -1)
			{
				//did not find the item
				cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
			}
			else {
				//calls the delete item function in player
				player.showItem(player.PlayerInventory[id]);
			}
		}
	}
	else if (command.find("/storeitem") == 0) {
		string itemName = command.substr(11, (command.length() - 11));
		int id = SearchStoreItem(StoreItems, itemName);
		if (id == -1)
		{
			//did not find the item
			cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
		}
		else {
			//calls the delete item function in player
			showStoreItem(StoreItems[id]);
		}
	}
	else if (command.find("/equip") == 0) {
		cout << "\nNot implemented yet!\n";
	}
	else if (command == "/gearEquipped") {
		cout << "\nNot implemented yet!\n";
	}
	else if (command == "/quit")
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		cout << "\nUnrecognized command. Type '/help' to see the list of commands.\n";
	}

}