/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 12:42:02 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/15 13:25:39 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_sphere(t_sphere *sphere, char **buff)
{
	char	**tab_line;

	if (!(tab_line = ft_strsplit(*buff, ' ')))
		error_msg(2);
	if (!tab_line[0] || (!tab_line[1] && ft_strcmp(tab_line[0], "}")))
		error_msg(3);
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&sphere->coord, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&sphere->col, buff);
	else if (!ft_strcmp(tab_line[0], "width"))
		sphere->r = ft_atoi(tab_line[1]);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		sphere_values(int fd, t_sphere *sphere, t_list **list)
{
	char	*buff;

	get_next_line(fd, &buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_sphere(sphere, &buff);
	}
	ft_lstback(list, sphere, sizeof(*sphere));
}

void		parse_cone(t_cone *cone, char **buff)
{
	char	**tab_line;

	if (!(tab_line = ft_strsplit(*buff, ' ')))
		error_msg(2);
	if (!tab_line[0] || (!tab_line[1] && ft_strcmp(tab_line[0], "}")))
		error_msg(3);
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&cone->center, buff);
	else if (!ft_strcmp(tab_line[0], "direction"))
		get_coord(&cone->vertex, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&cone->col, buff);
	else if (!ft_strcmp(tab_line[0], "width"))
		cone->angle = tan(ft_atoi(tab_line[1]) * PI / 180);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		cone_values(int fd, t_cone *cone, t_list **list)
{
	char	*buff;

	get_next_line(fd, &buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_cone(cone, &buff);
	}
	dot_sub(&cone->center, &cone->vertex, &cone->hei);
	normalize(&cone->hei, &cone->hei);
	ft_lstback(list, cone, sizeof(*cone));
}
