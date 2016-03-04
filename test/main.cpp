/*
 * SYH : 2016-02-24
 **/
#include <cppsqlx.hpp>
using namespace cppsqlx;

int main()
{
   LOG_INFO("BEGIN_TEST");
   /*Create connection to database */
   auto con = Database().
             dbms("Netezza").
             host("hostname").
             port(5480).
             name("db_name").
             connect("username","password");

   /*Create Datasets to work with */
   auto TMS = GET_DATASET("V_STORAGE",con);
   TMS.setSchema("ADMIN");

   /* Issue a query */
   auto res =
   SELECT
   (
      "SAMPLE_TIME"_sql AS("STIME"),
      "TOTAL"_sql       AS("TOT"),
      "DOM1"_sql        AS("D1"),
      "DOM2"_sql        AS("D2"),
      "DOM3"_sql        AS("D3"),   
      "DOM4"_sql        AS("D4")
   )
   FROM( TMS  AS("V_S"))
   ORDERBY
   ( 
      "SAMPLE_TIME"_sql ASC, 
      "TOTAL"_sql       DESC, 
      "DOM1"_sql        DESC
   )
   LIMIT(10)
   DIALECT(DBPROVIDER::NETEZZA)
   EXEC(con);

   /* Output result */
   std::wcout << res;
  
   LOG_INFO("END_TEST");
   return EXIT_SUCCESS;
}

