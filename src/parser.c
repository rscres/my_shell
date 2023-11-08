/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:55:50 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/08 18:23:30 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char	*update_save(char *save, int i)
{
	char	*tmp;

	tmp = ft_strdup(save + i);
	free(save);
	return (tmp);
}

char	*tokenizer(char *str)
{
	static char	*save;
	char		*token;
	int			i;
	int			j;

	i = 0;
	if (str)
		save = ft_strdup(str);
	while (save[i] && ft_iswhitespace(save[i]))
		i++;
	if (save[i] == '\0')
	{
		if (save)
			free(save);
		return (NULL);
	}
	j = i;
	while (save[j] && !ft_iswhitespace(save[j]))
		j++;
	token = ft_strndup(save + i, j - i);
	save = update_save(save, j);
	return (token);
}

int	get_type(char *token)
{
	if (ft_strcmp(token, ">>") == 0)
		return (DOUBLE_GREATER_THAN);
	if (ft_strcmp(token, "<<") == 0)
		return (DOUBLE_LESS_THAN);
	if (ft_strcmp(token, ">") == 0)
		return (GREATER_THAN);
	if (ft_strcmp(token, "<") == 0)
		return (LESS_THAN);
	if (ft_strcmp(token, "&&") == 0)
		return (AND);
	if (ft_strcmp(token, "||") == 0)
		return (OR);
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	return (WORD);
}

t_token	*create_token(char *str, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->name = ft_strdup(str);
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	clear_tokens(void)
{
	t_token	*tmp;

	while (g_main.tokens)
	{
		tmp = g_main.tokens;
		g_main.tokens = g_main.tokens->next;
		free(tmp->name);
		free(tmp);
	}
}

void	add_token(t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (g_main.tokens == NULL)
		g_main.tokens = new;
	else
	{
		tmp = g_main.tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	syntax_analyser()
{

}

int	parse_line(char *str)
{
	char	*token;

	token = tokenizer(str);
	while (token)
	{
		add_token(create_token(token, get_type(token)));
		free(token);
		token = tokenizer(NULL);
	}
	t_token	*tmp = g_main.tokens;
	while (tmp)
	{
		printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	clear_tokens();
	return (0);
}

// int main(void)
// {
// 	char	*line;
// 	char	*token;

// 	line = get_line();
// 	while (line)
// 	{
// 		token = tokenizer(line);
// 		while (token)
// 		{
// 			printf("%s\n", token);
// 			free(token);
// 			token = tokenizer(NULL);
// 		}
// 		free(line);
// 		line = get_line();
// 	}
// 	return (0);
// }