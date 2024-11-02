#include <stdio.h>

struct makanan{
    int soto;
    int gado;
    int molen;
};
typedef struct makanan mkn;
int main() {

    mkn harga;
    harga.soto = 10000;
    harga.gado = 12000;
    harga.molen = 5000;

    printf("Harga soto adalah Rp %d\n", harga.soto);
    printf("Harga gado adalah Rp %d\n", harga.gado);
    printf("Harga molen adalah Rp %d\n", harga.molen);
}
