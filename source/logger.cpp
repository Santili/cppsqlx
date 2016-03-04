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
#include <logger.hpp>

namespace cppsqlx
{


Logger::Logger()
{
   log4cpp::PatternLayout *layout = new log4cpp::PatternLayout();
   layout->setConversionPattern("%t %d: [%p] %m %n");
   appender_ = new log4cpp::OstreamAppender("console", &std::cout);
   appender_->setLayout(layout);
   
#ifndef NDEBUG
   log4cpp::Category::getRoot().setPriority(log4cpp::Priority::DEBUG);
#else
   log4cpp::Category::getRoot().setPriority(log4cpp::Priority::INFO);
#endif
   log4cpp::Category::getRoot().addAppender(appender_);

   log4cpp::Category::getRoot() << log4cpp::Priority::DEBUG << "Logger::Logger()";
}

Logger::~Logger()
{
   log4cpp::Category::getRoot() << log4cpp::Priority::DEBUG << "Logger::~Logger()";
}

std::shared_ptr<Logger>  Logger::getInstance()
{
   if(loggerinstance_ == nullptr)
   {
     loggerinstance_ = std::shared_ptr<Logger>(new Logger());
   }
   return  loggerinstance_;
}

log4cpp::Category& Logger::logger()
{
   return log4cpp::Category::getRoot();
}

void Logger::log(std::string message,log4cpp::Priority::PriorityLevel level)
{
   log4cpp::Category::getRoot() << level << message.c_str();
}



}/*namespace cppsqlx*/
