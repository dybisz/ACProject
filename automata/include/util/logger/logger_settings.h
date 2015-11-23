//
// Created by jakub on 11/22/15.
//

#ifndef AC_LOG_SETTINGS_H
#define AC_LOG_SETTINGS_H

/*
 * All Log Settings are defined such as:
 *      Verbose levels
 *      Log files.
 *      Styling string.
 *
 */

#include <iostream>
#include "logger_colors.h"

/*
 * File to specify extra output file
 */
struct File {
    File(){}
    File(std::string name){
        this->name = name;
        doStyle = true;
    }
    File(std::string name, bool doStyle){
        this->name = name;
        this->doStyle = doStyle;
    }
    std::string name;
    bool doStyle;
};

enum Verbose_t
{
    INFO,
    WARNING,
    DEBUG,

    PSO,
    OPTIMIZER
};

struct Verbose
{
    Verbose(){}
    Verbose(Verbose_t type){
        this->type = type;
        setNameAndColor();
    }

    void setNameAndColor()
    {
        switch(this->type) {
            case INFO:
                this->name = "Info";
                this->color = logger::colors::GREEN;
                break;
            case WARNING:
                this->name = "Warning";
                this->color = logger::colors::BLUE;
                break;
            case DEBUG:
                this->name = "Debug";
                this->color = logger::colors::RED;
                break;
            case PSO:
                this->name = "PSO";
                this->color = logger::colors::LIGHT_CYAN;
                break;
            case OPTIMIZER:
                this->name = "Optimizer";
                this->color = logger::colors::LIGHT_CYAN;
                break;
        }
    }

    Verbose_t type;
    std::string name;
    std::string color;

};


namespace logger
{
    namespace settings
    {
        //-----------------------------------------------------------//
        //  VARIABLES
        //-----------------------------------------------------------//

        // Name of the default file.
        // The file will be saved in the:
        // LOG_MAIN_DIR/LOG_CURR_DIR directory
        extern std::string DEFAULT_FILE_NAME;

        // Default File output
        extern std::ofstream DEFAULT_FILE_STREAM;
        // Extra file output
        extern std::ofstream EXTRA_FILE_STREAM;

        // Extra file
        extern File EXTRA_FILE;
        extern Verbose DEFAULT_VERBOSE;
        extern Verbose CURRENT_VERBOSE;
        extern int CURRENT_VERBOSE_DEPTH;

        //-----------------------------------------------------------//
        //  CONSTANTS
        //-----------------------------------------------------------//

        // Full path directory to current log dir
        extern std::string FULL_DIR_STR;

        /* ------ STYLES ----- */

        // String separator between date variables
        extern std::string DATE_SEPARATOR;
        // String separator between time variables
        extern std::string TIME_SEPARATOR;
        // String separator between path statements
        extern std::string BETWEEN_SEPARATOR;

        // The separator between paths
        extern std::string PATH_SEPARATOR;

        // The intent style between beginning of line and the message itself
        extern std::string LOG_INTENT;
        extern std::string LOG_INTENT_WHITESPACE;

    }
}

#endif //AC_LOG_SETTINGS_H