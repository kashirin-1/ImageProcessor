#!/bin/bash

# Сборка с санитайзерами address и undefined

set -e  # Прерывать выполнение при ошибке

echo "=== Сборка проекта с санитайзерами ==="

# Создаем директорию для сборки если её нет
mkdir -p build_san
cd build_san

# Настраиваем CMake с указанием цели для санитайзеров
echo "Настройка CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Собираем проект с санитайзерами
echo "Сборка проекта с санитайзерами..."
make image_processor_san -j$(nproc)

# Копируем бинарник в корень проекта
echo "Копирование бинарника в корень проекта..."
cp image_processor_san ../

cd ..

echo "=== Сборка с санитайзерами завершена ==="
echo "Исполняемый файл: ./image_processor_san"
echo ""
echo "Для запуска с санитайзерами используйте:"
echo "./image_processor_san"
echo ""
echo "Примечание: для обнаружения утечек памяти используйте:"
echo "ASAN_OPTIONS=detect_leaks=1 ./image_processor_san"