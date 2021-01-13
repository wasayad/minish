#include "../includes/minishell.h"

void	ischaracter_slash(t_minishell *ms, int i)
{
	if (ms->line[i] == ';') //REPERE QUI DIFFERENCIE LES CARACTERE HORS GUILLEMETS
		ms->line[i] = -50;
	if (ms->line[i] == '>' && ms->line[i+1] == '>') //GESTION BLACKSLASH AVEC DIFFERENT CARACTERE DE PARSING
	{	str_remove_index(i+1, ms);
		ms->line[i] = -53;
	}
	if (ms->line[i] == '>')
		ms->line[i] = -51;
	if (ms->line[i] == '<')
		ms->line[i] = -52;
	if (ms->line[i] == '|')
		ms->line[i] = -54;

	if (ms->line[i] == '\\' && ms->line[i+1] == '|')
	{
		str_remove_index(i, ms);
	}
	if (ms->line[i] == '\\' && ms->line[i+1] == '>')
	{
		str_remove_index(i, ms);
	}
	if (ms->line[i] == '\\' && ms->line[i+1] == '<')
	{
		str_remove_index(i, ms);
	}
	if (ms->line[i] == '\\' && ms->line[i+1] == ';')
	{
		str_remove_index(i, ms);
	}
	if (ms->line[i] == '\\' && ms->line[i+1] == '\\')
	{
		str_remove_index(i, ms);
	}
	//ischaracter_slash_next(ms, i);
}

int		ischaracter_quotes(t_minishell *ms, int i)
{
	str_remove_index(i, ms);
	while (ms->line[i])
	{
		if (ms->line[i] == '\\' && ms->line[i + 1] == '\\')
		{
			str_remove_index(i, ms);
		}
		else if (ms->line[i] == '\\' && ms->line[i + 1] == '"')
		{
			str_remove_index(i, ms);
		}
		else if (ms->line[i] == '"')
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

int		ischaracter_squotes(t_minishell *ms, int i)
{
	str_remove_index(i, ms);
	while (ms->line[i])
	{
		if (ms->line[i] == '\\' && ms->line[i + 1] == '\'')
		{
			str_remove_index(i, ms);
		}
		else if (ms->line[i] == '\'')
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

void	ft_testing(t_minishell *ms)
{	
	int		i;

	i = 0;
	while (ms->line[i])
	{
		ischaracter_slash(ms, i);
		ft_printf("%c\n", ms->line[i]);
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

void	ft_init_env_var(t_minishell *ms)
{
	if (!(ms->ev = malloc(sizeof(t_env_var) * 1)))
		ft_exit(ms);
	ms->ev->var = ft_strdup("path"); //temporaire
	ms->ev->content = ft_strdup("jsp"); //temporaire
	ms->ev->last = 1;
}

void	ft_init(t_minishell *ms)
{
	ms->line = NULL;
    ms->command = NULL;
    ms->current_workdir = NULL;
	ms->return_value = 0;
	get_next_line(1, NULL); //à vérifier
	ft_init_env_var(ms);
}

int		get_command(t_minishell *ms)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ms->line[i] && ms->line[i] == ' ')
		i++;
	j = i;
	while (ms->line[j] && ms->line[j] != ' ')
		j++;
	if (!(ms->command = ft_substr(ms->line, i, j - i)))
		return (0);
	while (ms->line[j] && ms->line[j] == ' ')
		j++;
	if (!(ms->line = ft_substr_free(ms->line, j , ft_strlen(ms->line))))
		return (0);
	return (1);
}

int		main(void)
{
	t_minishell ms[1];
	int			i;

	i = 0;
	ft_init(ms);
	while (1)
	{
		get_next_line(0, &ms->line);
		ft_testing(ms);
		ft_printf("%s |||| %s\n", ms->command_tab[0], ms->line);
		while (ms->command_tab[i])
		{
			ms->line = ms->command_tab[i];
			if (!(get_command(ms)))
				return (0);
			if (ft_strcmp(ms->command, "echo") == 0)
				get_echo(ms);
			if (ft_strcmp(ms->command, "pwd") == 0)
				ft_pwd(ms);
			if (ft_strcmp(ms->command, "cd") == 0)
				ft_cd(ms);
			if (ft_strcmp(ms->command, "exit") == 0)
				check_exit(ms);
			if (ft_strcmp(ms->command, "export") == 0)
				ft_export(ms);
			if (ft_strcmp(ms->command, "unset") == 0)
				ft_unset(ms);
			if (ft_strcmp(ms->command, "env") == 0)
				ft_env(ms);
			ft_strdel(ms->line);
			ft_strdel(ms->command);
			i++;
		}
		i = 0;
	}
	ft_exit(ms);
	return (1);
}
