/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Assembler.cpp
 *
 *
 *  Assembler.cpp: Provides the implementation for the methods defined in the
 *  Assembler.h header file.
 */

#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "SymTab.h"

/** Assembler::Assembler()
 *  Assembler::Assembler()
 *
 *  NAME
 *    Assembler::Assembler
 *
 *  SYNOPSIS
 *    Assembler::Assembler(int argc, char* argv[]);
 *   
 *    argc --> number of command line arguments
 *    argv --> command line arguments
 *
 *  DESCRIPTION
 *    This function, which is the constructor for the assembler class,
 *    initializes the file access object with argc and argv.
 *
 *  RETURNS
 *    ((none))
 */

Assembler::Assembler(int argc, char* argv[]) : m_file_access(argc, argv) { }
/*Assembler::Assembler(int argc, char* argv[]);*/

/** Assembler::PassOne()
 *  Assembler::PassOne()
 *
 *  NAME
 *    Assembler::PassOne
 *
 *  SYNOPSIS
 *    void Assembler::PassOne();
 *
 *  DESCRIPTION
 *    This function goes through the assembly program and collects all symbols
 *    and their locations, readying them for the symbol table.
 *
 *  RETURNS
 *    ((void))
 */

void Assembler::PassOne() {
  // Tracks location of the instructions to be generated.
  int location = 0;

  // Process each line of source code.
  while (true) {
    string buffer;

    // If there are no more lines, an end statement is missing. This error
    // will be reported in pass 2.
    if (!m_file_access.GetNextLine(buffer)) {
      return;
    }

    // Parse the instruction and get the instruction type.
    Instruction::InstructionType type = m_instruction.ParseInstruction(buffer);

    // If this is an end statement, there is nothing left to do in pass one.
    // Pass two will determine if the end is the last statement.
    if (type == Instruction::END_INSTRUCTION) {
      return;
    }

    // Labels can only be on machine language and assembly language type
    // instruction. Skip all other types.
    if (type != Instruction::MACHINE_LANGUAGE &&
        type != Instruction::ASSEMBLY_LANGUAGE) {
      continue;
    }

    // If the instruction has a label, record the label and its location in the
    // symbol table.
    if (m_instruction.IsLabel()) {
      m_symbol_table.AddSymbol(m_instruction.Label(), location);
    }

    // Compute the location of the next instruction.
    location = m_instruction.LocationNextInstruction(location);
  }
}
/*void Assembler::PassOne();*/

/** Assembler::PassTwo()
 *  Assembler::PassTwo()
 *
 *  NAME
 *    Assembler::PassTwo
 *
 *  SYNOPSIS
 *    void Assembler::PassTwo();
 *
 *  DESCRIPTION
 *    This function goes through the assembly program and generates a
 *    translation.
 *
 *  RETURNS
 *    ((void))
 */

void Assembler::PassTwo() {
  // Start the ability to record errors and clear out any unwanted information
  // from possible previous runs.
  Errors::InitErrorReporting();

  // Rewind the file so that we can evaluate it from the beginning.
  m_file_access.Rewind();

  // Tracks the location of the instruction being executed.
  int location = 0;
  int operand_location = 0;
  cout << "_________________________________________________" << endl;
  cout << "Translation of program:" << endl;
  cout << "Location\tContents\tOriginal Instruction" << endl;

  // Process each line of source code.
  while (true) {
    string buffer;

    // If there are no more lines to read, it must mean there is no end
    // statement.
    if (!m_file_access.GetNextLine(buffer)) {
      Errors::RecordError("FATAL ERROR. MISSING END STATEMENT.");
      Errors::DisplayCurrentError();
      return;
    }

    // Get the type of instruction.
    Instruction::InstructionType type = m_instruction.ParseInstruction(buffer);
    if (type == Instruction::END_INSTRUCTION) {
      // If there is a line after the end statement, report an error.
      if (m_file_access.GetNextLine(buffer)) {
        Errors::RecordError("Statement after END statement.");
        Errors::DisplayCurrentError();
      }
      return;
    }

    // If the type is a comment, meaning it is not end, assembly, or machine,
    // just print the comment.
    if (type != Instruction::MACHINE_LANGUAGE &&
        type != Instruction::ASSEMBLY_LANGUAGE) {
      PrintTranslation(location, operand_location, m_instruction.OpCodeNum(),
                       buffer, type);
      continue;
    }
    operand_location = 0;

    // Checking for an alphanumeric operand in the symbol table.
    if (m_instruction.IsOperand() && !m_instruction.IsNumericOperand() &&
        !m_symbol_table.LookupSymbol(m_instruction.Operand(),
                                     operand_location)) {
      if (operand_location == SymbolTable::m_MULTIPLY_DEFINED_SYMBOL) {
        Errors::RecordError("Symbol " + m_instruction.Operand() +
                            " is multiply defined.");
        Errors::DisplayCurrentError();
      } else {
        Errors::RecordError("Symbol " + m_instruction.Operand() +
                            " is undefined.");
        m_symbol_table.AddSymbol(m_instruction.Operand(),
                                 m_symbol_table.m_UNDEFINED_SYMBOL);
        Errors::DisplayCurrentError();
      }
    }

    // If the location is out of memory, report the error.
    if (location > Emulator::m_MEMORY_SIZE) {
      Errors::RecordError("Location " + to_string(location) +
                          " is out of memory.");
      Errors::DisplayCurrentError();
      return;
    }

    // Now that we're done handling all the necessary errors, we can print the
    // translation.
    PrintTranslation(location, operand_location, m_instruction.OpCodeNum(),
                     buffer, type);

    // Get the location of the next instruction.
    location = m_instruction.LocationNextInstruction(location);
  }
}
/*void Assembler::PassTwo();*/

/** Assembler::PrintTranslation()
 *  Assembler::PrintTranslation()
 *
 *  NAME
 *    Assembler::PrintTranslation
 *
 *  SYNOPSIS
 *    void Assembler::PrintTranslation(const int& a_instruction_location,
 *                                     const int& a_operand_location,
 *                                     const int& a_op_code_number,
 *                                     const string& a_instruction,
 *                                     const Instruction::InstructionType& a_type);
 *
 *    a_instruction_location --> the location of the instruction
 *    a_operand_location --> the location of the operand
 *    a_op_code_number --> the numeric value of the op code
 *    a_instruction --> the actual instruction
 *    a_type --> the symbolic name for the type of instruction
 *
 *  DESCRIPTION
 *    This function prints a single line of the translated instruction. It is
 *    used in pass two when we are translating every line.
 *
 *   RETURNS
 *    ((void))
 */

void Assembler::PrintTranslation(const int& a_instruction_location,
                                 const int& a_operand_location,
                                 const int& a_op_code_number,
                                 const string& a_instruction,
                                 const Instruction::InstructionType& a_type) {
  string contents = "";
  InstructionInformation instruction_information;
  stringstream ss;
  int location = a_operand_location;

  // If the type of instruction is a comment or an end instruction, we can just
  // print out the instruction. There is nothing else we have to do.
  if (a_type == Instruction::COMMENT ||
      a_type == Instruction::END_INSTRUCTION) {
    cout << "\t\t\t" << a_instruction << endl;
    return;
  }

  // Handle specifically if the instruction is assembly, since we have to
  // handle these differently.
  if (a_type == Instruction::ASSEMBLY_LANGUAGE) {
    if (m_instruction.OpCodeNum() == Instruction::ORG ||
        m_instruction.OpCodeNum() == Instruction::DC) {
      cout << "  " << a_instruction_location << "\t\t\t" << a_instruction
           << endl;
      if (m_instruction.OpCodeNum() == Instruction::ORG) {
        ss.str(string());
        ss << setfill('0') << setw(6) << m_instruction.OperandValue();
        contents = ss.str();
        instruction_information.s_contents = stoi(contents);
        instruction_information.s_location = a_instruction_location;
        m_instruction_information.push_back(instruction_information);
      }
      return;
    }
    location = m_instruction.OperandValue();
  }

  // Handle if the instruction is either assembly or machine.
  ss.str(string());
  ss << setfill('0') << setw(2) << a_op_code_number << setw(4) << location;
  contents = ss.str();
  instruction_information.s_contents = stoi(contents);
  instruction_information.s_location = a_instruction_location;
  cout << "  " << a_instruction_location << "\t\t" << contents
       << "\t\t" << a_instruction << endl;
  m_instruction_information.push_back(instruction_information);
}
/*void Assembler::PrintTranslation(const int& a_instruction_location,
                                   const int& a_operand_location,
                                   const int& a_op_code_number,
                                   const string& a_instruction,
                                   const Instruction::InstructionType& a_type);*/

/** Assembler::RunEmulator()
 *  Assembler::RunEmulator()
 *
 *  NAME
 *    Assembler::RunEmulator
 *
 *  SYNOPSIS
 *    void Assembler::RunEmulator();
 *
 *  DESCRIPTION
 *    This function runs the emulator.
 *
 *  RETURNS
 *    ((void))
 */

void Assembler::RunEmulator() {
  for (auto it = m_instruction_information.begin();
       it != m_instruction_information.end(); it++) {
    // If memory is available to insert, insert it. Otherwise, we have run out
    // of memory and we have to report a fatal error.
    if (m_emulator.InsertMemory(it->s_location, it->s_contents)) {
      continue;
    } else {
      Errors::RecordError("FATAL ERROR. OUT OF MEMORY.");
      Errors::DisplayCurrentError();
      system("pause");
      exit(1);
    }
  }
  cout << "Results from emulating program:" << endl;

  // If the emulation is successful, print it. Otherwise, we have to report a
  // fatal error.
  if (m_emulator.RunProgram()) {
    cout << "Emulation successful." << endl;
  } else {
    Errors::RecordError("FATAL ERROR. UNABLE TO COMPLETE EMULATION.");
    Errors::DisplayCurrentError();
    system("pause");
    exit(1);
  }
}
/*void Assembler::RunEmulator();*/
