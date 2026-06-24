#include "push_swapper.h"
#include <stdio.h>			// printf()
#include <stdlib.h>			// calloc(), free(), atoi()

// 1. Receber números ---------------------------------------------------- **DONE**
// 2. Validar que são números (A decidir o que fazer com não números) ----
// 3. Colocá-los em uma lista -------------------------------------------- **DONE**
// 4. Listá-los como está no PDF ----------------------------------------- **DONE**
// 5. Criar comandos e fazê-los funcionar --------------------------------

static void	list_nums(const int *nums);

int	main(int ac, char **av)
{
	int tmp[] = {1, 2, 3, 4};
	int	*nums;
	int	i;

	if (ac <= 1)
		nums = &(tmp[0]);
	else
	{
		nums = calloc((ac - 1), sizeof(int));
		i = 0;
		while (av[++i])
			nums[i - 1] = atoi(av[i]);
	}
	list_nums(nums);
	return (0);
}

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
