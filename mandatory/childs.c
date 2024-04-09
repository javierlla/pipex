/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:48:22 by jllarena          #+#    #+#             */
/*   Updated: 2024/03/18 10:48:25 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*paths es la entrada con los directorios donde se encuentras los comandos, 
utilizamos la funcion strjoin con el inicio de los directorios y lo juntamos
al nombre del comando
acess busca el comando en la ruta de los directorios y devuelve
 un 0 si hay coincidencia*/

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}
/*todo lo que se escriba en la salida standar, se redirige al pipe,
cerramos el extremo de lectura en el prmer hijo.
en el segundo hijo todo lo redirigimos a la entrada al fd[0] de lectura y
cerramos el de escritura.
spliteo el comando que le metamos y busca la ruta con get_cmd y lo 
almacenamos en pipex.cmd.
ejecutamos el comando con execve(ruta, comando y variable de entorno) */

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.fd[1], STDOUT_FILENO);
	close(pipex.fd[0]);
	dup2(pipex.infile, STDIN_FILENO);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
/*todo lo que entre por la entrada estandar viene al pipe en modo de lectura,
cerramos el proceso de escritura, y todo lo que salga por la salida standar,
se envia al fichero outfile*/

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.fd[0], STDIN_FILENO);
	close(pipex.fd[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
