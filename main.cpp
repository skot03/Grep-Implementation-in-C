#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#pragma warning(disable : 4996)
#define MAX_DLUGOSC_LINII 10000

int main()
{

    int opcja;
    system ("chcp 1250");
    char *szukany_ciag = (char *)malloc(MAX_DLUGOSC_LINII * sizeof(char));
    char nazwa_pliku[] = "tekst.txt";
    setlocale(LC_CTYPE, ".1250");
    printf("Podaj szukany ciag znakow: Upewnij sie ze ustawione jest kodowanie ANSI! ");
    fgets(szukany_ciag, MAX_DLUGOSC_LINII, stdin);
    szukany_ciag[strcspn(szukany_ciag, "\n")] = '\0'; // usunięcie znaku nowej linii

    printf("Wybierz opcje:\n");
    printf("1. Linie zawierajace szukany ciag\n");
    printf("2. Linie zaczynajace sie od szukanego ciagu\n");
    printf("3. Linie konczace sie na szukany ciag\n");
    scanf("%d", &opcja);

    FILE *plik = fopen(nazwa_pliku, "r");
    if (plik == NULL)
    {
        printf("Błąd: nie udało sie otworzyć pliku.\n");
        return 1;
    }

    char *linia = (char *)malloc(MAX_DLUGOSC_LINII * sizeof(char));
    int numer_linii = 0;
    int znaleziono = 0; // zmienna logiczna informująca, czy znaleziono szukany ciąg

    while (fgets(linia, MAX_DLUGOSC_LINII, plik) != NULL)
    {
        numer_linii++;

        switch (opcja)
        {
        case 1:
            if (strstr(linia, szukany_ciag) != NULL)
            {
                printf("Linia %d: %s", numer_linii, linia);
                znaleziono = 1;
            }
            break;
        case 2:
            if (strncmp(linia, szukany_ciag, strlen(szukany_ciag)) == 0)
            {
                printf("Linia %d: %s", numer_linii, linia);
                znaleziono = 1;
            }
            break;
        case 3:
            if (strlen(linia) >= strlen(szukany_ciag))
            {
                char *koniec_linii = linia + strlen(linia) - 1;
                char *koniec_ciagu = szukany_ciag + strlen(szukany_ciag) - 1;
                while (koniec_linii >= linia && isspace(*koniec_linii))
                {
                    koniec_linii--;
                }
                while (koniec_ciagu >= szukany_ciag && isspace(*koniec_ciagu))
                {
                    koniec_ciagu--;
                }
                if (*koniec_ciagu == '\0' || *koniec_linii == *koniec_ciagu)
                {
                    koniec_ciagu--;
                    koniec_linii--;
                    while (koniec_ciagu >= szukany_ciag && koniec_linii >= linia && *koniec_ciagu == *koniec_linii)
                    {
                        koniec_ciagu--;
                        koniec_linii--;
                    }
                    if (koniec_ciagu < szukany_ciag)
                    {
                        printf("Linia %d: %s", numer_linii, linia);
                        znaleziono = 1;
                    }
                }
            }
            break;
        default:
            printf("Błąd: nieprawidłowa opcja.\n");
            return 1;
        }
    }

    if (znaleziono == 0)
    {
        printf("Brak wystapienia w tekscie.\n");
    }

    free(szukany_ciag);
    free(linia);
    fclose(plik);

    return 0;
}
