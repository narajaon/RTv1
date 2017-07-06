#include "rtv1.h"

int		check_shadow(t_env *e)
{
	if (shad_cone(&e->inter.ray, &e->cone, &e->light))
		return (1);
	if (shad_sphere(&e->inter.ray, &e->sphere, &e->light))
		return (1);
	if (shad_cyli(&e->inter.ray, &e->cyli, &e->light))
		return (1);
	return (0);
}

int		check_collision(t_env *e)
{
	init_inter(&e->inter);
	init_ray(&e->view, &e->pix);
	is_plane(&e->view.ray, &e->plane, &e->light, &e->inter);
	is_sphere(&e->view.ray, &e->sphere, &e->light, &e->inter);
	is_cyli(&e->view.ray, &e->cyli, &e->light, &e->inter);
	is_cone(&e->view.ray, &e->cone, &e->light, &e->inter);
	//printf("shape %d\n", e->inter.shape);
	if (e->inter.shape == SPHERE)
		e->inter.shape = e->sphere.col.i;
	else if (e->inter.shape == CONE)
		e->inter.shape = e->cone.col.i;
	else if (e->inter.shape == CYLI)
		e->inter.shape = e->cyli.col.i;
	else if (e->inter.shape == PLANE)
		e->inter.shape = e->plane.col.i;
	//printf("col %d\n", e->inter.shape);
	if (check_shadow(e))
		return (e->img.img[e->pix.y * WIN_Y + e->pix.x] =
				shad_col(&e->inter, e->inter.shape, &e->light));
	return (e->img.img[e->pix.y * WIN_Y + e->pix.x]  = e->inter.col.i);
}
