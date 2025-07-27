### mini-pgw - Выпускная работа С++ школы

**mini-pgw** - упрощённая модель сетевого компонента PGW (Packet Gateway), способная обрабатывать UDP-запросы, управлять сессиями абонентов по IMSI, вести CDR-журнал, предоставлять HTTP API, поддерживать чёрный список IMSI и корректно завершать работу.


## Архитектура решения

# Клиент

* читает конфигурацию из JSON-файла;
* читает IMSI (в ASCII кодировке) из командной строки кодирует IMSI (в BCD-кодировку);
* отправляет UDP-пакет с IMSI (в BCD-кодировке);
* получает ответ от сервера;
* записывает логи.

# Сервер

* читает конфигурацию из JSON-файла;
* записывает логи и CDR;
* поддерживает чёрный список IMSI (в ASCII-формате);
* принимает UDP пакеты, содержащие IMSI (в BCD-кодировке);
* декодирует IMSI (в ASCII-формат);
* если IMSI находится в чёрном списке, отправляет 'rejected';
* если IMSI не находится в чёрном списке, создаёт сессию (или продлевает, если сессия с таким IMSI уже существует) и отправляет 'created'.


## Дерево проекта

.
├── Client
│   ├── cfg.json
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── Client.h
│   │   └── Config.h
│   ├── main.cpp
│   └── src
│       ├── Client.cpp
│       └── Config.cpp
├── CMakeLists.txt
├── IConfig
│   ├── CMakeLists.txt
│   ├── include
│   │   └── IConfig.h
│   └── src
│       └── IConfig.cpp
├── Identifier
│   ├── CMakeLists.txt
│   ├── include
│   │   └── Identifier.h
│   └── src
│       └── Identifier.cpp
├── LoggerTypes.h
├── README.md
├── Server
│   ├── cfg.json
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── Config.h
│   │   ├── HttpServer.h
│   │   ├── IRepository.h
│   │   ├── Repository.h
│   │   ├── ServerLauncher.h
│   │   ├── Service.h
│   │   └── UdpServer.h
│   ├── main.cpp
│   └── src
│       ├── Config.cpp
│       ├── HttpServer.cpp
│       ├── IRepository.cpp
│       ├── Repository.cpp
│       ├── ServerLauncher.cpp
│       ├── Service.cpp
│       └── UdpServer.cpp
└── tests
    ├── CMakeLists.txt
    └── identifier_tests.cpp


## Сборка

cd mini-pgw
mkdir build && cd build
cmake ..
make

## Запуск

# Сервер:
cd mini-pgw/build/Server
./server_prog

# Клиент
cd mini-pgw/build/Client
./client_prog 001010000000001

# Тесты
cd mini-pgw/build/tests
./IdentifierTests

## HTTP API

* Команда **/check_subscriber** проверяет, существует ли сессия c заданным IMSI, и возвращает ответ в виде текста 'active' или 'not active':
curl -X GET http://127.0.0.1:8080/check_subscriber?imsi=6753562

* Команда **/stop** завершает работу приложения, используя механизм graceful offload. Сессии удаляются с заданной скоростью, происходит запись CDR:
curl -X POST http://127.0.0.1:8080/stop -d "noop=1"