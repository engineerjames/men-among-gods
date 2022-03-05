#include "ItemTemplateApi.h"

#include <fstream>
#include <iostream>
#include <ostream>

namespace api
{
namespace v1
{

const constexpr int MAX_TITEMS = 4548;

items::items()
    : itemTemplates_()
{
  std::cerr << "Attempting to load item templates..." << std::endl;

  std::ifstream datFile { "./titem.dat", std::ios::binary | std::ios::in };

  for ( int i = 0; i < MAX_TITEMS; ++i )
  {
    auto newItem = std::make_unique< item >();

    datFile.read( reinterpret_cast< char* >( newItem.get() ), sizeof( item ) );
    std::cerr << "Reading item: " << newItem->name << std::endl;
    itemTemplates_.push_back( std::move( newItem ) );
  }

  std::cerr << "Done." << std::endl;
}

void items::getItemTemplates( const drogon::HttpRequestPtr&                             req,
                                        std::function< void( const drogon::HttpResponsePtr& ) >&& callback, int id ) const
{
  ( void ) req;

  if ( id >= 0 && id < MAX_TITEMS && itemTemplates_[ id ] != nullptr )
  {
    Json::Value jsonResponse = itemTemplates_[ id ]->toJson();
    auto        response     = drogon::HttpResponse::newHttpJsonResponse( jsonResponse );
    response->setStatusCode( drogon::HttpStatusCode::k200OK );
    callback( response );
  }
  else
  {
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode( drogon::HttpStatusCode::k404NotFound );
    callback( response );
  }
}

} // namespace v1
} // namespace api