/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:18:46 by renato            #+#    #+#             */
/*   Updated: 2024/02/02 22:06:22 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	backup_fd(int backup[2])
{
	backup[0] = dup(0);
	backup[1] = dup(1);
}

void	restore_fd(int backup[2])
{
	dup2(backup[0], 0);
	close(backup[0]);
	dup2(backup[1], 1);
	close(backup[1]);
}

// void	prep_exit(t_cmd *cmd, int backup[2])
// {
// 	restore_fd(backup);
// 	close(0);
// 	close(1);
// 	ft_exit(cmd->args, cmd->argc);
// }

int	set_fd_in(t_cmd *cmd)
{
	if (cmd->infile != NULL)
	{
		cmd->fd[0] = open(cmd->infile, O_RDONLY);
		if (cmd->fd[0] < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->infile, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	set_fd_out(t_cmd *cmd)
{
	if (cmd->outfile != NULL)
	{
		if (cmd->redir[1] == APPEND)
			cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (cmd->redir[1] == OUTFILE)
			cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd[1] < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->outfile, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	exec_builtin(t_cmd *cmd)
{
	// int	backup[2];

	// backup_fd(backup);
	// set_fd(cmd);
	int fd_set[2];

	fd_set[0] = set_fd_in(cmd);
	fd_set[1] = set_fd_out(cmd);
	if (!ft_strcmp(cmd->name, "echo"))
		g_main.status = (ft_echo(cmd->args + 1, cmd->fd[1]));
	else if (!ft_strcmp(cmd->name, "cd"))
		g_main.status = (ft_cd(cmd->args));
	else if (!ft_strcmp(cmd->name, "pwd"))
		g_main.status = (ft_pwd(cmd->fd[1]));
	else if (!ft_strcmp(cmd->name, "export"))
		g_main.status = (ft_export(cmd->args, cmd->argc, cmd->fd[1]));
	else if (!ft_strcmp(cmd->name, "unset"))
		g_main.status = (ft_unset(cmd->args + 1));
	else if (!ft_strcmp(cmd->name, "env"))
		g_main.status = (ft_env());
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd->args, cmd->argc);
		// prep_exit(cmd, backup);
	else if (!ft_strcmp(cmd->name, "<<"))
		heredoc(cmd->args[0]);
	if (fd_set[0] == 0)
		close(cmd->fd[0]);
	if (fd_set[1] == 0)
		close(cmd->fd[1]);
	// restore_fd(backup);
	return (0);
}
