# rand-str

## Setup

```bash
# Clone this repository
git clone https://github.com/mes32/rand-str.git

# Compile the program using the Makefile
cd rand-str
make all

# Generate a random string
./bin/rand-str
```

## Usage and Options
```bash
Usage: rand-str [-h] [-l length] [-n count] [--lowercase true/false] [--uppercase true/false] [--numbers true/false] [--symbols true/false] [--ambiguous true/false]
  Options:
    -h: Print usage screen
    -l length: Number of characters in random string (default 16)
    -n count: How many random strings to generate per run (default 1)

  Note: If any of the following configuration flags are present, the others become false by default. In none of these flags are present, then the default configuration is to include lowercase letters, uppercase letters, numbers, symbols, and to exclude visually ambiguous characters.
    -c, --lowercase true/false: Include lowercase letters
    -C, --uppercase true/false: Include uppercase letters
    -#, --numbers true/false: Include numbers
    -$, --symbols true/false: Include symbols
    -a, --ambiguous true/false: Include visually ambiguous characters
```
