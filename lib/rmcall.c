#include <kernel.h>

extern void int32(unsigned char intnum, regs16_t *regs);

/*
 * Wrapper for libfalcon's int32()
 *
 */

void rmcall(char interrupt, regs16_t *r)
{
	int32(interrupt, r);
}