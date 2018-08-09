/****************************************************************************
*                                                                           *
*                                 TWTSP90.C                                 *
*                                                                           *
*                 Heuristic Dynamic Programming Algorithm                   *
*                   for the Traveling Salesman Problem                      *
*                                                                           *
*                               Written by                                  *
*                           Chryssi Malandraki                              *
*             								    *
*			      modified by 				    *
*			    Anil K. Singh ( 28 to 59 nodes )                *
*                                                                           *
*    Copyright (c) 1990 Roadnet Technologies, Inc. All Rights Reserved.     *
*                                                                           *
*****************************************************************************
+---------------------------------------------------------------------------+
|                              MODIFICATION LOG                             |
|---------------------------------------------------------------------------|
|    Date   | Name |             Modification                               |
|---------------------------------------------------------------------------|
| 11 Apr 90 | ChM  | Source code started.                                   |
|---------------------------------------------------------------------------|
|  8 May 90 | ChM  | Improvements started.  BubbleSort/qsort replaced.      |
|---------------------------------------------------------------------------|
| 13 Jun 90 | AF   | Trace back solution. Include tracer.c file.            |
|---------------------------------------------------------------------------|
|  6 Jul 90 | AF   | Time windows and other options. Include options.c file.|
|---------------------------------------------------------------------------|
| 12 Jul 90 |AF/ChM| Time windows with distance minimization.               |
+---------------------------------------------------------------------------+
| 6th Nov 90| AKS | extend to 59 nodes                                      |
+----------------------------------------------------------------------------
| 7th Jan 91 | aks | started Preedence  and likely Precedence modifications |
+----------------------------------------------------------------------------
+ 4th March  | aks | extend to 90 nodes 
+---------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>     /* for rand(), srand()*/
#include <time.h>       /* for time()         */
#include <search.h>     /* for qsort()        */
#include <malloc.h>
#include <sys/types.h>
#include <sys/timeb.h>

#include <stdtype.h>
#include "selectu16.h"

extern FILE *outData;

#ifndef max
#define max(a,b)	((a) > (b) ? (a) : (b))
#endif



#define INF  32767

/* To recalculate precedence values */

#define HVAL 5000
#define SIZEVAL 5000
#define TNODE 90
#define AVAL	2
#define SVAL	2



/***********************************************************************
*
*	GETK(set)
*	Tells which of the first 7 bits in setlo are on.
*
* 	0x7f (hex) == 0111,1111 (binary)
*
*	usage: bool-val = GETK(U32-set)
*
***********************************************************************/
#define GETK(setlo)	((U16) (setlo & 0x7f))

/**************************************************************************
*
*	SETK(k,set)
*	Will ALTER the value of set.
*	Sets the low 7 bits of setlo (an U32) to k.
*
*	0x80 (hex) == 1000,0000 (binary)
*	0x7f (hex) == 0111,1111
*
*	usage: SETK(k, set)
*	[remember: SETK returns nothing]
*
**************************************************************************/
#define SETK(k, setlo) setlo=(((setlo) & (U32) 0xffffff80l)\
	 | ((U32) (k) & (U32) 0x7f))

/***********************************************************************
*
*	TESTBIT(i, setlo, sethi)
*	Checks to see if the (i+7)-th bit (start count at zero)
*	is on.  sethi's bit count starts where setlo's leaves off.
*
*	usage: bool-val = TESTBIT(i, U32-set, U32-set)
*
************************************************************************/

#define TESTBIT(i, setlo, setmi, sethi) ((i < 26) ? ((U16) (setlo >> ((i) + 6)) & 1)\
				: ((i < 58) ? ((U16) (setmi >> ((i) - 26)) & 1 ) :\
				  ((U16) (sethi >> ((i) - 58)) & 1)))
/*************************************************************************
*
*	SETBIT(i, setlo, setmi, sethi)
*	Will ALTER the value of set.
*	Turns on the (i+7)-th bit (start count at zero).  sethi's bit 
*	count starts where setlo's leaves off.
*
*	usage: SETBIT(i,U32-set, set, U32-set)
*	[remember: SETBIT returns nothing]
*
************************************************************************/
#define alter1(i,setlo) setlo = ((setlo) | ((U32) 1 << ((i) + 6)))
#define alter2(i,setmi) setmi = ((setmi) | ((U32) 1 << ((i) - 26)))
#define alter3(i,sethi) sethi = ((sethi) | ((U32) 1 << ((i) - 58)))
#define SETBIT(i, setlo, setmi, sethi) if (i < (U16) 26) alter1(i,setlo);\
								 else if (i < (U16) 58) alter2(i,setmi);\
								 else alter3(i,sethi) 
											   

void   main(int,char**);
S16    **matrixAlloc(S16, S16);
S16    *arrayAlloc(unsigned);
U32    *arrayU32Alloc(unsigned);
void   printMatrix(S16 **, S16, S16);
void   printIntArray(S32, S16*);
void   printU32Array(S32, S32*);
void   printU90Array(S32, U32*, U32*, U32*);
void   stage1(void);
void   procCost(void);
void   combine1(void);
void   combinek(void);
void   stagek(void);
void   disDuple(void);
void   backDepot(void);
void   printBinary(U32,U32,U32);
S16    maxValue(S32, S16*);
S32    equalCost(S16, S32, S32, S16*);
S32    equalCost1(S16, S32, S32, S16*);
void   Uinsitu(S32, U32 *, U32 *, U32*, S32 *) ;
void   Uinsitu1(S32, U32 *,  S32 *) ;
void   intInsitu(S32, S16*, S16*);
void   insitu3(S32, S16*, S16*, S16*, S16 *);
void   insitu4(S32, S16*, S32*, S16*, S32 *);
void   minSols(void);
void Floyd_sp ( S16 nodes, S16 inf,  S16  **dist, S16  *ServT, S16 **SD);
void bprint (void) ;
void rtime(long *t);

void   U32MaxMin(U32*, S32, S32, U32*, U32*);
void   U32Sort(U32*, S32*, S32, S32, U32, U32);
void   sortThem(void) ;
S16    minValue(S32, S16*);
long   filesize (int fd);

time_t  stime = -1L, etime, t1, t2, t3, t4; /* vars for keeping the time */
      /* time_t is equavalent to long */



S16 nodes, **cost, **travTime, *servTime;
S32 H,SIZE ;
S16 maxCost = INF, nofmaxCost, maxTime = INF, startCost = 0, startTime = 0;
U16 k;

U32 *loSet0h, *loSet1H, *loSet1SIZE, *lotempSet ;
U32 *miSet0h, *miSet1H, *miSet1SIZE, *mitempSet ;
U32 *hiSet0h, *hiSet1H, *hiSet1SIZE, *hitempSet ;

S16 *tCost0H, *tCost1H, *tCost1SIZE;
S16 *tTrav0H, *tTrav1H, *tTrav1SIZE;
S32  *predSIZE, *predH, *best;
S32 *J ;
S16 *J1 ;
S32 indexHC, indexHL, indexS;
S16 nodenum ;
S32 equCost;
S32  endex, I;
U32  *tempSet;

S16 Optimal = 1 ; /* Assume an optimal solution */
char *nfile ;
 /* For updating the precedence table at K*A stage */
 
S16 A = AVAL ;
S16 K = 1 ;

#include "twoption.c"
#include "twtracer.c" 
#include "ddsort90.c"
#include "twprec90.c"

/****************************************************************************
*                                   main
*
* This heuristic algorithm solves the TSP  with hard time windows, with
* minimization of a cost function different than elapsed time using dynamic
* programming.  The algorithm cannot guarantee an optimal solution because
* at each stage only a given number of alternatives is examined.  In the
* presence of time windows, the total cost (distance, etc.) of a tour is
* minimized for a given starting time. 
*
* Command Line
* ------------
* TWTSP90 w filein fileout
*
* Options
* -------
* w	hard time windows
*
* Parameters
* ----------
* nodes  (int) Number of nodes (max = 28, later more).
* H      (int) Number of alternatives retained at one stage (max = ?).
* SIZE   A number usually comparable to H and SIZE >= H.
* k      (U16) Last-visited node in the set of visited nodes.
* maxCost (int) Max value of total cost for retained partial tours.
* indexS (int) The index of the last entry in any array of SIZE.  When
*        the array is filled up indexS = SIZE.
* indexHC (int) The index of the last entry in array ordCostSIZE when used
*        to sort costs. (C for current).
* indexHL (int) The index of the last entry in any array of size H.  When
*        the array is filled up indexHL = H. (L for last).
* equCost (int) The number of elements retained with cost equal to maxCost.
*
* startCost (int) Initial starting cost (travel time); 0 for standard TSP.
*
* **cost (int) Square array of link costs (distances, etc.).
* **travTime (int) Square array of link travel times (including service 
*            times).
* *servTime (int) Array of service times.
*
* Any *Set... is an U32 with the 5 low bits representing the last-visited
*        node k and the other 27 bits representing inclusion or not of
*        the 27 customer nodes.
*
* *Set0H (U32) Array of size H representing the set of included nodes
*              and last visited node for the last completed stage (i-1).
* *Set1H (U32) As *Set0H but for the current stage (i).
* *Set1SIZE (U32) As *Set1H but of size SIZE.
* *tCost0H (int) Array of size H for the total cost of a partial tour
*              for the last completed stage.
* *tCost1H (int) As tCost0H but for the current stage.
* *tCost1SIZE (int) As tCost1H but of size SIZE.
* *tTrav0H (int) Array of size H for the total travel time of a partial
*              tour for the last completed stage.
* *tTrav1H (int) As tTrav0H but for the current stage.
* *tTrav1SIZE (int) As tTrav1H but of size SIZE.
*
* *J  (int) Array of integers of size (SIZE+H) to use for sorting parallel
*         arrays and other temporary storage.
* *predSIZE  (int) Predecesor array of size SIZE holding indices indicating
*         from which alternative on stage i-1 each alternative in stage i
*         comes.
* *predH  (int) Predecesor array of size H holding indices indicating
*         from which alternative on stage i-1 each alternative in stage i
*         comes.
*         At the end of each stage the values of the predH array and in 
*         parallel the values of k are written on disk.
*
****************************************************************************/
/*0000000000000000000

Add a feature that will check if indexHL < H always.  In that case it will 
return a note tha t the solution is optimal.  This is good for very tight
problems.  The variable optimal will be set to 0 or 1.

0000000000000000000000*/

void twtsp_main(int argc, char **argv)

{
   register i;
   
   rtime(&t1) ; /* start accounting for elapsed time */

   nfile = argv[argc-2] ;
   readArgs(argc,argv);
   openFiles
();
   (*readInput)();
   fflush(outFile) ;

	stime = 0 ;
	indexHC = H;
	indexHL = H;
	indexS = SIZE;

	loSet1SIZE = arrayU32Alloc(SIZE);
	loSet0h = arrayU32Alloc(H);  /* Create the Set and tCost arrays */
	loSet1H = arrayU32Alloc(H);
	lotempSet = arrayU32Alloc(H);

	miSet1SIZE = arrayU32Alloc(SIZE);
	miSet0h = arrayU32Alloc(H);  /* Create the Set and tCost arrays */
	miSet1H = arrayU32Alloc(H);
	mitempSet = arrayU32Alloc(H);

/* The change of allocation (max of 8100, or H < H+SIZE is to store LP
   (likely precedence eij) values in this array */

 	J = (S32 *) arrayU32Alloc(max((SIZE +  H),8100)) ;
	J1 = (S16 *)J ;

	hiSet1SIZE = arrayU32Alloc(SIZE);
	for (i=0; i<SIZE; i++)
	{
		loSet1SIZE[i] = miSet1SIZE[i] = hiSet1SIZE[i] = 0;
	}
	hiSet0h = arrayU32Alloc(H);  /* Create the Set and tCost arrays */
	hiSet1H = arrayU32Alloc(H);
	hitempSet = arrayU32Alloc(H);

	tCost1SIZE = arrayAlloc(max(SIZE,8100));
	tTrav1SIZE = arrayAlloc(max(SIZE,8100));
	predSIZE = (S32 *) arrayU32Alloc(SIZE);
	tCost0H = arrayAlloc(H);
	tCost1H = arrayAlloc(max(H,8100));
	tTrav0H = arrayAlloc(H);
	tTrav1H = arrayAlloc(max(H,8100));
	predH = (S32 *) arrayU32Alloc(H);
	best = (S32 *) arrayU32Alloc(nodes);


	rtime(&t1) ;

	pr_build (nodes,pr_qual, (S16) 0 ) ;

	rtime(&t2) ;
	fprintf(outFile,"\nElasped Time for Preprocessing is %ld seconds.\n",t2 - t1) ;
   fflush(outFile) ;

#if DEBUG
	fprintf(outFile,"\n*** Precedence Array **************\n") ;
	printU90Array (nodes,loPreQual,miPreQual,hiPreQual) ;
#endif

	initializeTracer(nodes);

	fprintf(outFile,"\n*** Stage 1 / |S| = 1 *****************************\n");
	fflush (outFile);
	stage1();
	fflush (outFile);

   diskWrite(1,indexHL,predH,loSet0h,J,nodes);
   /* It writes on disk the values of k and predH corresponding to Set0H 
	   and tCost0H/tTrav0H arrays. */

	/* Process all stages. */

   for (i = 2; i < nodes; i++)
	{
		fprintf(outFile,"\n*** Stage %d / |S| = %d *****************************\n",i,i);
		fflush (outFile);

 		/* update the precedence tables */
 
 		if ((i >= (A * K)) && (i <= (nodes - SVAL) )) {
			rtime(&t1) ;
 			pr_build(nodes,pr_qual1,(S16)i) ;
 			K++;
			rtime(&t2) ;
			fprintf(outFile,"\nElasped Time for Updating tables is %ld seconds.\n",t2 - t1) ;
		fflush (outFile);
#if   DEBUG
   	fprintf(outFile,"\n*** Precedence Array *********************\n");
   	printU90Array (nodes,loPreQual,miPreQual,hiPreQual) ;
#endif
 		}
		rtime(&t1);
		stagek();
		rtime(&t2);
		fprintf(outFile,"\nElapsed Time for Stage %d is %ld seconds.\n ", i, t2 - t1);
		fflush (outFile);
		rtime(&t1);
      diskWrite(i,indexHL,predH,loSet0h,J,nodes);
		rtime(&t2);
		fprintf(outFile,"\nElapsed Time for diskWrite is %ld seconds.\n ", t2 - t1);
		fflush (outFile);
	}

	fprintf(outFile,"\n*** Back to Depot **********************************\n");
	backDepot();
	
	/* Find the Min tCost1SIZE 3 times or indexHL times whichever smallest.*/
	/* i.e. no. of best tours to be printed, here it is 3 */

	indexS = (indexHL < 3) ? indexHL : 3;
 	
	minSols();

	fprintf(outFile,"\n********* The Final Tours **********\n");

	/* Backtrack with k and predecessor values from disk to trace back
	   each one of the solution tours. Find last k before depot then get
		parallel pred; find k then parallel pred; ...; find k.  Print
		tours and final tour costs. */

	rtime(&t1);

	traceBack(outFile,nodes,H, indexS,strgFile,strgPositions,tCost1SIZE,tTrav1SIZE);
		
	rtime(&t2);
	fprintf(outFile,"\n\nETime for traceBack tours is %ld seconds.\n ", t2 - t1);

	if (Optimal)
	{
		fprintf(outFile,"\nThe Solution is Optimal\n") ;
		fprintf(outData,"KnownOptimal");
	}
	else
		fprintf(outData,"UnknownOptimal");
	
	rtime(&etime);
	fprintf(outFile,"\nTotal Elapsed Time is %ld seconds.\n ", etime - stime);


	fprintf(outFile,"\n\n\n");
	tw_getpt() ;

	/************************************
	*
	*	save results onto the end of rslt1.txt
	*
	**************************************/
	#if BATCH
	{
		FILE *f;
		char *s = "No Opt " ;
		char *s1 = "Opt " ;
		
		f = fopen("rslt1.txt", "a");
		fprintf(f,"\n%s\t%d\t%d\t%ld\t%s", nfile,
		tCost1SIZE[0],tTrav1SIZE[0],etime-stime,Optimal? s1 : s);
		fclose(f);
	}
	#endif


	/* destroy storage.bin, the tracer file */
        fprintf(outFile, "\nTotal bytes used by 'storage.bin` is %ld\n", filesize (strgFile));
        fflush(outFile);
	close(strgFile);
/*
	strgFile = open("/tmp/storage.bin",(int) O_TRUNC, (int) S_IWRITE);
	close(strgFile);
        fclose (outFile);
 */
	cleanup();
}
/* end of main */

	

cleanup()
/*
	cleanup code 10/28/92 rag 
*/
{
#define matFree(n,M) for (i=0; i<n; i++) free(M[i]); free(M); 

	/* twtsp90.c */
	int i,j;
	free(loSet1SIZE);
	free(loSet0h);
	free(loSet1H);
	free(lotempSet);
	free(miSet1SIZE);
	free(miSet0h);
	free(miSet1H);
	free(mitempSet);
 	free(J);
	free(hiSet1SIZE);
	free(hiSet0h);
	free(hiSet1H);
	free(hitempSet);
	free(tCost1SIZE);
	free(tTrav1SIZE);
	free(predSIZE);
	free(tCost0H);
	free(tCost1H);
	free(tTrav0H);
	free(tTrav1H);
	free(predH);
	free(best);

	/* twoption.c */
	free(in_filename);
	free(outFilename);
	free(servTime);
	for (i=0; i<nodes; i++)
	{
		if (!numwindows[i])
		{
			free(TWs[i]);
			free(TWm[i]);
		}
	}
	free(TWs);
	free(TWm);
	free(numwindows);
	free(numwindowsm);

	matFree(nodes,cost);
	matFree(nodes,travTime);

	/* twprec90.c */
	matFree(nodes,ST);
	free(loPreQual);
	free(miPreQual);
	free(hiPreQual);
/*
	extern int p_lprH;
	free(p_lprH);
	free(p_lprV);
*/

	/* twtracer.c */
	free(strgPositions);
}

/***************************** F I L E S I Z E ********************************
 *
 *  Answer size (in bytes) of file associated with 'fd'.
 *
 *****************************************************************************/
long filesize (int fd)
{
	int	s;
	struct stat status[1];

	s = fstat(fd, status);
	return status[0].st_size;
}

/****************************************************************************
*                              stage1
*
* It processes stage 1.
* It uses global variables.  It should be modified to use handles.
*
* The function does the following:
* It fills up the Set1SIZE and tCost1SIZE/tTrav1SIZE arrays.
* It selects the Hth best total cost value between tCost1SIZE and tCost1H if
* tCost1H already filled before using SELECT.
* It updates the maxCost value.
* It goes over Set1SIZE, Set1H, tCost1SIZE, and tCost1H arrays (if the ..1H
* arrays have already some values) and discards values of cost larger than
* maxCost. If there are more than one entries with total cost equal to
* maxCost, the number retained with total cost equal to maxCost must be the
* same as in the set of H best values.
* It puts the selected values in the Set1H and tCost1H arrays.
* It puts the sorted total costs and corresponding sets in the Set0H
* and tCost0H arrays when all elements in stage 1 have been processed.
*
****************************************************************************/

void stage1()

{
   register i = 0;
	S16 tmpCost, tmpTrav;
	U32 lotmpSet, mitmpSet;
	U32 tmp, hitmpSet ;

	/* we may go thru more than one fill up of SIZE arrays if S is small*/

	tCost1H[0] = INF;    /* First iteration */
	maxCost = INF; 		/* maximum at start, anything less take it */
	
	endex = -1;
	k = 0; 			/* starting from depot */
	nodenum = 1;  /* will visit the node 1 first */

		/* the partial tours will look like this at end:
		   {1},1 ; {2},2 ;  */

	while (nodenum < nodes)
	{
		/* Fill up the Set1SIZE and tCost1SIZE/tTrav1SIZE arrays. */
		/* The ..1SIZE arrays may be filled more than once for stage 1. */

		while (nodenum < nodes && endex + 1 < SIZE)
		{
		   if (!(loPreQual[nodenum] || miPreQual[nodenum] ||  hiPreQual[nodenum])) {
			tmpCost = compCost(startCost, k, nodenum);
			tmpTrav = compTime(startTime, k, nodenum,TWm,numwindowsm);

	/* If this value is less than maxcost, or there was space left in H array
	 from previous iteration so that maxcost can be increased. This may be
	the case if network was sparse or small */

			if ((tmpCost < maxCost || indexHL < H)
				&& tmpCost != INF && tmpTrav != INF)
			{
				endex++;
				tmp = (U32) nodenum & 0x7fff; /* SETBIT needs a U16 */
				lotmpSet = 0l ;
				mitmpSet = 0l ;
				hitmpSet = 0l ;
				SETBIT(tmp, lotmpSet,mitmpSet, hitmpSet ) ;
				SETK(nodenum, lotmpSet) ;
				loSet1SIZE[endex] = lotmpSet;
				miSet1SIZE[endex] = mitmpSet;
				hiSet1SIZE[endex] = hitmpSet;
				tCost1SIZE[endex] = tmpCost;
				tTrav1SIZE[endex] = tmpTrav;
			}
		  }
			nodenum++;
		}

		indexS = endex+1;  /* number of partial tours in the size array */
		endex = -1;

#if DEBUG
		/*Print the Set1SIZE and tCost1SIZE/tTrav1SIZE arrays. */

		fprintf(outFile,"\nThe Set1SIZE array.\n");
		printU90Array(indexS, loSet1SIZE,miSet1SIZE, hiSet1SIZE);
		fprintf(outFile,"\nThe tCost1SIZE array.\n");
		printIntArray(indexS, tCost1SIZE);
		fprintf(outFile,"\nThe tTrav1SIZE array (Arrival time).\n");
		printIntArray(indexS, tTrav1SIZE);
		fflush (outFile);
#endif

		procCost(); /* find the Hth smallest value */
		combine1(); /* keep only H values */
	}


	if (indexHL == 0)
   {
   	fprintf(outFile,"\nThe algorithm cannot find a feasible solution.\n");
			
	if (Optimal)
		fprintf(outFile,"\nThe Solution is Optimal\n") ;

		rtime(&etime);
		fprintf(outFile,"\nTotal Elapsed Time is %ld seconds.\n ", etime - stime);

#if BATCH
	bprint();
#endif

		/* destroy storage.bin, the tracer file */
		close(strgFile);
		strgFile = open("/tmp/storage.bin",(int) O_TRUNC, (int) S_IWRITE);
		close(strgFile);

		exit(-1);
   }

	/* get ready for next stage (1), transfer the values to set0H arrays */

	for (i = 0; i < indexHL; i++)
	{
		loSet0h[i] = loSet1H[i];
		miSet0h[i] = miSet1H[i];
		hiSet0h[i] = hiSet1H[i];
	 	tCost0H[i] = tCost1H[i];
		tTrav0H[i] = tTrav1H[i];
	}

	if (indexHL == H)
	    Optimal = 0 ;

#if DEBUG
	fprintf(outFile,"\nThe Set0H array.\n");
	printU90Array(indexHL, loSet0h, miSet0h, hiSet0h);
	fprintf(outFile,"\nThe tCost0H array.\n");
	printIntArray(indexHL, tCost0H);
	fprintf(outFile,"\nThe tTrav0H array (Arrival time).\n");
	printIntArray(indexHL, tTrav0H);
	fflush (outFile);
#endif
}
/* end of stage1 */

/****************************************************************************
*                           procCost
*
* It puts the values of the arrays tCost1H and tCost1SIZE in J and finds
* the Hth smallest value of cost in J using the algorithm SELECT. 
*
* INPUT : tCost1SIZE, tCost1H
* SIDE EFFECT : maxCost is set to Hth smallest value 
*		equCost is set to no. of maxCost values included in H values
*		IndexHL to last entry in H array (if first iteration of Stage)
*		   Otherwise, it already points to that entry.
*		IndexHC to H or the last entry in SIZE if < H
*
*   Calculate no. of partial tours , temp1
*    if temp1 <= H 
*	we can retain all the PTs value of this stage
*       get the Hth value and equcost (Hth value will be max value in array) 
*    else
*	we can retain only H PTs   
*       get the Hth smallest value and equcost 
*    endif
*
*    This Hth smallest value and equcost is used in combine to retain
*    only H number of values.
****************************************************************************/

void procCost()

{
	register i,m;
	S32 temp1, temp2;

	maxTime = INF ;

	if (tCost1H[0] == INF)
		temp1 = indexS;
	else
		temp1 = indexS + indexHL;

	if (temp1 <= H) /* at most H alternatives */ 
	{
		temp2 = (S32) maxValue(indexS, tCost1SIZE);
		if (tCost1H[0] == INF)
		{
			maxCost = temp2;

			indexHC = (H > indexS) ? indexS : H;
			indexHL = indexHC;

#if DEBUG == 0
 			fprintf(outFile,"\nmaxCost = %d\n", maxCost);
			fflush (outFile);
#endif


		 	equCost = equalCost(maxCost, 0, indexS, tCost1SIZE);
		}
		else
		{
			if (temp2 > maxCost)
				maxCost = temp2;

			indexHC = (H > indexS) ? indexS : H;

#if DEBUG == 0
		   fprintf(outFile,"\nmaxCost = %d\n", maxCost);
#endif

 			fflush (outFile);
		
			equCost = equalCost(maxCost, 0, indexS, tCost1SIZE);
			temp2 = equalCost(maxCost, 0, indexHL, tCost1H);
			equCost = equCost + temp2;
		}
	}
	else /* more than H alternatives */
	{
	 	/* Put the values of the arrays tCost1H and tCost1SIZE in array J. */

		for (i = 0; i < indexS; i++)
			J1[i] = tCost1SIZE[i];

		if (tCost1H[0] != INF)
			for (i = 0; i < indexHL; i++)
				J1[indexS+i] = tCost1H[i];

		kthSmallest_U16((U16 *)J1, (S32)H-1, (S32)0, temp1-1,(S32**) NULL, (S32) 0);

		maxCost = J1[H-1];

		indexHC = (H > indexS) ? indexS : H;
		if (tCost1H[0] == INF)
			indexHL = indexHC;

#if DEBUG == 0
  		fprintf(outFile,"\nmaxCost = %d\n", maxCost);
#endif

 			fflush (outFile);

		/* equCost is the # of elements retained with total cost == maxCost */

		equCost = equalCost1(maxCost, 0, H, J1);


/* Retain only those equCost values which have minimum travel times */
/* Maybe multiple maxCost values are not present. If nofmaxCost is Gt 1
   (set in equalCost), then muliple values are there  */

	if (nofmaxCost > 1) /* multiple maxCost values */
	{
		for (i = 0,m=0 ; i < indexS; i++)
			if (tCost1SIZE[i] == maxCost)
				J1[m++] = tTrav1SIZE[i];

		if (tCost1H[0] != INF)
			for (i = 0; i < indexHL; i++)
				if (tCost1H[i] == maxCost)
					J1[m++] = tTrav1H[i];

	fflush(outFile) ;
	kthSmallest_U16((U16 *)J1, (S32)equCost-1, (S32)0, (S32)m-1, (S32 **)NULL, (S32) 0);

		maxTime = J1[equCost - 1] ;
	}
    }

#if DEBUG
  		fprintf(outFile,"\nmaxTime in equCost = %d\n", maxTime);
#endif
}
/* end of procCost */

/****************************************************************************
*                           maxValue
*
* It finds the max value in an array of int.
*
****************************************************************************/

S16 maxValue (S32 size,S16 *ptr)

{
   S16 r ;
   S32 i;

   r = 0;
	for (i = 0; i < size; i++)
	{
		if (ptr[i] > r)
			r = ptr[i];
	}
   return(r);
}
/* end of maxValue */
/****************************************************************************
*                           minValue
*
* It finds the min value in an array of int.
*
****************************************************************************/

S16 minValue (S32 size,S16 *ptr)

{
   S16 r ;
   S32 i;

   r =INF;
	for (i = 0; i < size; i++)
	{
		if (ptr[i] < r)
			r = ptr[i];
	}
   return(r);
}
/* end of minValue */

/****************************************************************************
*                           equalCost
*
* It finds the number of elements from lo to hi of an integer array that
* are equal to value.
*
****************************************************************************/

S32 equalCost (S16 value, S32 lo, S32 hi, S16 *ptr)

{
   S32 r, i;

   r = 0;
	for (i = 0; i < (hi - lo); i++)
	{
		if (ptr[i] == value)
			r++;
	}
   return(r);
}
/* end of equalCost */

/****************************************************************************
*                           equalCost1
*
* It finds the number of elements from lo to hi of an integer array that
* are equal to value. Also, it sets nofmaxCost to indicate the presence
* of more than 1 maxCost values that may not be retained.
* This version of equalCost is called only when we have more than H
* alternatives.
*
****************************************************************************/

S32 equalCost1 (S16 value, S32 lo, S32 hi, S16 *ptr)

{
   S32 r, i;

   	r = 0;


	for (i = 0; i < (hi - lo); i++)
	{
		if (ptr[i] == value)
			r++;
	}

	/*  In procCost, nofmaxCost is used to decide whether to calculate
	    maxTime in equalCosts of maxCost */

		nofmaxCost = r ;

	/* well r may be one. we can only retain one maxCost value. But
	  that does not mean only one maxCost value was found. So check
	  the next value to make sure we did'nt have multiple maxCost values */
		if ( r < 2 )
		  if (ptr[i] == value)
			nofmaxCost = 2 ;

   return(r);
}
/* end of equalCost */
/****************************************************************************
*                           combine1
*
* It combines elements of ..1SIZE and ..1H arrays for stage 1.
*
****************************************************************************/

void combine1()

{
	register i, j;

	/* Go over Set1SIZE, Set1H, tCost1SIZE, and tCost1H, tTrav1H arrays (if
		the ..1H arrays have already some values) and discard values of cost
		larger than maxCost. If there are more than one entries with total
		cost equal to maxCost, the number retained with total cost equal
		to maxCost must be the same as in the set of H best elements. Put
		selected values in Set1H and tCost1H arrays.  No requirement to
		order by Set for stage1. */

	/* Process tCost1H first, if it has been filled before */

	j = 0;
	if (tCost1H[0] != INF)
		for (i = 0; i < indexHL; i++)
			if (tCost1H[i] < maxCost)
			{
				tCost1H[j] = tCost1H[i];
				tTrav1H[j] = tTrav1H[i];
				loSet1H[j] = loSet1H[i];
				miSet1H[j] = miSet1H[i];
				hiSet1H[j] = hiSet1H[i];
				j++;
			}
			else if ((equCost > 0) && (tCost1H[i] == maxCost)
				&& (tTrav1H[i] <= maxTime))
			{
				tCost1H[j] = tCost1H[i];
				tTrav1H[j] = tTrav1H[i];
				loSet1H[j] = loSet1H[i];
				miSet1H[j] = miSet1H[i];
				hiSet1H[j] = hiSet1H[i];
				j++;
				equCost--;
			}

	/* Process tCost1SIZE now */

	for (i = 0; i < indexS; i++)
		if (tCost1SIZE[i] < maxCost)
		{
			tCost1H[j] = tCost1SIZE[i];
			tTrav1H[j] = tTrav1SIZE[i];
			loSet1H[j] = loSet1SIZE[i];
			miSet1H[j] = miSet1SIZE[i];
			hiSet1H[j] = hiSet1SIZE[i];
			j++;
		}
		else 
		if ((equCost > 0) && (tCost1SIZE[i] == maxCost)
			&& (tTrav1SIZE[i] <= maxTime))
			{
				tCost1H[j] = tCost1SIZE[i];
				tTrav1H[j] = tTrav1SIZE[i];
				loSet1H[j] = loSet1SIZE[i];
				miSet1H[j] = miSet1SIZE[i];
				hiSet1H[j] = hiSet1SIZE[i];
				j++;
				equCost--;
			}
#if DEBUG
	fprintf(outFile,"\nThe Set1H array.\n");
	printU90Array(indexHL, loSet1H, miSet1H, hiSet1H);
	fprintf(outFile,"\nThe tCost1H array.\n");
	printIntArray(indexHL, tCost1H);
	fprintf(outFile,"\nThe tTrav1H array (Arrival Time).\n");
	printIntArray(indexHL, tTrav1H);
	fflush (outFile);
#endif
}
/* end of combine1 */

/****************************************************************************
*                              stagek
*
* It processes stage k.
*
* The function does the following:
* It fills up the Set1SIZE and tCost1SIZE/tTrav.. arrays by processing the
* elements of the Set0H, tCost0H array (stage k-1) that are ordered
* by setsize.
* It sorts the Set1SIZE array and discards duplicates (parallel tCost1SIZE
* follows).
* It selects the Hth best total cost value between tCost1SIZE and tCost1H
* if tCost1H already filled before.
* It updates the maxCost value.
* It goes over Set1SIZE, Set1H, tCost1SIZE, and tCost1H arrays (if the ..1H
* arrays have already some values) and discards values of cost larger than
* maxCost. If there are more than one entries with total cost equal to
* maxCost, the number retained with total cost equal to maxCost must be the
* number of values equal to maxCost that make up H values.
* It puts the selected values in the Set1H and tCost1H arrays.
* When all elements processed from previous stage (k-1), it puts the sorted
* sets and corresponding total costs in the Set0H and tCost0H arrays.
*
****************************************************************************/

void stagek()
{
   register i;
	S32 indexPrev ;
	S16 tmpCost, tmpTrav;
 	U32 lotmpSet, mitmpSet;
	U32 tmp, hitmpSet;

 	/* Process the elements of Set0H array. */

	tCost1H[0] = INF;
	maxCost = INF;

	endex = -1;
	I = 0;
	nodenum = 1;
	indexPrev = indexHL; /* set to the last value in the H array */

	while (I < indexPrev) /* Are all partial Tours (PTs) extended */
	{
		/* Fill up the Set1SIZE and tCost1SIZE/tTrav1SIZE arrays. */
		/* The ..1SIZE arrays may be filled more than once. */

		/* for each partial tour in Set0h, extend the tour to all the nodes
		   which are not in the set already */

	/* loop till there is PT left & SIZE array is not full */

		while (I < indexPrev && endex + 1 < SIZE)
		{
			while (nodenum < nodes && endex + 1 < SIZE)
			{

			if ((TESTBIT((U16)nodenum, loSet0h[I],miSet0h[I],hiSet0h[I]) == 0) &&
 			    (CHK_PREC(loSet0h[I],miSet0h[I],hiSet0h[I],nodenum))) {
				k = GETK(loSet0h[I]);
				tmpCost = compCost(tCost0H[I], k, nodenum);
				if ((tmpCost < maxCost || indexHL < H) 
					&& (tmpCost != INF) 
			&& ((tmpTrav = compTime(tTrav0H[I], k, nodenum,TWm,numwindowsm)) != INF)) 
#if LPRC
					{
					if (CHK_LPREC(loSet0h[I],miSet0h[I],hiSet0h[I],nodenum,tmpTrav))
#endif
					
					{
						endex++;
						predSIZE[endex] = I; /* where it came from */
						tmp = (U16) nodenum & 0x7fff; /* SETBIT needs a U16 */
						lotmpSet = loSet0h[I] ;
						mitmpSet = miSet0h[I] ;
						hitmpSet = hiSet0h[I] ;
						SETBIT(tmp,lotmpSet,mitmpSet,hitmpSet) ;
						SETK(nodenum, lotmpSet) ;
						loSet1SIZE[endex] = lotmpSet ;
						miSet1SIZE[endex] = mitmpSet ;
						hiSet1SIZE[endex] = hitmpSet ;
						tCost1SIZE[endex] = tmpCost;
						tTrav1SIZE[endex] = tmpTrav;
					}

#if LPRC
#if DEBUG
 	else {
 
 	fprintf (outFile,"\n********Rejected tour LP**\t\tnode\tTtim\tCase\n") ;
 	printBinary(loSet0h[I],miSet0h[I],hiSet0h[I]) ;
 	fprintf (outFile,"\t%d\t%d\t%d\n",nodenum,tmpTrav,Wlp) ;
 	}
#endif
			 		}
#endif
 			  } /*CHK_PREC*/
#if	DEBUG
 	else {
 
 	fprintf (outFile,"\n********Rejected tour P****\t\tnode\n") ;
 	printBinary(loSet0h[I],miSet0h[I],hiSet0h[I]) ;
 	fprintf (outFile,"\t%d\n",nodenum) ;
 	}
#endif
 
				nodenum++; /* for this PT, try to extend to next node */
			} /* end of 3rd while */

		/* IS last PT extension is over */

			if (nodenum == nodes)
			{ 
			    /* Yes it is over */
				nodenum = 1;
				I++; /* pick up next PT from Set0H array */
			}
		}/* end of 2nd while */

		indexS = endex+1;
		endex = -1;

		/*Print the Set1SIZE and tCost1SIZE arrays. */
#if DEBUG
		fprintf(outFile,"\nThe Set1SIZE array.\n");
		printU90Array(indexS, loSet1SIZE,miSet1SIZE, hiSet1SIZE);
		fprintf(outFile,"\nThe tCost1SIZE array.\n");
		printIntArray(indexS, tCost1SIZE);
		fprintf(outFile,"\nThe tTrav1SIZE array (Arrival Time).\n");
		printIntArray(indexS, tTrav1SIZE);
		fprintf(outFile,"\nThe predSIZE array.\n");
		printU32Array(indexS, predSIZE);
		fflush (outFile);
#endif

		disDuple(); /* discard duplicate set values */

#if DEBUG
		fprintf(outFile,"\nThe Set1SIZE array, sorted/no duplicates.\n");
		printU90Array(indexS, loSet1SIZE,miSet1SIZE, hiSet1SIZE);
		fprintf(outFile,"\nThe tCost1SIZE array, parallel.\n");
		printIntArray(indexS, tCost1SIZE);
		fflush (outFile);
		fprintf(outFile,"\nThe tTrav1SIZE array (Arrival time).\n");
		printIntArray(indexS, tTrav1SIZE);
		fprintf(outFile,"\nThe predSIZE array, parallel.\n");
		printU32Array(indexS, predSIZE);
		fflush (outFile);
#endif

		procCost(); /* find the Hth smallest value */

		combinek(); /* retain the H values */

	} /* end of first while */

	/* If Set0H has no values in it, that means we could not extend
		the tour at all */

   if (indexHL == 0)
   {
   	fprintf(outFile,"\nThe algorithm cannot find a feasible solution.\n");

	if (Optimal)
		fprintf(outFile,"\nThe Solution is Optimal\n") ;

		rtime(&etime);
		fprintf(outFile,"\nTotal Elapsed Time is %ld seconds.\n ", etime - stime);

#if BATCH
	bprint();
#endif
		/* destroy storage.bin, the tracer file */
		close(strgFile);
		strgFile = open("/tmp/storage.bin",(int) O_TRUNC, (int) S_IWRITE);
		close(strgFile);

		exit(-1);
   }

	/* get ready for the next stage. Shuffle this stage values to Set0h */

	for (i = 0; i < indexHL; i++)
	{
		loSet0h[i] = loSet1H[i];
		miSet0h[i] = miSet1H[i];
		hiSet0h[i] = hiSet1H[i];
	 	tCost0H[i] = tCost1H[i];
		tTrav0H[i] = tTrav1H[i];
		predSIZE[i] = predH[i];
	}

	if (indexHL == H)
		Optimal = 0 ;

#if DEBUG
	fprintf(outFile,"\nThe Set0H array.\n");
	printU90Array(indexHL, loSet0h, miSet0h, hiSet0h);
	fprintf(outFile,"\nThe tCost0H array.\n");
	printIntArray(indexHL, tCost0H);
	fprintf(outFile,"\nThe tTrav0H array (Arrival Time).\n");
	printIntArray(indexHL, tTrav0H);
	fflush (outFile);
#endif
}
/* end of stagek */

/****************************************************************************
*                           disDuple
*
* It sorts the array Set1SIZE (tCost1SIZE/tTrav1SIZE tagging) and discards
* duplicates.  It checks if duplicates exist between arrays Set1SIZE and
* Set1H and discards (if Set1H/tCost1H filled before).  Duplicates are
* alternatives with same Set1SIZE values with dominating tCost1SIZE/
* tTrav1SIZE values.
* How the duplicates are formed ?
*  A tour {1,2,3}, 2  may be extended to {1,2,3,4},4 = {1,2,3}, 2 + 24
*  A tour {1,2,3}, 3 may be extended to  {1,2,3,4},4 = {1,2,3}, 3 + 34
*  
*  In standard TSP problem we keep the set which has minimum cost. The cost
*  may be distance or travel time or some other parameter.
*
* In this case, we are trying to minimize distance traveled with certain
* twists.
*
*  For duplicate sets,
*	  if cost1 > cost2
*		  if trav1 < trav2 , keep both
*		  else if trav1 >= trav2, keep 2
*	   else
*	  if cost1 < cost2
*		  if trav1 <= trav2, keep 1
*		  else (trav1 > trav2), keep both
*	   else
*	  if cost1 == cost2 
*		  if trav1 <= trav2	, keep cost1
*         else trav1 > trav2, keep cost2
*	   else
*	   
*
****************************************************************************/

void disDuple ()

{
   register j, m, p, q;

	/* Sort the array Set1SIZE.  Keep the corresponding values in
	   tCost1SIZE/tTrav1SIZE and predSIZE. */

#if DEBUG
  		fprintf(outFile,"In sortThem \n\n ");
		fflush(outFile) ;
#endif

	sortThem() ;

#if DEBUG
  		fprintf(outFile,"sortThem over\n\n ");
		fflush(outFile) ;
#endif

/*
***Now sort subsets of equal Set1SIZE by tCost1SIZE with rest tagging.
   Use qsort.
*/

	ddSort();
#if DEBUG
  		fprintf(outFile,"ddSort over\n\n ");
		fflush(outFile) ;
#endif

	/* Discard duplicates in Set1SIZE array. */
	/* When time windows are present duplicate indexed j with
		Set1SIZE[i] == Set1SIZE[j] is discarded in all cases except if
		(tCost1SIZE[i] < tCost1SIZE[j]) && (tTrav1SIZE[i] > tTrav1SIZE[j]).
		Since duplicates are sorted by tCost1SIZE we only need to compare
		the next duplicate with the one last retained. */

/***TEST THIS WELL*/

	m = 0; /* m is the slot where next value is shifted */
		  /* j always indicates the value under consideration */

	for (j = 0; j < indexS; j++)
	{
		if ((hiSet1SIZE[j] != hiSet1SIZE[j+1])
		    || (miSet1SIZE[j] != miSet1SIZE[j+1])
		    || (loSet1SIZE[j] != loSet1SIZE[j+1]))
		{
			hiSet1SIZE[m] = hiSet1SIZE[j];
			loSet1SIZE[m] = loSet1SIZE[j];
			miSet1SIZE[m] = miSet1SIZE[j];
			tCost1SIZE[m] = tCost1SIZE[j];
			tTrav1SIZE[m] = tTrav1SIZE[j];
			predSIZE[m] = predSIZE[j];
			m++;
		}
		/* j and j+1 sets are equal */
		else if ((tCost1SIZE[j] < tCost1SIZE[j+1]) && 
		        (tTrav1SIZE[j] > tTrav1SIZE[j+1]))
		{
		  /* keep both the values */

			hiSet1SIZE[m] = hiSet1SIZE[j];
			loSet1SIZE[m] = loSet1SIZE[j];
			miSet1SIZE[m] = miSet1SIZE[j];
			tCost1SIZE[m] = tCost1SIZE[j];
			tTrav1SIZE[m] = tTrav1SIZE[j];
			predSIZE[m] = predSIZE[j];
			m++;
		}
		else if ((tCost1SIZE[j] == tCost1SIZE[j+1]) && 
		        (tTrav1SIZE[j] > tTrav1SIZE[j+1]))
		{
		/* do not retain this (j) value . ratain j+1 value.*/
		}
		else
		{
		/* do not retain (J+1) value */

		  	tCost1SIZE[j+1] = tCost1SIZE[j];
			tTrav1SIZE[j+1] = tTrav1SIZE[j];
			predSIZE[j+1] = predSIZE[j];
		} 	
	}
	indexS = m;

	/* Check if duplicates exist between arrays Set1SIZE and	Set1H
	   and discard duplicates (if tCost1H filled before).  Update
		Set1H, tCost1H, tTrav1H.  Recall Set.. are ordered in increasing
		order and equal values of Set.. are ordered by tCost.. in strictly
		increasing order and for those tTrav.. is in strictly decreasing
		order. */

	if (tCost1H[0] != INF)
	{
		p = q = 0; /* p for SET1SIZE, and q for SET1H */ 
				   /* j for SET1SIZE, and m for SET1H */

	   /* j and m indexes the values under consideration , whereas, p and q
		  holds the positions next value to be retained */


	/* At this point we have Set1H arrays with no duplicates but ordered by
       set values. Similarly for Set1SIZE arrays. Now we have to eliminate
	   the duplicate values betwwn two arrays. */

		for (j = 0, m = 0; j < indexS && m < indexHL; )
		{
			if ((hiSet1SIZE[j] < hiSet1H[m]) ||
			   (hiSet1SIZE[j] == hiSet1H[m] &&
			    miSet1SIZE[j] < miSet1H[m] ) ||
				(hiSet1SIZE[j] == hiSet1H[m] && 
				 miSet1SIZE[j] == miSet1H[m] &&
				 loSet1SIZE[j] < loSet1H[m] ))
			{
				/* Set1SIZE is < Set1H  */

				loSet1SIZE[p] = loSet1SIZE[j];
				miSet1SIZE[p] = miSet1SIZE[j];
				hiSet1SIZE[p] = hiSet1SIZE[j];
				tCost1SIZE[p] = tCost1SIZE[j];
				tTrav1SIZE[p] = tTrav1SIZE[j];
				predSIZE[p] = predSIZE[j];
				j++;
				p++;
			}
			else
			if ((hiSet1SIZE[j] > hiSet1H[m]) ||
			   (hiSet1SIZE[j] == hiSet1H[m] &&
			    miSet1SIZE[j] > miSet1H[m] )||
			   (hiSet1SIZE[j] == hiSet1H[m] &&
			    miSet1SIZE[j] == miSet1H[m] &&
				loSet1SIZE[j] > loSet1H[m] ))
			{
				/* Set1SIZE is > Set1H */

				loSet1H[q] = loSet1H[m];
				miSet1H[q] = miSet1H[m];
				hiSet1H[q] = hiSet1H[m];
				tCost1H[q] = tCost1H[m];
				tTrav1H[q] = tTrav1H[m];
				predH[q] = predH[m];
				m++;
				q++;
			}
			else  /* sets are equal */
			{
			 	if (tCost1SIZE[j] < tCost1H[m])
				{
					if (tTrav1SIZE[j] <= tTrav1H[m])
					/* keep j alt., discard m alt. */
					{
						m++;
					}
					else /* tTrav1SIZE[j] > tTrav1H[m] */
					/* keep both alternatives */
					{
						hiSet1SIZE[p] = hiSet1SIZE[j];
						miSet1SIZE[p] = miSet1SIZE[j];
						loSet1SIZE[p] = loSet1SIZE[j];
						tCost1SIZE[p] = tCost1SIZE[j];
						tTrav1SIZE[p] = tTrav1SIZE[j];
						predSIZE[p] = predSIZE[j];
						p++;
						j++;
					}
				}
				else if (tCost1SIZE[j] > tCost1H[m])
				{
					if (tTrav1SIZE[j] < tTrav1H[m])
					/* keep both alternatives */
					{
						
						loSet1H[q] = loSet1H[m];
						miSet1H[q] = miSet1H[m];
						hiSet1H[q] = hiSet1H[m];
						tCost1H[q] = tCost1H[m];
						tTrav1H[q] = tTrav1H[m];
						predH[q] = predH[m];
						q++;
						m++;
					}
					else /* tTrav1SIZE[j] >= tTrav1H[m] */
					/* discard j alt., keep m alt. */
					{
						j++;
					}
				}
				else /* tCost1SIZE[j] == tCost1H[m] */
				{
					if (tTrav1SIZE[j] <= tTrav1H[m])
					/* keep j alt., discard m alt. */
					{
						m++;
					}
					else /* tTrav1SIZE[j] > tTrav1H[m] */
					/* discard j alt., keep m alt. */
					{
						j++;
					}
				}
			}
		}
		if (j == indexS)
			for ( ; m < indexHL; m++)
			{
				loSet1H[q] = loSet1H[m];
				miSet1H[q] = miSet1H[m];
				hiSet1H[q] = hiSet1H[m];
				tCost1H[q] = tCost1H[m];
				tTrav1H[q] = tTrav1H[m];
				predH[q] = predH[m];
				q++;
			}
		else if (m == indexHL)
			for ( ; j < indexS; j++)
			{
				loSet1SIZE[p] = loSet1SIZE[j];
				miSet1SIZE[p] = miSet1SIZE[j];
				hiSet1SIZE[p] = hiSet1SIZE[j];
				tCost1SIZE[p] = tCost1SIZE[j];
				tTrav1SIZE[p] = tTrav1SIZE[j];
				predSIZE[p] = predSIZE[j];
				p++;
			}
		indexS = p;
		indexHL = q;
	}
}
/* end of disDuple */

/****************************************************************************
*                           combinek
*
* It combines elements of ..1SIZE and ..1H arrays for stage k.
*
****************************************************************************/

void combinek()

{
	register i, j, m;
	int temp;

	/* Go over Set1SIZE, Set1H, tCost1SIZE, and tCost1H, tTrav1H arrays (if
		the ..1H arrays have already some values) and discard values of cost
		larger than maxCost. If there are more than one entries with total
		cost equal to maxCost, the number retained with total cost equal
		to maxCost must be the same as in  the set of H best values. Put
		selected values in Set1H, tCost1H and predH arrays ordered by Set. */

	temp = equCost;

	if (tCost1H[0] == INF)
	/* If tCost1H never filled before, only the ..1SIZE arrays are
	   considered. */
	{
		for (i = 0, j = 0; (i < indexS && j < H); i++)
		{
			if (tCost1SIZE[i] < maxCost)
			{
				tCost1H[j] = tCost1SIZE[i];
				tTrav1H[j] = tTrav1SIZE[i];
				hiSet1H[j] = hiSet1SIZE[i];
				miSet1H[j] = miSet1SIZE[i];
				loSet1H[j] = loSet1SIZE[i];
				predH[j] = predSIZE[i];
				j++;
			}
			else if ((temp > 0) && (tCost1SIZE[i] == maxCost)
				   && (tTrav1SIZE[i] <= maxTime))
			{
				tCost1H[j] = tCost1SIZE[i];
				tTrav1H[j] = tTrav1SIZE[i];
				hiSet1H[j] = hiSet1SIZE[i];
				miSet1H[j] = miSet1SIZE[i];
				loSet1H[j] = loSet1SIZE[i];
				predH[j] = predSIZE[i];
				j++;
				temp--;
			}
		}
		indexHL = j;
	}
	else   /* tCost1H has been filled before */

	/* Select the elements < maxCost (or sometimes == maxCost) from
	   both ..1SIZE and ..1H arrays.  Put them in ..1H arrays
		ordered by Set.  Use arrays tempSet, and J for temporary storage.
		The indices 0 to H-1 of J are used to store tTime.. values and the 
		indices H to 2H-1 of J are used to store pred.. values the first pass.
		A second pass is used for the tCost.. because of lack of	storage space.
		The Set1SIZE and Set1H arrays do not have duplicates. */
	{
     /* First pass */
	  {
		i = j = m = 0;
		while(m < H && m < (indexHC + indexHL))
		{
			if (i < indexS && j < indexHL)
			{
				if ((hiSet1SIZE[i] < hiSet1H[j]) ||
				   (hiSet1SIZE[i] == hiSet1H[j] &&
				    miSet1SIZE[i] < miSet1H[j] ) ||
				   (hiSet1SIZE[i] == hiSet1H[j] &&
				    miSet1SIZE[i] == miSet1H[j] &&
				    loSet1SIZE[i] < loSet1H[j] ))
				    
				{
					if (tCost1SIZE[i] < maxCost)
					{
						J[m] = predSIZE[i];
						hitempSet[m] = hiSet1SIZE[i];
						mitempSet[m] = miSet1SIZE[i];
						lotempSet[m] = loSet1SIZE[i];
						m++;
					}
					else if ((temp > 0) && (tCost1SIZE[i] == maxCost) &&
			    (tTrav1SIZE[i] <= maxTime))
					{
						J[m] = predSIZE[i];
						hitempSet[m] = hiSet1SIZE[i];
						mitempSet[m] = miSet1SIZE[i];
						lotempSet[m] = loSet1SIZE[i];
						m++;
						temp--;
					}
					i++;
				}
				else  /* Set1SIZE[i] >= Set1H[j] */
					/* sets may be equal */

				{
					if (tCost1H[j] < maxCost)
					{
						J[m] = predH[j];
						hitempSet[m] = hiSet1H[j];
						mitempSet[m] = miSet1H[j];
						lotempSet[m] = loSet1H[j];
						m++;
					}
					else if ((temp > 0) && (tCost1H[j] == maxCost)
			   && (tTrav1H[j] <= maxTime))
					{
						J[m] = predH[j];
						hitempSet[m] = hiSet1H[j];
						mitempSet[m] = miSet1H[j];
						lotempSet[m] = loSet1H[j];
						m++;
						temp--;
					}
					j++;
				}
			}
			else /* finished with one array */
			{
				if (i == indexS)
				{
					if (tCost1H[j] < maxCost)
					{
						J[m] = predH[j];
						hitempSet[m] = hiSet1H[j];
						mitempSet[m] = miSet1H[j];
						lotempSet[m] = loSet1H[j];
						m++;
					}
					else if ((temp > 0) && (tCost1H[j] == maxCost)
			   && (tTrav1H[j] <= maxTime))
					{
						J[m] = predH[j];
						hitempSet[m] = hiSet1H[j];
						mitempSet[m] = miSet1H[j];
						lotempSet[m] = loSet1H[j];
						m++;
						temp--;
					}
					j++;
				}
				else /* j == indexHL */
				{
					if (tCost1SIZE[i] < maxCost)
					{
						J[m] = predSIZE[i];
						hitempSet[m] = hiSet1SIZE[i];
						mitempSet[m] = miSet1SIZE[i];
						lotempSet[m] = loSet1SIZE[i];
						m++;
					}
					else if ((temp > 0) && (tCost1SIZE[i] == maxCost)
			   && (tTrav1SIZE[i] <= maxTime))
					{
						J[m] = predSIZE[i];
						hitempSet[m] = hiSet1SIZE[i];
						mitempSet[m] = miSet1SIZE[i];
						lotempSet[m] = loSet1SIZE[i];
						m++;
						temp--;
					}
					i++;
				}
			}
		}
	
		for (i = 0; i < m; i++)
		{
			predH[i] = J[i];
		}
	  }

	  /* Second pass */


	  {
		i = j = m = 0;
		while(m < H && m < (indexHC + indexHL))
		{
			if (i < indexS && j < indexHL)
			{
				if ((hiSet1SIZE[i] < hiSet1H[j]) ||
				   (hiSet1SIZE[i] == hiSet1H[j] &&
				    miSet1SIZE[i] < miSet1H[j] ) ||
				   (hiSet1SIZE[i] == hiSet1H[j] &&
				    miSet1SIZE[i] == miSet1H[j] &&
				    loSet1SIZE[i] < loSet1H[j] ))
				 {
					if (tCost1SIZE[i] < maxCost)
					{
						J[m] = tCost1SIZE[i] ;
					        J[H+m] = tTrav1SIZE[i] ;
						m++;
					}
					else if ((equCost > 0) && (tCost1SIZE[i] == maxCost)
			   && (tTrav1SIZE[i] <= maxTime))
					{
						J[m] = tCost1SIZE[i];
					        J[H+m] = tTrav1SIZE[i] ;
						m++;
						equCost--;
					}
					i++;
				}
				else  /* Set1SIZE[i] > Set1H[j] */
			/* or sets may be equal */
				{
					if (tCost1H[j] < maxCost)
					{
						J[m] = tCost1H[j];
					        J[H+m] = tTrav1H[j] ;
						m++;
					}
					else if ((equCost > 0) && (tCost1H[j] == maxCost)
			   && (tTrav1H[j] <= maxTime))
					{
						J[m] = tCost1H[j];
					        J[H+m] = tTrav1H[j] ;
						m++;
						equCost--;
					}
					j++;
				}
			}
			else /* finished with one array */
			{
				if (i == indexS)
				{
					if (tCost1H[j] < maxCost)
					{
						J[m] = tCost1H[j];
					        J[H+m] = tTrav1H[j] ;
						m++;
					}
					else if ((equCost > 0) && (tCost1H[j] == maxCost)
			   && (tTrav1H[j] <= maxTime))
					{
						J[m] = tCost1H[j];
					        J[H+m] = tTrav1H[j] ;
						m++;
						equCost--;
					}
					j++;
				}
				else /* j == indexHL */
				{
					if (tCost1SIZE[i] < maxCost)
					{
						J[m] = tCost1SIZE[i];
						J[H+m] = tTrav1SIZE[i] ;
						m++;
					}
					else if ((equCost > 0) && (tCost1SIZE[i] == maxCost)
			   && (tTrav1SIZE[i] <= maxTime))
					{
						J[m] = tCost1SIZE[i];
						J[H+m] = tTrav1SIZE[i] ;
						m++;
						equCost--;
					}
					i++;
				}
			}
		}
		indexHL = m;
	
		for (i = 0; i < indexHL; i++)
		{
			tCost1H[i] = J[i];
			tTrav1H[i] = J[H+i];
			hiSet1H[i] = hitempSet[i];
			miSet1H[i] = mitempSet[i];
			loSet1H[i] = lotempSet[i];
		}
	  }
	}

#if DEBUG
	fprintf(outFile,"\nThe Set1H array.\n");
	printU90Array(indexHL, loSet1H, miSet1H, hiSet1H);
	fprintf(outFile,"\nThe tCost1H array.\n");
	printIntArray(indexHL, tCost1H);
	fprintf(outFile,"\nThe tTrav1H array (Arrival time).\n");
	printIntArray(indexHL, tTrav1H);
	fprintf(outFile,"\nThe predH array.\n");
	printU32Array(indexHL, predH);
	fflush (outFile);
#endif

}
/* end of combinek */

/****************************************************************************
*                             backDepot
*
* It returns to the depot closing the tour.  It retains all the solutions
* that can be obtained from the last stage before backDepot.
*
* At this stage in program, we have coversd the last stage and 0h arrays
* has best H values for the tour covering all the nodes. Now we extend this
* tour to include the cost of travelling back to the depot. tCost1SIZE and
* tTrav1SIZE will have the required costs and the time.
****************************************************************************/

void backDepot()

{
   register i;
 
	for (i = 0; i < indexHL; i++)
	{
		/* Fill up the tCost1SIZE array. */
		/* The tCost1SIZE array will be filled only once for backDepot since
		   H <= SIZE. */

		k = GETK(loSet0h[i]);
		tCost1SIZE[i] = compCost(tCost0H[i], k, 0);
		tTrav1SIZE[i] = compTime(tTrav0H[i], k, 0,TWm,numwindowsm);
	}
}
/* end of backDepot */

/****************************************************************************
*                           arrayAlloc
*
* It dynamically allocates memory for an array of int.
* It returns a pointer to an int.
*
****************************************************************************/

S16 *arrayAlloc (unsigned size)

{
   S16 *r;

   r = (S16*) malloc (size * sizeof(S16));
   if (r == NULL)
   {
      fprintf(outFile,"Out of memory. \n");
	fflush (outFile);
      exit(-1);
   }
   return(r);
}
/* end of arrayAlloc */

/****************************************************************************
*                           arrayU32Alloc
*
* It dynamically allocates memory for an array of U32.
* It returns a pointer to a U32.
*
****************************************************************************/

U32 *arrayU32Alloc (unsigned size)

{
   U32 *r;

   r = (U32*) malloc (size * sizeof(U32));
   if (r == NULL)
   {
      fprintf(outFile,"Out of memory. \n");
	fflush (outFile);
      exit(-1);
   }
   return(r);
}
/* end of arrayU32Alloc */

/****************************************************************************
*                         matrixAlloc
*
* It dynamically allocates memory for a matrix of int.
* It returns a pointer to a pointer of int.
*
****************************************************************************/

S16 **matrixAlloc (S16 rows, S16 cols)

{
   register i;
   S16 **r;

   r = (S16 **)malloc(rows * sizeof(S16 *));
   if (r == NULL)
   {
      fprintf(outFile,"Out of memory. \n");
		fflush (outFile);
      exit(-1);
   }
   else
   {
      for (i = 0; i < rows; i++)
      {
         r[i] = (S16 *)malloc(cols * sizeof(S16));
         if (r[i] == NULL)
         {
	         fprintf(outFile,"Out of memory. \n");
				fflush (outFile);
	         exit(-1);
         }
      }
   }
   return(r);
}
/* end of matrixAlloc */

/****************************************************************************
*                         printMatrix
*
* It prints a two-dimensional array.
*
****************************************************************************/

void printMatrix(S16 **arr, S16 rows,S16  cols)

{
   register i, j;

   for (i = 0; i < rows; i++)
   {
      for (j = 0; j < cols; j++)
         fprintf(outFile,"%3d ", arr[i][j]);
      fprintf(outFile,"\n");
   }
}
/* end of printMatrix */

/****************************************************************************
*                         printIntArray
*
* It prints an array of int.
*
****************************************************************************/

void printIntArray(S32 size, S16 *ptr)

{
   register i;

   for (i = 0; i < size; i++)
   {
      fprintf(outFile,"%d\t%d\n", i, *ptr);
		ptr++;
	}
}
/* end of printIntArray */

/****************************************************************************
*                         printU32rray
*
* It prints an array of int.
*
****************************************************************************/

void printU32Array(S32 size, S32 *ptr)

{
   register i;

   for (i = 0; i < size; i++)
   {
      fprintf(outFile,"%d\t%d\n", i, *ptr);
		ptr++;
	}
}
/* end of printIntArray */


/****************************************************************************
*                         printU90Array
*
* It prints an array of U90.
*
****************************************************************************/

void printU90Array(S32 size, U32 *ptrlo,  U32 *ptrmi, U32 *ptrhi)

{
   register i;

	for (i = 0; i < size; i++)
	{
		fprintf(outFile,"%d ", i);
	   	printBinary(*ptrlo, *ptrmi,  *ptrhi);

		fprintf(outFile," %lu %lu %lu\n", *ptrhi, *ptrmi, *ptrlo);
		/* This values get cutoff by laser printer */

		ptrlo++;
		ptrmi++;
		ptrhi++;
	}
}
/* end of printU90Array */



/****************************************************************************
*                         printBinary
*
* It prints the value of a set and the value k.
*
****************************************************************************/

void printBinary(U32 setlo, U32 setmi, U32 sethi)

{
	int j;
	U16 i;
	U32 temp;

	for (j = 31; j >= 0; j--)
	{
		i = (U16) j;
		temp = sethi >> i;
		temp = temp & 1;
		putc('0' + (int) temp, outFile);
	}
		putc('\n' , outFile);
		putc(' ' , outFile);
		putc(' ' , outFile);

	for (j = 31; j >= 0; j--)
	{
		i = (U16) j;
		temp = setmi >> i;
		temp = temp & 1;
		putc('0' + (int) temp, outFile);
	}
		putc('\n' , outFile);
		putc(' ' , outFile);
		putc(' ' , outFile);


	for (i = 31; i > 5; i--)
	{
		temp = setlo >> i;
		temp = temp & 1;
		putc('0' + (int) temp, outFile);
	}

	fprintf(outFile," %u", GETK(setlo));
}
/* end of printBinary */

/************************************************************************
*                         intInsitu
*
* It obtains a sorted array of int when given the sorted indices, J. 
*
****************************************************************************/

void intInsitu(S32 size, S16 *array, S16 *J)

{
   register i, j, k;
	S16 temp;

   for (i = 0; i < size; i++)
   {
		if (J[i] != i)
		{
			temp = array[i];
			k = i;
			do
			{
				j = k;
				array[j] = array[J[j]];
				k = J[j];
				J[j] = j;
			}
			while(k != i);
			array[j] = temp;
		}
	}
}
/* end of intInsitu */


/****************************************************************************
*                         Uinsitu
*
* It obtains two parallel sorted arrays (U32 and U32) when given the sorted
* indices, J. 
*
****************************************************************************/

void Uinsitu(S32 size, U32 *array1, U32 *array2, U32 *array3, S32 *J)

{
	register i, j, k;
	U32 temp1;
	U32 temp2;
	U32 temp3;

   for (i = 0; i < size; i++)
   {
		if (J[i] != i)
		{
			temp1 = array1[i];
			temp2 = array2[i];
			temp3 = array3[i];
			k = i;
			do
			{
				j = k;
				array1[j] = array1[J[j]];
				array2[j] = array2[J[j]];
				array3[j] = array3[J[j]];
				k = J[j];
				J[j] = j;
			}
			while(k != i);
			array1[j] = temp1;
			array2[j] = temp2;
			array3[j] = temp3;
		}
	}
}
/* end of Uinsitu */

/****************************************************************************
*                         Uinsitu1
*
* It obtains two parallel sorted arrays (U32 and U32) when given the sorted
* indices, J. 
*
****************************************************************************/

void Uinsitu1(S32 size, U32 *array1,   S32 *J)

{
	register i, j, k;
	U32 temp1;

   for (i = 0; i < size; i++)
   {
		if (J[i] != i)
		{
			temp1 = array1[i];
			k = i;
			do
			{
				j = k;
				array1[j] = array1[J[j]];
				k = J[j];
				J[j] = j;
			}
			while(k != i);
			array1[j] = temp1;
		}
	}
}
/* end of Uinsitu */

/****************************************************************************
*                         insitu3
*
* It obtains 3 parallel sorted arrays of int when given the sorted
* indices, J. 
*
****************************************************************************/

void insitu3(S32 size, S16 *array1, S16 *array2, S16 *array3, S16 *J)

{
   register i, j, k;
   S16 temp1, temp2, temp3;

   for (i = 0; i < size; i++)
   {
		if (J[i] != i)
		{
			temp1 = array1[i];
			temp2 = array2[i];
			temp3 = array3[i];
			k = i;
			do
			{
				j = k;
				array1[j] = array1[J[j]];
				array2[j] = array2[J[j]];
				array3[j] = array3[J[j]];
				k = J[j];
				J[j] = j;
			}
			while(k != i);
			array1[j] = temp1;
			array2[j] = temp2;
			array3[j] = temp3;
		}
	}
}
/* end of insitu3 */

/****************************************************************************
*                         insitu4
*
* It obtains 3 parallel sorted arrays of int when given the sorted
* indices, J. 
*
****************************************************************************/

void insitu4(S32 size, S16 *array1, S32 *array2, S16 *array3, S32 *J)

{
   register i, j, k;
   S16 temp1, temp3;
   S32 temp2 ;

   for (i = 0; i < size; i++)
   {
		if (J[i] != i)
		{
			temp1 = array1[i];
			temp2 = array2[i];
			temp3 = array3[i];
			k = i;
			do
			{
				j = k;
				array1[j] = array1[J[j]];
				array2[j] = array2[J[j]];
				array3[j] = array3[J[j]];
				k = J[j];
				J[j] = j;
			}
			while(k != i);
			array1[j] = temp1;
			array2[j] = temp2;
			array3[j] = temp3;
		}
	}
}
/* end of insitu4 */

/****************************************************************************
*                         minSols
*
* It obtains the indexS solutions of minimum costs using some sort of 
* selection sort.
* main() uses these function to get the minimum costs solns.
****************************************************************************/

void minSols()

{
	register i, j;
	S16 temp, temp1;
	S32 minIndex = 0;

	/* At this point in the program, tCost1SiZE contains indexS number
	   of solutions. The k and the pred arrays has been written on the
	   disk for last stage. The solutions in the Cost1Size arrays have
	   the travel time to depot added to each solutions. After sorting 
	   this array and keeping trace of origiinal index in best[], the
	   tour path for a solution can be traced. best[] has indexes into
	   last array of values written on the disk */

	for (i = 0; i < indexHL; i++)
		J[i] = i;

	/* for i=0 upto size of array
		find out the min val from i to end of array
		exchange the value with ith value
		exchange the same values in best[]
	   endfor 
	*/

	for (i = 0; i < indexS; i++)
	{
		temp = INF;

	/*	find out the min val from i to end of array */

		for (j = i; j < indexHL; j++)
			if ((tCost1SIZE[j] < temp) ||
			   ((tCost1SIZE[j] == temp) &&
			    (tTrav1SIZE[j] < tTrav1SIZE[minIndex])))
			{
				temp = tCost1SIZE[j];
				temp1 = tTrav1SIZE[j];
				minIndex = j;
			}

	/*	exchange the value with ith value */

		tCost1SIZE[minIndex] = tCost1SIZE[i];
		tTrav1SIZE[minIndex] = tTrav1SIZE[i];

		tCost1SIZE[i] = temp;
		tTrav1SIZE[i] = temp1;

	/*	exchange the same values in best[] */

		temp =  J[minIndex];
		J[minIndex] = J[i];
		J[i] = temp;

	} /* end of for */

	for (i = 0; i < indexS; i++)
		best[i] = J[i];
}
/* end of minSols */


/****************************************************************************
*                         sortThem
*
* It sorts the hiSet and then the subsets of the loSet with the same 
* hiset.  Cost and pred tag along.
* 
* It is used by disDupl() to sort set1SIZE arrays.
****************************************************************************/

void	sortThem()
{
	int	j;
	S32	start, end;
	U32   lo, hi;

	/* why J is initialized? J[i] value is first set to 1 to n.
	   When elements are interchanged in actual array to be sorted, 
	   corresponding elements in J are also interchanged. After the
	   array sorting is over, J has the indexes to original values.
	   For eg. arr[1] =2 , j[1]=10, shows that first element in arr
	  was at 10th place in unsorted array */

	for (j = 0; j < indexS; j++) J[j] = j;

	/* First sort by hiSet1SIZE (an U32). */

	U32MaxMin (hiSet1SIZE, 0,  indexS-1, &lo, &hi);
	U32Sort (hiSet1SIZE,  J, 0,  indexS-1, lo, hi);

	/* Now J has sorted indices for hiSet values */

	for (j = 0; j < indexS; j++)
		J[H + j] = J[j]; 	/* save this values */

	/* This copying is done because Uinsitu sorts the J too. */

  	Uinsitu1(indexS, miSet1SIZE ,J);

	/* Now SetSIZE arrays are sorted by hiSET values. To get the
	full sort for Sets, arrange loSet value within hiSet */

	for (j = 0; j < indexS; j++)
		J[j] = J[H + j];    /* restore the original J values */

	/* Then sort by the subsets of miSet1SIZE (U32) with same hiSet1SIZE. */

	end = 0;
	do {
		start = end;
		while ((end < indexS) &&
				(hiSet1SIZE[start] == hiSet1SIZE[end]))
			end++;

		if (start < (end - 1))
		{
			U32MaxMin(miSet1SIZE, start, end - 1, &lo, &hi);
			U32Sort(miSet1SIZE,  J, start, end - 1, lo, hi);
		}
	} while (end < indexS);

	/* Then sort by the subsets of loSet1SIZE (U32) with same miSet1SIZE. */

	for (j = 0; j < indexS; j++)
		J[H + j] = J[j]; 	/* save this values */

  	Uinsitu1(indexS, loSet1SIZE ,J);

	for (j = 0; j < indexS; j++)
		J[j] = J[H + j];    /* restore the original J values */

	end = 0;
	do {
		start = end;
		while ((end < indexS) &&
				(hiSet1SIZE[start] == hiSet1SIZE[end]) &&
				(miSet1SIZE[start] == miSet1SIZE[end]))
			end++;

		if (start < (end - 1))
		{
			U32MaxMin(loSet1SIZE, start, end - 1, &lo, &hi);
			U32Sort(loSet1SIZE,  J, start, end - 1, lo, hi);
		}
	} while (end < indexS);

	/*  Before sorting:
		hiSet1 7 7 9 9 9 10 10
		loset1 3 2 1 8 7 6  7
		     J 2 5 8 3 9 6  1
	    After sorting:
		hiSet1 7 7 9 9 9 10 10 
		loset1 2 3 1 7 8  6 7
		     J 5 2 8 9 3  6 1

	 So, we have a sorted Set array and the original indexes in J, which
	  can be used to align corresponding values in other arrays */

	/* Now need to rearrange all (hi, lo, and parallel) arrays */
	/* by contents of J */

	insitu4 (indexS, tCost1SIZE, predSIZE, tTrav1SIZE, J);	

}

#if BATCH
void bprint()
{
	/************************************
	*
	*	save results onto the end of rslt1.txt
	*
	**************************************/
		FILE *f;
		char *s = "No Opt " ;
		char *s1 = "Opt " ;
		
		f = fopen("rslt1.txt", "a");
		fprintf(f,"\n%s\t%s\t\t%ld\t%s", nfile,
			"infeas",etime-stime,Optimal? s1 : s);
		fclose(f);
}
#endif




/****************************************************************************
*			function rtime
*
*	It calculates the run time of the process up to the point it s called.
****************************************************************************/

void rtime(long *t)
{
	struct timeb tb ;
	static time_t starttime = 0;
	ftime(&tb) ;
	if (! starttime) starttime = tb.time;
	*t = tb.time - starttime;

}

