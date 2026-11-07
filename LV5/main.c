#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//5. Za dvije sortirane liste L1 i L2(mogu se pročitati iz datoteke ili unijeti ručno, bitno je samo da su
//	sortirane), napisati program koji stvara novu vezanu listu tako da računa :
//a) L1∪L2,
//b) L1∩ L2.
//Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po kojem su
//sortirane.

typedef struct Cvor* pozicija;
typedef struct Cvor {
	int broj;
	pozicija next;
}cvor;

int citajIzDatoteke(pozicija p, char dat[]) {
	FILE* fp = NULL;
	fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}
	pozicija q;
	q = (pozicija)malloc(sizeof(cvor));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return -1;
	}
	while (fscanf(fp, "%d", &q->broj) == 1) {
		q->next = p->next;
		p->next = q;
		q = (pozicija)malloc(sizeof(cvor));
		if (q == NULL) {
			printf("Greska pri alokaciji memorije!\n");
			return -1;
		}
	}
	fclose(fp);
	free(q);
	return 0;
}

int sortiraj(pozicija p) {
	pozicija j_prev, j, temp, start = p, end = NULL;
	while (p->next != end) {
		j_prev = p;
		j = p->next;
		while (j->next != end) {
			if (j->broj > j->next->broj) {
				temp = j->next;
				j_prev->next = temp;
				j->next = j->next->next;
				temp->next = j;
				j = temp;
			}
			j_prev = j;
			j = j->next;
		}
		end = j;
	}
	p = start;
	pozicija q, i, temp2;
	while (p->next != NULL) {
		i = p->next;
		q = i;
		while (q->next != NULL) {
			if (i->broj == q->next->broj) {
				temp2 = q->next;
				q->next = q->next->next;
				free(temp2);
			}
			else {
				q = q->next;
			}
		}
		p = p->next;
	}
	return 0;
}

int sviZajedno(pozicija p1, pozicija p2, pozicija u) {
	pozicija q, temp, pocetak = u;
	q = (pozicija)malloc(sizeof(cvor));
	if (q == NULL) {
		printf("Greska pri alociranju memorije!\n");
		return -1;
	}
	while (p1 != NULL) {
		u = pocetak;
		q->broj = p1->broj;
		while (u->next != NULL) {
			u = u->next;
		}
		q->next = u->next;
		u->next = q;
		q = (pozicija)malloc(sizeof(cvor));
		if (q == NULL) {
			printf("Greska pri alociranju memorije!\n");
			return -1;
		}
		p1 = p1->next;
	}
	free(q);
	q = (pozicija)malloc(sizeof(cvor));
	if (q == NULL) {
		printf("Greska pri alociranju memorije!\n");
		return -1;
	}
	while (p2 != NULL) {
		u = pocetak;
		q->broj = p2->broj;
		while (u->next != NULL) {
			u = u->next;
		}
		q->next = u->next;
		u->next = q;
		q = (pozicija)malloc(sizeof(cvor));
		if (q == NULL) {
			printf("Greska pri alociranju memorije!\n");
			return -1;
		}
		p2 = p2->next;
	}
	free(q);
	pozicija j;
	u = pocetak;
	while (u->next != NULL) {
		j = u->next;
		q = j;
		while (q->next != NULL) {
			if (j->broj == q->next->broj) {
				temp = q->next;
				q->next = q->next->next;
				free(temp);
			}
			else {
				q = q->next;
			}
		}
		u = u->next;
	}
	return 0;
}

int samoZajednicki(pozicija p1, pozicija p2, pozicija pres) {
	pozicija q, pocetak = pres, start = p2;
	while (p1 != NULL) {
		p2 = start;
		while (p2 != NULL) {
			if (p2->broj == p1->broj) {
				q = (pozicija)malloc(sizeof(cvor));
				if (q == NULL) {
					printf("Greska pri alociranju memorije!\n");
					return -1;
				}
				q->broj = p1->broj;
				q->next = NULL;

				while (pres->next != NULL) {
					pres = pres->next;
				}

				pres->next = q;
			}

			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return 0;
}

int ispis(pozicija p) {
	while (p != NULL) {
		printf("%d\n", p->broj);
		p = p->next;
	}
	return 0;
}
int main() {
	cvor head1, head2, unija, presjek;
	head1.next = NULL;
	head2.next = NULL;
	unija.next = NULL;
	presjek.next = NULL;
	citajIzDatoteke(&head1, "L1.txt");
	citajIzDatoteke(&head2, "L2.txt");
	printf("\nL1:\n");
	ispis(head1.next);
	printf("\nL2:\n");
	ispis(head2.next);
	printf("\n");
	sortiraj(&head1);
	sortiraj(&head2);
	printf("\nL1 sortirana:\n");
	ispis(head1.next);
	printf("\nL2 sortirana:\n");
	ispis(head2.next);
	sviZajedno(head1.next, head2.next, &unija);
	printf("\nUnija:\n");
	ispis(unija.next);
	printf("\nPresjek:\n");
	samoZajednicki(head1.next, head2.next, &presjek);
	ispis(presjek.next);
	return 0;
}