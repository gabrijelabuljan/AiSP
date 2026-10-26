#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Osoba* Pozicija;
typedef struct Osoba {
	char ime[20];
	char prezime[20];
	int g_r;
	Pozicija Next;
}osoba;

int UnosNaPocetak(const char im[20], const char prez[20], int g, Pozicija P);
int Ispis(Pozicija P);
int UnosNaKraj(const char im[20], const char prez[20], int g, Pozicija P);
int Trazi(const char prez[20], Pozicija P);
int Brisi(const char ime[20], Pozicija P);
int dodajIza(const char im[20], const char prez[20], int g, const char im1[20], const char prez1[20], Pozicija P);
int dodajIspred(const char im[20], const char prez[20], int g, const char im1[20], const char prez1[20], Pozicija P);
int sortiraj(Pozicija P);
int unosUDatoteku(Pozicija P);
int citanjeIzDatoteke(Pozicija P);

int main() {
	osoba Head;
	Head.Next = NULL;
	UnosNaPocetak("Mate", "Matic", 2000, &Head);
	Ispis(Head.Next);
	printf("\n");
	UnosNaKraj("Jure", "Juric", 2001, &Head);
	Ispis(Head.Next);
	printf("\n");
	UnosNaPocetak("Stipe", "Stipic", 2000, &Head);
	Ispis(Head.Next);
	printf("\n");
	UnosNaKraj("Ana", "Anic", 2000, &Head);
	Ispis(Head.Next);
	printf("\n");
	Trazi("Juric", Head.Next);
	Brisi("Ana", &Head);
	Ispis(Head.Next);
	printf("\n");
	dodajIspred("Ivan", "Ivic", 2000, "Jure", "Juric", &Head);
	Ispis(Head.Next);
	printf("\n");
	dodajIza("Luka", "Lukic", 2000, "Jure", "Juric", &Head);
	Ispis(Head.Next);
	printf("\n");
	sortiraj(&Head);
	Ispis(Head.Next);
	printf("\n");
	unosUDatoteku(Head.Next);
	printf("Sadrzaj datoteke:\n");
	citanjeIzDatoteke(Head.Next);
	printf("\nLista nakon citanja:\n");
	Ispis(Head.Next);
	while (Head.Next != NULL) {
		Pozicija q = Head.Next;
		Head.Next = q->Next;
		free(q);
	}
	return 0;
}

int unosUDatoteku(Pozicija P) {
	FILE* fp = NULL;
	fp = fopen("osobe.txt", "w");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	while (P != NULL) {
		fprintf(fp, "%s %s %d\n", P->ime, P->prezime, P->g_r);
		P = P->Next;
	}
	fclose(fp);
	return 0;
}

int citanjeIzDatoteke(Pozicija P)
{
	FILE* fp = fopen("osobe.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	Pozicija q;
	while (1) {
		q = (Pozicija)malloc(sizeof(struct Osoba));

		if (q == NULL) {
			printf("Neuspjesna alokacija memorije.\n");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%19s %19s %d",
			q->ime, q->prezime, &q->g_r) != 3) {
			free(q);
			break;
		}
		q->Next = NULL;
		while (P->Next != NULL)
			P = P->Next;
		P->Next = q;
		P = q;
	}
	fclose(fp);
	return 0;
}
int sortiraj(Pozicija P) {
	Pozicija q, temp;
	while (P->Next != NULL && P->Next->Next != NULL) {
		q = P->Next->Next;
		if (_strcmpi(P->prezime, q->prezime) > 0) {
			temp = P->Next;
			temp->Next = q->Next;
			q->Next = temp;
			P->Next = q;
		}
		P = P->Next;
	}
	return 0;
}
int dodajIza(const char im[20], const char prez[20], int g, const char im1[20], const char prez1[20], Pozicija P) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return 1;
	}
	while (P->Next != NULL && (_strcmpi(P->Next->ime, im1) != 0 || _strcmpi(P->Next->prezime, prez1) != 0))
		P = P->Next;
	if (P->Next == NULL) {
		printf("Osoba pod imenom %s i prezimenom %s ne postoji u listi.\n", im1, prez1);
		return 1;
	}
	strcpy_s(q->ime, sizeof(q->ime), im);
	strcpy_s(q->prezime, sizeof(q->prezime), prez);
	q->g_r = g;
	q->Next = P->Next->Next;
	P->Next->Next = q;

	return 0;
}
int dodajIspred(const char im[20], const char prez[20], int g, const char im1[20], const char prez1[20], Pozicija P) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return 1;
	}
	while (P->Next != NULL && (_strcmpi(P->Next->ime, im1) != 0 || _strcmpi(P->Next->prezime, prez1) != 0))
		P = P->Next;
	if (P->Next == NULL) {
		printf("Osoba pod imenom %s i prezimenom %s ne postoji u listi.\n", im1, prez1);
		return 1;
	}
	strcpy_s(q->ime, sizeof(q->ime), im);
	strcpy_s(q->prezime, sizeof(q->prezime), prez);
	q->g_r = g;
	q->Next = P->Next;
	P->Next = q;

	return 0;
}
int UnosNaPocetak(const char im[20], const char prez[20], int g, Pozicija P) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return 1;
	}
	strcpy_s(q->ime, sizeof(q->ime), im);
	strcpy_s(q->prezime, sizeof(q->prezime), prez);
	q->g_r = g;
	q->Next = P->Next;
	P->Next = q;
	return 0;
}
int UnosNaKraj(const char im[20], const char prez[20], int g, Pozicija P) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return 1;
	}
	while (P->Next != NULL)
		P = P->Next;

	strcpy_s(q->ime, sizeof(q->ime), im);
	strcpy_s(q->prezime, sizeof(q->prezime), prez);
	q->g_r = g;
	q->Next = P->Next;
	P->Next = q;

	return 0;
}
int Trazi(const char prez[20], Pozicija P) {
	while (P != NULL && (_strcmpi(P->prezime, prez) != 0))
		P = P->Next;
	if (P == NULL) {
		printf("Osoba pod prezimenom %s ne postoji u listi.\n", prez);
	}
	else if (_strcmpi(P->prezime, prez) == 0) {
		printf("Pronadena osoba pod prezimenom %s je: %s %s %d\n", prez, P->ime, P->prezime, P->g_r);
	}
	return 0;
}
int Brisi(const char ime[20], Pozicija P) {
	Pozicija q;
	while (P->Next != NULL && (_strcmpi(P->Next->ime, ime) != 0)) {
		P = P->Next;
	}
	if (P == NULL) {
		printf("Osoba pod prezimenom %s ne postoji u listi.\n", ime);
	}
	else if (_strcmpi(P->Next->ime, ime) == 0) {
		q = P->Next;
		P->Next = q->Next;
		free(q);
	}
	return 0;
}
int Ispis(Pozicija P) {
	while (P != NULL) {
		printf("%s %s %d\n", P->ime, P->prezime, P->g_r);
		P = P->Next;
	}
	return 0;
}