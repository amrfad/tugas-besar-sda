#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Song.h"
using namespace std;

struct User {
    int userId;
    string name;
    string password;
    vector<LicenseTicket> licenses; // Daftar tiket lisensi yang dimiliki pengguna
};

#endif