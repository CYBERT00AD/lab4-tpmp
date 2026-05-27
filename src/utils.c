#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void read_line(const char *prompt, char *buffer, size_t size) {
    if (prompt) {
        printf("%s", prompt);
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
}

int read_int(const char *prompt) {
    char buffer[128];
    char *endptr;
    long value;

    while (1) {
        read_line(prompt, buffer, sizeof(buffer));
        value = strtol(buffer, &endptr, 10);

        if (endptr != buffer && *endptr == '\0') {
            return (int)value;
        }

        printf("Invalid integer. Try again.\n");
    }
}

double read_double(const char *prompt) {
    char buffer[128];
    char *endptr;
    double value;

    while (1) {
        read_line(prompt, buffer, sizeof(buffer));
        value = strtod(buffer, &endptr);

        if (endptr != buffer && *endptr == '\0') {
            return value;
        }

        printf("Invalid number. Try again.\n");
    }
}

void pause_screen(void) {
    char buffer[8];
    printf("\nPress Enter to continue...");
    fgets(buffer, sizeof(buffer), stdin);
}