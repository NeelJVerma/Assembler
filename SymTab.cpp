/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: SymTab.cpp
 *
 *
 *  SymTab.h: Provides the implementation for the functions in the SymTab.h
 *  header file. Allows for lookup into the table, display of thte table, and
 *  adding to the table.
 */

#include "stdafx.h"
#include "SymTab.h"

/** SymbolTable::SymbolTable()
 *  SymbolTable::SymbolTable()
 *
 *  NAME
 *    SymbolTable::SymbolTable
 *
 *  SYNOPSIS
 *    SymbolTable::SymbolTable();
 *
 *  DESCRIPTION
 *    This function, which is the constructor for the symbol table class,
 *    initializes the symbol table with a size of 0.
 * 
 *  RETURNS
 *    ((none))
 */

SymbolTable::SymbolTable() : m_symbol_table_size(0) { }
/*SymbolTable::SymbolTable();*/

/** SymbolTable::~SymbolTable()
 *  SymbolTable::~SymbolTable()
 *
 *  NAME
 *    SymbolTable::~SymbolTable
 *
 *  SYNOPSIS
 *    SymbolTable::~SymbolTable();
 *
 *  DESCRIPTION
 *    This function, which is the destructor for the symbol table, cleans up
 *    the map m_symbol_table (the actual symbol table). It also resets the size
 *    of the symbol table.
 *
 *  RETURNS
 *    ((none))
 */

SymbolTable::~SymbolTable() {
  m_symbol_table_size = 0;
  m_symbol_table.clear();
}
/*SymbolTable::~SymbolTable();*/

/** SymbolTable::AddSymbol()
 *  SymbolTable::AddSymbol()
 *
 *  NAME
 *    SymbolTable::AddSymbol
 *
 *  SYNOPSIS
 *    void SymbolTable::AddSymbol(const string& a_symbol,
 *                                const int& a_location);
 *
 *    a_symbol --> the symbol to record into the table
 *    a_location --> the symbol's location
 *
 *  DESCRIPTION
 *    This function adds a symbol to the symbol table. If the symbol has
 *    already been defined (meaning it is already in the table), record a
 *    multiply defined symbol as the location for that symbol and return.
 *
 *  RETURNS
 *    ((void))
 */

void SymbolTable::AddSymbol(const string& a_symbol, const int& a_location) {
  auto table_entry = m_symbol_table.find(a_symbol);

  // Don't check for undefined symbols. That is done when looking up a symbol.
  // Here, we only check for multiply defined symbols.
  if (table_entry != m_symbol_table.end() && m_symbol_table_size) {
    table_entry->second = m_MULTIPLY_DEFINED_SYMBOL;
    return;
  }

  // If symbol wasn't already in table, add it to the table.
  m_symbol_table[a_symbol] = a_location;
  m_symbol_table_size++;
}
/*void SymbolTable::AddSymbol(const string& symbol, const int& a_location);*/

/** SymbolTable::DisplaySymbolTable()
 *  SymbolTable::DisplaySymbolTable()
 *
 *  NAME
 *    SymbolTable::DisplaySymbolTable
 *
 *  SYNOPSIS
 *    void SymbolTable::DisplaySymbolTable() const;
 *
 *  DESCRIPTION
 *    This function displays the symbol table.
 *
 *  RETURNS
 *    ((void))
 */

void SymbolTable::DisplaySymbolTable() const {
  int entry_number = 0;

  cout << "Symbol #" << setw(13) << "Symbol" << setw(15) << "Location" << endl;

  for (auto table_entry : m_symbol_table) {
    cout << entry_number << setw(17) << table_entry.first << setw(14)
         << table_entry.second << endl;
    entry_number++;
  }
}
/*void SymbolTable::DisplaySymbolTable() const;*/

/** SymbolTable::LookupSymbol()
 *  SymbolTable::LookupSymbol()
 *
 *  NAME
 *    SymbolTable::LookupSymbol
 *
 *  SYNOPSIS
 *    bool SymbolTable::LookupSymbol(const string& a_symbol,
 *                                   const int& a_location) const;
 *
 *    a_symbol --> the symbol to lookup
 *    a_location --> the location at which the symbol was found
 *
 *  DESCRIPTION
 *    This function will lookup a symbol in the table and return whether or not
 *    it was found.
 *
 *  RETURNS
 *    Returns true if the symbol is in the table and records its location into
 *    a_location. Otherwise, it returns false and records an undefined symbol
 *    identifier into a_location.
 */

bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_location) const {
  auto table_entry = m_symbol_table.find(a_symbol);

  // If the entry is in the table, set a_location to that location and return
  // true.
  if (table_entry != m_symbol_table.end()) {
    a_location = table_entry->second;
    return true;
  }

  // If it is not in the table, set the location to be an undefined symbol and
  // return false.
  a_location = m_UNDEFINED_SYMBOL;
  return false;
}
/*bool SymbolTable::LookupSymbol(const string& a_symbol,
                                 const int& a_location) const;*/