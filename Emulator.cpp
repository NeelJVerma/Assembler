/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Emulator.h
 *
 *
 *  Emulator.cpp: Implements the methods contained in the Emulator.h header
 *  file.
 */

#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"

/** Emulator::Emulator()
 *  Emulator::Emulator()
 *
 *  NAME
 *    Emulator::Emulator
 *
 *  SYNOPSIS
 *    Emulator::Emulator();
 *
 *  DESCRIPTION
 *    This function, which is the constructor for the emulator class,
 *    initializes the assembler with a default value for the accumulator and
 *    default values for every position in the memory array.
 *
 *  RETURNS
 *    ((none))
 */

Emulator::Emulator() : m_accumulator(0) {
  memset(m_memory, 0, m_MEMORY_SIZE * sizeof(int));
}
/*Emulator::Emulator();*/

/** Emulator::InsertMemory()
 *  Emulator::InsertMemory()
 *
 *  NAME
 *    Emulator::InsertMemory
 *
 *  SYNOPSIS
 *    bool Emulator::InsertMemory(const int& a_location,
 *                                const int& a_contents);
 *
 *    a_location --> the location in memory to insert into
 *    a_contents --> the contents to insert into a_location in memory
 *
 *  DESCRIPTION
 *    This function inserts information into a specified location in memory.
 *
 *  RETURNS
 *    Returns true if the insertion was successful, false otherwise.
 */

bool Emulator::InsertMemory(const int& a_location, const int& a_contents) {
  // Location is out of memory size. This will be reported during pass two of
  // assembler run through.
  if (a_location > m_MEMORY_SIZE) {
    return false;
  }

  // Successful memory insert. Set that location to hold the passed in
  // contents.
  m_memory[a_location] = a_contents;
  return true;
}
/*bool Emulator::InsertMemory(const int& a_location, const int& a_contents);*/

/** Emulator::RunProgram()
 *  Emulator::RunProgram()
 *
 *  NAME
 *    Emulator::RunProgram
 *
 *  SYNOPSIS
 *    bool Emulator::RunProgram();
 *
 *  DESCRIPTION
 *    This function runs the emulated program.
 *
 *  RETURNS
 *    Returns true if the emulation was successful, false otherwise.
 */

bool Emulator::RunProgram() {
  // Set the emulator to start running from the beginning of memory.
  int current_location = 0;
  current_location = m_memory[current_location];

  // Go through every section of memory until we get to the end.
  while (current_location < m_MEMORY_SIZE) {
    string contents = to_string(m_memory[current_location]);
    string op_code = "";
    string location = "";
    int it = 0;

    // If the contents are > 99999, the opcode must be between 10 and 13. This
    // is because 10xxxx, 11xxxx, 12xxxx, 13xxxx. Here, we are building the
    // machine language instructions based on how they would look in memory.
    if (stoi(contents) > 99999) {
      while (it < 2) {
        op_code = op_code + contents[it];
        it++;
      }
      while (it < contents.size()) {
        location = location + contents[it];
        it++;
      }
    } else {
      while (it < 1) {
        op_code = op_code + contents[it];
        it++;
      }
      while (it < contents.size()) {
        location = location + contents[it];
        it++;
      }
    }
    int op_code_value = stoi(op_code);
    int location_int = stoi(location);
    
    // Process each op code and call the appropriate function.
    switch (op_code_value) {
    case ADD:
      Add(location_int);
      break;
    case SUB:
      Subtract(location_int);
      break;
    case MULT:
      Multiply(location_int);
      break;
    case DIV:
      Divide(location_int);
      break;
    case LOAD:
      Load(location_int);
      break;
    case STORE:
      Store(location_int);
      break;
    case READ:
      Read(location_int);
      break;
    case WRITE:
      Write(location_int);
      break;
    case B:
      current_location = Branch(location_int);
      continue;
    case BM:
      if (m_accumulator < 0) {
        current_location = Branch(location_int);
        continue;
      }
      break;
    case BZ:
      if (m_accumulator == 0) {
        current_location = Branch(location_int);
        continue;
      }
      break;
    case BP:
      if (m_accumulator > 0) {
        current_location = Branch(location_int);
        continue;
      }
      break;
    case HALT:
      // It may seem pointless to return a function that just returns true, but
      // it is used for readability and so that the reader can take one glance
      // and figure out that this section is halting.
      return Halt();
    default:
      Errors::RecordError("Unknown op code. Terminating emulation.");
      Errors::DisplayCurrentError();
      return false;
    }
    current_location++;
  }
  
  // If we made it here, that means no halt statement was found, and therefore
  // the emulation was not successful.
  return false;
}
/*bool Emulator::RunProgram();*/

/** Emulator::Add()
 *  Emulator::Add()
 *
 *  NAME
 *    Emulator::Add
 *
 *  SYNOPSIS
 *    void Emulator::Add(const int& a_location);
 *
 *    a_location --> the location of memory's contents to add to accumulator
 *
 *  DESCRIPTION
 *    This function adds a section of memory to the accumulator.
 *
 *  RETURNS
 *    ((void))
 */

void Emulator::Add(const int & a_location) {
  m_accumulator += m_memory[a_location];
}
/*void Emulator::Add(const int& a_location);*/

/** Emulator::Subtract()
 *  Emulator::Subtract()
 *
 *  NAME
 *    Emulator::Subtract
 *
 *  SYNOPSIS
 *    void Emulator::Add(const int& a_location);
 *
 *    a_location --> the location of memory's contents to subtract from
 *                   accumulator
 *
 *  DESCRIPTION
 *    This function subtracts a section of memory from the accumulator.
 *
 *  RETURNS
 *    ((void))
 */

void Emulator::Subtract(const int& a_location) {
  m_accumulator -= m_memory[a_location];
}
/*void Emulator::Subtract(const int& a_location();*/

/** Emulator::Multiply()
 *  Emulator::Multiply()
 *
 *  NAME
 *    Emulator::Multiply
 *
 *  SYNOPSIS
 *    void Emulator::Multiply(const int& a_location);
 *
 *    a_location --> the location of memory's contents to multiply by
 *                   accumulator
 *
 *  DESCRIPTION
 *    This function multiplies a section of memory by the accumulator.
 *
 *  RETURNS
 *     ((void))
 */

void Emulator::Multiply(const int& a_location) {
  m_accumulator *= m_memory[a_location];
}
/*void Emulator::Multiply(const int& a_location);*/

/** Emulator::Djvide()
 *  Emulator::Divide()
 *
 *  NAME
 *    Emulator::Divide
 *
 *  SYNOPSIS
 *    void Emulator::Divide(const int& a_location);
 *
 *    a_location --> the location of memory's contents to divide by accumulator
 *
 *  DESCRIPTION
 *    This function divides a section of memory by the accumulator.
 *
 *  RETURNS
 *    ((void))
 */

void Emulator::Divide(const int& a_location) {
  // Division by zero is a fatal error, therefore exit the program.
  if (m_memory[a_location] == 0) {
    Errors::RecordError("FATAL ERROR. DIVISION BY ZERO.");
    Errors::DisplayCurrentError();
    system("pause");
    exit(1);
  }
  m_accumulator /= m_memory[a_location];
}
/*void Emulator::Divide(const int& a_location);*/

/** Emulator::Load()
 *  Emulator::Load()
 *
 *  NAME
 *    Emulator::Load
 *
 *  SYNOPSIS
 *    void Emulator::Load(const int& a_location);
 *
 *    a_location --> the location of memory's contents to load into accumulator
 *
 *  DESCRIPTION
 *    This function loads a section of memory into the accumulator.
 *
 *  RETURNS
 *    ((void))
 */

void Emulator::Load(const int& a_location) {
  m_accumulator = m_memory[a_location];
}
/*void Emulator::Load(const int& a_location);*/

/** Emulator::Store()
 *  Emulator::Store()
 *
 *  NAME
 *    Emulator::Store
 *
 *  SYNOPSIS
 *    void Emulator::Store(const int& a_location);
 *
 *    a_location --> the location of memory's contents to store into
 *
 *  DESCRIPTION
 *    This function stores the accumulator's contents into a section of memory.
 *
 *  RETURNS
 *    ((void))
 */

void Emulator::Store(const int& a_location) {
  m_memory[a_location] = m_accumulator;
}
/*void Emulator::Store(const int& a_location);*/

/** Emulator::Read()
 *  Emulator::Read()
 *
 *  NAME
 *    Emulator::Read
 *
 *  SYNOPSIS
 *    void Emulator::Read(const int& a_location);
 *
 *    a_location --> the location of memory's contents read into
 *
 *  DESCRIPTION
 *    This function reads ONLY AN INTEGER into a section  of memory.
 *
 *  RETURNS
 *    ((void))
 */

void Emulator::Read(const int& a_location) {
  string input;
  bool is_alpha = true;
  
  // Read the input until it is entered as an integer.
  while (is_alpha) {
    cout << "Reading: ";
    cin >> input;

    for (auto it = input.begin(); it != input.end(); it++) {
      if (isdigit(*it)) {
        is_alpha = false;
        continue;
      } else if (*it == '-' && it == input.begin()) {
        continue;
      }
    }
    if (is_alpha) {
      cout << "Input must be an integer." << endl;
    }
  }
  m_memory[a_location] = stoi(input);
}
/*void Emulator::Read(const int& a_location);*/

/** Emulator::Write()
 *  Emulator::Write()
 *
 *  NAME
 *    Emulator::Write
 *
 *  SYNOPSIS
 *    void Emulator::Write(const int& a_location);
 *
 *    a_location --> the location of memory's contents to write to the screen
 *
 *  DESCRIPTION
 *    This function writes a section of memory's contents to the screen.
 *
 *  RETURNS
 *    ((void))
 */

void Emulator::Write(const int& a_location) {
  cout << m_memory[a_location] << endl;
}

/** Emulator::Branch()
 *  Emulator::Branch()
 *
 *  NAME
 *    Emulator::Branch
 *
 *  SYNOPSIS
 *    void Emulator::Branch(const int& a_location);
 *
 *    a_location --> the location of memory to branch to
 *
 *  DESCRIPTION
 *    This function branches to a section of memory.
 *
 *  RETURNS
 *    Returns the passed in location, which is the location to branch to.
 */

int Emulator::Branch(const int& a_location) {
  return a_location;
}
/*int Emulator::Branch(const int& a_location);*/

/** Emulator::Halt()
 *  Emulator::Halt()
 *
 *  NAME
 *    Emulator::Halt
 *
 *  SYNOPSIS
 *    bool Emulator::Halt();
 *
 *  DESCRIPTION
 *    This function indicates that we have come to a halt statement and that it
 *    is okay to terminate execution of the program.
 *
 *  RETURNS
 *    Always returns true to indicate that a halt statement was reached.
 */

bool Emulator::Halt() {
  return true;
}
/*bool Emulator::Halt();*/