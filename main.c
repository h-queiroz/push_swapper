#include <stdio.h> // printf()
#include <stdlib.h> // atoi()

// 1. Receber números
// 2. Validar que são números (A decidir o que fazer com não números)
// 3. Colocá-los em uma lista
// 4. Listá-los como está no PDF
// 5. Criar comandos e fazê-los funcionar

int	main(int ac, char **av)
{
	char	**nums;
	// Listar argumentos, mesmo que não receba nenhum
	(void)ac;
	nums = (av + 1);
	if (ac == 1)
	{
		*(nums + 0) = "1";
		*(nums + 1) = "2";
		*(nums + 2) = "3";
		*(nums + 3) = "4";
		*(nums + 4) = NULL;
	}
	while (*nums)
		printf("%s\n", *(nums++));

	return (0);
}
