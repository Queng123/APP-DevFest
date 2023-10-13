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
#define IO_LED_BOMB 14
#define IO_LED_MISSILE_WARNING 15
#define IO_LED_WALLS_WARNING 18

extern "C" {
    #include <pigpio.h>
    #include <unistd.h>
}

namespace IO {
    class IOHandler {
        public:
            IOHandler()
            {
                _ioInfos.shipStarted = false;
                _ioInfos.bombLaunched = false;
                _ioInfos.magicNumber = MAGIC_NUMBER;
                _needsToStop = false;
                if (gpioInitialise() < 0) {
                    throw std::runtime_error("Failed to initialize GPIO");
                }
                gpioSetMode(IO_SWITCH_START_1, PI_INPUT);
                gpioSetPullUpDown(IO_SWITCH_START_1, PI_PUD_UP);
                gpioSetMode(IO_SWITCH_START_2, PI_INPUT);
                gpioSetPullUpDown(IO_SWITCH_START_2, PI_PUD_UP);
                gpioSetMode(IO_SWITCH_START_3, PI_INPUT);
                gpioSetPullUpDown(IO_SWITCH_START_3, PI_PUD_UP);
                gpioSetMode(IO_BUTTON_START, PI_INPUT);
                gpioSetPullUpDown(IO_BUTTON_START, PI_PUD_UP);
                gpioSetMode(IO_BUTTON_BOMB, PI_INPUT);
                gpioSetPullUpDown(IO_BUTTON_BOMB, PI_PUD_UP);
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
                while (!_needsToStop) {
                    update();
                }
            }
            void handleInputs() {
	        _ioInfos.shipStarted = !gpioRead(IO_SWITCH_START_1) && !gpioRead(IO_SWITCH_START_2) && !gpioRead(IO_SWITCH_START_3) && !gpioRead(IO_BUTTON_START);
	        _ioInfos.bombLaunched = !gpioRead(IO_BUTTON_BOMB);
            }
            void handleOutputs() {
                gpioWrite(IO_LED_BOMB, _gameDatas.canSendBomb);
                gpioWrite(IO_LED_MISSILE_WARNING, _gameDatas.missileWarning);
                gpioWrite(IO_LED_WALLS_WARNING, _gameDatas.wallsWarning);
            }
            void stop() {
                _needsToStop = true;
            }
            bool getNeedsToStop() {
                return _needsToStop;
            }

        private:
            Game::IOInfos _ioInfos;
            Game::GameDatas _gameDatas;
            bool _needsToStop;
    };
}
