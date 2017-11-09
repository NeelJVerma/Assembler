/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Emulator.h
 *
 *
 *  Emulator.h: Contains functionality to record an assembly language program
 *  and execute it.
 */

#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include "stdafx.h"

class Emulator {
 public:
  const static int m_MEMORY_SIZE = 10000; // The size of the memory of the
                                          // VC3600.

  // Constructor.
  Emulator();

  // Records instructions and data into the VC3600 memory.
  bool InsertMemory(const int& a_location, const int& a_contents);

  // Runs the VC3600 program recorded in memory.
  bool RunProgram();

 private:
  int m_memory[m_MEMORY_SIZE]; // The memory for the VC3600.
  int m_accumulator; // The accumulator for the VC3600.

  // The symbolic machine op codes. This is the same as it is in Instruction.h,
  // but it is here for readability.
  enum MachineOpCode {
    ADD = 1, // ACC = c(ACC) + c(ADDR)
    SUB, // ACC = c(ACC) - c(ADDR)
    MULT, // ACC = c(ACC) * c(ADDR)
    DIV, // ACC = c(ACC) / c(ADDR)
    LOAD, // ACC = c(ADDR)
    STORE, // ADDR = c(ACC)
    READ, // Read line. First 6 digits are placed in specified address.
    WRITE, // c(ADDR) is displayed.
    B, // Go to ADDR for next instruction.
    BM, // Go to ADDR if c(ACC) < 0.
    BZ, // Go to ADDR if c(ACC) = 0.
    BP, // Go to ADDR if c(ACC) > 0.
    HALT // Terminate execution.
  };

  // Functions for symbolic op codes. Again, just for readability.
  void Add(const int& a_location);
  void Subtract(const int& a_location);
  void Multiply(const int& a_location);
  void Divide(const int& a_location);
  void Load(const int& a_location);
  void Store(const int& a_location);
  void Read(const int& a_location);
  void Write(const int& a_location);

  // We only include one branch because all branching functions will return the
  // location, so there is no need to write that four times.
  int Branch(const int& a_location);
  bool Halt();
};

#endif