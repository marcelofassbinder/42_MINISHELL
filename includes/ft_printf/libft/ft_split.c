/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:01:29 by mfassbin          #+#    #+#             */
/*   Updated: 2023/10/28 13:57:33 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if ((s[i] != c) && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

static int	next_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **s, int n)
{
	while (n >= 0)
		free(s[n--]);
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		j;
	int		n;

	n = count_words(s, c);
	result = ft_calloc (sizeof(char *), n + 1);
	if (!s || !result)
		return (NULL);
	j = 0;
	while (j < n)
	{
		if (*s != c)
		{
			result[j] = (char *)ft_calloc(sizeof(char), next_word(s, c) + 1);
			if (!result[j])
				return (ft_free(result, j));
			ft_strlcpy(result[j], s, next_word(s, c) + 1);
			s += next_word(s, c);
			j++;
		}
		s++;
	}
	return (result);
}
/* 
#include <stdio.h>

int main(void)
{
	char s[] = "split  ||this|for|me|||||!|";
	char **r = ft_split(s, '|');
	
	printf("%s\n", r[0]);
	printf("%s\n", r[1]);
	printf("%s\n", r[2]);
	printf("%s\n", r[3]);
	printf("%s\n", r[4]);
	printf("%s\n", r[5]);
} */