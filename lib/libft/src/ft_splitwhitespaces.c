/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 19:51:39 by awyart            #+#    #+#             */
/*   Updated: 2017/10/06 18:14:02 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_word(char const *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			count++;
		while ((s[i] != ' ' && s[i] != '\t' && s[i] != '\n') && s[i])
			i++;
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}

static int		word_len(char *s)
{
	int i;

	i = 0;
	while ((s[i] != ' ' && s[i] != '\t' && s[i] != '\n') && s[i])
		i++;
	return (i);
}

char			**ft_split_whitespaces(char *s)
{
	char	**tab;
	int		i;
	int		j;
	int		jc;
	int		word;

	i = 0;
	j = 0;
	word = nb_word(s);
	if (!(tab = (char **)malloc(sizeof(char *) * (word + 2))))
		return (NULL);
	while (word)
	{
		jc = 0;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		tab[j] = (char *)malloc(sizeof(char *) * (word_len(s + i) + 1));
		while ((s[i] != ' ' && s[i] != '\t' && s[i] != '\n') && s[i])
			tab[j][jc++] = s[i++];
		tab[j][jc] = '\0';
		j++;
		word--;
	}
	tab[j] = NULL;
	return (tab);
}
