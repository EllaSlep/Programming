# Programming labs
***
## For C programming labs.

**_Here are labs from ITMO ISiT_**
- _1 course 1 semester:_
    Номер | Ссылка на код | Текст задачи
    :------- |:----------------:| -----------------:
    1 lab | [Функция Word Cont](https://github.com/EllaSlep/Programming/blob/main/C/WordCont.c) | [Текст задания](#WordCont) <a id="up2"></a>
    2 lab | [Тип данных uint1024_t](https://github.com/EllaSlep/Programming/blob/main/C/uint1024_t.c) | [Текст задания](#uint1024_t) <a id="up1"></a>
    3 lab | [Анализ файла](https://github.com/EllaSlep/Programming/blob/main/C/analiz2.c) | [Текст задания](#Analiz) <a id="up3"></a>
    4 lab | [Чтение mp3](https://github.com/EllaSlep/Programming/blob/main/C/mp3_reader2.c) | [Текст задания](#mp3_reader) <a id="up4"></a> [^файл_музыка]
    5 lab | [Игра "Жизнь"](https://github.com/EllaSlep/Programming/blob/main/C/Life.c) | [Текст задания](#Life) <a id="up5"></a> [^файл_игра]
    6 lab | [Архиватор](https://github.com/EllaSlep/Programming/blob/main/C/arc.c) | [Текст задания](#arc) <a id="up6"></a>

Для работы с лабараторными есть файлы: [3](https://github.com/EllaSlep/Programming/blob/main/C/files/2-08%20o%20no%20no%20no%20(not%20clip).mp3), [5](https://github.com/EllaSlep/Programming/blob/main/C/files/Pulsar.bmp).

***
<a id="WordCont"></a>
###Лабораторная работа. Утилита WordCount

#####Задача.
Реализовать утилиту WordCount подсчитывающую количество строк, слов и байт для указанного файла и выводить эту информацию в поток вывода.

Программа должна поддерживать следующие опции:
1. -l, --lines вывод только количества строк
2. -c, --bytes вывод размера файла в байтах
3. -w, --words вывод количества слов

Название файла и опции передаются через аргументы командной строки в следующем формате: WordCont.exe [OPTION] filename

#####Примечание.
>1. Для реализации утилиты потребуется воспользоваться стандартной библиотекой вводы\вывода [описание](https://en.cppreference.com/w/c/io).
>2. Пример того, как можно организовать парсинг аргументов командной строки, можно посмотреть [здесь](https://www.cplusplus.com/articles/DEN36Up4/).

[Вернуться](#up2)

***
<a id="uint1024_t"></a>
###Лабораторная работа. uint1024_t

#####Задача
Реализовать пользовательский тип для целого беззнакового числа фиксированной длины uint1024_t

Для вышеуказанного типа реализовать функции с следующими сигнатурами:
1. `uint1024_t from_uint(unsigned int x)` - генерация из числа
2. `uint1024_t add_op(uint1024_t x, uint1024_t y)` - сложение
3. `uint1024_t subtr_op(uint1024_t x, uint1024_t y)` - вычетание
4. `uint1024_t mult_op(uint1024_t x, uint1024_t y)` - умножение
5. `void printf_value(uint1024_t x)` - вывод в стандартный поток вывода
6. `void scanf_value(uint1024_t* x)` - чтение из стандартного потока ввода

#####Примечание:
>1. Переполнение - Undefined Behavior
>2. При реализации думать об оптимальном использовании памяти
>3. Реализовать программу демонстрирующую работоспособность вышеуказанных функций

[Вернуться](#up1)

***

<a id="Analiz"></a>
###Лабораторная работа. Анализ логов сервера

#####Задача
Вам предоставлен access.log одного из серверов NASA [скачать](https://drive.google.com/file/d/1jjzMocc0Rn9TqkK_51Oo93Fy78KYnm2i/view).

Это текстовый файл, каждая строка которого имеет следующий формат:
___\$remote_addr - - [\$local_time] “\$request” \$status \$bytes_send___

___\$remote_addr___ - источник запроса
___\$local_time___ - время запроса
___\$request___ - запрос
___\$status___ - статус ответ
___\$bytes_send___ - количество переданных в ответе байт

#####Например:
>198.112.92.15 - - [03/Jul/1995:10:50:02 -0400] "GET /shuttle/countdown/HTTP/1.0" 200 3985

#####Требуется:
1. Подготовить список запросов, которые закончились 5xx ошибкой, с количеством неудачных запросов
2. Найти временное окно (длительностью параметризуются), когда количество запросов на сервер было максимально

#####Примечание:
>1. Для парсинга строк проще всего воспользоваться библиотеками stdio.h и string.h стандартной библиотеки
>2. Про коды ответа можно почитать например вот [тут](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)

[Вернуться](#up3)

***

<a id="mp3_reader"></a>
###Лабораторная работа. Редактор метаинформации mp3-файла

#####Задача.
Реализовать редактор текстовой метаинформации mp3 файла. В качестве стандарта метаинформации принимаем ID3v2.

Редактор представлять из себя консольную программу принимающую в качестве аргументов имя файла через параметра _--filepath_ , а также одну из выбранных команд:
1. _--show_ - отображение всей метаинформации в виде таблицы
2. _--set=prop_name --value=prop_value_ - выставляет значение определенного поля метаинформации с именем prop_name в значение prop_value
3. _--get=prop_name_ - вывести определенное поле метаинформации с именем prop_name

#####Например:
>1. _app.exe --filepath=Song.mp3 --show_
>2. _app.exe --filepath=Song.mp3 --get=TIT2_
>3. _app.exe --filepath=Song.mp3 --set=COMM --value=Test_

#####Примечание.
>При выполнения данной работы разрешается использовать только стандартную библиотеку языка С. Исключением может являться процесс разбора аргументов командной строки.

[Вернуться](#up4)

[^файл_музыка]: Можете взять [файл mp3](https://github.com/EllaSlep/Programming/blob/main/C/files/2-08%20o%20no%20no%20no%20(not%20clip).mp3)

***

<a id="Life"></a>
###Лабораторная работа. Игра жизнь

Целью лабораторной работы является реализация [игры “Жизнь”](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), позволяющая выводить поколение игры в монохромную картинку в [формате BMP](https://en.wikipedia.org/wiki/BMP_file_format). Плоскость “вселенной” игры ограничена положительными координатами.

Лабораторная работы должна быть выполнена в виде консольного приложения принимающего в качестве аргументов следующие параметры:
1. ___--input input_file.bmp___ - где input_file.bmp - монохромная картинка в формате bmp, хранящая начальную ситуация (первое поколение) игры
2. ___--output dir_name___ - название директории для хранения поколений игры в виде монохромной картинки
3. ___--max_iter N___ - максимальное число поколений которое может эмулировать программа. (Необязательный параметр, по-умолчанию бесконечность)
4. ___--dump_freq N___ - частота с которой программа должно сохранять поколения виде картинки. (Необязательный параметр, по-умолчанию равен 1)

#####Примечание
>Программа должна предусматривать исключительные ситуации, которые могут возникать во время ее работы и корректно их обрабатывать.[^файл_игра]

[Вернуться](#up5)

[^файл_игра]:Можете взять [файл bmp](https://github.com/EllaSlep/Programming/blob/main/C/files/Pulsar.bmp)

***

<a id="arc"></a>
###Лабораторная работа. Архиватор файлов.

Целью лабораторной работы является разработка программы по архивированию и распаковке нескольких файлов в один архив. Архиватор должен:
1. Уметь архивировать несколько (один и более) указанных файлов в архив с расширением __*.arc__
2. Уметь распаковывать файловых архив, извлекая изначально запаковонные файлы
3. Предоставлять список файлов упакованных в архиве
4. _Сжимать и разжимать данные при архивировании с помощью алгоритма Хаффмана (опциональное задание, оценивается доп баллами)_

Архиватор должен быть выполнен в виде консольного приложения, принимающего в качестве аргументов следующий параметры:
- **--file FILE** - Имя файлового архива с которым будет работать архиватор
- **--create** - Команда для создания файлового архива
- **--extract** - Команда для извлечения из файлового архива файлов
- -**-list** - Команда для предоставления списка файлов, хранящихся в архиве
- **FILE1 FILE2 .... FILEN** - Свободные аргументы для передачи списка файлов для запаковки

#####Примеры использования:
>___arc --file data.arc --create a.txt b.bin c.bmp___
>___arc --file data.arc --extract___
>___arc --file data.arc --list___

[Вернуться](#up6)

