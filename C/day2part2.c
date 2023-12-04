#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    char line_buffer[256];

    int possible[] = {12, 13, 14};

    char *colors[] = {"red", "green", "blue" };
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
        int color_ints[] = {0, 0, 0};

        strtok(line_buffer, " ,:;");
        int game_number = atoi(strtok(NULL, " ,:;"));
        char *word = strtok(NULL, " ,:;");

        // Extract remaining words.
        while (word != NULL) {
            int number = atoi(word);
            word = strtok(NULL, " ,:;");
            for (int i = 0; i < sizeof(colors)/sizeof(colors[0]); i++) {
                if (strstr(word, colors[i]) != NULL) {
                    if (color_ints[i] < number) {
                        color_ints[i] = number;
                    }
                    break;
                }
            }

            word = strtok(NULL, " ,:;");
        }

        total += color_ints[0] * color_ints[1] * color_ints[2];
    }

    printf("The total is: %d\n", total);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
