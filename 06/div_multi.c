#include <stdio.h>

float multi(int, int), div(int, int);

main()
{
	int i, j;

	for(i=0;i < 10;i++) {
		for(j=0;j < 5000000;j++) multi(i,j);
		for(j=1;j < 10000001;j++) div(i, j);
	}
}

float multi(int i, int j)
{
	return (float)((float)i * (float)j);
}

float div(int i, int j)
{
	return (float)((float)i / (float)j);
}
