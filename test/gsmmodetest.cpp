#include <gtest/gtest.h>
#include <atcommandscheduler.h>
#include <atcommandbase.h>
#include <iostream>

class TestGsmSender
{
    const std::vector<std::string> response = {
        "+GSMBUSY: 1",
        "OK"
    };

    uint8_t m_current;

public:
    TestGsmSender() : m_current(0) {}

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

class AtGsmCommand : public AtCommandBase
{
public:
  uint16_t timeout() const override { return 2; }
  std::string command() override { return "AT+GSMBUSY?"; }
  std::string commandComplete() override { return "OK"; }

  bool processResponses(const std::vector<std::string>& responses) override
  {
    if (not responses.empty()) {
      auto message = responses.front();
      std::cout << "Message: " << message << std::endl;

      if (message.rfind("+GSMBUSY", 0) == 0) {
        int mode =
            std::stoi(message.substr(message.find(" ") + 1, message.size()));

        std::cout << "Mode: " << mode << std::endl;

        return mode == 1;
      }
    }

    return false;
  }
};

TEST(attestsource, gsmtest)
{
    AtGsmCommand command;
    bool result = AtCommandScheduler<TestGsmSender>::instance()->process(&command);

    ASSERT_TRUE(result);
}
