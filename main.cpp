#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Song.h"
#include "User.h"
#include "Menu.h"

int main()
{
    UserManager userManager = UserManager();

    _SongList.loadSongsFromFile();

    printLoginMenu(&userManager);

    _SongList.saveSongsToFile();
    userManager.saveUsersToFile();

    return 0;
}