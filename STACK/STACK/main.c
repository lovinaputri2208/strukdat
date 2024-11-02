#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

//=======================================================

typedef struct Stack {
    int arr[MAXSIZE];
    int top;
} Stack;

//=======================================================

void inisialisasiStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return (s->top == -1);
}

int isFull(Stack *s) {
    return (s->top == MAXSIZE - 1);
}

//=======================================================

void push(Stack *s, int data) {
    if (!isFull(s)) {
        s->arr[++s->top] = data;
        printf("%d berhasil ditambahkan ke stack\n", data);
    } else {
        printf("Stack Penuh\n");
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        int data = s->arr[s->top--];
        printf("%d berhasil dihapus dari stack\n", data);
        return data;
    } else {
        printf("Stack Kosong\n");
        return -1;
    }
}

int top(Stack *s) {
    return isEmpty(s) ? -1 : s->arr[s->top];
}

int count(Stack *s) {
    return s->top + 1;
}

//=======================================================

void destroy(Stack *s) {
    s->top = -1;
    printf("Stack berhasil dihancurkan\n");
}

int main() {
    Stack s;
    inisialisasiStack(&s);
    int pilihan, data;

    do {
        printf("\nMenu Operasi Stack\n");
        printf("1. Tambah Data (Push)\n");
        printf("2. Hapus Data (Pop)\n");
        printf("3. Lihat data teratas (Top)\n");
        printf("4. Hitung jumlah data (Count)\n");
        printf("5. Hancurkan stack (Destroy)\n");
        printf("6. Keluar\n");
        printf("Masukkan operasi yang diinginkan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Masukkan data yang akan ditambahkan: ");
                scanf("%d", &data);
                push(&s, data);
                break;

            case 2:
                pop(&s);
                break;

            case 3:
                data = top(&s);
                if (data == -1) {
                    printf("Stack kosong\n");
                } else {
                    printf("Data teratas adalah %d\n", data);
                }
                break;

            case 4:
                printf("Jumlah data dalam stack: %d\n", count(&s));
                break;

            case 5:
                destroy(&s);
                break;

            case 6:
                printf("Keluar dari program\n");
                break;

            default:
                printf("Pilihan tidak valid, silahkan coba lagi\n");
        }
    } while (pilihan != 6);
    system("cls");
    return 0;
}
