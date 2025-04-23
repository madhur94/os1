#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1; 
    }

    const char* pattern = argv[1];
    const char* filename = argv[2];
    char line[5000];

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        char* match = strstr(line, pattern);
        if (match) {
            *match = '\0';  // Temporarily break the string at the match
            printf("%s", line); // Print before match
            printf("\033[31m%s\033[0m", pattern); // Print match in red
            printf("%s", match + strlen(pattern)); // Print after match
        }
    }

    fclose(fp);
    return 0;
}
