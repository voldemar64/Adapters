[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=14091759&assignment_repo_type=AssignmentRepo)
# Лабораторная работа 8

Бинарное дерево поиска. Шаблоны. STL.

## Задача

Три STL-совместимых контейнера для [BinarySearchTree](https://en.wikipedia.org/wiki/Binary_search_tree), реализующие различные [способы обхода дерева (in-, pre-, post-order)](https://en.wikipedia.org/wiki/Tree_traversal) через итератор.
Использовалась [Tag Dispatch Idiom](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Tag_Dispatching)

## Требования

Контейнер предоставляет из себя шаблон, праметрезируемый типом хранимых объетов, оператором сравнения и аллокатором, а так же удовлетворять следующим требованиям к stl - совместимым контейнерам:

  - [контейнера](https://en.cppreference.com/w/cpp/named_req/Container)
  - [ассоциативный контейнера](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer)
  - [контейнера с обратным итератором](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer)
  - [контейнера поддерживающие аллокатор](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer)
  - [oбладать двунаправленным итератом](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator)

Способ обхода дерева реализован через итератор, те оператор "++" приводит к перемещению итератора к следующему элементу в дереве, согласно правилу обхода.

## Тесты

Все вышеуказанные требования покрыты тестами, с помощью фреймворка [Google Test](http://google.github.io/googletest).
