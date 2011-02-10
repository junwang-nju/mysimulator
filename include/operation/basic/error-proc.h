
/**
 * @file error-proc.h
 * @brief Procedures for error processing
 *
 * Several procedures to processes the errors or warning for my pacakge
 * are defined here. This eases to locate the errors or warnings.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Error_Process_H_
#define _Error_Process_H_

#include "operation/basic/console-output.h"
#include <cstdlib>

namespace std {

  /**
   * @brief pop up a warning
   *
   * Just write the desired warning messages to CErr.
   *
   * @param [in] msg
   *        The warning messages in C-style string
   */
  void myWarn(const char* msg) { CErr<<msg<<Endl; }
  
  /**
   * @brief pop up an error
   *
   * Just write out a desired message and stop the whole program.
   *
   * @param [in] msg
   *        The warning messages in C-style string
   */
  void myError(const char* msg) { myWarn(msg); exit(0); }

}

#endif
