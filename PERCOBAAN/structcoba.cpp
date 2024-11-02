#include <stdio.h>

// Definisi struct untuk menyimpan informasi buku
struct Buku {
    char judul[100];
    char pengarang[50];
    int tahunTerbit;
};

// Fungsi untuk menampilkan informasi buku
void tampilkanBuku(struct Buku bk) {
    printf("Judul Buku      : %s", bk.judul);
    printf("Pengarang       : %s", bk.pengarang);
    printf("Tahun Terbit    : %d\n", bk.tahunTerbit);
}

int main() {
    // Menyimpan dua data buku
    struct Buku buku1, buku2;

    // Input buku pertama
    printf("Masukkan data buku pertama\n");
    printf("----------------------------\n");
    printf("Judul Buku: ");
    fgets(buku1.judul, sizeof(buku1.judul), stdin);

    printf("Pengarang Buku: ");
    fgets(buku1.pengarang, sizeof(buku1.pengarang), stdin);

    printf("Tahun Terbit: ");
    scanf("%d", &buku1.tahunTerbit);

    getchar();  // Membersihkan input buffer

    // Input buku kedua
    printf("\nMasukkan data buku kedua\n");
    printf("----------------------------\n");
    printf("Judul Buku: ");
    fgets(buku2.judul, sizeof(buku2.judul), stdin);

    printf("Pengarang Buku: ");
    fgets(buku2.pengarang, sizeof(buku2.pengarang), stdin);

    printf("Tahun Terbit: ");
    scanf("%d", &buku2.tahunTerbit);

    // Tampilkan data buku
    printf("\nData Buku yang Telah Dimasukkan:\n");
    printf("================================\n");
    printf("Buku Pertama:\n");
    tampilkanBuku(buku1);

    printf("\nBuku Kedua:\n");
    tampilkanBuku(buku2);

    return 0;
}
