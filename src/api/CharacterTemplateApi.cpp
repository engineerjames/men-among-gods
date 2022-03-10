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

    characterMap_[ newCharacter->name ].emplace_back( i, newCharacter.get() );

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
    jsonResponse[ "id" ]     = id;

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
        for ( auto&& [ cid, charptr ] : characterlist )
        {
          Json::Value root = charptr->toJson();
          root[ "id" ]     = cid;

          jsonResponse.append( root );
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

void characters::copyExistingTemplateById( const drogon::HttpRequestPtr&                             req,
                                           std::function< void( const drogon::HttpResponsePtr& ) >&& callback, int id )
{
  ( void ) req;

  std::cerr << "Looking for space to copy id: " << id << " into." << std::endl;

  int newId = 0;
  for ( int i = 0; i < MAX_TCHARS; ++i )
  {
    if ( characterTemplates_[ id ] && characterTemplates_[ i ] && ! characterTemplates_[ i ]->used && i > id )
    {
      *characterTemplates_[ i ] = *characterTemplates_[ id ];
      std::cerr << "Copied into id: " << i << std::endl;
      newId = i;
      break;
    }
  }

  if ( newId == 0 )
  {
    auto resp = drogon::HttpResponse::newHttpJsonResponse( {} );
    resp->setStatusCode( drogon::HttpStatusCode::k404NotFound );
    callback( resp );
    return;
  }

  Json::Value root {};
  root[ "id" ] = newId;
  auto resp    = drogon::HttpResponse::newHttpJsonResponse( root );
  resp->setStatusCode( drogon::HttpStatusCode::k200OK );
  callback( resp );
}

void characters::updateExistingTemplateById( const drogon::HttpRequestPtr&                             req,
                                             std::function< void( const drogon::HttpResponsePtr& ) >&& callback, int id )
{
  if ( id < 0 || id >= MAX_TCHARS || characterTemplates_[ id ] == nullptr )
  {
    auto resp = drogon::HttpResponse::newHttpJsonResponse( {} );
    resp->setStatusCode( drogon::HttpStatusCode::k400BadRequest );
    callback( resp );
  }

  if ( ! req->getJsonError().empty() )
  {
    std::cerr << req->getJsonError() << std::endl;
    return;
  }

  auto      jsonBody                 = req->getJsonObject();
  character receivedCharacterDetails = character::fromJson( *jsonBody );

  *characterTemplates_[ id ] = receivedCharacterDetails;

  auto resp = drogon::HttpResponse::newHttpJsonResponse( *jsonBody );
  resp->setStatusCode( drogon::HttpStatusCode::k200OK );
  callback( resp );
}

} // namespace v1
} // namespace api