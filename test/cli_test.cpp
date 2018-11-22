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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "argv.h"

class CliTest : public ::testing::Test
{
protected:
    CliTest() { }

    virtual ~CliTest() { }

    virtual void SetUp() 
    { 
        value_.clear(); 
        counter_ = 0; 
        errors_.clear(); 
    }

    virtual void TearDown() { }

    std::vector<std::string> errors_;

public:
    std::string value_;
    int counter_ = 0;
};

TEST_F(CliTest, Instance)
{
    ASSERT_NO_THROW(qwikpirate::ArgVee a);
}

TEST_F(CliTest, Options_X)
{
    const char* argv[1] = { "theapp.exe" };
    int argc = 1;
    qwikpirate::ArgVee a;
    std::vector<std::string> errors;

    bool success = a.parse(argc, argv, errors_);
    ASSERT_TRUE(success);
}

TEST_F(CliTest, Options_FFF)
{
    const char* argv[4] = { "theapp.exe", "--one", "--two", "--three" };
    int argc = 4;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, true);
    a.setOption("--two", true, true);
    a.setOption("--three", true, true);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_TRUE(success);
}

TEST_F(CliTest, Options_F2XF)
{
    const char* argv[4] = { "theapp.exe", "--one", "--onr", "--three" };
    int argc = 4;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, true);
    a.setOption("--two", true, true);
    a.setOption("--three", true, true);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_TRUE(success);
}

TEST_F(CliTest, Options_FVOF)
{
    const char* argv[4] = { "theapp.exe", "--one", "one", "--three" };
    int argc = 4;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, false);
    a.setOption("--two", true, true);
    a.setOption("--three", true, true);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_TRUE(success);
}

void Options_FVXF_Callback_cb(const std::string& flag, const std::string& value, void* param)
{
    if (nullptr != param)
    {
        ((CliTest*)param)->counter_++;
    }
}

TEST_F(CliTest, Options_FVXF_Callback)
{
    const char* argv[4] = { "theapp.exe", "--one", "one", "--three" };
    int argc = 4;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, false, Options_FVXF_Callback_cb, this);
    a.setOption("--two", true, true, Options_FVXF_Callback_cb, this);
    a.setOption("--three", true, true, Options_FVXF_Callback_cb, this);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_TRUE(success);

    a.apply();
    ASSERT_EQ(2, counter_);
}

void Options_FVXF_NULL_Callback_cb(const std::string& flag, const std::string& value, void* param)
{
    if (nullptr != param)
    {
        if (flag == std::string("--one"))
        {
            ((CliTest*)param)->value_ = value;
        }
    }
}

TEST_F(CliTest, Options_FVXF_NULL_Callback)
{
    const char* argv[4] = { "theapp.exe", "--one", "one_val", "--three" };
    int argc = 4;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, false, Options_FVXF_NULL_Callback_cb, this);
    a.setOption("--two", true, true, nullptr);
    a.setOption("--three", true, true, Options_FVXF_NULL_Callback_cb, this);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_TRUE(success);

    a.apply();
    ASSERT_EQ(0, value_.compare("one_val"));
}

void Options_FVXF_NULL_Callback_cb2(const std::string& flag, const std::string& value, void* param)
{
    if (nullptr != param)
    {
        if (flag == std::string("-one"))
        {
            ((CliTest*)param)->value_ = value;
        }
    }
}

TEST_F(CliTest, Options_SingleDashRegex_FVXF_NULL_Callback)
{
    const char* argv[4] = { "theapp.exe", "-one", "one_val", "-three" };
    int argc = 4;
    qwikpirate::ArgVee a("-[a-zA-Z0-9_]+$");

    a.setOption("-one", true, false, Options_FVXF_NULL_Callback_cb2, this);
    a.setOption("-two", true, true, nullptr);
    a.setOption("-three", true, true, Options_FVXF_NULL_Callback_cb2, this);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_TRUE(success);

    a.apply();
    ASSERT_EQ(0, value_.compare("one_val"));
}

////////////// Failure conditions

TEST_F(CliTest, Malformed_Flag_Fails)
{
    //                                    *malformed
    const char* argv[4] = { "theapp.exe", "-one", "one", "--three" };
    int argc = 0;
    qwikpirate::ArgVee a;

    bool success = a.setOption("--one", true, false);
    a.setOption("--two", true, true);
    a.setOption("--three", true, true);

    success = a.parse(argc, argv, errors_);
    ASSERT_FALSE(success);
}

TEST_F(CliTest, Malformed_Option_Fails)
{
    const char* argv[4] = { "theapp.exe", "--one", "one", "--three" };
    int argc = 0;
    qwikpirate::ArgVee a;

    bool success = a.setOption("-one", true, false); //malformed

    ASSERT_FALSE(success);
}

TEST_F(CliTest, Options_Zero_Argc_Fails)
{
    const char* argv[4] = { "theapp.exe", "--one", "one", "--three" };
    int argc = 0;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, false);
    a.setOption("--two", true, true);
    a.setOption("--three", true, true);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_FALSE(success);
}

TEST_F(CliTest, Options_Null_Argv_Fails)
{
    const char** argv = nullptr;
    int argc = 4;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, false);
    a.setOption("--two", true, true);
    a.setOption("--three", true, true);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_FALSE(success);
}

TEST_F(CliTest, Options_OXO_MissingFlag_Fails)
{
    const char* argv[1] = { "theapp.exe" };
    int argc = 1;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, true);
    a.setOption("--two", false, true);
    a.setOption("--three", true, true);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_FALSE(success);

    ASSERT_EQ(1, errors_.size());

    ASSERT_EQ(0, errors_.front().compare("Missing flag: --two"));
}

TEST_F(CliTest, Options_ORXO_MissingValue_Fails)
{
    const char* argv[4] = { "theapp.exe", "--one", "--two", "--three" };
    int argc = 4;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, true);
    a.setOption("--two", false, false);
    a.setOption("--three", true, true);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_FALSE(success);

    ASSERT_EQ(1, errors_.size());

    ASSERT_EQ(0, errors_.front().compare("Mismatch flag/value pair"));
}

TEST_F(CliTest, Options_FXOF_Fails)
{
    const char* argv[4] = { "theapp.exe", "--one", "--two", "--three" };
    int argc = 4;
    qwikpirate::ArgVee a;

    a.setOption("--one", true, false);
    a.setOption("--two", true, true);
    a.setOption("--three", true, true);

    bool success = a.parse(argc, argv, errors_);
    ASSERT_FALSE(success);

    ASSERT_EQ(0, errors_[0].compare("Mismatch flag/value pair"));
}



