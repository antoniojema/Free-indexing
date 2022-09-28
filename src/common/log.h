/*
    Developers: Miguel D. Ruiz-Cabello. Antonio J. Martin Valverde
    Institution: UGR, Electromagnetic group of Granada
    Proyect: FDTDpp
*/
#pragma once
#include <filesystem>
#include <string>
#include <array>

#define Q(x) #x
#define QUOTE(x) Q(x)
#define ERRORINFILELINEMSG "Error in " __FILE__ ", line" QUOTE(__LINE__)
#define ERRORINFILELINE ::Log::ASSERT(false, ERRORINFILELINEMSG)

namespace Log
{   
    /*****************/
    /*    Enum ID    */
    /*****************/
    enum ID {
        none=-1, log, err, warn
    };
    
    /*******************/
    /*    File names   */
    /*******************/
    //inline const std::array<::std::filesystem::path, 3> fname {  // BUG AJMV 17-nov-2021
    //    "simulation_report.txt",                                 // Explicado en log.cpp
    //    "error_report.txt",                                      // fname[Log::ID] sustituida por FNAME(Log::ID)
    //    "warning_report.txt"
    //};
    
    /****************************/
    /*    Specific functions    */
    /****************************/
    void LOG (const ::std::string str, bool endl=false);
    void ERR (const ::std::string str, bool endl=false);
    void WARN(const ::std::string str, bool endl=false);
    
    /***************************/
    /*    General functions    */
    /***************************/
    void FLUSH();
    void OPEN ();
    void CLOSE();
    void DEL  ();
    std::filesystem::path FNAME(const ID);
    void ASSERT(const bool, const std::string&, const int=1);
} // namespace Log
