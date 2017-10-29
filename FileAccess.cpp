/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: FileAccess.cpp
 *
 *
 *  FileAccess.cpp: Provides the implementation of the functions in the
 *  FileAccess.h header. Allows for the file to be opened, read line by line,
 *  and rewinded to the beginning, if need be.
 */

#include "stdafx.h"
#include "FileAccess.h"

/** FileAccess::FileAccess()
 *  FileAccess::FileAccess()
 *
 *  NAME
 *    FileAccess::FileAccess
 *
 *  SYNOPSIS
 *    FileAccess::FileAccess(int argc, char* argv[]);
 *
 *    argc --> number of arguments passed in via command line
 *    argv --> name of the VC3600 assembly language file
 *
 *  DESCRIPTION
 *    This function, which is the constructor for the file access class,
 *    attempts to open a VC3600 assembly language file. If there is more than
 *    one file passed into the program, or if the one file could not be opened,
 *    it will terminate.
 *
 *  RETURNS
 *    ((none))
 */

FileAccess::FileAccess(int argc, char* argv[]) {
  // Check that there is exactly one runtime parameter. We check to see that
  // argc is exactly 2 because the first argument is the program source file
  // name (not to be confused with VC3600 assembly language file name).
  if (argc != 2) {
    cerr << "Usage: Assem <FileName>" << endl;
    exit(1);
  }

  // Open the VC3600 assembly language file. ios::in is the default mode for
  // ifstream objects, but we pass it in just to be thorough in understanding.
  m_source_file.open(argv[1], ios::in);

  // If the source file could not be opened, terminate the program.
  if (!m_source_file) {
    cerr << "Source file could not be opened, assembler terminated." << endl;
    exit(1);
  }
}
/*FileAccess::FileAccess(int argc, char* argv[]);*/

/** FileAccess::~FileAccess()
 *  FileAccess::~FileAccess()
 *
 *  NAME
 *    FileAccess::~FileAccess
 *
 *  SYNOPSIS
 *    FileAccess::~FileAccess();
 *
 *  DESCRIPTION
 *    This function, which is the destructor for the file access class, closes
 *    the previously opened VC3600 assembly language file.
 *
 *  RETURNS
 *    ((none))
 */

FileAccess::~FileAccess() {
  m_source_file.close();
}
/*FileAccess::~FileAccess();*/

/** FileAccess::GetNextLine()
 *  FileAccess::GetNextLine()
 *
 *  NAME
 *    FileAccess::GetNextLine
 *
 *  SYNOPSIS
 *    bool FileAccess::GetNextLine(string& a_buffer);
 *
 *    a_buffer --> one line from the opened file
 *
 *  DESCRIPTION
 *    This function attempts to read in a line from the file. If the file has
 *    reached the end, then no line will be read.
 *
 *  RETURNS
 *    Returns true if there is a line to be read and false if the eofbit is
 *    set, meaning that the file has reached the end and there are no more
 *    lines to be read.
 */

bool FileAccess::GetNextLine(string& a_buffer) {
  // Return false if the eofbit is set.
  if (m_source_file.eof()) {
    return false;
  }

  // Reads a line from the source file (an ifstream object) into the string
  // called a_buffer. Returns true if this step was reached.
  getline(m_source_file, a_buffer);
  return true;
}
/*bool FileAccess:GetNextLine(string& a_buffer);*/

/** FileAccess::Rewind()
 *  FileAccess::Rewind()
 *
 *  NAME
 *    FileAccess::Rewind
 *
 *  SYNOPSIS
 *    void FileAccess::Rewind();
 *
 *  DESCRIPTION
 *    This function clears any flags that were set on the file and sets the
 *    file pointer back to the beginning.
 *
 *  RETURNS
 *    ((void))
 */

void FileAccess::Rewind() {
  // Clear any flags that were set on the file.
  m_source_file.clear();

  // Reset the file with an offset of 0 from ios::beg (the beginning of the
  // file).
  m_source_file.seekg(0, ios::beg);
}
/*void FileAcces::Rewind();*/