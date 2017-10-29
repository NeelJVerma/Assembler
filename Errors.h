/** Name: Neel Verma
 *  Course: CMPS361 - Software Design
 *  Project: Assembler
 *  Instructor: Dr. Victor Miller
 *  Current File: Errors.h
 *
 *
 *  Errors.h: Provides class abstraction for error storage and displaying.
 */

#ifndef _ERRORS_H_
#define _ERRORS_H_

#include "stdafx.h"

class Errors {
 public:
   // Start reporting errors.
   static void InitErrorReporting();

   // Record an error message.
   static void RecordError(const string& a_error_message);

   // Create an instance of an error.
   static string CreateError(const int& a_location, const string& a_error);

   // Print all errors.
   static void DisplayErrors();

 private:
  static vector<string> m_error_messages; // Storage for the error messages.
  static int m_total_errors; // The total number of error messages.
};

#endif