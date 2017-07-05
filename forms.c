#include "rtv1.h"

int		check_shadow(t_env *e)
{
	return (0);
}

void	check_collision(t_env *e)
{
	init_inter(&e->inter);
	init_ray(&e->view, &e->pix);
	is_plane(&e->view.ray, &e->plane, &e->light, &e->inter);
	is_sphere(&e->view.ray, &e->sphere, &e->light, &e->inter);
	is_cyli(&e->view.ray, &e->cyli, &e->light, &e->inter);
	is_cone(&e->view.ray, &e->cone, &e->light, &e->inter);
	e->img.img[e->pix.y * WIN_Y + e->pix.x]  = e->inter.col.i;
}
