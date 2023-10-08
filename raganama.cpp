#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

#define LGMAX_NUME 100
#define MAXCIF_NRMARE 200

using namespace std;

ifstream fin("raganama.in");
ofstream fout("raganama.out");

int main()
{
	int C, i, j;
	char s[LGMAX_NUME+1];

	// citesc cerinta si primul nume de fata
	fin >> C >> s;

	if (C == 1)
	{
		char p[LGMAX_NUME+1];

		strcpy(p, s);

		int lg = strlen(p);
		
		// retin in p cel mai frumos nume de fata (cel mai mic dpdv lexicografic)
		sort(p, p+lg);

		do
		{
			if (strcmp(p, s))
			{
				fout << p;
				break;
			}
			else
			{
				// generez urmatorul cel mai frumos nume de fata

				for (i = lg-2; i >= 0 && p[i] >= p[i+1]; i--);

				if (i < 0)
				{
					break; // am generat toate anagramele
				}
				else
				{
					for (j = lg-1; p[j] <= p[i] && j >= 1; j--);

					swap(p[i], p[j]);

					for (i = i+1, j = lg-1; i < j; i++, j--)
					{
						swap(p[i], p[j]);
					}
				}
			}
		}
		while (fin >> s);
	}
	else
	{
		char *c;
		int ap[26], dfp_lg[100], dfp_ap[100], lg, d, p, aux, nr[MAXCIF_NRMARE], k, t, n, nn[MAXCIF_NRMARE];
		
		// n = nr. de fete din trib	
		for (n = 1; fin >> s; n++);

		// initializez vector de frecventa
		for (i = 0; i < 26; ap[i] = 0, i++);
		
		// contorizez frecventa literelor dintr-o anagrama
		for (lg = 0, c = s; *c; c++, lg++) 
		{
			ap[*c-'a']++;
		}

		// initializez dfp_ap si dfp_lg
		//
		// dfp_ap = descompunerea in factori primi a lui ap
		// unde ap = ap[1]! * ap[2]! * ... * ap[i]!
		//
		// dfp_lg = descompunerea in factori primi a lui lg
		// unde lg = 1 * 2 * 3 * ... * lg
		for (i = 0; i < 100; i++)
		{
			dfp_ap[i] = dfp_lg[i] = 0;
		}
	
		// calculez dfp_lg	
		for (i = 2; i <= lg; i++)
		{
			aux = i;

			for (d = 2; d*d <= aux; d++)
			{
				for (p = 0; aux % d == 0; p++, aux /= d);

				if (p)
				{
					dfp_lg[d] += p;
				}
			}

			if (aux > 1)
			{
				dfp_lg[aux]++;
			}
		}

		// calculez dfp_ap
		for (i = 0; i < 26; i++)
		{
			if (ap[i] > 1)
			{
				for (j = 2; j <= ap[i]; j++)
				{
					aux = j;

					for (d = 2; d*d <= aux; d++)
					{
						for (p = 0; aux % d == 0; p++, aux /= d);

						if (p)
						{
							dfp_ap[d] += p;
						}
					}

					if (aux > 1)
					{
						dfp_ap[aux]++;
					}
				}
			}
		}
		
		// initializez numerele mari nr[] si nn[]
		for (i = 0; i < MAXCIF_NRMARE; i++)
		{
			nr[i] = nn[i] = 0;
		}
		
		// initializez nr cu 1
		lg = 1, nr[0] = 1; // in acest context lg = nr cifre a lui nr[]
		
		// calculez nr = dfp_lg/dfp_ap (numar mare)
		for (i = 0; i < 100; i++)
		{
			if (dfp_lg[i] > 0)
			{
				dfp_lg[i] -= dfp_ap[i];
					
				for (j = 1; j <= dfp_lg[i]; j++)
				{	
					for (t = k = 0; k < lg; k++)
					{
						p = nr[k]*i + t;

						nr[k] = p % 10;

						t = p / 10;
					}

					while (t)
					{
						nr[k++] = t % 10;

						t /= 10;
					}

					if (k > lg)
					{
						lg = k;
					}
				}
			}
		}
	
		// transform pe n in numar mare	
		for (k = 0; n; n /= 10)
		{
			nn[k++] = n % 10;
		}

		// calculez diferenta a doua numere mari (nr-nn)
		for (t = i = 0; i < lg; i++)
		{
			nr[i] = nr[i] - nn[i] - t;

			if (nr[i] < 0)
			{
				nr[i] += 10;
				t = 1;
			}
			else
			{
				t = 0;
			}
		}

		// sar peste zerourile de la inceput
		for (i = lg-1; i >= 0 && nr[i] == 0; i--);

		// afisez rezultatul
		for (; i >= 0; i--)
		{
			fout << nr[i];
		}

	}
	
	return 0;
}
// scor 100
