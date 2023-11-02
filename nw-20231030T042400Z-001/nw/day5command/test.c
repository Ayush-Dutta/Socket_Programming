#include <stdio.h>

int main ()
{
	char buff[128]="date>abc";
	int p=system(buff);
	printf("\np=%d",p);
}
