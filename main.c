#include <stdio.h>
#include <stdlib.h>

typedef struct stack_s
{
    	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

typedef struct bus_s
{
    	char *arg;
	FILE *file;
	char *content;
	int lifi;
} bus_t;

bus_t bus = {NULL, NULL};

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t capacity = 128;
    size_t index = 0;
    int ch;

    if (*lineptr == NULL)
    {
        *lineptr = (char *)malloc(capacity);
        if (*lineptr == NULL)
            return -1;
        *n = capacity;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n')
    {
        (*lineptr)[index++] = (char)ch;

        if (index == *n - 1)
        {
            capacity *= 2;
            char *temp = realloc(*lineptr, capacity);
            if (temp == NULL)
                return -1;
            *lineptr = temp;
            *n = capacity;
        }
    }

    if (index > 0)
        (*lineptr)[index] = '\0';
    else
        return -1;

    return (ssize_t)index;
}




int main(int argc, char *argv[])
{
    char *content;
    FILE *file;
    size_t size = 0;
    ssize_t read_line = 1;
    stack_t *stack = NULL;
    unsigned int counter = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
    file = fopen(argv[1], "r");
    bus.file = file;
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while (read_line > 0)
    {
        content = NULL;
        read_line = custom_getline(&content, &size, file);
        bus.content = content;
        counter++;
        if (read_line > 0)
        {
            execute(content, &stack, counter, file);
        }
        free(content);
    }
    free_stack(stack);
    fclose(file);
    return 0;
}
