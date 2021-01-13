#include "../libft/libft.h"
#include "errno.h"

typedef struct      env_var //liste chaînée pour variable d'environnement 
{
    char    *var;
    char    *content;
    void    *first_var;
    void    *next_var;
    void    *prev_var;
    int     last;
}                   t_env_var;

typedef struct		s_minishell
{
	char	*line;
    char	*command;
    char    **command_tab;
    char	*current_workdir;
	int		return_value;
    t_env_var *ev;
}					t_minishell;


int			get_quotes(t_minishell *ms);
int			get_echo(t_minishell *ms);
int			get_command(t_minishell *ms);
void		ft_exit(t_minishell *ms);
void		check_exit(t_minishell *ms);


int			remove_no_backslash_quotes(t_minishell *ms, char c);
void		str_remove_index(int i, t_minishell *ms);
void		backslash_checker_no_quotes(t_minishell *ms);
void		backslash_checker(t_minishell *ms);


void		ft_pwd(t_minishell *ms);
int			ft_cd(t_minishell *ms);
void		check_exit(t_minishell *ms);
void		ft_exit(t_minishell *ms);
int 	    ft_export(t_minishell *ms);
void        ft_unset(t_minishell *ms);
void	    ft_env(t_minishell *ms);
