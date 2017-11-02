# Сравнение списка с пропусками и АВЛ-дерева

В данной работе приводится сравнение указанных выше структур данных, каждая из которых имеет свои преимущества и недостатки, которые будут показаны на практике после тестирования.

# Содержание
[AVL-Tree](https://github.com/anastasiya0304/Structures/blob/master/Create%20AVL-Tree.cpp)  
[SkipList](https://github.com/anastasiya0304/Structures/blob/master/Skiplist.cpp)  
[Тестирование](#test)

Для каждой из структур данных реализованы:

1. Операция вставки - *insert*
2. Операция поиска по ключу - *search*
3. Операция удаления по ключу - *remove*
4. Операция получения минимального значения - *findmin*
5. Операция вывода на экран - *print*

******
# AVL-Tree

АВЛ-дерево — это прежде всего двоичное дерево поиска, ключи которого удовлетворяют стандартному свойству: ключ любого узла дерева не меньше любого ключа в левом поддереве данного узла и не больше любого ключа в правом поддереве этого узла. Особенностью АВЛ-дерева является то, что оно является сбалансированным в следующем смысле: для любого узла дерева высота его правого поддерева отличается от высоты левого поддерева не более чем на единицу. Авл-деревья обычно используются в учебной практике.

*k* - ключ  
*p* - корень  

### insert

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p

Вставка нового ключа в АВЛ-дерево выполняется, так же, как это делается в простых деревьях поиска: спускаемся вниз по дереву, выбирая правое или левое направление движения в зависимости от результата сравнения ключа в текущем узле и вставляемого ключа. Единственное отличие заключается в том, что при возвращении из рекурсии (т.е. после того, как ключ вставлен либо в правое, либо в левое поддерево, и это дерево сбалансировано) выполняется балансировка текущего узла.

*Сложность по времени O(log(n)) по памяти O(n).*

### search

node* search(node* p, int k) //поиск ключа k в дереве p

Поиск выполняется так же как в дереревьях поиска. Для каждого узла сравниваем значение его ключа с искомым ключом. Если ключи одинаковы, то функция возвращает текущий узел, в противном случае функция вызывается рекурсивно для левого или правого поддерева.

*Сложность по времени O(log(n)) по памяти O(n).*

### remove

node* remove(node* p, int k) // удаление ключа k из дерева p

Удаление происходит сложнее. Находим узел p с заданным ключом k (если не находим, то делать ничего не надо), в правом поддереве находим узел min с наименьшим ключом и заменяем удаляемый узел p на найденный узел min.

При реализации возникает несколько нюансов. Прежде всего, если у найденный узел p не имеет правого поддерева, то по свойству АВЛ-дерева слева у этого узла может быть только один единственный дочерний узел (дерево высоты 1), либо узел p вообще лист. В обоих этих случаях надо просто удалить узел p и вернуть в качестве результата указатель на левый дочерний узел узла p.

*Сложность по времени O(log(n)) по памяти O(n).*

### print

Функция вывода структуры. Пример вывода дерева  
........1............... Вывод:..1   
...... /.\ ........................2  
......2...3 .......................3           
........ /.\ ........................4  
........4...5........................5  
        
## Выводы

Использование вместо простых двоичных деревьев поиска приводит к уменьшению времени операций поиска, вставки и удаления данных при одинаковом количестве элементов в дереве, в силу минимизированной высоты. Однако это приводит к усложнению алгоритма взаимодействия с деревом ввиду того, что после выполнения каждой операции вставки и удаления приходится выполнять операцию проверки дерева на сбалансированность, и при обнаружении разбалансировки выполнять операции поворота узлов дерева.

*****

# SkipList

Списки с пропусками — это вероятностная альтернатива сбалансированным деревьям. Они балансируются с использованием генератора случайных чисел. Из-за того, что эти структуры данных представляют из себя связные списки с дополнительными указателями для пропуска промежуточных узлов, их называют списками с пропусками.

*key* - ключ типа K  
*data* - данные типа T  

### search

T find (list skip_list, K key)

Начиная с указателя наивысшего уровня, двигаемся вперед по указателям до тех пор, пока они ссылаются на элемент, не превосходящий искомый. Затем спускаемся на один уровень ниже и снова двигаемся по тому же правилу. Если мы достигли уровня 1 и не можем идти дальше, то мы находимся как раз перед элементом, который ищем (если он там есть).

*Сложность по времени O(log(n)) в среднем и O(N) в худшем, по памяти O(nlog(n))*

### insert

void insert (list skip_list, K key, T data)

Для вставки узла применяем алгоритм поиска для нахождения всех элементов перед вставляемым (или удаляемым), затем обновляем соответствующие указатели.Для запоминания элементов перед вставляемым(или удаляемым) используется массив update. Элемент update[i] — это указатель на самый правый узел, уровня i или выше, из числа находящихся слева от места обновления.

Если случайно выбранный уровень вставляемого узла оказался больше, чем уровень всего списка (т.е. если узлов с таким уровнем ещё не было), увеличиваем уровень списка и инициализируем соответствующие элементы массива update указателями на заголовок. После каждого удаления проверяем, удалили ли мы узел с максимальным уровнем и, если это так, уменьшаем уровень списка.

*Сложность по времени O(log(n)) в среднем и O(N) в худшем, по памяти O(nlog(n))*

### remove

void remove (list skip_list, K key)

Для удаления узла так же применяем алгоритм поиска для нахождения всех элементов перед вставляемым , затем обновляем соответствующие указатели.После каждого удаления проверяем, удалили ли мы узел с максимальным уровнем и, если это так, уменьшаем уровень списка.

*Сложность по времени O(log(n)) в среднем и O(N) в худшем, по памяти O(nlog(n))*

## Выводы:

Несмотря на то, что у списков с пропусками плохая производительность в худшем случае, не существует такой последовательности операций, при которой бы это происходило постоянно. Как итог алгоритмы получаются более простыми для реализации и, на практике, более быстрыми по сравнению со сбалансированными деревьями и кроме того очень эффективно используют память. Они могут быть реализованы так, чтобы на один элемент приходился в среднем примерно 1.33 указатель (или даже меньше) и не требуют хранения для каждого элемента дополнительной информации о балансе или приоритете.

Списки с пропусками — это простая структура данных, которая может использоваться вместо сбалансированных деревьев в большинстве случаев.Алгоритмы очень легко реализовывать, расширять и изменять. Обычные реализации операций на списках с пропусками примерно такие же быстрые, как высокооптимизированные реализации на сбалансированных деревьях и в значительной степени быстрее обычных, невысокооптимизированных реализаций.
<a name="test"></a>
# Тестирование

1. Сначала проводим тест на добавление в структуру. Берем разное количество данных и кидаем в программу. 
2. для каждого количества данных проводим определенное количество операций поиска и удаления к заполненным структурам.
3. Сравниваем и делаем вывод.

