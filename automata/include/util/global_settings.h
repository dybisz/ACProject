//
// Created by dybisz on 11/12/15.
//

#ifndef AC_GLOBAL_SETTINGS_H
#define AC_GLOBAL_SETTINGS_H

#include <string>
#include <cmath>

// Few remarks about whole project:
// |--o   symbols take values from interval [1; _numberOfSymbols]
// |--o   states are marked by values from interval [1; _numberOfStates]
// |--o   actual values declared in global_settings.cpp (<3 c++)
// |--o   alphabet is represented by integers from interval [_alphabet[0], _alphabet.size()]

namespace global_settings {
    /* ------ OPTIMIZER SETTINGS ----- */
    // Minimum states to check
    extern int MIN_STATES;
    // Maximum number of states to check
    extern int MAX_STATES;

    /* ------ PSO SETTINGS ----- */
    // URL to file with tool automaton
    extern std::string TOOL_URL;
    // Maximum iterations of PSO algorithm
    extern int MAX_ITER;
    // TODO comment
    extern double LEARNING_FACTOR;
    // TODO comment
    extern double PARTICLE_VELOCITY;
    // When encoding particle back to automaton
    // each dimension must be casted down to integer value.
    // If p[i] > x.5 then take the ceiling.
    // otherwise take the floor.
    // Formally:
    //      encodedValue = (int)p[i]
    //      delta = p[i] - encodedValue
    //      if delta > ENCODING_DELTA
    //          encodedValue++
    //
    extern double ENCODING_DELTA;

    // Becouse of the nature of the encoding the
    // upper interval bound must a bit less than:
    // n + ENCODING_DELTA
    extern double UPPER_BOUND_ERR;

    // The factor of the maximum change in position that one particle can take
    // during a single PSO iteration.
    extern double SPEED_FACTOR;

    // The swarm size is scaled by this factor
    extern double POPULATION_FACTOR;

    /* ------ WORDS GENERATION ----- */
    // Maximum number of testing words
    extern int R_MAX;
    // Number of words in omega_{S}
    extern int SIZE_S;
    // Number of words in omega_{M}
    extern int SIZE_M;
    // Number of words in omega_{L}
    extern int SIZE_L;
    // Minimum word length in omega_{S}
    extern int MIN_LENG_S;
    // Maximum word length in omega_{S}
    extern int MAX_LENG_S;
    // Minimum word length in omega_{M}
    extern int MIN_LENG_M;
    // Maximum word length in omega_{M}
    extern int MAX_LENG_M;
    // Minimum word length in omega_{L}
    extern int MIN_LENG_L;
    // Maximum word length in omega_{L}
    extern int MAX_LENG_L;

    /* ------ CLUSTERING ----- */
    // The convergence tolerance in kmeans
    extern double KM_TOL;
    // The maximum iterations of kmeans
    extern int KM_MAX_ITER;
}


#endif //AC_GLOBAL_SETTINGS_H
