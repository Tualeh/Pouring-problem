#include <stdio.h>
#include <stdlib.h>

// Checks whether two integer vectors "veca" and "vecb" 
// of size "length" are equal.
int equal_vec (int length, int* veca, int* vecb)
  {
  int i;
  int equal = 1;

  for (i=1; i<=length; i++)
    {
    if (veca[i] != vecb[i])
      equal = 0;
    }
  return equal;
  }

// Sorts the vector "vec" of size "length" so that the entries
// are non-decreasing.
void sort_vec (int length, int* vec)
  {
  int i,j;
  int swap;

  for (i=1; i<=length; i++)
		for (j=i+1; j<=length; j++)
			{
			if (vec[i] > vec[j])
        {
        swap = vec[i];
        vec[i] = vec[j];
        vec[j] = swap;
        }
			}

  }

// Checks whether the vector "vertexvecb" can be obtained 
// from the vector "vertexveca" by a pouring step,
// where both vectors have size "k".
int gadjacheck (int k, int* vertexveca, int* vertexvecb)
  {
	int i,j,t;
  int success;
	int *valuevec;

  valuevec = (int*) malloc(sizeof(int) * (k+1));

	for (i=1; i<=k; i++)
		for (j=i+1; j<=k; j++)
      {
			for (t=1; t<=k; t++)
				{
        if (t == i)
					valuevec[t] = 2*vertexveca[i];
        else
					if (t == j)
						valuevec[t] = vertexveca[j] - vertexveca[i];
					else
						valuevec[t] = vertexveca[t]; 
        }

      sort_vec (k, valuevec);  

			success = equal_vec (k,valuevec,vertexvecb);

      if (success == 1)
        {
        i = k+1;
        break;
        }
      }

  free (valuevec);  

  return success;
  }


// Computes recursively (in the number of the entries)
// the number of divisions of the integer n into a sum of 
// k positive integers so that the numbers are non-decreasing.
// The number is guessed to be 1,000,000. If the correct
// number is larger, the value has to be increased. 
int compute_numsum (int n, int k, int numsumupp, int** vertexmat)
  {  
	int i,j,l,t;
  int spei;
  int vnumber;

  int* sumvec;
  int** summat;
  int** ssummat;
  int** svertexmat;

	sumvec = (int*) malloc(sizeof(int) * (k+1));

  summat = (int**) malloc(sizeof(int*) * (numsumupp+1));
	
  for (i=0; i<=numsumupp; i++)
	  summat[i] = (int*) malloc(sizeof(int) * (k+1));

  ssummat = (int**) malloc(sizeof(int*) * (numsumupp+1));
	
  for (i=0; i<=numsumupp; i++)
	  ssummat[i] = (int*) malloc(sizeof(int) * (k+1));

  svertexmat = (int**) malloc(sizeof(int*) * (numsumupp+1));
	
  for (i=0; i<=numsumupp; i++)
	  svertexmat[i] = (int*) malloc(sizeof(int) * (k+1));

  for (l=1; l<=k; l++)
    {
    if (l == 1)
      {
			for (i=1; i<=n+1; i++)
        {
				vertexmat[i][l] = i-1;
				svertexmat[i][l] = i-1;
				summat[i][l] = i-1;
				ssummat[i][l] = i-1;
        }
			sumvec[1] = n+1;
      }
    else
      {
			sumvec[l] = 0;

			if (l == k)
				{
				for (j=1; j<=sumvec[l-1]; j++)
          {
          spei = n - ssummat[j][l-1];
          if (spei >= svertexmat[j][l-1])
            {
						sumvec[l]++;
						if (sumvec[l] >= numsumupp)
						  {
							printf ("A: Increase the value of m.\n"); 
							printf ("m= %d\n", numsumupp); 
							exit(1);
							}
            for (t=1; t<=l-1; t++)
              {
							vertexmat[sumvec[l]][t] = svertexmat[j][t];
							summat[sumvec[l]][t] = ssummat[j][t];
              }
						vertexmat[sumvec[l]][l] = spei;
						summat[sumvec[l]][l] = ssummat[j][l-1] + spei;
            }
          }
        }
      else
        {
				for (j=1; j<=sumvec[l-1]; j++)
          {
          spei = n - ssummat[j][l-1];
					for (i=svertexmat[j][l-1]; i<=spei; i++)
            {
						if (i + ssummat[j][l-1] <= n)
              {
							sumvec[l]++;
							if (sumvec[l] >= numsumupp)
								{
								printf ("B: Increase the value of m.\n"); 
								printf ("m=%d\n",numsumupp); 
								exit(1);
								}
							for (t=1; t<=l-1; t++)
                {
								vertexmat[sumvec[l]][t] = svertexmat[j][t];
								summat[sumvec[l]][t] = ssummat[j][t];
                }
							vertexmat[sumvec[l]][l] = i;
							summat[sumvec[l]][l] = ssummat[j][l-1] + i;
              }
            }
          }
        }

			for (j=1; j<=sumvec[l]; j++)
				for (t=1; t<=l; t++)
          {
					svertexmat[j][t] = vertexmat[j][t];
					ssummat[j][t] = summat[j][t];
          }
			}
    }

  vnumber = sumvec[k];

  free (sumvec);

  for (i=0; i<=numsumupp; i++)
	  free (summat[i]);
	
  free (summat);

  for (i=0; i<=numsumupp; i++)
	  free (ssummat[i]);
	
  free (ssummat);

  for (i=0; i<=numsumupp; i++)
	  free (svertexmat[i]);
	
  free (svertexmat);

  return vnumber;
  }

// Uses Breadth-First Search to compute the number of pouring
// steps for the worst-case instance for given "n" and "k".
int gbreadthsearch (int n, int k, int numsumupp)
	{
	int i,j,l,t;
	int aktsteg;
	int contin;
	int vnumber;
	int success;

  int **vertexmat;

  vertexmat = (int**) malloc(sizeof(int*) * (numsumupp+1));
	
  for (i=0; i<=numsumupp; i++)
	  vertexmat[i] = (int*) malloc(sizeof(int) * (k+1));

	vnumber = compute_numsum (n,k,numsumupp,vertexmat);

  int *stegvec;

  stegvec = (int*) malloc(sizeof(int) * (vnumber+1));

  for (i=1; i<=vnumber; i++)
    stegvec[i] = -1;

  // These are the vectors with at least one entry 0,
	// i.e., they need exactly 0 pouring steps.
  for (i=1; i<=vnumber; i++)
	  {
		for (j=1; j<=k; j++)
      {
			if (vertexmat[i][j] == 0) 
        {
				stegvec[i] = 0;
        break;
        }
      }
		}

  aktsteg = 0;

  while (1)
	  {
		contin = 0;
		for (i=1; i<=vnumber; i++)
		  {
			// These are the sum vectors which have not been considered until now.
			if (stegvec[i] == -1)
			  contin = 1;
      else
			  continue;

      for (j=1; j<=vnumber; j++)
        {
				if (stegvec[j] != aktsteg)
					continue;

				success = gadjacheck (k,vertexmat[i],vertexmat[j]);

				if (success == 1)
					{
          stegvec[i] = aktsteg+1;
					break;
				  }
				}
			}
		
		if (contin == 0)
		  break;
		else
		  aktsteg++;
		}

  for (i=0; i<=numsumupp; i++)
	  free (vertexmat[i]);
	
  free (vertexmat);

  free (stegvec);

	return aktsteg;
  }

int main (int argc, char **argv)
  {
	int i,j;
  int start;
	int aktsteg;
	int reverse = 0;
	int numsumupp = 1000000;
	int k = 3;
	int l = 1;
	int u = 100;
  int N = 0;

  // The following parameters can be changed by the user.
  for (start = 1; start < argc; start++)
		{    
		if (*argv[start] == '-') 
			{    
			char *ep; 
			char *sc = argv[start] + 1; 
			
			while (*sc)
				{
				switch (*sc++)
				  {
					case 'k': 
						// Number of pouring vessels
					  k = strtoul(sc, &ep, 10); 
					  if (ep > sc)
							sc = ep; 
					break;
					case 'm': 
						// Estimated upper bound for the
						// number of divisions of the maximum considered integer n
						// into a sum of k positive integers so that the numbers are
						// non-decreasing.
						// If this parameter is not set, then this upper bound is
						// m=1000000
						// If an error messages is obtained, 
						// increase "m" for example by setting "-m1000001" 
						// for the next-largest number.
					  numsumupp  = strtoul(sc, &ep, 10); 
					  if (ep > sc)
							sc = ep; 
					break;
					case 'l': 
						// Minimum number tested to obtain at least "N" pouring steps
						// for the worst case instance with sum exactly "n".
					  l = strtoul(sc, &ep, 10); 
					  if (ep > sc)
							sc = ep; 
					break;
					case 'u': 
						// Maxinum number tested to obtain at least "N" pouring steps
						// for the worst case instance with sum exactly "n".
					  u = strtoul(sc, &ep, 10); 
					  if (ep > sc)
							sc = ep; 
          break;
					case 'N': 
						// Number of pouring steps aimed for.
					  N  = strtoul(sc, &ep, 10); 
					  if (ep > sc)
							sc = ep; 
          break;
					case 'r': 
						// Change to reverse order.
					  reverse = 1;
          break;
          }
				}
			}
		}	

  printf ("k=%d\n",k);
  printf ("N=%d\n",N);

  // Starting with "l" and finishing with "u", 
	// test for which sum "n" with "k" pouring vessels
	// at least "N" pouring steps are needed.
	// For the given "k" and for each "n", the number of pouring steps
  // of the corresponding worst case instance is listed.
	// With option "-r" do it in opposite direction,
  // starting with "u" and finishing it with "l". 
	for (j=l; j<=u; j++)
		{
		if (reverse == 1)
		  i = u + l - j; 
		else	
      i = j;

		aktsteg = gbreadthsearch (i,k,numsumupp);
		printf ("N(n,%d) = %3d \n",i,aktsteg); 
		if (aktsteg >= N)
			{
			if (l == 1 && reverse == 0) 
				printf ("g(%d, %d) = %d\n", N, k, i); 
			else
				printf ("g(%d, %d) <= %d\n", N, k, i); 
			printf ("h(%d, %d) >= %d\n", N, k, i); 
			break;
			}
		}

  }

