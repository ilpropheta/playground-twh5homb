#ifndef MICROURL_GUARD
#define MICROURL_GUARD

#include <string>
#include <map>

struct MicroUrl
{
  std::string Original;
  std::string Short;
  int Clicks;
};

class MicroUrl
{
public:
  std::string Shorten(const char* url);
  std::string Visit(const char* url); 
private:
  std::map<long, MicroUrl> m_db;
};

#endif
