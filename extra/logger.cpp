#pragma once
#include <iostream>
#include <cassert>

#define INFO " [INFO]"
#define ERROR "[ERROR]"
#define WARN " [WARN]"
#define IMPL " [IMPL]"

using namespace std;

void log_out(const char *_lvl, const char *_file, const char *_func, int _line, const char *_msg)
{

    printf("%s %s:%s:%03d: %s\n", _lvl, _file, _func, _line, _msg);
    assert(strcmp(_lvl, WARN) != 0);
    assert(strcmp(_lvl, ERROR) != 0);
}

#ifdef DEBUG
#define LOG(_lvl, _msg) log_out(_lvl, __FILE__, __FUNCTION__, __LINE__, _msg)
#else
#define LOG(_lvl, _msg)
#endif
