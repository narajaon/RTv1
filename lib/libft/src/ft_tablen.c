/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 03:46:23 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 17:11:56 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tablen(char **tab)
{
	int	count;

	count = 0;
	if (tab != NULL)
	{
		while (tab[count] != NULL)
			count++;
		return (count);
	}
	return (-1);
}
