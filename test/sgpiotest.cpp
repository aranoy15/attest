#include <gtest/gtest.h>
#include <atcommandscheduler.h>
#include <atcommandbase.h>
#include <iostream>
#include <utils.h>

class TestSgpioSender
{
    const std::vector<std::string> response = {
        "+SGPIO: 0,1,0,0",
        "+SGPIO: 1,2,1,1",
        "OK"
    };

    uint8_t m_current;

public:
    TestSgpioSender() : m_current(0) {}

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

class AtGpioCommand : public AtCommandBase
{
public:
    enum Operation
    {
        Set = 0,
        Read = 1
    };

    enum Function
    {
        Input = 0,
        Output = 1
    };

    enum Level
    {
        Low = 0,
        High = 1
    };

    struct GpioInfo
    {
		Operation operation;
		int gpio_number;
		Function function;
		Level level;

        bool parse(std::string& data) 
        {
            auto splitData = utils::split(data, ',');

            if (splitData.size() >= 4) {
				operation = static_cast<Operation>(std::stoi(splitData[0]));
				gpio_number = static_cast<int>(std::stoi(splitData[1]));
                function = static_cast<Function>(std::stoi(splitData[2]));
                level = static_cast<Level>(std::stoi(splitData[3]));

                return true;
			}

            return false;
        }

        void print()
        {
			std::cout << "Operation = " << operation
			          << ", gpio number: " << gpio_number
			          << ", function = " << function << ", level = " << level
			          << std::endl;
		}
	};

private:
    std::vector<GpioInfo> result;

public:
    AtGpioCommand() : result() {}

	uint16_t timeout() const override { return 2; }
	std::string command() override { return "AT+SGPIO=?"; }
	std::string commandComplete() override { return "OK"; }

	bool processResponses(const std::vector<std::string>& responses) override
	{
		if (not responses.empty()) {
            bool result = true;
            for (const std::string& item : responses) {
                std::string data = item.substr(item.find(" ") + 1, item.size());
                std::cout << "Data: " << data << std::endl;

                GpioInfo info;
				if (info.parse(data))
					info.print();
				else
					result = false;
			}

            return result;
		}

		return false;
	}
};

TEST(attestsource, sgpiotest)
{
	AtGpioCommand command;
	bool result =
	    AtCommandScheduler<TestSgpioSender>::instance()->process(&command);

	ASSERT_TRUE(result);
}
