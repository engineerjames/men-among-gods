#include "CharacterTemplateApi.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <ostream>

namespace api
{
namespace v1
{

const constexpr int MAX_TCHARS = 4548;

characters::characters()
{
}

void characters::loadTemplateFile( CharacterTemplates& templates, CharacterMap& map ) const
{
  std::ifstream datFile { "./.dat/tchar.dat", std::ios::binary | std::ios::in };

  for ( int i = 0; i < MAX_TCHARS; ++i )
  {
    auto newCharacter = std::make_unique< character >();

    datFile.read( reinterpret_cast< char* >( newCharacter.get() ), sizeof( character ) );

    map[ newCharacter->name ].emplace_back( i, newCharacter.get() );

    templates.push_back( std::move( newCharacter ) );
  }

  datFile.close();
}

void characters::saveTemplateFile( const CharacterTemplates& templates ) const
{
  std::ofstream datFile { "./.dat/tchar.dat", std::ios::binary | std::ios::out };

  for ( int i = 0; i < MAX_TCHARS; ++i )
  {
    datFile.write( reinterpret_cast< const char* >( templates[ i ].get() ), sizeof( character ) );
  }

  datFile.close();
}

void characters::getCharacterTemplates( const drogon::HttpRequestPtr&                             req,
                                        std::function< void( const drogon::HttpResponsePtr& ) >&& callback, int id )
{
  ( void ) req;

  CharacterTemplates templates {};
  CharacterMap       map {};

  loadTemplateFile( templates, map );

  if ( id >= 0 && id < MAX_TCHARS && templates[ id ] != nullptr )
  {
    nlohmann::json jsonResponse = templates[ id ]->toJson();
    jsonResponse[ "id" ]     = id;

    auto response = drogon::HttpResponse::newHttpResponse( );
    response->setBody(jsonResponse.dump());
    response->setStatusCode( drogon::HttpStatusCode::k200OK );
    callback( response );
  }
  else
  {
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode( drogon::HttpStatusCode::k404NotFound );
    callback( response );
  }

  // No modification so therefore, no need to save!
}

void characters::getCharacterTemplatesByName( const drogon::HttpRequestPtr&                             req,
                                              std::function< void( const drogon::HttpResponsePtr& ) >&& callback, const std::string& name )
{
  ( void ) req;

  CharacterTemplates templates {};
  CharacterMap       map {};

  loadTemplateFile( templates, map );

  if ( ! name.empty() && map.count( name ) != 0 )
  {
    nlohmann::json jsonResponse{};

    std::vector<nlohmann::json> arrayMembers{};

    for ( auto&& [ n, characterlist ] : map )
    {
      if ( n.find( name ) != std::string::npos )
      {
        for ( auto&& [ cid, charptr ] : characterlist )
        {
          nlohmann::json root = charptr->toJson();
          root[ "id" ]     = cid;

          arrayMembers.push_back( root );
        }
      }
    }

    jsonResponse = arrayMembers;

    auto response = drogon::HttpResponse::newHttpResponse( );
    response->setBody(jsonResponse.dump());
    callback( response );
  }
  else
  {
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode( drogon::HttpStatusCode::k404NotFound );
    callback( response );
  }

  // No modification so therefore, no need to save!
}

void characters::copyExistingTemplateById( const drogon::HttpRequestPtr&                             req,
                                           std::function< void( const drogon::HttpResponsePtr& ) >&& callback, int id )
{
  ( void ) req;

  CharacterTemplates templates {};
  CharacterMap       map {};

  loadTemplateFile( templates, map );

  std::cerr << "Looking for space to copy id: " << id << " into." << std::endl;

  int newId = 0;
  for ( int i = 0; i < MAX_TCHARS; ++i )
  {
    if ( templates[ id ] && templates[ i ] && ! templates[ i ]->used && i > id )
    {
      *templates[ i ] = *templates[ id ];
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

  nlohmann::json root {};
  root[ "id" ] = newId;
  auto response = drogon::HttpResponse::newHttpResponse( );
  response->setBody(root.dump());
  callback( response );

  saveTemplateFile( templates );
}

void characters::updateExistingTemplateById( const drogon::HttpRequestPtr&                             req,
                                             std::function< void( const drogon::HttpResponsePtr& ) >&& callback, int id )
{

  CharacterTemplates templates {};
  CharacterMap       map {};

  loadTemplateFile( templates, map );

  if ( id < 0 || id >= MAX_TCHARS || templates[ id ] == nullptr )
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

  std::cerr << "Received: " << ( req->getJsonObject() )->toStyledString();

  auto      jsonBody                 = req->getJsonObject()->toStyledString();
  character receivedCharacterDetails = character::fromJson( nlohmann::json::parse(jsonBody) );

  *templates[ id ] = receivedCharacterDetails;

  auto resp = drogon::HttpResponse::newHttpResponse( );
  resp->setBody(jsonBody);
  resp->setStatusCode( drogon::HttpStatusCode::k200OK );
  callback( resp );

  saveTemplateFile( templates );
}

} // namespace v1
} // namespace api