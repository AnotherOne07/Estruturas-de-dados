class MySet:
    def __init__(self):
        self.elements = []

    def add(self, item):
        # Adiciona um elemento ao conjunto se ele ainda não estiver presente
        if item not in self.elements:
            self.elements.append(item)

    def remove(self, item):
        # Remove um elemento do conjunto se ele estiver presente
        if item in self.elements:
            self.elements.remove(item)

    def contains(self, item):
        # Verifica se um elemento está no conjunto
        return item in self.elements

    def size(self):
        # Retorna o tamanho do conjunto (número de elementos)
        return len(self.elements)

    def items(self):
        # Retorna uma lista dos elementos no conjunto
        return self.elements

# Exemplo de uso:
my_set = MySet()
my_set.add(1)
my_set.add(2)
my_set.add(3)

print(my_set.contains(2))  # Saída: True
print(my_set.contains(4))  # Saída: False

my_set.remove(2)
print(my_set.contains(2))  # Saída: False

print(my_set.size())       # Saída: 2 (1 e 3)
print(my_set.items())      # Saída: [1, 3]

