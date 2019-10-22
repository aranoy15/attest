#pragma once

#include <vector>
#include <atcommandbase.h>
#include <ctime>

/** Планировщик ат команд 
 * Sender - клас для отправки и получения сообщений
*/
template<class Sender>
class AtCommandScheduler
{
private:
    static AtCommandScheduler<Sender>* m_instance;

private:
    Sender m_sender;
    std::clock_t m_clock_timeout; // переменная для отсчета таймаута

private:
    void start() { m_clock_timeout = std::clock(); }

    /** Проверка таймаута */
    bool has_expired(uint16_t secs) {
      auto ticks = static_cast<int>((std::clock() - m_clock_timeout) / CLOCKS_PER_SEC);
      return ticks >= secs;
    }

public:

    AtCommandScheduler(const AtCommandScheduler&) = delete;
    AtCommandScheduler operator=(const AtCommandScheduler&) = delete;

    AtCommandScheduler() {}
    virtual ~AtCommandScheduler() {}

    static AtCommandScheduler* instance()
    {
        if (m_instance == nullptr) {
            m_instance = new AtCommandScheduler<Sender>();
        }

        return m_instance;
    }

    /** Обработка команды */
    bool process(AtCommandBase* command)
    {
        std::vector<std::string> lines;

        m_sender.write(command->command());

        start();

        while (true) {
            if (has_expired(command->timeout())) return false;

            std::string line = m_sender.readLine();

            if (line == command->commandComplete()) break;

            if (not line.empty())
                lines.push_back(line);
        }

        return command->processResponses(lines);
    }

};

template<class Sender>
AtCommandScheduler<Sender>* AtCommandScheduler<Sender>::m_instance = nullptr;
