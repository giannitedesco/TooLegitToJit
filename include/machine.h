/*
* (C) Iain Fraser - GPLv3  
* Physical machine interface. Each arch supported needs to implement it.
*/

#ifndef _MACHINE_H_
#define _MACHINE_H_

#include <assert.h>	// TODO: remove once error checking in temp_reg
#include "operand.h"
#include "emitter.h"

struct machine {
	int sp;
	int nr_reg;
	int nr_temp_regs;  // first NR_TEMP_REGS registers are temps the rest are used for locals and consts
	int reg[];
};

struct machine_ops {
	void (*move)( struct emitter* me, struct machine* m, operand d, operand s );
	void (*add)( struct emitter* me, struct machine* m, operand d, operand s, operand t );
	void (*sub)( struct emitter* me, struct machine* m, operand d, operand s, operand t );
	void (*mul)( struct emitter* me, struct machine* m, operand d, operand s, operand t );
	void (*div)( struct emitter* me, struct machine* m, operand d, operand s, operand t );
	void (*mod)( struct emitter* me, struct machine* m, operand d, operand s, operand t );
	void (*pow)( struct emitter* me, struct machine* m, operand d, operand s, operand t );
	void (*b)( struct emitter* me, struct machine* m, label l );
	void (*beq)( struct emitter* me, struct machine* m, operand d, operand s, label l );
	void (*blt)( struct emitter* me, struct machine* m, operand d, operand s, label l );
	void (*bgt)( struct emitter* me, struct machine* m, operand d, operand s, label l );
	void (*ble)( struct emitter* me, struct machine* m, operand d, operand s, label l );
	void (*bge)( struct emitter* me, struct machine* m, operand d, operand s, label l );
	void (*call)( struct emitter* me, struct machine* m, operand fn );
	void (*ret)( struct emitter* me, struct machine* m );

	void (*call_cfn)( struct emitter* me, struct machine* m, uintptr_t fn, size_t argsz );

	// each machine has an associated emitter 
	void (*create_emitter)( struct emitter** e, size_t vmlines );
};

static inline int temp_reg( struct machine* m, int idx ){
	assert( idx < m->nr_temp_regs );		// TODO: error checking instead
	return m->reg[ idx ]; 
}

#endif 

