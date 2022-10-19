#pragma once
#include <iostream>

#define INFO " [INFO]"
#define ERROR "[ERROR]"
#define WARN " [WARN]"
#define IMPL " [IMPL]"

using namespace std;

void log_out(const char *_lvl, const char *_file, int _line, const char *_msg)
{

    printf("%s %s:%03d: %s\n", _lvl, _file, _line, _msg);

    // cout
    //     << _lvl << " " << _file << ":" << _line << ": " << _msg << "\n";
    // cout << ":\n\t" << _msg << "\n";
}

#ifdef DEBUG
#define LOG(_lvl, _msg) log_out(_lvl, __FILE__, __LINE__, _msg)
#else
#define LOG(_lvl, _msg)
#endif
