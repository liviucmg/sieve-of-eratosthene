/*
 * Sieve of Eratosthene. Using bitwise operations.
 * O(n) time
 * O(n/8) space
 */

#include <stdio.h>
#include <cstdlib>

int main() {
    long n, i, j;

	// Pre-computed powers of 2 for faster bit lookup.
	char pow2[8] = {1, 2, 4, 8, 16, 32, 64, 128};

    // Read input data.
    FILE *f = fopen("input.txt", "r");
    fscanf(f, "%ld", &n);
    fclose(f);

    // Create array containing one bit for each number. The first bit will represent the number "1". Each bit is initially zero.
    long aLength = n / 8;
    if (n % 8 != 0) {
        aLength++;
    }
    char *a = (char*)calloc(1, aLength);

	// Take each prime number starting with 2.
    long k = 2, km;
    while (k < n) {
		// Mark each multiple starting with k * 2.
        km = k * 2;
        while (km <= n) {
			// Mark corresponding bit.
			a[(km - 1) / 8] |= pow2[(km - 1) % 8];
			// Get next multiple.
            km += k;
        }

		// Get next prime (next unmarked number).
		do {
			k++;
		}
		while (
			k <= n &&
			(a[(k - 1) / 8] & pow2[(k - 1) % 8]) != 0
		);
    }
	
    // Print prime numbers. Start with "2" which is the second number in the array.
    f = fopen("output.txt", "w");
    long aPos = 0; // Current position in the array.
	char bitPos = 1; // Current 0-indexed position in the current byte.
    for (i = 2; i <= n; i++) {
		// Print the number if it is a prime.
        if ((a[aPos] & pow2[bitPos]) == 0) {
            fprintf(f, "%d ", i);
        }

		// Move to the next number.
		bitPos = (bitPos + 1) % 8; // Move to the next bit.
		aPos += !bitPos; // When bitPos is set to zero, we move to the next element in the array.
    }
    fclose(f);
}
