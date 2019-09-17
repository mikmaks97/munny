#include <iostream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

int STEP = 6;

int main() {
  auto r = cpr::Get(cpr::Url{"https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=MSFT&apikey=OOU2E54XUQ0W6OLK&outputsize=full"},
                    cpr::VerifySsl{false});
  std::cout << r.status_code << std::endl;
  auto j = json::parse(r.text);

  // convert dict of dates to list
  std::vector<double> closes;
  for (const auto& v: j["Time Series (Daily)"]) {
    closes.push_back(std::stod(std::string(v["5. adjusted close"])));
  }

  std::vector<double> fiveday;

  // do first five
  fiveday.push_back(closes[0] + closes[1] + closes[2] + closes[3] + closes[4]);

  // do rest
  for (size_t i = STEP; i < closes.size(); i++) {
    fiveday.push_back(fiveday[i-STEP]-closes[i-STEP] + closes[i]);
  }

  for (auto& v: fiveday) {
    v /= STEP;
  }

  bool holding = false;
  double bought_for = 0;
  double overall = 0;
  for (size_t i = STEP; i < closes.size(); i++) {
    double day_price = closes[i];
    if (day_price > fiveday[i-STEP] && !holding) {
      holding = true;
      bought_for = closes[i];
      std::cout << "bought:" << closes[i] << " > " << fiveday[i-STEP] <<  std::endl;
    }
    else if (day_price < fiveday[i-STEP] && holding) {
      holding = false;
      std::cout << "sold:" << closes[i] << " < " << fiveday[i-STEP] <<  std::endl;
      std::cout << "PROFIT " << closes[i] - bought_for << std::endl;
      overall += closes[i] - bought_for;
    }
  }
  std::cout << std::endl;
  std::cout << "Overall performance: " << overall << std::endl;

  return 0;
}
