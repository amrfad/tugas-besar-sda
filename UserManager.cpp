#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include "User.h"
#include "UserManager.h"

namespace fs = std::filesystem;

UserManager::UserManager()
{
    loadUsersFromFile();
}

void UserManager::registerUser(const std::string &name, const std::string &password)
{
    int newUserId = users.size() + 1;
    User newUser(newUserId, name, password);
    users.push_back(newUser);
    saveUsersToFile();
}

User *UserManager::loginUser(const std::string &name, const std::string &password)
{
    for (auto &user : users)
    {
        if (user.getUserName() == name && user.getPassword() == password)
        {
            // Buat direktori MyDownload jika belum ada
            fs::path downloadPath = fs::current_path() / "MyDownload"; /* / std::to_string(user.getUserId()); */
            if (!fs::exists(downloadPath))
            {
                fs::create_directory(downloadPath);
            }

            // Pindahkan lagu-lagu yang tercatat dalam downloadedSongs ke direktori MyDownload
            if  (!user.downloadedSongs.empty()) {
                for (const auto &song : user.downloadedSongs)
                {
                    // Pindahkan file lagu ke direktori MyDownload
                    downloadSong(song);
                }
            }

            return &user;
        }
    }
    return nullptr;
}

void UserManager::logoutUser(User &user)
{
    // Hapus semua file dalam direktori MyDownload
    fs::path downloadPath = fs::current_path() / "MyDownload" / std::to_string(user.getUserId());
    if (fs::exists(downloadPath))
    {
        fs::remove_all(downloadPath);
    }

    // Kosongkan downloadedSongs
    user.downloadedSongs.clear();
}

void UserManager::addDownloadedSong(User &user, std::string song)
{
    // Simpan file lagu ke direktori MyDownload
    downloadSong(song);
    user.downloadedSongs.push_back(song);
}

void UserManager::loadUsersFromFile()
{
    std::ifstream file(userFilePath);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            User user;
            std::stringstream ss(line);
            std::string token;
            
            // Parsing userId
            std::getline(ss, token, ',');
            user.userId = std::stoi(token);
            
            // Parsing name
            std::getline(ss, token, ',');
            user.name = token;
            
            // Parsing password
            std::getline(ss, token, ',');
            user.password = token;
            
            // Parsing downloadedSongs
            std::getline(ss, token); // Mengambil sisa baris
            std::stringstream songsSs(token);
            while (std::getline(songsSs, token, '|'))
            {
                user.downloadedSongs.push_back(token);
            }
            
            users.push_back(user);
        }
        file.close();
    }
}

void UserManager::saveUsersToFile()
{
    std::ofstream file(userFilePath);
    for (const auto &user : users)
    {
        std::stringstream line;
        line << user.userId << ",";
        line << user.name << ",";
        line << user.password << ",";
        if (!user.downloadedSongs.empty()) {
            for (const auto &song : user.downloadedSongs)
            {
                line << song << "|";
            }
        }
        file << line.str() /*.substr(0, line.str().length() - 1)*/ << std::endl; // Menghapus pemisah terakhir
    }
    file.close();
}