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
#include <sqlexpression.hpp>
#include <helperfunctions.hpp>
#include <logger.hpp>

namespace cppsqlx
{

SQLExpression::SQLExpression():expression_("*")
{
}

SQLExpression::~SQLExpression()
{
}

SQLExpression::SQLExpression(std::string expression):expression_(expression)
{
}

SQLExpression::SQLExpression(int intvalue):expression_(std::to_string(intvalue))
{
}

SQLExpression::SQLExpression(std::string columnname,std::string tablealias,bool doublequoted)
{
   expression_ = doublequoted ? (tablealias + ".\"" + columnname + "\"") : (tablealias + "." + columnname);
}


SQLExpression& SQLExpression::operator+(const SQLExpression& sqexp)
{
  expression_ = std::string("(") + expression_ + std::string(" + ") + sqexp.expression_ + ")";
  return *this;
}

SQLExpression& SQLExpression::operator+(const int& intexp)
{
  expression_ = std::string("(") + expression_ + std::string(" + ") + std::to_string(intexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator+(const float& fexp)
{
  expression_ = std::string("(") + expression_ + std::string(" + ") + float_to_string(fexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator+(const long double& fexp)
{
  expression_ = std::string("(") + expression_ + std::string(" + ") + float_to_string(fexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator-(const SQLExpression& sqexp)
{
  expression_ = std::string("(") + expression_ + std::string(" - ") + sqexp.expression_ + ")";
  return *this;
}

SQLExpression& SQLExpression::operator-(const int& intexp)
{
  expression_ = std::string("(") + expression_ + std::string(" - ") + std::to_string(intexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator-(const float& fexp)
{
  expression_ = std::string("(") + expression_ + std::string(" - ") + float_to_string(fexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator-(const long double& fexp)
{
  expression_ = std::string("(") + expression_ + std::string(" - ") + float_to_string(fexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator*(const SQLExpression& sqexp)
{
  expression_ = std::string("(") + expression_ + std::string(" * ") + sqexp.expression_ + ")";
  return *this;
}

SQLExpression& SQLExpression::operator*(const int& intexp)
{
  expression_ = std::string("(") + expression_ + std::string(" * ") + std::to_string(intexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator*(const float& fexp)
{
  expression_ = std::string("(") + expression_ + std::string(" * ") + float_to_string(fexp) + ")";
  return *this;
}



SQLExpression& SQLExpression::operator*(const long double& fexp)
{
  expression_ = std::string("(") + expression_ + std::string(" * ") + float_to_string(fexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator/(const SQLExpression& sqexp)
{
  expression_ = std::string("(") + expression_ + std::string(" / ") + sqexp.expression_ + ")";
  return *this;
}

SQLExpression& SQLExpression::operator/(const int& sqexp)
{
  expression_ = std::string("(") + expression_ + std::string(" / ") + std::to_string(sqexp) + ")";
  return *this;
}


SQLExpression& SQLExpression::operator/(const float& fexp)
{
  expression_ = std::string("(") + expression_ + std::string(" / ") + float_to_string(fexp) + ")";
  return *this;
}

SQLExpression& SQLExpression::operator/(const long double& fexp)
{
  expression_ = std::string("(") + expression_ + std::string(" / ") + float_to_string(fexp) + ")";
  return *this;
}


bool SQLExpression::operator!=(const SQLExpression& sqexp)
{
  return expression_ != sqexp.expression_;
}

SQLExpression& SQLExpression::cast(SQL::TYPE type)
{
  expression_ = "CAST(" + expression_ + " AS " + SQLTYPE(type) + ")";
  return *this;
}

SQLExpression& SQLExpression::cast(SQL::TYPE type,int precision)
{
  expression_ = "CAST(" + expression_ + " AS " + SQLTYPE(type) + "(" + std::to_string(precision)  + ") )";
  return *this;
}

SQLExpression& SQLExpression::cast(SQL::TYPE type,int precision,int scale)
{
  expression_ = "CAST(" + expression_ + " AS " + SQLTYPE(type) + "(" + std::to_string(precision)  + "," + std::to_string(scale) + ") )";
  return *this;
}


SQLExpression& SQLExpression::avg()
{
   expression_ = "AVG(" + expression_ + ")";
   return *this;
}


SQLExpression& SQLExpression::sum()
{
   expression_ = "SUM(" + expression_ + ")";
   return *this;
}


SQLExpression& SQLExpression::count()
{
   expression_ = "COUNT(" + expression_ + ")";
   return *this;
}


SQLExpression& SQLExpression::max()
{
   expression_ = "MAX(" + expression_ + ")";
   return *this;
}


SQLExpression& SQLExpression::min()
{
   expression_ = "MIN(" + expression_ + ")";
   return *this;
}


SQLExpression& SQLExpression::upper()
{
   expression_ = "UPPER(" + expression_ + ")";
   return *this;
}


SQLExpression& SQLExpression::lower()
{
   expression_ = "LOWER(" + expression_ + ")";
   return *this;
}


SQLExpression& SQLExpression::nvl(int nullvalue)
{
   expression_ = "nvl(" + expression_ + "," + std::to_string(nullvalue) + ")";
   return *this;
}



SQLExpression& SQLExpression::round()
{
   expression_ = "round(" + expression_ + ")";
   return *this;
}


SQLExpression& SQLExpression::power(int p)
{
   expression_ = "pow(" + expression_ + "," + std::to_string(p) + ")";
   return *this;
}


SQLExpression& SQLExpression::descending()
{
    expression_ += " DESC";
    return *this;
}


SQLExpression& SQLExpression::ascending()
{
    expression_ += " ASC";
    return *this;
}


SQLExpression& SQLExpression::coalesce(std::string str)
{
    expression_ = "COALESCE(" + expression_ + ",'" + str + "')";
    return *this;
}


SQLExpression& SQLExpression::notLike(const std::string& s)
{
    expression_ += " NOT LIKE '" +  s + "'";
    return *this;
}

SQLExpression& SQLExpression::like(const std::string& s)
{
    expression_ += " LIKE '" +  s + "'";
    return *this;
}

SQLExpression& SQLExpression::opAND(const SQLExpression& sqexp)
{
    expression_ += " AND (" + sqexp.expression_ + ")";
    return *this;
}


SQLExpression& SQLExpression::opOR(const SQLExpression& sqexp)
{
    expression_ += " OR (" + sqexp.expression_ + ")";
    return *this;
}


SQLExpression& SQLExpression::opOR(const std::string& sqexp)
{
    return opOR(SQLExpression(sqexp));
}


SQLExpression& SQLExpression::opAND(const std::string& sqexp)
{
    return opAND(SQLExpression(sqexp));
}


std::string SQLExpression::now()
{
   return std::string("NOW()");
}


std::string SQLExpression::toString()
{
  if( alias_ == "")
  return expression_;
  else
  return expression_ + " AS " + alias_;
}

std::string SQLExpression::expression()
{
   return expression_;
}


SQLExpression& SQLExpression::equal(const SQLExpression& sqexp)
{
  expression_ += " = " + sqexp.expression_;
  return *this;
}


SQLExpression& SQLExpression::notEqual(const SQLExpression& sqexp)
{
  expression_ += " != " + sqexp.expression_;
  return *this;
}

SQLExpression& SQLExpression::less(const SQLExpression& sqexp)
{
  expression_ += " < " + sqexp.expression_;
  return *this;
}


SQLExpression& SQLExpression::notLess(const SQLExpression& sqexp)
{
  expression_ += " !< " + sqexp.expression_;
  return *this;
}


SQLExpression& SQLExpression::greater(const SQLExpression& sqexp)
{
  expression_ += " > " + sqexp.expression_;
  return *this;
}


SQLExpression& SQLExpression::notGreater(const SQLExpression& sqexp)
{
  expression_ += " !> " + sqexp.expression_;
  return *this;
}


SQLExpression& SQLExpression::lessOrEqual(const SQLExpression& sqexp)
{
  expression_ += " <= " + sqexp.expression_;
  return *this;
}


SQLExpression& SQLExpression::greaterOrEqual(const SQLExpression& sqexp)
{
  expression_ += " >= " + sqexp.expression_;
  return *this;
}


std::string SQLExpression::alias()
{
  return alias_;
}


};/*namespace cppsqlx*/
