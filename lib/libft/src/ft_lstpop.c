/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 18:09:24 by narajaon          #+#    #+#             */
/*   Updated: 2017/09/23 18:19:38 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstpop(t_list **list, int (*cmp)(), void *to_cmp)
{
	t_list		*tmp;

	tmp = *list;
	if (tmp != NULL)
	{
		if (cmp(tmp->content, to_cmp) == 0)
		{
			*list = tmp->next;
			free(tmp->content);
			free(tmp);
			tmp = NULL;
		}
		else
		{
			while (tmp->next && cmp(tmp->next, to_cmp) != 0)
				tmp = tmp->next;
			if (tmp != NULL)
			{
				free(tmp->next->content);
				free(tmp->next);
				tmp->next = tmp->next->next;
			}
		}
	}
}
