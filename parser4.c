/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 12:43:54 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/15 12:44:36 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_cyli(t_cyli *cyli, char **buff)
{
	char	**tab_line;

	if (!(tab_line = ft_strsplit(*buff, ' ')))
		error_msg(2);
	if (!tab_line[0] || (!tab_line[1] && ft_strcmp(tab_line[0], "}")))
		error_msg(3);
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&cyli->center, buff);
	else if (!ft_strcmp(tab_line[0], "direction"))
		get_coord(&cyli->cap_u, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&cyli->col, buff);
	else if (!ft_strcmp(tab_line[0], "width"))
		cyli->r = ft_atoi(tab_line[1]);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		cyli_values(int fd, t_cyli *cyli, t_list **list)
{
	char	*buff;

	get_next_line(fd, &buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_cyli(cyli, &buff);
	}
	dot_sub(&cyli->center, &cyli->cap_u, &cyli->hei);
	normalize(&cyli->hei, &cyli->hei);
	ft_lstback(list, cyli, sizeof(*cyli));
}

void		parse_light(t_light *light, char **buff)
{
	char	**tab_line;

	if (!(tab_line = ft_strsplit(*buff, ' ')))
		error_msg(2);
	if (!tab_line[0] || (!tab_line[1] && ft_strcmp(tab_line[0], "}")))
		error_msg(3);
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&light->coord, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&light->col, buff);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		light_values(int fd, t_light *light)
{
	char	*buff;

	get_next_line(fd, &buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_light(light, &buff);
	}
}
