#ifndef MEN_AMONG_GODS_ITEM_TEMPLATE_API
#define MEN_AMONG_GODS_ITEM_TEMPLATE_API

#include <drogon/HttpController.h>
#include <memory>
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
  METHOD_LIST_END

  // your declaration of processing function maybe like this:
  void getCharacterTemplates( const drogon::HttpRequestPtr& req, std::function< void( const drogon::HttpResponsePtr& ) >&& callback,
                         int id ) const;

  characters();

private:
  std::vector< std::unique_ptr< character > > characterTemplates_;
};
} // namespace v1
} // namespace api

#endif