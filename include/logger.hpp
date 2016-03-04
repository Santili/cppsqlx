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
#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#include <cppsqlxincludes.hpp>

namespace cppsqlx
{

/*
 * Logger
 * Singleton used for logging
 **/
class Logger
{
   public:
   Logger();
   ~Logger();

   private:
   log4cpp::Appender*  appender_;

   public:
   static std::shared_ptr<Logger>  loggerinstance_;
   static std::shared_ptr<Logger>  getInstance();
   log4cpp::Category& logger();
   void log(std::string message,log4cpp::Priority::PriorityLevel level = log4cpp::Priority::INFO);
};

#define LOG(X) Logger::getInstance()->log(X)
#define LOG_INFO(X) Logger::getInstance()->log(X,log4cpp::Priority::INFO)
#define LOG_ERROR(X) Logger::getInstance()->log(X,log4cpp::Priority::ERROR)
#define LOG_WARN(X) Logger::getInstance()->log(X,log4cpp::Priority::WARN)
#define LOG_NOTICE(X) Logger::getInstance()->log(X,log4cpp::Priority::NOTICE)
#define LOG_DEBUG(X) Logger::getInstance()->log(X,log4cpp::Priority::DEBUG)

};/*namespace cppsqlx*/
#endif//__LOGGER_HPP__
