/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utente <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:47:46 by utente            #+#    #+#             */
/*   Updated: 2023/04/08 13:40:41 by utente           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_strcmp(char *str_1, char *str_2)
{
	while ((*str_1 == *str_2)
		&& *(str_1 + 1)
		&& *(str_1 + 1) != '\n')
	{
		++str_1;
		++str_2;
	}
	return (*str_1 - *str_2);
}

static void	error(t_stack_node **a, t_stack_node **b)
{
	free_stack(a);
	free_stack(b);
	write(2, "Error\n", 6);
	exit(1);
}

static void	parse_command(t_stack_node **a, t_stack_node **b, char *command)
{
	if (!ft_strcmp(command, "pa"))
		pa(a, b, true);
	else if (!ft_strcmp(command, "pb"))
		pb(b, a, true);
	else if (!ft_strcmp(command, "sa"))
		sa(a, true);
	else if (!ft_strcmp(command, "sb"))
		sb(b, true);
	else if (!ft_strcmp(command, "ss"))
		ss(a, b, true);
	else if (!ft_strcmp(command, "ra"))
		ra(a, true);
	else if (!ft_strcmp(command, "rb"))
		rb(b, true);
	else if (!ft_strcmp(command, "rr"))
		rr(a, b, true);
	else if (!ft_strcmp(command, "rra"))
		rra(a, true);
	else if (!ft_strcmp(command, "rrb"))
		rrb(b, true);
	else if (!ft_strcmp(command, "rrr"))
		rrr(a, b, true);
	else
		error(a, b);
}

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	char			*next_line;

	a = NULL;
	b = NULL;
	if (1 == argc)
		return (0);
	else if (2 == argc)
		argv = ft_split(argv[1], 32);
	stack_init(&a, argv + 1, 2 == argc);
	next_line = get_next_line(STDIN_FILENO);
	while (next_line)
	{
		parse_command(&a, &b, next_line);
		next_line = get_next_line(STDIN_FILENO);
	}
	if (stack_sorted(a))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free(a);
}
