#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//functie pentru verfificarea extesiilor
int verif_extensie(char str[])
{
	char *p = str + strlen(str) - 4;
	if (strcmp(p, ".exe") == 0)
		return 1;
	else if (strcmp(p, ".pdf") == 0)
		return 1;
	else if (strcmp(p, ".doc") == 0)
		return 1;
	else if (strcmp(p, ".bin") == 0)
		return 1;
	return 0;
}

int main(void)
{
	char mat[2000][50], str[1500];
	char date[40] = "data/urls/domains_database";
	int k = 0, t = 0, i = 0, x = 0;
	FILE *data = fopen(date, "rt");
	//copiez datele din fisierul ajutator
	// intr-o matrice de string-uri
	while (fgets(str, 1500, data)) {
		int lung = strlen(str);
		str[lung - 1] = '\0';
		strcpy(mat[++k], str);
	}
	fclose(data);
	char nume[40] = "data/urls/urls.in";
	FILE *in = fopen(nume, "rt");
	int verif = 0;
	char output[] = "urls-predictions.out";
	FILE *out = fopen(output, "wt");
	while (fgets(str, 1500, in)) {
		int lung = strlen(str);
		str[lung - 1] = '\0';//elimin "\n" de la sfarsitul url-ului
		verif = 0;
		//verific daca datele din fisierul ajutator
		//se gasesc in url-ul curent
		for (i = 1; i <= k; i++) {
			if (strstr(str, mat[i]))
				verif = 1;
		}
		//verific daca exista o extensie malitioasa
		if (verif_extensie(str) == 1)
			verif = 1;
		t = 0;
		x = 0;
		while (x <= (int)strlen(str) && str[x] != '/')
			x++;
		//numar cifrele din domeniu
		for (i = 0; i < x; i++)
			if (str[i] >= '0'  && str[i] <= '9')
				t++;
		if (2.0 * t >= 0.1 * x)
			verif = 1;
			fprintf(out, "%d\n", verif);
	}
	fclose(out);
	fclose(in);
	char task2[] = "data/traffic/traffic.in";
	char *p;
	in = fopen(task2, "rt");
	out = fopen("traffic-predictions.out", "wt");
	fgets(str, 1500, in);
	while (fgets(str, 1500, in)) {
		k = 0;
		int ok = 0;
		int timp = 0;
		int lung = strlen(str);
		str[lung - 1] = '\0';
		//despart in token-uri separate prin virgula
		p = strtok(str, ",");
		while (p) {
			k++;
			if (k == 5) {
				if (p[0] != '0')
					timp = 1;
				for (int i = 7; i <= 14; i++) {
					if (p[i] != '0' && p[i] != ':')
						timp = 1;
				}
			} else if (k == 17) {
				if (p[0] != '0')
					ok = 1;
			}
			p = strtok(NULL, ",");
		}
		if (timp == 1 && ok == 1)
			fprintf(out, "1\n");
		else
			fprintf(out, "0\n");
	}
	fclose(out);
	fclose(in);
}

