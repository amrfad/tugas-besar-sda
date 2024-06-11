#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include "User.h"

namespace fs = std::filesystem;

class UserManager {
private:
    std::vector<User> users;
    std::string userFilePath = "asset/users.bin";

public:
    UserManager() {
        loadUsersFromFile();
    }

    void registerUser(const std::string& name, const std::string& password) {
        int newUserId = users.size() + 1;
        User newUser(newUserId, name, password);
        users.push_back(newUser);
        saveUsersToFile();
    }

    User* loginUser(const std::string& name, const std::string& password) {
        for (auto& user : users) {
            if (user.getUserName() == name && user.getPassword() == password) {
                // Buat direktori MyDownload jika belum ada
                fs::path downloadPath = fs::current_path() / "MyDownload" / std::to_string(user.getUserId());
                if (!fs::exists(downloadPath)) {
                    fs::create_directory(downloadPath);
                }

                // Pindahkan lagu-lagu yang tercatat dalam downloadedSongs ke direktori MyDownload
                for (const auto& song : user.downloadedSongs) {
                    // Pindahkan file lagu ke direktori MyDownload
                    downloadSong(song.title);
                }

                return &user;
            }
        }
        return nullptr; 
    }

    void logoutUser(User& user) {
        // Hapus semua file dalam direktori MyDownload
        fs::path downloadPath = fs::current_path() / "MyDownload" / std::to_string(user.getUserId());
        if (fs::exists(downloadPath)) {
            fs::remove_all(downloadPath);
        }

        // Kosongkan downloadedSongs
        user.downloadedSongs.clear();
    }

    void addDownloadedSong(User& user, const Song& song) {
        user.downloadedSongs.push_back(song);
        // Simpan file lagu ke direktori MyDownload
        downloadSong(song.title);
    }

private:
    void loadUsersFromFile() {
        // Implementasi pembacaan data pengguna dari file
        std::ifstream file(userFilePath, std::ios::binary);
        if (file.is_open()) {
            User user;
            while (file.read(reinterpret_cast<char*>(&user), sizeof(User))) {
                users.push_back(user);
            }
            file.close();
        }
    }

    void saveUsersToFile() {
        // Implementasi penyimpanan data pengguna ke file
        std::ofstream file(userFilePath, std::ios::binary);
        for (const auto& user : users) {
            file.write(reinterpret_cast<const char*>(&user), sizeof(User));
        }
        file.close();
    }
};