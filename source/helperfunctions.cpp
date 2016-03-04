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
#include <helperfunctions.hpp>
#include <cstring>

namespace cppsqlx
{

std::string time_point_to_string(std::chrono::system_clock::time_point &tp)
{
   using namespace std;
   using namespace std::chrono;
   auto ttime_t = system_clock::to_time_t(tp);
   auto tp_sec = system_clock::from_time_t(ttime_t);
   milliseconds ms = duration_cast<milliseconds>(tp - tp_sec);
   std::tm * ttm = localtime(&ttime_t);
   char date_time_format[] = "%Y-%m-%d %H:%M:%S";
   char time_str[] = "yyyy.mm.dd.HH:MM:SS.fff";
   strftime(time_str, strlen(time_str), date_time_format, ttm);
   std::string result(time_str);
   result.append(".");
   result.append(to_string(ms.count()));
   return result;
}

std::string truncate(std::string str, size_t width, bool show_ellipsis)
{
    if (str.length() > width)
    {
        if (show_ellipsis)
        {
            return str.substr(0, width - 3) + "...";
        }
        else
        {
            str.substr(0, str.length());
            return str.substr(0, str.length());
        }
    }
    return str;
}


std::string time_to_string(std::chrono::system_clock::time_point &tp)
{
   using namespace std;
   using namespace std::chrono;
   auto ttime_t = system_clock::to_time_t(tp);
   auto tp_sec = system_clock::from_time_t(ttime_t);
   milliseconds ms = duration_cast<milliseconds>(tp - tp_sec);
   std::tm * ttm = localtime(&ttime_t);
   char date_time_format[] = "%H:%M:%S";
   char time_str[] = "HH:MM:SS.fff";
   strftime(time_str, strlen(time_str), date_time_format, ttm);
   std::string result(time_str);
   result.append(".");
   result.append(to_string(ms.count()));
   return result;
}


std::string date_to_string(std::chrono::system_clock::time_point &tp)
{
   using namespace std;
   using namespace std::chrono;
   auto ttime_t = system_clock::to_time_t(tp);
   auto tp_sec = system_clock::from_time_t(ttime_t);
   milliseconds ms = duration_cast<milliseconds>(tp - tp_sec);
   std::tm * ttm = localtime(&ttime_t);
   char date_time_format[] = "%Y-%m-%d";
   char time_str[] = "yyyy.mm.dd.HH";
   strftime(time_str, strlen(time_str), date_time_format, ttm);
   std::string result(time_str);
   return result;
}


};/*namespace cppsqlx*/
