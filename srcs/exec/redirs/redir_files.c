
#include "minishell.h"
#include "minishell_louis.h"

/*
sert a faire nos redirection au debut du child
il y a 4 possibilites 

-> on a au moins un pipe
	-> si il est en entre
	-> si il est en sortie
	-> il est en entree et en sortie
-> on a pas de pipe

on s'occuperas de modifier la sortie standard et 
l'entree standard dans tout les cas possible
grace a dup2 exactement comme on le fait dans split
*/

void	redir_from(t_cmd *cmd, t_files *f, int *fail_open)
{
	cmd->input = file_from;
	if (cmd->prev_in)
		close(cmd->fd_in);
	if (access(f->filename, F_OK) == -1)
	{
		cmd->fd_in = -1;
		ft_dprintf(STDERR_FILENO, D_ER_NO_FILDIR, f->filename); //1
		*fail_open = 1;
	}
	else if (cmd->fd_in != -2)
	{
		cmd->fd_in = open(f->filename, O_RDONLY);
		if (cmd->fd_in == -1)
			ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename); //1
		cmd->prev_in = true;
	}
}

void	redir_to(t_cmd *cmd, t_files *f)
{
	cmd->output = file_to;
	if (cmd->prev_out)
		close (cmd->fd_out);
	cmd->fd_out = open(f->filename, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename); //1
		cmd->fd_out = -1;
	}
	cmd->prev_out = true;
}

void	redir_append(t_cmd *cmd, t_files *f)
{
	cmd->output = file_to;
	if (cmd->prev_out)
		close (cmd->fd_out);
	cmd->fd_out = open(f->filename, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename);
		cmd->fd_out = -1;
	}
	cmd->prev_out = true;
}

int	redir_ambigous_in(t_cmd *cmd, t_files *f)
{
	if (cmd->prev_in)
		close (cmd->fd_in);
	cmd->fd_in = -1;
	ft_dprintf(STDERR_FILENO, D_ER_AMB, f->filename);
	return (1);
}

int	redir_ambigous_out(t_cmd *cmd, t_files *f)
{
	if (cmd->prev_out)
		close (cmd->fd_out);
	cmd->fd_out = -1;
	ft_dprintf(STDERR_FILENO, D_ER_AMB, f->filename);
	return (1);
}
