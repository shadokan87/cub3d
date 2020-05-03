
#include <unistd.h>
#include <stdlib.h>
#include "gnl_working/get_next_line.h"
#include "libft/libft.h"

typedef struct var_s
{
    char **text_paths;
    char *paramFile;
    int s_h;
    int s_w;
    int F_color[3];
    int C_color[3];
    
    //
    char **ParamSliced;
}   var_t;

void    getParamFile(int fd, char **line, var_t *var)
{
    int ret;

    ret = 0;
    while ((ret = get_next_line(fd, line)) > 0)
       var->paramFile = ft_strjoin(var->paramFile ? var->paramFile : "", *line);
}

// void    init_textPaths(var_t *var)
// {
//     if (!(var->text_paths = malloc(sizeof(char *) * 8)))
//         return ;
    
// }

int  ft_strcmp(char *str, char *str2)
{
    int i;

    i = 0;
    if (ft_strlen(str) != ft_strlen(str2))
        return (0);
    while (str[i])
    {
        if (str[i] == str2[i])
            i++;
        else
            return (0);
    }
    return (1);
}

// int fill_texture(char *token, var_t *var, char *str)
// {
//     int i;

//     i = 0;
//     if ((ft_strcmp(token, "NO")))
//         i = 2;
//     else if ((ft_strcmp(token, "SO")))
//         i = 3;
//     else if ((ft_strcmp(token, "WE")))
//         i = 4;
//     else if ((ft_strcmp(token, "EA")))
//         i = 5;
//     else if ((ft_strcmp(token, "S")))
//         i = 6;
//     if (i == 0)
//         return (0);
//     if ((ft_strcmp(token, "S")))
//         printf("%s", str);
//     var->text_paths[i] = ft_strdup(str);
//     return (i);
// }

// void    fill_screenResolution(char *token, var_t *var, char *str)
// {
//     if (!ft_strcmp(token, "R"))
//         return ;
//     var->s_w = ft_atoi(ft_split(str, ' ')[0]);
//     var->s_h = ft_atoi(ft_split(str, ' ')[1]);
// }

// void    get_screenResolution(var_t *var)
// {
//     getParamByToken("R", var);
// }

// int    getParamByToken(char *token, var_t *var)
// {
//     char *str;
//     int t_index;

//     if ((str = ft_strnstr(var->paramFile, token, ft_strlen(var->paramFile))))
//         str = ft_split(str, '\n')[0];
//     else
//         return (0);
//     str = ft_strtrim(str, token)[0] == ' '
//     ? ft_strtrim(str, token) + 1 : ft_strtrim(str, token);
//     fill_texture(token, var, str);
//     fill_screenResolution(token, var, str);
//     return (1);
// }

// void    get_textureFromPF(var_t *var)
// {
//     getParamByToken("SO", var);
//     getParamByToken("NO", var);
//     getParamByToken("WE", var);
//     getParamByToken("EA", var);
//     getParamByToken("S", var);
// }

void    fill_color(var_t *var, int i)
{
    if (ft_strcmp(var->ParamSliced[i], "F"))
    {
        var->F_color[0] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[0]);
        var->F_color[1] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[1]);
        var->F_color[2] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[2]);
        // var->F_color[0] = ft_atoi(ft_split(var->ParamSliced[i++], ',')[0]);
        // var->F_color[1] = ft_atoi(ft_split(var->ParamSliced[i++], ',')[1]);  
        // var->F_color[2] = ft_atoi(ft_split(var->ParamSliced[i++], ',')[2]);
        // return ;         
    }
    // var->C_color[0] = ft_atoi(ft_split(var->ParamSliced[i++], ',')[0]);
    // var->C_color[1] = ft_atoi(ft_split(var->ParamSliced[i++], ',')[1]);  
    // var->C_color[2] = ft_atoi(ft_split(var->ParamSliced[i++], ',')[2]);
}

int main(int argc, char **argv)
{
    int fd;
    int ret;
    char *line;
    int i = 0;
    int y = 0;
    var_t var;
    var.paramFile = NULL;
    ret = 0;
    fd = open(argv[1], O_RDONLY);
    // init_textPaths(&var);
    getParamFile(fd, &line, &var);
    i = 0;
    while (var.paramFile[i])
    {
        if (var.paramFile[i] == '\n')
            var.paramFile[i] = ' ';
        i++;
    }
    i = 0;
    var.ParamSliced = ft_split(var.paramFile, ' ');
    if (!(var.text_paths = malloc(sizeof(char *) * 8)))
        return (0);
    while (var.ParamSliced[i] != NULL)
    {
        printf("%s\n", var.ParamSliced[i]);
        i++;
    }
    i = 0;
    while (var.ParamSliced[i] != NULL)
    {
        if (ft_strcmp(var.ParamSliced[i], "R"))
        {
            var.s_w = ft_atoi(var.ParamSliced[i + 1]);
            var.s_h = ft_atoi(var.ParamSliced[i + 2]);
        }
        if (ft_strcmp(var.ParamSliced[i], "NO"))
            var.text_paths[2] = ft_strdup(var.ParamSliced[i + 1]);
        if (ft_strcmp(var.ParamSliced[i], "SO"))
            var.text_paths[3] = ft_strdup(var.ParamSliced[i + 1]);
        if (ft_strcmp(var.ParamSliced[i], "WE"))
            var.text_paths[4] = ft_strdup(var.ParamSliced[i + 1]);
        if (ft_strcmp(var.ParamSliced[i], "EA"))
            var.text_paths[5] = ft_strdup(var.ParamSliced[i + 1]);
        if (ft_strcmp(var.ParamSliced[i], "S"))
            var.text_paths[6] = ft_strdup(var.ParamSliced[i + 1]);
        if (ft_strcmp(var.ParamSliced[i], "F") || ft_strcmp(var.ParamSliced[i], "C"))
            fill_color(&var, i);
        i++;
    }
    printf("\n->%d %d", var.s_w, var.s_h);
    printf("\n->%s", var.text_paths[3]);
    printf("\n->%s", var.text_paths[4]);
    printf("\n->%s", var.text_paths[5]);
    printf("\n->%s", var.text_paths[6]);
    //printf("%s", var.text_paths[2]);
    printf("%d", var.F_color[0]);
    // get_textureFromPF(&var);
    // get_screenResolution(&var);
    // printf("%s", var.text_paths[6]);
    // int i = 2;

    // while (i < 6)
    // {
    //     printf("%s\n", var.text_paths[i]);
    //     i++;
    // }
    
    //printf("%s", paramFile);
}