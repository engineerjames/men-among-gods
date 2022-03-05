#include <drogon/drogon.h>

int main()
{
  // clang-format off
  drogon::app().setLogPath( "./" )
               .setLogLevel( trantor::Logger::kWarn )
               .addListener( "0.0.0.0", 5556 )
               .setThreadNum( 1 )
               //.enableRunAsDaemon() Can't do this in Windows...
               .run();
  // clang-format on
}