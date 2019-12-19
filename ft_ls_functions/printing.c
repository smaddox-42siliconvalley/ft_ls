#include "directory_info.h"
#include "ft_lstQueue.h"
#include "time.h"
#include "pwd.h"
#include "grp.h"

void	dir_print( t_list *node, t_options opts)
{
	if (opts.flags & DIRPATH)
		ft_printf("%s:\n", T_NODE( t_dir_info*, node, path_ref ));
	if (opts.flags & LFORMAT)
		ft_printf("total %d\n", count_blocks(node));
	ft_lstiter(node, opts.prnt);
	if(!(opts.flags & LFORMAT))
		ft_printf("\n");
}

void	print_type( mode_t mode )
{
	char c;
	
	c = '-';
	if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISLNK(mode))
		c = 'l';
	ft_printf("%c", c);
}

char	*get_owner(uid_t uid)
{
	return((getpwuid(uid)) -> pw_name);
}

char	*get_group( gid_t gid )
{
	return((getgrgid(gid) -> gr_name)); 
}

void	print_mode( mode_t mode )
{
	const char *characters;
	size_t i;
	char buf[11];

	print_type(mode);
	characters = "rwxrwxrwx";
	i = 0;
	while( i < 9 )
	{
		buf[i] = (mode & (1 << (8 - i))) ? characters[i] : '-';
		i++;
	}
	buf[10] = '\0';
	if (mode & S_ISVTX)
		buf[8] = (S_ISDIR(mode)) ? 't' : 'T';
	if (mode & S_ISUID)
		buf[2] = (S_ISDIR(mode)) ? 's' : 'S';
	if(mode & S_ISGID)
		buf[5] = (S_ISDIR(mode)) ? 's' : 'S';
	ft_printf("%s ", buf);
}


void	get_datetime(struct stat status)
{
	char **strings; 
	char *str;
	time_t ttime;

	str = ctime( &status.st_mtime );
	strings = ft_strsplit(str, ' ');
	// Super lazy formatting 
	// overwrite the unneeded seconds and the newline char on the year
	strncpy((strings[3] + (ft_strlen(strings[3]) - 3)), "\0\0\0", 3);
	strncpy((strings[4] + (ft_strlen(strings[4]) - 1)), "\0", 1);
	ft_printf("%s %2s %s ", strings[1], strings[2],
	((time(NULL) - status.st_mtime) >= 15552000)
	? strings[4] : strings[3]);	
	while( *strings )
	{
		free(*strings);
		strings++;
	}
}

void	long_format_print( t_list *node )
{
	char symlinkbuf[255];
	ft_bzero(symlinkbuf, 255);
	print_mode(TDI(node, status.st_mode));
	ft_printf("%3d ", TDI(node, status.st_nlink));
	ft_printf("%10s ", get_owner(TDI(node, status.st_uid)));
	ft_printf("%10s ", get_group(TDI(node, status.st_gid)));
	ft_printf("%6d ", TDI(node, status.st_size));
	get_datetime(TDI(node, status));
	ft_printf("%-s ", TDI(node, print_name));
	if( S_ISLNK(TDI(node, status.st_mode)))
	{
		readlink(TDI(node, path), symlinkbuf, 255);
		ft_printf("-> %s", symlinkbuf);
	}
	ft_printf("\n");
	return;
}

void	default_print( t_list *node )
{
	ft_printf("%s ", T_NODE( t_dir_info*, node, print_name ));
	return;
}

