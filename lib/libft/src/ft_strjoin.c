/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:13:22 by narajaon          #+#    #+#             */
/*   Updated: 2017/09/26 14:58:51 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ptr = str;
	while (s1[i])
		*ptr++ = s1[i++];
	while (s2[j])
		*ptr++ = s2[j++];
	return (str);
}
