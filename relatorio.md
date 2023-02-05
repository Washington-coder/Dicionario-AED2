# Relatório do Trabalho sobre Dicionários
## Nomes: Lucas de Oliveira, ... nomes

***Resumo.*** *O trabalho se trata de alguma coisa bem interessante e chato de se usar, a não ser que voce use python*

## **1.Dicionários**
Os dicionário são um tipo abstrato de dados orientados a conteúdo, e considerando que se tratam do tema principal de estudo do trabalho, é importante salientar pontos importantes deles.

Operações implementadas:

Inserir (d, x): insere um item x no dicionário d;

Remover (d, x): remove um item x no dicionário d;

Buscar(d, k): busca uma chave k em um dicionário d; 

Inicia (d): inicia um  dicionário d;

Cheio (d): Testa se o dicionário d está cheio;

Vazio (d): testa se o dicionário d está vazio;

Vimos três tipos de dicionários: Estático,  Semi-Dinâmico e Dinâmico.

**ESTÁTICOS:**  Uma vez construídos seus dados não mudam;  Suas buscas tem um custo ótimo, desde que seus elementos estejam ordenados. 
O dicionário estático é implementado em um vetor.

**SEMI-DINÂMICOS:** são construídos com uma certa margem para possíveis alterações; Têm suporte para inserção e Busca, mas faz pouquíssimas  remoções, o que acaba  sendo um problema; Hashing tem o endereçamento fechado.
Os dicionários semi-dinâmicos são baseados em comparações de chaves.

Seu algoritmo mais eficiente considera elementos ordenados, e ele tem custo computacional O(log n).

A busca baseada em Hashing(tabela de dispersão ou espalhamento) é mais eficiente.

Na média, é possível encontrar a chave com apenas K comparações, onde K é menor que o tamanho do conjunto de chaves.

**FUNÇÃO DE HASH:**

A função hash mapeia uma chave de busca para um índice da tabela. O seu ideal é que a função forneça índices únicos para o conjunto de chaves.

A **função de Hashing** tem influência direta na eficiência das operações de Hash. Quanto melhor for o espelhamento, mais eficiente serão as operações.

A **função de Hashing:** é possível usá-la para codificar dados, transformar a entrada em um "código hash" ou em um "valor do hash". O algoritmo hash é projetado para minimizar a possibilidade de duas entradas terem o mesmo valor do hash, o que é chamado de colisão. 

**As colisões:** Quando duas chaves distintas são mapeadas para a mesma entrada da tabela o tratamento de colisões é  feito. Seu tratamento é feito com encadeamento ou endereçamento aberto.

**Encadeamento:** uma das formas de resolver colisões é construir uma lista linear para cada endereço da tabela, assim todas as chaves com o mesmo endereço são encadeadas em uma lista linear.

É usual efetuar-se a inclusão de uma nova chave x no final da lista correspondente ao endereço h(x).  A ideia é que a lista seja percorrida de qualquer maneira, para assegurar que x não pertence à mesma. Mas, caso chaves repetidas sejam aceitas, essa condição pode ser relaxada, e a chave inserida no início da lista.

Endereçamento aberto: as chaves que sofrem colisão são inseridas na própria tabela e sem o uso de listas encadeadas. Logo, o fator de carga não pode exceder o valor 1. O espaço gasto com encadeamento é economizado e a colisão é tratada com a busca de uma posição vazia na própria tabela para inserção.

Quando uma chave k é endereçada para uma entrada da tabela que já esteja ocupada(colisão), uma sequência de localizações alternativas h1(k), h2(k), … é escolhida. Mas se nenhuma das h1(k), h2(k), … posições está vazia, então a tabela está cheia e não podemos inserir k.

 Existem várias propostas para a escolha de localizações alternativas. A mais simples é a prospecção linear: O índice é incrementado(+i)(h(x)+i)  RESTO M. Encerra Prospecção se a posição está vazia.

**DINÂMICOS:** são construídos com completa capacidade de alteração. Tem suporte para inserção, busca e remoção e são implementados com um ótimo custo. Árvores e Hashing com o endereçamento aberto.

## **2.Objetivos**
O índice remissivo é uma lista de palavras importantes que se repetem em um texto junto com as páginas em que elas ocorrem, elas servem para criar uma relação de termos importantes para o texto em geral. Mas é perceptivel que seria muito custoso uma pessoa verificar quais palavras são importantes de serem citadas, onde elas aparecem e em quais páginas, logo o objetivo principal do trabalho é usar a ideia de dicionários para criar um programa capaz de otimizar esse trabalho, o programa deverá ser capaz de ler um arquivo de texto e retorna outro arquivo com o índice remissivo, e dessa forma entender melhor como funciona a estrutura de dicionários.

## **3.Metódologia**
### **3.1 Planejamento**
A construção do código foi dividida em partes, a primeira parte se trata do pré-processamento do texto, primeiro ele executará a função de stop words que lerá o arquivo das stop words, e os colocará em um vetor, depois disso a função de ler o livro será ativado ele lerá o arquivo de texto que deverá ser tratado, ao ler esse arquivo o código colocará as palavras de uma página em um tipo pagina dentro do tipo livro, porém excluindo as stop words, então por fim acaba a parte de pré-processamento quando a função retorna o tipo livro completo.
Depois da parte de pré-processamento, começa a parte de processamento em si, no caso o código lerá o tipo livro do pré-processsamento, e colocará as palavras no diconario, alocado junto com as repetições e as páginas em que ocorrem, a partir disso será calculado o TF-IDF.

### **3.2 Configuração geral**
aqui a gente vai mostrar e falar o que a gente fez nos códigos e os códigos, detalhar bem os códigos

### **3.3 Configurações Experimentais**
aqui a gente vai falar como fizemos os experimentos, usar figuras esquematicas de como as coisas se interligam

### **3.4 Resultados e interpretações**
essa parte  é importante, talvez a mais importante, eu não entendi como fazer isso:
![image](https://user-images.githubusercontent.com/107904641/216778332-55d1cc53-6011-4b32-8b16-26b95eaa2dbe.png)
![image](https://user-images.githubusercontent.com/107904641/216778654-00af5076-81c4-4d3d-9274-39894d759100.png)

## **4.Discussões**
discutir os resultados em geral dos experimentos e dizer qual foi o melhor jeito de usar
