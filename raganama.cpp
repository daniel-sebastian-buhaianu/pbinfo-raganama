#include <fstream>
#include <cstring>
#include <algorithm>

#define LGMAX_NUME 100

using namespace std;

ifstream fin("raganama.in");
ofstream fout("raganama.out");

int main()
{
	int C, lg, gasit, i, j, n, nr;
	char s[LGMAX_NUME+1], p[LGMAX_NUME+1];

	fin >> C;

	fin >> s;

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
		n = 1;

		while (fin >> s)
		{
			n++;
		}
		
		nr = 0;

		while (!gasit)
		{
			nr++;
			
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

		fout << nr-n;
	}

	return 0;
}
// scor 50
