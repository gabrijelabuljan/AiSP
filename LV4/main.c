#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Cvor* Pozicija;
typedef struct Cvor {
	int koef;
	int eksponent;
	Pozicija next;
}cvor;
int Citanje(Pozicija P) {
	FILE* fp = NULL;
	fp = fopen("polinomi.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke\n");
		return -1;
	}
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Cvor));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije");
		return -1;
	}
	while (fscanf(fp, "%d %d", &q->koef, &q->eksponent) == 2) {
		Pozicija temp = P;
		while (temp->next != NULL && temp->next->eksponent < q->eksponent) {
			temp = temp->next;
		}
		q->next = temp->next;
		temp->next = q;
		q = (Pozicija)malloc(sizeof(struct Cvor));
		if (q == NULL) {
			printf("Greska pri alokaciji memorije");
			return -1;
		}
	}
	fclose(fp);
	return 0;
}
int Zbroji(Pozicija P) {
	Pozicija temp,q=P;
	int zbroj = 0;
	while (q != NULL) {
		temp = q->next;
		zbroj = q->koef;
		while (temp != NULL) {
			if (temp->eksponent == q->eksponent) {
				zbroj += temp->koef;
			}
			temp = temp->next;
		}
		printf("Zbroj polinoma %d stupnja je %d\n", q->eksponent, zbroj);
		while (q->next != NULL && q->next->eksponent == q->eksponent) {
			q = q->next;
		}
		q = q->next;
	}
	return 0;
}

int Mnozenje(Pozicija P) {
	Pozicija temp, q = P;
	int umnozak = 0;
	while (q != NULL) {
		temp = q->next;
		umnozak = q->koef;
		while (temp != NULL) {
			if (temp->eksponent == q->eksponent) {
				umnozak *= temp->koef;
			}
			temp = temp->next;
		}
		printf("Umnozak polinoma %d stupnja je %d\n", q->eksponent, umnozak);
		while (q->next != NULL && q->next->eksponent == q->eksponent) {
			q = q->next;
		}
		q = q->next;
	}
	return 0;
}
int Ispis(Pozicija P) {
	while (P != NULL) {
		printf("%d %d\n", P->koef, P->eksponent);
		P = P->next;
	}
	return 0;
}
int main() {
	cvor Head;
	Head.next = NULL;
	Citanje(&Head);
	Ispis(Head.next);
	Zbroji(Head.next);
	Mnozenje(Head.next);
	return 0;
}
