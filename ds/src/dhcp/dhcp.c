/*
Developer:	Sergey Konstantinovsky
Date:		16.06.2020
Reviewer:	Jenia Edelshtein
*/

#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for memcmp*/
#include <math.h> 	/*for pow*/

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
	trie_node_t *child[NUMBER_OF_CHILDREN];
	int is_full;
}; 

struct dhcp
{
	trie_node_t *root;
	ip_t subnet;
	size_t locked_bits;
};


#define TOTAL_NUM_OF_BITS (IP_LEN * BITS_IN_BYTE * sizeof(unsigned char))
#define SAVED_ADDRESSES_REQUIRED (2)
#define BITS_IN_BYTE (8)

#define iTH_DIGIT_FROM_LSB (0x1 << (BITS_IN_BYTE - 1 - i))) >> (BITS_IN_BYTE - 1 - i)
#define iTH_PLACE_FROM_LSB (BITS_IN_BYTE - 1 - i)

static dhcp_status_t FreeImp(dhcp_t *dhcp, child_t *path_arr, size_t height);
static void StoreReturnIpImp(ip_t *subnet, ip_t *ip, child_t *path_arr, size_t locked_bits);
static int IsChildrenFullImp(trie_node_t *node);
static void RetrievePathImp(ip_t *ip, size_t locked_bits, child_t *arr);
static dhcp_status_t FollowPathImp(dhcp_t *dhcp, child_t *path_arr, size_t height);
static int IsIpEqualImp(ip_t *ip_1, ip_t *ip_2);
static dhcp_status_t InitSystemAddressesImp(dhcp_t *dhcp);
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
udefined behaviour: locked_bits > TOTAL_NUM_OF_BITS - SAVED_ADDRESSES_REQUIRED 

-> creates and inits dhcp struct
-> creates and inits trie root
-> inits trie skeleton with saved adresses
*/
dhcp_t *DHCPCreate(ip_t subnet_id, size_t locked_bits)
{
	dhcp_t *dhcp = NULL;
		
	assert(locked_bits < TOTAL_NUM_OF_BITS - SAVED_ADDRESSES_REQUIRED);
	
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
	if (DHCP_SUCCESS != InitSystemAddressesImp(dhcp))
	{
		free(dhcp);
		return NULL;
	}
		
	return dhcp;	
}

/*creates trie node*/
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
	node->child[LEFT] = left_child;
	node->child[RIGHT] = right_child;
	node->is_full = is_full;
	
	return node;
}


static dhcp_status_t InitSystemAddressesImp(dhcp_t *dhcp)
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

	DestroyTrieImp(node->child[LEFT]);
	DestroyTrieImp(node->child[RIGHT]);
	
	node->parent = NULL;
	node->child[RIGHT] = NULL;
	node->child[LEFT] = NULL;
	node->is_full = 0;
	
	free(node);
	node = NULL;
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
	size_t free_leaves = 0;
	
	assert(NULL != dhcp);
		
	free_leaves = (size_t)pow(NUMBER_OF_CHILDREN, (TOTAL_NUM_OF_BITS - dhcp->locked_bits)) - 
					CountFullPreOrderImp(dhcp->root);		
		
	return (free_leaves);
}

size_t CountFullPreOrderImp(trie_node_t *node)
{	
	if (NULL == node)
	{
		return 0;
	}

	return( IsFullLeafImp(node) + 
			CountFullPreOrderImp(node->child[LEFT]) + 
			CountFullPreOrderImp(node->child[RIGHT]));
}

static int IsFullLeafImp(trie_node_t *node)
{
	assert(NULL != node);
	
	return (1 == node->is_full && NULL == node->child[LEFT] && 
			NULL == node->child[RIGHT]);
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
	
	child_t *path_arr = NULL;
	
	size_t arr_size = 0;

	assert(NULL != dhcp);
	assert(NULL != return_ip);
	
	/*array for bits*/
	arr_size = TOTAL_NUM_OF_BITS - dhcp->locked_bits;
	path_arr =  (child_t *)calloc(arr_size, sizeof(child_t));
	if (NULL == path_arr)
	{
		return DHCP_MALLOC_FAIL;
	}
	
	/*fill array*/
	RetrievePathImp(&(ip_request), dhcp->locked_bits, path_arr);	

	/*create path in trie*/
	status = FollowPathImp(dhcp, path_arr, arr_size);
	if (DHCP_NO_FREE_IP == status || DHCP_MALLOC_FAIL == status)
	{
		free(path_arr);
		return status;
	}	
	
	/*store ip back*/
	StoreReturnIpImp(&(dhcp->subnet), return_ip, path_arr, dhcp->locked_bits);
	
	free(path_arr);
	return status;
}

static int IsIpEqualImp(ip_t *ip_1, ip_t *ip_2)
{
	assert(NULL != ip_1);
	assert(NULL != ip_2);
	
	return !(memcmp((void *)(ip_1->ip_chars), (void *)(ip_2->ip_chars), IP_LEN));
}

/*retrives correct path from ip_requested, 
starting after locked bits, into arr given 

arr[0] gets MSB, arr[end] gets LSB*/
static void RetrievePathImp(ip_t *ip, size_t locked_bits, child_t *arr)
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
			child_t child = 
			(child_t)(((ip->ip_chars[byte_num]) >> (BITS_IN_BYTE - 1 - i) ) & 0x1);

			/*save in array only free bits*/
			if (bit_num >= locked_bits)
			{
				arr[arr_index] = child;
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
	
-> when reached the end (path index == height)
	- mark node as is_full
	
-> go upward and check if parent has 2 children and they are full
	-if so - make him full ad go up again
	-if not, return status
*/
static dhcp_status_t FollowPathImp(dhcp_t *dhcp, child_t *path_arr, size_t height)
{
	trie_node_t *curr_node = NULL;
	
	child_t next_child = LEFT;
	
	size_t path_index = 0;
	
	dhcp_status_t status = DHCP_SUCCESS;
	
	assert(NULL != dhcp);
	assert(NULL != path_arr);
	assert(NULL != dhcp->root);
	
	curr_node = dhcp->root;
	
	/*until reached final leaf*/
	while (path_index < height)
	{
		next_child = path_arr[path_index];
		
		/*if next child doesnt exist*/
		if (NULL == curr_node->child[next_child])
		{
			/*create child*/
			curr_node->child[next_child] = 
			CreateTrieNodeImp(curr_node, NULL, NULL, 0);
			
			if (NULL == curr_node->child[next_child])
			{
				return DHCP_MALLOC_FAIL;
			}
			
			/*move to next child in path*/
			curr_node = curr_node->child[next_child];
			++path_index;
		}
		
		/*if next child exists and is full goes to next child*/
		else if (1 == curr_node->child[next_child]->is_full)
		{			
			/*no free path case*/
			if (RIGHT == next_child)
			{				
				while (NULL != curr_node->parent && 
						curr_node  == curr_node->parent->child[RIGHT])	
				{
					curr_node = curr_node->parent;
					--path_index;				
				}
				
				if (NULL == curr_node->parent)
				{
					return DHCP_NO_FREE_IP;
				}
				
				curr_node = curr_node->parent;
			}
			
			status = DHCP_REQUEST_TAKEN;	
			
			/*update path*/
			path_arr[path_index] = RIGHT;			
		}
		
		/*has a child and not full*/
		else
		{
			/*move to next child in path*/
			curr_node = curr_node->child[next_child];
			++path_index;
		}				
	}
	
	/*got to final leaf, mark curr node as full*/
	curr_node->is_full = 1;
	
	/*go upward and mark as is_full what needs to be marked*/
	while (NULL != curr_node->parent && IsChildrenFullImp(curr_node->parent))
	{
		curr_node->parent->is_full = 1;
		curr_node = curr_node->parent;
	}
		
	return status;
}

/*stores subnet and ip from path arr into return ip*/
static void StoreReturnIpImp(ip_t *subnet, ip_t *ip, child_t *path_arr, size_t locked_bits)
{
	size_t bit_num = 0;
	size_t byte_num = 0;
	
	assert(NULL != ip);
	assert(NULL != subnet);
	assert(NULL != path_arr);
	
	/*nullify return ip*/
	ip->ip_chars[0] = 0;
	ip->ip_chars[1] = 0;
	ip->ip_chars[2] = 0;
	ip->ip_chars[3] = 0;
	
	/*whole ip loop*/		
	while (bit_num < TOTAL_NUM_OF_BITS)
	{
		size_t i = 0;
		unsigned char temp_bit = 0;
		
		/*single char loop*/
		while (i < BITS_IN_BYTE)
		{
			/*copies free address*/
			if (bit_num >= locked_bits)
			{
				temp_bit = (unsigned char)path_arr[bit_num - locked_bits];
				
				ip->ip_chars[byte_num] |= temp_bit << iTH_PLACE_FROM_LSB;
			}
			
			/*copies subnet*/
			else
			{
				/*take first bit from subnet*/
				temp_bit = (subnet->ip_chars[byte_num] & iTH_DIGIT_FROM_LSB;
				
				ip->ip_chars[byte_num] |= temp_bit << iTH_PLACE_FROM_LSB;
				
			}			
			
			++bit_num;
			++i;			
		}
		
		++byte_num;
	}
}


static int IsChildrenFullImp(trie_node_t *node)
{
	assert(NULL != node);
	
	if (NULL == node->child[RIGHT] && node->child[LEFT]->is_full == 1)
	{
		return  0;
	}
	
	if (NULL == node->child[LEFT] && node->child[RIGHT]->is_full == 1)
	{
		return  0;
	}
	
	return node->child[LEFT]->is_full == 1 && node->child[RIGHT]->is_full == 1;
}


/*	O(log n)	
	can only free ips generated
	return SUCCESS 
	INVALID_FREE for address already freed
	unspecified: ip recivded was not generated by dhcp */
dhcp_status_t DHCPFreeIp(dhcp_t *dhcp, ip_t ip)
{
	child_t *path_arr = NULL;
	dhcp_status_t status = DHCP_SUCCESS;
	size_t arr_size = 0;
	
	assert(NULL != dhcp);
	
	if (1 == IsIpEqualImp(&ip, &g_network_address) ||
		1 == IsIpEqualImp(&ip, &g_server_address) ||
		1 == IsIpEqualImp(&ip, &g_broadcast_address))
	{
		return DHCP_INVALID_FREE;
	}
	
	/*array for bits*/
	arr_size = TOTAL_NUM_OF_BITS - dhcp->locked_bits;
	path_arr =  (child_t *)calloc(arr_size, sizeof(child_t));
	if (NULL == path_arr)
	{
		return DHCP_MALLOC_FAIL;
	}
	
	/*fill array*/
	RetrievePathImp(&(ip), dhcp->locked_bits, path_arr);	
	
	status = FreeImp(dhcp, path_arr, arr_size);

	free(path_arr);
	return status;
}

static dhcp_status_t FreeImp(dhcp_t *dhcp, child_t *path_arr, size_t height)
{
	trie_node_t *curr_node = NULL;
	
	child_t next_child = LEFT;
	
	size_t path_index = 0;
	
	assert(NULL != dhcp);
	assert(NULL != path_arr);
	assert(NULL != dhcp->root);
	
	curr_node = dhcp->root;
	
	/*until reached final leaf*/
	while (path_index < height)
	{
		next_child = path_arr[path_index];
		
		/*if next child doesnt exist*/
		if (NULL == curr_node->child[next_child])
		{
			return DHCP_ALREADY_FREE;
		}
	
		else if (path_index == height - 1 && 0 == curr_node->is_full)
		{
			return DHCP_ALREADY_FREE;		
		}
		
		/*move to next child in path*/
		curr_node = curr_node->child[next_child];
		++path_index;
	}
	
	/*got to final leaf, mark curr node as full*/
	curr_node->is_full = 0;
	
	/*go upward and mark as as empty what needs to be marked*/
	while (NULL != curr_node->parent && 1 == curr_node->parent->is_full)
	{
		curr_node->parent->is_full = 0;
		curr_node = curr_node->parent;
	}
		
	return DHCP_SUCCESS;
}
