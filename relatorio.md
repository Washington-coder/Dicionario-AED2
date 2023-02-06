# Relatório do Trabalho sobre Dicionários
## Nomes: Lucas de Oliveira, ... nomes

***Resumo.*** *O trabalho se trata de alguma coisa bem interessante e chato de se usar, a não ser que voce use python*



## **1.Objetivos**

Os dicionários são um tipo de estrutura de dados muito importantes e úteis na área da computação, visto isso o objetivo do trabalho é resolver um problema utilizando essa estrutura. O índice remissivo é uma lista de palavras importantes de texto anexado junto com as páginas em que elas ocorrem, ele serve para criar uma relação de termos importantes para o texto em geral. Mas é perceptivel que seria muito custoso uma pessoa verificar quais palavras são importantes de serem citadas, onde elas aparecem e em quais páginas, e esta é a dificuldade que foi proposta resolver utilizando a ideia de dicionários, afim de otimizar esse trabalho, o programa deverá ser capaz de ler um arquivo de texto e retorna outro arquivo com o índice remissivo.



## **2.Dicionários**

Os dicionário são um tipo abstrato de dados orientados a conteúdo, e considerando que se tratam do tema principal de estudo do trabalho, é importante salientar pontos importantes deles.
Existem três tipos de dicionários: Estático, Semi-Dinâmico e Dinâmico.

**ESTÁTICOS:**  Uma vez construídos seus dados não mudam;  Suas buscas tem um custo ótimo, desde que seus elementos estejam ordenados. 
O dicionário estático é implementado em um vetor.

**SEMI-DINÂMICOS:** São construídos com uma certa margem para possíveis alterações, têm suporte para inserção e Busca, mas faz pouquíssimas  remoções, o que pode acabar sendo um problema.

**DINÂMICOS:** São construídos com completa capacidade de alteração. Tem suporte para inserção, busca e remoção e são implementados com um ótimo custo. Árvores e Hashing com o endereçamento aberto.

Durante o planejamento do trabalho foi decidido que usaremos um dicionário estático para guardar as stop words, afinal não será preciso alterar o dicionário uma vez que ele ja foi construído, apenas fazer a busca dentro dele. E também foi decidido a utilização de um dicionário dinâmico afim de adicionar as possíveis palavras que serão colocadas no índisse remissivo, a função de remoção do dicionário dinâmico será útil na parte de redimensionamento.

**FUNÇÃO DE HASH:** Algo em comum entre o dicionário semi-dinâmico e o dicionário dinâmico é que ambos possuem uma função de hashing, a função mapeia uma chave de busca para um índice do vetor. O seu ideal é que a função forneça índices únicos para o conjunto de chaves.
A **função de Hashing** tem influência direta na eficiência das operações de Hash. Quanto melhor for o espelhamento, mais eficiente serão as operações.
É possível usá-la para codificar dados, transformar a entrada em um "código hash" ou em um "valor do hash". O algoritmo hash é projetado para minimizar a possibilidade de duas entradas terem o mesmo valor do hash, o que é chamado de colisão. 

**As colisões:** Colisão é o nome do fenômeno que acontece quando duas chaves distintas são mapeadas para a mesma entrada da tabela, nesse caso deve  ser feito o tratamento de colisões. Pode ser resolvido através de encadeamento ou endereçamento aberto.

**Encadeamento:** uma das formas de resolver colisões é construir uma lista linear para cada endereço da tabela, assim todas as chaves com o mesmo endereço são encadeadas em uma lista linear. É usual efetuar-se a inclusão de uma nova chave x no final da lista correspondente ao endereço h(x).

**Endereçamento aberto:** As chaves que sofrem colisão são inseridas na própria tabela e sem o uso de listas encadeadas. Logo, o fator de carga não pode exceder o valor 1. O espaço gasto com encadeamento é economizado e a colisão é tratada com a busca de uma posição vazia na própria tabela para inserção. Quando uma chave k é endereçada para uma entrada da tabela que já esteja ocupada(colisão), uma sequência de localizações alternativas é escolhida. Mas se nenhuma das posições está vazia, então a tabela está cheia e não podemos inserir k. Existem várias propostas para a escolha de localizações alternativas. A mais simples é a prospecção linear: O índice é incrementado, encerra Prospecção se a posição está vazia.



## **3.Metodologia**

### **3.1 Planejamento**

A construção do código foi dividida em partes.

**Pré-processamento:** onde é executada a função `carregaStopwords(.)`, que faz a leitura o arquivo das stop words e retorna um vetor das suas palavras. Depois disso, a função `lerPagina(arquivo, stopwords, num_pagina)` é ativada e faz a leitura do arquivo de texto que deverá ser tratado. Ao ler esse arquivo, o código insere as palavras de uma página -- excluindo as stopwords -- em uma `struct TPagina`, contendo o vetor de palavras, sua quantidade, e o número da respectiva página. Essa função é chamada repetidamente pela função `lerLivro(arquivo, stopwords)`, que guarda seus resultados dentro de uma `struct TLivro`, contendo um vetor de `TPagina`s e a quantidade de páginas. Uma vez que se chegue ao fim do livro, a função retorna o TLivro completo.

**Dicionário Dinâmico:** depois da parte de pré-processamento, começa a parte de processamento em si, onde o código lerá o tipo livro do pré-processsamento, e colocará as palavras no dicionário, a partir disso será calculado o TF-IDF.


### **3.2 Descrição do código**

aqui a gente vai mostrar e falar o que a gente fez nos códigos e os códigos, detalhar bem os códigos

### **3.3 Configurações Experimentais**

aqui a gente vai falar como fizemos os experimentos, usar figuras esquematicas de como as coisas se interligam

### **3.4 Resultados e interpretações**

essa parte  é importante, talvez a mais importante, eu não entendi como fazer isso:
![image](https://user-images.githubusercontent.com/107904641/216778332-55d1cc53-6011-4b32-8b16-26b95eaa2dbe.png)
![image](https://user-images.githubusercontent.com/107904641/216778654-00af5076-81c4-4d3d-9274-39894d759100.png)

## **4.Discussões**

discutir os resultados em geral dos experimentos e dizer qual foi o melhor jeito de usar
