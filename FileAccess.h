/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: FileAccess.h
 *
 *
 *  FileAccess.h: Provides class abstraction to read in the VC3600 assembly
 *  file line by line.
 */

#ifndef _FILEACCESS_H_
#define _FILEACCESS_H_

#include "stdafx.h"

class FileAccess {
 public:
  // Opens the file.
  FileAccess(int argc, char *argv[]);

  // Closes the file.
  ~FileAccess();

  // Get the next line from the source file.
  bool GetNextLine(string& a_buffer);

  // Put the file pointer back to the beginning of the file.
  void Rewind();

 private:
  ifstream m_source_file; // The source file to read in.
};

#endif
