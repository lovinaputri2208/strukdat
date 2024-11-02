#include <stdio.h>

struct Transportasi {
    char jenis[50];
    char merk[50];
    int tahunPembuatan;
};

int main() {
    struct Transportasi kendaraan;

    printf("Masukkan jenis transportasi (misal: Mobil, Motor, Sepeda): ");
    fgets(kendaraan.jenis, sizeof(kendaraan.jenis), stdin);

    printf("Masukkan merk transportasi: ");
    fgets(kendaraan.merk, sizeof(kendaraan.merk), stdin);

    printf("Masukkan tahun pembuatan: ");
    scanf("%d", &kendaraan.tahunPembuatan);

    printf("\nInformasi Alat Transportasi:\n");
    printf("Jenis         : %s", kendaraan.jenis);
    printf("Merk          : %s", kendaraan.merk);rs
    printf("Tahun Pembuatan: %d\n", kendaraan.tahunPembuatan);

    return 0;
}
