# graph_widget
Виджет для работы с графами
# Инструкция по сборке (Windows, Visual Studio)
1) Установить Qt(версия 5.9.7 или выше)
2) Задать переменную QMAKESPEC, добавить Qt в Path
3) Выполнить из папки проекта qmake && nmake для сборки проекта
4) Для создания проекта vs выполнить из папки проекта qmake -tp vc. Если при сборке проекта из vs возникает ошибка : "Не удалось найти Windows SDK версии .." - необходимо перенацелить проект: в контекстном меню проекта в обозревателе решений.
