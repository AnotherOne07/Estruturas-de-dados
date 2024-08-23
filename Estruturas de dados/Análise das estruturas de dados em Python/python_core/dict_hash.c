Codigo que mostra que o dict usa tabela hash: 

// Search key from Generic table.
static Py_ssize_t
dictkeys_generic_lookup(PyDictObject *mp, PyDictKeysObject* dk, PyObject *key, Py_hash_t hash)
{
    PyDictKeyEntry *ep0 = DK_ENTRIES(dk); // Obtemos um ponteiro para a entrada da tabela de chaves.
    size_t mask = DK_MASK(dk); // Máscara usada para calcular o índice na tabela.
    size_t perturb = hash; // Valor de perturbação inicial.
    size_t i = (size_t)hash & mask; // Cálculo inicial do índice com base no hash.
    Py_ssize_t ix;
    
    for (;;) { // Loop infinito para procurar a chave.
        ix = dictkeys_get_index(dk, i); // Obtém o índice da chave na tabela.
        
        if (ix >= 0) { // Se o índice for válido (a chave está na tabela).
            PyDictKeyEntry *ep = &ep0[ix]; // Obtemos um ponteiro para a entrada da chave.
            assert(ep->me_key != NULL); // Verificamos se a chave não é nula.
            
            if (ep->me_key == key) { // Se a chave for encontrada na posição atual.
                return ix; // Retornamos o índice da chave.
            }
            
            if (ep->me_hash == hash) { // Se os hashes coincidirem (possível colisão).
                PyObject *startkey = ep->me_key; // Salva a chave de início.
                Py_INCREF(startkey); // Incrementa a referência para evitar a liberação prematura.
                int cmp = PyObject_RichCompareBool(startkey, key, Py_EQ); // Compara as chaves.
                Py_DECREF(startkey); // Decrementa a referência para liberar a chave de início.
                
                if (cmp < 0) { // Se houver um erro na comparação.
                    return DKIX_ERROR; // Retorna um código de erro.
                }
                
                if (dk == mp->ma_keys && ep->me_key == startkey) {
                    if (cmp > 0) { // Se as chaves forem iguais.
                        return ix; // Retornamos o índice da chave.
                    }
                }
                else {
                    /* O dicionário foi alterado, reinicie */
                    return DKIX_KEY_CHANGED; // Retorna um código indicando que a chave foi alterada.
                }
            }
        }
        else if (ix == DKIX_EMPTY) { // Se o índice estiver vazio.
            return DKIX_EMPTY; // Retorna um código indicando que o índice está vazio.
        }
        
        perturb >>= PERTURB_SHIFT; // Reduz o valor de perturbação.
        // deslocamento uma posicao em 10 -> 10/2^1
        // deslocamento duas poscieso em 10 -> 10/2^2
        i = mask & (i*5 + perturb + 1); // Calcula um novo índice com base na perturbação.
    }
    Py_UNREACHABLE(); // Nunca deve ser alcançado.
}

