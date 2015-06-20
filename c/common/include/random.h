#ifndef RANDOM_H_
#define RANDOM_H_

#define LFG_MOD		1000000
#define	LFG_OFFSET	500000

#define LCG_MOD		(1 << 20)
#define LCG_OFFSET	(1 << 19)

#define next_lfg_u()	next_lfg(0)
#define next_lfg_s()	next_lfg(LFG_OFFSET)

int next_lfg (int);
int next_lcg (void);

#endif
