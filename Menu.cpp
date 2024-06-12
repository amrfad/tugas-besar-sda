#include "menu.h"

void print(std::string text) {
    std::cout << text;
}

void println(std::string text) {
    std::cout << text << std::endl;
}

void printMenu(User* user) {
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
            // println("1. Sorting berdasarkan judul");
            // println("2. Sorting berdasarkan penyanyi");
            // println("3. Sorting berdasarkan genre");
            // println("4. Sorting berdasarkan durasi");
            // println("5. Kembali");
            // print("Masukkan pilihan anda : ");

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
            downloadSong(judul);
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