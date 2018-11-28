/* File: listrek.h */
/* ADT ListRek linier dengan representasi pointer */
/* Implementasi ListRek linier secara rekursif */

#ifndef _LISTREK_H_
#define _LISTREK_H_

#include "item.h"
#include "boolean.h"

#define TreeNil NULL

/* Definisi Type */
typedef Item treeinfotype;
typedef struct tElmtlist *treeaddress;
typedef struct tElmtlist { 
	treeinfotype info;
	treeaddress next;
} ElmtList;

/* Definisi ListRek : */
/* ListRek kosong : L = TreeNil */
typedef treeaddress ListRek;

/* Deklarasi  nama untuk variabel kerja */ 
/*  	L : ListRek */
/*  	P : treeaddress 	*/
/* Maka penulisan First(L) menjadi L */
/*                P.info menjadi Info(P); P.next menjadi Next(P) */

/* Selektor */
#define Info(P) (P)->info
#define Next(P) (P)->next

/* *** Manajemen Memori *** */
treeaddress Alokasi (treeinfotype X);
/* Mengirimkan treeaddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka treeaddress tidak TreeNil, dan misalnya menghasilkan P, 
  maka Info(P) = X, Next(P) = TreeNil */
/* Jika alokasi gagal, mengirimkan TreeNil */
void Dealokasi (treeaddress P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian treeaddress P */

/* *** Primitif-primitif yang harus direalisasikan *** */

/* Pemeriksaan Kondisi ListRek */
int ListRekIsEmpty(ListRek L);
/* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */
int IsOneElmt(ListRek L);
/* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */

/* *** Selektor *** */
treeinfotype FirstElmt (ListRek L);
/* Mengirimkan elemen pertama sebuah ListRek L yang tidak kosong */
ListRek ListRekTail(ListRek L);
/* Mengirimkan ListRek L tanpa elemen pertamanya, mungkin menjadi ListRek kosong */

/* *** Konstruktor *** */
ListRek Konso(treeinfotype e, ListRek L);
/* Mengirimkan ListRek L dengan tambahan e sebagai elemen pertamanya. 
e dialokasi terlebih dahulu. Jika alokasi gagal, mengirimkan L. */
ListRek KonsB(ListRek L, treeinfotype e);
/* Mengirimkan ListRek L dengan tambahan e sebagai elemen pertamanya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan L */ 

/* *** Operasi Lain *** */
ListRek Copy (ListRek L);
/* Mengirimkan salinan ListRek L (menjadi ListRek baru) */
/* Jika ada alokasi gagal, mengirimkan L */ 
void MCopy (ListRek Lin, ListRek *Lout);
/* I.S. Lin terdefinisi */
/* F.S. Lout berisi salinan dari Lin */
/* Proses : menyalin Lin ke Lout */
ListRek Concat (ListRek L1, ListRek L2);
/* Mengirimkan salinan hasil konkatenasi ListRek L1 dan L2 (menjadi ListRek baru) */
/* Jika ada alokasi gagal, menghasilkan TreeNil */
void MConcat (ListRek L1, ListRek L2, ListRek *LHsl);
/* I.S. L1, L2 terdefinisi */
/* F.S. LHsl adalah hasil melakukan konkatenasi L1 dan L2 dengan cara "disalin" */
/* Proses : Menghasilkan salinan hasil konkatenasi ListRek L1 dan L2 */
void PrintList (ListRek L);
/* I.S. L terdefinisi. */
/* F.S. Setiap elemen ListRek dicetak. */
int NbElmtList (ListRek L);
/* Mengirimkan banyaknya elemen ListRek L, Nol jika L kosong */
boolean Search (ListRek L, treeinfotype X);
/* Mengirim true jika X adalah anggota ListRek, false jika tidak */

#endif