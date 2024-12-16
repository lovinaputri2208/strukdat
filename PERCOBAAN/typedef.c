#include <stdio.h>

struct mahasiswa {
    char nama [40];
    char npm [15];
    float nilai;
};
typedef struct mahasiswa mhs;
int main (){

    int n,i;
    mhs mhs[10];
    printf("Masukkan berapa data mahasiswa :"); scanf("%d",&n);
    for (i=0;i<n;i++){

        getchar();
        printf("Masukkan nama :"); scanf("%[^\n]", mhs[i].nama);
        printf("Masukkan npm :"); scanf("%s", mhs[i].npm);
        printf("Masukkan nilai :"); scanf("%f", &mhs[i].nilai);
    };
    printf("DATA MAHASISWA :\n");
    for (i=0;i<n;i++){
        printf("Nama : %s\n", mhs[i].nama );
        printf("npm : %s\n", mhs[i].npm );
        printf("nilai : %f\n", mhs[i].nilai );


    }


}
