#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Program Manajemen Pesanan Restoran
// Kelompok 2, Beranggotakan:
// ACHMAD FATHONI (23081010017)
// LOVINA PUTRI PRATAMA (23081010018)
// RIKY HERMAWAN (23081010021)
// ACHMAD ZAKI AL AKBAR (23081010022)
// FADHIL DJIBRAN (23081010030)
// Evaluasi Akhir Semester
// Struktur Data F081

//========================================================

// Deklarasi Struct

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

//========================================================

// Deklarasi Variabel Global

int jam = 7; // Restoran mulai dari Jam 07.00
int menit = 0;
int pesananCounter = 1;

//========================================================

// Deklarasi Judul Fungsi

void updateWaktu(int durasi);
void printWaktu();
void enqueue(Queue* queue, char* makanan, char* minuman, char* pemesan, int kasirId, int trayId);
Pesanan* dequeue(Queue* queue);
void push(Stack** stack, int trayId);
int pop(Stack** stack);
Kasir* createKasir();
void printShiftKasir(Kasir* head, Kasir* kasirAktif);

//========================================================

// Fungsi Main

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
        printf("Menu:\n");
        printf("1. Tambah Pesanan ke Antrian\n");
        printf("2. Sajikan Pesanan\n");
        printf("3. Selesaikan Pesanan\n");
        printf("4. Lihat Shift Kasir\n");
        printf("5. Cek Info Pesanan\n");
        printf("6. Cek Tray Pesanan\n");
        printf("7. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        system("cls");
        switch (pilihan) {
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
    			if (pesananQueue.front) {
        			Pesanan* temp = pesananQueue.front;
        			printf("Daftar Pesanan yang Dapat Disajikan:\n");
        			while (temp) {
            			if (strcmp(temp->status, "Dipesan") == 0) {
                			printf("ID: %d, Makanan: %s, Minuman: %s, Pemesan: %s, Tray: %d, Status: %s\n",
                    		temp->id, temp->makanan, temp->minuman, temp->pemesan, temp->trayId, temp->status);
            			}
            			temp = temp->next;
        			}
        			printf("Masukkan ID pesanan yang ingin disajikan (Tekan 0 untuk batal): ");
        			int idSajikan;
        			scanf("%d", &idSajikan);

        			if (idSajikan == 0) {
            			printf("Penyajian dibatalkan.\n");
            			getchar();
        			} else {
            			temp = pesananQueue.front;
            			while (temp) {
                			if (temp->id == idSajikan && strcmp(temp->status, "Dipesan") == 0) {
                    		strcpy(temp->status, "Disajikan");
                    		system("cls");
                    	printf("Pesanan ID %d telah disajikan.\n", temp->id);
                    	getchar();
                    	break;
						}
                		temp = temp->next;
            			}
            			if (!temp) {
            				system("cls");
                			printf("Pesanan dengan ID %d tidak ditemukan atau sudah disajikan.\n", idSajikan);
                			getchar();
            			}
        			}
    			} else {
    				system("cls");
        			printf("Antrian kosong. Tidak ada pesanan yang dapat disajikan.\n");
				}
    			break;
			}

			case 3: {
    			if (pesananQueue.front) {
        			Pesanan* temp = pesananQueue.front;
        			printf("Daftar Pesanan yang Dapat Diselesaikan:\n");
        			while (temp) {
            			if (strcmp(temp->status, "Disajikan") == 0) {
                			printf("ID: %d, Makanan: %s, Minuman: %s, Pemesan: %s, Tray: %d, Status: %s\n",
                       		temp->id, temp->makanan, temp->minuman, temp->pemesan, temp->trayId, temp->status);
            			}
            		temp = temp->next;
        			}

        			printf("Masukkan ID pesanan yang ingin diselesaikan (0 untuk batal): ");
        			int idSelesaikan;
       				scanf("%d", &idSelesaikan);

					if (idSelesaikan == 0) {
        				system("cls");
            			printf("Penyelesaian dibatalkan.\n");
            			getchar();
        			} else {
            			Pesanan* prev = NULL;
            			temp = pesananQueue.front;
            			while (temp) {
                			if (temp->id == idSelesaikan && strcmp(temp->status, "Disajikan") == 0) {
                    			if (prev) {
                        			prev->next = temp->next;
                    			} else {
                        			pesananQueue.front = temp->next;
                    			}
                    			if (temp == pesananQueue.rear) {
                        			pesananQueue.rear = prev;
                    			}
                    			push(&piringStack, temp->trayId);
                    			system("cls");
                    			printf("Pesanan ID %d selesai dan tray ID %d dikembalikan ke stack.\n", temp->id, temp->trayId);
                   				free(temp);
                    			getchar();
                    			break;
                			}
                			prev = temp;
                			temp = temp->next;
            			}
            			if (!temp) {
            				system("cls");
                			printf("Pesanan dengan ID %d tidak ditemukan atau belum disajikan.\n", idSelesaikan);
                			getchar();
            			}
        			}
    			} else {
        			printf("Antrian kosong. Tidak ada pesanan yang dapat diselesaikan.\n");
        			getchar();
    			}
    			break;
			}

            case 4: {
                printShiftKasir(shiftKasir, kasirAktif);
                getchar();
                break;
            }

            case 5: {
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

            case 6: {
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

            case 7:
                printf("Berhasil keluar dari program manajemen pesanan restoran.\n");
                getchar();
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
        if (pilihan != 7) {
            printf("\nTekan tombol apa saja untuk melanjutkan...");
            getchar();
        }
    } while (pilihan != 7);

    return 0;
}

// Deklarasi Isi Fungsi

//========================================================

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

//========================================================

void printWaktu() {
    printf("Waktu sekarang: %02d:%02d\n", jam, menit);
}

//========================================================

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

//========================================================

Pesanan* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        printf("Antrian kosong.\n");
        return NULL;
    }

    Pesanan* temp = queue->front;
    queue->front = queue->front->next;
    queue->count--;

    if (queue->front == NULL)
        queue->rear = NULL;

    return temp;
}

//========================================================

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

//========================================================

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

//========================================================

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

//========================================================

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

//========================================================
