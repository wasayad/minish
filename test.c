
#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "includes/minishell.h"
//NE PAS SUPPRIMER TEST POUR PARSING
char *str_repack(int i, char *str)
{
	char	*str1;
	int		j;
	int		k;

	j = 0;
	k = 0;
	str1 = malloc(sizeof(char) * (ft_strlen(str)));
	while (str[j])
	{
		if (j != i)
		{
			str1[k] = str[j];
			k++;
		}
		j++;
	}
	str1[k] = '\0';
	free(str);
	return(str1);
}
int main(void)
{
	int		i;
	char *str;
	char **command;

	i = 0;
	while (1)
	{
		get_next_line(0, &str);
		while (str[i])
		{
			if (str[i] == ';') //REPERE QUI DIFFERENCIE LES CARACTERE HORS GUILLEMETS
				str[i] = -50;
			if (str[i] == '>')
				str[i] = -51;
			if (str[i] == '<')
				str[i] = -52;
			if (str[i] == '>' && str[i + 1] == '>') //GESTION BLACKSLASH AVEC DIFFERENT CARACTERE DE PARSING
			{
				str = str_repack(i+1, str);
				str[i] = -53;
			}
			if (str[i] == '\\' && str[i + 1] == '>')
			{
				str = str_repack(i, str);
			}
			if (str[i] == '\\' && str[i + 1] == '<')
			{
				str = str_repack(i, str);
			}
			if (str[i] == '\\' && str[i + 1] == ';')
			{
				str = str_repack(i, str);
			}
			if (str[i] == '\\' && str[i + 1] == '\\')
			{
				str = str_repack(i, str);
			}

			if (str[i] == '"')
			{
				str = str_repack(i, str);
				if (i != 0)
					i--;
				while (str[i])
				{
					if (str[i] == '\\' && str[i + 1] == '\\')
					{
						str = str_repack(i, str);
					}
					if (str[i] == '"')
					{
						str = str_repack(i, str);
						if (i != 0)
							i--;
						break;
					}
					i++;
				}
			}
			else if (str[i] == '\'')
			{
				str = str_repack(i, str);
				if (i != 0)
					i--;
				while (str[i])
				{
					if (str[i] == '\'')
					{
						str = str_repack(i, str);
						if (i != 0)
							i--;
						break;
					}
					i++;
				}
			}
			i++;
		}
		command = ft_split(str, -50);
		ft_printf("%s\n", command[0]);
		free(str);
	}
}