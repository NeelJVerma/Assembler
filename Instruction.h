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

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "stdafx.h"

class Instruction {
 public:
  // Constructor.
  Instruction();

  // Destructor.
  ~Instruction();

  // Codes to indicate the type of instruction we are processing.
  enum InstructionType {
    MACHINE_LANGUAGE = 1, // Machine language instruction.
    ASSEMBLY_LANGUAGE, // Assembly language instruction.
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

  const int m_MAX_VALUE = 999999; // Max value for an operand.
  const int m_MISSING_OPCODE = 99; // Code for a missing opcode. It just has to
                                   // be something that's not an opcode number.
                                   // I picked 99 because I wanted to stay
                                   // consistent with the 9 trend.
  const string m_UNKNOWN_OPERAND = "????"; // The string code for an unknown
                                           // operand.
  const string m_UNKNOWN_OPERATOR = "??"; // The string  code for a missing
                                          // operator.

  // Parse the instruction.
  InstructionType ParseInstruction(string& a_buffer);
  
  // Compute the location of the next instruction.
  int LocationNextInstruction(const int& a_location);

  // LABEL INFORMATION.
  // Get the label.
  inline string& Label() { return m_label; }

  // Determine if a label was entered.
  inline bool IsLabel() const { return !m_label.empty(); }

  // OPCODE INFORMATION.
  // Get the opcode.
  inline string& OpCode() { return m_op_code; }

  // Get opcode number.
  inline int OpCodeNum() const { return m_op_code_num; }

  // OPERAND INFORMATION.
  // Get the operand.
  inline string& Operand() { return m_operand; }

  // Get the operand value.
  inline int OperandValue() const { return m_operand_value; }

  // Return true if is numeric operand.
  inline bool IsNumericOperand() const { return m_is_numeric_operand; }

  // Return true if an operand was entered.
  inline bool IsOperand() const { return !m_operand.empty(); }

 private:
  // The elements of an instruction.
  string m_label; // The label.
  string m_op_code; // The symbolic op code.
  string m_operand; // The operand.

  // The original instruction.
  string m_instruction;

  // Derived values.
  int m_op_code_num; // The numerical value of the op code.
  InstructionType m_type; // The type of instruction.
  bool m_is_numeric_operand; // Tell if an operand is numeric.
  int m_operand_value; // The value of the operand, if it is numeric.

  // Functions to tell whether an instruction is assembly or machine language.
  bool IsAssemblyInstruction(const string& a_segment);
  bool IsMachineInstruction(const string& a_segment);

  // Remove the comment from the instruction.
  void RemoveComment(string& a_segment);

  // Clearing the members of the class. Used in parsing line by line.
  void ClearInformation();

  // Check if an operand only contains an integer value.
  bool IsNumericOperand(const string& a_segment);
  
  // Check if the label is valid.
  bool IsValidLabel(const string& a_segment);

  // Check if proper syntax was used for an assembly or machine language
  // instruction.
  void CheckAssemblySyntax();
  void CheckMachineSyntax();

  // A hash map used to translate the string into an actual machine language
  // instruction.
  const unordered_map<string, MachineOpCode> m_machine_code {
    { "ADD", ADD },
    { "SUB", SUB },
    { "MULT", MULT },
    { "DIV", DIV },
    { "LOAD", LOAD },
    { "STORE", STORE },
    { "READ", READ },
    { "WRITE", WRITE },
    { "B", B },
    { "BM", BM },
    { "BZ", BZ },
    { "BP", BP },
    { "HALT", HALT }
  };

  // A hash map used to translate the string into an actual assembly language
  // instruction.
  const unordered_map<string, AssemblyCode> m_assembly_code {
    { "ORG", ORG },
    { "DC", DC },
    { "DS", DS },
    { "END", END_PROGRAM }
  };
};

#endif