#include <unistd.h>

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *cmd[4];
    cmd[0] = "ls";
    cmd[1] = "-lRa";
    cmd[2] = "src/parser";
    cmd[3] = NULL;
    execve("/usr/local/bin/ls", cmd, envp);
}