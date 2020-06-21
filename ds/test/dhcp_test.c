#include <string.h>	/*for memcpy*/
#include <stdio.h>	/*printf*/
#include <assert.h>

#include "dhcp.h"

#define ERROR printf("\nError in line: %d",__LINE__); \
				printf("\n%d . %d . %d . %d\n",return_ip.ip_chars[0],\
				return_ip.ip_chars[1],return_ip.ip_chars[2],return_ip.ip_chars[3]);

static int IsIpEqualImp(ip_t *ip_1, ip_t *ip_2);

int main()
{
	dhcp_t *dhcp = NULL;
	dhcp_status_t status = 0;
	
	ip_t return_ip = {{0,0,0,0}};
	ip_t request_1 = {{192,168,2,255}}; 	/*no ip*/
	
	ip_t request_2 = {{192,168,2,0}};		/*ip taken returns next one free*/
	ip_t excpected_2 = {{192,168,2,1}};
	ip_t excpected_3 = {{192,168,2,2}};
	ip_t excpected_4 = {{192,168,2,3}};
	
	ip_t request_3 = {{192,168,2,1}};		/*ip taken returns next one free*/
	
	ip_t subnet = {{192,168,2,1}};
		
	dhcp = DHCPCreate(subnet, 24);
	if(NULL == dhcp)
	{
		ERROR;
	}
	
	if (253 != DHCPCountFree(dhcp))
	{
		printf("\nError in line: %d, %lu",__LINE__, DHCPCountFree(dhcp));
	}
	
	status = DHCPAllocateIp(dhcp, request_1, &return_ip);
	if (DHCP_NO_FREE_IP != status)
	{
		ERROR;
	}

	status = DHCPAllocateIp(dhcp, request_2, &return_ip);
	if (DHCP_REQUEST_TAKEN != status)
	{
		ERROR;
	}
	if (1 != IsIpEqualImp(&return_ip, &excpected_2))
	{
		ERROR;
	}
	
	status = DHCPAllocateIp(dhcp, request_2, &return_ip);
	if (DHCP_REQUEST_TAKEN != status)
	{
		ERROR;
	}
	if (1 != IsIpEqualImp(&return_ip, &excpected_3))
	{
		ERROR;
	}
	
	status = DHCPAllocateIp(dhcp, request_2, &return_ip);
	if (DHCP_REQUEST_TAKEN != status)
	{
		ERROR;
	}
	if (1 != IsIpEqualImp(&return_ip, &excpected_4))
	{
		ERROR;
	}
	
	status = DHCPFreeIp(dhcp, request_3);
	if (DHCP_SUCCESS != status)
	{
		ERROR;
	}
	
	status = DHCPFreeIp(dhcp, request_3);
	if (DHCP_ALREADY_FREE != status)
	{
		ERROR;
	}
	
	printf("\n\n");
	DHCPDestroy(dhcp);	
	return 0;
}


static int IsIpEqualImp(ip_t *ip_1, ip_t *ip_2)
{
	assert(NULL != ip_1);
	assert(NULL != ip_2);
	
	return !(memcmp((void *)(ip_1->ip_chars), (void *)(ip_2->ip_chars), IP_LEN));
}
