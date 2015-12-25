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
#include <map>
#include <list>

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
    template<typename T>
    class Option
    {
        public:
            Option<T>() = delete;
            Option<T>(const T& name, bool optional, bool flag_only, optioncb_t callback = nullptr, 
                      void* data = nullptr)
                : name_( name ), optional_( optional ), flag_only_( flag_only ),
                callback_( callback ), data_( data ){}
            
            T getName() const { return name_; }
            bool getOptional() const { return optional_; }
            bool getFlagOnly() const { return flag_only_; }
            optioncb_t getCallback() const { return callback_; }
            void* getData() const { return data_; }

        private:
            T name_;
            bool optional_ = true;
            bool flag_only_ = true;
            optioncb_t callback_ = nullptr;
            void* data_ = nullptr;
    };

    template<typename T>
    class Arguments
    {
        public:
            Arguments<T>() = default;
            virtual ~Arguments<T>() = default;

            bool set(const T& flag, const T& value)
            {
                try
                {
                    args_.insert(std::make_pair(flag, value));
                }
                catch (std::bad_alloc&)
                {
                    return false;
                }
                return true;
            }

            bool get(const T& flag, std::vector<T>& values)
            {
                bool found = false;
                typename std::pair <typename std::multimap<T, T>::iterator, typename std::multimap<T, T>::iterator> ret;
                ret = args_.equal_range(flag);

                for (typename std::multimap<T, T>::iterator it = ret.first; it != ret.second; ++it)
                {
                    found = true;
                    values.push_back(it->second);
                }
              
                return found;
            }

            bool has(const T& flag) const
            {
                if (args_.end() == args_.find(flag))
                    return false;
                return true;
            }

            void clear() { args_.clear(); }

        private:
            std::multimap<T, T> args_;
    };

    class CLI_EXPORT ArgVee
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


