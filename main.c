#include "push_swapper.h"
#include <stdio.h> // printf()

// 1. Receber números
// 2. Validar que são números (A decidir o que fazer com não números)
// 3. Colocá-los em uma lista
// 4. Listá-los como está no PDF
// 5. Criar comandos e fazê-los funcionar

void	list_nums(char **nums);

int	main(int ac, char **av)
{
	// int		*nums;
	char	**nums_str;
	// Listar argumentos, mesmo que não receba nenhum
	nums_str = (av + 1);
	if (ac == 1)
	{
		*(nums_str + 0) = "1";
		*(nums_str + 1) = "2";
		*(nums_str + 2) = "3";
		*(nums_str + 3) = "4";
		*(nums_str + 4) = NULL;
	}
	
	list_nums(nums_str);

	return (0);
}

void	list_nums(char **nums_str)
{
	printf(RED "##################################\n");
	printf(GREEN "Init A and B:\n");
	while (*nums_str)
		printf(YELLOW "%5s\n", *(nums_str++));
	printf(CYAN "-----\t-----\n");
	printf("  A\t  B\n");
	printf(RED "##################################\n");
	printf(RESET);
}
