#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>
#include "User.h"

class UserManager {
private:
    std::vector<User> users;
    std::string userFilePath = "assets/users.txt";

    void loadUsersFromFile();

public:
    UserManager();

    void registerUser(const std::string& name, const std::string& password);
    User* loginUser(const std::string& name, const std::string& password);
    void logoutUser(User& user);
    void addDownloadedSong(User &user, std::string song);
    void saveUsersToFile();
};

#endif // USERMANAGER_H
