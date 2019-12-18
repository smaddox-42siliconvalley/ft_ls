#include "directory_info.h"

void	tdi_clean( void *data, size_t size )
{
	t_dir_info *node;

	node = (t_dir_info*)data;
	free( node -> path_ref );
	free( node -> path );
	free( node -> print_name );
}
