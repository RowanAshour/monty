#include "monty.h"

/**
 * main - Entry point for the Monty interpreter
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: Exit status
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	stack_t *stack = NULL;
	char opcode[256];
	unsigned int line_number = 1;

	while (fscanf(file, "%s", opcode) != EOF)
	{
		if (opcode[0] == '#')
		{
			char ch;
			while ((ch = fgetc(file)) != EOF && ch != '\n')
				;
			line_number++;
			continue;
		}

		if (strcmp(opcode, "push") == 0)
		{
			int value;
			if (fscanf(file, "%d", &value) == EOF)
			{
				fprintf(stderr, "L%u: usage: push integer\n", line_number);
				fclose(file);
				free_stack(stack);
				return (EXIT_FAILURE);
			}
			push(&stack, value, line_number);
		}
		else if (strcmp(opcode, "pall") == 0)
		{
			pall(&stack, line_number);
		}
		else if (strcmp(opcode, "pint") == 0)
		{
			pint(&stack, line_number);
		}
		else if (strcmp(opcode, "pop") == 0)
		{
			pop(&stack, line_number);
		}
		else if (strcmp(opcode, "swap") == 0)
		{
			swap(&stack, line_number);
		}
		else if (strcmp(opcode, "add") == 0)
		{
			add(&stack, line_number);
		}
		else if (strcmp(opcode, "nop") == 0)
		{
			nop(&stack, line_number);
		}
		else if (strcmp(opcode, "sub") == 0)
		{
			sub(&stack, line_number);
		}
		else if (strcmp(opcode, "div") == 0)
		{
			div_op(&stack, line_number);
		}
		else if (strcmp(opcode, "mul") == 0)
		{
			mul_op(&stack, line_number);
		}
		else if (strcmp(opcode, "mod") == 0)
		{
			mod_op(&stack, line_number);
		}

		line_number++;
	}

	fclose(file);
	free_stack(stack);

	return (EXIT_SUCCESS);
}

