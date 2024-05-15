/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:09 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/15 14:06:47 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "expand.h"

int	check_v_env(char *str)
{
	printf("entre check_v_env\n");
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if(str[i ]== '$')
			j++;
		i++;
	}
	return (j);
}

/*
//	ce que je veux ici : 
//	je check dabord les quotes autour du $..., 
//	[si c'est bon, 
//	{	
//		[si le $....(jusqu'a != lettre) existe, 
//			je le remplace]]
//		[sinon
//			 je le mets a NULL]
//	}
//	sinon je change pas.
*/
void	env_str(t_expand *expand, int w_str)
{
	printf("entre env_str\n");

	int	j = 0;
	int i = 0;
	int nb_env = check_v_env(expand->test[w_str]);
	while (i < nb_env)
	{
		if (valid_quotes_env(expand, expand->test[w_str], i))
			printf("valid quotes\n");
	//		j = realloc et replace(str, j)		//le j sera la position a partir de ou recommencer a check
		i++;
	}
	//	i++

	return;
}

int		check_quotes(t_expand *expand, int w_str)
{
	printf("entre check_quotes\n");
	return (0);
}

void	transform_str(t_expand *expand, int w_str)
{
	
	printf("entre transform_str\n");
	return;
}


int	expander(t_expand *expand)
{
	/*
	t_parser exp;
	int	i;

	exp = data->first_parser;
	i = 0;
	while (exp->next)
	{
		i = 0;
		while(exp->cmd[i])				//	while(i < 2) pour les test en dessous;
		{
			if (check_v_env(exp->cmd[i]) == 1)		//ici je check si y a un ou plusieur $			ok?
				env_str(exp->cmd[i]);				//ici je check dabord les quotes autour du $..., [si c'est bon, [si le $....(jusqu'a != lettre) existe, je le remplace]]sinon je change pas.
			if(check_quotes(exp->cmd[i]) == 1)		//ici je check si il reste des quotes
				transform_str(exp->cmd[i]);			//ici je tej les quotes que je peu tej
			i++;
		}
	}*/
	
	int	i;

	i = 0;
	while (i < 2)
	{
		printf("\n------\nCMD[%i] == %s\n------\n", i, expand->test[i]);
		reset_init(expand);
		if (check_v_env(expand->test[i]))		//ici je check si y a un ou plusieur $			ok?
			env_str(expand, i);				//ici je check dabord les quotes autour du $..., [si c'est bon, [si le $....(jusqu'a != lettre) existe, je le remplace]]sinon je change pas.
		if(check_quotes(expand, i) == 1)		//ici je check si il reste des quotes
			transform_str(expand, i);			//ici je tej les quotes que je peu tej
			i++;
	}
	return (0);
}



/*
CHECK SI $			=======check_v_env

SI $, CHECK QUTOTES,
SI DOUBLE OU RIEN, REMPLACER PAR ENV OU RIEN SI PAS DANS ENV
SI SIMPLE, JUSTE RETIRER LES SIMPLE QUOTES

SI PAS DE $





??????????????????????????????????
?????? ECHO $$USER le chiffre
?????? ECHO $$$$USER le chiffre 2 fois 

*/



/*----MAIN DE TEST-----*/

int main()
{
	int i = 0;
	t_expand expand;
	expand.test = malloc(sizeof(char *) * 2);
	expand.test[0] = malloc(sizeof(char) * 50);
	expand.test[1] = malloc(sizeof(char) * 50);
	
	expand.test[0] = "cmd0";
	expand.test[1] = "n\"$do\'$t\'st\"";

	expander(&expand);
	printf("---FIN---\n");
}