#include "../../include/minishell.h"

int	valid_quotes_env(t_data *data, t_lexer *exp, int i)
{
	int	j;
	int	doll;

	j = 0;
	doll = -1;
	while (exp->token_str[j])
	{
		if (exp->token_str[j] == '$')
		{
			doll++;
			if (doll == i)
			{
				printf("DOLL = i\n");
				if (check_longuest_q(exp->token_str, j))		//ca a l'air ok
				{
					printf("VALID_QUOTES_FAUT REPLACE [$%c]\n", exp->token_str[j+1]);
					return (1);
				}
				else if (count_quotes(data, exp, j))	//a faire
				{
					printf("VALID_QUOTES_FAUT REPLACE [$%c]\n", exp->token_str[j+1]);
					return (2);
				}
			}
		}
		j++;
	}
	return (0);
}

void	env_str(t_data *data, t_lexer	*exp)
{
	printf("entre env_str\n");

	int	j = 0;
	int i = 0;
	int nb_env = check_v_env(exp->token_str);
	while (i < nb_env)
	{
		j = valid_quotes_env(data, exp, i);
		if (j == 1)
			printf("cas db quotes\n");
		else if (j == 2)
			printf("cas singles quotes\n");
		i++;
	}
	return;
}

int	expander(t_data *data)
{
	t_lexer	*exp;

	exp = data->first;
	data->expand = malloc(sizeof(t_expander));
	while (exp->next)
	{
		printf("=======EXP : %s=======\n", exp->token_str);
		if(check_v_env(exp->token_str))
			env_str(data, exp);
//		if(check_quotes(exp) == 1)		//ici je check si il reste des quotes
//			transform_str(exp);			//ici je tej les quotes que je peu tej
		exp = exp->next;
	}
	printf("=======EXP : %s=======\n", exp->token_str);
	if(check_v_env(exp->token_str))
		env_str(data, exp);
	return (0);
}