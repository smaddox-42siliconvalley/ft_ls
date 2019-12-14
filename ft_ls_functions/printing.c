#include "directory_info.h"
#include "ft_lstQueue.h"
#include "time.h"

void	dir_print( t_list *node, t_options opts)
{
	if ( opts.flags & DIRPATH )
		ft_printf("%s:\n", T_NODE( t_dir_info*, node, path_ref ));
	ft_lstiter(node, opts.prnt);
	if ( opts.flags & DIRPATH )
		ft_printf("\n\n");
}

void	long_format_print( t_list *node )
{
	ft_printf("%s ", T_NODE( t_dir_info*, node, print_name ));
	return;
}

void	default_print( t_list *node )
{
	//time_t this = time(&TDI(node, status.st_mtime));
	ft_printf("%s ", T_NODE( t_dir_info*, node, print_name ));
	//ft_printf("%s: %s: %ld\n", TDI(node, print_name), ctime(&this), TDI(node, status.st_mtim.tv_nsec));
	return;
}
