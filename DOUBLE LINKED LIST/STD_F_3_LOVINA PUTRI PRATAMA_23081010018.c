#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
    struct node *prev;  // Tambahkan pointer ke node sebelumnya
};
typedef struct node node;

void tambahAwal(node **head);
void tambahAkhir(node **head);
void tambahData(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head, int nilai);
void hapusAkhir(node **head);
void cariData(node *head, int nilai);
void tranverse(node *head);
void tranverseReverse(node *head);  // Traversal mundur
int hitungJumlahNode(node *head);
int jumlahTotalData(node *head);
void freeList(node **head);

//========================================================

int main() {
    node *head;
    char pilih;
    int nilai;

    head = NULL;
    do {
        system("cls");
        printf("Input pilihan\n");
        printf("0. Cetak isi list\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir list\n");
        printf("4. Hapus data di awal list\n");
        printf("5. Hapus data di tengah list\n");
        printf("6. Hapus data di akhir list\n");
        printf("7. Cari data\n");
        printf("8. Hitung jumlah data\n");
        printf("9. Hitung total data\n");
        printf("10. Cetak list terbalik\n");
        printf("INPUT PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf(" %c", &pilih);

        if (pilih == '0') {
            tranverse(head);
            getch();
        } else if (pilih == '1') {
            tambahAwal(&head);
        } else if (pilih == '2') {
            tambahData(&head);
        } else if (pilih == '3') {
            tambahAkhir(&head);
        } else if (pilih == '4') {
            hapusAwal(&head);
        } else if (pilih == '5') {
            printf("Input nilai data yang akan dihapus: ");
            scanf("%d", &nilai);
            hapusTengah(&head, nilai);
            getch();
        } else if (pilih == '6') {
            hapusAkhir(&head);
        } else if (pilih == '7') {
            printf("Input nilai data yang dicari: ");
            scanf("%d", &nilai);
            cariData(head, nilai);
            getch();
        } else if (pilih == '8') {
            printf("Jumlah node: %d\n", hitungJumlahNode(head));
            getch();
        } else if (pilih == '9') {
            printf("Total semua data: %d\n", jumlahTotalData(head));
            getch();
        } else if (pilih == '10') {
            tranverseReverse(head);  // Traversal terbalik
            getch();
        }

    } while (pilih != 'q');

    freeList(&head);
    return 0;
}

//========================================================

void freeList(node **head) {
    node *current = *head;
    node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("Input bilangan: ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        pNew->prev = NULL;  // Pointer prev ke NULL karena ini node pertama
        if (*head != NULL) {
            (*head)->prev = pNew;  // Update prev node awal jika list tidak kosong
        }
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pLast;

    system("cls");
    fflush(stdin);
    printf("Input bilangan: ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            pNew->prev = NULL;
            *head = pNew;
        } else {
            pLast = *head;
            while (pLast->next != NULL) {
                pLast = pLast->next;
            }
            pLast->next = pNew;
            pNew->prev = pLast;  // Pointer prev menunjuk ke node terakhir sebelumnya
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nPosisi penyisipan setelah data bernilai: ");
    scanf("%d", &pos);
    printf("\nBilangan: ");
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pNew->prev = pCur;  // Update pointer prev
        if (pCur->next != NULL) {
            pCur->next->prev = pNew;  // Update prev node berikutnya jika ada
        }
        pCur->next = pNew;
    }
}

//========================================================

void hapusAwal(node **head) {
    system("cls");
    if (*head != NULL) {
        node *temp = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;  // Update prev node baru pertama
        }
        free(temp);
    }
}

//========================================================

void hapusTengah(node **head, int nilai) {
    node *pCur = *head;

    while (pCur != NULL && pCur->data != nilai) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Data tidak ditemukan\n");
    } else {
        if (pCur->prev != NULL) {
            pCur->prev->next = pCur->next;
        } else {
            *head = pCur->next;
        }
        if (pCur->next != NULL) {
            pCur->next->prev = pCur->prev;  // Update prev node berikutnya jika ada
        }
        free(pCur);
    }
}

//========================================================

void hapusAkhir(node **head) {
    node *pCur = *head;

    if (pCur != NULL) {
        while (pCur->next != NULL) {
            pCur = pCur->next;
        }
        if (pCur->prev == NULL) {
            *head = NULL;
        } else {
            pCur->prev->next = NULL;
        }
        free(pCur);
    }
}

//========================================================

void cariData(node *head, int nilai) {
    node *pCur = head;
    int found = 0;

    while (pCur != NULL) {
        if (pCur->data == nilai) {
            printf("Data ditemukan\n");
            found = 1;
            break;
        }
        pCur = pCur->next;
    }
    if (!found) {
        printf("Data tidak ditemukan\n");
    }
}

//========================================================

void tranverse(node *head) {
    system("cls");
    if (head == NULL) {
        printf("List kosong\n");
    } else {
        node *pCur = head;
        printf("NULL <-> ");
        while (pCur != NULL) {
            printf("%d <-> ", pCur->data);
            pCur = pCur->next;
        }
        printf("NULL\n");
    }
}

//========================================================

void tranverseReverse(node *head) {
    system("cls");
    if (head == NULL) {
        printf("List kosong\n");
    } else {
        node *pCur = head;
        while (pCur->next != NULL) {
            pCur = pCur->next;
        }
        printf("NULL <-> ");
        while (pCur != NULL) {
            printf("%d <-> ", pCur->data);
            pCur = pCur->prev;
        }
        printf("NULL\n");
    }
}

//========================================================

int hitungJumlahNode(node *head) {
    int count = 0;
    node *pCur = head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }
    return count;
}

//========================================================

int jumlahTotalData(node *head) {
    int total = 0;
    node *pCur = head;

    while (pCur != NULL) {
        total += pCur->data;
        pCur = pCur->next;
    }
    return total;
}
