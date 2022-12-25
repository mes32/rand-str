#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const static int MY_SEED = 0; 
// const static char LOWERCASE_LETTERS[] = "abc";

void printUsage() {
    printf("Usage: rand-str [-h] [-l length] [-c count] [-a] [-A] [-n] [-s] [-xa]\n");
    printf("  Options:\n");
    printf("    -h: Print usage screen\n");
    printf("    -l length: Number of characters in random string (default 16)\n");
    printf("    -c count: How many random strings to generate per run (default 1)\n");
    printf("    -a: Include lowercase letters\n");
    printf("    -A: Include uppercase letters\n");
    printf("    -n: Include numbers\n");
    printf("    -s: Include symbols\n");
    printf("    -xa: Exclude visually ambiguous characters\n");
    exit(0);
}

const char* randomString(size_t length) {
    char charset[] = "abc";
    size_t charsetSize = strlen(charset);

    srand(time(NULL) + MY_SEED);

    char* randomString = malloc(sizeof(char) * (length + 1));
    if (randomString == NULL) {
        printf("Out of memory. Could not allocate memory for random string.");
        exit(1);
    }
    for (size_t i = 0; i < length; i++) {
        int randomIndex = rand() % charsetSize;
        randomString[i] = charset[randomIndex];
    }
    randomString[length] = '\0';

    return randomString;
}

int main(int argc, char** argv) {
    for(int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    if (argv[1] && strcmp(argv[1], "-h") == 0) {
        printUsage();
    }

    printf("%s\n", randomString(10));
    return 0;
}