#include "rtv1.h"

double		dot_prod(t_coor *a, t_coor *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double		vect_pow(t_coor *a)
{
	return (pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
}

double		vect_len(t_coor *a)
{
	return (sqrt(vect_pow(a)));
}

void		dot_mult(t_coor *a, t_coor *tmp, double nb)
{
	tmp->x = a->x * nb;
	tmp->y = a->y * nb;
	tmp->z = a->z * nb;
}

void		normalize(t_coor *a, t_coor *tmp)
{
	float		len;

	len = vect_len(a);
	dot_mult(a, tmp, 1 / len);
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

void		dot_add(t_coor *a, t_coor *tmp, int nb)
{
	tmp->x = a->x + nb;
	tmp->y = a->y + nb;
	tmp->z = a->z + nb;
}

void		dot_sum(t_coor *a, t_coor *b, t_coor *tmp)
{
	tmp->x = a->x + b->x;
	tmp->y = a->y + b->y;
	tmp->z = a->z + b->z;
}

void		dot_cpy(t_coor *src, t_coor *dst)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

void		point_on_ray(t_coor *origin, t_coor *direction, t_coor * res, float len)
{
	dot_mult(direction, res, len);
	dot_sum(res, origin, res);
}

void		fill_coord(t_coor *coord, float x, float y, float z)
{
	coord->x = x;
	coord->y = y;
	coord->z = z;
}
