#ifndef queuepoint_H
#define queuepoint_H

#include "point.h"

typedef struct {
	POINT *T;   /* tabel penyimpan elemen */
    int HEADPoint;  /* alamat penghapusan */
   	int TAILPoint;  /* alamat penambahan */
    int MaxElPoint;     /* Max elemen queue */
} QueuePoint;

#define HeadPoint(Q) (Q).HEADPoint
#define TailPoint(Q) (Q).TAILPoint
#define InfoHeadPoint(Q) (Q).T[(Q).HEADPoint]
#define InfoTailPoint(Q) (Q).T[(Q).TAILPoint]
#define MaxElPoint(Q) (Q).MaxElPoint

boolean IsEmptyQueuePoint (QueuePoint Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFullQueuePoint (QueuePoint Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmtQueuePoint (QueuePoint Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateEmptyQueuePoint (QueuePoint * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasiQueuePoint (QueuePoint *Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void AddPoint (QueuePoint *Q, POINT X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void DelPoint (QueuePoint *Q, POINT *X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */

#endif