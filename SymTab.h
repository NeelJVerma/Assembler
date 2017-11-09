/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: SymTab.h
 *
 *
 *  SymTab.h: Stores a symbol table. Allows for symbol table manipulation.
 */

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "stdafx.h"

class SymbolTable {
 public:
  // Constructor to initialize size to 0.
  SymbolTable();

  // Destructor to clean up the symbol table.
  ~SymbolTable();

  // Symbolic constants.
  const static int m_MULTIPLY_DEFINED_SYMBOL = -999; // Recognize a multiply
                                                     // defined symbol.
  const static int m_UNDEFINED_SYMBOL = -1000; // Recognize an undefined
                                               // symbol.
  
  // Add a new symbol to the symbol table.
  void AddSymbol(const string& a_symbol, const int& a_location);
  
  // Display the symbol table.
  void DisplaySymbolTable() const;

  // Lookup a symbol in the symbol table.
  bool LookupSymbol(const string& a_symbol, int& a_location) const;

 private:
  map<string, int> m_symbol_table; // The actual symbol table.
  int m_symbol_table_size; // The size of the symbol table.
};

#endif