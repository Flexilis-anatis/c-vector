This is an implementation of a `std::vector` like growable array, but in plain 
C89 code. The result is a type safe, easy to use, dynamic array that has a 
familiar set of operations.

It works by using the same trick as many allocators, which is to slightly 
allocate more data than requested, and using that extra padding in the front
as storage for meta-data. Thus any non-null vector looks like this in memory:

	+------+----------+---------+
	| size | capacity | data... |
	+------+----------+---------+
	                  ^
	                  | user's pointer

Where the user is given a pointer to first element of `data`. This way the 
code has trivial access to the necessary meta-data, but the user need not be
concerned with these details. The total overhead is `2 * sizeof(size_t)` per
vector.

To allow the code to be maximally generic, it is implemented as all macros, and
is thus header only. Usage is simple:

	#include "vector.h"
	#include <stdio.h>

	int main(int argc, char *argv[]) {

		/* this is the variable that will store the array, you can have
		 * a vector of any type! For example, you may write float *v = NULL, 
		 * and you'd have a vector of floats :-). NULL will have a size 
		 * and capacity of 0. additionally, vector_begin and vector_end will 
		 * return NULL on a NULL vector.
		 */
		int *v = NULL;
		
		/* add some elements to the back */
		v_push_back(v, 10);
		v_push_back(v, 20);
		v_push_back(v, 30);

		/* and remove one too */
		v_pop_back(v);

		/* print out some stats about the vector */
		printf("pointer : %p\n",  (void *)v);
		printf("capacity: %lu\n", v_capacity(v));
		printf("size    : %lu\n", v_size(v));

		/* iterator over the vector using "iterator" style */
		if(v) {
			int * it;
			int i = 0;
			for(it = v_begin(v); it != v_end(v); ++it) {
				printf("v[%lu] = %d\n", i, *it);
				++i;
			}
		}
		
		/* iterator over the vector standard indexing too! */
		if(v) {
			size_t i;
			for(i = 0; i < v_size(v); ++i) {
				printf("v[%d] = %d\n", i, v[i]);
			}
		}		

		/* well, we don't have destructors, so let's clean things up */
		v_free(v);
		
		return 0;
	}
