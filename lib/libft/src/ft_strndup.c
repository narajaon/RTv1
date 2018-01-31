/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 17:37:59 by narajaon          #+#    #+#             */
/*   Updated: 2017/10/01 17:38:58 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strndup(const char *src, int n)
{
	char	*dup;
	int		i;

	i = 0;
	if (!(dup = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (src[i] && i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
