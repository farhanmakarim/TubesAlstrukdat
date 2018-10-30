#include "map.h"
#include <stdio.h>

void CreateMap(int m, int n, MATRIKS* M) {
  NBrsEff(*M) = m;
  NKolEff(*M) = n;
  int i;
  for (i=0; i<m; i++) {
    int j;
    for (j=0; j<n; j++) {
      if (i%4==0) {
          Elmt(*M,i,j).CC='*';
      Elmt(*M,i,j).kepemilikan=3;
      }
      else {
        if (j%4==0) {
          Elmt(*M,i,j).CC='*';
      Elmt(*M,i,j).kepemilikan=3;
        }
        else {
          Elmt(*M,i,j).CC=' ';
      Elmt(*M,i,j).kepemilikan=3;
        }
      }
    }
  }

  Elmt(*M, m-4, 6).CC = 'C';
  Elmt(*M, m-4, 6).kepemilikan = 1;
  Elmt(*M, m-8, 6).CC = 'T';
  Elmt(*M, m-8, 6).kepemilikan = 1;
  Elmt(*M, m-7, 6).CC = 'K';
  Elmt(*M, m-7, 6).kepemilikan = 1;
  Elmt(*M, m-12, 6).CC = 'C';
  Elmt(*M, m-12, 6).kepemilikan = 1;
  Elmt(*M, m-8, 2).CC = 'C';
  Elmt(*M, m-8, 2).kepemilikan = 1;
  Elmt(*M, m-8, 10).CC = 'C';
  Elmt(*M, m-8, 10).kepemilikan = 1;

  Elmt(*M, 1, n-7).CC = 'C';
  Elmt(*M, 1, n-7).kepemilikan = 2;
  Elmt(*M, 5, n-7).CC = 'T';
  Elmt(*M, 5, n-7).kepemilikan = 2;
  Elmt(*M, 6, n-7).CC = 'K';
  Elmt(*M, 6, n-7).kepemilikan = 2;
  Elmt(*M, 5, n-3).CC = 'C';
  Elmt(*M, 5, n-3).kepemilikan = 2;
  Elmt(*M, 5, n-11).CC = 'C';
  Elmt(*M, 5, n-11).kepemilikan = 2;
  Elmt(*M, 9, n-7).CC = 'C';
  Elmt(*M, 9, n-7).kepemilikan = 2;
}

void PrintMap(int m, int n, MATRIKS M) {
  int k;
  for (k=0; k<(n-1)/4; k++) {
    if (k==0) {
        printf("   ");
    }
    printf("  ");
    printf("%d", k);
    if (k==((n-1)/4)-1) {
      printf("\n");
    }
    else {
      if (k<10) {
        printf(" ");
      }
    }
  }

  int l = 0;
  int i;
  for (i=0; i<m; i++) {
    int j;
    for (j=0; j<n; j++) {
      if (j==0) {
        if ((i-2)%4==0) {
          if (l<10) {
            printf(" %d ", l);
          }
          else {
            printf("%d ", l);
          }
          l++;
        }
        else {
          printf("   ");
        }
      }

      print_char(Elmt(M, i, j)); //printf("%c", Elmt(M, i, j));
      if (j==(n-1)) {
        printf("\n");
      }
    }
  }
}

void convertIndex (int *m, int *n) {
    *m = ((*m)*4)+1;
    *n = ((*n)*4)+1;
}

void RecruitMap(int m, int n, MATRIKS *M, int x)
/* Untuk Menampilkan Cell yang ditempati untuk recruit*/
{
  if (x == 1) {
    if (Elmt(*M, m-3, 6).CC == ' ') {
      Elmt(*M, m-3, 6).CC = '#';
      Elmt(*M, m-3, 6).kepemilikan = 3;
    }
    if (Elmt(*M, m-11, 6).CC == ' ') {
      Elmt(*M, m-11, 6).CC = '#';
      Elmt(*M, m-11, 6).kepemilikan = 3;
    }
    if (Elmt(*M, m-7, 2).CC == ' ') {
      Elmt(*M, m-7, 2).CC = '#';
      Elmt(*M, m-7, 2).kepemilikan = 3;
    }
    if (Elmt(*M, m-7, 10).CC == ' ') {
      Elmt(*M, m-7, 10).CC = '#';
      Elmt(*M, m-7, 10).kepemilikan = 3;
    }
  } else if (x == 2) {
    if (Elmt(*M, 2, n-7).CC == ' ') {
      Elmt(*M, 2, n-7).CC = '#';
      Elmt(*M, 2, n-7).kepemilikan = 3;
    }
    if (Elmt(*M, 6, n-3).CC == ' ') {
      Elmt(*M, 6, n-3).CC = '#';
      Elmt(*M, 6, n-3).kepemilikan = 3;
    }
    if (Elmt(*M, 6, n-11).CC == ' ') {
      Elmt(*M, 6, n-11).CC = '#';
      Elmt(*M, 6, n-11).kepemilikan = 3;
    }
    if (Elmt(*M, 10, n-7).CC == ' ') {
      Elmt(*M, 10, n-7).CC = '#';
      Elmt(*M, 10, n-7).kepemilikan = 3;
    }
  }
}

void UpdateMoveMAP(MATRIKS *MAP, MATRIKS *Jarak, Unit X, int player, int BarisR, int KolomR) {
  QueuePoint bfs;
  POINT PMAP;
  POINT Now = X.pos;
  POINT Neighbour;
  int jaraknow;

  CreateEmptyQueuePoint(&bfs, 100);

  AddPoint(&bfs, X.pos);

  PMAP = AksesMatriksUnit(Now.X, Now.Y);
  
  while(!IsEmptyQueuePoint(bfs)) {

    DelPoint(&bfs, &Now);

    PMAP = AksesMatriksUnit(Now.X, Now.Y);

    jaraknow = Elmt(*Jarak, PMAP.X, PMAP.Y).kepemilikan;

    if (Elmt(*Jarak, PMAP.X, PMAP.Y).kepemilikan < X.maxmove) {
      if (Now.X > 0) {
        PMAP = AksesMatriksUnit(Now.X-1, Now.Y);
        if (Elmt(*MAP, PMAP.X, PMAP.Y).CC == ' ' || Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan == player) {
          Neighbour.X = Now.X-1;
          Neighbour.Y = Now.Y;  

          if (Elmt(*MAP, PMAP.X, PMAP.Y).CC == ' ') {
            Elmt(*MAP, PMAP.X, PMAP.Y).CC = '?';
            Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan = 3;
          } 

          AddPoint(&bfs, Neighbour);
        
          Elmt(*Jarak, PMAP.X, PMAP.Y).kepemilikan = jaraknow + 1;
        }
      }

      if (Now.Y > 0) {
        PMAP = AksesMatriksUnit(Now.X, Now.Y-1);
        if (Elmt(*MAP, PMAP.X, PMAP.Y).CC == ' ' || Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan == player) {

          Neighbour.X = Now.X;
          Neighbour.Y = Now.Y-1;

          if (Elmt(*MAP, PMAP.X, PMAP.Y).CC == ' ') {
            Elmt(*MAP, PMAP.X, PMAP.Y).CC = '?';
            Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan = 3;
          } 

          AddPoint(&bfs, Neighbour);
        
          Elmt(*Jarak, PMAP.X, PMAP.Y).kepemilikan = jaraknow + 1;
        }
      }

      if (Now.X < BarisR - 1) {
        PMAP = AksesMatriksUnit(Now.X+1, Now.Y);
        if (Elmt(*MAP, PMAP.X, PMAP.Y).CC == ' ' || Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan == player) {

          Neighbour.X = Now.X+1;
          Neighbour.Y = Now.Y;

          if (Elmt(*MAP, PMAP.X, PMAP.Y).CC == ' ') {
            Elmt(*MAP, PMAP.X, PMAP.Y).CC = '?';
            Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan = 3;
          } 

          AddPoint(&bfs, Neighbour);
        
          Elmt(*Jarak, PMAP.X, PMAP.Y).kepemilikan = jaraknow + 1;
        }
      }

      if (Now.Y < KolomR - 1) {
        PMAP = AksesMatriksUnit(Now.X, Now.Y+1);
        if (Elmt(*MAP, PMAP.X, PMAP.Y).CC == ' ' || Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan == player) {

          Neighbour.X = Now.X;
          Neighbour.Y = Now.Y+1;

          if (Elmt(*MAP, PMAP.X, PMAP.Y).CC == ' ') {
            Elmt(*MAP, PMAP.X, PMAP.Y).CC = '?';
            Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan = 3;
          } 

          AddPoint(&bfs, Neighbour);
        
          Elmt(*Jarak, PMAP.X, PMAP.Y).kepemilikan = jaraknow + 1;
        }
      }
    }
  }
}

void CopyMap(MATRIKS Min, MATRIKS *Mout)
/*Untuk Mengcopy Map ke suatu Map kosong*/
{
  CopyMATRIKS(Min, Mout);
}

void PrintAttack(int i, List L, Unit X, MATRIKS MAP, int PosAttack[], boolean *CantAttack, int BarisR, int KolomR) {
	POINT Pos;
	int ke = 1;
	address ListP;

	if (X.pos.X > 0) {
		Pos.X = X.pos.X-1;
		Pos.Y = X.pos.Y;
		
		if (Elmt(MAP, AksesMatriksUnit(Pos.X, Pos.Y).X, AksesMatriksUnit(Pos.X, Pos.Y).Y).CC != ' ' && Elmt(MAP, AksesMatriksUnit(Pos.X, Pos.Y).X, AksesMatriksUnit(Pos.X, Pos.Y).Y).kepemilikan != i ) {
			ListP = SearchPoint(L, Pos);
			printf("%d. ", ke);
			PrintUnitAttack(X, InfoList(ListP));
			(PosAttack)[ke] = 1;
			ke++;
			printf("\n");				
		}
	}

	if (X.pos.Y > 0) {
		Pos.X = X.pos.X;
		Pos.Y = X.pos.Y-1;
		
		if (Elmt(MAP, AksesMatriksUnit(Pos.X, Pos.Y).X, AksesMatriksUnit(Pos.X, Pos.Y).Y).CC != ' ' && Elmt(MAP, AksesMatriksUnit(Pos.X, Pos.Y).X, AksesMatriksUnit(Pos.X, Pos.Y).Y).kepemilikan != i ) {
			ListP = SearchPoint(L, Pos);
			printf("%d. ", ke);
			PrintUnitAttack(X, InfoList(ListP));
			(PosAttack)[ke] = 2;
			ke++;
			printf("\n");			
		}
	}

	if (X.pos.Y < KolomR - 1) {
		Pos.X = X.pos.X;
		Pos.Y = X.pos.Y+1;
		
		if (Elmt(MAP, AksesMatriksUnit(Pos.X, Pos.Y).X, AksesMatriksUnit(Pos.X, Pos.Y).Y).CC != ' ' && Elmt(MAP, AksesMatriksUnit(Pos.X, Pos.Y).X, AksesMatriksUnit(Pos.X, Pos.Y).Y).kepemilikan != i ) {
			ListP = SearchPoint(L, Pos);
			printf("%d. ", ke);
			PrintUnitAttack(X, InfoList(ListP));
			(PosAttack)[ke] = 3;
			ke++;
			printf("\n");				
		}
	}

	if (X.pos.X < BarisR - 1) {
		Pos.X = X.pos.X+1;
		Pos.Y = X.pos.Y;
		
		if (Elmt(MAP, AksesMatriksUnit(Pos.X, Pos.Y).X, AksesMatriksUnit(Pos.X, Pos.Y).Y).CC != ' ' && Elmt(MAP, AksesMatriksUnit(Pos.X, Pos.Y).X, AksesMatriksUnit(Pos.X, Pos.Y).Y).kepemilikan != i ) {
			ListP = SearchPoint(L, Pos);
			printf("%d. ", ke);
			PrintUnitAttack(X, InfoList(ListP));
			(PosAttack)[ke] = 4;
			ke++;
			printf("\n");				
		}
	}

	if (ke == 1) {
		printf("There's no enemy you can attack\n");
		*CantAttack = 1;
	}
}