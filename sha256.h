#ifndef SHA256_H
#define SHA256_H

#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

extern const int a,b,c,d,e,f,g,h;

// Inisialisasi nilai konstanta SHA-256
extern const uint32_t K[64];

// Inisialisasi nilai hash awal SHA-256
extern uint32_t H[8];

// Melakukan rotasi kanan bit untuk nilai x sebanyak n posisi.
uint32_t right_rotate(uint32_t x, uint32_t n);

// Fungsi little_sigma_0, little_sigma_1, big_sigma_0, big_sigma_1: Melakukan operasi bitwise yang diperlukan untuk SHA-256.
uint32_t little_sigma_0(uint32_t x);
uint32_t little_sigma_1(uint32_t x);
uint32_t big_sigma_0(uint32_t x);
uint32_t big_sigma_1(uint32_t x);

// Membentuk array W dari blok input block, dengan 16 kata pertama diambil langsung dari blok dan 48 kata sisanya dihitung dengan fungsi sigma kecil.
void message_schedule(uint32_t (&W)[64], uint8_t (&block)[64]);

// Mengembalikan salah satu dari dua input berdasarkan bit-bit input pertama.
uint32_t choice(uint32_t x, uint32_t y, uint32_t z);

// Mengembalikan nilai mayoritas dari tiga input.
uint32_t majority(uint32_t x, uint32_t y, uint32_t z);

// Melakukan satu putaran komputasi SHA-256, memperbarui register H dengan konstanta putaran dan kata jadwal.
void round(uint32_t (&H)[8], uint32_t round_constant, uint32_t schedule_word);

// Mengkompres blok 512-bit input dengan memanggil fungsi message_schedule dan round.
void compress_block(uint32_t (&H)[8], uint8_t (&block)[64]);

// Fungsi utama untuk menghitung hash dari blok data
string sha256(uint8_t* data, size_t length);
string sha256(string m);

#endif