#include "CharacterTemplateApi.h"

#include <fstream>
#include <iostream>
#include <ostream>

namespace api
{
namespace v1
{

const constexpr int MAX_TCHARS = 4548;

characters::characters()
    : characterTemplates_()
    , characterMap_()
{
  std::cerr << "Attempting to load character templates..." << std::endl;

  std::ifstream datFile { "./tchar.dat", std::ios::binary | std::ios::in };

  for ( int i = 0; i < MAX_TCHARS; ++i )
  {
    auto newCharacter = std::make_unique< character >();

    datFile.read( reinterpret_cast< char* >( newCharacter.get() ), sizeof( character ) );

    characterMap_[ newCharacter->name ].push_back( newCharacter.get() );

    characterTemplates_.push_back( std::move( newCharacter ) );
  }

  std::cerr << "Done." << std::endl;
}

void characters::getCharacterTemplates( const drogon::HttpRequestPtr&                             req,
                                        std::function< void( const drogon::HttpResponsePtr& ) >&& callback, int id )
{
  ( void ) req;

  if ( id >= 0 && id < MAX_TCHARS && characterTemplates_[ id ] != nullptr )
  {
    Json::Value jsonResponse = characterTemplates_[ id ]->toJson();
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

void characters::getCharacterTemplatesByName( const drogon::HttpRequestPtr&                             req,
                                              std::function< void( const drogon::HttpResponsePtr& ) >&& callback, const std::string& name )
{
  ( void ) req;

  if ( ! name.empty() && characterMap_.count( name ) != 0 )
  {
    Json::Value jsonResponse = Json::arrayValue;

    for ( auto&& [ n, characterlist ] : characterMap_ )
    {
      if ( n.find( name ) != std::string::npos )
      {
        for ( auto&& c : characterlist )
        {
          jsonResponse.append( c->toJson() );
        }
      }
    }

    auto response = drogon::HttpResponse::newHttpJsonResponse( jsonResponse );
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