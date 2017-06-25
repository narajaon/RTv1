#include "rtv1.h"

unsigned int	put_col_sphere(t_light *light, t_inter *inter, t_plane *plane)
{
	return (1);
}

void	fill_inter_plane(t_light *light, t_plane *plane,
		t_inter *inter, t_view *view)
{
}

int		is_plane(t_view *view, t_plane *plane, t_light *light, t_inter *inter)
{
	float		dn;
	float		t;
	t_coor		tmp;
	t_coor		hit;

	dn = dot_prod(&view->ray.direction, &plane->norm);
	if (dn < 0.00001)
		return (0);
	t = dot_prod(&plane->center, &plane->norm);
	t = (t - dot_prod(&view->ray.direction, &plane->norm)) / dn;
	if (t <= RAY_MIN || t >= RAY_MAX)
		return (plane->dist = 0);
	fill_inter_plane(light, plane, inter, view);
	return (plane->dist = t);
}
