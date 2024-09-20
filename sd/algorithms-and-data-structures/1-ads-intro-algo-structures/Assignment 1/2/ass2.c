#include <stdio.h>
#include <time.h>
/* 2nd part of Assignment 1 SD */
void Sort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already sorted
        for (j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int get_difference_between_min_and_max_sum_of_k_elems(int arr[], int n, int k) {
	Sort(arr, n);
	int min_sum = 0;
	int max_sum = 0;
	for (int i = 0; i < k; i++) {
		min_sum += arr[i];
	}
	for (int i = n - 1; i > n - k - 1; i--) {
		max_sum += arr[i];
	}
	return max_sum - min_sum;
}

int main() {
	/* this is code to measure the time of your algorithm, please don't touch it */

    	clock_t t; 
	double time_taken;

    	t = clock(); 
  
		/* Reading input values */
	int n;
	scanf("%d", &n);

	int arr[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	int k;
	scanf("%d", &k);

	int outcome=0;

	outcome = get_difference_between_min_and_max_sum_of_k_elems(arr, n, k);

	/* implement her your code e.g. like this 
	 * outcome = get_difference_between_min_and_max_sum_of_k_elems( choose your own arguments );
	 */


	/* this is the (performance) test code, please don't touch it */

	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("difference between minimum and maximum sum of K elements is %d\n", outcome);
#ifdef TEST_TIME
	printf("time needed was %f seconds\n", time_taken);
#endif
	return 0;
}
