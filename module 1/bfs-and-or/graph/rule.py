from typing import List
from graph.node import Node


class Rule:
    def __init__(self, number: int, node_arr: List[Node], out_node: Node, label=0):
        self.number = number  # номер правила
        self.node_arr = node_arr  # массив входных вершин правила, связанных связкой 'И'
        self.out_node = out_node  # выходная вершина
        self.label = label  # открытое (0) / закрытое (1) правило

    def __repr__(self):
        return str(self.number)
