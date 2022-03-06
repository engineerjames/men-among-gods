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
class items : public drogon::HttpController< items >
{
public:
  METHOD_LIST_BEGIN
  METHOD_ADD( items::getItemTemplates, "/{1}", drogon::Get );
  METHOD_LIST_END

  // your declaration of processing function maybe like this:
  void getItemTemplates( const drogon::HttpRequestPtr& req, std::function< void( const drogon::HttpResponsePtr& ) >&& callback,
                         int id ) const;

  items();

private:
  std::vector< std::unique_ptr< item > > itemTemplates_;
};
} // namespace v1
} // namespace api

#endif