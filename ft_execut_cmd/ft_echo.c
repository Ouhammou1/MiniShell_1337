/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:06:30 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/01 23:38:32 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	complet_function(t_command *list, int k, bool flag)
{
	char	**new;

	if (test_redir_here_doc(list) == 1)
	{
		hundle_redirections(list);
		new = ft_new_args(list->arg, list->doc);
		execution_cmd(list, new);
	}
	while (list->arg[k])
	{
		printf("%s", list->arg[k]);
		if (list->arg[k + 1] != NULL)
			printf(" ");
		k++;
	}
	if (!flag || k == 1)
		printf("\n");
}

void	ft_echo(t_command *list)
{
	int		k;
	bool	flag;
	bool	flag_dolar;
	int		i;

	k = 1;
	flag = false;
	flag_dolar = false;
	while (list->arg[k])
	{
		if (list->arg[k][0] == '-' && list->arg[k][1] != '\0')
		{
			i = 1;
			while (list->arg[k][i] == 'n')
				i++;
			if (list->arg[k][i] != '\0')
				break ;
			flag = true;
		}
		else
			break ;
		k++;
	}
	complet_function(list, k, flag);
}
