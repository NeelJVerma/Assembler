/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Errors.cpp
 *
 *
 *  Errors.cpp: Provides the implementation for the functions in the Errors.h
 *  header file. Allows for errors to be recorded and displayed.
 */

#include "stdafx.h"
#include "Errors.h"

// Initialize the static member variables.
int Errors::m_total_errors;
vector<string> Errors::m_error_messages;

/** Errors::InitErrorReporting()
 *  Errors::InitErrorReporting()
 *
 *  NAME
 *    Errors::InitErrorReporting
 *
 *  SYNOPSIS
 *    void Errors::InitErrorReporting();
 *
 *  DESCRIPTION
 *    This function clears out all previous error messages and starts the error
 *    counting. We don't use a constructor because we want one object to remain
 *    everywhere throughout the program.
 *
 *  RETURNS
 *    ((void))
 */

void Errors::InitErrorReporting() {
  m_total_errors = 0;

  // If there are no errors, there is no need to clear the vector. Otherwise,
  // we will clear it.
  if (!m_total_errors) return;

  m_error_messages.clear();
}
/*void Errors::InitErrorReporting();*/

/** Errors::RecordError()
 *  Errors::RecordError()
 *
 *  NAME
 *    Errors::RecordError
 *
 *  SYNOPSIS
 *    void Errors::RecordError(const string& a_error_message);
 *
 *    a_error_message --> the error message to be recorded
 *
 *  DESCRIPTION
 *    This function appends an error message to the m_error_messages, if there
 *    is no empty string passed in.
 *
 *  RETURNS
 *    ((void))
 */

void Errors::RecordError(const string& a_error_message) {
  // If no error message was found, don't record anything.
  if (a_error_message.empty()) return;

  m_error_messages.push_back(a_error_message);
  m_total_errors++;
}
/*void Errors::RecordError(const string& a_error_message);*/

/** Errors::CreateError()
 *  Errors::CreateError()
 *
 *  NAME
 *    Errors::CreateError
 *
 *  SYNOPSIS
 *    string Errors::CreateError(const int& a_location, const string& a_error);
 *
 *    a_location --> location where error was found
 *    a_error --> error message
 *
 *  DESCRIPTION
 *    This function creates an instance of an error.
 *
 *  RETURNS
 *    Returns the error message. We return it so we can pass it into
 *    void Errors::RecordError.
 */

string Errors::CreateError(const int& a_location, const string& a_error) {
  return("Error at location " + to_string(a_location) + ": " + a_error);
}
/*string Errors::RecordError(const int& a_location, const string& a_error);*/

/** Errors::DisplayErrors()
 *  Errors::DisplayErrors()
 *
 *  NAME
 *    Errors::DisplayErrors
 *
 *  SYNOPSIS
 *    void Errors::DisplayErrors();
 *
 *  DESCRIPTION
 *    This function displays all error messages that were recorded, if there
 *    were any.
 *
 *  RETURNS
 *    ((void))
 */

void Errors::DisplayErrors() {
  // If no errors were recorded, program was translated successfully.
  if (!m_total_errors) {
    cout << "Program translated successfully!" << endl;
    return;
  }

  // Print the error messages.
  cout << m_total_errors
       << (m_total_errors == 1 ? " ERROR REPORT:" : " ERROR REPORTS:") << endl;

  for (auto error : m_error_messages) {
    cout << error << endl;
  }
}
/*void Errors::DisplayErrors();*/