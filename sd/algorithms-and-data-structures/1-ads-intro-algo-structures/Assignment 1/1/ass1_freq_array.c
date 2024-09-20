#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100001  // As per problem constraints (0 <= ai <= 100000)

/* Function to find the smallest number with exactly K occurrences */
int get_minimum_number_with_k_occurences(int n, int arr[], int k) {
    int frequency[MAX] = {0};  // Array to store frequency of numbers

    // Step 1: Populate the frequency array
    for (int i = 0; i < n; i++) {
        frequency[arr[i]]++;
    }

    // Step 2: Find the smallest number with exactly K occurrences
    int smallest_number = INT_MAX;
    for (int i = 0; i < MAX; i++) {
        if (frequency[i] == k && i < smallest_number) {
            smallest_number = i;
        }
    }

    // Return the smallest number found
    return smallest_number;
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

	/* Call the function to find the smallest number with exactly K occurrences */
	int outcome = get_minimum_number_with_k_occurences(n, arr, k);

	/* Output the result */
	printf("minimum number of K occurences is %d\n", outcome);

	/* Performance testing code, do not modify */
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
#ifdef TEST_TIME
	printf("time needed was %f seconds\n", time_taken);
#endif
	return 0;
}
