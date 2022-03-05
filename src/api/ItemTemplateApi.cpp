#include "ItemTemplateApi.h"

#include <fstream>
#include <iostream>
#include <ostream>

namespace api
{
namespace v1
{

ItemTemplateApi::ItemTemplateApi()
    : itemTemplates_()
{
  std::cerr << "Attempting to load item templates..." << std::endl;

  std::ifstream datFile { "./titem.dat", std::ios::binary | std::ios::in };

  for ( int i = 0; i < 4548; ++i )
  {
    item newItem {};
    datFile.read( reinterpret_cast< char* >( &newItem ), sizeof( item ) );
    std::cerr << "Reading item: " << newItem.name << std::endl;
    itemTemplates_.push_back( newItem );
  }

  std::cerr << "Done." << std::endl;
}

void ItemTemplateApi::getItemTemplates( const drogon::HttpRequestPtr&                             req,
                                        std::function< void( const drogon::HttpResponsePtr& ) >&& callback ) const
{
  ( void ) req;

  auto response = drogon::HttpResponse::newHttpResponse();
  response->setStatusCode( drogon::HttpStatusCode::k200OK );
  callback( response );

  std::cerr << "GET DEM ITEMS!" << std::endl;
}
} // namespace v1
} // namespace api