#include "menu.h"

void print(std::string text) {
    std::cout << text;
}

void println(std::string text) {
    std::cout << text << std::endl;
}

void printLoginMenu(UserManager* userManager) {
    
    println("------------------------------------");
    println("       Aplikasi Bank Lagu           ");
    println("------------------------------------");
    println("1. Login");
    println("2. Register");
    println("3. Keluar");
    print("Masukkan pilihan anda: ");
    int choice;
    std::cin >> choice;
    std::cin.ignore(256, '\n');

    switch (choice) {
        case 1: {
            print("Masukkan Username: ");
            std::string username;
            std::getline(std::cin, username);
            print("Masukkan Password: ");
            std::string password;
            std::getline(std::cin, password);

            User* user = userManager->loginUser(username, password);
            if (user) {
                system("cls");
                printMainMenu(userManager, user);
            } else {
                println("Username atau password salah");
                getch();
                system("cls");
            }
            break;
        }
        case 2: {
            print("Masukkan Username: ");
            std::string username;
            std::getline(std::cin, username);
            print("Masukkan Password: ");
            std::string password;
            std::getline(std::cin, password);

            userManager->registerUser(username, password);
            println("Registrasi berhasil");
            getch();
            system("cls");
            break;
        }
        case 3: {
            system("cls");
            exit(0);
        }
    }
}

void printMainMenu(UserManager* userManager, User* user) {
    system("cls");
    while (true) {
        int pilihan;
        println("------------------------------------");
        println("        Aplikasi Bank Lagu          ");
        println("------------------------------------");
        println("1. Informasi User");
        println("2. Cari Lagu dalam Bank");
        println("3. Cetak Playlist");
        println("4. Sorting Lagu dalam Playlist");
        println("5. Registrasikan Lagu ke Bank");
        println("6. Memutar Lagu");
        println("7. Mengunduh Lagu");
        println("8. Verifikasi Lagu");
        println("9. Keluar\n");

        print("Masukkan pilihan anda : ");
        std::cin >> pilihan;
        std::cin.ignore(256, '\n');
        system("cls");

        if (pilihan == 1) {
            println("------------------------------------");
            println("          Informasi User            ");
            println("------------------------------------");
            println("User ID : " + std::to_string(user->getUserId()));
            println("Nama : " + user->getUserName());
            println("Lagu yang diunduh : ");
            if (!user->downloadedSongs.empty())
            for (const auto& song : user->downloadedSongs) {
                println(song);
            }
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 2) {
            println("------------------------------------");
            println("       Cari Lagu dalam Bank         ");
            println("------------------------------------");
            print("Masukkan judul lagu : ");
            std::string judul;
            std::getline(std::cin, judul);
            SongList songListTemp;
            if (_SongList.searchSong(judul) != NULL) {
                Song song = _SongList.searchSong(judul)->song;
                songListTemp.addSong(song);
                println("Lagu ditemukan.");
                songListTemp.printSongs();
            } else {
                println("Lagu tidak ditemukan.");
            }
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 3) {
            println("------------------------------------");
            println("           Cetak Playlist            ");
            println("------------------------------------");
            println("Playlist : ");
            _SongList.printSongs();
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 4) {
            println("------------------------------------");
            println("    Sorting Lagu dalam Playlist     ");
            println("------------------------------------");
            println("Pilih metode sorting : ");
            println("1. Ascending");
            println("2. Descending");
            print("Masukkan pilihan anda : ");
            int choice;
            std::cin >> choice;
            std::cin.ignore(256, '\n');
            if (choice == 1) {
                _SongList.sortSongs(true);
            } else if (choice == 2) {
                _SongList.sortSongs(false);
            } else {
                println("Pilihan tidak tersedia");
            }
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 5) {
            println("------------------------------------");
            println("    Registrasikan Lagu ke Bank      ");
            println("------------------------------------");
            println("Masukkan path dari lagu yang ingin diregistrasikan : ");
            std::string judul;
            std::cin >> judul;
            user->registerSong(judul);
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 6) {
            println("------------------------------------");
            println("            Putar Lagu              ");
            println("------------------------------------");
            print("Masukkan judul lagu : ");
            Song song;
            std::getline(std::cin, song.title);
            playSong(song);
            system("cls");

        } else if (pilihan == 7) {
            println("------------------------------------");
            println("            Unduh Lagu              ");
            println("------------------------------------");
            print("Masukkan judul lagu : ");
            std::string judul;
            std::getline(std::cin, judul);
            println("Memulai pengunduhan lagu ...");
            if (_SongList.searchSong(judul) != NULL) {
                println("Memeriksa keaslian lagu ...");
                userManager->addDownloadedSong(*user, judul);
            }
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 8) {
            println("------------------------------------");
            println("          Verifikasi Lagu           ");
            println("------------------------------------");
            println("Masukkan judul lagu pada direktori MyDownload yang ingin diverifikasi : ");
            std::string judul;
            std::getline(std::cin, judul);
            if (_SongList.isHashExist(judul)) {
                println("Lagu terverifikasi orisinil.");
            } else {
                println("Lagu tidak terverifikasi orisinil.");
            }
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 9) {
            println("Keluar..");
            getch();
            system("cls");
            break;

        } else {
            println("Pilihan tidak tersedia");
            getch();
            system("cls");
        }
    }
}