#include <stdio.h>

int main(){
    int score = 50;
    int hp = 100;

    int *ptr_hp = &hp;

    printf("Nama variabel \t Alamat \t Konten\n");
    printf("Score \t\t %p \t %d \n", (void*)&score, score);
    printf("hp \t\t %p \t %d \n", (void*)&hp, hp);
    printf("ptr_hp \t %p \t %p \n", (void*)&ptr_hp, (void*)ptr_hp);
    printf("*ptr_hp \t %p \t %d \n", (void*)&ptr_hp, *ptr_hp);

    *ptr_hp = 95;

    printf("hp \t\t %p \t %d \n", (void*)&hp,hp);
    printf("*ptr_hp \t %p \t %d \n", (void*)&ptr_hp, *ptr_hp);

    return 0;
}
