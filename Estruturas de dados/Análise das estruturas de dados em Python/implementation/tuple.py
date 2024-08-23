class MyTuple:
    def __init__(self, *args):
        self.elements = args

    def __getitem__(self, index):
        # Método especial para acessar elementos da tupla pelo índice
        return self.elements[index]

    def __len__(self):
        # Método especial para obter o tamanho da tupla
        return len(self.elements)

    def __str__(self):
        # Método especial para representação de string da tupla
        return "(" + ", ".join(map(str, self.elements)) + ")"

# Exemplo de uso:
my_tuple = MyTuple(1, 2, 3, 4, 5)

print(my_tuple[2])    # Saída: 3 (acessando o elemento pelo índice)
print(len(my_tuple))  # Saída: 5 (tamanho da tupla)
print(my_tuple)       # Saída: (1, 2, 3, 4, 5) (representação em string da tupla)

