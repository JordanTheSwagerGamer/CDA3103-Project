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
int instruction_decode(unsigned op, struct_controls *controls)
{
    switch (op)
    {
        case(0): // r-type instruction (000000)
        {
            controls->RegDst = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->ALUOp = 7;
            controls->MemWrite = 0;
            controls->MemtoReg = 0;
            controls->ALUSrc = 0;
            controls->RegWrite = 1;
            break;
        }
        case(2): // j (000010)
        {
            controls->RegDst = 2;
            controls->Jump = 1;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            controls->MemtoReg = 2;
            controls->ALUSrc = 1;
            controls->RegWrite = 0;

            break;
        }
        case(4): // beq (000100)
        {
            controls->RegDst = 2;
            controls->Jump = 0;
            controls->Branch = 1;
            controls->MemRead = 0;
            controls->ALUOp = 1; // Subtraction
            controls->MemWrite = 0;
            controls->MemtoReg = 2;
            controls->ALUSrc = 0;
            controls->RegWrite = 0;

            break;
        }
        case(8): // addi (001000)
        {
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->ALUOp = 0; // Addition
            controls->MemWrite = 0;
            controls->MemtoReg = 0;
            controls->ALUSrc = 1;
            controls->RegWrite = 1;

            break;
        }
        case(10): //slti (001010)
        {
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->ALUOp = 2; // Signed Less than
            controls->MemWrite = 0;
            controls->MemtoReg = 0;
            controls->ALUSrc = 1;
            controls->RegWrite = 1;

            break;
        }
        case(11): // sltiu (001011)
        {  
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->ALUOp = 3; // Unisgned less than
            controls->MemWrite = 0;
            controls->MemtoReg = 0;
            controls->ALUSrc = 1;
            controls->RegWrite = 1;

            break;
        }
        case (15): // lui (001111)
        {
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->ALUOp = 6; // << 16.
            controls->MemWrite = 0;
            controls->MemtoReg = 0;
            controls->ALUSrc = 1;
            controls->RegWrite = 1;

            break;
        }
        case (35): // lw (100011)
        {
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 1;
            controls->ALUOp = 0; // Unsure...
            controls->MemWrite = 0;
            controls->MemtoReg = 1;
            controls->ALUSrc = 1;
            controls->RegWrite = 1;

            break;
        }
        case (43): // sw (101011)
        {
            controls->RegDst = 2; 
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->ALUOp = 0; // Unsure...
            controls->MemWrite = 1;
            controls->MemtoReg = 2;
            controls->ALUSrc = 1;
            controls->RegWrite = 0;

            break;
        }
        default:
        {
            return 1; // Fail
        }

    }
    return 0; // Success

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    // Simple copy over
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{   
    // Shift the 15th bit from the offset and isolate it.

    // i.e Let's say we have 
    // 111 1011 1001 1111
    // We shift >> 15.
    // 000 0000 0000 0001
    // Then we isolate by masking with 1 (01).
    // This should give us the bit by itself in this case it's 1

    int result = (offset >> 15) & 1;

    // We must perform a sign extent if and only if the most significant bit is 1. (Meaning negative)
    if (result == 1)
    {
        *extended_value = offset | (0xFFFF0000); // Perform a bitwise OR to force the upper 16 bits (0xFFFF0000) to be 1's 
        // This helps retain the original value but just extends it to be 32 bits long. 

    }else // Else we just leave the upper bits as they are (AKA) as 0's
    {
        *extended_value = offset & (0x0000FFFF); // Forces upper bits to be 0 with a binary op AND.
    }

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

