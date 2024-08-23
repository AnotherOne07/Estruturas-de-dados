Codigo que implementa lista no python:

PyObject *
PyList_New(Py_ssize_t size)
{
    PyListObject *op;

    // Verifica se o tamanho solicitado é negativo, o que não é válido
    if (size < 0) {
        PyErr_BadInternalCall(); // Gera uma exceção de chamada interna inválida
        return NULL;
    }

#if PyList_MAXFREELIST > 0
    struct _Py_list_state *state = get_list_state();

#ifdef Py_DEBUG
    // PyList_New() não deve ser chamado após _PyList_Fini()
    assert(state->numfree != -1);
#endif

    // Verifica se há objetos livres disponíveis no pool de reciclagem
    if (PyList_MAXFREELIST && state->numfree) {
        state->numfree--;

        // Recupera um objeto de lista do pool de reciclagem
        op = state->free_list[state->numfree];

        // Incrementa a estatística de objetos reciclados
        OBJECT_STAT_INC(from_freelist);

        // Cria uma nova referência ao objeto reciclado
        _Py_NewReference((PyObject *)op);
    }
    else
#endif
    {
        // Se não houver objetos livres disponíveis no pool de reciclagem

        // Aloca memória para criar uma nova lista de objetos Python
        op = PyObject_GC_New(PyListObject, &PyList_Type);

        // Verifica se a alocação de memória falhou
        if (op == NULL) {
            return NULL; // Retorna NULL em caso de erro na alocação de memória
        }
    }

    // Inicializa a lista como vazia se o tamanho for menor ou igual a zero
    if (size <= 0) {
        op->ob_item = NULL;
    }
    else {
        // Aloca memória para armazenar os elementos da lista
        op->ob_item = (PyObject **) PyMem_Calloc(size, sizeof(PyObject *));

        // Verifica se a alocação de memória falhou
        if (op->ob_item == NULL) {
            Py_DECREF(op); // Libera a lista em caso de erro
            return PyErr_NoMemory(); // Retorna NULL com uma exceção de falta de memória
        }
    }

    // Configura o tamanho e a capacidade da lista
    Py_SET_SIZE(op, size);
    op->allocated = size;

    // Adiciona a nova lista ao rastreamento de coleta de lixo (garbage collection)
    _PyObject_GC_TRACK(op);

    return (PyObject *) op; // Retorna a nova lista como um objeto PyObject
}

