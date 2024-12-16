#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
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
        }

    } while (pilih != 'q');

    freeList(&head);
    return 0;

}

//========================================================

void freeList(node **head) {
    node *current = *head;
    node *next;

    if (*head != NULL) {
        // Bypass circular reference by making last node's next point to NULL
        node *last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        last->next = NULL;

        // Free list as usual
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }

        *head = NULL;
    }
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew, *pLast;

    system("cls");
    fflush(stdin);
    printf("Input bilangan: ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head; // circular reference
        } else {
            pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pNew->next = *head;
            *head = pNew;
            pLast->next = *head; // update last node's next pointer
        }
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

        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head; // circular reference
        } else {
            pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pLast->next = pNew;
            pNew->next = *head; // maintain circular reference
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

    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }

    pCur = *head;
    do {
        if (pCur->data == pos) {
            break;
        }
        pCur = pCur->next;
    } while (pCur != *head);

    if (pCur->data != pos) {
        printf("\nNode tidak ditemukan");
        getch();
        return;
    }

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->next = pCur->next;
    pCur->next = pNew;
}

//========================================================

void hapusAwal(node **head) {
    if (*head == NULL) {
        return;
    }

    node *pCur = *head, *pLast = *head;

    if (pCur->next == *head) { // Only one node
        free(pCur);
        *head = NULL;
    } else {
        while (pLast->next != *head) {
            pLast = pLast->next;
        }
        pLast->next = pCur->next;
        *head = pCur->next;
        free(pCur);
    }
}

//========================================================

void hapusTengah(node **head, int nilai) {
    if (*head == NULL) {
        printf("List kosong\n");
        return;
    }

    node *pCur = *head, *pPrev = NULL;

    do {
        if (pCur->data == nilai) {
            break;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    if (pCur->data != nilai) {
        printf("Data tidak ditemukan\n");
        return;
    }

    if (pPrev == NULL) {
        hapusAwal(head); // Special case for head
    } else {
        pPrev->next = pCur->next;
        free(pCur);
    }
}

//========================================================

void hapusAkhir(node **head) {
    if (*head == NULL) {
        return;
    }

    node *pCur = *head, *pPrev = NULL;

    if (pCur->next == *head) { // Only one node
        free(pCur);
        *head = NULL;
    } else {
        while (pCur->next != *head) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *head;
        free(pCur);
    }
}

//========================================================

void cariData(node *head, int nilai) {
    if (head == NULL) {
        printf("List kosong\n");
        return;
    }

    node *pCur = head;
    int found = 0;

    do {
        if (pCur->data == nilai) {
            printf("Data ditemukan\n");
            found = 1;
            break;
        }
        pCur = pCur->next;
    } while (pCur != head);

    if (!found) {
        printf("Data tidak ditemukan\n");
    }
}

//========================================================

void tranverse(node *head) {
    if (head == NULL) {
        printf("List kosong\n");
    } else {
        node *pCur = head;
        do {
            printf("%d -> ", pCur->data);
            pCur = pCur->next;
        } while (pCur != head);
        printf("%d (kembali ke awal)\n", head->data); // Modifikasi ini untuk kembali ke awal
    }
}

//========================================================

int hitungJumlahNode(node *head) {
    if (head == NULL) {
        return 0;
    }

    int count = 0;
    node *pCur = head;

    do {
        count++;
        pCur = pCur->next;
    } while (pCur != head);

    return count;
}

//========================================================

int jumlahTotalData(node *head) {
    if (head == NULL) {
        return 0;
    }

    int total = 0;
    node *pCur = head;

    do {
        total += pCur->data;
        pCur = pCur->next;
    } while (pCur != head);

    return total;
}
