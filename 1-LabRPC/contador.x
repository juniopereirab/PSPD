struct params {
        char dados<>;
        char palavras<>;
};


struct result {
        int ocorrencias;
        int cont;
};


program PROG {
        version VERSAO {
                result GET_WORDS_QUANTITY(params) = 1;
        } = 100;
} = 55555555;