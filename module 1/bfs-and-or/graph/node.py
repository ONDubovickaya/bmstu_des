class Node:
    def __init__(self, number: int, flag=0):
        self.number = number  # номер вершины
        self.flag = flag  # открытая (0) / закрытая (1) вершина

    def __repr__(self):
        return str(self.number)
