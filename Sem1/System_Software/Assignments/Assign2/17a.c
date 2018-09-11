#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int fd[2];

    pipe(fd);

    if (!fork()) {
        close(1);       /* close normal stdout */
        dup(fd[1]);   /* make stdout same as pfds[1] */
        close(fd[0]); /* we don't need this */
        execlp("ls", "ls", "-l", (char *)0);
    } else {
        close(0);       /* close normal stdin */
        dup(fd[0]);   /* make stdin same as pfds[0] */
        close(fd[1]); /* we don't need this */
        execlp("wc", "wc", (char *)0);
    }

    return 0;
}

