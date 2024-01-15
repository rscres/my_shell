/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:32:42 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/14 18:07:05 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*check_path(char *name)
{
	char		*path;
	char		**paths;
	int			i;

	i = -1;
	path = search_value(g_main.env_var, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free(path, name);
		if (!access(path, F_OK))
		{
			free_tab(paths);
			return (path);
		}
		ft_safe_free((void **)&path);
	}
	free_tab(paths);
	return (NULL);
}

static void	exec(t_cmd *cmd, char *path)
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		return ;
	}
	if (pid == 0)
	{
		printf("out: %d\n", cmd->fd_out);
		if (cmd->fd_in != 0)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out != 1)
			dup2(cmd->fd_out, STDOUT_FILENO);
		if (execve(path, cmd->args, g_main.envp) == -1)
			ft_putstr_fd("execve error\n", 2);
		exit(1);
	}
	else
		waitpid(pid, &g_main.status, 0);
}

int	check_if_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0 || ft_strcmp(name, "<<") == 0)
		return (1);
	return (0);
}

void	execute_cmd_list(void)
{
	t_cmd	*cmd;
	char	*path;

	cmd = g_main.cmd_list;
	while (cmd)
	{
		if (cmd->type == WORD)
		{
			printf("fd_out: %d\n", cmd->fd_out);
			g_main.is_cmd_running = 1;
			if (check_if_builtin(cmd->name))
				g_main.status = exec_builtin(cmd->name, cmd->args, cmd->argc);
			else
			{
				path = check_path(cmd->name);
				if (!access(cmd->name, F_OK))
					exec(cmd, cmd->name);
				else if (path)
					exec(cmd, path);
				else
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->name, 2);
					ft_putstr_fd(": command not found\n", 2);
					g_main.status = 127;
				}
				ft_safe_free((void **)&path);
			}
			g_main.is_cmd_running = 0;
		}
		cmd = cmd->next;
	}
}