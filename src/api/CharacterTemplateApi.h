#ifndef MEN_AMONG_GODS_ITEM_TEMPLATE_API
#define MEN_AMONG_GODS_ITEM_TEMPLATE_API

#include <drogon/HttpController.h>
#include <memory>
#include <tuple>
#include <vector>

#include "apiTypes.h"

namespace api
{
namespace v1
{
class characters : public drogon::HttpController< characters >
{
public:
  METHOD_LIST_BEGIN
  METHOD_ADD( characters::getCharacterTemplates, "/{1}", drogon::Get );
  METHOD_ADD( characters::getCharacterTemplatesByName, "/name/{1}", drogon::Get );
  METHOD_ADD( characters::copyExistingTemplateById, "/{1}/copy", drogon::Post );
  METHOD_LIST_END

  void getCharacterTemplates( const drogon::HttpRequestPtr& req, std::function< void( const drogon::HttpResponsePtr& ) >&& callback,
                              int id );
  void getCharacterTemplatesByName( const drogon::HttpRequestPtr& req, std::function< void( const drogon::HttpResponsePtr& ) >&& callback,
                                    const std::string& name );
  void copyExistingTemplateById( const drogon::HttpRequestPtr& req, std::function< void( const drogon::HttpResponsePtr& ) >&& callback,
                                 int id );
  characters();

private:
  std::vector< std::unique_ptr< character > >                                     characterTemplates_;
  std::unordered_map< std::string, std::vector< std::tuple< int, character* > > > characterMap_;
};
} // namespace v1
} // namespace api

#endif