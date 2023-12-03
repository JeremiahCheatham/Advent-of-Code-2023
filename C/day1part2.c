#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *input_file = NULL;
    FILE *output_file = NULL;

    char line_buffer[256];

    int first_int = 0;
    char *first_ptr = NULL;
    int last_int = 0;
    char *last_ptr = NULL;

    char *p = NULL;

    int total = 0;
    char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

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
        first_int = 0;
        first_ptr = NULL;
        last_int = 0;
        last_ptr = NULL;

        int length = strlen(line_buffer);

        for ( int i = 0; i < length; i++) {
            if (( line_buffer[i] >= '0' ) && ( line_buffer[i] <= '9' )) {
                first_ptr = &line_buffer[i];
                first_int = line_buffer[i] - '0';
                break;
            }
        }

        for ( int i = length -1 ; i >= 0; i--) {
            if (( line_buffer[i] >= '0' ) && ( line_buffer[i] <= '9' )) {
                last_ptr = &line_buffer[i];
                last_int = line_buffer[i] - '0';
                break;
            }
        }

        for (int j = 0; j < sizeof(numbers)/sizeof(numbers[0]); j++) {
            p = line_buffer;
            while ((p = strstr(p, numbers[j])) != NULL) {
                if (!first_ptr || (first_ptr > p)) {
                    first_ptr = p;
                    first_int = j;
                }
                if (!last_ptr || (last_ptr < p)) {
                    last_ptr = p;
                    last_int = j;
                }
                p++;
            }
        }
        
        fprintf(output_file, "%d%d\n", first_int, last_int);
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
