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

Emulator::Emulator() : m_accumulator(0) {
  memset(m_memory, 0, m_MEMORY_SIZE * sizeof(int));
}

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

bool Emulator::RunProgram() {
  // FIX LATER.
  int current_location = 0;
  current_location = m_memory[current_location];

  while (current_location < m_MEMORY_SIZE) {
    string contents = to_string(m_memory[current_location]);
    string op_code = "";
    string location = "";
    int it = 0;

    // If the contents are > 99999, the opcode must be between 10 and 13. This
    // is because 10xxxx, 11xxxx, 12xxxx, 13xxxx.
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
      return Halt();
    default:
      Errors::RecordError("Unknown op code. Terminating emulation.");
      Errors::DisplayCurrentError();
      return false;
    }
    current_location++;
  }
  return false;
}

void Emulator::Add(const int & a_location) {
  m_accumulator += m_memory[a_location];
}

void Emulator::Subtract(const int& a_location) {
  m_accumulator -= m_memory[a_location];
}

void Emulator::Multiply(const int& a_location) {
  m_accumulator *= m_memory[a_location];
}

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

void Emulator::Load(const int& a_location) {
  m_accumulator = m_memory[a_location];
}

void Emulator::Store(const int& a_location) {
  m_memory[a_location] = m_accumulator;
}

void Emulator::Read(const int& a_location) {
  string input;
  bool is_alpha = true;
  
  while (is_alpha) {
    cout << "Reading: ";
    cin >> input;

    for (auto it = input.begin(); it != input.end(); it++) {
      if (isdigit(*it)) {
        is_alpha = false;
        continue;
      } else if (*it == '-') continue;
      else {
        is_alpha = true;
        Errors::RecordError("Input is not an integer.");
        break;
      }
    }
    if (is_alpha) cout << "Input must be an integer." << endl;
  }
  m_memory[a_location] = stoi(input);
}

void Emulator::Write(const int& a_location) {
  cout << m_memory[a_location] << endl;
}

int Emulator::Branch(const int& a_location) {
  return a_location;
}

bool Emulator::Halt() {
  return true;
}