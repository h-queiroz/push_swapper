#include "push_swapper.h"	// COLORS Macro, t_stacks
#include <stdio.h>			// printf(), scanf()
#include <stdlib.h>			// calloc(), free(), atoi()
#include <string.h>			// strcmp()

//  1. Receber números ---------------------------------------------------------- **DONE**
//  2. Validar que são números (A decidir o que fazer com não números) ----------
//  3. Colocá-los em uma stackA ------------------------------------------------- **DONE**
//  4. Criar stackB de tamanho idêntico preenchida por zeros -------------------- **DONE**
//  5. Listar stacks bem formatado como está no PDF ----------------------------- **DONE**
//  6. Receber operações -------------------------------------------------------- **DONE**
//  7. Fazer operações funcionar ------------------------------------------------ **DONE**
//  8. Receber arquivo como argumento, seguindo pela flag "-f" ------------------
//  9. Ler operação de cada linho do arquivo recebido e aplicar as stacks -------
// 10. Criar função de comparar strings, case insensitive -----------------------

static t_stacks		init_stacks(int ac, char **av);
static unsigned	int	stack_len(int *stack, int max_len);
static void			print_stacks(t_stacks stacks);
static e_operation	get_operation(void);
static void			apply_operation(e_operation op, t_stacks stacks);
static void			swap_first_two(int *stack, int max_len);
static void			push_to_dest(int *stack_dest, int *stack_src, int max_len);
static void			rotate_upwards(int *stack, int max_len);
static void			rotate_downwards(int *stack, int max_len);

int	main(int ac, char **av)
{
	t_stacks	stacks;
	e_operation	current_op;

	stacks = init_stacks(ac, av);
	print_stacks(stacks);
	while ((current_op = get_operation()) != QUIT)
	{
		// printf("OP: %d\n", current_op);
		apply_operation(current_op, stacks);
		print_stacks(stacks);
	}
	printf("Quitting.\n");
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
static unsigned	int	stack_len(int *stack, int max_len)
{
	unsigned int	i;

	i = 0;
	while (stack[i] != 0 && i < (unsigned int)max_len)
		i++;
	return (i);
}

// Printa a lista de números de maneira bem formatada
static void	print_stacks(t_stacks stacks)
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

		if (stacks.s_a[i] == 0 && stacks.s_b[i] != 0)
			printf("%5d\n", stacks.s_b[i]);
		else if (stacks.s_a[i] != 0 && stacks.s_b[i] != 0)
			printf("\t%5d\n", stacks.s_b[i]);
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
static e_operation	get_operation(void)
{
	char		input[4];

	printf("List of Operations, case insensitive:\n");
	printf("(sa)  - Swap A\n");
	printf("(sb)  - Swap B\n");
	printf("(ss)  - Swap Both\n");
	printf("(pa)  - Push A\n");
	printf("(pb)  - Push B\n");
	printf("(ra)  - Rotate A\n");
	printf("(rb)  - Rotate B\n");
	printf("(rr)  - Rotate Both\n");
	printf("(rra) - Reverse Rotate A\n");
	printf("(rrb) - Reverse Rotate B\n");
	printf("(rrr) - Reverse Rotate Both\n");
	printf("(q)   - Quit\n");
	printf("-------------------\n");
	while (1)
	{
		printf("Insert operation: ");
		scanf("%3s", input); // Gets only first 2 chars at maximum

		if (strcmp(input, "sa") == 0 || strcmp(input, "Sa") == 0 || strcmp(input, "sA") == 0 || strcmp(input, "SA") == 0)
			return (SA);
		else if (strcmp(input, "sb") == 0 || strcmp(input, "Sb") == 0 || strcmp(input, "sB") == 0 || strcmp(input, "SB") == 0)
			return (SB);
		else if (strcmp(input, "ss") == 0 || strcmp(input, "Ss") == 0 || strcmp(input, "sS") == 0 || strcmp(input, "SS") == 0)
			return (SS);
		else if (strcmp(input, "pa") == 0 || strcmp(input, "Pa") == 0 || strcmp(input, "pA") == 0 || strcmp(input, "PA") == 0)
			return (PA);
		else if (strcmp(input, "pb") == 0 || strcmp(input, "Pb") == 0 || strcmp(input, "pB") == 0 || strcmp(input, "PB") == 0)
			return (PB);
		else if (strcmp(input, "ra") == 0 || strcmp(input, "Ra") == 0 || strcmp(input, "rA") == 0 || strcmp(input, "RA") == 0)
			return (RA);
		else if (strcmp(input, "rb") == 0 || strcmp(input, "Rb") == 0 || strcmp(input, "rB") == 0 || strcmp(input, "RB") == 0)
			return (RB);
		else if (strcmp(input, "rr") == 0 || strcmp(input, "Rr") == 0 || strcmp(input, "rR") == 0 || strcmp(input, "RR") == 0)
			return (RR);
		else if (strcmp(input, "rra") == 0 || strcmp(input, "Rra") == 0 || strcmp(input, "rRa") == 0 || strcmp(input, "rrA") == 0 || strcmp(input, "RRa") == 0 || strcmp(input, "RrA") == 0 || strcmp(input, "rRA") == 0 || strcmp(input, "RRA") == 0)
			return (RRA);
		else if (strcmp(input, "rrb") == 0 || strcmp(input, "Rrb") == 0 || strcmp(input, "rRb") == 0 || strcmp(input, "rrB") == 0 || strcmp(input, "RRb") == 0 || strcmp(input, "RrA") == 0 || strcmp(input, "rRA") == 0 || strcmp(input, "RRA") == 0)
			return (RRB);
		else if (strcmp(input, "rrr") == 0 || strcmp(input, "Rrr") == 0 || strcmp(input, "rRr") == 0 || strcmp(input, "rrR") == 0 || strcmp(input, "RRr") == 0 || strcmp(input, "RrA") == 0 || strcmp(input, "rRA") == 0 || strcmp(input, "RRA") == 0)
			return (RRR);
		else if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
			return (QUIT);
		else
			printf("Invalid Operation\n");
	}
}

// Apply given operation to stacks
static void	apply_operation(e_operation op, t_stacks stacks)
{
	if (op == SA)
		swap_first_two(stacks.s_a, stacks.length);
	if (op == SB)
		swap_first_two(stacks.s_b, stacks.length);
	if (op == SS)
	{
		swap_first_two(stacks.s_a, stacks.length);
		swap_first_two(stacks.s_b, stacks.length);
	}
	if (op == PA)
		push_to_dest(stacks.s_a, stacks.s_b, stacks.length);
	if (op == PB)
		push_to_dest(stacks.s_b, stacks.s_a, stacks.length);
	if (op == RA)
		rotate_upwards(stacks.s_a, stacks.length);
	if (op == RB)
		rotate_upwards(stacks.s_b, stacks.length);
	if (op == RR)
	{
		rotate_upwards(stacks.s_a, stacks.length);
		rotate_upwards(stacks.s_b, stacks.length);
	}
	if (op == RRA)
		rotate_downwards(stacks.s_a, stacks.length);
	if (op == RRB)
		rotate_downwards(stacks.s_b, stacks.length);
	if (op == RRR)
	{
		rotate_downwards(stacks.s_a, stacks.length);
		rotate_downwards(stacks.s_b, stacks.length);
	}
}

// Swap the first two elements at the top of stack.
// (Do nothing if there is only one or no elements)
static void	swap_first_two(int *stack, int max_len)
{
	unsigned int	len;
	int				temp;

	len = stack_len(stack, max_len);
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

// Takes the first element at the top of SRC Stack and put it at the top of DEST Stack.
// (Do nothing if SRC Stack is empty)
static void	push_to_dest(int *stack_dest, int *stack_src, int max_len)
{
	int src_len = stack_len(stack_src, max_len);
	if (src_len >= 1)
	{
		printf("Pushing top element from SRC Stack to the top of DEST Stack\n");
		stack_dest[stack_len(stack_dest, max_len)] = stack_src[src_len - 1];
		stack_src[src_len - 1] = 0;
	}
	else
		printf("Not enough elements in SRC Stack\n");
}

// Shifts up all elements of the Stack by one
// The first element becomes the last one
static void	rotate_upwards(int *stack, int max_len)
{
	int	temp;
	int	i;

	if (stack_len(stack, max_len) >= 2)
	{
		printf("Pushing the top element of Stack to the bottom, and shifting up all other elements\n");
		i = stack_len(stack, max_len) - 1;
		temp = stack[i];
		while ((--i) >= 0)
			stack[i + 1] = stack[i];
		stack[0] = temp;
	}
	else
		printf("Not enough elements in Stack\n");
}

// Shift down all elements of stack a by one
// The last element becomes the first one
static void	rotate_downwards(int *stack, int max_len)
{
	int				temp;
	unsigned int	i;
	unsigned int	len;

	len = stack_len(stack, max_len);
	if (len >= 2)
	{
		printf("Pushing the bottom element of Stack to the top, and shifting down all other elements\n");
		i = 0;
		temp = stack[i];
		while ((++i) < len)
			stack[i - 1] = stack[i];
		stack[len - 1] = temp;
	}
	else
		printf("Not enough elements in Stack\n");
}
