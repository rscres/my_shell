/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:49:46 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/01 13:45:05 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Join two strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i <= (int)len1)
		*(str + i) = *(s1 + i);
	i -= 1;
	while (i++ < (int)(len2 + len1))
		*(str + i - 1) = *(s2 + i - len1 - 1);
	*(str + i - 1) = '\0';
	return (str);
}

//Joins two strings and frees the first one
char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i <= (int)len1)
		*(str + i) = *(s1 + i);
	i -= 1;
	while (i++ < (int)(len2 + len1))
		*(str + i - 1) = *(s2 + i - len1 - 1);
	*(str + i - 1) = '\0';
	ft_safe_free((void **)&s1);
	return (str);
}
