/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhindou <ykhindou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:47:12 by ykhindou          #+#    #+#             */
/*   Updated: 2025/04/15 15:33:47 by ykhindou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("Leetshell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		free(line);
	}
	clear_history();
	return (0);
}

// int	main()
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("Leetshell$ ");
// 		if (!line) // Ctrl+D
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		if (*line)
// 			add_history(line);
// 		// printf("you entred : %s \n", line);
// 		// tokens = lexer(line);
// 		// tokens = lexer(tokens);
// 		// ast = parser(tokens);
// 		// executor(ast);
// 		free(line);
// 	}
// 	clear_history();
// 	return (0);
// }