#include "../../include/minishell.h"

int	in_env(t_data *data, t_env *env, char *str)
{
	int	i;
	char *tempo;
	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	tempo = ft_substr(str, 0, i, data);
	if (!tempo)
	{
		free(tempo);
		return (0);
	}
	while(env->next)
	{
		if (env_cmp(tempo, env->env_str))
		{
			free(tempo);
			printf("ouiii\n");
			return (1);
		}
		env = env->next;
	}
	free(tempo);
	return (0);
}

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
				// test_quotes(data, exp, j);
				// if (check_longuest_q(exp->token_str, j))		//ca a l'air ok
				// {
				// 	printf("VALID_QUOTES_FAUT REPLACE [$%c]\n", exp->token_str[j+1]);
				// 	if (in_env(data, data->first_env, exp->token_str + j + 1))
				// 		printf("inv envvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
				// 	return (1);
				// }
				if (count_quotes(data, exp, j))	//a faire
				{
					printf("VALID_QUOTES_FAUT REPLACE [$%c]\n", exp->token_str[j+1]);
					if (in_env(data, data->first_env, exp->token_str + j + 1))
						printf("inv envvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
					return (1);
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