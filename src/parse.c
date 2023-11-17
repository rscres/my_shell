/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:27:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/17 14:47:30 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_type(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(str, ">"))
		return (OUTFILE);
	else if (!ft_strcmp(str, "<"))
		return (INFILE);
	else if (!ft_strcmp(str, "&&"))
		return (AND);
	else if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (WORD);
}

char	*trim_quotes(char *token)
{
	char	*tmp;

	if (!token)
		return (NULL);
	if (*token == '\'' || *(token + ft_strlen(token) - 1) == '\'')
		tmp = ft_strtrim(token, "\'");
	else if (*token == '\"' || *(token + ft_strlen(token) - 1) == '\"')
		tmp = ft_strtrim(token, "\"");
	else
		tmp = ft_strdup(token);
	free(token);
	return (tmp);
}

int	parse_line(char **str)
{
	char	*token;
	char	*trim;
	int		expand;
	char	*new_str;

	token = tokenizer(*str);
	expand = 1;
	while (token)
	{
		if (token[0] == '\'' && get_type(token) == WORD)
			expand = 0;
		trim = trim_quotes(token);
		add_token(trim, get_type(trim), expand);
		free(trim);
		token = tokenizer(NULL);
		expand = 1;
	}
	while (g_main.open_quote)
	{
		new_str = readline("> ");
		token = tokenizer(new_str);
		while (token)
		{
			trim = trim_quotes(token);
			add_token(trim, get_type(trim), expand);
			free(trim);
			token = tokenizer(NULL);
		}
		*str = ft_strjoin(*str, "\n");
		*str = ft_strjoin(*str, new_str);
		free(new_str);
	}
	// if (g_main.open_quote)
	// {
	// 	ft_putstr_fd("Error: unclosed quotes\n", 2);
	// 	g_main.open_quote = 0;
	// 	clear_token_list();
	// 	return (1);
	// }
	//---move this block----
	create_cmd_list();
	expand_var(g_main.cmd_list->args);
	// parse_tree(); //need to code this
	g_main.status = exec_builtin(g_main.cmd_list->name, g_main.cmd_list->args);
	clear_token_list();
	clear_cmd_list();
	//---move this block----
	if (token)
		free(token);
	return (0);
}

// int	parse_line(char **str)
// {
// 	char	*token;
// 	// char	*new_str;
// 	char	*trim;

// 	token = tokenizer(*str);
// 	while (token)
// 	{
// 		trim = trim_quotes(token);
// 		add_token(trim, get_type(trim));
// 		free(trim);
// 		token = tokenizer(NULL);
// 	}
// 	//deal with open quotes-----------
// 	// while (g_main.open_quote)
// 	// {
// 	// 	new_str = readline("> ");
// 	// 	token = tokenizer(new_str);
// 	// 	while (token)
// 	// 	{
// 	// 		trim = trim_quotes(token);
// 	// 		add_token(trim, get_type(trim));
// 	// 		free(trim);
// 	// 		token = tokenizer(NULL);
// 	// 	}
// 	// 	*str = ft_strjoin(*str, "\n");
// 	// 	*str = ft_strjoin(*str, new_str);
// 	// 	free(new_str);
// 	// }
// 	//-----------------------------------
// 	// t_token	*tmp = g_main.tokens;
// 	// while (tmp)
// 	// {
// 	// 	printf("%s=>", tmp->name);
// 	// 	printf("%i\n", tmp->type);
// 	// 	tmp = tmp->next;
// 	// }
// 	clear_tokens();
// 	if (token)
// 		free(token);
// 	return (0);
// }