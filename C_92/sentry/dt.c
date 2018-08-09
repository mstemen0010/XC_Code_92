#include<stdio.h>
#include<stdlib.h>
#include<time.h>


char    date[BUFSIZ];

main()
{
strcpy (date, ctime());
printf("%s", date);
}

