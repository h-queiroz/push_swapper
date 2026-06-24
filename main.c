#include "push_swapper.h"
#include <stdio.h>			// printf()
#include <stdlib.h>			// calloc(), free(), atoi()

// 1. Receber números ---------------------------------------------------- **DONE**
// 2. Validar que são números (A decidir o que fazer com não números) ----
// 3. Colocá-los em uma lista -------------------------------------------- **DONE**
// 4. Listá-los como está no PDF ----------------------------------------- **DONE**
// 5. Criar comandos e fazê-los funcionar --------------------------------

static int	*init_nums(int ac, char **av);
static void	list_nums(const int *nums);

int	main(int ac, char **av)
{
	int	*nums;

	nums = init_nums(ac, av);
	list_nums(nums);
	free(nums);
	return (0);
}

// Inicia a lista de números
// Se receber parâmetros de números, os adiciona a lista
// Se NÃO receber parâmetro nenhum, começa com uma lista inicial de valor {1, 2, 3, 4}
// Não estou fazendo checagem de números válidos ainda
static int	*init_nums(int ac, char **av)
{
	int	i;
	int *nums;

	i = 0;
	if (ac <= 1)
	{
		nums = calloc(4, sizeof(int));
		while ((i++) < 4)
			nums[i - 1] = i;
	}
	else
	{
		nums = calloc((ac - 1), sizeof(int));
		while (av[++i])
			nums[i - 1] = atoi(av[i]);
	}
	return (nums);
}

// Printa a lista de números de maneira bem formatada
static void	list_nums(const int *nums)
{
	printf(RED "##################################\n");
	printf(GREEN "Init A and B:\n");
	while (*nums)
		printf(YELLOW "%5d\n", *(nums++));
	printf(CYAN "-----\t-----\n");
	printf("  A\t  B\n");
	printf(RED "##################################\n");
	printf(RESET);
}
