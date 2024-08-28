/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:06:30 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/27 18:20:27 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 	ft_echo(t_command *list, char **env)
{
	int		k;
	bool	flag;
	char	**new;
	int		i;

	(void)env;
	k = 1;
	flag = false;
	while (list->arg[k])
	{
		if (list->arg[k][0] == '-' && list->arg[k][1] != '\0')
		{
			i = 1;
			while (list->arg[k][i] == 'n')
			{
				i++;
			}
			if (list->arg[k][i] != '\0')
			{
				break ;
			}
			flag = true;
		}
		else
		{
			break ;
		}
		k++;
	}
	if (test_redir_here_doc(list) == 1 )
	{
    	hundle_redirections(list);
		new = ft_new_args(list->arg, list->doc);
		execution_cmd(list, new, env);
	}
	while (list->arg[k])
	{
		printf("{...} %s", list->arg[k]);
		if (list->arg[k + 1] != NULL)
			printf(" ");
		k++;
	}
	if (!flag || k == 1)
		printf("\n");
}
// 		i=0;
// 		while (list->arg[k][i])
// 		{
// 			if (list->arg[k][0] == '-' && list->arg[k][i+1] == 'n')
// 			{
// 				printf("list->arg[k][i] = %c\n", list->arg[k][i]);
// 				flag = true;
// 			}
// 			else
// 			{
// 				flag = false;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if(flag == false)
// 			break ;
// 		k++;
// 	}
// k--;
// if (flag == true)
// {
// 	while (list->arg[k])
// 	{
// 		j = 0;
// 		while (list->arg[k][j])
// 		{
// 			write(1, &list->arg[k][j], 1);
// 			j++;
// 		}
// 		write(1, "[]\n", 4);
// 		k++;
// 	}
// }

// else
// {
// 	write(1, "\n", 1);
// 	return (0);
// }
// 	if (k > 0)
// 	{
// 		ft_echo_flag(list , k );
// 		if (test_redir_here_doc(list) == 1)
// 		{
// 			new = ft_new_args(list->arg, list->doc);
// 			execution_cmd(list, new, env);
// 		}
// 	}
// 	else if ( k == 1)
// 	{
// 		i = 1;
// 		while (list->arg[i])
// 		{
// 			j = 0;
// 			while (list->arg[i][j])
// 			{
// 				write(1, &list->arg[i][j], 1);
// 				j++;
// 			}
// 			write(1, " ", 2);
// 			i++;
// 		}
// 		write(1, "\n", 1);
// 		if (test_redir_here_doc(list) == 1)
// 		{
// 			printf("..............................\n\n");

// 			new = ft_new_args(list->arg, list->doc);
// 			execution_cmd(list, new, env);
// 		}
// 	}

// 	return (1);
// }

// void	ft_echo_flag(t_command *list , int k)
// {
// 	printf("kkkkkkkkkkkkkkkkkkk   = %d\n", k);
// 	// int	j;
// 	while (list->arg[k])
// 	{
// 		printf("%s", list->arg[k]);
// 		if (list->arg[k + 1])
// 			printf(" ");
// 		k++;
// 	}
// }
