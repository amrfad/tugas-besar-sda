#include "User.h"

// Konstruktor default untuk User
User::User() {
    userId = 0;
    name = "";
    password = "";
}

// Konstruktor dengan parameter untuk User
User::User(int id, const std::string& userName, const std::string& userPassword) {
    userId = id;
    name = userName;
    password = userPassword;
}

// Fungsi untuk mengambil ID pengguna
int User::getUserId() const {
    return userId;
}

// Fungsi untuk mengambil nama pengguna
std::string User::getUserName() const {
    return name;
}

// Fungsi untuk mengubah nama pengguna
void User::setUserName(const std::string& newName) {
    name = newName;
}

// Fungsi untuk mengambil password pengguna
std::string User::getPassword() const {
    return password;
}

// Fungsi untuk mengubah password pengguna
void User::setPassword(const std::string& newPassword) {
    password = newPassword;
}
