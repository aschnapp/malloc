#include "malloc.h"

void	ft_putnbr_hex(uintptr_t nb)
{
  char c;

	if (nb >= 16)
	{
		ft_putnbr_hex(nb / 16);
		ft_putnbr_hex(nb % 16);
	}
	else
	{
    if (nb % 16 < 10)
			c = nb % 16 + '0';
		else
			c = nb % 16 - 10 + 'A';
		write(1, &c, 1);
  }
}
