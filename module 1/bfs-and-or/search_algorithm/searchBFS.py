from graph.node import Node
from graph.rule import Rule
import os


# ПОИСК В ШИРИНУ ОТ ДАННЫХ В ГРАФАХ "И/ИЛИ"
class SearchBFS:
    def __init__(self, rule_arr: [Rule]):
        self.rule_arr = rule_arr  # список базы правил

        self.closed_node_list = []  # список закрытых вершин
        self.closed_rule_list = []  # список закрытых правил

        self.goal = None  # целевая вершина

        self.solution_found = 1
        self.solution_not_found = 1

    def realise_searchBFS(self, goal_node: Node, in_node_arr: [Node]):
        # инициализация целевой вершины
        self.goal = goal_node

        # в список закрытых (доказанных) вершин записываем ВХОДНЫЕ вершины
        self.closed_node_list = in_node_arr

        self.create_graph()

        print(f'\nCLOSED RULES: {self.closed_rule_list}')
        print(f'CLOSED NODES: {self.closed_node_list}\n')

        # пока оба флага в 1
        while self.solution_found and self.solution_not_found:
            # вызываем метод ПОТОМКИ
            active_rule_cnt = self.children_search()

            print(f'\nNumber of NEW ACTIVE (proved) rules: {active_rule_cnt}')
            print('----------------------------------------------------------------------\n')

            # проверяем, был ли изменён в методе потомков флаг НЕТ_РЕШЕНИЯ
            if not self.solution_not_found:
                print("SOLUTION WAS FOUND!")
                print(f"ACTIVE RULES: {self.closed_rule_list}")
                print(f"PROVED NODES: {self.closed_node_list}")
                self.create_graph(is_result_graph=True)
                break

            # иначе смотрим кол-во новых активных правил
            elif active_rule_cnt == 0:  # новых активных правил НЕТ
                self.solution_found = 0
                print("SOLUTION WASN'T FOUND..")
                break

    # вычисление кол-ва новых активных правил
    # определяем, покрывается ли текущее правило доказанными (закрытыми) вершинами
    def children_search(self):
        count_active_rules = 0

        for rule in self.rule_arr:
            if not self.solution_not_found:  # решение найдено
                break

            else:
                if self.goal in self.closed_node_list:  # целевая вершина в списке доказанных
                    print(f'GOAL {self.goal} is in CLOSED NODE')
                    self.solution_not_found = 0
                    print('SOLUTION WAS FOUND!')
                    break

                # выполняем поиск активных правил
                elif rule.label == 0:  # правило ещё НЕ ПРОЙДЕНО (т.е. открыто)
                    print(f'> Current rule is {rule.number}')
                    print(f'INPUT NODES: {rule.node_arr}')

                    # проверяем покрытие входных вершин текущего правила доказанными
                    is_input_nodes_of_rule_covered = True

                    for node in rule.node_arr:
                        if node not in self.closed_node_list:
                            print(f'[!] Node {node} not in CLOSED')
                            is_input_nodes_of_rule_covered = False
                            break

                    if not is_input_nodes_of_rule_covered:
                        print(f'NOT ALL of them in CLOSED\n')
                    else:
                        print(f'ALL of them in CLOSED')

                        # помечаем текущее правило и его выходную вершину как закрытые (доказанные)
                        rule.label = 1
                        rule.out_node.flag = 1

                        # добавляем их в список закрытых
                        self.closed_rule_list.append(rule)
                        print(f'\nRule {rule.number} added to CLOSED RULES')

                        if rule.out_node not in self.closed_node_list:
                            self.closed_node_list.append(rule.out_node)
                            print(f'Node {rule.out_node} added to CLOSED NODES\n')
                        else:
                            print(f'Node {rule.out_node} already in CLOSED NODES\n')

                        print(f'CLOSED RULES: {self.closed_rule_list}')
                        print(f'CLOSED NODES: {self.closed_node_list}\n')

                        # проверяем выходную вершину доказанного правила
                        if rule.out_node == self.goal:  # это целевая вершина
                            self.solution_not_found = 0
                            print(f'Rule {rule.number} leads to GOAL')

                        count_active_rules += 1

                elif rule.label == 1:  # правило уже ПРОЙДЕНО (т.е. закрыто)
                    print(f'> Current rule is {rule.number}')
                    print(f'[Already passed]\n')

        return count_active_rules

    # создание изображения графа
    def create_graph(self, is_result_graph=False):
        gv_filename = "schemas\graph_result.gv" if is_result_graph else "schemas\graph_schema.gv"

        with open(gv_filename, 'w') as file:
            file.write("digraph G {\n")

            for rule in self.rule_arr:
                # добавление и окрашивание правил
                square_color = 'darkgreen' if is_result_graph and rule in self.closed_rule_list else 'white'
                file.write(f"\t{rule.number} [shape=square, label={rule.number}, style=filled, fillcolor={square_color}];\n")

                # добавление входных вершин правил
                for input_node in rule.node_arr:
                    if input_node in self.closed_node_list:
                        circle_color = 'lightgreen'
                        circle_shape = 'circle'
                    else:
                        circle_color = 'white'
                        circle_shape = 'ellipse'

                    file.write(f"\t{input_node.number} [shape={circle_shape}, label={input_node.number}, style=filled, fillcolor={circle_color}];\n")

                    # условие для окрашивания рёбер
                    edge_color = 'lightcoral' if (circle_color != 'white' and (is_result_graph and (rule in self.closed_rule_list or input_node.number in self.closed_node_list))) else 'black'
                    file.write(f"\t{input_node.number} -> {rule.number} [color={edge_color}];\n")

                # добавление выходных вершин правил
                if rule.out_node == self.goal:
                    circle_color = 'lightcoral'
                    circle_shape = 'circle'
                elif rule.out_node in self.closed_node_list:
                    circle_color = 'lightgreen'
                    circle_shape = 'circle'
                else:
                    circle_color = 'white'
                    circle_shape = 'ellipse'

                file.write(f"\t{rule.out_node.number} [shape={circle_shape}, label={rule.out_node.number}, style=filled, fillcolor={circle_color}];\n")

                # условие для окрашивания рёбер
                edge_color = 'lightcoral' if (circle_color != 'white' and (is_result_graph and (rule in self.closed_rule_list or rule.out_node.number in self.closed_node_list))) else 'black'
                file.write(f"\t{rule.number} -> {rule.out_node.number} [color={edge_color}];\n")

            file.write("}\n")
            file.close()

        os.system(f"dot -Tsvg {gv_filename} -o {gv_filename[:-3]}.svg")
        os.system(f"dot -Tpng {gv_filename} -o {gv_filename[:-3]}.png")

        os.system(f"explorer {gv_filename[:-3]}.svg")
