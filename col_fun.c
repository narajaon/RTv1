#include "rtv1.h"

void	init_col(t_col *col, char r, char g, char b)
{
	col->tab[0] = b;
	col->tab[1] = g;
	col->tab[2] = r;
	col->tab[3] = 0x00;
}

int		mult_col(t_col *col1, t_col *col2) //absorbtion
{
	t_col		new_col;

	new_col.tab[0] = col1->tab[0] * col2->tab[0];
	new_col.tab[1] = col1->tab[1] * col2->tab[1];
	new_col.tab[2] = col1->tab[2] * col2->tab[2];
	new_col.tab[3] = 0x00;
	return (new_col.i);
}

int		add_col(t_col *col1, t_col *col2) //mixing 2 colours
{
	t_col		new_col;

	new_col.tab[0] = col1->tab[0] + col2->tab[0];
	new_col.tab[1] = col1->tab[1] + col2->tab[1];
	new_col.tab[2] = col1->tab[2] + col2->tab[2];
	new_col.tab[3] = 0x00;
	return (new_col.i);
}

int		gamma_cor(t_col *col, double expos, double gamma)
{
	t_col		new_col;

	new_col.tab[0] = pow(col->tab[0] * expos, gamma);
	new_col.tab[1] = pow(col->tab[1] * expos, gamma);
	new_col.tab[2] = pow(col->tab[2] * expos, gamma);
	new_col.tab[3] = 0x00;
	return (new_col.i);
}
