#include<stdio.h>
#include<utmp.h>

struct utmp ulist;
char    ilist[100][BUFSIZ];
FILE 	*fp;
int		i = 0, j;

main()
{
	if ((fp = fopen("/etc/utmp", "r")) == NULL)
		printf("Unable to open file");

	while ((fread(&ulist, sizeof(ulist), 1, fp)) != 0) {
		if ((strcmp(ulist.ut_name, "")) != 0){
			strcat(ilist[i], ulist.ut_name);
			if ((strcmp(ulist.ut_host, "")) != 0){
				strcat(ilist[i], "@");
				strcat(ilist[i], ulist.ut_host);
			}
			i++;
		}
	}
	fclose(fp);
	for (j = 0; j <= i; j++)
		printf("%s\n", ilist[j]); 
} 

