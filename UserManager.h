#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>
#include "User.h"

class UserManager {
private:
    std::vector<User> users;
    std::string userFilePath;

    void loadUsersFromFile();
    void saveUsersToFile();

public:
    UserManager();

    void registerUser(const std::string& name, const std::string& password);
    User* loginUser(const std::string& name, const std::string& password);
    void logoutUser(User& user);
    void addDownloadedSong(User& user, const Song& song);
};

#endif // USERMANAGER_H
