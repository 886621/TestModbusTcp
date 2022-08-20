#include <stdio.h>


#include <dlfcn.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "modbus_tcp_main.h"
#define LIB_MODTCP_PATH "/usr/lib/libmodtcp.so"
// 端口
PARA_MODTCP para_modtcp = {MASTER, 1,{6,}, {10,},{"192.168.4.24",},{502,}};
typedef int (*init_fun)(void *);
void ModTcp_Init(PARA_MODTCP *para)
{
	void *handle;
	char *error;
	init_fun my_func = (void *)0;
	//打开动态链接库
	handle = dlopen(LIB_MODTCP_PATH, RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();

	*(void **)(&my_func) = dlsym(handle, "modbus_tcp_main");
	if ((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
	my_func(para);

	printf("打开动态链接库成功！！！\n");}

int main(void)
{

	printf("77777 ssdlh %s\n", para_modtcp.server_ip[0]);
	printf("12345 ssdlh\n");
	ModTcp_Init(&para_modtcp);
	while (1)
	{}
	return 0;
}