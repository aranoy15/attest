#include <gtest/gtest.h>
#include <atcommandscheduler.h>
#include <atcommandbase.h>
#include <iostream>

class TimeoutSender
{
public:
    TimeoutSender() {}

    void write(std::string) {}

    std::string readLine() { return ""; }
};

class AtGsvCommand : public AtCommandBase
{
public:
  uint16_t timeout() const override { return 2; }
  std::string command() override { return ""; }
  std::string commandComplete() override { return ""; }

  bool processResponses(const std::vector<std::string>& responses) override
  {
     return true;
  }
};

TEST(attestsource, timeouttest)
{
    AtGsvCommand command;
    bool result = AtCommandScheduler<TimeoutSender>::instance()->process(&command);

    ASSERT_FALSE(result);
}
