=====================
    Pré-requisitos
=====================

- Um arquivo representado por uma lista encadeada de blocos.

- Cada bloco possui duas partes: um valor (1 byte - um caractere) e um ponteiro
  para o próximo bloco

- Cada arquivo será uma palavra, que será representada por uma lista ligada onde
  cada bloco da lista ligada irá representar uma letra da palavra.

- O sistema de arquivos será representado por um vetor de lista ligada de 32 bytes.
  (Basicamente, será um vetor com tamanho fixo de 32 elementos)

=====================
    Entendimento
=====================

Terei uma lista de 32 elementos,
