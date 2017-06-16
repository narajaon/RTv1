#include "rtv1.h"

double		dot_prod(t_coor *a, t_coor *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double		vect_len(t_coor *a)
{
	return (sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2)));
}

void		dot_mult(t_coor *a, t_coor *tmp, double nb)
{
	tmp->x = a->x * nb;
	tmp->y = a->y * nb;
	tmp->z = a->z * nb;
}

void		vect_norm(t_coor *a, t_coor *tmp, double len_a)
{
	dot_mult(a, tmp, 1 / len_a);
}

void		cross_prod(t_coor *a, t_coor *b, t_coor *tmp)
{
	tmp->x = a->y * b->z - a->z * b->y;
	tmp->y = a->z * b->x - a->x * b->z;
	tmp->z = a->x * b->y - a->y * b->x;
}

void		dot_sub(t_coor *a, t_coor *b, t_coor *tmp)
{
	tmp->x = a->x - b->x;
	tmp->y = a->y - b->y;
	tmp->z = a->z - b->z;
}

void		dot_sum(t_coor *a, t_coor *b, t_coor *tmp)
{
	tmp->x = a->x + b->x;
	tmp->y = a->y + b->y;
	tmp->z = a->z + b->z;
}
