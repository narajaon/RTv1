#include "rtv1.h"

int		check_shadow(t_env *e)
{
	if (shad_sphere(&e->inter.ray, &e->sphere, &e->light))
		return (1);
	if (shad_cone(&e->inter.ray, &e->cone, &e->light))
		return (1);
	if (shad_plane(&e->inter.ray, &e->plane, &e->light))
		return (1);
	if (shad_cyli(&e->inter.ray, &e->cyli, &e->light))
		return (1);
	return (0);
}

int		check_collision(t_env *e)
{
	init_inter(&e->inter);
	init_ray(&e->view, &e->pix);
	if (is_plane(&e->view.ray, &e->plane, &e->light, &e->inter))
	{
		if (check_shadow(e))
			return (e->img.img[e->pix.y * WIN_Y + e->pix.x]  = 0);
	}
	is_sphere(&e->view.ray, &e->sphere, &e->light, &e->inter);
	if (check_shadow(e))
		return (e->img.img[e->pix.y * WIN_Y + e->pix.x]  = 0);
	is_cyli(&e->view.ray, &e->cyli, &e->light, &e->inter);
	if (check_shadow(e))
		return (e->img.img[e->pix.y * WIN_Y + e->pix.x]  = 0);
	is_cone(&e->view.ray, &e->cone, &e->light, &e->inter);
	if (check_shadow(e))
		return (e->img.img[e->pix.y * WIN_Y + e->pix.x]  = 0);
	return (e->img.img[e->pix.y * WIN_Y + e->pix.x]  = e->inter.col.i);
}
