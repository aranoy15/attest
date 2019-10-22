#pragma once

#include <vector>
#include <string>

//Базовый интерфейс для обработки ат команд
class AtCommandBase
{
public:

    virtual uint16_t timeout() const = 0;                                   //таймаут выхода (в секундах)
    virtual std::string command() = 0;                                      //команда запроса
    virtual std::string commandComplete() = 0;                              //команда завершения
    virtual bool processResponses(const std::vector<std::string>&) = 0;     //обработка ответа
};