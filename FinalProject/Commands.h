#pragma once

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

void Commands(string command, Player& player, vector<Item>& list, bool store);