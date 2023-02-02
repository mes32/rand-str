#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const static int MY_SEED = 0; 
// TODO: Make sure these arrays are complete
const static char LOWERCASE_LETTERS[] = "abcdefghijklmnopqrstuvwxyz";
const static char UPPERCASE_LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const static char NUMBERS[] = "1234567890";
const static char SYMBOLS[] = "!\"#$%&'()*+,-./:;<=>?@`\\~[]]^_{}";
// const static char AMBIGUOUS_CHARACTERS[] = "o0O";

int stringLength = 16;
int numberOfStrings = 1;
bool hasSetIncludes = false;
bool includeLowercase = true;
bool includeUppercase = true;
bool includeNumbers = true;
bool includeSymbols = true;
bool includeAmbiguous = false;

void printUsage() {
    // TODO: Consider combining multiple printf's into one
    printf("Usage: rand-str [-h] [-l length] [-n count] [--lowercase true/false] [--uppercase true/false] [--numbers true/false] [--symbols true/false] [--ambiguous true/false]\n");
    printf("  Options:\n");
    printf("    -h: Print usage screen\n");
    printf("    -l length: Number of characters in random string (default 16)\n");
    printf("    -n count: How many random strings to generate per run (default 1)\n");
    printf("\n");
    printf("  Note: If any of the following configuration flags are present, the others become false by default. In none of these flags are present, then the default configuration is to include lowercase letters, uppercase letters, numbers, symbols, and to exclude visually ambiguous characters.\n");
    printf("    -c, --lowercase true/false: Include lowercase letters\n");
    printf("    -C, --uppercase true/false: Include uppercase letters\n");
    printf("    -#, --numbers true/false: Include numbers\n");
    printf("    -$, --symbols true/false: Include symbols\n");
    printf("    -a, --ambiguous true/false: Include visually ambiguous characters\n");
}

// TODO: Use this function to be permissive with accepted arguments
// Only consider {"false", "0", "off", "null", "nil"} to be falsy (case insensitive) and consider all other inputs as true
bool isTruthy(char* str) {
    return strcmp("false", str); // || strcmp("0", str) || strcmp("off", str) || strcmp("null", str) || strcmp("nil", str);
}

// TODO: Handle case where setting one input false typically results in all flags being false and "Floating point exception: 8"
void setIncludesToFalse() {
    if (!hasSetIncludes) {
        hasSetIncludes = true;
        includeLowercase = false;
        includeUppercase = false;
        includeNumbers = false;
        includeSymbols = false;
        includeAmbiguous = false;
    }
}

char* composeCharSet() {
    // TODO: Print the status of include flags for now
    printf("includeLowercase: %s\n", includeLowercase == 0 ? "false" : "true");
    printf("includeUppercase: %s\n", includeUppercase == 0 ? "false" : "true");
    printf("includeNumbers  : %s\n", includeNumbers == 0 ? "false" : "true");
    printf("includeSymbols  : %s\n", includeSymbols == 0 ? "false" : "true");
    printf("includeAmbiguous: %s\n", includeAmbiguous == 0 ? "false" : "true");
    printf("\n");

    size_t length = 0;
    if (includeLowercase) {
        length += strlen(LOWERCASE_LETTERS);
    }
    if (includeUppercase) {
        length += strlen(UPPERCASE_LETTERS);
    }
    if (includeNumbers) {
        length += strlen(NUMBERS);
    }
    if (includeSymbols) {
        length += strlen(SYMBOLS);
    }

    char* charSet = malloc(sizeof(char) * (length + 1));
    if (charSet == NULL) {
        printf("Out of memory. Could not allocate memory for character set string.");
        exit(1);
    }

    size_t j = 0;
    if (includeLowercase) {
        for (size_t i = 0; i < strlen(LOWERCASE_LETTERS); i++) {
            charSet[j++] = LOWERCASE_LETTERS[i];
        }
    }
    if (includeUppercase) {
        for (size_t i = 0; i < strlen(UPPERCASE_LETTERS); i++) {
            charSet[j++] = UPPERCASE_LETTERS[i];
        }
    }
    if (includeNumbers) {
        for (size_t i = 0; i < strlen(NUMBERS); i++) {
            charSet[j++] = NUMBERS[i];
        }
    }
    if (includeSymbols) {
        for (size_t i = 0; i < strlen(SYMBOLS); i++) {
            charSet[j++] = SYMBOLS[i];
        }
    }
    charSet[length] = '\0'; // TODO: Check if there is any value in doing this

    // TODO: if includeAmbiguous return here, otherwise remove ambiguous characters from a copy of charSet
    return charSet;
}

const char* randomString(size_t length, char* charset) {
    size_t charsetSize = strlen(charset);

    char* randomString = malloc(sizeof(char) * (length + 1));
    if (randomString == NULL) {
        printf("Out of memory. Could not allocate memory for random string.");
        exit(1);
    }
    for (size_t i = 0; i < length; i++) {
        int randomIndex = rand() % charsetSize;
        randomString[i] = charset[randomIndex];
    }
    randomString[length] = '\0'; // TODO: Check if there is any value in doing this

    return randomString;
}

int main(int argc, char** argv) {
    int option;

    struct option long_options[] = {
        {"lowercase", required_argument, 0, 'c'},
        {"uppercase", required_argument, 0, 'C'},
        {"numbers", required_argument, 0, '#'},
        {"symbols", required_argument, 0, '$'},
        {"ambiguous", required_argument, 0, 'a'},
        {0, 0, 0, 0}
    };

    while ((option = getopt_long(argc, argv, "hl:n:c:C:#:$:a:", long_options, NULL)) != -1) {
        switch (option) {
            case 'h':
                printUsage();
                exit(0);
            case 'l':
                if (sscanf (optarg, "%i", &stringLength) != 1 || stringLength < 0) {
                    // TODO: Try to find a more systematic/dry way to handle these scanning error messages
                    // TODO: Print these errors to the error stream
                    // TODO: Fix error messages for less than 0
                    printf("rand-str: option requires an argument of type int -- l\n");
                    printf("Invalid input, use option -h to see valid usage and options.\n");
                    exit(1);
                }
                break;
            case 'n':
                if (sscanf (optarg, "%i", &numberOfStrings) != 1 || numberOfStrings < 0) {
                    printf("rand-str: option requires an argument of type int -- n\n");
                    printf("Invalid input, use option -h to see valid usage and options.\n");
                    exit(1);
                }
                break;
            case 'c':
                setIncludesToFalse();
                if (isTruthy(optarg)) {
                    includeLowercase = true;
                } else {
                    includeLowercase = false;
                }
                break;
            case 'C':
                setIncludesToFalse();
                if (isTruthy(optarg)) {
                    includeUppercase = true;
                } else {
                    includeUppercase = false;
                }
                break;
            case '#':
                setIncludesToFalse();
                if (isTruthy(optarg)) {
                    includeNumbers = true;
                } else {
                    includeNumbers = false;
                }
                break;
            case '$':
                setIncludesToFalse();
                if (isTruthy(optarg)) {
                    includeSymbols = true;
                } else {
                    includeSymbols = false;
                }
                break;
            case 'a':
                setIncludesToFalse();
                if (isTruthy(optarg)) {
                    includeAmbiguous = true;
                } else {
                    includeAmbiguous = false;
                }
                break;
            default:
                printf("Invalid input, use option -h to see valid usage and options.\n");
                exit(1);
        }
    }

    char* charSet = composeCharSet();

    srand(time(NULL) + MY_SEED);
    for (int i = 0; i < numberOfStrings; i++) {
        printf("%s\n", randomString(stringLength, charSet));
    }
    return 0;
}