/*
   Functional simulation of all instructions 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
//#include <sys/time.h>

#include "machine.h"
#include "inst_process.h"
#include "pipeline.h"
#include "sim.h"

#define reg(x) reg_memory[x * 4].mem_data
#define mem(x) data_memory[x].mem_data

/* HOMEWORK: finish this part of code */
/* the input is a instruction, e.g. ADD	$1, $2, $3 */
void inst_func_simulation(char* inst){
	if(DATAPATH_TYPE!=3){
	int	i, j, k; 
	char *OP; 
	long r_d, r_s, r_t, C, shamt;
	char	reg_dest[32];

	/* instruction: ADD $1, $2, $3 */
	char tmp[128];
	strcpy(tmp, inst);
	OP = strtok(tmp, "\t"); 
	char* operands = OP + strlen(OP) + 1;
	printf("OP: %s operands: %s\n", OP, operands);
	PC += 4;
	if(strcmp(OP, "ADD") == 0) {
		/* get the source and destination register */
		/* get source data from the register file and calculate the result, and update the result to the register file  */
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) + reg(r_t);

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "SUB") == 0) {
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) - reg(r_t);

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "ADDI") == 0) {
		// r1 = r2 + const(imme)
		sscanf(operands, "$%ld, $%ld, %ld", &r_d, &r_s, &C);
		reg(r_d) = reg(r_s) + C;

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "SUBI") == 0) {
		// r1 = r2 - const(imme)
		sscanf(operands, "$%ld, $%ld, %ld", &r_d, &r_s, &C);
		reg(r_d) = reg(r_s) - C;

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "OR") == 0) {
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) | reg(r_t);

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "AND") == 0) {
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) & reg(r_t);

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "SLL") == 0) {
		sscanf(operands, "$%ld, $%ld, %ld", &r_d, &r_s, &shamt);
		reg(r_d) = reg(r_s) << shamt;

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "SRL") == 0) {
		sscanf(operands, "$%ld, $%ld, %ld", &r_d, &r_s, &shamt);
		reg(r_d) = reg(r_s) >> shamt;

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "LW") == 0) {
		// load one word from mem[r2+imme] to r1
		sscanf(operands, "$%ld, %ld($%ld)", &r_d, &C, &r_s);
		reg(r_d) = mem(reg(r_s) + C);

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 5;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 5;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "SW") == 0) {
		// store one word from r1 to mem[r2+imme]
		sscanf(operands, "$%ld, %ld($%ld)", &r_d, &C, &r_s);
		mem(reg(r_s) + C) = reg(r_d);

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

    if(strcmp(OP, "LBU") == 0) {
		// 	R[rt] = zeroext(Mem(R[rs]+signext(imme)))
		sscanf(operands, "$%ld, %ld($%ld)", &r_d, &C, &r_s);
		reg(r_d) = mem(reg(r_s) + C) & 0xFF;
		//oxFF = 255 (8 bit)
		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 5;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 5;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "SBU") == 0) {
		// zeroext(Mem(R[rs]+signext(imme))) = R[rt]
		sscanf(operands, "$%ld, %ld($%ld)", &r_d, &C, &r_s);
		mem(reg(r_s) + C) = reg(r_d) & 0xFF;

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "J") == 0) {
		sscanf(operands, "%s", reg_dest);
		//max_inst = inst number
		for(i = 0 ; i < max_inst * 4 ; i += 4) {
			if(strcmp(inst_memory[i].label, reg_dest)==0)
				break;
		}
		//PC = mem(i);
		PC = i;
		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 3;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 3;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "BEQ") == 0) {
		// jump to address pc+4+diff if r1 == r2
		sscanf(operands, "$%ld, $%ld, %s", &r_d, &r_s, reg_dest);
		if(reg(r_d) == reg(r_s)){
			for(i = 0 ; i < max_inst * 4 ; i += 4) {
				if(strcmp(inst_memory[i].label, reg_dest)==0)
					break;
			}
			//PC = PC + mem(j);
			PC = i;
		}

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 3;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 3;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if(strcmp(OP, "BNE") == 0) {
		// jump to address pc+4+diff if r1 != r2
		sscanf(operands, "$%ld, $%ld, %s", &r_d, &r_s, reg_dest);
		if(reg(r_d) != reg(r_s)){
			for(i = 0 ; i < max_inst * 4 ; i += 4) {
				if(strcmp(inst_memory[i].label, reg_dest)==0)
					break;
			}
			//PC = PC + mem(k);
			PC = i;
		}

		switch(DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 3;
				break;
			case PIPELINE:
				if(sim_cycles == 0)
					sim_cycles = 3;
				else
					sim_cycles++;
				break;
		}
		return;
	}

	if (strcmp(OP, "SLT") == 0) {
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		if (reg(r_s) < reg(r_t))
			reg(r_d) = 1;
		else
			reg(r_d) = 0;

		switch (DATAPATH_TYPE) {
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				if (sim_cycles == 0)
					sim_cycles = 4;
				else
					sim_cycles++;
				break;
		}
		return;
	}
}
	else {
		sim_cycles++;
		printf("Cycle: %d\n", sim_cycles);
		sim_cycles--;
		reg_update();
		mem_writeback();
		inst_execute();
		inst_decode();
		inst_fetch(inst);
		print_pipeline_register_content();
		sim_cycles++;
	}
	return;
}

