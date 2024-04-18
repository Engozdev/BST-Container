# STL контейнер: Бинарное дерево поиска

## Продукт

STL-совместимый контейнер для [BinarySearchTree](https://en.wikipedia.org/wiki/Binary_search_tree), реализующий
различные [способы обхода дерева (in-, pre-, post-order)](https://en.wikipedia.org/wiki/Tree_traversal) через итератор.

Чтобы не создавать три разных контейнера, я
воспользовался [Tag Dispatch Idiom.](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Tag_Dispatching)

Контейнер предоставляет из себя шаблон, параметризуемый типом хранимых объектов, оператором сравнения и аллокатором, а
также удовлетворяет следующим требованиям к stl - совместимым контейнерам:

- [контейнера](https://en.cppreference.com/w/cpp/named_req/Container)
- [ассоциативный контейнера](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer)
- [контейнера с обратным итератором](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer)
- [контейнера поддерживающие аллокатор](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer)
- [oбладать двунаправленным итератором](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator)

Способ обхода дерева реализован через итератор, те оператор "++" приводит к перемещению итератора к следующему элементу
в дереве, согласно правилу обхода.
Продукт реализован без использования контейнеров стандартной библиотеки.

## Тесты

Все вышеуказанные требования покрыты тестами, с помощью фреймворка [Google Test](http://google.github.io/googletest).