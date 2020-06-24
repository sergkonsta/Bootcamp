#ifndef _KNIGHTS_TOUR_H_
#define _KNIGHTS_TOUR_H_


/* O(1) ?
undefined behavior - res_path == NULL
res_path >= 64(sizeof(char)) */
int KnightsTour(unsigned char init_pos, unsigned char *res_path);

#endif /*knights_tour.h*/
