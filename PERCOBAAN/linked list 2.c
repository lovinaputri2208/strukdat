#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
	int data;
    struct node *next;
};
typedef struct node node;

//node *createNode(void);
void tambahAwal(node **head); //Menu 1
void tambahData(node **head); //Menu 2
void tranverse(node *head); //Menu 0
void tambahAkhir(node **head); //Menu 3
void hapusAwal(node **head); //Menu 4
void hapusTengah(node **head, int target); //Menu 5
void hapusAkhir(node **head); //Menu 6
void cariData(node *head, int target); //Menu 7
int hitungJumlahData(node *head); //Menu 8
int jumlahkanData(node *head); //Menu 9
void insertNode(node **head, node *pPre, node *pNew);

//========================================================

int main()
{
  node *head;
  char pilih;

  head = NULL;
  do{
     system("cls");
     printf("Masukkan pilihan\n");
     printf("1. Tambah data di awal\n");
     printf("2. Tambah data di tengah list\n");
     printf("3. Tambah data di akhir linkked list\n");
     printf("4. Hapus data di awal linked list\n");
     printf("5. Hapus data di tengah linked list\n");
     printf("6. Hapus data di akhir linked list\n");
     printf("7. Pencarian data dalam linked list\n");
     printf("8. Menampilkan informasi jumlah data di linked list\n");         
     printf("9. Menampilkan hasil penjumlahan dari semua data di linked list\n");
     printf("0. Cetak isi list\n");
     printf("MASUKKAN PILIHAN (Tekan q untuk keluar) : ");
     fflush(stdin);
     scanf("%c", &pilih);
     if (pilih == '1')
     		tambahAwal(&head);
     else if (pilih == '2')
			tambahData(&head);
     else if (pilih == '3')
            tambahAkhir(&head);
     else if (pilih == '4') {
            hapusAwal(&head);  // Memanggil fungsi hapusAwal
            printf("\nSetelah penghapusan node pertama:\n");
            tranverse(head);  // Tampilkan linked list setelah penghapusan
            getch();  // Tunggu input agar layar tidak langsung kembali
        }
     else if (pilih == '5') {
            int target; // Deklarasi variabel target
            system("cls");
            printf("Masukkan nilai yang akan dihapus: ");
            scanf("%d", &target);  // Ambil nilai target dari pengguna
            hapusTengah(&head, target);  // Panggil fungsi hapusTengah
            printf("\nSetelah penghapusan:\n");
            tranverse(head);  // Tampilkan linked list setelah penghapusan
            getch();  // Tunggu input agar layar tidak langsung kembali
        }
     else if (pilih == '6') {
            hapusAkhir(&head);  // Memanggil fungsi hapusAkhir
            printf("\nSetelah penghapusan node terakhir:\n");
            tranverse(head);  // Tampilkan linked list setelah penghapusan
            getch();  // Tunggu input agar layar tidak langsung kembali
        }
      else if (pilih == '7') {
            int target;
            printf("Masukkan data yang ingin dicari: ");
            scanf("%d", &target);
            cariData(head, target);  // Memanggil fungsi cariData
            getch();  // Tunggu input agar layar tidak langsung kembali
        }
      else if (pilih == '8') {
            int jumlahData = hitungJumlahData(head);  // Hitung jumlah data
            printf("Jumlah data dalam linked list: %d\n", jumlahData);
            getch();  // Tunggu input agar layar tidak langsung kembali
        }
      else if (pilih == '9') {
            int total = jumlahkanData(head);  // Hitung jumlah data
            printf("Hasil penjumlahan semua data dalam linked list: %d\n", total);
            getch();  // Tunggu input agar layar tidak langsung kembali
        }
     else if (pilih == '0'){
     		tranverse(head);
         getch();
        }
  } while (pilih != 'q');
  system ("cls"); //Tambahan Clear System
  return 0;
}

//========================================================

/*node *createNode(void){
  node *ptr;

  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}*/

//========================================================

void tambahAwal(node **head){
  int bil;
  node *pNew;

  system("cls");
  fflush(stdin);
  printf("Masukkan bilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = NULL;
      //add before first logical node or to an empty list
	  pNew -> next = *head;
      *head = pNew;
  }
  else{
      printf("Alokasi memori gagal");
      getch();
  }
}

//========================================================

void tambahData(node **head){
  int pos, bil;
  node *pNew, *pCur;

  system("cls");
  tranverse(*head);
  printf("\nPosisi penyisipan setelah data bernilai : ");
  fflush(stdin);
  scanf("%d", &pos);
  printf("\nBilangan : ");
  fflush(stdin);
  scanf("%d", &bil);

  pCur = *head;
  while (pCur != NULL && pCur -> data != pos) {
    pCur = pCur -> next;
  }

  pNew = (node *)malloc(sizeof(node));

  if (pCur == NULL){
     printf("\nNode tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){
     printf("\nAlokasi memori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = NULL;
     pNew -> next = pCur -> next;
     pCur -> next = pNew;
  }
}

//========================================================

void tranverse(node *head){
   //traverse a linked list
	node *pWalker;

   system("cls");
	pWalker = head;
	while (pWalker != NULL){
   	printf("%d\t", pWalker -> data);
   	pWalker = pWalker -> next;
      printf(" -> ");
	}
   printf("NULL");
}

//========================================================

void tambahAkhir(node **head) { //Menu 3
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    
    // Alokasi memori untuk node baru
    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL; // Karena ini node terakhir, next harus NULL
    } else {
        printf("Alokasi memori gagal");
        getch();
        return;
    }

    // Jika linked list kosong, tambahkan node sebagai head
    if (*head == NULL) {
        *head = pNew;
    } else {
        // Mulai dari head dan cari node terakhir
        pCur = *head;
        while (pCur->next != NULL) {
            pCur = pCur->next;
        }
        // Menyambungkan node terakhir ke node baru
        pCur->next = pNew;
    }
}

//========================================================

void hapusAwal(node **head) { //Menu 4
    // Cek jika linked list kosong
    if (*head == NULL) {
        printf("Linked list kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    // Simpan node yang akan dihapus
    node *pTemp = *head;

    // Ubah head ke node berikutnya
    *head = (*head)->next;

    // Hapus node pertama
    free(pTemp);

    printf("Node pertama berhasil dihapus.\n");
}

//========================================================

void hapusTengah(node **head, int target) { //Menu 5
    node *pCur, *pPrev;

    // Jika linked list kosong
    if (*head == NULL) {
        printf("Linked list kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    // Jika node pertama (head) adalah node yang ingin dihapus
    if ((*head)->data == target) {
        pCur = *head;  // Simpan node yang akan dihapus
        *head = (*head)->next;  // Ubah head ke node berikutnya
        free(pCur);  // Hapus node pertama
        printf("Node dengan nilai %d berhasil dihapus.\n", target);
        return;
    }

    // Mencari node yang memiliki nilai target
    pCur = *head;
    while (pCur != NULL && pCur->data != target) {
        pPrev = pCur;  // Simpan node sebelumnya
        pCur = pCur->next;  // Pindah ke node berikutnya
    }

    // Jika node dengan nilai target tidak ditemukan
    if (pCur == NULL) {
        printf("Node dengan nilai %d tidak ditemukan.\n", target);
        return;
    }

    // Hapus node yang ditemukan
    pPrev->next = pCur->next;  // Hubungkan node sebelumnya dengan node berikutnya
    free(pCur);  // Hapus node yang sesuai
    printf("Node dengan nilai %d berhasil dihapus.\n", target);
}

//========================================================

void hapusAkhir(node **head) { //Menu 6
    // Cek jika linked list kosong
    if (*head == NULL) {
        printf("Linked list kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    // Cek jika linked list hanya memiliki satu node
    if ((*head)->next == NULL) {
        free(*head);  // Hapus node pertama dan satu-satunya
        *head = NULL;  // Atur head menjadi NULL
        printf("Node terakhir berhasil dihapus, linked list sekarang kosong.\n");
        return;
    }

    // Cari node terakhir dan node sebelumnya
    node *pCur = *head;
    node *pPrev = NULL;

    // Iterasi hingga menemukan node terakhir
    while (pCur->next != NULL) {
        pPrev = pCur;  // Simpan node sebelumnya
        pCur = pCur->next;  // Pindah ke node berikutnya
    }

    // Hapus node terakhir
    free(pCur);
    pPrev->next = NULL;  // Node sebelumnya sekarang menjadi node terakhir
    printf("Node terakhir berhasil dihapus.\n");
}

//========================================================

void cariData(node *head, int target) { //Menu 7
    node *pCur = head;
    int posisi = 0;
    int ditemukan = 0;  // Penanda apakah data ditemukan

    // Telusuri seluruh linked list
    while (pCur != NULL) {
        if (pCur->data == target) {
            printf("Data %d ditemukan di posisi ke-%d.\n", target, posisi);
            ditemukan = 1;
        }
        pCur = pCur->next;
        posisi++;
    }

    if (!ditemukan) {
        printf("Data %d tidak ditemukan di dalam linked list.\n", target);
    }
}

//========================================================

int hitungJumlahData(node *head) { //Menu 8
    int count = 0;  // Inisialisasi counter
    node *pCur = head;

    // Telusuri seluruh linked list
    while (pCur != NULL) {
        count++;
        pCur = pCur->next;  // Lanjut ke node berikutnya
    }

    return count;  // Kembalikan jumlah node
}

//========================================================

int jumlahkanData(node *head) { //Menu 9
    int total = 0;  // Inisialisasi total penjumlahan
    node *pCur = head;

    // Telusuri seluruh linked list
    while (pCur != NULL) {
        total += pCur->data;  // Tambahkan nilai data ke total
        pCur = pCur->next;    // Pindah ke node berikutnya
    }

    return total;  // Kembalikan hasil penjumlahan
}

//========================================================

void insertNode(node **head, node *pPre, node *pNew){
    if (pPre == NULL){
       //add before first logical node or to an empty list
	    pNew -> next = *head;
       *head = pNew;
    }
    else {
       //add in the middle or at the end
       pNew -> next = pPre -> next;
       pPre -> next = pNew;
   }
}

//========================================================