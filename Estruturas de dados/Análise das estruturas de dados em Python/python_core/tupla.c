Codigo que mostra implementacao da tupla:
PyObject *PyTuple_New(Py_ssize_t size)
{
    PyTupleObject *op;

    // Verifica se o tamanho é igual a zero
    if (size == 0) {
        // Se o tamanho for zero, retorna uma tupla vazia preexistente
        return tuple_get_empty();
    }

    // Aloca memória para uma nova tupla com o tamanho especificado
    op = tuple_alloc(size);

    // Verifica se a alocação de memória falhou
    if (op == NULL) {
        return NULL; // Retorna NULL para indicar um erro
    }

    // Inicializa todos os elementos da nova tupla como NULL
    for (Py_ssize_t i = 0; i < size; i++) {
        op->ob_item[i] = NULL;
    }

    // Adiciona a nova tupla ao rastreamento de coleta de lixo (garbage collection)
    _PyObject_GC_TRACK(op);

    // Retorna a nova tupla como um objeto PyObject
    return (PyObject *) op;
}


