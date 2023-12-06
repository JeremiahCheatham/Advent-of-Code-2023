#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define buffer_size 256
#define winning_size 10
#define chosen_size 25
#define copies_size 10

struct Data {
    char buffer[buffer_size];
    int winning_numbers[winning_size];
    int chosen_numbers[chosen_size];
    int total;
    int copies_queue[copies_size];
};

void data_setup(struct Data *data);
void data_update(struct Data *data, FILE *input_file); 
void card_score(struct Data *data);
int pop_queue(struct Data *data); 

int main() {
    FILE *input_file = NULL;
    input_file = fopen("input-data", "r");
    if (!input_file) {
        fprintf(stderr, "Unable to open input file\n");
        return 1;
    }

    struct Data data;

    data_setup(&data);

    data_update(&data, input_file);
    while (*data.buffer) {
        card_score(&data);
        data_update(&data, input_file);
    }

    printf("The total is: %d\n", data.total);

    fclose(input_file);

    return 0;
}

void data_setup(struct Data *data) {
    memset(data->winning_numbers, 0, sizeof(data->winning_numbers));
    memset(data->chosen_numbers, 0, sizeof(data->chosen_numbers));
    memset(data->copies_queue, 0, sizeof(data->copies_queue));
    data->total = 0;
}

void data_update(struct Data *data, FILE *input_file) {
    char *word = NULL;
    int i = 0;

    memset(data->winning_numbers, 0, winning_size);
    memset(data->chosen_numbers, 0, chosen_size);
    memset(data->buffer, 0, buffer_size);

    fgets(data->buffer, buffer_size, input_file);

    strtok(data->buffer, " ");
    strtok(NULL, " ");

    while ((word = strtok(NULL, " "))) {
        if (word[0] == '|') break;
        data->winning_numbers[i] = atoi(word);
        i++;
    }
    i = 0;
    while ((word = strtok(NULL, " "))) {
        data->chosen_numbers[i] = atoi(word);
        i++;
    }
}

void card_score(struct Data *data) {
    int score = 0;
    int cards = 1;
    for (int i = 0; i < chosen_size; i++) {
        if (!data->chosen_numbers[i]) break;
        for (int j = 0; j < winning_size; j++) {
            if (!data->winning_numbers[j]) break;
            if (data->chosen_numbers[i] == data->winning_numbers[j]) {
                score++;
            }
        }
    }
    cards += pop_queue(data);
    if (score > copies_size) {
        printf("copies queue is too small.\n");
    }
    for (int i = 0; i < score; i++) {
        data->copies_queue[i] += cards;
    }
    data->total += cards;
}

int pop_queue(struct Data *data) {
    int pop = data->copies_queue[0];
    for (int i = 1; i < copies_size; i++) {
        data->copies_queue[i - 1] = data->copies_queue[i];
    }
    data->copies_queue[copies_size - 1] = 0;
    return pop;
}
