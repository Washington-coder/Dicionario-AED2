# Relatório do Trabalho sobre Dicionários
## Nomes: Lucas de Oliveira, ... nomes

***Resumo.*** *O trabalho se trata de alguma coisa bem interessante e chato de se usar, a não ser que voce use python*

### **1.Dicionários**
aqui algumas informações importantes sobre dicionários, aqui dá pra dizer de forma bem rapidinha como a gente tratou os dicionários

### **2.Objetivos**
O índice remissivo é uma lista de palavras importantes que se repetem em um texto junto com as páginas em que elas ocorrem, elas servem para criar uma relação de termos importantes para o texto em geral. Mas é perceptivel que seria muito custoso uma pessoa verificar quais palavras são importantes de serem citadas, onde elas aparecem e em quais páginas, logo o objetivo principal do trabalho é usar a ideia de dicionários para criar um programa capaz de otimizar esse trabalho, o programa deverá ser capaz de ler um arquivo de texto e retorna outro arquivo com o índice remissivo, e dessa forma entender melhor como funciona a estrutura de dicionários.

### **3.Metódologia**
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

### **4.Discussões**
discutir os resultados em geral dos experimentos e dizer qual foi o melhor jeito de usar
