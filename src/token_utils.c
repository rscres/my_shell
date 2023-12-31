/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:23:01 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/15 19:03:11 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*new_token(char *name, int type, int expand)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->name = ft_strdup(name);
	token->type = type;
	token->expand = expand;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token(char *name, int type, int expand)
{
	t_token	*tmp;

	if (g_main.token_list == NULL)
	{
		g_main.token_list = new_token(name, type, expand);
		return ;
	}
	tmp = g_main.token_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token(name, type, expand);
	tmp->next->prev = tmp;
}

void	clear_token_list(void)
{
	t_token	*tmp;

	while (g_main.token_list)
	{
		tmp = g_main.token_list;
		g_main.token_list = g_main.token_list->next;
		free(tmp->name);
		free(tmp);
	}
}
