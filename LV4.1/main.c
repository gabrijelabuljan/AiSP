#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se čitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani.

typedef struct Polinomi* pozicija;
typedef struct Polinomi {
	int koeficijent;
	int eksponent;
	pozicija next;
}polinomi;

int citanjeIzDatoteke(pozicija p, char dat[]) {
	FILE* fp = NULL;
	fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}
	pozicija q, pocetak = p;
	q = (pozicija)malloc(sizeof(polinomi));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return -1;
	}
	while (fscanf(fp, "%d %d", &q->koeficijent, &q->eksponent) == 2) {
		p = pocetak;
		while (p->next != NULL) {
			if (p->next->koeficijent == q->koeficijent && p->next->eksponent == q->eksponent) {
				break;
			}
			p = p->next;
		}
		if(p->next == NULL){
			q->next = p->next;
			p->next = q;
		}
		else {
			free(q);
		}
		q = (pozicija)malloc(sizeof(polinomi));
		if (q == NULL) {
			printf("Greska pri alokaciji memorije!\n");
			return -1;
		}
	}
	fclose(fp);
	free(q);
	return 0;
}
int zbroji(pozicija p, pozicija p2, pozicija z) {
	pozicija q ,pocetak =z;
	while (p != NULL) {
		z = pocetak;
		while (z->next != NULL && p->eksponent != z->next->eksponent) {
			z = z->next;
		}
		if (z->next != NULL) {
			z->next->koeficijent += p->koeficijent;
		}
		else {
			q = (pozicija)malloc(sizeof(polinomi));
			if (q == NULL) {
				printf("Greska pri alokaciji memorije!\n");
				return -1;
			}
			q->eksponent = p->eksponent;
			q->koeficijent = p->koeficijent;
			q->next = NULL;
			z->next = q;
		}
		p = p->next;
	}
	z = pocetak;
	while (p2 != NULL) {
		z = pocetak;
		while (z->next != NULL && p2->eksponent != z->next->eksponent) {
			z = z->next;
		}
		if (z->next != NULL) {
			z->next->koeficijent += p2->koeficijent;
		}
		else {
			q = (pozicija)malloc(sizeof(polinomi));
			if (q == NULL) {
				printf("Greska pri alokaciji memorije!\n");
				return -1;
			}
			q->eksponent = p2->eksponent;
			q->koeficijent = p2->koeficijent;
			q->next = NULL;
			z->next = q;
		}
		p2 = p2->next;
	}

	return 0;
}
int Sort(pozicija p) {
	pozicija j,q, temp;
	while (p->next != NULL) {
		j = p->next;
		q = j;
		while (q->next != NULL) {
			if (j->eksponent == q->next->eksponent) {
				j->koeficijent += q->next->koeficijent;
				temp = q->next;
				q->next = q->next->next;
				free(temp);
			}
			else {
				q = q->next;
			}
		}
		p = p->next;
	}
	return 0;
}

int mnozenje(pozicija p, pozicija p2, pozicija u) {
	pozicija q, pocetak = p2;
	while (p != NULL) {
		p2 = pocetak;
		while (p2 != NULL) {
			q = (pozicija)malloc(sizeof(polinomi));
			if (q == NULL) {
				printf("Greska pri alokaciji memorije!\n");
				return -1;
			}
			q->eksponent = p->eksponent + p2->eksponent;
			q->koeficijent = p->koeficijent * p2->koeficijent;
			q->next = NULL;
			u->next = q;
			u = q;
			p2 = p2->next;
		}
		p = p->next;
	}

	return 0;
}

int Ispis(pozicija p) {
	int prvi = 1;
	while (p != NULL) {
		if (p->koeficijent != 0) {
			if (p->koeficijent < 0) {
				printf("%d", p->koeficijent);
			}
			else {
				if (prvi == 0) {
					printf("+");
				}
				printf("%d", p->koeficijent);
			}

			if (p->eksponent != 0) {
				if (p->eksponent == 1) {
					printf("x");
				}
				else {
					printf("x^%d", p->eksponent);
				}
			}
			prvi = 0;
		}
		p = p->next;
	}
	return 0;
}
int main() {
	polinomi head1, head2, zbroj, umnozak;
	head1.next = NULL;
	head2.next = NULL;
	zbroj.next = NULL;
	umnozak.next = NULL;
	citanjeIzDatoteke(&head1, "polinomi1.txt");
	citanjeIzDatoteke(&head2, "polinomi2.txt");
	Ispis(head1.next);
	printf("\n");
	Ispis(head2.next);
	printf("\n");
	zbroji(head1.next, head2.next, &zbroj);
	printf("\n");
	Ispis(zbroj.next);
	printf("\n");
	Sort(&head1);
	Sort(&head2);
	Ispis(head1.next);
	printf("\n");
	Ispis(head2.next);
	printf("\n");
	mnozenje(head1.next, head2.next, &umnozak);
	Ispis(umnozak.next);
	Sort(&umnozak);
	printf("\nSortirani umnozak:\n");
	Ispis(umnozak.next);
	return 0;
}