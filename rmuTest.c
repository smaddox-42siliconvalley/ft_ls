#include "directory_info.h"

void	handle_dir( char *path, t_options opts )
{
	
	t_lstQ		queue;
	t_list		*node;
	t_list		*temp;

	queue = ft_newlstQueue();
	node = dir_list(path, opts);
	if (node)
	{
		dir_print( node, opts );
		if ( node && opts.flags & RECURSIVE )
		{
			crawl_tree( node, &queue, opts );
			while (( temp = (t_list*)(ft_lstDQ( &queue ))))
			{
				ft_printf("\n");
				dir_print( temp, opts );
				ft_lstdel( &temp, &tdi_clean );
			}
		}
	}
	else if(opts.flags & DIRPATH)
		ft_printf("%s:\n", path);
}
/*

void	handle_dir( char *path, t_options opts )
{
	
	t_lstQ		queue;
	t_list		*node;
	t_list		*temp;

	queue = ft_newlstQueue();
	node = dir_list(path, opts);
	if (!node )
	{
		if(opts.flags & DIRPATH)
			ft_printf("%s:\n", path);
		return;
	}
	dir_print( node, opts );
	if ( node && opts.flags & RECURSIVE )
	{
		crawl_tree( node, &queue, opts );
		while (( temp = (t_list*)(ft_lstDQ( &queue ))))
		{
			ft_printf("\n");
			dir_print( temp, opts );
			ft_lstdel( &temp, &tdi_clean );
		}
	}
}
*/
void	handleArgs(t_list *args, t_options opts)
{
	int files;

	files = 0;
	if(opts.flags & NOARGS)
		handle_dir(".", opts);
	while(args && !S_ISDIR(TDI(args, status.st_mode)))
	{
		files = 1;
		opts.prnt(args);
		args = args->next;
	}
	if(files)
		ft_printf("%s",
		(args && !(opts.flags & LFORMAT)) ? "\n\n" : "\n");
	while(args && S_ISDIR(TDI(args, status.st_mode)))
	{
		handle_dir(TDI(args, path), opts);
		if(args->next)
			ft_printf("\n");
		args = args->next;
	}
}
// returns 1 on "*/." and "*/.."

int	loldont(char *path)
{
	int	n;
	char	**strings;

	strings = ft_strsplit(path, '/');
	while(*strings && *(strings + 1))
	{
		free(*strings);
		strings++;
	}

	return(!(ft_strequ(*strings, ".") || ft_strequ(*strings, "..")));
}

int main(int ac, char **av)
{

	t_options	opts;
	t_list		*args;

	args = NULL;
	ft_bzero(&opts, sizeof(t_options));
	ls_init((av + 1), &args, &opts);
	handleArgs( args, opts );
	//ft_printf("%d\n", loldont(av[1]));
}
