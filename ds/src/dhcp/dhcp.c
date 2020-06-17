/*
Developer:	Sergey Konstantinovsky
Date:		16.06.2020
Reviewer:	Jenia Edelshtein
Status:
*/

#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for memcpy*/

#include "dhcp.h"


typedef enum children
{
	LEFT = 0,
	RIGHT,
	NUMBER_OF_CHILDREN
} child_t;

typedef struct trie_node trie_node_t;

struct trie_node
{
	trie_node_t *parent;
	trie_node_t *children[NUMBER_OF_CHILDREN];
	int is_full;
}; 

struct dhcp
{
	trie_node_t *root;
	ip_t subnet;
	size_t locked_bits;
};


#define TOTAL_NUM_OF_BITS (IPV4_LEN * sizeof(unsigned char))
#define SAVED_ADDRESSES_REQUIRED (3)
#define BITS_IN_BYTE (8)

static void RetrievePathImp(ip_t *ip, size_t locked_bits, char *arr);
static int IsIpEqualImp(ip_t *ip_1, ip_t *ip_2);
static dhcp_status_t InitTrieSkeleton(dhcp_t *dhcp);
static void DestroyTrieImp(trie_node_t *root);
size_t CountFullPreOrderImp(trie_node_t *node);
static int IsFullLeafImp(trie_node_t *node);
static trie_node_t *CreateTrieNodeImp(trie_node_t *parent, 
										trie_node_t *left_child, 
										trie_node_t *right_child,
										int is_full);


/*saved addresses*/
static ip_t g_network_address = {{0, 0, 0, 0}}; 
static ip_t g_server_address = {{255, 255, 255, 254}}; 
static ip_t g_broadcast_address = {{255, 255, 255, 255}}; 
	
/*------------------------------------------------------------------------------
O(1)
creates dhcp struct
on success: returns pointer to dhcp 
on fail: NULL
udefined behaviour: locked_bits < TOTAL_NUM_OF_BITS - SAVED_ADDRESSES_REQUIRED 

-> creates and inits dhcp struct
-> creates and inits trie root
-> inits trie skeleton with saved adresses
*/
dhcp_t *DHCPCreate(ip_t subnet_id, size_t locked_bits)
{
	dhcp_t *dhcp = NULL;
		
	assert(locked_bits > TOTAL_NUM_OF_BITS - SAVED_ADDRESSES_REQUIRED);
	
	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if (NULL == dhcp)
	{
		return NULL;
	}
	
	/*create trie root*/
	dhcp->root = CreateTrieNodeImp(NULL, NULL, NULL, 0);
	if (NULL == dhcp->root)
	{
		free(dhcp);
		return NULL;
	}
	
	dhcp->subnet = subnet_id;
	dhcp->locked_bits = locked_bits;
	
	/*inits dhcp skeleton*/
	if (DHCP_SUCCESS != InitTrieSkeleton(dhcp))
	{
		free(dhcp);
		return NULL;
	}
		
	return dhcp;	
}


static trie_node_t *CreateTrieNodeImp(trie_node_t *parent, 
										trie_node_t *left_child, 
										trie_node_t *right_child,
										int is_full)
{
	trie_node_t *node = (trie_node_t *)malloc(sizeof(trie_node_t));
	if (NULL == node)
	{
		return NULL;
	}

	node->parent = parent;
	node->children[LEFT] = left_child;
	node->children[RIGHT] = right_child;
	node->is_full = is_full;
	
	return node;
}


static dhcp_status_t InitTrieSkeleton(dhcp_t *dhcp)
{
	ip_t return_ip = {{0, 0, 0, 0}};
		
	dhcp_status_t status = DHCP_SUCCESS;
	
	assert(NULL != dhcp);
	
	/*init saved addresses*/
	status = DHCPAllocateIp(dhcp, g_network_address, &return_ip);
	if (DHCP_SUCCESS != status)
	{
		DestroyTrieImp(dhcp->root);
		return status;
	}

	status = DHCPAllocateIp(dhcp, g_server_address, &return_ip);
	if (DHCP_SUCCESS != status)
	{
		DestroyTrieImp(dhcp->root);
		return status;
	}

	status = DHCPAllocateIp(dhcp, g_broadcast_address, &return_ip);
	if (DHCP_SUCCESS != status)
	{
		DestroyTrieImp(dhcp->root);
		return status;
	}
	
	return status;
}


/*------------------------------------------------------------------------------
O(n)
destroy dhcp (post order)
on success: destroys dhcp
on fail: ---
udefined behaviour: dhcp == NULL

-> destroy all existing trie nodes in post order
post order means - from leaves up, 
meaning do the function only when a leaf is reached on every subtree starting from left

->destroys dhcp
*/	
void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	
	DestroyTrieImp(dhcp->root);
		
	dhcp->root = NULL;
	/*nullify subnet?*/
			
	free(dhcp);
	
	return;
}

/*post order trie destroy*/
static void DestroyTrieImp(trie_node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	DestroyTrieImp(node->children[LEFT]);
	DestroyTrieImp(node->children[RIGHT]);
	
	free(node);
}


/*------------------------------------------------------------------------------
O(n)
on success: returns amount of free leaves - addresses (pre-order)
on fail: ---
udefined behaviour: dhcp == NULL
	
-> counts already existing full leaves in pre order
pre-order means that i will count every time i go deeper into the Rec, 
starting from the root and going left.
	
-> substract amount of full leaves from total num of leaves
*/	
size_t DHCPCountFree(const dhcp_t *dhcp)
{		
	size_t free_bits = 0;
	
	assert(NULL != dhcp);
		
	free_bits = TOTAL_NUM_OF_BITS - CountFullPreOrderImp(dhcp->root);		
		
	return (free_bits);
}

size_t CountFullPreOrderImp(trie_node_t *node)
{	
	if (NULL == node)
	{
		return 0;
	}

	return( IsFullLeafImp(node) + 
			CountFullPreOrderImp(node->children[LEFT]) + 
			CountFullPreOrderImp(node->children[RIGHT]));
}

static int IsFullLeafImp(trie_node_t *node)
{
	assert(NULL != node);
	
	return (1 == node->is_full && 
			NULL == node->children[LEFT] &&
			NULL == node->children[RIGHT]);
}

/*	
O(log n) 
fail when no free adresses are available
fail due to malloc
success return 0 

undefined: ip requested is not part of given subnet

algorithm:
-> check if requested ip is valid (saved addresses)
-> get relevant bits from requested address (according to subnet)
	will be 0.0.0.0 or something else
-> find the first path available closest to requested path:
	-
	-
	-
*/
dhcp_status_t DHCPAllocateIp(dhcp_t *dhcp, ip_t ip_request, ip_t *return_ip)
{
	dhcp_status_t status = DHCP_SUCCESS;
	
	char *path_arr = NULL;
	
	size_t i = 0;
	size_t arr_size = 0;
	
	assert(NULL != dhcp);
	assert(NULL != return_ip);
	
	/*array for bits*/
	arr_size = TOTAL_NUM_OF_BITS - dhcp->locked_bits;
	path_arr =  (char *)calloc(arr_size, sizeof(int));
	if (NULL == path_arr)
	{
		return DHCP_MALLOC_FAIL;
	}
	
	/*fill array*/
	RetrievePathImp(&(ip_request), dhcp->locked_bits, path_arr);	
	
	/*create path in trie*/
	ChoosePathImp(dhcp, path_arr, arr_size);
	
	free(path_arr);
	return status;
}

static int IsIpEqualImp(ip_t *ip_1, ip_t *ip_2)
{
	size_t i = 0;
	
	assert(NULL != ip_1);
	assert(NULL != ip_2);
	
	memcmp((void *)(ip_1->ip_chars), (void *)(ip_2->ip_chars), IPV4_LEN);
	
	return 1;
}

/*retrives correct path from ip_requested, 
starting after locked bits, into arr given */
static void RetrievePathImp(ip_t *ip, size_t locked_bits, char *arr)
{
	size_t arr_index = 0;
	size_t bit_num = 0;
	size_t byte_num = 0;
	
	assert(NULL != ip);
	assert(NULL != arr);
	
	/*whole ip loop*/		
	while (bit_num < TOTAL_NUM_OF_BITS)
	{
		size_t i = 0;
		
		/*single char loop*/
		while (i < BITS_IN_BYTE)
		{
			char ch = (ip->ip_chars[byte_num] >> i) & 0x1;

			/*save in array only free bits*/
			if (bit_num > locked_bits)
			{
				arr[arr_index] = ch;
				++arr_index;
			}
			
			++bit_num;
			++i;			
		}
	
		++byte_num;
	}	
}

/*
-> check if the next child stated in path array is full
	-if next child in path is full go to closest one to its right, (like next bst), 
	create if needed and update path_arr, set return status as DHCP_REQUEST_TAKEN
	-if not full go it and check the next one
	
-> when reached the end (arr_size (height) is 0)
	- mark node as is_full
	
-> go upward and check if parent has 2 children and they are full
	-if so - make him full ad go up again
	-if not, return status
*/
dhcp_status_t ChoosePathImp(dhcp_t *dhcp, char *path_arr, size_t height)
{
	
}




/*	O(log n)	
	can only free ips generated
	return SUCCESS 
	INVALID_FREE for address already freed
	unspecified: ip recivded was not generated by dhcp */
dhcp_status_t DHCPFreeIp(dhcp_t *dhcp, ip_t ip)
{
	return 0;
}
