#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define buffer_size 256
#define map_size 40

struct Map {
    unsigned int source[map_size];
    unsigned int range[map_size];
    unsigned int offset[map_size];
};

struct Data {
    char buffer[buffer_size];
    unsigned int seeds[map_size];
    unsigned int answer;

    struct Map soil;
    struct Map fertilizer;
    struct Map water;
    struct Map light;
    struct Map temperature;
    struct Map humidity;
    struct Map location;
};

void data_setup(struct Data *data, FILE *input_file); 
void populate_map(struct Data *data, struct Map *map, FILE *input_file);
unsigned int convert(unsigned int input, struct Map *map);
void convert_seeds(struct Data *data); 

int main() {
    FILE *input_file = NULL;
    input_file = fopen("input-data", "r");
    if (!input_file) {
        fprintf(stderr, "Unable to open input file\n");
        return 1;
    }

    struct Data data;
    data_setup(&data, input_file);
    convert_seeds(&data);

    printf("The answer is: %d\n", data.answer);

    fclose(input_file);

    return 0;
}

void data_setup(struct Data *data, FILE *input_file) {
    char *word = NULL;
    int i = 0;
    
    memset(data, 0, sizeof(struct Data));
    data->answer = (unsigned int)-1;
    fgets(data->buffer, buffer_size, input_file);

    strtok(data->buffer, " ");

    while ((word = strtok(NULL, " "))) {
        data->seeds[i] = (unsigned)atoi(word);
        i++;
    }

    fgets(data->buffer, buffer_size, input_file);
    populate_map(data, &data->soil, input_file);
    populate_map(data, &data->fertilizer, input_file);
    populate_map(data, &data->water, input_file);
    populate_map(data, &data->light, input_file);
    populate_map(data, &data->temperature, input_file);
    populate_map(data, &data->humidity, input_file);
    populate_map(data, &data->location, input_file);
}

void populate_map(struct Data *data, struct Map *map, FILE *input_file) {
    int i = 0;

    fgets(data->buffer, buffer_size, input_file);
    while ((fgets(data->buffer, buffer_size, input_file)) && (data->buffer[0] != '\n')) {
        unsigned int destination = (unsigned)atoi(strtok(data->buffer, " "));
        map->source[i] = (unsigned)atoi(strtok(NULL, " "));
        map->range[i] = (unsigned)atoi(strtok(NULL, " "));
        map->offset[i] = destination - map->source[i];
        i++;
    } 
}

unsigned int convert(unsigned int input, struct Map *map) {
    for (int i = 0; i < map_size; i++) {
        if ((input >= map->source[i]) && (input <= map->source[i] + map->range[i])) {
            return input + map->offset[i];
        }
    }
    return input;
}

void convert_seeds(struct Data *data) {
    for (int i = 0; data->seeds[i]; i++) {
        unsigned int seed = data->seeds[i];
        unsigned int soil = convert(seed, &data->soil);
        unsigned int fertilizer = convert(soil, &data->fertilizer);
        unsigned int water = convert(fertilizer, &data->water);
        unsigned int light = convert(water, &data->light);
        unsigned int temperature = convert(light, &data->temperature);
        unsigned int humidity = convert(temperature, &data->humidity);
        unsigned int location = convert(humidity, &data->location);
        if (data->answer > location) {
            data->answer = location;
        }
    }
}
