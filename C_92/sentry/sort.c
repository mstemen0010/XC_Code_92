/*
** File: ptxview.c SCCS 2.8 - 1/6/94
** Author:   Matthew Stemen 
**
** Created:  04 Jan 1993 
** Edited:
**
**
** Purpose: Allows user to search company phone list and to keep a
**          personal phone list.
**  
*/

#include "sort.h"




void
sort_file (char infilename[BUFSIZ], int lines)
{
	char	messstr[BUFSIZ];
	char 	**lineptrs = (char **)malloc(lines*sizeof(char *));
	char 	buff[BUFSIZ];
	char 	*linebuff;
	char                cmd[40];
	int		i = 0, k, len_str;
	FILE                *infp, *outfp;
	
	

	if ((infp = fopen (infilename, "r")) == NULL)
    {
		fprintf(stdout, "Unable to open in file for sort");
		fflush (stdout);
    }
    else {
    	if ((outfp = fopen (TEMPSORTFILE, "w")) == NULL)
     	 {
			fprintf(stdout, "Unable to open TEMP file for sort");
			fflush (stdout);
     	 } 
    	else {
				fseek(infp, 0, 0);
				fseek (infp, 0L, 0L);
      			while(fgets (buff, MAXBUF, infp) != NULL) {
					if (buff[0] != '\n') {
						len_str = strlen(buff);
						lineptrs[i] = (char *)malloc (len_str + 1 * sizeof(char));
						strcpy(lineptrs[i], buff);
						i++;
					}		
				}
				qsort(lineptrs, i, sizeof(char **), stsrt);
        		for (k = 0; k < i; k++) {
	  				fputs(lineptrs[k], outfp);
					free(lineptrs[k]); 
				}
    	  		fclose (infp);
    	  		fclose (outfp);
    	  		strcpy (cmd, "/bin/cp ");
    	  		strcat (cmd, TEMPSORTFILE);
    	  		strcat (cmd, " ");
    	  		strcat (cmd, infilename);
    	  		system (cmd);
				unlink(TEMPSORTFILE);
		}
	free(lineptrs);	
	}
						
}
    
int
stsrt(const void *ptra, const void *ptrb)
{
 		return(strcmp(*((char **)ptra),*((char **) ptrb))); 
#if 0
		if (*ptra < *ptrb) 
				return(*ptrb);
		else if (*ptra > *ptrb) 
				return(*ptra);
#endif
}
/* 
void 
stsrt(char **strings, int num)
{
	char 		*temp;
	int			top, seek;
        
	for (top = 0; top < num; top++)
		for (seek = top + 1; seek < num; seek++)
			if (strcmp(strings[top], strings[seek]) > 0)
			{
				temp = strings[top];
				strings[top] = strings[seek];
				strings[seek] = temp;
			}
		
}

*/

