#include "rtv1.h"

void	init_col(t_col *col, char r, char g, char b)
{
	col->tab[0] = b;
	col->tab[1] = g;
	col->tab[2] = r;
	col->tab[3] = 0x00;
}
