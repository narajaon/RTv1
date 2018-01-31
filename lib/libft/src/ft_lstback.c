/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:58:35 by narajaon          #+#    #+#             */
/*   Updated: 2017/09/30 18:55:24 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstback(t_list **alst, void const *content, size_t size)
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
