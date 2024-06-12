#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Song.h"
#include "User.h"
#include "UserManager.h"

void print(std::string text);
void println(std::string text);
void printLoginMenu(UserManager* userManager);
void printMainMenu(UserManager* userManager, User* user);
void printMenu(UserManager* userManager);