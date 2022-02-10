#include <json/json.h>

#include <iostream>

int main()
{
  Json::Value root {};
  root[ "msg" ] = "Hello World!";

  std::cerr << root.toStyledString() << std::endl;
  return 0;
}