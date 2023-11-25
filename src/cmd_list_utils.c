/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:12:27 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/24 21:26:36 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd	*new_cmd(char *name)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(name);
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (g_main.cmd_list == NULL)
	{
		g_main.cmd_list = cmd;
		return ;
	}
	tmp = g_main.cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

void	clear_cmd_list(void)
{
	t_cmd	*tmp;
	int		i;

	while (g_main.cmd_list)
	{
		tmp = g_main.cmd_list;
		g_main.cmd_list = g_main.cmd_list->next;
		i = 0;
		while (i < tmp->argc)
		{
			ft_safe_free((void **)&tmp->args[i]);
			i++;
		}
		ft_safe_free((void **)&tmp->args);
		ft_safe_free((void **)&tmp->name);
		ft_safe_free((void **)&tmp);
	}
}

//------------------TEST FUNCTIONS------------------//
//------------------TEST FUNCTIONS------------------//
void	print_cmd_list(void)
{
	t_cmd	*tmp;
	int		i;

	tmp = g_main.cmd_list;
	while (tmp)
	{
		printf("cmd = %s\n", tmp->name);
		i = 0;
		while (i < tmp->argc)
		{
			printf("arg[%i] = %s\n", i, tmp->args[i]);
			i++;
		}
		printf("argc = %i\n", tmp->argc);
		tmp = tmp->next;
	}
}
//------------------TEST FUNCTIONS------------------//
//------------------TEST FUNCTIONS------------------//