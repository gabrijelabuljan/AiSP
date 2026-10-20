#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
//a) dinamički dodaje novi element na početak liste,
//b) ispisuje listu,
//c) dinamički dodaje novi element na kraj liste,
//d) pronalazi element u listi(po prezimenu),
//e) briše određeni element iz liste.
//U zadatku se ne smiju koristiti globalne varijable.
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