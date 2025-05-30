/*
 * Copyright (c) 2019 - 2025 Geode-solutions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <geode/basic/assert.hpp>

#include <cassert>

#include <absl/debugging/symbolize.h>

#include <geode/basic/logger.hpp>

namespace geode
{
    std::string OpenGeodeException::stack_trace() const
    {
        std::string stack_string;
        for( auto frame = 0; frame < stack_size_; ++frame )
        {
            absl::StrAppend( &stack_string, "  ", frame, ": " );
            if( std::array< char, SYMBOL_SIZE > symbol; absl::Symbolize(
                    stack_[frame], symbol.data(), sizeof( symbol ) ) )
            {
                absl::StrAppend( &stack_string, symbol.data() );
            }
            else
            {
                absl::StrAppend( &stack_string, "Unknown" );
            }
            absl::StrAppend( &stack_string, "\n" );
        }
        return stack_string;
    }

    void geode_assertion_failed( std::string_view condition,
        std::string_view message,
        std::string_view file,
        int line )
    {
        Logger::error( "File: ", file );
        Logger::error( "Line: ", line );
        Logger::error( "Info: ", message );
        throw OpenGeodeException{ "Assertion failed: ", condition };
    }

    int geode_lippincott()
    {
        try
        {
            throw;
        }
        catch( const OpenGeodeDataException& exception )
        {
            Logger::critical( "OpenGeodeDataException: ", exception.what(),
                "\n", exception.stack_trace() );
        }
        catch( const OpenGeodeResultException& exception )
        {
            Logger::critical( "OpenGeodeResultException: ", exception.what(),
                "\n", exception.stack_trace() );
        }
        catch( const OpenGeodeException& exception )
        {
            Logger::critical( "OpenGeodeException: ", exception.what(), "\n",
                exception.stack_trace() );
        }
        catch( const std::exception& exception )
        {
            Logger::critical( "std::exception: ", exception.what() );
        }
        catch( ... )
        {
            Logger::critical( "Unknown exception" );
        }
        return 1;
    }

    void throw_lippincott()
    {
        try
        {
            throw;
        }
        catch( const OpenGeodeException& /*unused*/ )
        {
            throw;
        }
        catch( const std::exception& exception )
        {
            throw OpenGeodeException{ "std::exception, ", exception.what() };
        }
        catch( ... )
        {
            throw OpenGeodeException{ "Unknown exception" };
        }
    }
} // namespace geode
