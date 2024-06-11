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

// Fungsi untuk mendapatkan daftar lisensi yang dimiliki pengguna
const std::vector<LicenseTicket>& User::getLicenses() const {
    return licenses;
}

// Fungsi untuk menambahkan lisensi baru ke daftar lisensi pengguna
void User::addLicense(const LicenseTicket& license) {
    licenses.push_back(license);
}

// Fungsi untuk menghapus lisensi dari daftar lisensi pengguna berdasarkan ID lagu dan ID pengguna
void User::removeLicense(int songId, int userId) {
    for (auto it = licenses.begin(); it != licenses.end(); ++it) {
        if (it->songId == songId && it->userId == userId) {
            licenses.erase(it);
            break;
        }
    }
}