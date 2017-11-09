/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Assembler.h
 *
 *
 *  Assembler.h: Container for the whole assembler. Will go through pass one,
 *  pass two, and run the emulator.
 */

#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include "stdafx.h"
#include "SymTab.h"
#include "FileAccess.h"
#include "Instruction.h"
#include "Emulator.h"
#include "Errors.h"

class Assembler {
 public:
  // Constructor.
  Assembler(int argc, char* argv[]);

  // Pass one. Establish location of the symbols.
  void PassOne();

  // Pass two. Generate a translation.
  void PassTwo();

  // Display the symbol table.
  inline void DisplaySymbolTable() { m_symbol_table.DisplaySymbolTable(); }

  // Run emulator on the generated translation.
  void RunEmulator();

 private:
  FileAccess m_file_access; // File access object.
  SymbolTable m_symbol_table; // Symbol table object.
  Instruction m_instruction; // Instruction object.
  Emulator m_emulator; // Emulator object.

  // The information needed to record an instruction.
  struct InstructionInformation {
    int s_location; // Instruction's location.
    int s_contents; // Instruction's contents.
  };
  vector<InstructionInformation> m_instruction_information; // A vector that
                                                            // holds the
                                                            // information of
                                                            // individual
                                                            // instructions.

  // A function to print each line of the emulated code.
  void PrintTranslation(const int& a_instruction_location,
                        const int& a_operand_location,
                        const int& a_op_code_number,
                        const string& a_instruction,
                        const Instruction::InstructionType& a_type);
};

#endif