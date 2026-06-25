#ifndef PUSH_SWAPPER_H
# define PUSH_SWAPPER_H

typedef struct s_stacks
{
	int	*s_a;
	int	*s_b;
	int	length;
}	t_stacks;

typedef enum
{
	SA = 1,			// (swap A) - Swap the first two elements at the top of stack A. (Do nothing if there is only one or no elements)
	SB,				// (swap B) - Swap the first two elements at the top of stack B. (Do nothing if there is only one or no elements)
	SS,				// SA and SB at the same time.
	PA,				// (push A) - Take the first element at the top of B and put it at the top of A. (Do nothing if B is empty)
	PB,				// (push B) - Take the first element at the top of A and put it at the top of B. (Do nothing if A is empty)
	QUIT,			// Quits program
	INVALID = 0,	// Anything other than the above or "q" "quit"
}	e_operation;

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
