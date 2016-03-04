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

#ifndef __SQLEXPRESSION_HPP__
#define __SQLEXPRESSION_HPP__
#include <cppsqlxincludes.hpp>
#include <sqltypes.hpp>

namespace cppsqlx
{

class SQLExpression
{
  public:
  SQLExpression();
  SQLExpression(std::string expression);
  SQLExpression(int intvalue);
  SQLExpression(std::string columnname,std::string tablealias,bool doublequoted = true);
  virtual ~SQLExpression();

  private:
  std::string     expression_;
  std::string     alias_;

  public:
  std::string    alias();
  SQLExpression& operator+(const SQLExpression& sqexp);
  SQLExpression& operator+(const int& intexp);
  SQLExpression& operator+(const float& fexp);
  SQLExpression& operator+(const long double& fexp);
  SQLExpression& operator-(const SQLExpression& sqexp);
  SQLExpression& operator-(const int& intexp);
  SQLExpression& operator-(const float& fexp);
  SQLExpression& operator-(const long double& fexp);
  SQLExpression& operator*(const SQLExpression& sqexp);
  SQLExpression& operator*(const int& intexp);
  SQLExpression& operator*(const float& fexp);
  SQLExpression& operator*(const long double& fexp);
  SQLExpression& operator/(const SQLExpression& sqexp);
  SQLExpression& operator/(const int& sqexp);
  SQLExpression& operator/(const float& fexp);
  SQLExpression& operator/(const long double& fexp);
  bool           operator!=(const SQLExpression& sqexp);
  SQLExpression& as(const std::string& s){ alias_ = s;return *this;}
  SQLExpression& cast(SQL::TYPE sqltype);
  SQLExpression& cast(SQL::TYPE sqltype,int precision);
  SQLExpression& cast(SQL::TYPE sqltype,int precision,int scale);
  SQLExpression& avg();
  SQLExpression& sum();
  SQLExpression& count();
  SQLExpression& max();
  SQLExpression& min();
  SQLExpression& upper();
  SQLExpression& lower();
  SQLExpression& nvl(int nullvalue);

  SQLExpression& round();
  SQLExpression& power(int p);
  SQLExpression& coalesce(std::string str);
  SQLExpression& descending();
  SQLExpression& ascending();
  SQLExpression& like(const std::string& s);
  SQLExpression& opAND(const SQLExpression& sqexp);
  SQLExpression& opAND(const std::string& sqexp);
  SQLExpression& opOR(const SQLExpression& sqexp);
  SQLExpression& opOR(const std::string& sqexp);
  SQLExpression& notLike(const std::string& s);

  SQLExpression& equal(const SQLExpression& sqexp);
  SQLExpression& notEqual(const SQLExpression& sqexp);
  SQLExpression& less(const SQLExpression& sqexp);
  SQLExpression& notLess(const SQLExpression& sqexp);
  SQLExpression& greater(const SQLExpression& sqexp);
  SQLExpression& notGreater(const SQLExpression& sqexp);
  SQLExpression& lessOrEqual(const SQLExpression& sqexp);
  SQLExpression& greaterOrEqual(const SQLExpression& sqexp);

  static std::string now();
  std::string toString();
  std::string expression();

};/*SQLExpression*/

};/*namespace cppsqlx*/

#endif //__SQLEXPRESSION_HPP__
