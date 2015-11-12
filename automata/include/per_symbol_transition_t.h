//
// Created by root on 11/12/15.
//

#ifndef AC_PER_SYMBOL_TRANSITION_T_H
#define AC_PER_SYMBOL_TRANSITION_T_H

#include "standard_transition_t.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

class PerSymbolTransitionTable: public StandardTransitionTable {
public:
    PerSymbolTransitionTable(string url);
    void print();
    bool operator()(int state1, int symbol, int state2);

private:
    bool _isTransition(int state1, int symbol, int state2);
    void _printEntries();
    void _printPerSymbolTransitionTable(int symbol);
};

#endif //AC_PER_SYMBOL_TRANSITION_T_H
