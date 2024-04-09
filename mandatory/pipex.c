/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:46:30 by jllarena          #+#    #+#             */
/*   Updated: 2024/03/18 10:46:32 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*se devuelve un puntero a la posicion siguiente a PATH= en caso de haber 
coincidencia.*/

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

/*O_TRUNC: Esta bandera indica que, si el archivo ya existe, su contenido se
truncará (es decir, se eliminará todo su contenido). Esta opción es relevante
cuando se quiere sobrescribir el contenido existente del archivo o crear un
archivo nuevo si no existe.
O_CREAT: Esta bandera especifica que el archivo debe ser creado si no existe.
O_RDWR: Esta bandera indica que el archivo se abrirá tanto para lectura como
para escritura.
0000644: Este es el modo de archivo en octal que se aplica al archivo si se crea.
En este caso, 0644 es un número octal que representa los permisos de archivo.
Aquí, 0644 otorga permisos de lectura y escritura al propietario del archivo y 
permisos de solo lectura a los demás.*/

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (msg(ERR_INPUT));
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		msg_error(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile < 0)
		msg_error(ERR_OUTFILE);
	if (pipe(pipex.fd) < 0)
		msg_error(ERR_PIPE);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}
