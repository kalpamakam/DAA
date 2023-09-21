#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

// Function to precompute the bad character heuristic table
void badCharHeuristic(char* pattern, int patternLength, int badChar[MAX_CHAR]) {
    for (int i = 0; i < MAX_CHAR; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < patternLength; i++) {
        badChar[(int)pattern[i]] = i;
    }
}

// Function to perform Horspool's string matching
void horspoolStringMatch(char* text, char* pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    int badChar[MAX_CHAR];
    badCharHeuristic(pattern, patternLength, badChar);

    int shift = 0;

    while (shift <= textLength - patternLength) {
        int j = patternLength - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            printf("Pattern found at index %d\n", shift);

            // Shift the pattern to find the next occurrence
            shift += (shift + patternLength < textLength) ? patternLength - badChar[text[shift + patternLength]] : 1;
        } else {
            // Shift based on the bad character heuristic
            shift += j - badChar[text[shift + j]];
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);

    horspoolStringMatch(text, pattern);
