from graph.node import Node
from graph.rule import Rule
from search_algorithm.searchBFS import SearchBFS


if __name__ == '__main__':
    node1 = Node(1)
    node2 = Node(2)
    node3 = Node(3)
    node4 = Node(4)
    node5 = Node(5)
    node6 = Node(6)
    node7 = Node(7)
    node8 = Node(8)
    node9 = Node(9)
    node10 = Node(10)

    node11 = Node(11)
    node12 = Node(12)
    node13 = Node(13)
    node14 = Node(14)
    node15 = Node(15)
    node16 = Node(16)
    node17 = Node(17)
    node18 = Node(18)
    node19 = Node(19)
    node20 = Node(20)

    node21 = Node(21)
    node22 = Node(22)
    node23 = Node(23)
    node24 = Node(24)

    rule_arr = [
        Rule(101, [node1, node2], node3),
        Rule(102, [node3, node2, node4], node7),
        Rule(103, [node5, node6], node4),
        Rule(104, [node8, node23], node3),
        Rule(105, [node7, node9], node13),
        Rule(106, [node4, node16, node10], node9),
        Rule(107, [node11, node12], node10),
        Rule(108, [node19, node14], node24),
        Rule(109, [node9, node19], node13),
        Rule(110, [node10, node15], node9),
        Rule(111, [node15, node17], node19),
        Rule(112, [node11, node18], node15),
        Rule(113, [node20, node21], node11),
        Rule(114, [node17, node22], node19),
        Rule(115, [node12, node18, node22], node17)
    ]

    print("<< Поиск в ширину от данных в графах И-ИЛИ >>")
    SearchBFS(rule_arr).realise_searchBFS(node13, [node5, node6, node2, node1, node16, node20, node21, node7, node12])
