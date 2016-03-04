# cppsqlx
C++ SQL library Extension

Make SQL integration into C++ code easy and readeable
Requires C++11 

Example  :
   auto res =
   SELECT
   (
      "SAMPLE_TIME"_sql AS("STIME"),
      "TOTAL"_sql       AS("TOT"),
      "DOM1"_sql        AS("D1")
   )
   FROM( TMS  AS("V_S"))
   ORDERBY
   (
      "SAMPLE_TIME"_sql ASC,
      "TOTAL"_sql       DESC,
      "DOM1"_sql        DESC
   )
   LIMIT(10)
   DIALECT(DBPROVIDER::NETEZZA)\n
   EXEC(con);

   std::wcout << res;
