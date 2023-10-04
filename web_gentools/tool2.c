#include <stdio.h>
#include <string.h>

typedef struct {
    char line[256];
    int isDiv;
    // TODO: Add more fields as needed
} line_data_t;

void read_page(char *filename) {
    FILE *fp;
    char line[256];
    fp = fopen(filename, "r");
    while (fgets(line, sizeof(line), fp)) {
        line_data_t lineData;
        // TODO: Add code to fill lineData struct from line
        printf("%s", lineData.line);
    }
    fclose(fp);
}

int main() {
    // TODO: Add code to get filename from user input
    read_page("newpage.php");
    return 0;
}