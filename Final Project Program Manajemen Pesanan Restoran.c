#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Pesanan {
    int id;
    char makanan[50];
    char minuman[50];
    char pemesan[50];
    int kasirId;
    int trayId;
    char status[20]; 
    struct Pesanan* next;
} Pesanan;

typedef struct Queue {
    Pesanan* front;
    Pesanan* rear;
    int count;  
} Queue;

typedef struct Stack {
    int trayId;
    struct Stack* next;
    int count;  
} Stack;

typedef struct Kasir {
    int id;
    char nama[50];
    struct Kasir* next;
} Kasir;

int jam = 7; 
int menit = 0;
int pesananCounter = 1; 

void updateWaktu(int durasi) {
    menit += durasi;
    if (menit >= 60) {
        menit -= 60;
        jam++;
    }
    if (jam >= 12 && menit > 0) {
        printf("Restoran sudah tutup!\n");
        getch();
        exit(0);
    }
}

void printWaktu() {
    printf("Waktu sekarang: %02d:%02d\n", jam, menit);
}

Kasir* createKasir() {
    const char* namaKasir[] = {"Fadhil", "Antony", "Riky", "Achmad Zaki", "Lovina"};
    int jumlahKasir = sizeof(namaKasir) / sizeof(namaKasir[0]);

    Kasir* head = NULL;
    Kasir* prev = NULL;

    for (int i = 0; i < jumlahKasir; i++) {
        Kasir* newKasir = (Kasir*)malloc(sizeof(Kasir));
        newKasir->id = i + 1;
        strcpy(newKasir->nama, namaKasir[i]);
        newKasir->next = NULL;

        if (head == NULL) {
            head = newKasir;
            prev = newKasir;
        } else {
            prev->next = newKasir;
            prev = newKasir;
        }
    }

    prev->next = head;
    return head;
}

void push(Stack** stack, int trayId) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    newStack->trayId = trayId;
    newStack->next = *stack;
    
    if (*stack == NULL) {
        newStack->count = 1;  
    } else {
        newStack->count = (*stack)->count + 1;  
    }
    
    *stack = newStack;
    printf("Tray nomor %d ditambahkan ke stack. Total tray: %d\n", trayId, newStack->count);
}

int pop(Stack** stack) {
    if (*stack == NULL) {
        printf("Stack kosong.\n");
        return -1;
    }

    int trayId = (*stack)->trayId;
    Stack* temp = *stack;
    *stack = (*stack)->next;

    if (*stack) {
    	if (temp->count > 1) {
        	(*stack)->count = temp->count - 1;
    	} else {
        	(*stack)->count = 0;
    	}
	}
    
    free(temp);
    return trayId;
}

void enqueue(Queue* queue, char* makanan, char* minuman, char* pemesan, int kasirId, int trayId) {
    Pesanan* newPesanan = (Pesanan*)malloc(sizeof(Pesanan));
    newPesanan->id = pesananCounter++;
    strcpy(newPesanan->makanan, makanan);
    strcpy(newPesanan->minuman, minuman);
    strcpy(newPesanan->pemesan, pemesan);
    newPesanan->kasirId = kasirId;
    newPesanan->trayId = trayId;
    strcpy(newPesanan->status, "Dipesan");
    newPesanan->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newPesanan;
        queue->count = 1;
    } else {
        queue->rear->next = newPesanan;
        queue->rear = newPesanan;
        queue->count++;
    }
}

void printShiftKasir(Kasir* head, Kasir* kasirAktif) {
    Kasir* temp = head;
    if (temp == NULL) {
        printf("Tidak ada kasir.\n");
        return;
    }

    printf("Shift Kasir:\n");
    do {
    if (temp == kasirAktif) {
        printf("ID: %d, Nama: %s (Sedang Melayani)\n", temp->id, temp->nama);
    } else {
        printf("ID: %d, Nama: %s\n", temp->id, temp->nama);
    }
    temp = temp->next;
} while (temp != head);
}

int main() {
    Queue pesananQueue = {NULL, NULL, 0};  
    Stack* piringStack = NULL;
    Kasir* shiftKasir = createKasir(); 
    Kasir* kasirAktif = shiftKasir;

    for (int i = 10; i >= 1; i--) {
        push(&piringStack, i);
    }

    int pilihan;
    do {
        system("cls");
        printf("Program Manajemen Pesanan Restoran\n");
        printf("EAS Struktur Data F081 Kelompok 2\n");
        printf("Restoran buka jam 07.00 - 12.00\n");
        printWaktu();
        printf("Kasir Aktif: %s\n", kasirAktif->nama);
        printf("0. Keluar\n");
        printf("1. Tambah Pesanan ke Antrian\n");
        printf("2. Lihat Shift Kasir\n");
        printf("3. Cek Info Pesanan\n");
        printf("4. Cek Tray Pesanan\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);
        
        system("cls");
        switch (pilihan) {
            case 0: {
            	    printf("Berhasil keluar dari program manajemen pesanan restoran.\n");
                getchar();
                break;
            }
            case 1: {
                char makanan[50], minuman[50], pemesan[50];
                fflush(stdin);
                printf("Masukkan Nama Makanan: ");
				fgets(makanan, sizeof(makanan), stdin);
				makanan[strcspn(makanan, "\n")] = '\0'; 

				printf("Masukkan Nama Minuman: ");
				fgets(minuman, sizeof(minuman), stdin);
				minuman[strcspn(minuman, "\n")] = '\0'; 

				printf("Masukkan Nama Pemesan: ");
				fgets(pemesan, sizeof(pemesan), stdin);
				pemesan[strcspn(pemesan, "\n")] = '\0'; 

                int trayId = pop(&piringStack);
                if (trayId == -1) {
                    printf("Tidak ada tray yang tersedia. Mohon untuk selesaikan pesanan sebelum melakukan pesanan lagi.\n");
                } else {
                    enqueue(&pesananQueue, makanan, minuman, pemesan, kasirAktif->id, trayId);
                    printf("Pesanan berhasil ditambahkan dengan tray ID %d oleh %s.\n", trayId, kasirAktif->nama);
                    updateWaktu(15);
                    if (menit == 0) kasirAktif = kasirAktif->next;
                }
                break;
            }
            case 2: {
                printShiftKasir(shiftKasir, kasirAktif);
                getchar();
                break;
            }
            case 3: {
                if (pesananQueue.front) {
                    Pesanan* temp = pesananQueue.front;
                    printf("Daftar Info Pesanan (Total Pesanan: %d):\n", pesananQueue.count);
                    while (temp) {
                        printf("ID: %d, Makanan: %s, Minuman: %s, Pemesan: %s, Tray: %d, Status: %s\n",
                               temp->id, temp->makanan, temp->minuman, temp->pemesan, temp->trayId, temp->status);
                        temp = temp->next;
                    }
                } else {
                    printf("Tidak ada pesanan dalam antrian.\n");
                }
                getchar();
                break;
            }
            case 4: {
                if (piringStack) {
                    printf("Daftar Tray Tersedia (Total Tray: %d):\n", piringStack->count);
                    Stack* temp = piringStack;
                    while (temp) {
                        printf("Tray ID: %d\n", temp->trayId);
                        temp = temp->next;
                    }
                } else {
                    printf("Tidak ada tray tersedia.\n");
                }
                getchar();
                break;
            }
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
    	}
    	if (pilihan != 0) {
            printf("\nTekan tombol apa saja untuk melanjutkan...");
            getchar();
        }
    } while (pilihan != 0);

    return 0;
}