#ifndef MEN_AMONG_GODS_ACCOUNT_TEMPLATE_API
#define MEN_AMONG_GODS_ACCOUNT_TEMPLATE_API

#include <drogon/HttpController.h>
#include <memory>
#include <vector>

namespace api
{
namespace v1
{
class account : public drogon::HttpController< account >
{
public:
  METHOD_LIST_BEGIN
  METHOD_ADD( account::addAccount, "/", drogon::Put );
  METHOD_LIST_END

  // your declaration of processing function maybe like this:
  void addAccount( const drogon::HttpRequestPtr& req, std::function< void( const drogon::HttpResponsePtr& ) >&& callback ) const;

  account();

private:
};
} // namespace v1
} // namespace api

#endif