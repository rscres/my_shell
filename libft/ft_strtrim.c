/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 23:50:46 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/08 00:51:44 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Trim the beginning and the end of a string with the characters in set
//Return a new string
char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*end;
	char		*trim;

	end = s1 + ft_strlen(s1);
	trim = NULL;
	while (*s1)
	{
		if (!ft_strchr(set, *s1))
			break ;
		s1++;
	}
	while (end != s1)
	{
		if (!ft_strchr(set, *(end - 1)))
			break ;
		end--;
	}
	trim = malloc((ft_strlen(s1) - ft_strlen(end) + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, s1, (ft_strlen(s1) - ft_strlen(end) + 1));
	return ((char *)trim);
}
