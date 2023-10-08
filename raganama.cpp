#include <fstream>
#include <cstring>
#include <algorithm>

#define LGMAX_NUME 100
#define MAXCIF_NRMARE 200

using namespace std;

ifstream fin("raganama.in");
ofstream fout("raganama.out");

int main()
{
	int C, lg, gasit, i, j;
	char s[LGMAX_NUME+1], p[LGMAX_NUME+1];

	fin >> C >> s;

	strcpy(p, s);

	lg = strlen(p);

	sort(p, p+lg);

	if (C == 1)
	{
		gasit = 0;

		do
		{
			if (strcmp(p, s))
			{
				fout << p;

				gasit = 1;
			}
			else
			{
				for (i = lg-2; i >= 0 && p[i] >= p[i+1]; i--);

				if (i < 0)
				{
					gasit = 1;
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
		while (fin >> s && !gasit);
	}
	else
	{
		int nr[MAXCIF_NRMARE], nn[MAXCIF_NRMARE], nrcif, d;

		for (i = 0; i < MAXCIF_NRMARE; i++)
		{
			nr[i] = nn[i] = 0;
		}

		for (i = 1; fin >> s; i++);

		for (j = 0; i; i /= 10, j++)
		{
			nn[j] = i%10;
		}

		nrcif = 1;

		while (1)
		{
			// nr++
			for (i = 0; nr[i] == 9 && i < nrcif; nr[i] = 0, i++);

			if (i == nrcif)
			{
				nr[i] = 1, nrcif++;
			}
			else
			{
				nr[i]++;
			}

			for (i = lg-2; i >= 0 && p[i] >= p[i+1]; i--);

			if (i < 0)
			{
				break;
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

		for (d = i = 0; i < nrcif; i++)
		{
			if (nr[i]-d < nn[i])
			{
				nr[i] = nr[i]+10-nn[i]-d;
				d = 1;
			}
			else
			{
				nr[i] = nr[i]-d-nn[i];
				d = 0;
			}
		}

		for (i = nrcif-1; i >= 0 && nr[i] == 0; i--);

		if (i < 0)
		{
			fout << 0;
		}
		else
		{
			for (; i >= 0; i--)
			{
				fout << nr[i];
			}
		}	
	}

	return 0;
}
// scor 60
