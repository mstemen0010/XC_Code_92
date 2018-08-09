/*
** File: genfunct.c SCCS 1.1 - 5/5/93
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
#include "genfunct.h"

 
int
readfile (char file[60], char matchword[100], int match_type)
{
  FILE                  *fp, *outfp;
  char                  tempword[BUFSIZ], line[BUFSIZ],
                        templine[BUFSIZ];
  int					openflag = 1, companyflag = 0;
  int					num = 0;
  int					temp_word_len = 0;
        
        
  max_word_len = 0;
  strcpy (num_lines_found, "");
  if ((fp = fopen (file, "r")) == NULL) 
    {
      notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error opening file:", file,
                                                " Try again", NULL,
                     NULL);
	  openflag = 0;
    }
	if (openflag) {
         
      if ((outfp = fopen (TEMPFILE, "w")) == NULL) 
        {
          	printf ("error opening TEMPFILE \n" ); 
      		notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", TEMPFILE,
                                                " Unable to search...", NULL,
                     NULL);
        }
      fseek (fp, 0L, 0L);
	  strcpy (line, "");
	  if (match_type == 0) { /* exact match */
      	while(fscanf (fp, "%s\n", line) == 1)
      		{
          		if (strcmp(line, matchword) == 0) {
					writeline(outfp, line);
					num++;
					temp_word_len = strlen(line);
					if (temp_word_len > max_word_len)
						max_word_len = temp_word_len;
				}

      	}
	}
	else {
      	while(fscanf (fp, "%s\n", line) == 1)
      		{
          		if (strstr(line, matchword) != NULL) {
					writeline(outfp, line);
					num++;
					temp_word_len = strlen(line);
					if (temp_word_len > max_word_len)
						max_word_len = temp_word_len;
				}

      	}
            
	}
            
      fclose(fp);
      fclose(outfp);
	  if (num == 1)
	  	sprintf (num_lines_found, "%d : match found", num);
	  else
	  	sprintf (num_lines_found, "%d : matches found", num);
	}
	return(num);
}

void
readfile_soundex (char file[60], char matchword[100], int tol)
{
  FILE                  *fp1, *fp2, *fp3;
  char                  tempword[BUFSIZ], line[BUFSIZ],
                        templine[BUFSIZ];
  int					openflag = 1, companyflag = 0;
  int 					weightnum = 0;
  char                  matchsub[BUFSIZ], linesub[BUFSIZ], buf[BUFSIZ];
  char                  *matchptr, *lineptr;
  int					i = 0;
  int					shortwordflag = 0;
  int					num = 0, index = 0;
  int					temp_word_len = 0;
        
        
  max_word_len = 0;


  strcpy (num_lines_found, "");
  if (strlen(matchword) >= 5) 
  	matchptr = &matchword[4];
  else
	shortwordflag = 1;
	
  if ((fp1 = fopen (file, "r")) == NULL) 
    {
      notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error opening file:", file,
                                                " Try again", NULL,
                     NULL);
	  openflag = 0;
    }
  if ((fp2 = fopen (TEMPSORT, "w")) == NULL) 
    {
      notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error opening file:", file,
                                                " Try again", NULL,
                     NULL);
	  openflag = 0;
    }
	if (openflag) {
         
      if ((fp3 = fopen (TEMPFILE, "w")) == NULL) 
        {
          /*	printf ("error opening TEMPFILE \n" ); */
      		notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", TEMPFILE,
                                                " Unable to search...", NULL,
                     NULL);
        }
      fseek (fp1, 0L, 0L);
	  strcpy (line, "");
      while(fscanf (fp1, "%s\n", line) == 1)
      {
  			weightnum = 0;
			weightnum = comp(line, matchword);
			if (weightnum == 16 ) {
				if (strlen(line) >= strlen(matchword))
					writeline(fp2, line);
			}
				
			
      }
            
      fclose(fp1);
      fclose(fp2);

 	  if ((fp2 = fopen (TEMPSORT, "r")) == NULL) 
      {
      		notice_prompt (panel, NULL,
            	NOTICE_NO_BEEPING,         TRUE,
                NOTICE_MESSAGE_STRINGS,    "Error opening file:", file,
                " Try again", NULL,
                NULL);
	  		openflag = 0;
   	  }

	  if (shortwordflag == 0){
	  		index = 16;
	  		while (index != 0) {
      			fseek (fp2, 0L, 0L);
      			while(fscanf (fp2, "%s\n", line) == 1)
      			{
						if (strlen(line) >= 5){
  							weightnum = 0;
  							lineptr = &line[4];
							weightnum = comp(lineptr, matchptr);
							if (weightnum == index && weightnum >= tol ) {
								sprintf(buf, "%s - %d", line, weightnum);
								writeline(fp3, line);
								num++;
								temp_word_len = strlen(line);
								if (temp_word_len > max_word_len)
									max_word_len = temp_word_len;
							}
						}
			
				}
	  		index--;
      		}

	  }
	  else {
      		fseek (fp2, 0L, 0L);
      		while(fscanf (fp2, "%s\n", line) == 1) {
				writeline(fp3, line);
				num++;
			}
	  }
	

      fclose(fp2);
      fclose(fp3);

	  if (num == 1)
	  	sprintf (num_lines_found, "%d : match found", num);
	  else
	  	sprintf (num_lines_found, "%d : matches found", num);
	}
}

void
batchreadfile (char file[60], char matchword[100])
{
  char 					cmd[20];
  FILE                  *fp, *outfp;
  char                  tempword[BUFSIZ], line[BUFSIZ],
                        templine[BUFSIZ], outmessage[BUFSIZ];
  int                   openflag = 1, companyflag = 0;
  int					matchflag = 0;

  strcpy (line, "");
  strcpy (tempword, matchword);
  if (strstr(file, "toolset/bin/phones") != NULL)
    companyflag = 1;

  uppercase (tempword);

  if ((fp = fopen (file, "r")) == NULL)
    {
      fprintf ( stderr, "Error opening file: for read\n", file);  
	  fflush (stdout);
      openflag = 0;
    }
    if (openflag) {
		writeline(stdout, "");
		writeline(stdout, "");

      fseek (fp, 0L, 0L);
      while(fgets (line, MAXBUF, fp) != NULL)
      {
         	strcpy(templine, line);
          	uppercase(templine);
          	if (strstr(templine, tempword) != NULL)
            {
				matchflag = 1;
              	/* line[strlen(line) - 1] = '\0'; */
              	if ( iscntrl(line[strlen(line) -2]) )
                	line[strlen(line ) -2 ] = '\0';
              	if (companyflag) {
                	if (isdigit(line[1]))
                    	writeline(stdout, line);
              	}  
              	else
                	writeline(stdout, line);
            }
      }
 
	  if (matchflag == 0) {
			strcpy (outmessage, "No match found for: \"");
			strcat (outmessage, matchword); 
			strcat (outmessage, "\" in file ");
			strcat (outmessage, file); 
			writeline(stdout, outmessage);
	  }
      fclose(fp);
    }
}           
 
void
writeline (FILE *fp, char *str) 
{
  int                   pipeflag = 0, 
                        derlimcnt = 0;

  while (*str != '\0') 
    {
     	putc(*str++, fp);
    }
  putc('\n',fp);
}    

void 
uppercase (char *str)
{
  while (*str != '\0')
    {
      *str = toupper(*str);
      str++;
    }
}


