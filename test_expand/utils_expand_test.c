#include "expand.h"

int count_l_quotes(t_expand *expand, char *str, int start)
{
	expand->l_s_quotes = 0;
	expand->l_db_quotes = 0;

	while (start > 0)
	{
		if (str[start] == '\"')
			expand->l_db_quotes++;
		else if (str[start] == '\'')
			expand->l_s_quotes++;
		start--;
	}
	return (0);
}

int count_r_quotes(t_expand *expand, char *str, int start)
{
	expand->r_s_quotes = 0;
	expand->r_db_quotes = 0;

	while (str[start])
	{
		if (str[start] == '\"')
			expand->r_db_quotes++;
		else if (str[start] == '\'')
			expand->r_s_quotes++;
		start++;
	}
	return (0);
}

int count_quotes(t_expand *expand, char *str, int start)
{
	printf("LET COUNT\n");
	count_l_quotes(expand, str, start);
	count_r_quotes(expand, str, start);
	if (expand->l_db_quotes == 0 && expand->l_s_quotes == 0 && expand->r_db_quotes == 0 && expand->r_s_quotes == 0)
		return (1);
	if ((expand->l_s_quotes % 2 == 0) || (expand->r_s_quotes % 2 == 0))
		return (1);
	return (0);
}

int	check_longuest_q(char *str, int j)
{
	int	i;
	int left;
	int	right;

	i = 0;
	left = -1;
	right = -1;
	int	len = strlen(str);
	while (i != j)
	{
		if (str[i] == 39)	//single quotes ascii
		{
			left = 0;
			break;
		}
		else if (str[i] == 34) //double quotes ascii
		{
			left = 1;
			break;
		}
		i++;
	}
	while (len != j)
	{
		if (str[len] == 39)	//single quotes ascii
		{
			right = 0;
			break;
		}
		else if (str[len] == 34) //double quotes ascii
		{
			right = 1;
			break;
		}
		len--;
	}
	if (right == 1 && left == 1)
		return (1);
	return (0);
}

int	valid_quotes_env(t_expand *expand, char *str, int i)
{
	int	j;
	int	doll;

	j = 0;
	doll = -1;
	while (str[j])
	{
		if (str[j] == '$')
		{
			doll++;
			if (doll == i)
			{
				printf("DOLL = i\n");
				if (check_longuest_q(str, j))		//ca a l'air ok 
					return (1);
				else if (count_quotes(expand,str, j))	//a faire
				{
					printf("VALID_QUOTES_FAUT REPLACE [$%c]\n", str[j+1]);
					return (2);
				}
			}
		}
		j++;
	}
	return (0);
}

void	reset_init(t_expand *expand)
{
	return ;
}
