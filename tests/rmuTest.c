#include "directory_info.h"

void	handle_dir( char *path, t_options opts )
{
	
	t_lstQ		queue;
	t_list		*node;
	t_list		*temp;

	queue = ft_newlstQueue();
	node = dir_list(path, opts);
	if (!node )
		return;
	dir_print( node, opts );
	if ( opts.flags & RECURSIVE )
	{
		crawl_tree( node, &queue, opts );
		while (( temp = (t_list*)(ft_lstDQ( &queue ))))
		{
			dir_print( temp, opts );
			//delete everything 
		}
	}
}

void	handleArgs( t_list *args, t_options opts )
{
	if ( args == NULL )
		handle_dir(".", opts);
	while( args )
	{
		if(S_ISDIR(T_NODE( t_dir_info*, args, status.st_mode )))
			handle_dir(T_NODE(t_dir_info*, args, path), opts);
		else	
			opts.prnt(args);
		args = args -> next;
	}
}

void temp_print( t_list *node )
{
	ft_printf("%s\n", T_NODE( t_dir_info*, node, print_name));
}

int main(int ac, char **av)
{

	t_options	opts;
	t_list		*args;

	args = NULL;
	ft_bzero(&opts, sizeof(t_options));
	ls_init( (av + 1), &args, &opts );
	//t_list *node = dir_list(".", opts);
	//ft_lstiter( node, &temp_print );
	handleArgs( args, opts );
}

/*
int main(int ac, char **av)
{
	t_list		*opts;
	t_list		*args;
	unsigned int	shit;


	args = NULL;
	opts = NULL;
	//new_get_args( av, &args, &opts );
	flag_stepper( av[1], &shit );
	printf("%u\n", shit);
	return(0);

	ls_print( node, opts );
	while (( temp = (t_list*)ft_lstDQ( &queue )))
	{
		ft_printf("\n--------------------------------------------\n");
		ls_print( temp, opts );
	}
		ft_printf("\n--------------------------------------------\n");
}
*/
