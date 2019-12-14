#include "directory_info.h"

/*		start new functs 

void		new_set_flags( t_list *opts, t_options *optstruc )
{
	while( opts )
	{
		flag_set(((char*)(opts -> content)), &(optstruc -> flags));
		opts = opts -> next;
	}
	func_set( optstruc );
}

*/

void		postProcOpts( t_options *optstruc )
{
/*	set defaults */
	optstruc -> cmp = &cmp_str;
	optstruc -> prnt = &default_print;
/*	immediately change them */
	if((optstruc -> flags) & TIME)
		optstruc -> cmp = &cmp_mtim;
	if((optstruc -> flags) & RECURSIVE)
		(optstruc -> flags) |= DIRPATH;
	if((optstruc -> flags) & LFORMAT)
	{
		optstruc -> prnt = &long_format_print;
		(optstruc -> flags) |= DIRPATH;
	}
}

void		flag_set( char *str, unsigned int *flag )
{
	char *options; 
	char *position;
	size_t	i;

	i = 1;
	options = "raRlt";
	while( *str )
	{
		position = options;
		if((position = ft_strchr( options, *str)))
			(*flag) |= ( i << (position - options));
		// error handling here
		str++;
	}
}
