
#include "minishell.h"
#include "minishell_louis.h"


/*
fonction get_env a modif un fois les deux codes link 
au lieu de parcourir envp on parcourra la liste chainée
*/

char	*find_home(char **envp)
{
	if (!envp[0])
		return (NULL);
	while (ft_strncmp("HOME", *envp, 4))
	{
		envp++;
		if (!*envp)
			return (NULL);
	}
	return (*envp + 5);
}

/*
principe de go_to :

prends en param la commande et un int du nombre d'argument
(soit 0 soit 1)
si 0 go_to doit chdir vers HOME
si 1 go_to doit chdir vers l'arg
    pourquoi les gens bossent avec des statics ?
met a jour old_pwd et pwd
*/

int    go_to(t_cmd *cmd, int nbr_arg, char **envp)
{
    if (nbr_arg == 0)
    {
        if (chdir(find_home(envp)) == -1)
        {
            //erreur a gerer
            return  (1);
        }
        //met a jour old_pwd et pwd
    }
    if (chdir(cmd->cmd_args[0]) == -1)
    {
        //erreur a gerer
        return (1);
    }
    return (0);
}

int bt_cd(t_cmd **cmd_tab, int i, char **envp)
{
    t_cmd   *cmd;

    cmd = cmd_tab[i];
    if (cmd->cmd_args[1])
    {
        if (cmd->cmd_args[2])
        {
            printf("too many arguments\n");
            return (1);
        }
        go_to(cmd, 1, envp);
    }
    if (!find_home(envp))
    {
        printf("HOME not set\n");
        return (1);
    }
    go_to(cmd, 0, envp);
    return (0);
}