#include "directory_info.h"
#include "ft_lstQueue.h"

t_list *dir_list( char *path, t_options opts )
{
	t_list *list;

	list = get_dir_list( path, opts );
	if(!list)
		return(NULL);
	lstMergeSort( &list, opts.cmp );
	if( opts.flags & REVERSE )
		ft_lstreverse( &list );
	return( list );
}

static void	setNames(char *path, t_dir_info *dir, char *d_name)
{
	dir->path_ref = ft_strdup( path );
	dir->print_name = ft_strdup(dir->entry->d_name);
	if(checkpathend(path))
		dir->path = ft_strjoin(path, d_name);
	else
	{
		path = ft_strjoin(path, "/");
		dir->path = ft_strjoin(path, d_name);
		free(path);
	}
}

t_list *get_dir_list( char *path, t_options opts )
{
	DIR		*directory;
	t_dir_info	dir_info;
	t_list		*node;

	node = NULL;
	if(!(directory = opendir(path)))
	{	
		ft_printf("ls: cannot open directory '%s': ", path);
		ft_printf("%s\n", strerror(errno));
		return(NULL);
	}
	while((dir_info.entry = readdir(directory)) != NULL)
	{
		if (*(dir_info.entry->d_name) == '.' && !(opts.flags & HIDDEN))
			continue;
		setNames(path, &dir_info, dir_info.entry->d_name);
		if(stat(dir_info.path, &(dir_info.status)) != -1)
			ft_lstPush(&node, &dir_info, sizeof(t_dir_info));
	}
	return(node);
}

/*
t_list *get_dir_list( char *path, t_options opts )
{
	DIR		*directory;
	t_dir_info	dir_info;
	t_list		*node;

	node = NULL;
	directory = opendir( path );
	if(!directory)
		return(NULL);
	dir_info.path_ref = ft_strdup( path );
	if(!checkpathend(path))
		path = ft_strjoin( path, "/" );
	while((dir_info.entry = readdir(directory)) != NULL)
	{
		if (*(dir_info.entry->d_name) == '.' && !(opts.flags & HIDDEN))
			continue;
		dir_info.print_name = ft_strdup(dir_info.entry->d_name);
		dir_info.path = ft_strjoin(path, dir_info.entry->d_name);
		//check stat to see if it fails throw appropriate error if yes 
		if(stat(dir_info.path, &(dir_info.status)) != -1)
			ft_lstPush(&node, &dir_info, sizeof(t_dir_info));
	}
	//free(path);
	return( node );
}

void	crawl_tree( t_list *lst, t_lstQ *queue, t_options opts )
{
	t_list *node;

	while( lst )
	{
		if( S_ISDIR( T_NODE( t_dir_info*, lst, status.st_mode)) && \
		(!((ft_strcmp( T_NODE( t_dir_info*, lst, entry -> d_name ), "." ) == 0) ||
		(ft_strcmp( T_NODE( t_dir_info*, lst, entry -> d_name ), "..") == 0))))
		{
			node = dir_list( T_NODE( t_dir_info*, lst, path ), opts);
			ft_lstQ( queue, node, sizeof( t_list ));
			crawl_tree( node, queue, opts );
		}
		lst = lst -> next;
	}
}
*/

void	crawl_tree( t_list *lst, t_lstQ *queue, t_options opts )
{
	t_list	*node;
	char	*s1;

	while(lst)
	{
		s1 = TDI(lst, entry->d_name);
		if(S_ISDIR(TDI(lst, status.st_mode)))
		{
			if(!(ft_strcmp(s1, ".") == 0 || 
			ft_strcmp(s1, "..") == 0))
			{
				node = dir_list(TDI(lst, path), opts);
				if(node)
				{
					ft_lstQ(queue, node, sizeof(t_list));
					crawl_tree(node, queue, opts);
				}
			}
		}
		lst = lst -> next;
	}
}
