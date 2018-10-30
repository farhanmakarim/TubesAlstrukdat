#include "queuepoint.h"

boolean IsEmptyQueuePoint (QueuePoint Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
	return ((HeadPoint(Q) == 0) && (TailPoint(Q) == 0));
}

boolean IsFullQueuePoint (QueuePoint Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    return ((HeadPoint(Q) == 1) && (TailPoint(Q) == MaxElPoint(Q)));
}

int NBElmtQueuePoint (QueuePoint Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
	if (IsEmptyQueuePoint(Q)) {
        return 0;
    } else if (HeadPoint(Q)>TailPoint(Q)) {
        return ((MaxElPoint(Q)-HeadPoint(Q)) + 1 + TailPoint(Q));
    } else {
        return (TailPoint(Q) - HeadPoint(Q) + 1);
    }
}

/* *** Kreator *** */
void CreateEmptyQueuePoint (QueuePoint * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
	(*Q).T = (POINT *) malloc ((Max+1) * sizeof(POINT));
    if ((*Q).T != NULL) {
        MaxElPoint(*Q) = Max;
        HeadPoint(*Q) = 0;
        TailPoint(*Q) = 0;
    } else /* alokasi gagal */ {
        MaxElPoint(*Q) = 0;
    }
}

/* *** Destruktor *** */
void DeAlokasiQueuePoint (QueuePoint *Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
	MaxElPoint(*Q) = 0;
    free((*Q).T);
}

/* *** Primitif Add/Delete *** */
void AddPoint (QueuePoint *Q, POINT X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
	if (IsEmptyQueuePoint(*Q)) {
        HeadPoint(*Q) = 1;
    }
    else if (TailPoint(*Q) == MaxElPoint(*Q)) {
        TailPoint(*Q) = 0;
    }
    TailPoint(*Q)++;
    InfoTailPoint(*Q).X = X.X;
    InfoTailPoint(*Q).Y = X.Y;
}

void DelPoint (QueuePoint *Q, POINT *X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
{
	(*X).X = InfoHeadPoint(*Q).X;
	(*X).Y = InfoHeadPoint(*Q).Y;

    if (HeadPoint(*Q)==TailPoint(*Q)) {
        HeadPoint(*Q)=0;
        TailPoint(*Q)=0;
    } else {
        HeadPoint(*Q)++;
    }
}