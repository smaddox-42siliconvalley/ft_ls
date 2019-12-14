#include "ft_printf.h"
#include "stdlib.h"
#include "directory_info.h"
#include "ft_lstQueue.h"

void	crawl_tree( t_list *lst, t_lstQ *queue );
int main( int ac, char **av)
{
	t_list *temp;	
	t_list *temp2;
	t_lstQ queue = ft_newlstQueue( );
	t_list *node = get_dir_list( "." );
	ft_lstQ( &queue, node, sizeof( t_list ));
	while( queue.head )
	{
		temp = ((t_list*)(ft_lstDQ(&queue)));
		ft_lstiter( temp, &print_dname_noHidden );
	}
	return( 0 );
}

/*
void	crawl_tree( t_list *lst, t_lstQ *queue )
{
	t_list *node;

	while ( lst )
	{
		if (S_ISDIR( T_NODE( t_dir_info*, lst, status.st_mode)))
		{
			if ( T_NODE( t_dir_info*, lst, entry -> d_name )[0] != '.' )
			{
				node = get_dir_list( T_NODE( t_dir_info*, lst, path ));
				ft_lstQ( queue, node, sizeof( t_list ));
				crawl_tree( node, queue );
			}
		}
		lst = lst -> next;
	}	
}
*/


