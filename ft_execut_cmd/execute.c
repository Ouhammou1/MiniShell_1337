/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/24 17:01:21 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	execution_cmd(t_command *list, char **new, char **env)
// {
// 	char	*ptr;
// 	int		pid;
// 	int		status;

// 	pid = fork();
// 	if (pid < 0)
// 		perror("fork");
// 	else if (pid == 0)
// 	{
// 		if (herdoc_exist(list) == 1)
// 		{
// 			handle_here_doc(list, env);
// 		}
// 		// printf("--------------------------\n");
// 		if (new[0][0] == '/')
// 			ptr = new[0];
// 		else
// 			ptr = path_command(new[0]);
// 		printf("ptr = %s\n", ptr);
// 		if (!ptr)
// 		{
// 			ft_putstr_fd("command not found\n", 2);
// 			// hundle_redirections(list);
// 			exit(127);
// 		}
// 		if(test_redir_here_doc(list) == 1)
// 		{
// 			hundle_redirections(list);
// 		}
		
// 		if (execve(ptr, new, env) == -1)
// 			perror("execve");
// 		if (access(ptr, X_OK) == -1)
// 			exit(126);
// 	}
// 	else
// 	{
// 		if (wait(&status) == -1)
// 			perror("wait");
// 	}
// }




void	hundle_redirections(t_command *list)
{
	printf(" tmp->store = %s\n", list->doc->store);
	t_redirect	*tmp;
	// int			redir;

	tmp = list->doc;
	// redir = 0;

	while (tmp != NULL )
	{
		printf("///////////////  hundle_redirections   /////////////////////// \n\n");
		printf("tmp->doc->type = %d  et tmp->doc->store = %s \n", tmp->type , tmp->store);
		if (tmp->type == REDIR_OUT)
		{
			hundle_redir_out(tmp->store);
			// redir = 1;
		}
		else if (tmp->type == REDIR_IN)
		{
			hundle_redir_in(tmp->store);
			// redir = 1;
		}
		else if (tmp->type == DREDIR_OUT)
		{
			// printf("tmp->doc->store =============================== = %s\n", tmp->doc->store);
			hundle_dredir_out(tmp->store);
			// redir = 1;
		}
		tmp = tmp->next;
	}
	// list = list->next;
	// return (redir);
}

int	built_in(t_envarment *var, t_command *list, char **env)
{
	if (list == NULL)
		return (0);
	if (ft_strcmp(list->content, "exit") == 0)
		return (ft_exit(var, list));
	if (ft_strcmp(list->content, "cd") == 0)
		return (ft_cd(list));
	if (ft_strcmp(list->content, "pwd") == 0)
		return (ft_pwd(list));
	if (ft_strcmp(list->content, "export") == 0)
		return (ft_export(var, list));
	if (ft_strcmp(list->content, "unset") == 0)
		return (ft_unset(var, list));
	if (ft_strcmp(list->content, "env") == 0)
		return (ft_env(var));
	if (ft_strcmp(list->content, "echo") == 0)
		return (ft_echo(list, env));
	return (0);
}

void	execution_cmd(t_command *list,char **new ,char **env)// char **new, char **env)
{
(void)list;
	char	*ptr;

		if (new[0][0] == '/')
			ptr = new[0];
		else
			ptr = path_command(new[0]);
		printf("ptr = %s\n", ptr);
		if (!ptr)
		{
			ft_putstr_fd("command not found\n", 2);
			exit(127);
		}
		if (execve(ptr, new , env) == -1)
			perror("execve");
		if (access(ptr, X_OK) == -1)
			exit(126);
}

void ft_exute(t_envarment *var, t_command *list, char **env)
{
    int fd;
    int status;
    char **new_args;

    printf("***************************************************************\n");
    printf("**************    \033[0;31m   Result of the Command   \033[0m******************\n");
    printf("***************************************************************\n\n");

    if (list == NULL)
        return;

    if (built_in(var, list, env))
        return;

    int pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        if (herdoc_exist(list))
        {
            handle_here_doc(list, env);
        }
        if (pipe_exist(list))
        {
            fd = handle_pipe(list, env);
            if (fd != -1)
            {
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
        }
        else
        {
            if (test_redir_here_doc(list))
            {
                hundle_redirections(list);
            }
            new_args = ft_new_args(list->arg, list->doc);
            execution_cmd(list, new_args, env);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        if (wait(&status) == -1)
        {
            perror("wait");
        }
    }
}




// void  ft_exute_o( t_envarment *var , t_command *list , char **env)
// {
// 	printf("***************************************************************\n");
// 	printf("**************    \033[0;31m   Result of the Command   \033[0m******************\n");
// 	printf("***************************************************************\n\n");

// 	(void)var;
// 	int pid ;
// 	int fd = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

// 	if (list == NULL)
// 		return ;
// 	pid = fork();
// 	if(pid < 0)
// 		perror("fork");
// 	else if(pid == 0)
// 	{
// 		if( herdoc_exist(list) == 1 && pipe_exist(list) == 0)
// 		{
// 			printf("1**********************1  \n\n");
// 			handle_here_doc(list,env);
// 			hundle_redirections(list);
// 			char **new = ft_new_args(list->arg, list->doc);
// 			printf("new[0] = %s\n", new[0]);
// 			execution_cmd(list,new, env);
// 		}
// 		else if (herdoc_exist(list) == 1 && pipe_exist(list) ==  1 )
// 		{
// 			printf("2**********************2  \n\n");
// 			handle_here_doc(list,env);
// 			fd = handle_pipe(list, env);
// 			dup2(fd, 1);
// 			close(fd);
// 		}
// 		else if (herdoc_exist(list) == 0 && pipe_exist(list) == 1)
// 		{
// 			printf("3**********************3  \n\n");
// 			fd = handle_pipe(list, env);
// 			dup2(fd, 1);
// 			close(fd);
// 		}
// 		else
// 		{
// 			printf("4**********************4  \n\n");
// 			if(test_redir_here_doc(list) == 1)
// 			{
// 				hundle_redirections(list);
// 			}
// 			char **new = ft_new_args(list->arg, list->doc);
// 			printf("new[0] = %s\n", new[0]);
// 			execution_cmd(list,new, env);
// 		}
// 	}
// 	else
// 	{
// 		int status;
// 		if(wait(&status) == -1)
// 			perror("wait");
// 	}
// }

// void  ft_exute( t_envarment *var , t_command *list , char **env)
// {
//                 printf("***************************************************************\n");
//                 printf("**************    \033[0;31m   Result of the Command   \033[0m******************\n");
//                 printf("***************************************************************\n\n");

//         if (list == NULL)
//                 return ;
				
//         if(ft_strcmp(list->content , "exit") == 0)
//             ft_exit(var , list);

//         else if(ft_strcmp(list->content, "cd") == 0)
//             ft_cd(list);

//         else if (ft_strcmp(list->content, "pwd") == 0)
//             ft_pwd(list);

//         else if(ft_strcmp(list->content, "export") == 0)
//             ft_export(var , list );
			
//         else if(ft_strcmp(list->content, "unset") == 0)
//             ft_unset(var , list );

//         else if(ft_strcmp(list->content, "env") == 0)
//             ft_env(var);

//         else if(ft_strcmp(list->content, "echo") == 0)
//             ft_echo(list,env);
//         else
//         {
// 			if(herdoc_exist(list) == 1)
// 			{printf("1\n\n");
// 					handle_here_doc(list,env);
// 			}
// 			if( pipe_exist(list) == 1)
// 			{printf("2\n\n");

// 					handle_pipe(list, env);
// 			}
// 			else
// 			{
// 				printf("3\n\n");
// 					char **new = ft_new_args(list->arg, list->doc);
// 					printf("new[0] = %s\n", new[0]);
// 					execution_cmd(list, new ,env);
// 			}
//         }
// }

// void	ft_exute(t_envarment *var, t_command *list, char **env)
// {
// 	char	**new;
// 	char	**new;

// 	printf("***************************************************************\n");
// 	printf("**************    \033[0;31m   Result of the Command   \033[0m******************\n");
// 	printf("***************************************************************\n\n");
// 	if (list == NULL)
// 		return ;
// 	// if(herdoc_exist(list) == 1)
// 	// {
// 	// 	built_in( var ,list  ,env);
// 	// 	handle_here_doc(list,env);
// 	// }
// 	// if( pipe_exist(list) == 1)
// 	// {
// 	// 	built_in( var ,list  ,env);
// 	// 	handle_pipe(list, env);
// 	// }
// 	// else
// 	// {
// 	// 	// char **new = ft_new_args(list->arg, list->doc);
// 	// 	// (void)new;
// 	// 	// built_in( var ,list  ,env);
// 	// 	if(built_in( var ,list  ,env) == 0)
// 	// 		execution_cmd(list, list->arg ,env);
// 	// }
// 	// if (herdoc_exist(list))
// 	// {
// 	// 	handle_here_doc(list, env);
// 	// }
// 	if (built_in(var, list, env))
// 	{
// 		return ;
// 	}
// 	if (pipe_exist(list))
// 	{
// 		if (test_redir_here_doc(list) == 1)
// 		{
// 			printf("..................................................\n");
// 			new = ft_new_args(list->arg, list->doc);
// 			execution_cmd(list, new, env);
// 		}
// 		handle_pipe(list, env);
// 	}
// 	// if(hundle_redirections(list) == 1)
// 	// {
// 	// 	printf("..................................................\n");
// 	// 	char **new = ft_new_args(list->arg, list->doc);
// 	// 	execution_cmd(list, new,env);
// 	// }
// 	else
// 	{
// 		if (test_redir_here_doc(list) == 1)
// 		{
// 			printf("..................................................\n");
// 			new = ft_new_args(list->arg, list->doc);
// 			execution_cmd(list, new, env);
// 		}
// 		else
// 			execution_cmd(list, list->arg, env);
// 	}
// }

// void  ft_exute( t_envarment *var , t_command *list , char **env)
// {
//                 printf("***************************************************************\n");
//                 printf("**************    \033[0;31m   Result of the Command   \033[0m******************\n");
//                 printf("***************************************************************\n\n");

//         if (list == NULL)
//                 return ;

//         if(ft_strcmp(list->content , "exit") == 0)
//                 ft_exit(var , list);

//         else if(ft_strcmp(list->content, "cd") == 0)
//                 ft_cd(list);

//         else if (ft_strcmp(list->content, "pwd") == 0)
//                 ft_pwd(list);

//         else if(ft_strcmp(list->content, "export") == 0)
//                 ft_export(var , list );

//         else if(ft_strcmp(list->content, "unset") == 0)
//                 ft_unset(var , list );

//         else if(ft_strcmp(list->content, "env") == 0)
//                 ft_env(var);

//         else if(ft_strcmp(list->content, "echo") == 0)
//                 ft_echo(list,env);
//         else
//         {
//                 if(herdoc_exist(list) == 1)
//                 {
//                         handle_here_doc(list,env);
//                 }
//                 if( pipe_exist(list) == 1)
//                 {
//                         handle_pipe(list, env);
//                 }
//                 else
//                 {
// 					printf("..........++++++++++++++ OK OK ++++++++++++++ .................\n");
//                         char **new = ft_new_args(list->arg, list->doc);
//                         (void)new;
//                         execution_cmd(list, list->arg ,env);
//                 }
//         }
// }

// void	ft_exute(t_envarment *var, t_command *list, char **env)
// {
// 	(void)var;


// 	if (list == NULL)
// 		return ;
// 	printf("***************************************************************\n");
// 	printf("**************    \033[0;31m   Result of the Command   \033[0m******************\n");
// 	printf("***************************************************************\n\n");
	// if (built_in(var, list, env))
	// 	return ;
	
	// if (herdoc_exist(list))
	// {
	// 	printf("..................****** OK >>> OK >>> OK >>>> OK *******  ........................\n");
	// 	while(list)
	// 	{
	// 		if(pipe_exist(list))
	// 		{
	// 			handle_pipe(list, env);
	// 		}
	// 		else if(!pipe_exist(list) && herdoc_exist(list))
	// 		{
	// 			printf("...........--==-==-...........\n");
	// 			handle_here_doc(list, env);
	// 		}
	// 		else
	// 		{
	// 			new_args = ft_new_args(list->arg, list->doc);
	// 			if (new_args != NULL)
	// 			{
	// 				execution_cmd(list, new_args, env);
	// 				free(new_args);
	// 			}
	// 			else
	// 			{
	// 				execution_cmd(list, list->arg, env);
	// 			}
	// 		}
	// 		list = list->next;
	// 	}
	// }
	// new_args = ft_new_args(list->arg, list->doc);
	// if (new_args != NULL)
	// {
	// 	execution_cmd(list, new_args, env);
	// 	// free(new_args);
	// }
	// else
	// {
	// 	execution_cmd(list, list->arg, env);
	// }
// if (list == NULL)
//                 return ;

//         if(ft_strcmp(list->content , "exit") == 0)
//                 ft_exit(var , list);

//         else if(ft_strcmp(list->content, "cd") == 0)
//                 ft_cd(list);

//         else if (ft_strcmp(list->content, "pwd") == 0)
//                 ft_pwd(list);

//         else if(ft_strcmp(list->content, "export") == 0)
//                 ft_export(var , list );

//         else if(ft_strcmp(list->content, "unset") == 0)
//                 ft_unset(var , list );

//         else if(ft_strcmp(list->content, "env") == 0)
//                 ft_env(var);

//         else if(ft_strcmp(list->content, "echo") == 0)
//                 ft_echo(list,env);
//         else
//         {
//                 if(herdoc_exist(list) == 1)
//                 {
//                         handle_here_doc(list,env);
//                 }
//                 if( pipe_exist(list) == 1)
//                 {
//                         handle_pipe(list, env);
//                 }
//                 else
//                 {
//                         char **new = ft_new_args(list->arg, list->doc);
//                         execution_cmd(list, list->arg ,env);
//                 }
//         }

// 		printf(".....................****************.............................\n");
		
	// if (built_in(var, list, env))
	// 	return ;
	// 	// handle_here_doc(list, env);
	// if (pipe_exist(list))
	// {
	// 	// printf(".....................****************.............................\n");
	// 	handle_pipe(list, env);
	// 	return ;
	// }
	// else
	// {
	// 	printf("..........++++++++++++++++++++++++++++ .................\n");
	// 	new_args = ft_new_args(list->arg, list->doc);
	// 	if (new_args != NULL)
	// 	{
	// 		execution_cmd(list, new_args, env);
	// 		free(new_args);
	// 	}
	// 	else
	// 	{
	// 		execution_cmd(list, list->arg, env);
	// 	}
	// }
// }
