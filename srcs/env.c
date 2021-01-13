#include "../includes/minishell.h"

void	ft_env(t_minishell *ms)
{
	t_env_var	*temp;

	temp = ms->ev;
	while (temp->last != 1)
	{
		ft_printf("%s=%s\n", temp->var, temp->content);
		temp = temp->next_var;
	}
	ft_printf("%s=%s\n", temp->var, temp->content);
}