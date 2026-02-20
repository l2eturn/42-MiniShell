/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 01:34:48 by slimvutt          #+#    #+#             */
/*   Updated: 2026/02/21 01:34:48 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	command_cd(char **args, char **envp)
{
	(void)envp;
	if (args[1] == NULL)
	{
		write(2, "minishell: cd: expected argument\n", 33);
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	command_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}

int	command_env(char **envp)
{
	int	i;

	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

static int	is_n_flag(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	command_echo(char **args, char **envp)
{
	int	i;
	int	n_flag;

	(void)envp;
	i = 1;
	n_flag = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

static int	get_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

/* * export: รับ char **envp เก่ามา 
 * และ return char **envp ตัวใหม่ที่มีตัวแปรเพิ่มเข้าไป 
 */
char	**command_export(char **args, char **envp)
{
	char	**new_env;
	int		size;
	int		i;

	// ถ้าไม่มีอาร์กิวเมนต์ ให้ปริ้นท์ env ทั้งหมดที่มีคำว่า "declare -x"
	if (!args[1])
		return (envp); 
	
	size = get_env_size(envp);
	// +2 เพราะต้องเผื่อช่องให้ตัวแปรใหม่ 1 ช่อง และ NULL ปิดท้าย 1 ช่อง
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (envp);
		
	i = 0;
	while (i < size)
	{
		new_env[i] = envp[i]; // ในงานจริงควรใช้ ft_strdup
		i++;
	}
	new_env[i] = args[1]; // ใส่ตัวแปรใหม่ (งานจริงใช้ ft_strdup)
	new_env[i + 1] = NULL;
	
	// หมายเหตุ: งานจริงต้อง free(envp) เก่าด้วย (ถ้ามันเป็นตัวที่เรา malloc มา)
	return (new_env);
}

/* * unset: สร้าง new_env ใหม่ที่ตัดตัวแปรที่ตรงกับ args[1] ออก
 */
char	**command_unset(char **args, char **envp)
{
	// ลอจิกจะคล้าย export แต่เปลี่ยนเป็นการเช็ค strncmp 
	// ถ้าตัวแปรไหนชื่อตรงกับ args[1] เราก็แค่ไม่ copy มันลงไปใน new_env ครับ
	
	return (envp); // return ตัวที่ลบเสร็จแล้วไปให้ main ใช้ต่อ
}

