/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 12:42:09 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/15 12:43:45 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_plane(t_plane *plane, char **buff)
{
	char	**tab_line;

	if (!(tab_line = ft_strsplit(*buff, ' ')))
		error_msg(2);
	if (!tab_line[0] || (!tab_line[1] && ft_strcmp(tab_line[0], "}")))
		error_msg(3);
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&plane->center, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&plane->col, buff);
	else if (!ft_strcmp(tab_line[0], "direction"))
		get_coord(&plane->norm, buff);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		plane_values(int fd, t_plane *plane, t_list **list)
{
	char	*buff;

	get_next_line(fd, &buff);
	while (!ft_strchr(buff, '}'))
	{
		get_next_line(fd, &buff);
		parse_plane(plane, &buff);
	}
	dot_sub(&plane->norm, &plane->center, &plane->norm);
	normalize(&plane->norm, &plane->norm);
	ft_lstback(list, plane, sizeof(*plane));
}

void		parse_view(t_view *view, char **buff)
{
	char	**tab_line;

	if (!(tab_line = ft_strsplit(*buff, ' ')))
		error_msg(2);
	if (!tab_line[0] || (!tab_line[1] && ft_strcmp(tab_line[0], "}")))
		error_msg(3);
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&view->coord, buff);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		view_values(int fd, t_view *view)
{
	char	*buff;

	get_next_line(fd, &buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_view(view, &buff);
	}
}
