#include "rtv1.h"

int		is_min(double a, double b, double c, double d)
{
	if ((a > 0 && !b && !c && !d))
		return (1);
	if ((a > 0) && (b || c || d) && (a < b || a < c || a < d))
		return (1);
	return (0);
}

double	min_dist(t_env *e)
{
	if (is_min(e->sphere.dist, e->cone.dist, e->plane.dist, e->cyli.dist))
		fill_inter_sphere(&e->light, &e->sphere, &e->inter, &e->view);

	else if (is_min(e->cone.dist, e->sphere.dist, e->plane.dist, e->cyli.dist))
		fill_inter_cone(&e->light, &e->cone, &e->inter, &e->view);

	else if (is_min(e->cyli.dist, e->cone.dist, e->sphere.dist, e->plane.dist))
		fill_inter_cyli(&e->light, &e->cyli, &e->inter, &e->view);

	else if (is_min(e->plane.dist, e->cone.dist, e->cyli.dist, e->sphere.dist))
		fill_inter_plane(&e->light, &e->plane, &e->inter, &e->view);
	return (0);
}

void	check_dist(t_env *e)
{
	int		xy;

	xy = e->pix.y * WIN_Y + e->pix.x;
	e->inter.dist_min = min_dist(e);
	e->img.img[xy]  = e->inter.col.i;
}

void	check_collision(t_env *e)
{
	init_inter(&e->inter);
	init_ray(&e->view, &e->pix);
	is_plane(&e->view, &e->plane, &e->light, &e->inter);
	is_sphere(&e->view, &e->sphere, &e->light, &e->inter);
	is_cyli(&e->view, &e->cyli, &e->light, &e->inter);
	is_cone(&e->view, &e->cone, &e->light, &e->inter);
	printf("sphere %f cone %f plane %f cyli %f\n\n",
			e->sphere.dist, e->cone.dist, e->plane.dist, e->cyli.dist);
	check_dist(e);
}
