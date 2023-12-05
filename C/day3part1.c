#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define buffer_size 256

struct Data {
    char buffer[3][buffer_size];
    int total;
};

void buffer_setup(struct Data *data, FILE *input_file);
void buffer_update(struct Data *data, FILE *input_file); 
int adjacent_number(struct Data *data, int i);

int main() {
    FILE *input_file = NULL;
    input_file = fopen("input-data", "r");
    if (!input_file) {
        fprintf(stderr, "Unable to open input file\n");
        return 1;
    }

    struct Data data;
    buffer_setup(&data, input_file);

    while (data.buffer[1][0]) {

        for (int i = 0; i < strlen(data.buffer[1]); i++) {
            char symbol = data.buffer[1][i];
            if ((symbol != '.') && (symbol != '\n') && ((symbol < '0') || (symbol > '9'))) {
                adjacent_number(&data, i);
            }
        }

        buffer_update(&data, input_file);
    }

    printf("The total is: %d\n", data.total);

    fclose(input_file);

    return 0;
}

void buffer_setup(struct Data *data, FILE *input_file) {
    memset(data->buffer[0], 0, buffer_size);
    memset(data->buffer[1], 0, buffer_size);
    memset(data->buffer[2], 0, buffer_size);
    fgets(data->buffer[1], buffer_size, input_file);
    fgets(data->buffer[2], buffer_size, input_file);
    data->total = 0;
}

void buffer_update(struct Data *data, FILE *input_file) {

    memset(data->buffer[0], 0, buffer_size);
    strncpy(data->buffer[0], data->buffer[1], buffer_size - 1);
    memset(data->buffer[1], 0, buffer_size);
    strncpy(data->buffer[1], data->buffer[2], buffer_size - 1);
    memset(data->buffer[2], 0, buffer_size);
    fgets(data->buffer[2], buffer_size, input_file);
}

int adjacent_number(struct Data *data, int i) {
    int low = i > 0 ? i - 1 : 0;
    int high = i < buffer_size - 1 ? i + 1 : buffer_size - 1;
    int last_number = 0;
    for (int j = 0; j < 3; j++) {
        for (int k = low; k <= high; k++) {
            if ((data->buffer[j][k] >= '0') && (data->buffer[j][k] <= '9')) {
                int l = k;
                while ((k > 0) && (data->buffer[j][l - 1] >= '0') && (data->buffer[j][l - 1] <= '9')) {
                    l--;
                }
                int number = 0;
                sscanf(&data->buffer[j][l], "%d", &number);
                if (last_number != number) {
                    data->total += number;
                    last_number = number;
                }
            }
        }
    }
    return 0;
}
