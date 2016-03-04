#include <cppsqlx.hpp>

using namespace cppsqlx;

int main()
{
   LOG_INFO("BEGIN_TEST");
   /*Create connection to database */
   auto con = Database().
             dbms("Oracle").
             host("hostname").
             port(1521).
             name("DSID").
             schema("uschema").
             connect("scott","tiger");

  LOG_DEBUG(std::string(__FILE__) + " " + std::to_string(__LINE__));

  try
  {
     auto oscv = GET_DATASET("OPB_SESS_CNX_VALS",con);
     auto opb  = GET_DATASET("OPB_SWIDGET_INST",con);
     auto ots  = GET_DATASET("OPB_TASK",con);
     auto trg  = GET_DATASET("OPB_TARG",con);
     auto src  = GET_DATASET("OPB_SRC",con);
     
     LOG_DEBUG(std::string(__FILE__) + " " + std::to_string(__LINE__));
  }
  catch(SQLException& e)
  {
     LOG_ERROR( e.what());
  }

  return 0;
}
