#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_DATA 20

//=============================================================

typedef struct Node {
    char nama[50];
    char jenisKelamin;
    struct Node* next;
} Node;

Node* head = NULL;
int count = 0;

Node* createNode(char* nama, char jenisKelamin) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nama, nama);
    newNode->jenisKelamin = jenisKelamin;
    newNode->next = NULL;
    return newNode;
}

//=============================================================

void tambahDataAwal(char* nama, char jenisKelamin) {
    if (count >= MAX_DATA) {
        printf("Sudah memenuhi kapasitas\n");
        return;
    }

    Node* newNode = createNode(nama, jenisKelamin);

    if (strcmp(nama, "Irsyad") == 0) {
        Node* newNodeArsyad = createNode("Arsyad", jenisKelamin);
        newNode->next = newNodeArsyad;
        newNodeArsyad->next = head ? head : newNodeArsyad; // Mengatur next ke head atau ke newNodeArsyad itu sendiri jika head NULL
        head = newNode;
    } else if (strcmp(nama, "Cindy") == 0) {
        if (jenisKelamin == 'P') {
            Node* newNodeCindy = createNode("Cindy", jenisKelamin);
            newNodeCindy->next = head ? head : newNodeCindy; // Mengatur next ke head atau ke newNodeCindy itu sendiri jika head NULL
            head = newNodeCindy;
        } else {
            printf("Cindy hanya dapat ditambahkan jika jenis kelamin perempuan\n");
            return;
        }
    } else {
        if (head == NULL) {
            head = newNode;
            head->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }
    count += (strcmp(nama, "Irsyad") == 0) ? 2 : 1; // Tambah 2 jika Irsyad ditambahkan, jika tidak tambah 1
    printf("Atas nama %s (%c) berhasil ditambahkan di awal\n", nama, jenisKelamin);
}

//=============================================================

void tambahDataAkhir(char* nama, char jenisKelamin) {
    if (count >= MAX_DATA) {
        printf("Sudah memenuhi kapasitas\n");
        return;
    }

    Node* newNode = createNode(nama, jenisKelamin);

    if (strcmp(nama, "Irsyad") == 0) {
        Node* newNodeArsyad = createNode("Arsyad", jenisKelamin);
        if (head == NULL) {
            head = newNode;
            head->next = newNodeArsyad;
            newNodeArsyad->next = head; // Lingkaran
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = newNodeArsyad;
            newNodeArsyad->next = head; // Lingkaran
        }
        count += 2; // Tambah 2 jika Irsyad ditambahkan
    } else if (strcmp(nama, "Cindy") == 0) {
        if (jenisKelamin == 'P') {
            Node* newNodeCindy = createNode("Cindy", jenisKelamin);
            if (head == NULL) {
                head = newNodeCindy;
                head->next = head; // Lingkaran
            } else {
                Node* temp = head;
                while (temp->next != head) {
                    temp = temp->next;
                }
                temp->next = newNodeCindy;
                newNodeCindy->next = head; // Lingkaran
            }
            count++;
        } else {
            printf("Cindy hanya dapat ditambahkan jika jenis kelamin perempuan\n");
            return;
        }
    } else {
        if (head == NULL) {
            head = newNode;
            head->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        count++;
    }
    printf("Atas nama %s (%c) berhasil ditambahkan di akhir\n", nama, jenisKelamin);
}

//=============================================================

void tambahDataTengah(char* nama, char jenisKelamin, char* namaPos) {
    if (count >= MAX_DATA) {
        printf("Sudah memenuhi kapasitas\n");
        return;
    }

    Node* pCur = head;
    while (pCur != NULL && strcmp(pCur->nama, namaPos) != 0) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Nama %s tidak ditemukan di dalam list\n", namaPos);
        return;
    }

    Node* newNode = createNode(nama, jenisKelamin);
    if (strcmp(nama, "Irsyad") == 0) {
        Node* newNodeArsyad = createNode("Arsyad", jenisKelamin);
        newNode->next = pCur->next;
        pCur->next = newNode;
        newNodeArsyad->next = newNode->next;
        newNode->next = newNodeArsyad;
        count += 2;
    } else if (strcmp(nama, "Cindy") == 0) {
        if (jenisKelamin == 'P') {
            Node* newNodeCindy = createNode("Cindy", jenisKelamin);
            newNodeCindy->next = pCur->next;
            pCur->next = newNodeCindy;
            count++;
        } else {
            printf("Cindy hanya dapat disisipkan jika jenis kelamin perempuan\n");
            return;
        }
    } else {
        newNode->next = pCur->next;
        pCur->next = newNode;
        count++;
    }
    printf("Atas nama %s (%c) berhasil disisipkan setelah %s (%c)\n", nama, jenisKelamin, namaPos, pCur->jenisKelamin);
}

//=============================================================

void hapusData(char* nama) {
    if (head == NULL) {
        printf("Belum ada nama di dalam urutan\n");
        return;
    }

    Node *temp = head, *prev = NULL;
    if (strcmp(temp->nama, nama) == 0) {
        char delJenisKelamin = temp->jenisKelamin;
        if (temp->next == head) {
            free(temp);
            head = NULL;
        } else {
            while (temp->next != head) {
                temp = temp->next;
            }
            Node* delNode = head;
            temp->next = head->next;
            head = head->next;
            free(delNode);
        }
        count--;
        printf("Atas nama %s (%c) berhasil dihapus\n", nama, delJenisKelamin);
        return;
    }

    temp = head;
    do {
        prev = temp;
        temp = temp->next;
    } while (temp != head && strcmp(temp->nama, nama) != 0);

    if (strcmp(temp->nama, nama) == 0) {
        prev->next = temp->next;
        char delJenisKelamin = temp->jenisKelamin;
        free(temp);
        count--;
        printf("Atas nama %s (%c) berhasil dihapus\n", nama, delJenisKelamin);
    } else {
        printf("Atas nama %s tidak ditemukan\n", nama);
    }
}

//=============================================================

void tranverse(Node *head) {
    if (head == NULL) {
        printf("Belum ada nama di dalam urutan\n");
        return;
    }

    Node *pWalker = head;

    do {
        printf("%s (%c) -> ", pWalker->nama, pWalker->jenisKelamin);
        pWalker = pWalker->next;
    } while (pWalker != head);
    printf("%s (%c)\n", head->nama, head->jenisKelamin);
}

//=============================================================

void tampilkanBerdasarkanJenisKelamin(char jenisKelamin) {
    if (head == NULL) {
        printf("Belum ada nama di dalam urutan\n");
        return;
    }

    Node* temp = head;
    int found = 0;
    do {
        if (temp->jenisKelamin == jenisKelamin) {
            printf("%s (%c) -> ", temp->nama, temp->jenisKelamin);
            found = 1;
        }
        temp = temp->next;
    } while (temp != head);

    if (found) {
        printf("%s (%c)\n", head->nama, head->jenisKelamin);
    } else {
        printf("Tidak ada data dengan jenis kelamin %c\n", jenisKelamin);
    }
}

//=============================================================

int main() {
    int opsi;
    char nama[50], jenisKelamin, delName[50];

    do {
        printf("\nOpsi untuk camping bersama teman-teman\n");
        printf("1. Masukkan Nama\n");
        printf("2. Hapus Nama\n");
        printf("3. Tampilkan Urutan\n");
        printf("4. Tampilkan Urutan Berdasarkan Jenis Kelamin\n");
        printf("5. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &opsi);

        switch (opsi) {
            case 1:
                if (count < MAX_DATA) {
                    int opsiTambah;
                    printf("1. Menambahkan nama di awal\n");
                    printf("2. Menambahkan nama di tengah\n");
                    printf("3. Menambahkan nama di akhir\n");
                    printf("Masukkan opsi untuk menambahkan pilihanmu: ");
                    scanf("%d", &opsiTambah);

                    printf("Masukkan nama: ");
                    scanf("%s", nama);
                    printf("Masukkan jenis kelamin (L/P): ");
                    scanf(" %c", &jenisKelamin);

                    if (opsiTambah == 1) {
                        tambahDataAwal(nama, jenisKelamin);
                    } else if (opsiTambah == 2) {
                        char namaPos[50];
                        printf("Masukkan nama setelah data akan disisipkan: ");
                        scanf("%s", namaPos);
                        tambahDataTengah(nama, jenisKelamin, namaPos);
                    } else if (opsiTambah == 3) {
                        tambahDataAkhir(nama, jenisKelamin);
                    } else {
                        printf("Opsi tidak valid\n");
                    }
                } else {
                    printf("Sudah memenuhi kapasitas\n");
                }
                break;
            case 2:
                printf("Masukkan nama yang ingin dihapus: ");
                scanf("%s", delName);
                hapusData(delName);
                break;
            case 3:
                tranverse(head);
                break;
            case 4:
                printf("Masukkan jenis kelamin yang ingin ditampilkan (L/P): ");
                scanf(" %c", &jenisKelamin);
                tampilkanBerdasarkanJenisKelamin(jenisKelamin);
                break;
            case 5:
                printf("Keluar\n");
                break;
            default:
                printf("ERROR. Ulangi program\n");
        }

        getch();

    } while (opsi != 5);

    return 0;
}
