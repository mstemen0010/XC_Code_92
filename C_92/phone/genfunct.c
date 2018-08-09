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

char	*delimit = " ";

int
readfile (char file[60], char matchword[100])
{
  FILE                  *fp, *outfp;
  char                  tempword[BUFSIZ], line[BUFSIZ], number[BUFSIZ], templine[BUFSIZ];
  int					openflag = 1, companyflag = 0;
  int					num_lines = 0, isNotNumber = FALSE, i;
  char					*token;
        
  strcpy (line, "");
  strcpy (tempword, matchword);
  if (strstr(file, "toolset/bin/phones") != NULL){
	companyflag = 1;
	delimit = " ";
  }
  else
	delimit = "~";

  uppercase (tempword);
        
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
          /*	printf ("error opening TEMPFILE \n" ); */
      		notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", TEMPFILE,
                                                " Unable to search...", NULL,
                     NULL);
        }
      rmtempfileflag = 1; 
      fseek (fp, 0L, 0L);
      while(fgets (line, MAXBUF, fp) != NULL)
        {
		  isNotNumber = FALSE;
          strcpy(templine, line);
          uppercase(templine);
          if (strstr(templine, tempword) != NULL) {
              /* line[strlen(line) - 1] = '\0'; */
              if ( iscntrl(line[strlen(line) -2]) )
				  line[strlen(line ) -2 ] = '\0'; 
			  if (companyflag) {
				 strcpy(templine, line);
				 if ((token = strtok (templine, delimit )) != NULL) {
					strcpy(number, token);
					for (i = 0; i < strlen(number); i++) {
						if (isdigit(number[i]) == 0)
							isNotNumber = TRUE;
					}
					if (isNotNumber == FALSE && line[0] != ' '){
              			writeline(outfp, line);
	                	num_lines++;
                 	} 
				}
			  }
			  else {
				writeline(outfp, line);
	            num_lines++;
			  }
            }
        }
            
      fclose(fp);
      fclose(outfp);
	}
    return(num_lines);
}
 

int
readfile_soundex (char file[60], char matchword[100], int tol)
{
  FILE                  *fpDataIn, *fpSort, *fpDataOut, *fpUnique;
  char					*noDoubles = " ";
  char					*alphaStr = " ";
  char					deAlphaStr[BUFSIZ] = " ";
  char					*hiLight = " ";
  char                  number[BUFSIZ], tempword[BUFSIZ], line[BUFSIZ], templine[BUFSIZ];
  char					outline[BUFSIZ];
  char                  matchsub[BUFSIZ], linesub[BUFSIZ], buf[BUFSIZ];
  char					percentStr[BUFSIZ];
  char					candidate[BUFSIZ] = " ";
  int					openflag = 1, companyflag = 0;
  int 					weightnum = 0;
  char                  matchptr[BUFSIZ] = " ", *lineptr;
  char					*token = " ";
  char 					cmd[BUFSIZ];
  int					i = 0, match = FALSE;
  int					shortword = FALSE;
  int					num = 0, index = 0;
  int					temp_word_len = 0;
  int					num_lines = 0, isNumber = FALSE;
  int					ntol;
  int					foundPercent = FALSE;
  int					pieceNum = 1, count = 0;
  int					fieldValue;
  int					tokenCount;

        
        
  max_word_len = 0;
  strcpy (matchptr, "");
  alphaStr = alphatize_string(matchword);
  strcpy(deAlphaStr, alphaStr);
  noDoubles = remove_double_con(deAlphaStr);
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
          /*	printf ("error opening TEMPFILE \n" ); */
      		notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", TEMPFILE,
                                                " Unable to search...", NULL,
                     NULL);
      }
      fseek (fpDataIn, 0L, 0L);
	  strcpy (line, "");
      fieldValue = (int)xv_get(soundex_field_toggle, PANEL_VALUE);
	  if (fieldValue == 2 || !companyflag)
		fieldValue = 10;

	while(fgets (line, MAXBUF, fpDataIn) != NULL) {
            tokenCount = 0;
			count = 2;
			pieceNum = 2;
			match = FALSE;
			foundPercent = FALSE;
          	isNumber = FALSE;
			alphaStr = alphatize_string(line);
  			strcpy(deAlphaStr, alphaStr);
  			noDoubles = remove_double_con(deAlphaStr);
			token = strtok(noDoubles, delimit);
			while (token != NULL  && tokenCount <= fieldValue) {
				if (tokenCount == fieldValue || fieldValue == 10){
  					weightnum = 0;
					weightnum = comp(matchptr, token);

					if (weightnum >= tol ) {
						if (! foundPercent ) {
							sprintf (percentStr, "%3d%% - ", weightnum);
							foundPercent = TRUE;
							strcpy(candidate, token);
							pieceNum = count;
						}
						match = TRUE;
					}
				}
				token = strtok(NULL, delimit);
				count++;
				tokenCount++;
			}


			if (match) {
              		if ( iscntrl(line[strlen(line) -2]) )
						line[strlen(line ) -2 ] = '\0'; 
					hiLight = hilight_match(line, pieceNum);
					sprintf(outline, "%s %s", percentStr, hiLight);
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
	return(num_lines);
}

int
batchreadfile_soundex (char file[60], char matchword[100], int tol, int fieldValue)
{
  FILE                  *fpDataIn, *fpSort, *fpDataOut, *fpUnique;
  char                  *noDoubles = " ";
  char                  *alphaStr = " ";
  char                  deAlphaStr[BUFSIZ] = " ";
  char                  *hiLight = " ";
  char                  number[BUFSIZ], tempword[BUFSIZ], line[BUFSIZ], templine[BUFSIZ];
  char                  outline[BUFSIZ];
  char                  outmessage[BUFSIZ];
  char                  matchsub[BUFSIZ], linesub[BUFSIZ], buf[BUFSIZ];
  char                  percentStr[BUFSIZ];
  char                  candidate[BUFSIZ] = " ";
  int                   openflag = 1, companyflag = 0;
  int                   weightnum = 0;
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
  int                   pieceNum = 1, count = 0;
  int                   tokenCount;
 
 
 
  max_word_len = 0;
  strcpy (matchptr, "");
  alphaStr = alphatize_string(matchword);
  strcpy(deAlphaStr, alphaStr);
  noDoubles = remove_double_con(deAlphaStr);
  strcpy (matchptr, noDoubles);
 
  strcpy (num_lines_found, "");
  if (strstr(file, "toolset/bin/phones") != NULL)
    companyflag = 1;
   
  /* open database file */

  if ((fpDataIn = fopen (file, "r")) == NULL)
    {
      fprintf ( stderr, "Error opening file %s: for read\n", file);
      fflush (stdout);
	  exit(1);
    }

 
    if ((fpDataOut = fopen (TEMPFILE, "w")) == NULL) {
      	fprintf ( stderr, "Error opening TEMPFILE: for write\n");
      	fflush (stdout);
	  	exit(1);
    }    

      fseek (fpDataIn, 0L, 0L);
      writeline(stdout, "");
      writeline(stdout, "");
      strcpy (line, "");
      if (fieldValue == 2 || !companyflag)
        fieldValue = 10;

    while(fgets (line, MAXBUF, fpDataIn) != NULL) {
            tokenCount = 0;
            count = 2;
            pieceNum = 2;
            match = FALSE;
            foundPercent = FALSE;
            isNumber = FALSE;
            alphaStr = alphatize_string(line);
            strcpy(deAlphaStr, alphaStr);
            noDoubles = remove_double_con(deAlphaStr);
            token = strtok(noDoubles, delimit);
            while (token != NULL  && tokenCount <= fieldValue) {
                if (tokenCount == fieldValue || fieldValue == 10){
                    weightnum = 0;
                    weightnum = comp(matchptr, token);
 
                    if (weightnum >= tol ) {
                        if (! foundPercent ) {
                            sprintf (percentStr, "%3d%% - ", weightnum);
                            foundPercent = TRUE;
                            strcpy(candidate, token);
                            pieceNum = count;
                        }
                        match = TRUE;
                    }
                }
                token = strtok(NULL, delimit);
                count++;
                tokenCount++;
            }
 
 
            if (match) {
                    if ( iscntrl(line[strlen(line) -2]) )
                        line[strlen(line ) -2 ] = '\0';
                    hiLight = hilight_match(line, pieceNum);
                    sprintf(outline, "%s %s", percentStr, hiLight);
                    if (companyflag) {
                        strcpy(templine, line);
                        if (isdigit(templine[0]))
                            isNumber = TRUE;
                        if (isNumber && line[0] != ' '){
                            writeline(stdout, outline);
                            num_lines++;
                        }
                    }    
                    else {
                        writeline(stdout, outline);
                        num_lines++;
                    }
            }

    }
    fclose(fpDataIn);
    fclose(fpDataOut);
    if (num_lines == 0) {
    	strcpy (outmessage, "No soundex match found for: \"");
        strcat (outmessage, matchword);
        strcat (outmessage, "\" in file ");
        strcat (outmessage, file);
        writeline(stdout, outmessage);
    }
    unlink(TEMPSORT);
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
      if (*str != '~' )
        {
          if (*str != '|')
            {
              if (derlimcnt == 3)
                {
                  fputs("Ext: ",fp);
                  putc(*str++, fp);
                  derlimcnt = 10;
                }
              else
                putc(*str++, fp);
            }
          else
            { 
              pipeflag++;
              putc('\n', fp);
              if (pipeflag == 1)
                fputs("Address: ",fp);
              if (pipeflag == 2)
                fputs("Notes: ",fp);
              *str++;
            }
        }
      else
        {
          derlimcnt++;
          *str--;
          putc(' ',fp);
          *str++;
          *str++;
        }
    }
	*str--;
	if (*str != '\n')
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
getprint_list(char *rcprinter)
{
    FILE    *fp;
    char    plist[BUFSIZ * 2];
    char    token[BUFSIZ];
    int     i;

    if ((fp = fopen("/etc/printcap", "r")) == NULL)
        printf("Unable to open printcap");
    else {
        while(fgets (printer, BUFSIZ, fp) != NULL && printer[0] != '\n'){
            if (isdigit(printer[0])){
                strcpy(token, strtok(printer, "|"));
                strcat(printlist[prcount], token);
                if (strcmp (rcprinter, printer) == 0){
                    prflag = prcount;
                }
                prcount ++;
            }
        }
    prcount --;
    fclose(fp);
    strcat(printlist[prcount + 1], "File");
    for (i = 0; i <= prcount + 1  ; i++)
        xv_set(prop_print,
            PANEL_CHOICE_STRING, i, printlist[i],
            NULL);
    }
    xv_set(prop_print, PANEL_VALUE, prflag, NULL);
    strcpy (printer, printlist[prflag]);
    window_fit (proppanel);
    window_fit (propframe);
   
}

char *
alphatize_string(char *str)
{
	char    returnStr[BUFSIZ] = " ";
    char    *tempstr = " ";
    int     i, cnt = 0, len;
 
    len = strlen(str);
    tempstr = &str[0];
    strcpy (returnStr, "");

	for (i = 0; i < len; i++){
		if (isalpha(*tempstr) || isspace(*tempstr) || *tempstr == '\\n') {
			if (*tempstr != '-' || *tempstr != '\'') {
				returnStr[cnt] = *tempstr;
				cnt++;
				tempstr++;	
			}
			else
				tempstr++;	
		}
		else
			tempstr++;	
	}

	return(returnStr);
				

}


char *
remove_double_con(char *str)
{
	char	returnStr[BUFSIZ] = " ";
	char	*oldLetter = " ";
	char    *tempstr = " ";
	int		i, cnt = 0, len;

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


char *
hilight_match(char *line, int pieceNum)
{
	char *token;
	char    *tempstr = " ";
	char	*substr = " ";
	char	returnStr[BUFSIZ] = " ";
	char    templine[BUFSIZ] = " ";
	int	 bpos, epos, cnt = 0, i, len1 = 0, len2 = 0, len3 = 0;


	tempstr = &line[0];
	strcpy (templine, line);
	token = strtok(templine, delimit);
	strcpy (returnStr, "");
	if (pieceNum == 1) {
		bpos = 0;
		epos = strlen(token);
	}
		
	else {
		for (i = 2; i <= pieceNum; i++) {
			token = strtok(NULL, delimit);
			if (token != NULL){
				if ( i == pieceNum ) {
					substr = strstr(line, token);
					len1 = strlen(substr);
					len2 = strlen(line);
					len3= strlen(token);
					bpos = len2 - len1;
					epos = bpos + len3;
				}
			}
		}
	}
	for (i = 0; i <= strlen(line); i++) {
		if (i == bpos) {
			returnStr[cnt++] = '['; 
			returnStr[cnt++] = *tempstr;
		}
		else if (i == epos) {
			returnStr[cnt++] = ']'; 
			returnStr[cnt++] = *tempstr;
		}
		
		else
			returnStr[cnt++] = *tempstr;
		tempstr++;
	}
	/*
	fprintf(stdout, "line: %s\n", returnStr);
	*/
	return(returnStr);
}
