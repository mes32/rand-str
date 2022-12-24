#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const static int MY_SEED = 0; 
// const static char LOWERCASE_LETTERS[] = "abc";

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

    printf("randomeString = %s\n", randomString(10));

    return 0;
}