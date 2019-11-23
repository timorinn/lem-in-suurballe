/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:54:19 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 15:09:38 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <fcntl.h>
# include "../libft/libft.h"

# include <stdio.h>

struct t_link;
struct s_input;
struct s_room;
struct s_params;

typedef struct		s_input
{
	char			*s;
	struct s_input	*next;
}					t_input;

typedef struct		s_room
{
	int				visit;
	char			*name;
	int				x;
	int				y;
	int				num;
	int				ant;
	int				ant_num;
	int				start;
	int				end;
	int				num_links;
	int				suur;
	int				path;
	struct s_link	*link;
	struct s_room	*next;
}					t_room;

typedef struct		s_link
{
	int				status;
	struct s_room	*room;
	struct s_link	*next;
}					t_link;

typedef struct		s_params
{
	int				num;
	int				startend;
	int				ants;
	int				links;
	char			*name;
}					t_params;

typedef struct		s_path
{
	int				len;
	int				num;
	int				suur;
	t_room			**room;
	int				step_ants;
	struct s_path	*next;
}					t_path;

t_input				*ft_analize_input(void);
t_input				*ft_lstnew_input(char *s);
t_link				*ft_lstnew_link(t_room *room);
int					ft_lstdel_input(t_input *list);
int					ft_del_all(t_input *input, t_room *room);

t_room				*ft_make_rooms(t_input *input);
t_room				*ft_make_room_list(char *s, t_room *room, t_params *par);
t_params			ft_init_room_param(t_input **input);
t_room				*ft_lstnew_room(char *name, int x, int y, t_params *par);

int					ft_limit_path(t_room *room);
int					get_path(t_room *room, t_path **answer);
int					ft_get_ant(t_room *room);
int					ft_len_output(t_path *answer, int ant, int dop);
int					ft_lstdel_path(t_path **path);
int					ft_path_len(t_path *itog);

int					ft_get_path(t_room *room, t_path **path,
	t_room *start, t_room *end);
void				ft_null_room(t_room *room);
int					ft_push_ended_path(t_path **buf, t_path **path);
int					ft_analize_path(t_path **path, int path_num);
t_path				*re_malloc_path(t_path *path);
t_room				*ft_find_end(t_room *room);
t_room				*ft_find_start(t_room *room);
void				ft_find_path(t_room *room, t_path **path, int ant);
int					ft_push_tail(t_path **buf, t_link *buf_child);
int					ft_conflict(t_path **path, t_path *last, int num_conf_path);
int					ft_repath_first(t_path *conf, t_path *last,
	t_room *room_first, t_room *room_last);
int					ft_len_room_list(t_room **list);

int					ft_check_flag(int argc, char **argv);
int					ft_flag_and_other(int argc, char **argv, t_path *path);

void				steps_print(t_path *path, t_room *room);

void				ft_print_path(t_path *path, int flag);
void				ft_print_link(t_link *link);
void				ft_print_room_and_link(t_room *room);
void				ft_print_path_once(t_path *path, char *s);

#endif
