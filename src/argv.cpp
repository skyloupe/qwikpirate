/*
*    A silly C++ library to parse command line parameters for your C and C++ programs.
*
*    Copyright (C) 2015 Skyloupe LLC
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

#include <iostream>
#include <regex>
#include <vector>

#include "argv.h"

namespace qwikpirate
{

bool ArgVee::isFlag(const std::string& str) const
{
    try
    {
        return std::regex_match(str, std::regex(flagregex_));
    }
    catch (std::regex_error& err)
    {
        std::cerr << err.what() << std::endl;
    }
    return false;    
}

bool ArgVee::findFlag(const std::string& flag) const
{
    return arguments_.has(flag);
}

bool ArgVee::setOption(const std::string& name, bool optional, bool flag_only, 
                       optioncb_t callback, void* data)
{
    if(false == isFlag(name))
    {
        return false;
    }

    Option<std::string> opt(name, optional, flag_only, callback, data);
    
    try
    {
        options_.push_back(opt);
    }
    catch (const std::exception&)
    {
        return false;
    }

    return true;    
}

bool ArgVee::parse(int argc, const char* argv[], std::vector<std::string>& errors)
{
    arguments_.clear();

    if (argc < 1) 
    {
        errors.push_back("No command line arguments");
        return false;
    }

    if (nullptr == argv)
    {
        errors.push_back("Null command line");
        return false;
    }

    if (1 < argc && true == options_.empty())
    {
        errors.push_back("No options set");
        return false;
    }

    for (int i = 1; i < argc; i++)
    {
        if (nullptr == argv[i])
        {
            errors.push_back("Null argument in command line");
            return false;
        }

        std::string argi(argv[i]);

        // Flags must be of the form specified in this->keyregex_
        if (true == this->isFlag(argi))
        {
            // Strip the leading dashes
            std::string flag = argi;//.substr(2);
            std::string value;

            // End case flag with no options, so give it an empty value
            if (i + 1 >= argc)  
            {
                this->arguments_.set(flag, value);
                i++;
                continue;
            }
        
            // If next argument is a value, add flag/value and skip to what should 
            // be the next flag
            std::string argi1(argv[i+1]);
            if (false == this->isFlag(argi1))
            {
                // Set the value
                value = argv[i + 1];
                i++;
            }
                
            this->arguments_.set(flag, value);
        }
        else
        {
            // Should only encounter flags on each iteration
            return false;
        }
    }

    return verify(errors);
}

bool ArgVee::verify(std::vector<std::string>& errors)
{
    bool valid = true;

    //figure out how to verify regex syntax

    //verify options
    for (auto& option : options_)
    {
        std::vector<std::string> values;

        bool getflag = getFlag(option.getName(), values);

        if (false == getflag && false == option.getOptional())
        {
            errors.push_back(std::string("Missing flag: ") + option.getName());
            valid = false;
            continue;
        }

        if (false == getflag && option.getOptional())
        {
            continue;
        }

        bool has_flag_only = true;
        for (auto val : values)
        {
            if (false == val.empty())
            {
                has_flag_only = false;
                break;
            }
        }

        // != works like xor for bool.  Think about it.
        if (has_flag_only != option.getFlagOnly())
        {
            errors.push_back("Mismatch flag/value pair");
            valid = false;
            continue;
        }
    }

    return valid;
}

bool ArgVee::getFlag(const std::string& flag, std::vector<int>& values)
{
    std::vector<std::string> vals;
    if (false == arguments_.get(flag, vals))
        return false;

    for (auto value : vals)
    {
        try
        {
            values.push_back(std::stoi(value));
        }
        catch (const std::exception&)
        {
            return false;
        }        
    }

    return true;
}

bool ArgVee::getFlag(const std::string& flag, std::vector<double>& values)
{
    std::vector<std::string> vals;
    if (false == arguments_.get(flag, vals))
        return false;

    for (auto value : vals)
    {
        try
        {
            values.push_back(std::stod(value));
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    return true;
}

bool ArgVee::getFlag(const std::string& flag, std::vector<std::string>& values)
{
    std::vector<std::string> vals;
    if (false == arguments_.get(flag, values))
        return false;

    return true;
}

void ArgVee::apply()
{
    for (auto& option : options_)
    {
        std::vector<std::string> values;
        optioncb_t callback = option.getCallback();

        bool getflag = getFlag(option.getName(), values);

        if (false == getflag && option.getOptional())
        {
            continue;
        }

        for (auto val : values)
        {
            if (nullptr != callback)
            {
                callback(option.getName(), val, option.getData());
            }
        }
    }
}

}

