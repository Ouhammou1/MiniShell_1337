/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/07 22:33:30 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void  ft_exute( t_envarment *var , t_command *list , t_splitor *x)
{

	(void) var;
	(void) x;	
	if (list == NULL)
		return ;

	if(ft_strcmp(list->content , "exit") == 0)
	{
		exit(0);
	}
		
	else if(ft_strcmp(list->content, "cd") == 0)
		ft_cd(list);
		
	else if (ft_strcmp(list->content, "pwd") == 0 )
	{
		ft_pwd(list);
	}
	
	else if(ft_strcmp(list->content, "export") == 0)
		ft_export(var , list );
		
	// else if(ft_strcmp(list->str_input, "unset") == 0)
	// 	ft_unset(var , list );

	// else if(ft_strcmp(list->str_input, "env") == 0)
	// 	ft_env(var , list );		
		

	else
	{

		int pid = fork();
		if(pid < 0)
			perror("fork");
		else if(pid == 0)
		{
			printf("----------------------------->>>>>  %s \n", list->arg[0]);
			char *ptr = path_command(list->arg[0]);
			if (!ptr)
			{
				printf("command not found\n");
				exit(127);
			}
			printf("\033[31m********* --> ++++++++++++++++++++++++++++++++++++ <-- **********\033[0m\n");
			if(execve(ptr, list->arg, NULL) == -1)
			{
				perror("execve");
			}
				
			if (access(ptr, X_OK) == -1)
				exit(126);
		}
		else
		{
			int status;
			if(wait(&status) == -1)
				perror("wait");
		}
	}
}