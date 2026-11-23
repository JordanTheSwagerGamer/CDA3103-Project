#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    // 1. Fetch the instruction addressed by PC from Mem and write it to instruction.
    // 2. Return 1 if a halt condition occurs; otherwise, return 0.

    // Halt condition: Address must be a multiple of 4 per the rules of MIPS. (32 bits AKA 4 bytes)
   if (PC % 4 != 0) return 1;

   // Else we need to grab the starting point of the PC address to make sure we are copying the right thing.
   // Each Mem[i] holds 4 bytes, thus to make sure we obtain the full package we divide by 4.
   // Recall that to divide by 4 we can do >> 2.
   // We use the available macro given in spimcore.h
  
   *instruction =  MEM(PC);
   return 0;
}

/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{   
    // To obtain a specific portion of an instruction we must isolate the bits that we want.
    // 1. Shift right by the "lower bound" to ensure our instruction starts from 0.
    // 2. Mask (AKA only include) the specified bit ammount by using & (AND).
       // For 5 bits do : & 31 (1 1111)
       // For 6 bits do:  & 63 (11 1111)
       // For 16 bits do: & 0xFFFF (1111 1111 1111 1111)
       // For 26 bits do: & 3FFFFFF (11 1111 1111 1111 1111 1111 1111)
    // Note that we might not need to shift for some cases.

    *op = (instruction >> 26) & 63;
    *r1 = (instruction >> 21) & 31;
    *r2 = (instruction >> 16) & 31;
    *r3 = (instruction >> 11) & 31;
    *funct = instruction & 63;
    *offset = instruction & 0xFFFF;
    *jsec = instruction & 0x3FFFFFF;

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

