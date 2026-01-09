# Pouring-problem
These files contain a program and results for paper "The Generalized Double Pouring Problem: Analysis, Bounds and Algorithms" by
Gerold Jäger and Tuomo Lehtilä, arXiv:2504.03039 (2025). 


Besides this file 
1. "readme.txt" 

this folder contains the following 7 files:

2. "pouring.cc"
   This file is a C++ program. You can compile it for example
   with "gcc pouring.cc" and obtain the executable "a.out".

   You can start it as follows.
   "a.out -N5 -k4 -l20 -u80"
	 This will try to compute the values N(20,4), N(21,4),...,N(80,4) and stop
	 if one of these values is 5. In the example it stops with N(76,4) = 5 and 
	 outputs: 
   g(5,4) <= 76,
   h(5,4) >= 76.
	 The user can use the reverse order, i.e., computing values N(80,4), N(79,4),...,N(20,4), 
	 by the additional option "-r".
   Note that for l=1 and usual (non-reverse) order, if one value N
	 is found, the program can conclude directly the exact value of g(N,k).
	 In other words: "a.out -N5 -k3 -l1 -u80" outputs:
   g(5,4) = 76,
   h(5,4) >= 76.

	 Finally, an upper bound 1,000,000 is given for the number of divisions of the maximum 
	 considered integer n as a sum of k positive integers so that the numbers are
	 non-decreasing.
	 For some pairs (N,k) with large N,k this might be not large enough. In that 
	 case the user gets an error message and advice to choose a larger value for this upper
	 bound by using for example the value 10,0000,000 and adding the option "-m10000000".

The last six files are result files based on the runs of
the program "pouring.cc".
Each file contains the values of the following
function N(n,k) for one of k=3,4,5,6,7,8 and for 
n in a given interval between 1 and an upper bound
for the maximum value which can be computed in reasonable time.
N(n,k) means the number of pourings which a worst case instance
with k vessels and sum of the entries of vessels n needs.

3. "results_k3.txt"
   This file contains all results for pouring with k=3 vessels,
	 where the sum of the entries of the vessels is n=1,2,...,65535.
4. "results_k4.txt"
   This file contains all results for pouring with k=4 vessels,
	 where the sum of the entries of the vessels is n=1,2,...,2047.
5. "results_k5.txt"
   This file contains all results for pouring with k=5 vessels,
	 where the sum of the entries of the vessels is n=1,2,...,255.
6. "results_k6.txt"
   This file contains all entries of the vessels for pouring with k=6 vessels,
	 where the sum of the vessels is n=1,2,...,134.
7. "results_k7.txt"
   This file contains all entries of the vessels for pouring with k=7 vessels,
	 where the sum of the vessels is n=1,2,...,100.
8. "results_k8.txt"
   This file contains all entries of the vessels for pouring with k=8 vessels,
	 where the sum of the vessels is n=1,2,...,86.

The values g(N,k) of Table 1 and the upper bounds of h(N,k) of Table 2 can be read
from these result files. 
For example, g(5,4) = 76 is the smallest n for which N(n,4) = 5.
On the other hand, h(5,4) = 204 is the largest (found) n for which N(n,4) = 5.
Note that by Corollary 16, we can compute exact values of h(N,3).

