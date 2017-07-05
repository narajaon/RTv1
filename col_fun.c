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

double			clamp_col(double col, double cos, char light)
{
	if (cos < 0)
		return (0x00);
	if (col * cos * 255 > 255)
		return (col * cos / 255);
	return (col * cos);
}

unsigned int	put_col(t_light *light, t_inter *inter, t_col *shape)
{
	t_col		col;
	double		b;
	double		g;
	double		r;

	b = clamp_col(shape->tab[0], inter->cos_alph, light->col.tab[0]) * 255;
	g = clamp_col(shape->tab[1], inter->cos_alph, light->col.tab[1]) * 255;
	r = clamp_col(shape->tab[2], inter->cos_alph, light->col.tab[2]) * 255;
	init_col(&inter->col, r, g, b);
	inter->col.i = mult_col(&inter->col, &light->col);
	return (inter->col.i);
}
