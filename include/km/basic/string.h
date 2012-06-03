
/**
 * @file basic/string.h
 * @brief some basic operations for char-array-based strings
 *
 * In \c C -language, char array could be treated as string. the \a \<cstring\>
 * includes some basic operations. Besides these functions, there are some
 * more needs for the string operations (such as parsing PDB file). This file
 * includes some additional operations for the char-array-base string.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_String_H_
#define _Basic_String_H_

namespace mysimulator {

  /** @fn unsigned int mysimulator::LineSize(const char* s)
   * @brief get the size of a string as a line
   *
   * a line could be regared as a char-array-based string with the char '\\n'
   * or '\0' as its terminal. This function gives out the size of the line,
   * namely the number of chars in the line (except the terminal char).
   *
   * @param s [in] the input string (char array)
   * @return the size of string line
   */
  unsigned int LineSize(const char* s) {
    char* l=const_cast<char*>(s);
    while(((*l)!='\n')&&((*l)!='\0')) ++l;
    return static_cast<unsigned int>(l-s);
  }

  /** @fn void mysimulator::SubString(char*,const char*,unsigned int,unsigned int)
   * @brief get sub-string based on assigned edges
   *
   * Sometime, we need to pick out part of string as a new string. Since
   * char-array-based string needs '\0' as terminal of string, this function
   * copies out the content of sub-string and append a terminal '\0' behind
   * the content.
   *
   * @param sub [out] the output string (char array)
   * @param src [in] the input string (char array)
   * @param bg,ed [in] the beginning and end locations of sub-string in source
   *                   string
   */
  void SubString(char* sub,const char* src,unsigned int bg,unsigned int ed) {
    char* p=const_cast<char*>(src)+bg;
    char* pend=const_cast<char*>(src)+ed+1;
    char* q=sub;
    for(;p!=pend;)  *(q++)=*(p++);
    *q='\0';
  }

}

#endif

