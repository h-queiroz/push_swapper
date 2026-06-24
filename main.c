#include "push_swapper.h"	// COLORS Macro, t_stacks
#include <stdio.h>			// printf()
#include <stdlib.h>			// calloc(), free(), atoi()

// 1. Receber números ---------------------------------------------------- **DONE**
// 2. Validar que são números (A decidir o que fazer com não números) ----
// 3. Colocá-los em uma stackA ------------------------------------------- **DONE**
// 4. Criar stackB de tamanho idêntico preenchida por zeros -------------- **DONE**
// 5. Listar stacks bem formatado como está no PDF ----------------------- **DONE**
// 6. Receber comandos ---------------------------------------------------
// 7. Fazer comandos funcionar -------------------------------------------

static t_stacks	init_stacks(int ac, char **av);
static void	list_nums(t_stacks stacks);

int	main(int ac, char **av)
{
	t_stacks stacks;

	stacks = init_stacks(ac, av);
	list_nums(stacks);
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
	t_stacks stacks;
	int	i;
	int	j;

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

// Printa a lista de números de maneira bem formatada
static void	list_nums(t_stacks stacks)
{
	int i;

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
