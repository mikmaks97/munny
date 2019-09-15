#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
using json = nlohmann::json;

int main() {
  // JSON!
  json j2 = R"(
    {
      "happy": true,
      "pi": 3.141
    }
  )"_json;
  std::cout << j2.dump(4) << std::endl;

  // GET request!
  auto r = cpr::Get(cpr::Url{"https://api.github.com/repos/mikmaks97/munny/contributors"});
  std::cout << r.status_code << std::endl;
  std::cout << r.text << std::endl;

  return 0;
}
