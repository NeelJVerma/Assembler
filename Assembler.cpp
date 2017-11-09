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

// TODO: Add to the destructor if needed.
Assembler::~Assembler() { }

void Assembler::PassOne() {
  // Tracks location of the instructions to be generated.
  int location = 0;

  // Process each line of source code.
  while (true) {
    string buffer;

    // If there are no more lines, an end statement is missing. This error
    // will be reported in pass 2.
    if (!m_file_access.GetNextLine(buffer)) return;

    // Parse the instruction and get the instruction type.
    Instruction::InstructionType type = m_instruction.ParseInstruction(buffer);

    // If this is an end statement, there is nothing left to do in pass 1. Pass
    // two will determine if the end is the last statement.
    if (type == Instruction::END_INSTRUCTION) return;

    // Labels can only be on machine language and assembly language type
    // instruction. Skip all other types.
    if (type != Instruction::MACHINE_LANGUAGE &&
        type != Instruction::ASSEMBLY_LANGUAGE) continue;

    // If the instruction has a label, record the label and its location in the
    // symbol table.
    if (m_instruction.IsLabel()) {
      m_symbol_table.AddSymbol(m_instruction.Label(), location);
    }

    // Compute the location of the next instruction.
    location = m_instruction.LocationNextInstruction(location);
  }
}

void Assembler::PassTwo() {
  // Start the ability to record errors and clear out any unwanted information
  // from possible previous runs.
  Errors::InitErrorReporting();

  // Rewind the file so that we can evaluate it from the beginning.
  m_file_access.Rewind();

  int location = 0;
  int operand_location = 0;
  cout << "_________________________________________________" << endl;
  cout << "Translation of program:" << endl;
  cout << "Location\tContents\tOriginal Instruction" << endl;
  while (true) {
    string buffer;
    if (!m_file_access.GetNextLine(buffer)) {
      Errors::RecordError("FATAL ERROR. MISSING END STATEMENT.");
      return;
    }

    Instruction::InstructionType type = m_instruction.ParseInstruction(buffer);

    if (type == Instruction::END_INSTRUCTION) {
      if (m_file_access.GetNextLine(buffer)) {
        Errors::RecordError("Statement after END statement.");
        Errors::DisplayCurrentError();
        return;
      }
    }
    if (type != Instruction::MACHINE_LANGUAGE &&
        type != Instruction::ASSEMBLY_LANGUAGE) {
      PrintTranslation(location, operand_location, m_instruction.OpCodeNum(),
                       buffer, type);
      continue;
    }
    operand_location = 0;

    if (m_instruction.IsOperand() && !m_instruction.IsNumericOperand() &&
        !m_symbol_table.LookupSymbol(m_instruction.Operand(),
                                     operand_location)) {
      if (operand_location == m_symbol_table.m_MULTIPLY_DEFINED_SYMBOL) {
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

    PrintTranslation(location, operand_location, m_instruction.OpCodeNum(),
                     buffer, type);

    if (location > Emulator::m_MEMORY_SIZE) {
      Errors::RecordError("Location " + to_string(location) +
                          " is out of memory.");
      Errors::DisplayCurrentError();
    }
    location = m_instruction.LocationNextInstruction(location);
  }
  system("pause");
}

void Assembler::PrintTranslation(const int & a_instruction_location,
                                 const int & a_operand_location,
                                 const int & a_op_code_number,
                                 const string & a_instruction,
                                 const Instruction::InstructionType & a_type) {
  string contents = "";
  InstructionInformation instruction_information;
  stringstream ss;
  int location = a_operand_location;

  if (a_type == Instruction::COMMENT ||
      a_type == Instruction::END_INSTRUCTION) {
    cout << "\t\t\t" << a_instruction << endl;
    return;
  }

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
  ss.str(string());
  ss << setfill('0') << setw(2) << a_op_code_number << setw(4) << location;
  contents = ss.str();

  instruction_information.s_contents = stoi(contents);
  instruction_information.s_location = a_instruction_location;
  cout << "  " << a_instruction_location << "\t\t" << contents
       << "\t\t" << a_instruction << endl;
  m_instruction_information.push_back(instruction_information);
}

void Assembler::RunEmulator() {
  for (auto it = m_instruction_information.begin();
       it != m_instruction_information.end(); it++) {
    if (m_emulator.InsertMemory(it->s_location, it->s_contents)) continue;
    else {
      Errors::RecordError("FATAL ERROR. OUT OF MEMORY.");
      Errors::DisplayCurrentError();
      system("pause");
      exit(1);
    }
  }

  if (m_emulator.RunProgram()) cout << "Emulation successful." << endl;
  else {
    Errors::RecordError("FATAL ERROR. UNABLE TO COMPLETE EMULATION.");
    Errors::DisplayCurrentError();
    system("pause");
    exit(1);
  }
  system("pause");
}
