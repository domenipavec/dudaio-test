
#include "webservice.h"

#include <stdlib.h>

DUDA_REGISTER("Duda IO test", "Test");

void cb_info(duda_request_t *dr)
{
	response->http_status(dr, 200);

	FILE *cmdline = fopen("/proc/cpuinfo", "rb");
	char *arg = 0;
	size_t size = 0;
	while(getdelim(&arg, &size, 0, cmdline) != -1)
	{
		response->printf(dr, arg);
	}
	free(arg);
	fclose(cmdline);
	
	response->end(dr, NULL);
}

void cb_cputemp(duda_request_t *dr)
{
	response->http_status(dr, 200);
	
	FILE *cmdline = fopen("/sys/class/thermal/thermal_zone0/temp", "rb");
	if (cmdline != NULL) {
		char *arg = 0;
		size_t size = 0;
		while(getdelim(&arg, &size, 0, cmdline) != -1)
		{
			response->printf(dr, arg);
		}
		free(arg);
		fclose(cmdline);
	} else {
		response->printf(dr, "ERROR");
	}
	
	response->end(dr, NULL);
}

int duda_main()
{
	map->static_add("/information", "cb_info");
	map->static_add("/cputemp", "cb_cputemp");
	
	return 0;
}
