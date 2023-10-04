#include <stdio.h>
#include <stdlib.h>

int main() {
    // Change to the src directory
    int ret = system("cd src");

    if (ret == -1) {
        perror("system");
        return EXIT_FAILURE;
    }

    // Compile all C files in the src directory
    ret = system("gcc -static -O3 *.c -o output");

    if (ret == -1) {
        perror("system");
        return EXIT_FAILURE;
    }

    printf("Compilation completed successfully.\n");

    return EXIT_SUCCESS;
}