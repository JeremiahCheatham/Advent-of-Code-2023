#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *input_file = NULL;
    FILE *output_file = NULL;

    char line_buffer[256];

    int total = 0;

    input_file = fopen("input-data", "r");
    if (!input_file) {
        fprintf(stderr, "Unable to open input file\n");
        return 1;
    }

    output_file = fopen("output-data", "w");
    if (!output_file) {
        fprintf(stderr, "Unable to open output file\n");
        return 1;
    }

    while (fgets(line_buffer, sizeof(line_buffer), input_file)) {
        int length = strlen(line_buffer);

        for ( int i = 0; i < length; i++) {
            if ( line_buffer[i] >= '0' ) {
                if ( line_buffer[i] <= '9' ) {
                    fprintf(output_file, "%c", line_buffer[i]);
                    break;
                }
            }
        }

        for ( int i = length -1 ; i >= 0; i--) {
            if ( line_buffer[i] >= '0' ) {
                if ( line_buffer[i] <= '9' ) {
                    fprintf(output_file, "%c", line_buffer[i]);
                    break;
                }
            }
        }

        fprintf(output_file, "\n");
    }

    fclose(output_file);
    output_file = NULL;

    output_file = fopen("output-data", "r");
    if (!output_file) {
        fprintf(stderr, "Unable to open output file\n");
        return 1;
    }

    while (fgets(line_buffer, sizeof(line_buffer), output_file)) {
        total += atoi(line_buffer);
    }

    printf("The total is: %d\n", total);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
