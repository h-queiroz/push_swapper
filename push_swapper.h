#ifndef PUSH_SWAPPER_H
# define PUSH_SWAPPER_H

typedef struct s_stacks
{
	int	*s_a;
	int	*s_b;
	int	length;
}	t_stacks;

// Default stack_a length if no arguments are provided
# define TMP_LEN 4

// COLOR MACROS
# define BLACK	"\033[1;30m"
# define RED		"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define WHITE	"\033[1;37m"
# define RESET	"\033[0m"

#endif // PUSH_SWAPPER_H
