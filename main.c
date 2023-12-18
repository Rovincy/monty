#include <stdio.h>
#include <string.h>
#include "monty.h"

#define BUFFER_SIZE 256

bus_t bus = {NULL, NULL, NULL, 0};

/**
 * main - monty code interpreter
 * @argc: number of arguments
 * @argv: monty file location
 * Return: 0 on success
 */
int main(int argc, char *argv[]) {
  char *content;
  FILE *file;
  size_t size = 0;
  unsigned int counter = 0;
  stack_t *stack = NULL;

  if (argc != 2) {
    fprintf(stderr, "USAGE: monty file\n");
    exit(EXIT_FAILURE);
  }

  file = fopen(argv[1], "r");
  bus.file = file;
  if (!file) {
    fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  while ((content = fgets(bus.buffer, BUFFER_SIZE, file)) != NULL) {
    size_t len = strchr(bus.buffer, '\n') - bus.buffer;
    if (len > 0 && bus.buffer[len - 1] == '\n') {
      bus.buffer[len - 1] = '\0'; // remove newline character
    }
    counter++;
    execute(bus.buffer, &stack, counter, file);
  }

  free_stack(stack);
  fclose(file);

  return 0;
}
