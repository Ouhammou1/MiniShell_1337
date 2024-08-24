/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execur_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:58 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/24 17:02:46 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_exist(t_command *list)
{
	t_command	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->content[0] == '|')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	num_pipe(t_command *list)
{
	t_command	*tmp;
	int			i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (tmp->content[0] == '|')
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*command_execut(t_command *list)
{
	char	*ptr;

	if (list == NULL)
	{
		fprintf(stderr, "Error: Command not found\n");
		return (NULL);
	}
	ptr = path_command(list->content);
	if (!ptr)
		perror("Error: Command not found");
	return (ptr);
}

int	**return_pipe(int num_cmd)
{
	int	**pipe;
	int	i;

	pipe = (int **)malloc(sizeof(int *) * num_cmd);
	if (!pipe)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_cmd)
	{
		pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe);
}

t_command	*get_list_command(t_command *list)
{
	t_command	*tmp;
	t_command	*head;
	t_command	*prev;

	tmp = NULL;
	head = NULL;
	prev = NULL;
	while (list)
	{
		if (list->content[0] == '|')
			list = list->next;
		else
		{
			tmp = (t_command *)malloc(sizeof(t_command));
			if (!tmp)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			tmp->content = list->content;
			tmp->arg = list->arg;
			tmp->doc = list->doc;
			tmp->next = NULL;
			if (prev)
				prev->next = tmp;
			else
				head = tmp;
			prev = tmp;
			list = list->next;
		}
	}
	return (head);
}

void	close_free_wait(int *pids, int **pipefd, int num_cmd,
		t_command *tmp_cmd)
{
	int	i;
	int	j;
	int	status;

	close(pipefd[num_cmd - 1][0]);
	close(pipefd[num_cmd - 1][1]);
	j = 0;
	while (j < num_cmd)
	{
		if (waitpid(pids[j], &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		j++;
	}
	i = 0;
	free(pids);
	while (i < num_cmd - 1)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
	free(tmp_cmd);
}
void	child_process(int **pipefd, int i, t_command *tmp_cmd, char **env,
		int num_cmd) //, int *red)
{
	(void)env;
	(void)tmp_cmd;
	// char	**new_args;
	// char	*ptr;

	if (i > 0)
	{
		close(pipefd[i - 1][1]);
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		close(pipefd[i - 1][0]);
	}
	if (i < num_cmd - 1)
	{
		close(pipefd[i][0]);
		dup2(pipefd[i][1], STDOUT_FILENO);
		close(pipefd[i][1]);
	}
	
	// new_args = ft_new_args(tmp_cmd->arg, tmp_cmd->doc);
	// printf("new_args = %s\n", new_args[0]);
	// ptr = command_execut(tmp_cmd);
	// if (!ptr)
	// 	exit(EXIT_FAILURE);
	// execve(ptr, new_args, env);
	// perror("execve failed");
	exit(EXIT_FAILURE);
}


int 		handle_pipe_p(t_command *list, char **env)
{
	int			num_cmd;
	int			**pipefd;
	t_command	*tmp_cmd;
	pid_t		*pids;
	int			i;
	int fd;

	num_cmd = num_pipe(list) + 1;
	pipefd = return_pipe(num_cmd);
	// int red = 0;
	tmp_cmd = get_list_command(list);
	pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);
	if (!pids)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_cmd && tmp_cmd)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pids[i] == 0)
		{
			// if (herdoc_exist(tmp_cmd))
			// {
			// 	handle_here_doc(tmp_cmd, env);
			// }
			// printf(" id child = %d\n", i);
			child_process(pipefd, i, tmp_cmd, env, num_cmd); //, &red);
		}
		if (i > 0)
		{
			close(pipefd[i - 1][0]);
			close(pipefd[i - 1][1]);
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}
	printf("num_cmd -----------------= %d\n", num_cmd);
	fd = pipefd[num_cmd - 2][0];

	close_free_wait(pids, pipefd, num_cmd, tmp_cmd);
	return (fd);
}

int handle_pipe(t_command *list, char **env)
{
    int num_cmd;
    int **pipefd;
    t_command *tmp_cmd;
    pid_t *pids;
    int i;
    int fd;

    num_cmd = num_pipe(list) + 1;  // Calculate the number of commands (pipes + 1)
    pipefd = return_pipe(num_cmd); // Allocate pipe file descriptors
    pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);
    if (!pids)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    tmp_cmd = get_list_command(list); 
    i = 0;
    while (i < num_cmd && tmp_cmd)
    {
        if (pipe(pipefd[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0)
        {
            if (i > 0) 
            {
                close(pipefd[i - 1][1]);
                dup2(pipefd[i - 1][0], STDIN_FILENO);
                close(pipefd[i - 1][0]);
            }
            if (i < num_cmd - 1) 
            {
                close(pipefd[i][0]);
                dup2(pipefd[i][1], STDOUT_FILENO);
                close(pipefd[i][1]);
            }

            if (test_redir_here_doc(tmp_cmd))
            {
                hundle_redirections(tmp_cmd);
            }

            char **new_args = ft_new_args(tmp_cmd->arg, tmp_cmd->doc);
            char *ptr = command_execut(tmp_cmd);
            if (!ptr)
                exit(EXIT_FAILURE);
            execve(ptr, new_args, env);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }

        if (i > 0) 
        {
            close(pipefd[i - 1][0]);
            close(pipefd[i - 1][1]);
        }

        tmp_cmd = tmp_cmd->next;
        i++;
    }

    close_free_wait(pids, pipefd, num_cmd, tmp_cmd);
    fd = pipefd[num_cmd - 2][0]; 
    return fd;
}


// void	handle_pipe(t_command *list, char **env)
// {
// 	int			num_cmd;
// 	int			**pipefd;
// 	t_command	*tmp_cmd;
// 	pid_t		*pids;
// 	int			i;

// 	num_cmd = num_pipe(list) + 1;
// 	pipefd = return_pipe(num_cmd);

// 	// Get the list of commands (excluding the pipes themselves)
// 	tmp_cmd = get_list_command(list);
// 	pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);
// 	if (!pids)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}

// 	i = 0;
// 	while (i < num_cmd && tmp_cmd)
// 	{
// 		if (pipe(pipefd[i]) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 		pids[i] = fork();
// 		if (pids[i] == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}

// 		if (pids[i] == 0)
// 		{
// 			// Child process handles redirections and execution

// 			// Handle input from previous pipe (if not the first command)
// 			if (i > 0)
// 			{
// 				close(pipefd[i - 1][1]);
// 				dup2(pipefd[i - 1][0], STDIN_FILENO);
// 				close(pipefd[i - 1][0]);
// 			}

// 			// Handle output to next pipe (if not the last command)
// 			if (i < num_cmd - 1)
// 			{
// 				close(pipefd[i][0]);
// 				dup2(pipefd[i][1], STDOUT_FILENO);
// 				close(pipefd[i][1]);
// 			}
// 			if (hundle_redirections(tmp_cmd) == 1)
// 			{
// 				// If redirection fails, print an error and exit
// 				perror("Error with redirections");
// 				exit(EXIT_FAILURE);
// 			}

// 			// Execute the command
// 			char **new_args = ft_new_args(tmp_cmd->arg, tmp_cmd->doc);
// 			char *ptr = command_execut(tmp_cmd);
// 			if (!ptr)
// 				exit(EXIT_FAILURE);
// 			execve(ptr, new_args, env);
// 			perror("execve failed");
// 			exit(EXIT_FAILURE);
// 		}

// 		// Close pipes in the parent process
// 		if (i > 0)
// 		{
// 			close(pipefd[i - 1][0]);
// 			close(pipefd[i - 1][1]);
// 		}
// 		tmp_cmd = tmp_cmd->next;
// 		i++;
// 	}

// 	close_free_wait(pids, pipefd, num_cmd, tmp_cmd);
// }
