#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Song.h"

struct User
{
    int userId;
    std::string name;
    std::string password;
    std::vector<Song> downloadedSongs; // Daftar lagu yang telah diunduh oleh pengguna

    User();
    User(int id, const std::string &userName, const std::string &userPassword);

    int getUserId() const;
    std::string getUserName() const;
    void setUserName(const std::string &newName);
    std::string getPassword() const;
    void setPassword(const std::string &newPassword);
};

#endif