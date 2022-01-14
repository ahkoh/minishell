/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:40:17 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/14 10:41:05 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

/* if the arg exists in the env variable
   shift the env variable and free it
   then add the arg into the env variable */
static void	add_env(t_prompt *prompt, char *s)
{
	int	a;
	int	b;

	a = 0;
	while (prompt->env[a] != NULL)
	{
		b = 0;
		while (s[b] != '=')
		{
			if (prompt->env[a][b] != s[b])
				break ;
			b++;
		}
		if (s[b] == '=' && prompt->env[a][b] == '=')
			free(ft_shift(prompt->env + a));
		else
			a++;
	}
	prompt->env[a] = ft_strdup(s);
}

/* get a copy of the env variable */
static char	**cpy_env(char **envp)
{
	int		a;
	char	**env;

	env = malloc(sizeof(char *) * 1001);
	a = 0;
	while (envp[a])
	{
		env[a] = ft_strdup(envp[a]);
		a++;
	}
	env[a] = NULL;
	return (env);
}

/* if export has no arg, make a copy of env variable
   then sort and display them in order */
static void	display_ordered_env(char **env)
{
	int		a;
	char	**cpy;

	a = 0;
	while (env[a])
		a++;
	cpy = cpy_env(env);
	ft_str_qsort(cpy, 0, a - 1);
	a = 0;
	while (cpy[a])
	{
		printf("declare -x %s\n", cpy[a]);
		free(cpy[a]);
		a++;
	}
	free(cpy);
}

/* checks and see if the arg is valid
   if yes add the env into env variable
   if no display error and change the exit status to 1 */
int	mini_export(t_prompt *prompt, char **argv)
{
	int	a;
	int	b;

	a = 0;
	prompt->e_status = 0;
	while (argv[a])
	{
		b = 0;
		while (argv[a][b] != '\0'
			&& (ft_isalnum(argv[a][b]) || argv[a][b] == '_'))
			b++;
		if (ft_isdigit(argv[a][0]) || (!ft_isalnum(argv[a][b])
			&& argv[a][b] != '\0' && argv[a][b] != '_' && argv[a][b] != '='))
		{
			printf("export: '%s': not a valid identifier\n", argv[a]);
			prompt->e_status = 1;
		}
		if (argv[a][b] == '=' && b != 0 && !ft_isdigit(argv[a][0]))
			add_env(prompt, argv[a]);
		a++;
	}
	if (a == 0)
		display_ordered_env(prompt->env);
	return (prompt->e_status);
}

int	export(char **argv, t_prompt *prompt)
{
	return (mini_export(prompt, argv + 1));
}
