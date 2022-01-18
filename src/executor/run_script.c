/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_script.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:22:27 by skoh              #+#    #+#             */
/*   Updated: 2022/01/18 21:23:10 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*next_string_find(char *search, char delimiter)
{
	char	quote;

	--search;
	while (*++search)
	{
		if (quote == '"' && *search == '\\' && *search && ++search)
			continue ;
		if (quote)
		{
			if (*search == quote)
				quote = '\0';
			continue ;
		}
		if (*search == delimiter)
			return (search);
		if (*search == '"' || *search == '\'')
			quote = *search;
	}
	return (NULL);
}

static bool	next_string(char **dup, char **search, char delimiter)
{
	char	*found;

	*dup = NULL;
	if (*search == NULL)
		return (false);
	found = next_string_find(*search, delimiter);
	if (found)
	{
		*dup = ft_strndup(*search, found - *search);
		*search = found + 1;
	}
	else
	{
		*dup = ft_strdup(*search);
		*search = NULL;
	}
	return (true);
}

int	run_script(char *input, char **envp)
{
	t_prompt	prompt;
	char		*part;

	ft_bzero(&prompt, sizeof(prompt));
	prompt.env = init_env(envp);
	change_dir(&prompt, ".");
	while (next_string(&part, &input, ';'))
	{
		prompt.full_cmds = part;
		if (get_cmds(&prompt.cmds, &prompt))
			prompt.e_status = execute_line(prompt.cmds, &prompt);
		cleanup_cmd(&prompt);
	}
	cleanup(&prompt);
	return (prompt.e_status);
}
