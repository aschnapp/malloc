#include "malloc.h"

void	ft_putnbr(int n)
{
	unsigned int	nb;
  char c;

	if (n < 0)
	{
		nb = -n;
		write(1, "-", 1);
	}
	else
		nb = n;
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
    ft_putnbr(nb % 10);
	}
	else
	{
    c = nb + '0';
    write(1, &c, 1);
  }
}
