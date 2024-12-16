#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 20

//========================================================

struct node {
    char nama[50];
    char jenis_kelamin;
    struct node *next;
};
typedef struct node node;

void tambahAwal(node **head, char *nama, char jenis_kelamin);
void tambahAkhir(node **head, char *nama, char jenis_kelamin);
void tambahMahasiswa(node **headL, node **headP);
void tranverse(node *head);
void pisahkanLingkaran(node *headL, node *headP);
void freeList(node **head);
void cindyRule(node **headP);
void tambahKembar(node **headL, node **headP, char *nama1, char *nama2);
void keluarMahasiswa(node **head, char *nama);
int countStudents(node *head);

//========================================================

int main() {
    node *headL = NULL, *headP = NULL;
    char pilih;

    do {
        system("cls");
        printf("Input pilihan\n");
        printf("1. Tambah mahasiswa\n");
        printf("2. Cetak lingkaran laki-laki\n");
        printf("3. Cetak lingkaran perempuan\n");
        printf("4. Pisahkan lingkaran laki-laki dan perempuan\n");
        printf("5. Aturan Cindy\n");
        printf("6. Tambah kembar Arsyad dan Irsyad\n");
        printf("7. Keluar dari lingkaran\n");
        printf("INPUT PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);
        scanf(" %c", &pilih);

        if (pilih == '1') {
            tambahMahasiswa(&headL, &headP);
        } else if (pilih == '2') {
            tranverse(headL);
            getch();
        } else if (pilih == '3') {
            tranverse(headP);
            getch();
        } else if (pilih == '4') {
            pisahkanLingkaran(headL, headP);
            getch();
        } else if (pilih == '5') {
            cindyRule(&headP);
            getch();
        } else if (pilih == '6') {
            tambahKembar(&headL, &headL, "Arsyad", "Irsyad");
            getch();
        } else if (pilih == '7') {
            char nama[50];
            printf("Input nama mahasiswa yang ingin keluar: ");
            fflush(stdin);
            scanf("%s", nama);
            keluarMahasiswa(&headL, nama);
            keluarMahasiswa(&headP, nama);
            getch();
        }

    } while (pilih != 'q');

    freeList(&headL);
    freeList(&headP);
    return 0;
}

//========================================================

void freeList(node **head) {
    node *current = *head;
    node *next;

    if (*head != NULL) {
        node *last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        last->next = NULL;

        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }

        *head = NULL;
    }
}

//========================================================

void tambahAwal(node **head, char *nama, char jenis_kelamin) {
    node *pNew, *pLast;

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        strcpy(pNew->nama, nama);
        pNew->jenis_kelamin = jenis_kelamin;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head;
        } else {
            pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pNew->next = *head;
            *head = pNew;
            pLast->next = *head;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahAkhir(node **head, char *nama, char jenis_kelamin) {
    node *pNew, *pLast;

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        strcpy(pNew->nama, nama);
        pNew->jenis_kelamin = jenis_kelamin;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head;
        } else {
            pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pLast->next = pNew;
            pNew->next = *head;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

int countStudents(node *head) {
    if (head == NULL) return 0;

    int count = 0;
    node *current = head;

    do {
        count++;
        current = current->next;
    } while (current != head);

    return count;
}

//========================================================

void tambahMahasiswa(node **headL, node **headP) {
    char nama[50], jenis_kelamin;

    system("cls");
    fflush(stdin);
    printf("Input nama mahasiswa: ");
    scanf("%s", nama);
    printf("Input jenis kelamin (L/P): ");
    scanf(" %c", &jenis_kelamin);
     if (posisi == 1) {
            tambahAwal(headL, nama1, 'L');
            tambahAwal(headP, nama2, 'P');
        } else if (posisi == 2) {
            tambahTengah(headL, nama1, 'L');
            tambahTengah(headP, nama2, 'P');
        } else {
            tambahAkhir(headL, nama1, 'L');
            tambahAkhir(headP, nama2, 'P');
        }
    if (jenis_kelamin == 'L') {
        if (countStudents(*headL) < MAX_STUDENTS) {
            tambahAkhir(headL, nama, jenis_kelamin);
        } else {
            printf("Batas maksimum mahasiswa laki-laki sudah tercapai.\n");
            getch();
        }
    } else if (jenis_kelamin == 'P') {
        if (countStudents(*headP) < MAX_STUDENTS) {
            tambahAkhir(headP, nama, jenis_kelamin);
        } else {
            printf("Batas maksimum mahasiswa perempuan sudah tercapai.\n");
            getch();
        }
    } else {
        printf("Input tidak valid.\n");
    }
}

//========================================================

void tranverse(node *head) {
    if (head == NULL) {
        printf("Lingkaran kosong\n");
    } else {
        node *pCur = head;
        do {
            printf("%s (%c) -> ", pCur->nama, pCur->jenis_kelamin);
            pCur = pCur->next;
        } while (pCur != head);
        printf("%s (%c) (kembali ke awal)\n", head->nama, head->jenis_kelamin);
    }
}

//========================================================

void pisahkanLingkaran(node *headL, node *headP) {
    printf("Lingkaran Laki-laki:\n");
    tranverse(headL);
    printf("\nLingkaran Perempuan:\n");
    tranverse(headP);
}

//========================================================

void cindyRule(node **headP) {
    node *pCur = *headP;
    if (pCur == NULL) {
        printf("Lingkaran kosong, tidak ada mahasiswi.\n");
        return;
    }

    int found = 0;
    do {
        if (strcmp(pCur->nama, "Cindy") == 0) {
            found = 1;
            break;
        }
        pCur = pCur->next;
    } while (pCur != *headP);

    if (found) {
        printf("Cindy hanya bisa bergandengan dengan mahasiswi lain.\n");
    } else {
        printf("Cindy tidak ditemukan dalam lingkaran perempuan.\n");
    }
}

//========================================================

void tambahKembar(node **headL, node **headP, char *nama1, char *nama2) {
    if (countStudents(*headL) < MAX_STUDENTS) {
         if (posisi == 1) {
            tambahAwal(headL, nama1, 'L');
            tambahAwal(headL, nama2, 'L');
        } else if (posisi == 2) {
            tambahTengah(headL, nama1, 'L');
            tambahTengah(headL, nama2, 'L');
        } else {
            tambahAkhir(headL, nama1, 'L');
            tambahAkhir(headL, nama2, 'L');
        }
    } else {
        printf("Batas maksimum mahasiswa laki-laki sudah tercapai.\n");
        return;
    }

    if (countStudents(*headP) < MAX_STUDENTS) {
        tambahAkhir(headP, nama2, 'P');
    } else {
        printf("Batas maksimum mahasiswa perempuan sudah tercapai.\n");
        return;
    }

    printf("%s dan %s (kembar) berhasil ditambahkan ke lingkaran.\n", nama1, nama2);
}

//========================================================

void keluarMahasiswa(node **head, char *nama) {
    if (*head == NULL) {
        printf("Lingkaran kosong, tidak ada mahasiswa untuk dikeluarkan.\n");
        return;
    }

    node *current = *head;
    node *prev = NULL;

    do {
        if (strcmp(current->nama, nama) == 0) {
            if (prev == NULL) {
                node *last = *head;
                while (last->next != *head) {
                    last = last->next;
                }
                if (current->next == *head) {
                    free(current);
                    *head = NULL;
                } else {
                    last->next = current->next;
                    *head = current->next;
                    free(current);
                }
            } else {
                prev->next = current->next;
                free(current);
            }
            printf("%s berhasil dikeluarkan dari lingkaran.\n", nama);
            return;
        }
        prev = current;
        current = current->next;
    } while (current != *head);

    printf("Mahasiswa dengan nama %s tidak ditemukan.\n", nama);
}
