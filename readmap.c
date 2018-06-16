int     readmap(char *string, t_var *var)
{
    int i;
    int j;
    int k;
    char **str;

    j = 0;
    if (!(var->fd = open(string, O_RDWR)))
    {
        ft_putendl("Invaild file");
        return (-1);
    }
    while (get_next_line(var->fd, &var->line))
    {
        k = 0;
        i = 0;
        str = ft_strsplit(var->line, ' ');
        while (str[i])
            var->map[j][k++] = ft_atoi(str[i++]);
        j++;
    }
    return (0);
}
