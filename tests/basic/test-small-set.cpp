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

#include <geode/basic/logger.hpp>
#include <geode/basic/small_set.hpp>

#include <geode/tests/common.hpp>

void test()
{
    geode::OpenGeodeBasicLibrary::initialize();
    geode::Logger::set_level( geode::Logger::LEVEL::debug );
    geode::SmallSet< double > set;
    OPENGEODE_EXCEPTION( set.empty(), "[Test] Set should be empty" );
    OPENGEODE_EXCEPTION( set.insert( 0 ), "[Test] Insert should be done" );
    OPENGEODE_EXCEPTION( set.insert( 1 ), "[Test] Insert should be done" );
    OPENGEODE_EXCEPTION( !set.insert( 0 ), "[Test] Insert not allow" );
    OPENGEODE_EXCEPTION( !set.insert( 1 ), "[Test] Insert not allow" );
    OPENGEODE_EXCEPTION( set.size(), "[Test] Set size should be 2" );
    set.erase( 0 );
    OPENGEODE_EXCEPTION( set.size(), "[Test] Set size should be 1" );
    OPENGEODE_EXCEPTION( set.at( 0 ) == 1, "[Test] Wrong value in set" );
    geode::SmallSet< double > set2;
    set2.insert( 0 );
    OPENGEODE_EXCEPTION( set2 != set, "[Test] Wrong first comparison of sets" );
    set2.insert( 2 );
    OPENGEODE_EXCEPTION(
        set2 != set, "[Test] Wrong second comparison of sets" );
    geode::SmallSet< double > set3;
    set3.insert( 2 );
    set3.insert( 0 );
    OPENGEODE_EXCEPTION(
        set2 == set3, "[Test] Wrong third comparison of sets" );
}

OPENGEODE_TEST( "small-set" )
