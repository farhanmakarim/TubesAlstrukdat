#include <stdio.h>
#include "stackt.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void StackCreateEmpty (Stack *S){
	Top (*S) = Nil;
}
/* I.S. sembarang{} */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas StackMaxEl */
/* jadi indeksnya antara 1.. StackMaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean StackIsEmpty (Stack S){
	return (Top(S) == Nil);
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean StackIsFull (Stack S){
	return (Top(S) == StackMaxEl);
}

/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void StackPush (Stack * S, stackinfotype X){
	if(StackIsEmpty(*S))
	{
		Top(*S) = 1;
	}
	else
	{
		Top(*S)++;
	}
	InfoTop(*S) = X;
}
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void StackPop (Stack * S, stackinfotype* X){
	*X = InfoTop(*S);
	if (Top(*S) == 1){
        StackCreateEmpty(S);
    }
    else{
        Top(*S) -= 1;
    }
}
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */