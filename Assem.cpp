/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Assem.cpp
 *
 *
 *  Assem.cpp: The main program that will run and test assembler functionality.
 */

#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "Emulator.h"

int main(int argc, char* argv[]) {
  Assembler assem(argc, argv);

  // Establish the location of the labels:
  assem.PassOne();

  // Display the symbol table.
  assem.DisplaySymbolTable();
  system("pause");
  
  // Output the symbol table and the translation.
  assem.PassTwo();
  system("pause");

  // Run the emulator on the VC3600 program that was generated in Pass II.
  assem.RunEmulator();
  system("pause");

  // Terminate indicating all is well.  If there is an unrecoverable error, the 
  // program will terminate at the point that it occurred with an exit(1) call.

  return 0;
}