/*
*    A silly C++ library to parse command line parameters for your C and C++ programs.
*
*    Copyright (C) 2015  Geoffrey Atkinson
*    
*    Geoffrey Atkinson <gatkinson@skyloupe.com>
*    
*    This library is free software; you can redistribute it and/or
*    modify it under the terms of the GNU Lesser General Public
*    License as published by the Free Software Foundation; either
*    version 3 of the License, or (at your option) any later version.
*    
*    This library is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    Lesser General Public License for more details.
*    
*    You should have received a copy of the GNU Lesser General Public
*    License along with this library; if not, write to the Free Software
*    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <string>
#include <vector>

#include "opts.h"

#if defined (_WIN32) 
#if defined (cli_EXPORTS)
#define  CLI_EXPORT __declspec(dllexport)
#else
#define  CLI_EXPORT __declspec(dllimport)
#endif 
#else 
#define CLI_EXPORT
#endif

typedef void(*optioncb_t)(const std::string& flag, const std::string& value, void* param);

namespace qwikpirate
{
    class  ArgVee
    {
    public:
        ArgVee(const std::string keyregex = "--[a-zA-Z0-9_]+$") : flagregex_(keyregex) { }
        virtual ~ArgVee() = default;

        virtual bool setOption(const std::string& name, bool optional = true, bool flag_only = true,
                               optioncb_t callback = nullptr, void* data = nullptr);
        virtual bool parse(int argc, const char* argv[], std::vector<std::string>& errors);

        virtual bool getFlag(const std::string& key, std::vector<int>& values);
        virtual bool getFlag(const std::string& key, std::vector<double>& values);
        virtual bool getFlag(const std::string& key, std::vector<std::string>& values);

        virtual void reset() { arguments_.clear(); options_.clear(); }

        virtual void apply();

    private:
        virtual bool verify(std::vector<std::string>& errors);
        bool isFlag(const std::string& str) const;
        bool findFlag(const std::string& flag) const;

        std::string flagregex_;
        Arguments<std::string> arguments_;
        std::vector<Option<std::string> > options_;
    };
}


