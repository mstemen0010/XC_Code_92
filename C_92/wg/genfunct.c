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

	FILE                  *fpDataIn, *fpSort, *fpDataOut, *fpUnique;
  char                  number[BUFSIZ], tempword[BUFSIZ], line[BUFSIZ], templine[BUFSIZ];
  char                  outline[BUFSIZ];
  char                  matchsub[BUFSIZ], linesub[BUFSIZ], buf[BUFSIZ];
  char                  alphaStr[BUFSIZ], malphaStr[BUFSIZ];
  char                  percentStr[BUFSIZ];
  int                   openflag = 1, companyflag = 0;
  int                   weightnum = 0;
  char                  *noDoubles = " ";
  char                  matchptr[BUFSIZ] = " ", *lineptr;
  char                  *token = " ";
  char                  cmd[BUFSIZ];
  int                   i = 0, match = FALSE;
  int                   shortword = FALSE;
  int                   num = 0, index = 0;
  int                   temp_word_len = 0;
  int                   num_lines = 0, isNumber = FALSE;
  int                   ntol;
  int                   foundPercent = FALSE;

         

  max_word_len = 0;
  strcpy (matchptr, "");
  strcpy(alphaStr, matchword);
  alphatize_string(alphaStr);
  noDoubles = remove_double_con(alphaStr);
  strcpy (matchptr, noDoubles);
 
  strcpy (num_lines_found, "");
  if (strstr(file, "toolset/bin/phones") != NULL)
    companyflag = 1;
    
  /* open database file */
  if ((fpDataIn = fopen (file, "r")) == NULL) {
      notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error opening file:", file,
                                                " Try again", NULL,
                     NULL);
  }
         
      if ((fpDataOut = fopen (TEMPFILE, "w")) == NULL) {
          /*    printf ("error opening TEMPFILE \n" ); */
            notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", TEMPFILE,
                                                " Unable to search...", NULL,
                     NULL);
      }
      fseek (fpDataIn, 0L, 0L);
      strcpy (line, "");
    while(fgets (line, MAXBUF, fpDataIn) != NULL) {
            match = FALSE;
            foundPercent = FALSE;
            isNumber = FALSE;
            strcpy(alphaStr, line);
            alphatize_string(alphaStr);
            noDoubles = remove_double_con(alphaStr);
            token = strtok(noDoubles, " ");
            while (token != NULL ) {
                weightnum = 0;
                weightnum = comp(matchptr, token);
                if (weightnum >= tol ) {
                        if (! foundPercent ) {
                            sprintf (percentStr, "%3d%%   - ", weightnum);
                            foundPercent = TRUE;
                        }
                        match = TRUE;
                }
                token = strtok(NULL, " ");
            }
 
 
            if (match) {
                    if ( iscntrl(line[strlen(line) -2]) )
                        line[strlen(line ) -2 ] = '\0';
                    sprintf(outline, "%s %s", percentStr, line);
                    temp_word_len = strlen(outline);
                    if (temp_word_len > max_word_len)
                    	max_word_len = temp_word_len;
                    if (companyflag) {
                        strcpy(templine, line);
                        if (isdigit(templine[0]))
                            isNumber = TRUE;
                        if (isNumber && line[0] != ' '){
                            writeline(fpDataOut, outline);
                            num_lines++;
                        }
                    }
                    else {
                        writeline(fpDataOut, outline);
                        num_lines++;
                    }
            }
 
    }
    fclose(fpDataIn);
    fclose(fpDataOut);
    sprintf(cmd, "sort -rn %s  > %s", TEMPFILE, TEMPSORT);
    system(cmd);
    sprintf(cmd, "cp %s %s", TEMPSORT, TEMPFILE);
    system(cmd);
    unlink(TEMPSORT);
	if (num == 1)
	  	sprintf (num_lines_found, "%d : match found", num_lines);
	  else
	  	sprintf (num_lines_found, "%d : matches found", num_lines);
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


void
alphatize_string(char *str)
{
  while (*str != '\0')
    {
        if (! (isalpha(*str)) )
            *str = ' ';
      str++;
    }
}
 
char *
remove_double_con(char *str)
{
    char    returnStr[BUFSIZ] = " ";
    char    *oldLetter = " ";
    char    *tempstr = " ";
    int     i, cnt = 0, len;
 
    len = strlen(str);
    tempstr = &str[0];
    strcpy (returnStr, "");
 
    for (i = 0 ; i < len; i++) {
        if (! isspace(*tempstr)) {
            if ( *tempstr != *oldLetter ) {
                returnStr[cnt] = *tempstr;
                cnt++;
            }
        }
        else {
                returnStr[cnt] = ' ';
                cnt++;
        }
        
        
        *oldLetter = *tempstr;
        tempstr++;
    }
    /*
    printf("orgstr: %s newstr: %s\n", str, returnStr);
    */
    return(returnStr);
}
