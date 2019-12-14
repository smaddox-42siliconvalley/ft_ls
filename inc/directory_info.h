#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "ft_printf.h"
#include "ft_lstQueue.h"
#include <stdio.h>
#include <errno.h>

/*	options			*/

#define REVERSE 1
#define HIDDEN 2
#define RECURSIVE 4
#define LFORMAT 8
#define TIME 16 
#define DIRPATH 32
#define NOARGS 64


#define TDI(x, y) (((t_dir_info*)((x)->content))->y)


/*	directory information	*/

typedef struct		s_dir_info
{
	char		*path_ref;	
	char		*path;
	char		*print_name;
	struct dirent	*entry;
	struct stat	status;
}			t_dir_info;

typedef struct		s_Finfo
{
	char		*path;
	struct stat	status;
}			t_Finfo;


/*	options information	*/

typedef struct		s_options
{
	unsigned int	flags;
	int		(*cmp)(void*, void*);
	void		(*prnt)(t_list*);
}			t_options;

/*	directory functions   */

t_list			*dir_list( char *path, t_options opts);
t_list			*get_dir_list( char *path, t_options opts );
void			crawl_tree( t_list *lst, t_lstQ *queue, t_options opts );

/*	utility	*/
int			checkfornull( void *data );
int			checkpathend( char *str );

/* special comparison funcs for sorting */

int			cmp_mtim( void *a, void *b );
int			cmp_str( void *a, void *b );
int			cmp_file(void *a, void *b);

/*	printing funcs	*/

void	dir_print( t_list *node, t_options opts );
void	long_format_print( t_list *node );
void	default_print( t_list *node );


/*	Parsing and option handling	*/

void	ls_init( char **av, t_list **args, t_options *options );
void	postProcOpts( t_options *optstruct );
void	flag_set( char *str, unsigned int *flag );
void	add_args( char *str, t_list **args );
