/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:22:50 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/14 10:04:53 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int i;

	i = 0;
	while ((s1[i] || s2[i]) && n)
	{
		if (s1[i] - s2[i])
			return (0);
		i++;
		n--;
	}
	return (1);
}
