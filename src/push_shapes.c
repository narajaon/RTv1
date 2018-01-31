/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:47:44 by narajaon          #+#    #+#             */
/*   Updated: 2018/01/31 14:58:27 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void		ft_lstback(t_list **alst, void const *content, size_t size)
{
	t_list		*lst;

	lst = *alst;
	if (!lst)
		*alst = ft_lstnew(content, size);
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = ft_lstnew(content, size);
	}
}

void		free_list(t_list **shape)
{
	t_list		*list;

	list = *shape;
	while (list)
	{
		free(list->content);
		list = list->next;
	}
	(*shape) ? free(*shape) : 0;
}

void		exit_rt(t_env *e)
{
	free_list(&e->spheres);
	free_list(&e->planes);
	free_list(&e->cones);
	free_list(&e->cylinders);
	close(e->fd);
	mlx_destroy_image(e->mlx, e->img.img_ptr);
	mlx_destroy_window(e->mlx, e->win);
	error_msg(0);
}
