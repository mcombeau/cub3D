#include "libft.h"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putendl_fd("Bad arguments.", 2);
		return (1);
	}
	(void)av;
	return (0);
}
