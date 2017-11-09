/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Instruction.cpp
 *
 *
 *  Instruction.cpp: Provides the implementation for the functions in the
 *  Instruction.h header file.
 */

#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"

/** Instruction::Instruction()
 *  Instruction::Instruction()
 *
 *  NAME
 *    Instruction::Instruction
 *
 *  SYNOPSIS
 *    Instruction::Instruction();
 *
 *  DESCRIPTION
 *    This function, which is the constructor for the instruction class, calls
 *    ClearInformation, which clears everything/sets everything with default
 *    values.
 *
 *  RETURNS
 *    ((none))
 */

Instruction::Instruction() { ClearInformation(); }
/*Instruction::Instruction();*/

/** Instruction::~Instruction()
 *  Instruction::~Instruction()
 *
 *  NAME
 *    Instruction::~Instruction
 *
 *  SYNOPSIS
 *    Instruction::~Instruction();
 *
 *  DESCRIPTION
 *    This function, which is the destructor for the instruction class, calls
 *    ClearInformation, which clears everything/sets everything with default
 *    values. This is doing the same thing as the constructor, but it is useful
 *    to clear out the class variables when it goes out of scope.
 *
 *  RETURNS
 *    ((none))
 */

Instruction::~Instruction() { ClearInformation(); }
/*Instruction::~Instruction();*/

/** Instruction::ClearInformation()
 *  Instruction::ClearInformation()
 *
 *  NAME
 *    Instruction::ClearInformation
 *
 *  SYNOPSIS
 *    void Instruction::ClearInformation();
 *
 *  DESCRIPTION
 *    This function clears/sets default values of the member variables of the
 *    instruction class.
 *
 *  RETURNS
 *    ((void))
 */

void Instruction::ClearInformation() {
  // Set default values of strings to be empty.
  m_label = "";
  m_op_code = "";
  m_operand = "";
  m_instruction = "";

  // Set default value of opcode number to be invalid.
  m_op_code_num = 0;

  // Set default operand value to just be 0.
  m_operand_value = 0;

  // Assume the operand is not numeric at first.
  m_is_numeric_operand = false;

  // Set default instruction type to be a comment.
  m_type = COMMENT;
}
/*void Instruction::ClearInformation();*/

/** Instruction::RemoveComment()
 *  Instruction::RemoveComment()
 *
 *  NAME
 *    Instruction::RemoveComment
 *
 *  SYNOPSIS
 *    void Instruction::RemoveComment(string& a_segment);
 *
 *    a_segment --> the line to remove the comment from
 *
 *  DESCRIPTION
 *    This function parses out a comment, if there is one.
 *
 *  RETURNS
 *    ((void))
 */

void Instruction::RemoveComment(string& a_segment) {
  auto comment_start = a_segment.find(';');

  // If there is a comment, remove it, as it is not relevant.
  if (comment_start != string::npos) {
    a_segment = a_segment.substr(0, comment_start);
    return;
  }
}
/*void Instruction::RemoveComment(string& a_segment);*/

/** Instruction::IsValidLabel()
 *  Instruction::IsValidLabel()
 *
 *  NAME
 *    Instruction::IsValidLabel
 *
 *  SYNOPSIS
 *    bool Instruction::IsValidLabel(const string& a_segment);
 *
 *    a_segment --> the label to examine
 *
 *  DESCRIPTION
 *    This function determines if a label follows the constraints of being a
 *    valid label.
 *
 *  RETURNS
 *    Returns true if the label passed in is valid, false otherwise.
 */

bool Instruction::IsValidLabel(const string& a_segment) {
  // If the label is an empty string, it is considered valid.
  if (a_segment.empty()) return true;

  bool is_valid = true;

  // If first character isn't a letter, it is not valid.
  if (!isalpha(a_segment[0])) {
    Errors::RecordError(a_segment +
                        " has invalid syntax. Must start with a letter.");
    is_valid = false;
  }

  // If it has a length greater than 10, it is not valid.
  if (a_segment.length() > 10) {
    Errors::RecordError(a_segment + " cannot be more than 10 characters.");
    is_valid = false;
  }

  // If any character violates the alphanumeric rule, it is not valid.
  for (auto it = a_segment.begin(); it != a_segment.end(); it++) {
    if (!isalnum(*it)) {
      Errors::RecordError(a_segment + "has an invalid character " + *it + ".");
      is_valid = false;
    }
  }
  return is_valid;
}
/*bool Instruction::IsValidLabel(const string& a_segment);*/

/** Instruction::IsMachineInstruction()
 *  Instruction::IsMachineInstruction()
 *
 *  NAME
 *    Instruction::IsMachineInstruction
 *
 *  SYNOPSIS
 *    bool Instruction::IsMachineInstruction(const string& a_segment);
 *
 *    a_segment --> the instruction to proof
 *
 *  DESCRIPTION
 *    This function determines if an instruction is a machine language
 *    instruction.
 *
 *  RETURNS
 *    Returns true if the passed in instruction is a machine language
 *    instruction, false otherwise.
 */

bool Instruction::IsMachineInstruction(const string& a_segment) {
  auto it = m_machine_code.find(a_segment);

  // If the passed in segment is found in the machine code hash map, we set
  // the appropriate values and return true. Otherwise, return false.
  if (it != m_machine_code.end()) {
    m_op_code = it->first;
    m_op_code_num = it->second;
    m_type = MACHINE_LANGUAGE;
    return true;
  }
  return false;
}
/*bool Instruction::IsMachineInstruction(const string& a_segment);*/

/** Instruction::IsAssemblyInstruction()
 *  Instruction::IsAssemblyInstruction()
 *
 *  NAME
 *    Instruction::IsAssemblyInstruction
 *
 *  SYNOPSIS
 *    bool Instruction::IsAssemblyInstruction(const string& a_segment);
 *
 *    a_segment --> the instruction to proof
 *
 *  DESCRIPTION
 *    This function determines if an instruction is an nassembly language
 *    instruction.
 *
 *  RETURNS
 *    Returns true if the passed in instruction is an assembly language
 *    instruction, false otherwise.
 */

bool Instruction::IsAssemblyInstruction(const string& a_segment) {
  auto it = m_assembly_code.find(a_segment);

  // If the passed in segment is found in the assembly code hash map, we set
  // the appropriate values and return true. Otherwise, return false;
  if (it != m_assembly_code.end()) {
    m_op_code = it->first;
    m_op_code_num = 0;

    // If the instruction is to end the program, we set the type of instruction
    // to end.
    if (it->second == END_PROGRAM) m_type = END_INSTRUCTION;
    else m_type = ASSEMBLY_LANGUAGE;
    return true;
  }
  return false;
}
/*bool Instruction::IsAssemblyInstruction(const string& a_segment);*/

/** Instruction::ParseInstruction()
 *  Instruction::ParseInstruction()
 *
 *  NAME
 *    Instruction::ParseInstruction
 *
 *  SYNOPSIS
 *    Instruction::InstructionType
 *    Instruction::ParseInstruction(string& a_buffer);
 *
 *    a_buffer --> the instruction to parse
 *
 *  DESCRIPTION
 *    This function parses the instruction into its appropriate parts, which
 *    are operand, opcode, and label. It also attempts to classify the
 *    instruction into four types, which are comment, assembly, machine, or the
 *    end instruction.
 *
 *  RETURNS
 *    Returns the instruction type of the parsed instruction. For example,
 *    machine or assembly.
 */

Instruction::InstructionType
Instruction::ParseInstruction(string& a_buffer) {
  // Clear the information at the beginning of every instruction parse.
  ClearInformation();

  // If there an empty line, return it as a comment. Additionally, if the first
  // character is a ';', the whole line is a comment.
  if (a_buffer.empty() || a_buffer.find_first_of(';') == 0) return m_type;

  m_instruction = a_buffer;
  string temp_buffer = a_buffer;

  // Remove the comment if there is one. We use a temporary buffer because we
  // have to preserve the original instruction.
  RemoveComment(temp_buffer);

  istringstream iss(temp_buffer);
  vector<string> instruction_parts;

  // Read each segment into a string stream and put it into a vector of the
  // three separate parts of an instruction: label, opcode, operand.
  while (iss >> temp_buffer) {
    // Still have to check for emptiness.
    if (!temp_buffer.empty()) instruction_parts.push_back(temp_buffer);
  }

  // VC3600 can only hold 3 parts of an instruction.
  if (instruction_parts.size() > 3) {
    Errors::RecordError("Too many arguments. VC3600 only allows 3.");
  }

  bool is_assembly = false; 
  bool is_machine = false;
  bool label_validation = false;

  // Go through each instruction part and assign it to the member variables.
  for (int column = 0; column < instruction_parts.size(); column++) {
    string temp_part = instruction_parts[column];

    // If the part is in the first column and there are 3 parts, the first part
    // must be a label.
    if (column == 0 && instruction_parts.size() == 3) {
      m_label = instruction_parts[column];
      label_validation = IsValidLabel(m_label);
      continue;
    }

    // Convert the part to all uppercase, to handle differing case of
    // instructions.
    transform(temp_part.begin(), temp_part.end(), temp_part.begin(),
              ::toupper);

    // Handle if an instruction is machine language.
    if (is_machine) {
      m_operand = instruction_parts[column];

      // For machine language, the label is the operand.
      label_validation = IsValidLabel(m_operand);
      
      // Machine language instructions are not allowed to have numeric
      // operands.
      m_is_numeric_operand = IsNumericOperand(m_operand);
      if (m_is_numeric_operand) {
        Errors::RecordError("Invalid use of numeric operand " + m_operand +
                            " on machine language instruction.");
      }
      continue;
    }

    // Handle if an instruction is assembly language.
    if (is_assembly) {
      m_operand = instruction_parts[column];

      // Assembly language instructions can only have numeric operands.
      m_is_numeric_operand = IsNumericOperand(m_operand);
      if (!m_is_numeric_operand) {
        Errors::RecordError("Invalid use of non-numeric operand " + m_operand +
                            " on assembly language instruction.");
      }
      else m_operand_value = stoi(instruction_parts[column]);
      continue;
    }

    // Verifying if an instruction is machine or assembly.
    is_machine = IsMachineInstruction(temp_part);
    is_assembly = IsAssemblyInstruction(temp_part);

    if (is_machine) continue;
    if (is_assembly) continue;
  }

  // Check if machine/assembly syntax is correct.
  if (is_machine) CheckMachineSyntax();
  else if (is_assembly) CheckAssemblySyntax();
  else {
    Errors::RecordError("Invalid syntax. No instruction found.");
    m_op_code = m_MISSING_OPCODE;
    m_operand = m_UNKNOWN_OPERAND;
  }
  return m_type;
}
/*Instruction::InstructionType
  Instruction::ParseInstruction(string& a_buffer);*/

/** Instruction::LocationNextInstruction()
 *  Instruction::LocationNextInstruction()
 *
 *  NAME
 *    Instruction::LocationNextInstruction
 *
 *  SYNOPSIS
 *    int Instruction::LocationNextInstruction(const int& a_location);
 *
 *    a_location --> the location of the current instruction
 *
 *  DESCRIPTION
 *    This function will compute and return the location of the next
 *    instruction.
 *
 *  RETURNS
 *    Returns the location of the next instruction.
 */

int Instruction::LocationNextInstruction(const int & a_location) {
  // If the instruction type is assembly language, we should check if it is ORG
  // or DS. Otherwise, the location of the next instruction is just the
  // location + 1.
  if (m_type == ASSEMBLY_LANGUAGE && IsOperand()) {
    if (m_assembly_code.at(m_op_code) == ORG) {
      if (m_is_numeric_operand) return m_operand_value;
    } else if (m_assembly_code.at(m_op_code) == DS) {
      if (m_is_numeric_operand) return a_location + m_operand_value;
    }
  }
  return a_location + 1;
}
/*int Instruction::LocationNextInstruction(const int & a_location);*/

/** Instruction::IsNumericOperand()
 *  Instruction::IsNumericOperand()
 *
 *  NAME
 *    Instruction::IsNumericOperand
 *
 *  SYNOPSIS
 *    bool Instruction::IsNumericOperand(const string& a_segment);
 *
 *    a_segment --> the operand to proof
 *
 *  DESCRIPTION
 *    This function determine if an operand is numeric. This function is
 *    overloaded. The other version of this function is a getter method that
 *    returns the member variable m_is_numeric_operand.
 *
 *  RETURNS
 *    Returns true if the operand is numeric, false otherwise.
 */

bool Instruction::IsNumericOperand(const string& a_segment) {
  // Returns true if every character in the operand is a digit, false
  // otherwise.
  return ((!a_segment.empty()) && (find_if(a_segment.begin(), a_segment.end(),
          [](char c) { return !isdigit(c); }) == a_segment.end()));
}
/*bool Instruction::IsNumericOperand(const string& a_segment);*/

/** Instruction::CheckMachineSyntax()
 *  Instruction::CheckMachineSyntax()
 *
 *  NAME
 *    Instruction::CheckMachineSyntax
 *
 *  SYNOPSIS
 *    void Instruction::CheckMachineSyntax();
 *
 *  DESCRIPTION
 *    This function checks the validity of the machine instruction's syntax.
 *
 *  RETURNS
 *    ((void))
 */
 
void Instruction::CheckMachineSyntax() {
  if (!m_op_code.empty()) {
    string op_code = m_op_code;

    // Handle differing cases in instruction.
    transform(op_code.begin(), op_code.end(), op_code.begin(), ::toupper);

    // Locate the instruction in the machine code hash map and report errors
    // accordingly.
    auto it = m_machine_code.find(op_code);
    if (it != m_machine_code.end()) {
      if (it->second == HALT) {
        if (IsOperand()) {
          Errors::RecordError("Invalid syntax. Cannot call HALT on operand.");
        }
        return;
      } else {
        if (!IsOperand()) {
          Errors::RecordError("Operand required after " + m_operand + ".");
        }
      }
    }
  } else {
    // If we reached this point, no opcode was found. That is an error in which
    // the program cannot continue.
    Errors::RecordError("FATAL ERROR. NO OP CODE.");
    Errors::DisplayCurrentError();
    system("pause");
    exit(1);
  }
}
/*void Instruction::CheckMachineSyntax();*/

/** Instruction::CheckAssemblySyntax()
 *  Instruction::CheckAssemblySyntax()
 *
 *  NAME
 *    Instruction::CheckAssemblySyntax
 *
 *  SYNOPSIS
 *    void Instruction::CheckAssemmblySyntax();
 *
 *  DESCRIPTION
 *    This function checks the validity of the assembly instruction's syntax.
 *
 *  RETURNS
 *    ((void))
 */

void Instruction::CheckAssemblySyntax() {
  if (!m_op_code.empty()) {
    string op_code = m_op_code;

    // Handle differing cases in instruction.
    transform(op_code.begin(), op_code.end(), op_code.begin(), ::toupper);
   
    // Search for the op code in the assembly code hash map and report errors
    // accordingly.
    auto it = m_assembly_code.find(op_code);
    if (it != m_assembly_code.end()) {
      switch (it->second) {
      case ORG:
        if (IsLabel()) {
          // ORG instruction cannot have a label.
          Errors::RecordError("ORG cannot have a label.");
        }
        break;
      case DS:
      case DC:
        if (!IsLabel()) {
          // This case is the same for DS and DC. Both need a label.
          Errors::RecordError("DS and DC must have a label.");
        }
        break;
      default:
        if (IsLabel() || IsOperand()) {
          // END instruction cannot have a label or operand.
          Errors::RecordError("END cannot have a label or operand.");
        }
        return;
      }

      // Check if there is an operand.
      if (!IsOperand()) {
        Errors::RecordError("Missing operand on " + m_op_code +
                            " instruction.");
      }

      // If there is an operand, it is numeric, and it exceeds the max value of
      // an operand, report an error.
      if ((IsOperand()) && (m_is_numeric_operand) &&
          (m_operand_value > m_MAX_VALUE)) {
        Errors::RecordError("Operand exceeds max size of " +
                            to_string(m_MAX_VALUE) + ".");
      }
    } else {
      // If we reached this point, no opcode was found. That is an error in which
      // the program cannot continue.
      Errors::RecordError("FATAL ERROR. NO OP CODE.");
      Errors::DisplayCurrentError();
      system("pause");
      exit(1);
    }
  }
}
/*void Instruction::CheckAssemblySyntax();*/