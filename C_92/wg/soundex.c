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
#ifdef MSDOS
#include <io.h>
#endif
#include <ctype.h>
#include <assert.h>

#ifdef SPARC
static const char cFileID[] = "%W%:%P%	%G% %U%";
#endif

#ifdef MSDOS
unsigned short sndxCalc(unsigned char * s)
#else
unsigned short sndxCalc(s)
unsigned char * s;
#endif
   {
   /* Calculate a hash code given a string */
   /* use this coding scheme when SOUNDEX is specified */
   /* For long hash codes, this can be called twice, beginning with char 5 */
   /* Use a pseudo-SOUNDEX coding scheme. */


register unsigned long Hkey;
register unsigned long Code;
short i,j, len, digits, DiscardFlag;
unsigned short OldCode;
short ch;
short k = 1;

/* len = pStrLen(s); */
len = strlen(s);
Hkey = 0;

/* test to see if string begins with a numeric */
if (!isalpha(s[0]))
   { /* not an alpha means either a number or wierd character */
   /* use a randomizing hashing function --- set bit zero to 1 */
   Hkey = s[len-1] * len;
   for (i = len-1; i >= 0; i--)
      {
      j = i + 1;
      Hkey = Hkey * j;
      Hkey = Hkey + (s[i] * j);
      } /* end for */

   /* now set high order bit to one */
   Hkey = Hkey | 0x8000;
   return(Hkey);
   }

   /* Hash code is developed as follows:
   ** numerics: 1 + random code
   ** alphas:
   ** bit 0 = 0 (high order bit)
   **	 bits 1-5: initial character code, developed as in table
   **	 bits 6-8: second character of code (classes 1-6 + 7 for other)
   **	 bits 9-11: third character of code
   **	 bits 12-14: fourth character of code
   **	 bit 15: unused (set to zero)
   */
    ch = toupper(s[0]);
    switch (ch)
       {
       /* SOUNDEX dropped characters */
       case 'A': Code = 0; break;
       case 'E': Code = 1; break;
       case 'I': Code = 2; break;
       case 'U': Code = 3; break;
       case 'Y': Code = 4; break;
       case 'O': Code = 5; break;
       case 'H': Code = 6; break;
       case 'W': Code = 7; break;
       /* Soundex class 1 */
       case 'B': Code = 8; break;
       case 'P': Code = 9; break;
       case 'V': Code = 10; break;
       case 'F': Code = 11; break;
       /* Soundex class 3 */
       case 'D': Code = 12; break;
       case 'T': Code = 13; break;
       /* SOUNDEX Class 5 */
       case 'M': Code = 14; break;
       case 'N': Code = 15; break;
	/* SOUNDEX Class 2 */
       case 'C': Code = 16; break;
       case 'S': Code = 17; break;
       case 'Z': Code = 18; break;
       case 'K': Code = 19; break;
       case 'G': Code = 20; break;
       case 'J': Code = 21; break;
       case 'Q': Code = 22; break;
       case 'X': Code = 23; break;
       /* SOUNDEX Class 4 */
       case 'L': Code = 24; break;
       /* SOUNDEX Class 6 */
       case 'R': Code = 25; break;
       default:
	  Code = 26;
       } /* end switch */

    /* Shift the Code to the left */
    Hkey = Code << 20;

   /* now compute the remaining three characters of the code */
   i = 0;
   digits = 0;
   OldCode = 0;
   do
       {
       if (i >= len || digits == 6)
	  {
	  return(Hkey);
	  }
       DiscardFlag = 0;
       ch = toupper(s[i]);
       switch (ch)
	  {
	  case 'A':
	  case 'E':
	  case 'H':
	  case 'I':
	  case 'O':
	  case 'U':
	  case 'W':
	  case 'Y':
	     DiscardFlag = 1;
	     Code = 8;
	     break;

	  case 'B':
	  case 'F':
	  case 'P':
	  case 'V':
	     Code = 1;
	     break;

	  case 'C':
	  case 'G':
	  case 'J':
	  case 'K':
	  case 'Q':
	  case 'S':
	  case 'X':
	  case 'Z':
	     Code = 2;
	     break;

	  case 'D':
	  case 'T':
	     Code = 3;
	     break;

	  case 'L':
	     Code = 4;
	     break;

	  case 'M':
	  case 'N':
	     Code = 5;
	     break;

	  case 'R':
	     Code = 6;
	     break;

	  case '0':
	     Code = 0;
	  default:
	     Code = 7;
	  } /* end switch */

       if (i)
	  {
	  if (OldCode == Code)
	     {
	     DiscardFlag = 1;
	     }
	  if (!DiscardFlag)
	     {
	     Hkey = Hkey | Code << (14 - (digits * 3));
	     digits++;
	     } /* end no discard */
	  } /* end if i */
       OldCode = Code;
       i++;
       } while(k); /* do forever */
} /* end sndxCalc */

#define BITS_IN_LONG 32

/*
Returns a weight indicating to what degree s1 and s2 sound alike. The higher the
weight the more the strings sound alike. The minimum weight is one and the
maximum weight is sixteen.
*/
int comp(s1,s2)
    char* s1;
    char* s2;
{
    int num;
    int i;
    unsigned short 	mask, v1, v2, h1, h2;
	float			value, expected = 32.0, found;
    
    h1 = sndxCalc(s1);
    h2 = sndxCalc(s2);
    
    num = 0;
    for(i = BITS_IN_LONG - 1; i >= 0; i--)
    {
        mask = 1 << i;
        v1 = h1 & mask;
        v2 = h2 & mask;
        if(v1 == v2)
            num++;
        else
            break;
    }

	found = num;
	value = found/expected;
	num = value * 100; 
    return num;
}

/* end of t_str.c */
