# Сравнение списка с пропусками и АВЛ-дерева

В данной работе приводится сравнение указанных выше структур данных, каждая из которых имеет свои преимущества и недостатки, которые будут показаны на практике после тестирования.

# Содержание
[AVL-Tree](https://github.com/anastasiya0304/Structures/blob/master/AVLTree.cpp)  
[SkipList](https://github.com/anastasiya0304/Structures/blob/master/Skiplist.cpp)  
[Тестирование](#test)

******
# AVL-Tree

 АВЛ-дерево — это прежде всего двоичное дерево поиска, ключи которого удовлетворяют стандартному свойству: ключ любого узла дерева не меньше любого ключа в левом поддереве данного узла и не больше любого ключа в правом поддереве этого узла.  
 Особенностью АВЛ-дерева является то, что оно является сбалансированным в следующем смысле: для любого узла дерева высота его правого поддерева отличается от высоты левого поддерева не более чем на единицу. Авл-деревья обычно используются в учебной практике.
 
### Балансировка
 Относительно АВЛ-дерева балансировкой вершины называется операция, которая в случае разницы высот левого и правого поддеревьев = 2, изменяет связи предок-потомок в поддереве данной вершины так, что разница становится <= 1, иначе ничего не меняет. Указанный результат получается вращениями поддерева данной вершины:
 * [Малое левое вращение](https://github.com/anastasiya0304/Structures/blob/master/Annex/AVL_LR.gif)
 Используется когда: высота(R) = высота(L) + 2 и высота(C) ≤ высота(R).
 * [Большое левое вращение](https://github.com/anastasiya0304/Structures/blob/master/Annex/%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5_6.jpg)
 Используется когда: высота(R) = высота(L) + 1 и высота(C) = высота(L) + 2.
 * [Малое правое вращение](https://github.com/anastasiya0304/Structures/blob/master/Annex/AVL_LL.gif)
 Используется когда: высота(L) = высота(R) + 2 и высота(C) ≤ высота(L).
 * [Большое правое вращение](https://github.com/anastasiya0304/Structures/blob/master/Annex/AVL_BL.gif)
 Используется когда: высота(b-поддерева) — высота (R) = 2 и высота (c-поддерева) > высота (L)

 Операция приводит к нужному результату и полная высота уменьшается не более чем на 1 и не может увеличиться. Также можно заметить, что большое левое вращение это композиция правого малого вращения и левого малого вращения. Из-за условия балансированности высота дерева О(log(N)), где N- количество вершин, поэтому добавление элемента требует O(log(N)) операций.
 
*k* - ключ   *p* - корень  

### Вставка

   void Add ( int k ) 

 Вставка нового ключа в АВЛ-дерево выполняется, так же, как это делается в простых деревьях поиска: спускаемся вниз по дереву, выбирая правое или левое направление движения в зависимости от результата сравнения ключа в текущем узле и вставляемого ключа. Единственное отличие заключается в том, что при возвращении из рекурсии (т.е. после того, как ключ вставлен либо в правое, либо в левое поддерево, и это дерево сбалансировано) выполняется балансировка текущего узла.

*Сложность по времени O(log(n)) по памяти O(n).*

### Поиск

    bool  Has ( int k )

 Поиск выполняется так же как в дереревьях поиска. Для каждого узла сравниваем значение его ключа с искомым ключом. Если ключи одинаковы, то функция возвращает текущий узел, в противном случае функция вызывается рекурсивно для левого или правого поддерева.

*Сложность по времени O(log(n)) по памяти O(n).*

### Удаление

    bool Remove ( int k) 

Удаление происходит сложнее. Находим узел p с заданным ключом k (если не находим, то делать ничего не надо), в правом поддереве находим узел min с наименьшим ключом и заменяем удаляемый узел p на найденный узел min.

При реализации возникает несколько нюансов. Прежде всего, если у найденный узел p не имеет правого поддерева, то по свойству АВЛ-дерева слева у этого узла может быть только один единственный дочерний узел (дерево высоты 1), либо узел p вообще лист. В обоих этих случаях надо просто удалить узел p и вернуть в качестве результата указатель на левый дочерний узел узла p. Как уже говорилось, если удаляемая вершина — лист, то она удаляется, и обратный обход дерева происходит от родителя удалённого листа. Если не лист — ей находится «замена», и обратный обход дерева происходит от родителя «замены». Непосредственно после удаления элемента — «замена» получает баланс удаляемого узла.
При обратном обходе: если при переходе к родителю пришли слева — баланс увеличивается на 1, если же пришли справа — уменьшается на 1.
Это делается до тех пор, пока при изменении баланса он не станет равным −1 или 1: в данном случае такое изменение баланса будет гласить о неизменной высоте поддеревьев. Повороты происходят по тем же правилам, что и при вставке.

*Сложность по времени O(log(n)) по памяти O(n).*

### Операция вывода

    void print ( std::ostream )

Функция вывода структуры. Пример вывода дерева  [180, 51]->[190, 70]->[600, 92]
        
## Выводы

Операции вставки и удаления (а также более простая операция поиска) выполняются за время пропорциональное высоте дерева, т.к. в процессе выполнения этих операций производится спуск из корня к заданному узлу, и на каждом уровне выполняется некоторое фиксированное число действий. А в силу того, что АВЛ-дерево является сбалансированным, его высота зависит логарифмически от числа узлов. Таким образом, время выполнения всех трех базовых операций гарантированно логарифмически зависит от числа узлов дерева.
Использование вместо простых двоичных деревьев поиска приводит к уменьшению времени операций поиска, вставки и удаления данных при одинаковом количестве элементов в дереве, в силу минимизированной высоты. Однако это приводит к усложнению алгоритма взаимодействия с деревом ввиду того, что после выполнения каждой операции вставки и удаления приходится выполнять операцию проверки дерева на сбалансированность, и при обнаружении разбалансировки выполнять операции поворота узлов дерева.

## Области применения

Обоснованность применения АВЛ - деревьев неоднозначна, поскольку они требуют дополнительных затрат на поддержание сбалансированности при вставке или удалении узлов. Если в дереве постоянно происходят вставки и удаления элементов, эти операции могут значительно снизить быстродействие.
Для АВЛ - дерева не существует наихудшего случая, так как оно является почти полным бинарным деревом. Сложность балансировки обусловливает применение АВЛ - деревьев только там, где поиск является доминирующей операцией.

*****

# [SkipList](https://github.com/anastasiya0304/Structures/blob/master/Annex/%D0%9F%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5_7.png)

Списки с пропусками — это вероятностная альтернатива сбалансированным деревьям. Они балансируются с использованием генератора случайных чисел. Из-за того, что эти структуры данных представляют из себя связные списки с дополнительными указателями для пропуска промежуточных узлов, их называют списками с пропусками.

### Построение

Список с пропусками строится на основе существующего односвязного отсортированного списка. Добавив дополнительные уровни, каждый из которых представляет предыдущий уровень без нечетных элементов, мы получим возможность осуществлять поиск, вставку и удаление элементов подобно операциям с двоичным деревом поиска, следовательно, асимптотика этих операций будет составлять O(log(n)).


### Поиск

    bool Has ( int key )

Начиная с указателя наивысшего уровня, двигаемся вперед по указателям до тех пор, пока они ссылаются на элемент, не превосходящий искомый. Затем спускаемся на один уровень ниже и снова двигаемся по тому же правилу. Если мы достигли уровня 1 и не можем идти дальше, то мы находимся как раз перед элементом, который ищем (если он там есть). Чем больше уровень, тем более список на этом уровне разбит, по сравнению с нижележащими. Это разбиение дает оценку сложности поиска O(log(n)) - такую же, как у бинарных самобалансирующихся деревьев.

Скорость работы поиска будет зависить от количества элементов в верхнем списке |L1|. Для анализа преположим, что в L1 попало несколько элементов в случайном порядке. ([Приложение_8_1](https://github.com/anastasiya0304/Structures/blob/master/Annex/%D0%9F%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5_8_1.png))
Время поиска можно улучшать, добавляя новые экспресс-уровни: 2 отсортированных списка, 3 отсортированных списка, k отсортированных списка, log n отсортированных списка. log n сортированных связных списков ведут себя похоже на бинарное дерево. В идеальном списке с пропусками отношение количества элементов между уровнями постоянно и равно 2. В этом случае в нижнем списке будет 2^(log n) = n элементов. Поиск в этой структуре будет выполнятся за O(lg n) шагов. ([Приложение_8_2](https://github.com/anastasiya0304/Structures/blob/master/Annex/%D0%9F%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5_8_2.png)) Сложность операций вставки и удаления доказываются похожим образом.

*Сложность по времени O(log(n)) в среднем и O(N) в худшем, по памяти O(nlog(n))*

### Вставка

    bool Add ( int key )

Для вставки узла применяем алгоритм поиска для нахождения всех элементов перед вставляемым (или удаляемым), затем обновляем соответствующие указатели.Для запоминания элементов перед вставляемым(или удаляемым) используется массив update. Элемент update[i] — это указатель на самый правый узел, уровня i или выше, из числа находящихся слева от места обновления.

Если случайно выбранный уровень вставляемого узла оказался больше, чем уровень всего списка (т.е. если узлов с таким уровнем ещё не было), увеличиваем уровень списка и инициализируем соответствующие элементы массива update указателями на заголовок. После каждого удаления проверяем, удалили ли мы узел с максимальным уровнем и, если это так, уменьшаем уровень списка.

*Сложность по времени O(log(n)) в среднем и O(N) в худшем, по памяти O(nlog(n))*

### Удаление

    bool Remove ( int key )

Для удаления узла так же применяем алгоритм поиска для нахождения всех элементов перед вставляемым , затем обновляем соответствующие указатели.После каждого удаления проверяем, удалили ли мы узел с максимальным уровнем и, если это так, уменьшаем уровень списка.

*Сложность по времени O(log(n)) в среднем и O(N) в худшем, по памяти O(nlog(n))*

### Операция вывода

    void print ( std::ostream )

Функция вывода структуры данных. Пример вывода: [1, 2]->[2, 7]->[3, 12]

## Выводы:

У списков с пропусками плохая производительность в худшем случае, но алгоритмы получаются более простыми для реализации и, на практике, более быстрыми по сравнению со сбалансированными деревьями и кроме того очень эффективно используют память. Они могут быть реализованы так, чтобы на один элемент приходился в среднем примерно 1.33 указатель (или даже меньше) и не требуют хранения для каждого элемента дополнительной информации о балансе или приоритете.

Списки с пропусками — это простая структура данных, которая может использоваться вместо сбалансированных деревьев в большинстве случаев.Алгоритмы очень легко реализовывать, расширять и изменять. Обычные реализации операций на списках с пропусками примерно такие же быстрые, как высокооптимизированные реализации на сбалансированных деревьях и в значительной степени быстрее обычных, невысокооптимизированных реализаций.

## Области применения

С теоретической точки зрения, списки с пропусками не нужны. Сбалансированные деревья могут делать те же операции и имеют хорошую сложность в худшем случае (в отличие от списков с пропусками). Однако, реализация сбалансированных деревьев — сложная задача и, как следствие, они редко реализуются на практике, кроме как в качестве лабораторных работ в университетах.

Списки с пропусками — это простая структура данных, которая может использоваться вместо сбалансированных деревьев в большинстве случаев. Алгоритмы очень легко реализовывать, расширять и изменять. Обычные реализации операций на списках с пропусками примерно такие же быстрые, как высокооптимизированные реализации на сбалансированных деревьях и в значительной степени быстрее обычных, невысокооптимизированных реализаций.

<a name="test"></a>
# Тестирование

1. В ходе тестирования, начнем с проверки правильности работы структуры. Для этого передадим ей заранее известные значения, проверим и удалим часть из них. После выведем и сравним полученную структуру и с истинными значениями, полученными ранее вручную.
2. Далее приступим к сравнению производительности 2х структур, указанных в задании. Подсчитаем время, необходимое для выполнения разных сценариев использования.
3. Сравним полученные данные, соотнесем их с теоритической основой и сделам выводы об оптимальности использлвания в различных задачах.

# Входные и выходные данные

Будем передавать на вход текстовый файл с набором команд, зависящем от сценария. На выходе получим файл с выведенной в него струтурой, а так же инфорцию о корректности и времени работы в командную строку.

# Инструкция по запуску тестируемой программы

Скомпилировав код, будем  передавать ему адрес и имя 3х текстовых файлов в следующей последовательности: 1-с командами, 2-для вывода структуры, 3ий-для проверки корректности(опционально)


# Обработка результатов

В ходе тестированния, удостоверевшись в корректности работы структур, мы провели 3 временных теста для разных сценариев использования:

1. В первом тесте, произведя 1000 вставок и 100 удалений, мы получили 
      9.895 мс для АВЛ-дерева и 7.452 мс для Списка с пропусками 

2. Во втором тесте, сделав 15 вставок, 5 удалений и 250 поисков, получили 
      2.652 мс для АВЛ-дерева и 2.913 мс для Списка с пропусками

3. В третьем тесте, сделав в сумме 75 вставок, будем находить минимальный\максимальный элеменнт каждые 5, получим 
      1.852 мс для АВЛ-дерева и 1.351 мс для Списка с пропусками
      
Тесты производили на ноутбуке xiaomi mi notebook air. 

Таким образом, установим, что списки с пропусками быстрее выполняют операции удаления и вставки, но проигрывают по времени поиска, неисмотря на сложность операций эквивалентную АВЛ-деревьям. Выбор лучшей структуры, зависит от поставленной задачи, но стоит отметить, что Список с пропусками довольно простая структура. Его алгоритмы легко реализуются, изменяются и расширяются. В реальном проекте я бы отдала предпочтение именно этой структуре.



