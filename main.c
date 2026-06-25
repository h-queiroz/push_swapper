#include "push_swapper.h"	// COLORS Macro, t_stacks
#include <stdio.h>			// printf(), scanf()
#include <stdlib.h>			// calloc(), free(), atoi()
#include <string.h>			// strcmp()

// 1. Receber números ---------------------------------------------------- **DONE**
// 2. Validar que são números (A decidir o que fazer com não números) ----
// 3. Colocá-los em uma stackA ------------------------------------------- **DONE**
// 4. Criar stackB de tamanho idêntico preenchida por zeros -------------- **DONE**
// 5. Listar stacks bem formatado como está no PDF ----------------------- **DONE**
// 6. Receber comandos --------------------------------------------------- **DONE**
// 7. Fazer comandos funcionar ------------------------------------------- **PARTIAL**

static t_stacks	init_stacks(int ac, char **av);
static unsigned	int	stack_len(int *stack);
static void	list_nums(t_stacks stacks);
static e_operation	get_operation();
static void	apply_operation(e_operation op, t_stacks stacks);
static void	swap_first_two(int *stack);

int	main(int ac, char **av)
{
	t_stacks	stacks;
	e_operation	current_op;

	stacks = init_stacks(ac, av);

	list_nums(stacks);
	while ((current_op = get_operation()) != QUIT)
	{
		// printf("OP: %d\n", current_op);
		apply_operation(current_op, stacks);
		list_nums(stacks);
	}

	free(stacks.s_a);
	free(stacks.s_b);
	return (0);
}

// Maneira complicada de printar
// { 1, 2, 3, 4 }
// { 0, 5, 6, 7 }
//
// Maneira simples de printar
// { 4, 3, 2, 1 }
// { 7, 6, 5, 0 }
//
// 1
// 2	5
// 3	6
// 4	7
//
// Inicia a StackA com números e StackB do mesmo tamanho mas zerada
// Se receber parâmetros de números, os adiciona a StackA
// Se NÃO receber parâmetro nenhum, começa a StackA com valores {4, 3, 2, 1}
//
// OBS1: Os números são inseridos nos arrays "ao contrário". Ou seja,
// os valores do FUNDO da stack estão no COMEÇO do array,
// enquanto os do TOPO se encontram ao FINAL do array
// Fiz desta maneira para facilitar o modo de se printar os números na vertical
//
// OBS2: Não estou fazendo checagem de números válidos ainda
static t_stacks	init_stacks(int ac, char **av)
{
	t_stacks	stacks;
	int			i;
	int			j;

	j = 1;
	if (ac <= 1)
	{
		stacks.s_a = calloc(TMP_LEN, sizeof(int));
		stacks.s_b = calloc(TMP_LEN, sizeof(int));
		stacks.length = TMP_LEN;
		i = (stacks.length - 1);
		while (i >= 0)
			stacks.s_a[i--] = j++;
	}
	else
	{
		stacks.s_a = calloc((ac - 1), sizeof(int));
		stacks.s_b = calloc((ac - 1), sizeof(int));
		stacks.length = (ac - 1);
		i = (stacks.length - 1);
		while (i >= 0)
			stacks.s_a[i--] = atoi(av[j++]);
	}
	return (stacks);
}

// Returns amount of elements in determined Stack
static unsigned	int	stack_len(int *stack)
{
	unsigned int	i;

	i = 0;
	while (stack[i] != 0)
		i++;
	return (i);
}

// Printa a lista de números de maneira bem formatada
static void	list_nums(t_stacks stacks)
{
	int	i;

	i = (stacks.length - 1);
	printf(RED "#############\n");
	printf(GREEN "Init A and B:\n");
	while (i >= 0)
	{
		printf(YELLOW);
		if (stacks.s_a[i] != 0)
			printf("%5d", stacks.s_a[i]);
		else
			printf("\t");
		if (stacks.s_b[i] != 0)
			printf("%5d\n", stacks.s_b[i]);
		else
			printf("\n");
		i--;
	}
	printf(CYAN "-----\t-----\n");
	printf("  A\t  B\n");
	printf(RED "#############\n");
	printf(RESET);
}

// Prompts user to insert one operation to be done,
// applies it to the stacks and print it on the screen
//
// OBS1: Case Insensitive. E.g. (Sa == SA == sa == sA).
static e_operation	get_operation()
{
	e_operation	op;
	char		input[3];

	op = 0;
	printf("List of Operations, case insensitive:\n");
	printf("(sa) - Swap A\n");
	printf("(sb) - Swap B\n");
	printf("(ss) - Swap Both\n");
	printf("(pa) - Push A\n");
	printf("(pb) - Push B\n");
	printf("(q)  - Quit\n");
	printf("-------------------\n");
	while (op == 0)
	{
		printf("Insert operation: ");
		scanf("%2s", input); // Gets only first 2 chars at maximum

		if (strcmp(input, "sa") == 0 || strcmp(input, "Sa") == 0 || strcmp(input, "sA") == 0 || strcmp(input, "SA") == 0)
			return (SA);
		else if (strcmp(input, "sb") == 0 || strcmp(input, "Sb") == 0 || strcmp(input, "sB") == 0 || strcmp(input, "SB") == 0)
			return (SB);
		else if (strcmp(input, "ss") == 0 || strcmp(input, "Ss") == 0 || strcmp(input, "sS") == 0 || strcmp(input, "SS") == 0)
		{
			printf("Swappping 2 top elements from both Stacks\n");
			op = SS;
		}
		else if (strcmp(input, "pa") == 0 || strcmp(input, "Pa") == 0 || strcmp(input, "pA") == 0 || strcmp(input, "PA") == 0)
		{
			printf("Pushing Stack B top element to Stack A top\n");
			op = PA;
		}
		else if (strcmp(input, "pb") == 0 || strcmp(input, "Pb") == 0 || strcmp(input, "pB") == 0 || strcmp(input, "PB") == 0)
		{
			printf("Pushing Stack A top element to Stack B top\n");
			op = PB;
		}
		else if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			printf("Quitting\n");
			op = QUIT;
		}
		else
		{
			printf("Invalid Operation\n");
			op = INVALID;
		}
	}
	return (op);
}

// Apply given operation to stacks
static void	apply_operation(e_operation op, t_stacks stacks)
{
	if (op == SA)
		swap_first_two(stacks.s_a);
	if (op == SB)
		swap_first_two(stacks.s_b);
}

// Swap the first two elements at the top of stack.
// (Do nothing if there is only one or no elements)
static void	swap_first_two(int *stack)
{
	unsigned int len;
	int temp;

	len = stack_len(stack);
	if (len >= 2)
	{
		printf("Swappping 2 top elements from Stack\n");
		temp = stack[len - 1];
		stack[len - 1] = stack[len - 2];
		stack[len - 2] = temp;
	}
	else
		printf("Not enough elements in Stack\n");
}
