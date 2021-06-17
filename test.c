
#include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
#include "./getnextline/get_next_line.h"
#include <fcntl.h>

int countNumberOfline(char *file)
{
    int i = 0;
    char	*line;
    int fd = open(file, O_RDONLY);
    while(get_next_line(fd, &line) > 0)
    {
        i++;
        free(line);
		line = NULL;
    }
    i++;
    close(fd);
    return i;
}

char**		read_from_file(int fd,char **qst)
{
	char	*line;
	int n = 1;
    int i = 0;
	while (n > 0)
	{
		n = get_next_line(fd, &line);
		if (n != -1)
		{
			qst[i] = strdup(line);
			free(line);
			line = NULL;
            printf("%s\n",qst[i]);
            i++;
		}
	}
    
    qst[i] = NULL;
    
	return (qst);
}

int main(int ac, char **av)
{
    int fd;
    char **qst;
    int numberOfline = countNumberOfline(av[1]);
    printf("nbr line: %d\n", numberOfline);
    if ((fd = open(av[1], O_RDONLY)) < 0)
		exit(-1);
	else
	{
        qst = (char**)malloc(sizeof(char *) * (numberOfline + 1));
        //printf("ok\n");
		qst = read_from_file(fd, qst);
		close(fd);
	}
    int i = 0;
    
    while(qst[i] != NULL)
    {
        printf("%s\n",qst[i]);
        i++;
    }
        
}