#include "rtv1.h"

int		check_shadow(t_env *e)
{
	if (check_shadow_sphere(e->spheres, e))
		return (1);
	if (check_shadow_cylinder(e->cylinders, e))
		return (1);
	if (check_shadow_cone(e->cones, e))
		return (1);
	return (0);
}

int		check_collision(t_env *e)
{
	init_inter(&e->inter);
	init_ray(&e->view, &e->pix);
	is_plane(&e->view.ray, &e->plane, &e->light, &e->inter);
	closest_sphere(e->spheres, e);
	closest_cylinder(e->cylinders, e);
	closest_cone(e->cones, e);
	if (check_shadow(e))
		return (e->img.img[e->pix.y * WIN_Y + e->pix.x] =
				shad_col(&e->inter, e->inter.shape, &e->light));
	return (e->img.img[e->pix.y * WIN_Y + e->pix.x]  = e->inter.col.i);
}
