#include <stdio.h>

int main() {
    int angka = 10;      // Deklarasi variabel
    int *penunjuk;       // Deklarasi pointer

    penunjuk = &angka;   // Pointer menyimpan alamat memori dari variabel 'angka'

    // Output nilai dan alamat memori dari variabel 'angka'
    printf("Nilai dari variabel angka: %d\n", angka);
    printf("Alamat memori dari variabel angka: %p\n", &angka);

    // Output nilai dari pointer dan nilai yang ditunjuk oleh pointer
    printf("Alamat yang disimpan dalam pointer: %p\n", penunjuk);
    printf("Nilai yang ditunjuk oleh pointer: %d\n", *penunjuk);

    // Mengubah nilai variabel 'angka' melalui pointer
    *penunjuk = 20;

    // Output nilai baru dari variabel 'angka'
    printf("Nilai baru dari variabel angka: %d\n", angka);

    return 0;
}
