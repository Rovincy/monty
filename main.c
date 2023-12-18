#include <stdio.h>
#include <string.h>
#include "monty.h"

#define BUFFER_SIZE 256 // Adjust as needed for expected line length

/* Global bus structure definition */
bus_t bus = { NULL, NULL, NULL, 0 };

/**
 * main - monty code interpreter
 * @argc: Number of arguments
 * @argv: Monty file location
 * Return: 0 on success
 */
int main(int argc, char *argv[]) {
  // Check for correct number of arguments
  if (argc != 2) {
    fprintf(stderr, "USAGE: monty file\n");
    exit(EXIT_FAILURE);
  }

  // Open Monty file
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  bus.file = file; // Associate file with bus structure

  // Initialize variables
  char buffer[BUFFER_SIZE]; // Buffer to store each line
  unsigned int counter = 0; // Line counter
  stack_t *stack = NULL; // Stack head pointer

  // Loop through each line in the file
  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    // Remove newline character if present
    size_t len = strchr(buffer, '\n') - buffer;
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    }

    // Process line number and execute command
    counter++;
    execute(buffer, &stack, counter, file); // Call your `execute` function
  }

  // Clean up resources
  free_stack(stack); // Free allocated memory for stack
  fclose(file); // Close the Monty file

  return 0; // Exit successfully
}
