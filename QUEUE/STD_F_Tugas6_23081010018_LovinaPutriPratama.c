#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define MAX_STR 100

char queue [MAX][MAX_STR];
int depan = -1;
int belakang = -1;
int hitung = 1;

void createQueue() {
    depan = belakang = -1;
    hitung = 1;
    printf("Proses Pembuatan Queue berhasil\n");
}

void enqueue(char *data) {
    if ((belakang + 1) % MAX == depan) {
        printf("Queue sudah penuh\n");
    } else {
        if (depan == -1) depan = 0;
        belakang = (belakang + 1) % MAX;

        char temp[MAX_STR];
        snprintf(temp, sizeof(temp), "%d. %s", hitung++, data);
        strcpy(queue[belakang], temp);
    }
}

void dequeue() {
    if (depan == -1) {
        printf("Queue masih kosong\n");
    } else {
        printf("Dequeue data: %s\n", queue[depan]);
        if (depan == belakang) {
            depan = belakang = -1;
        } else {
            depan = (depan + 1) % MAX;
        }
    }
}

void queueFront() {
    if (depan == -1) {
        printf("Queue masih kosong\n");
    } else {
        printf("Queue yang paling depan adalah: %s\n", queue[depan]);
    }
}

void queueRear() {
    if (belakang == -1) {
        printf("Queue masih kosong\n");
    } else {
        printf("Queue yang paling belakang adalah: %s\n", queue[belakang]);
    }
}

int emptyQueue() {
    return depan == -1;
}

int fullQueue() {
    return (belakang + 1) % MAX == depan;
}

int queueCount() {
    if (depan == -1) {
        return 0;
    } else if (belakang >= depan) {
        return belakang - depan + 1;
    } else {
        return MAX - depan + belakang + 1;
    }
}

void destroyQueue() {
    depan = belakang = -1;
    hitung = 1;
    printf("Queue sudah berhasil direset\n");
}

void tampilkan() {
    if (depan == -1) {
        printf("Queue masih kosong\n");
    } else {
        printf("Queue: \n");
        for (int i = depan; i != belakang; i = (i + 1) % MAX) {
            printf("%s\n", queue[i]);
        }
        printf("%s\n", queue[belakang]);
    }
}

int main() {
    int pilihan;
    char nilai[MAX_STR];

    do {
        printf("\nMenu Queue\n");
        printf("1. Menambahkan Queue\n");
        printf("2. Menghapus Queue\n");
        printf("3. Menampilkan Queue\n");
        printf("4. Menampilkan Queue paling depan\n");
        printf("5. Menampilkan Queue paling belakang\n");
        printf("6. Mengecek Queue kosong\n");
        printf("7. Mengecek Queue penuh\n");
        printf("8. Menghitung total Queue\n");
        printf("9. Mereset Queue\n");
        printf("10. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
            printf("Input data yang ingin ditambahkan: ");
            scanf("%s", nilai);
            enqueue(nilai);
            break;
            
            case 2:
            dequeue();
            break;

            case 3:
            tampilkan();
            break;

            case 4:
            queueFront();
            break;

            case 5:
            queueRear();
            break;

            case 6:
            if (emptyQueue()) {
                printf("Queue masih kosong\n");
            } else {
                printf("Queue tidak kosong\n");
            }
            break;

            case 7:
            if (fullQueue()) {
                printf("Queue sudah penuh\n");
            } else {
                printf("Queue tidak penuh\n");
            }
            break;

            case 8:
            printf("Total Queue yang ada adalah: %d\n", queueCount());
            break;

            case 9:
            destroyQueue();
            break;
            
            case 10:
            printf("Keluar dari program\n");
            break;

            default:
            printf("ERROR\n");
        }
    } while (pilihan != 0);
    return 0;
}