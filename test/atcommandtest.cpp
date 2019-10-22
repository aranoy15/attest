#include <gtest/gtest.h>
#include <atcommandscheduler.h>
#include <atcommandbase.h>
#include <iostream>

class TestGsvSender
{
    const std::vector<std::string> response = {
        "SIMCOM_Ltd",
        "SIMCOM_SIM800H",
        "Revision: 1308B01SIM800H32",
        "OK"
    };

    uint8_t m_current;

public:
    TestGsvSender() : m_current(0) {}

    void write(std::string) {}

    std::string readLine()
    {
        if (m_current < response.size()) {
            auto& result = response[m_current];
            m_current++;
            return result;
        }

        return "";
    }
};

class AtGsvCommand : public AtCommandBase
{
public:
  uint16_t timeout() const override { return 2; }
  std::string command() override { return "AT+GSV"; }
  std::string commandComplete() override { return "OK"; }

  bool processResponses(const std::vector<std::string>& responses) override
  {
      if (responses.size() > 2) {
          auto company = responses[0];
          auto model = responses[1];

          auto revision = responses[2].substr(responses[2].find(" ") + 1, responses[2].size());

          std::cout << "Company: " << company << std::endl;
          std::cout << "Model: " << model << std::endl;
          std::cout << "Revision: " << revision << std::endl;

          if (company == "SIMCOM_Ltd" and model == "SIMCOM_SIM800H" and
              revision == "1308B01SIM800H32")
            return true;
      }

      return false;
  }
};

TEST(attestsource, atcommandtest)
{
    AtGsvCommand command;
    bool result = AtCommandScheduler<TestGsvSender>::instance()->process(&command);

    ASSERT_TRUE(result);
}
