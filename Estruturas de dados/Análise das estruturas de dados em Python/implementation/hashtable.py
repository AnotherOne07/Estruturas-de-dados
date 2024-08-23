class HashTable:
    def __init__(self, size):
        self.size = size  # Tamanho da tabela hash
        self.keys = [None] * size  # Lista para armazenar chaves
        self.values = [None] * size  # Lista para armazenar valores correspondentes

    def _hash(self, key):
        # Função de hash simples que retorna um índice com base na chave
        return hash(key) % self.size

    def _find_next_slot(self, key):
        # Encontra o próximo slot disponível para a chave usando sondagem linear
        index = self._hash(key)
        while self.keys[index] is not None:
            if self.keys[index] == key:
                return index  # Retorna o índice se a chave já existe
            index = (index + 1) % self.size  # Move-se para o próximo slot
        return index

    def put(self, key, value):
        # Insere um par chave-valor na tabela hash
        index = self._find_next_slot(key)
        self.keys[index] = key
        self.values[index] = value

    def get(self, key):
        # Obtém o valor associado a uma chave
        index = self._find_next_slot(key)
        if self.keys[index] == key:
            return self.values[index]  # Retorna o valor se a chave for encontrada
        else:
            return None  # Retorna None se a chave não for encontrada

    def remove(self, key):
        # Remove uma chave e seu valor correspondente da tabela hash
        index = self._find_next_slot(key)
        if self.keys[index] == key:
            self.keys[index] = None
            self.values[index] = None
        else:
            raise KeyError(f"Key '{key}' not found in the hash table")

# Exemplo de uso:
hash_table = HashTable(10)
hash_table.put("chave1", "valor1")
hash_table.put("chave2", "valor2")

print(hash_table.get("chave1"))  # Saída: "valor1"
print(hash_table.get("chave2"))  # Saída: "valor2"

hash_table.remove("chave1")
print(hash_table.get("chave1"))  # Saída: None

