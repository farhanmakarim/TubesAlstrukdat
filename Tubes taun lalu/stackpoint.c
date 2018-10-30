#include "stackpoint.h"

//typedef int infotype;
/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
/* Definisi stack S kosong : S.TOP = 0 */
/* Elemen yang dipakai menyimpan 0ai Stack T[1]..T[100] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas 100 */
/* jadi indeksnya antara 1.. 100+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP ber0ai 0 */
{
	Top(*S) = 0;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
	return Top(S) == 0;
}
boolean IsFullStack (Stack S)
/* Mengirim true jika tabel penampung 0ai elemen stack penuh */
{
	return Top(S) == 100;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, POINT P)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
	Top(*S) += 1;
	InfoTop(*S).X = P.X;
	InfoTop(*S).Y = P.Y;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, POINT * P)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah 0ai elemen TOP yang lama, TOP berkurang 1 */
{
	(*P).X = InfoTop(*S).X;
	(*P).Y = InfoTop(*S).Y;
	Top(*S) --;
}
