/*
** EPITECH PROJECT, 2023
** APP-DevFest [WSL: Ubuntu]
** File description:
** IOHandler
*/

#pragma once

#include "GameDatas.hpp"

#define IO_SWITCH_START_1 2
#define IO_SWITCH_START_2 3
#define IO_SWITCH_START_3 4
#define IO_BUTTON_START 17
#define IO_BUTTON_BOMB 27
#define IO_LED_BOMB 22
#define IO_LED_MISSILE_WARNING 10
#define IO_LED_WALLS_WARNING 9

extern "C" {
    #include <pigpio.h>
    #include <unistd.h>
}

namespace IO {
    class IOHandler {
        public:
            IOHandler()
            {
                if (gpioInitialise() < 0) {
                    throw std::runtime_error("Failed to initialize GPIO");
                }
                gpioSetMode(IO_SWITCH_START_1, PI_INPUT);
                gpioSetMode(IO_SWITCH_START_2, PI_INPUT);
                gpioSetMode(IO_SWITCH_START_3, PI_INPUT);
                gpioSetMode(IO_BUTTON_START, PI_INPUT);
                gpioSetMode(IO_BUTTON_BOMB, PI_INPUT);
                gpioSetMode(IO_LED_BOMB, PI_OUTPUT);
                gpioSetMode(IO_LED_MISSILE_WARNING, PI_OUTPUT);
                gpioSetMode(IO_LED_WALLS_WARNING, PI_OUTPUT);
            }
            ~IOHandler() {
                gpioTerminate();
            }

            const Game::IOInfos *operator->() const
            {
                return &_ioInfos;
            }
            const Game::IOInfos &operator*() const
            {
                return _ioInfos;
            }
            void operator=(const Game::GameDatas &data)
            {
                _gameDatas = data;
            }
            void update() {
                handleInputs();
                handleOutputs();
            };
            void run() {
                while (true) {
                    update();
                }
            }
            void handleInputs() {
                _ioInfos.shipStarted = gpioRead(IO_SWITCH_START_1) && gpioRead(IO_SWITCH_START_2) && gpioRead(IO_SWITCH_START_3) && gpioRead(IO_BUTTON_START);
                _ioInfos.bombLaunched = gpioRead(IO_BUTTON_BOMB);
            }
            void handleOutputs() {
                gpioWrite(IO_LED_BOMB, _gameDatas.canSendBomb);
                gpioWrite(IO_LED_MISSILE_WARNING, _gameDatas.missileWarning);
                gpioWrite(IO_LED_WALLS_WARNING, _gameDatas.wallsWarning);
            }

        private:
            Game::IOInfos _ioInfos;
            Game::GameDatas _gameDatas;
    };
}
