#ifndef _OSCOPE2100_COMMON_H_
#define _OSCOPE2100_COMMON_H_

#include <iostream>
#include <sstream>
#include <gtk/gtk.h>


typedef unsigned char uchar;

const std::string WINDOW_TITLE="Oscope 2100";


void load_settings();
void save_settings();

std::string fround4 (double x);
std::string val2str (double,std::string,bool=true);
std::string f2str(double,bool=false);
std::string pad(std::string s,unsigned int n);
bool prepare_expstr();

#define TO_STRING2(X) #X
#define TO_STRING(X) TO_STRING2(X)
#define LOG_PREFIX // __FILE__ "(" TO_STRING(__LINE__) "): "
#define ERROR(...)   fprintf(stderr, LOG_PREFIX "ERROR  : " __VA_ARGS__)
#define WARNING(...) fprintf(stderr, LOG_PREFIX "WARNING: " __VA_ARGS__)
#define INFO(...)    fprintf(stderr, LOG_PREFIX "INFO   : " __VA_ARGS__)
#define DEBUG(...)   fprintf(stderr, LOG_PREFIX "DEBUG  : " __VA_ARGS__)
#endif
