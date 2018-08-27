# Задание 7
## Условие
Разработать программу для пакетной обработки команд. Команды
считываются построчно из стандартного ввода и обрабатываются блоками
по `N` команд. Одна команда - одна строка, значение роли не играет. Если
данные закончились - блок завершается принудительно.
Параметр `N` передается как единственный параметр командной строки в
виде целого числа.
```
input | output
------|-------
cmd1  |
cmd2  |
cmd3  |
      |  bulk: cmd1, cmd2, cmd3
cmd4  |
cmd5  |
      |  bulk: cmd4, cmd5
```
Размер блока можно изменить динамически, если перед началом блока и
сразу после дать команды `{` и `}` соответственно. Предыдущий пакет при
этом принудительно завершается.
```
input | output
------|-------
cmd1  |
cmd2  |
cmd3  |
      |  bulk: cmd1, cmd2, cmd3
{     |
cmd4  |
cmd5  |
cmd6  |
cmd7  |
}     |
      | bulk: cmd4, cmd5, cmd6, cmd7
```
Такие блоки могут быть включены друг в друга при этом вложенные блоки
игнорируются.
```
input | output
------|-------
{     |
cmd1  |
cmd2  |
{     |
cmd3  |
cmd4  |
}     |
cmd5  |
cmd6  |
}     |
      | bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6
```
Если данные закончились внутри блока - блоки игнорируется целиком.
```
input | output
------|-------
cmd1  |
cmd2  |
cmd3  |
      |  bulk: cmd1, cmd2, cmd3
{     |
cmd4  |
cmd5  |
cmd6  |
cmd7  |
```
Вместе с выводом в консоль блоки должны сохранятся в отдельные файлы
с именами `bulk1517223860.log`, где `1517223860` - это время получения
первой команды из блока.
Требования к реализации
Бинарный файл должен называться `bulk`.
Результатом работы должен быть пакет `bulk` опубликованный на bintray.
### Проверка
Задание считается выполненным успешно, если после установки пакета
и запуска с тестовыми данными вывод соответствует описанию. Данные
подаются на стандартный вход построчно с паузой в `1` секунду для
визуального контроля.
Будет отмечена скорость выполнения задания, узнаваемый шаблон
“наблюдатель”, низкая связанность обработки данных, накопления пачек
команд, вывода в консоль и сохранения в файлы.
