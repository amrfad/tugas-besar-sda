#include "menu.h"

void print(std::string text) {
    std::cout << text;
}

void println(std::string text) {
    std::cout << text << std::endl;
}

void printMenu(SongList songList) {
    println("------------------------------------");
    println("     login Aplikasi Bank Lagu       ");
    println("------------------------------------");
    print("Masukkan UID : ");
    std::string uid;
    std::cin >> uid;
    print("Masukkan Password : ");
    std::string pass;
    std::cin >> pass;

    system("cls");

    while (true) {
        int pilihan;
        println("------------------------------------");
        println("        Aplikasi Bank Lagu          ");
        println("------------------------------------");
        println("1. Informasi User");
        println("2. Cari Lagu dalam Bank");
        println("3. Registrasikan Lagu ke Bank");
        println("4. Memutar Lagu");
        println("5. Mengunduh Lagu");
        println("6. Verifikasi Lagu");
        println("7. Keluar\n");

        print("Masukkan pilihan anda : ");
        std::cin >> pilihan;
        std::cin.ignore(256, '\n');

        if (pilihan == 1) {
            println("------------------------------------");
            println("          Informasi User            ");
            println("------------------------------------");
            println("User ID : 000023");
            println("Nama : Jake Hashmap");
            println("Lisensi dimiliki : S00034, S00006, S00286");
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
            if (songList.searchSong(judul) != NULL) {
                Song song = songList.searchSong(judul)->song;
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
            println("    Registrasikan Lagu ke Bank      ");
            println("------------------------------------");
            println("Masukkan path dari lagu yang ingin diregistrasikan : ");
            std::string path;
            std::cin >> path;
            println("Masukkan judul lagu: ");
            std::string judul;
            std::cin >> judul;
            println("Lagu berhasil diregistrasikan.");
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 4) {
            println("------------------------------------");
            println("            Putar Lagu              ");
            println("------------------------------------");
            print("Masukkan judul lagu : ");
            Song song;
            std::getline(std::cin, song.title);
            playSong(song);
            system("cls");

        } else if (pilihan == 5) {
            println("------------------------------------");
            println("            Unduh Lagu              ");
            println("------------------------------------");
            print("Masukkan judul lagu : ");
            std::string judul;
            std::getline(std::cin, judul);
            println("Memulai pengunduhan lagu ...");
            downloadSong(judul, songList);
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 6) {
            println("------------------------------------");
            println("          Verifikasi Lagu           ");
            println("------------------------------------");
            println("Masukkan judul lagu pada direktori MyDownload yang ingin diverifikasi : ");
            std::string judul;
            std::getline(std::cin, judul);
            if (songList.isHashExist(judul)) {
                println("Lagu terverifikasi orisinil.");
            } else {
                println("Lagu tidak terverifikasi orisinil.");
            }
            std::string temp;
            std::getline(std::cin, temp);
            system("cls");

        } else if (pilihan == 7) {
            println("Keluar..");
            getch();
            exit(0);
            system("cls");

        } else {
            println("Pilihan tidak tersedia");
            getch();
            system("cls");
        }
    }
}