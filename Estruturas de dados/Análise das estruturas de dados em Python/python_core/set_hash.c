Codigo que mostra implementacao do set e utiliza tabela hash:

static setentry *
set_lookkey(PySetObject *so, PyObject *key, Py_hash_t hash)
{
    setentry *table;
    setentry *entry;
    size_t perturb = hash; // Valor inicial de perturbação com base no hash
    size_t mask = so->mask; // Máscara de tamanho da tabela
    size_t i = (size_t)hash & mask; /* Índice inicial baseado no hash (unsigned para definir comportamento de overflow) */
    int probes; // Número de sondagens
    int cmp; // Variável para armazenar o resultado da comparação

    while (1) { // Loop infinito para procurar a chave
        entry = &so->table[i]; // Obtemos um ponteiro para a entrada da tabela
        probes = (i + LINEAR_PROBES <= mask) ? LINEAR_PROBES : 0; // Calcula o número de sondagens
        do {
            // Verifica se a entrada está vazia (hash == 0 e key == NULL)
            if (entry->hash == 0 && entry->key == NULL)
                return entry; // Retorna a entrada vazia

            // Verifica se o hash da entrada coincide com o hash da chave
            if (entry->hash == hash) {
                PyObject *startkey = entry->key;
                assert(startkey != dummy); // Verifica se a chave não é um valor dummy

                // Verifica se a chave é a mesma que a chave de início
                if (startkey == key)
                    return entry;

                // Verifica se a chave é igual à chave de início (para objetos Unicode)
                if (PyUnicode_CheckExact(startkey)
                    && PyUnicode_CheckExact(key)
                    && _PyUnicode_EQ(startkey, key))
                    return entry;

                table = so->table;
                Py_INCREF(startkey); // Incrementa a referência para evitar a liberação prematura
                cmp = PyObject_RichCompareBool(startkey, key, Py_EQ); // Compara as chaves
                Py_DECREF(startkey); // Decrementa a referência para liberar a chave de início

                if (cmp < 0)
                    return NULL; // Retorna NULL em caso de erro na comparação

                // Verifica se a tabela ou a chave de entrada foram alteradas durante a comparação
                if (table != so->table || entry->key != startkey)
                    return set_lookkey(so, key, hash);

                // Se a chave for igual à chave de início, retorna a entrada
                if (cmp > 0)
                    return entry;

                mask = so->mask; // Atualiza a máscara
            }
            entry++;
        } while (probes--); // Realiza sondagens
        perturb >>= PERTURB_SHIFT; // Atualiza o valor de perturbação
        i = (i * 5 + 1 + perturb) & mask; // Calcula um novo índice
    }
}

