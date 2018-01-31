/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_uni.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 19:01:07 by narajaon          #+#    #+#             */
/*   Updated: 2017/11/24 03:03:15 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putstr_uni(unsigned int *uni, char *str)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (uni[i])
		ret += ft_putuni_str(uni[i++], &str[ret]);
	return (ret);
}
