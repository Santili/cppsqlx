/*
 * Copyright (c) 2014-2016, Santili Y-HRAH KRONG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __HELPERFUNCTIONS_HPP__
#define __HELPERFUNCTIONS_HPP__
#include <cppsqlxincludes.hpp>
#include <iomanip>
#include <limits>

namespace cppsqlx
{

std::string truncate(std::string str, size_t width, bool show_ellipsis=true);
std::string time_point_to_string(std::chrono::system_clock::time_point &tp);
std::string time_to_string(std::chrono::system_clock::time_point &tp);
std::string date_to_string(std::chrono::system_clock::time_point &tp);

template<typename FloatingPointType>
std::string float_to_string(FloatingPointType value)
{
  std::stringstream ss;
  ss << std::setprecision(std::numeric_limits<FloatingPointType>::digits10+1);
  ss << value;
  return ss.str();
};

};/*namespace cppsqlx*/

#endif //__HELPERFUNCTIONS_HPP__
