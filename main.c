#include "./includes/minishell.h"

void	ft_init(t_minishell *ms)
{
	ms->line = NULL;
    ms->command = NULL;
    ms->current_workdir = NULL;
	ms->return_value = 0;
	get_next_line(1, NULL); //à vérifier
	//ft_init_env_var(ms);
}

int		ischaracter_quotes(t_minishell *ms, int i) // "" gestion
{
	str_remove_index(i, ms);
	if (i != 0)
		i--;
	while (ms->line[i])
	{
		if (ms->line[i] == '\\' && ms->line[i + 1] == '\\')
		{
			str_remove_index(i, ms);
		}
		if (ms->line[i] == '"')
		{
			str_remove_index(i, ms);
			if (i != 0)
				i--;
			break;
		}
		i++;
	}
	return (i);
}

int		ischaracter_squotes(t_minishell *ms, int i) // '' gestion
{
	str_remove_index(i, ms);
	if (i != 0)
		i--;
	while (ms->line[i])
	{
		if (ms->line[i] == '\'')
		{
			str_remove_index(i, ms);
			if (i != 0)
				i--;
			break;
		}
		i++;
	}
	return (i);
}

void	ischaracter_slash(t_minishell *ms, int i)
{
	if (ms->line[i] == ';') //REPERE QUI DIFFERENCIE LES CARACTERE HORS GUILLEMETS
		ms->line[i] = -50;
	if (ms->line[i] == '>')
		ms->line[i] = -51;
	if (ms->line[i] == '<')
		ms->line[i] = -52;
	if (ms->line[i] == '>' && ms->line[i+1] == '>') //GESTION BLACKSLASH AVEC DIFFERENT CARACTERE DE PARSING
	{	str_remove_index(i+1, ms);
		ms->line[i] = -53;
	}
	if (ms->line[i] == '\\' && ms->line[i+1] == '>')
		str_remove_index(i, ms);
	if (ms->line[i] == '\\' && ms->line[i+1] == '<')
		str_remove_index(i, ms);
	if (ms->line[i] == '\\' && ms->line[i+1] == ';')
		str_remove_index(i, ms);
	if (ms->line[i] == '\\' && ms->line[i+1] == '\\')
		str_remove_index(i, ms);
	//ischaracter_slash_next(ms, i);
}

void	ft_testing(t_minishell *ms)
{	
	int		i;

	i = 0;
	while (ms->line[i])
	{
		ischaracter_slash(ms, i);
		if (ms->line[i] == '\\' && ms->line[i + 1] == '"') //GESTION BLACKSLASH AVEC DIFFERENT CARACTERE DE PARSING
		{
			str_remove_index(i, ms);
		}
		else if (ms->line[i] == '\\' && ms->line[i + 1] == '\'') //GESTION BLACKSLASH AVEC DIFFERENT CARACTERE DE PARSING
		{
			str_remove_index(i, ms);
		}
		else if (ms->line[i] == '"')
		{
			i = ischaracter_quotes(ms, i);
		}
		else if (ms->line[i] == '\'')
		{
			i = ischaracter_squotes(ms, i);
		}
		i++;
	}
	ms->command_tab = ft_split(ms->line, -50);
}

int		main(void)
{
    t_minishell		ms[1];
    int				i;

	i = 0;
	ft_init(ms);
	while (1)
	{
		get_next_line(0, &ms->line);
		ft_testing(ms);
		while (ms->command_tab[i])
		{
			ft_printf("%s\n", ms->command_tab[i]);
			i++;
		}
		i = 0;
	}
}