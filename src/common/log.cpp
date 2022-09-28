#include "log.h"

#include <iostream>
#include <fstream>
#include <utility>
#include <assert.h>
#include <cstdlib>

namespace FS = std::filesystem;

namespace Log {
    namespace {
        struct Out {
            const FS::path file;
            const bool cout {false};
            std::ofstream *fout {nullptr};
            bool open {false};

            Out(const std::pair<FS::path, bool>& p);
            Out(const FS::path& file_, const bool cout_);
            ~Out();
            void FLUSH();
            void PRINT(const std::string str, bool endl=false);
            void CLOSE();
            void OPEN ();
        };
        using Pair = std::pair<FS::path, bool>;
        //std::array<Out, 3> output {    // BUG AJMV 17-nov-2021
        //    Pair{fname[log ], true },  // Inicializar esta variable usando fname (que es otra variable global)
        //    Pair{fname[err ], false},  // necesita que fname se haya inicializado antes.
        //    Pair{fname[warn], true }   // No se puede garantizar.
        //};
        std::array<Out, 3> output {
            Pair{"simulation_report.txt", true },
            Pair{"error_report.txt"     , false},
            Pair{"warning_report.txt"   , true }
        };
        bool is_open   = true;
        bool instanced = true;
    }
    
    /************************************/
    /*    vvv Specific functions vvv    */
    /************************************/
    void LOG(const std::string str, bool endl){
        if (is_open) output[log].PRINT(str, endl);
    }

    void ERR(const std::string str, bool endl){
        if (is_open) output[err].PRINT(str, endl);
    }

    void WARN(const std::string str, bool endl){
        if (is_open) output[warn].PRINT(str, endl);
    }
    /************************************/
    /*    ^^^ Specific functions ^^^    */
    /************************************/

    void FLUSH() {
        if (is_open) for (auto& o : output) o.FLUSH();
    }

    void OPEN () {
        if (instanced) {
            if (is_open) CLOSE();
            for (auto& o : output) o.OPEN();
            is_open = true;
        }
    }

    void CLOSE() {
        if (is_open){
            FLUSH();
            for (auto& o : output) o.CLOSE();
            is_open = false;
        }
    }

    void DEL () {
        CLOSE();
        instanced = false;
    }

    FS::path FNAME (const ID id) {
        return output[id].file;
    }

    void ASSERT (const bool condition, const std::string& message, const int exit_code) {
        if (!condition) {
            ::Log::ERR(message);
            std::exit(exit_code);
        }
    }

    namespace {
        Out::Out(const std::pair<FS::path, bool>& p) :
        file(p.first), cout(p.second), open(false) {
            this->OPEN();
        }

        Out::Out(const FS::path& file_, const bool cout_) :
        file(file_), cout(cout_), open(false) {
            this->OPEN();
        }

        Out::~Out(){
            this->CLOSE();
        }

        void Out::FLUSH() {
            if (this->open){
                this->fout->flush();
                if (this->cout) std::cout.flush();
            }
        }

        void Out::PRINT(const std::string str, bool endl){
            if (this->open) {
                *this->fout << str;
                if (this->cout) std::cout << str;
                if (endl){
                    *this->fout << std::endl;
                    if (this->cout) std::cout << std::endl;
                }
            }
        }

        void Out::CLOSE(){
            if(this->open){
                this->FLUSH();
                this->fout->close();
                delete this->fout;
                this->fout = nullptr;
                this->open = false;
            }
        }

        void Out::OPEN (){
            if (!this->open) {
                this->fout = new std::ofstream;
                this->fout->open(this->file);
                assert(this->fout->good());
                this->open = true;
            }
        }
    } // namespace
} // namespace Log
