# Фильтры:

-crop width height
-gs
-neg
-sharp
-edge threshold
-blur sigma
-crystal cell_size

# Сборки:

Сборка через cmake в build

make image_processor_san - сборка под санитайзерами
make image_processor - релизная сборка

# Применение фильтров

Описание формата аргументов командной строки:

`{имя программы} {путь к входному файлу} {путь к выходному файлу}
[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...]
[-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...`

# Пример:

./image_processor lenna.bmp lennw.bmp -crystal 25 -gs