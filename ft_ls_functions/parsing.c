#include "directory_info.h"

/*	replaces the contents of the node with the lstat struct
 *	corresponding to the name initially in the node 
 */

static void		getInfo( t_list *node )
{
	t_dir_info	*info;
	struct stat	temp;
	
	if((stat((char*)(node -> content), &temp)) != -1 ) 
	{
		info = (t_dir_info*)malloc(sizeof(t_dir_info));
		info -> status = temp;
		info -> print_name = (char*)(node -> content);
		info -> path = info -> print_name;
		info -> path_ref = info -> print_name;
		node -> content = info;
	}
	else
	{
		//error handling here
		node -> content = NULL;
	}
}

/*	parses the input from the command line into two lists
 *	one contains the file/dir stat structs and the other contains option strings.
 *	The args list is sorted alphabetically expecting that 
 *	files always come before folders
 */

void		ls_init( char **av, t_list **args, t_options *options  )
{
	int num_args = 0;
	while( *av )
	{
		if(((*av)[0] == '-') && (ft_strlen((*av)) > 1 ))
			flag_set(*av, &(options -> flags));
		else
		{
			num_args++;
			add_args( *av, args );
		}
		av++;
	}
	if ( num_args > 1 )
		(options -> flags) |= DIRPATH;
	postProcOpts( options );
	ft_lstiter( *args, &getInfo );
	ft_lst_rm_if( args, &checkfornull, &free );
	lstMergeSort(args, &cmp_file);
}

/*	add a string to a t_list 
 */

void		add_args( char *str, t_list **args )
{
		if( !(*args) )
			(*args) = ft_lstnew( str, ft_strlen(str));	
		else
			ft_lstPush( args, str, ft_strlen(str));
}
