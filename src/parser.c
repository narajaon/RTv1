/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:31:09 by narajaon          #+#    #+#             */
/*   Updated: 2018/01/31 14:57:55 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void		get_coord(t_coor *coord, char **buff)
{
	char	*tmp;
	char	**tab_coord;

	tmp = *buff;
	while (*tmp != ' ' && *tmp)
		tmp++;
	if (!(tab_coord = ft_strsplit(tmp, ' ')))
		error_msg(2);
	if (!tab_coord[0] || !tab_coord[1] || !tab_coord[2])
		error_msg(3);
	coord->x = ft_atoi(tab_coord[0]);
	coord->y = ft_atoi(tab_coord[1]);
	coord->z = ft_atoi(tab_coord[2]);
	free_tab(tab_coord);
}

void		get_shape_col(t_col *col, char **buff)
{
	char	*tmp;

	tmp = *buff;
	while (*tmp != ' ' && *tmp)
		tmp++;
	tmp++;
	if (!ft_strcmp(tmp, "RED"))
		col->i = RED;
	else if (!ft_strcmp(tmp, "GREEN"))
		col->i = GREEN;
	else if (!ft_strcmp(tmp, "YELLOW"))
		col->i = YELLOW;
	else if (!ft_strcmp(tmp, "WHITE"))
		col->i = WHITE;
	else if (!ft_strcmp(tmp, "BLUE"))
		col->i = BLUE;
	else
		error_msg(3);
}

void		get_values(int fd, t_env *e)
{
	char		*buff;
	int			ret;

	e->spheres = NULL;
	e->cylinders = NULL;
	e->cones = NULL;
	e->planes = NULL;
	while ((ret = get_next_line(fd, &buff)) > 0)
	{
		if (!ft_strcmp(buff, "view"))
			view_values(fd, &e->view);
		else if (!ft_strcmp(buff, "plane"))
			plane_values(fd, &e->plane, &e->planes);
		else if (!ft_strcmp(buff, "cylinder"))
			cyli_values(fd, &e->cyli, &e->cylinders);
		else if (!ft_strcmp(buff, "cone"))
			cone_values(fd, &e->cone, &e->cones);
		else if (!ft_strcmp(buff, "sphere"))
			sphere_values(fd, &e->sphere, &e->spheres);
		else if (!ft_strcmp(buff, "light"))
			light_values(fd, &e->light);
	}
	(ret < 0) ? error_msg(3) : 1;
}
