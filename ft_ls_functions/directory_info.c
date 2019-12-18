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

/*
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
*/

static void	setNames(char *path, t_dir_info *dir, char *d_name)
{
	char fullpath[255];
	
	ft_bzero(fullpath, 255);
	ft_strcpy(fullpath, path);
	dir->path_ref = ft_strdup(path);
	dir->print_name = ft_strdup(dir->entry->d_name);
	if((path)[ft_strlen(path) - 1] != '/')
		ft_strcat(fullpath, "/");
	ft_strcat(fullpath, dir->print_name);
	dir->path = ft_strdup(fullpath);
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
		if(lstat(dir_info.path, &(dir_info.status)) != -1)
			ft_lstPush(&node, &dir_info, sizeof(t_dir_info));
	}
	closedir(directory);
	return(node);
}

void	crawl_tree( t_list *lst, t_lstQ *queue, t_options opts )
{
	t_list	*node;
	char	*s1;

	while(lst)
	{
		s1 = TDI(lst, path);
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
