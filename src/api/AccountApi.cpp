#include "AccountApi.h"

#include <fstream>
#include <iostream>
#include <ostream>

#include "nlohmann/json.hpp"

namespace api
{
namespace v1
{

const constexpr int MAX_TITEMS = 4548;

account::account()
{
}

void account::addAccount( const drogon::HttpRequestPtr& req, std::function< void( const drogon::HttpResponsePtr& ) >&& callback ) const
{
  ( void ) req;
  ( void ) callback;

  if ( req && req->getJsonObject() && req->getJsonError().empty() )
  {
    // Good JSON body -- convert from jsoncpp to nlohmann json
    nlohmann::json root = nlohmann::json::parse( req->getJsonObject()->toStyledString() );

    // We want, e-mail, password hash, and that's it?
  }
}

} // namespace v1
} // namespace api