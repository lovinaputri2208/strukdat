#include <stdio.h>

// Definisi struct
struct Mahasiswa {
    int id;
    char nama[50];
    float ipk;
};

int main() {
    // Deklarasi variabel struct
    struct Mahasiswa mhs;

    // Input data mahasiswa
    printf("Masukkan ID Mahasiswa: ");
    scanf("%d", &mhs.id);

    printf("Masukkan Nama Mahasiswa: ");
    scanf("%s", mhs.nama);

    printf("Masukkan IPK Mahasiswa: ");
    scanf("%f", &mhs.ipk);

    // Output data mahasiswa
    printf("\nData Mahasiswa:\n");
    printf("ID: %d\n", mhs.id);
    printf("Nama: %s\n", mhs.nama);
    printf("IPK: %.2f\n", mhs.ipk);

    return 0;
}
