Установка библиотеки Mqtt.
1. Склонируйте репозитарий с исходниками библиотеки - git clone https://github.com/qt/qtmqtt.git --branch 5.15
2. Спомощью QtCreator откройте файл qtmqtt.pro.
3. Перед сборкой нужно установит пакет qtbase5-private-dev командой sudo apt install qtbase5-private-dev.
4. Собрать проект.
5. Перейти в папку с собранным проектом
- Скопировать заголовочные файлы include/QtMqtt в папку /usr/include/x86_64-linux-gnu/qt5/
- Скопировать библиотеки(.pri и .so) lib/ в папку /usr/lib/x86_64-linux-gnu/
- Скопировать файл /mkspecs/modules/qt_lib_mqtt.pri в папку /usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/

Склонируйте репозитарий https://github.com/GhostPastR/Mqtt_Test.git с тестовым заданием и открыть с помощью QtCreator.