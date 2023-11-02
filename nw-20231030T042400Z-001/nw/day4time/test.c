#include <stdio.h>
#include <time.h>

int main ()
{
	int year;
	time_t t=time(NULL);
	printf("%ld", t);
	year=(4*(t/126230400));	//365*4*86400   +86400
	t=t%(year*126230400/4);
	year+=1970;
	year+=t/31536000;
	printf("\nt=%ld", t);		//365*86400
	printf("\n%d",year);
	
}
