#include <stdio.h>
#include <string.h>

// Struct untuk menyimpan informasi buku
struct Buku {
    char judul[100];
    char pengarang[50];
    int tahunTerbit;
};

// Fungsi untuk menambahkan buku ke file
void tambahBuku() {
    struct Buku buku;
    FILE *file = fopen("buku.dat", "ab"); // Menambahkan data ke file

    printf("Masukkan Judul Buku: ");
    getchar(); // Menghindari masalah dengan input gobuffer
    fgets(buku.judul, sizeof(buku.judul), stdin);

    printf("Masukkan Pengarang Buku: ");
    fgets(buku.pengarang, sizeof(buku.pengarang), stdin);

    printf("Masukkan Tahun Terbit: ");
    scanf("%d", &buku.tahunTerbit);

    fwrite(&buku, sizeof(struct Buku), 1, file); // Simpan data ke file
    fclose(file);

    printf("Buku berhasil ditambahkan!\n");
}

// Fungsi untuk menampilkan semua buku yang ada di file
void tampilkanBuku() {
    struct Buku buku;
    FILE *file = fopen("buku.dat", "rb"); // Membaca file

    if (file == NULL) {
        printf("Belum ada data buku yang tersimpan.\n");
        return;
    }

    printf("\nDaftar Buku:\n");

    while (fread(&buku, sizeof(struct Buku), 1, file)) {
        printf("Judul      : %s", buku.judul);
        printf("Pengarang  : %s", buku.pengarang);
        printf("Tahun      : %d\n", buku.tahunTerbit);
        printf("---------------------\n");
    }

    fclose(file);
}

// Fungsi utama dengan menu sederhana
int main() {
    int pilihan;

    do {
        printf("\n=== Menu Manajemen Buku ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Lihat Semua Buku\n");
        printf("3. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2:
                tampilkanBuku();
                break;
            case 3:
                printf("Terima kasih, program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);

    return 0;
}
