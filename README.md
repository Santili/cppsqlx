##cppsqlx
---
C++ SQL library Extension

Makes SQL into C++ 
* Easier to intagrate
* Less prone to error than string based SQL 
* More readable than string concatenated SQL
* Database syntax independent
* It's funny...



##Requirements
* C++11
* unixODBC
* log4cpp

##Supported databases
* Netezza
* Greenplum
* Vertica
* Postgresql
* Oracle
* Drill
* Monetdb

##How to buid?
```bash
make && make install

```


##Example
```c++
   /*Create Datasets to work with */
   auto TMS = GET_DATASET("V_STORAGE",con);

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

```




