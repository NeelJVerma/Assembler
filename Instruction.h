/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Instruction.h
 *
 *
 *  Instruction.h: Provides functionality to parse and provide information 
 *  about instructions.
 */

// TODO: FIGURE OUT WHAT ELSE IS NEEDED, THEN IMPLEMENT CLASS METHODS.

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "stdafx.h"

class Instruction {
 public:
  // Constructor and destructor.
  Instruction();
  ~Instruction();

  // Codes to indicate the type of instruction we are processing.
  enum InstructionType {
    MACHINE_LANGUAGE = 1, // Machine language instruction.
    ASSEMBLER_INSTRUCTION, // Assembly language instruction.
    COMMENT, // Comment or blank line.
    END_INSTRUCTION // End instruction.
  };

  // Symbolic codes for machine language instructions.
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

  // Symbolic codes for assembly language instructions.
  enum AssemblyCode {
    ORG = 1, // Define origin. The operand specifies the address at which the
             // translation of the next instruction will be generated.
    DC, // Define constant. The constant is a decimal integer placed in the
        // operand field.
    DS, // Define storage. The operand specifides the number of words of
        // storage to be set aside.
    END_PROGRAM // Indicates that there are no additional statements to 
                // translate.
  };

  // Parse the instruction.
  InstructionType ParseInstruction(const string& a_buffer);
  
  // Compute the location of the next instruction.
  int LocationNextInstruction(const int& a_location);

  // Access the label.
  inline string GetLabel() const { return m_label; }

  // Determine if a label is blank.
  inline bool IsLabel() const { return !m_label.empty(); }

 private:
  // The elements of an instruction.
  string m_label; // The label.
  string m_op_code; // The symbolic op code.
  string m_operand; // The operand.

  // The original instruction.
  string m_instruction;

  // Derived values.
  int m_number_op_code; // The numerical value of the op code.
  InstructionType m_type; // The type of instruction.
  bool m_is_numeric_operand; // Tell if a operand is numeric.
  int m_operand_value; // The value of the operand, if it is numeric.
};

#endif