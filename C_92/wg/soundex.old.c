/*
**
**
**	File: %M%
**	Created on:Tue May 11 12:38:06 EDT 1993
**
**	The use, disclosure, reproduction, modification, transfer, or
**	transmittal of this work for any purpose in any form or by
**	any means without the written permission of United Parcel
**	Service is strictly prohibited.
**
**	Confidential, Unpublished Property of United Parcel Service.
**	Use and Distribution Limited Solely to Authorized Personnel.
**
**	Copyright 1993 United Parcel Service of America, Inc.
**	All Rights Reserved.
**	
**	Purpose: 
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char * sndxCalc(char * s, int length);

int comp(char *s1,char *s2);


char  *
sndxCalc( char * s , int length)
{
   /* Calculate a hash code given a string */
   /* use this coding scheme when SOUNDEX is specified */
   /* For long hash codes, this can be called twice, beginning with char 5 */
   /* Use a pseudo-SOUNDEX coding scheme. */


unsigned long i,j, len, digits, DiscardFlag;
short ch;
short k = 1;
unsigned long	hKey;
char	hCode[BUFSIZ];
char	*Code;

/* len = pStrLen(s); */

len = strlen(s);

	strcpy(hCode, "");


       ch = toupper(s[0]);
       switch (ch)
      {  
		
      case 'A':
         strcat(hCode, "1*");
         break;
		
      case 'E':
      case 'I':
         strcat(hCode, "2*");
         break;
      case 'O':
      case 'Y':
      case 'U':
         strcat(hCode, "3*");
         break;

      case 'H':
         strcat(hCode, "4*");
         break;
      case 'W':
         strcat(hCode, "5*");
         break;
 
      case 'B':
      case 'V':
         strcat(hCode, "6*");
      case 'F':
      case 'P':
         strcat(hCode, "7*");
         break;
 
      case 'C':
      case 'G':
      case 'S':
      case 'Z':
      case 'X':
         strcat(hCode, "8*");
         break;

      case 'J':
      case 'K':
      case 'Q':
         strcat(hCode, "9*");
         break;
 
      case 'D':
      case 'T':
         strcat(hCode, "10");
         break;
      case 'L':
      case 'M':
      case 'N':
         strcat(hCode, "11");
         break;
 
      case 'R':
         strcat(hCode, "12");
         break;
 
      case '0':
         strcat(hCode, "13");
         break;
      default:
         break;
      } /* end switch */
         

   for (i = 1; i < length ; i++) {
       DiscardFlag = 0;
       ch = toupper(s[i]);
       switch (ch)
	  {
	  case 'H':
	  case 'E':
	  case 'I':
	     break;
	  case 'W':
	  case 'Y':
	     strcat(hCode, "8");
	     break;

	  case 'B':
	  case 'F':
	  case 'P':
	  case 'V':
	     strcat(hCode, "1");
	     break;

	  case 'C':
	  case 'G':
	  case 'J':
	  case 'K':
	  case 'Q':
	  case 'S':
	  case 'X':
	  case 'Z':
	     strcat(hCode, "2");
	     break;

	  case 'D':
	  case 'T':
	     strcat(hCode, "3");
	     break;

	  case 'L':
	     strcat(hCode, "4");
	     break;

	  case 'M':
	  case 'N':
	     strcat(hCode, "5");
	     break;

	  case 'R':
	     strcat(hCode, "6");
	     break;

	  case 'O':
	  case 'A':
	  case 'U':
	  case '0':
	     strcat(hCode, "7");
	     break;
	  default:
	     break;
	  } /* end switch */

  } /* end for */ 
  Code = hCode;
  return(Code);
} /* end sndxCalc */



int comp(s1,s2)
    char* s1;
    char* s2;
{
	char *t1, *t2;
	char *save1 = " ", *save2 = " ";
	char h1[BUFSIZ], h2[BUFSIZ];
    int num, weight;
	int oldLen1, oldLen2, wordlen, letterdiff;
	int newLen1, newLen2;
    int i, similarities;
	float  value, lenValue, ssave, lsave;
	oldLen1 = strlen(s1);
	oldLen2 = strlen(s2);
	
	save1 = &s1[0];
	save2 = &s2[0];


	if (oldLen1 > oldLen2)  {
		similarities = oldLen1;
		wordlen = oldLen1;
	}
	else {
		similarities = oldLen2;
		wordlen = oldLen2;
	}

    t1 = sndxCalc(s1, wordlen);
	strcpy (h1, t1);
    t2 = sndxCalc(s2, wordlen);
	strcpy (h2, t2);

	/*
	fprintf (stdout, "match: %s/%s found: %s/%s \n", save1, h1, save2, h2);
	fflush(stdout);
	*/

    newLen1 = strlen(h1);
    newLen2 = strlen(h2);


    if (newLen1 > newLen2)  {
        similarities = newLen1;
        wordlen = newLen1;
    }
    else {
        similarities = newLen2;
        wordlen = newLen2;
    } 

	for (i = 0; i < wordlen; i++) {
		if ( strlen(h1) > strlen(h2)) {
			if (i < strlen(h2)) {
				if (h1[i] != h2[i])
					similarities--;
			}
			else
				similarities--;
		}
		else {
			if (i < strlen(h1)) {
				if (h1[i] != h2[i])
					similarities--;
			}
			else
				similarities--;
		}
	}
	ssave = oldLen1;
	lsave = oldLen2;

    /* no solutions half the size of the orginal string */
	if (oldLen1 > oldLen2)
		lenValue = (abs(oldLen1/oldLen2));
	else
		lenValue = (abs(oldLen2/oldLen1));

	if (lenValue >= 2 )
		wordlen = 0;

	if (wordlen > 0){
		ssave = similarities;
		lsave = wordlen;
		value = ssave / lsave;
		num = value * 100;
	}
	else	
		num = 0;

    return (num);
}

/* end of t_str.c */
