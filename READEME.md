# Game of Life 

O game of life é um autônomo celular cria do pelo britânico John Conway, consiste em um jogo que funciona sem a interação com o usuário, possui a formato de matriz na qual cada célula pode estar em dois estados, vivas ou mortas. Para que o jogo possa ser executado de forma correta é necessário que seja definido um estado inicial especificando quais células devem estar vivas no início do jogo, então a partir do estado inicial são aplicadas as seguintes regras: 1- As células vivas que possuírem menos de dois vizinhos vivos morrem por subpopulação. 2- As células vivas que possuírem exatamente dois vizinhos ou três, vivem para a próxima geração. 3- As células vivas que possuírem quatro vizinhos ou mais morrem por superpopulação. 4- As células mortas com exatamente três vizinhos vivos, vivem para próxima geração. 

### Trabalho realizado 

No presente trabalho o game of life foi adaptado a partir da versão encontrada no You Tube, no canal Cobb Coding (disponivel no link: https://youtu.be/I0ndY1Y4avQ?si=83_91MV9NTf4Gh53). 



As seguintes adaptações foram realizadas: a interface gráfica exibida no terminal foi removida,o estado inicial do jogo é definido em um arquivo de texto, caso esse arquivo não seja disponibilizado o jogo gera um estado inicial aleatório, foi adicionado ao jogo a funcionalidade de gerar imagens .pmb com capturas dos estados do jogo, outra saída do jogo será um arquivo de texto com o tempo real de execução em segundos. Além disso, será utilizado um arquivo de texto para configurar o jogo. Estão disponíveis aqui duas versões na primeira o código foi implementado de forma serial e na segunda de forma paralela usando openMP.  

### Arquivos do projeto 

O projeto está organizado nos seguintes arquivos arquivos: config.txt, este arquivo é responsável por passar parâmetros de entrada para a execução do software, nele são especificados quatro paramentos para a versão serial, separados por um espaço simples, os parâmetros são respectivamente, a altura da matriz, a largura da matriz, a quantidade de interações que serão realizadas, e o intervalo de interações para a capitara da imagem. Na versão paralela, além dos parâmetros mencionados para versão serial, um outro parâmetro será passado no arquivo de configuração, a quantidade de threads usadas. 

Main.c, este é o arquivo no qual está a função principal, esta função é a primeira a ser chamada ao executar o código, ela realiza a leitura do arquivo index.txt e pega as os dados contidos nele, e utiliza para fazer a comunicação com as funções que estão em outros arquivos fazendo o jogo funcionar. Além disso é na função main, é calculado o tempo real de execução e salvo em um arquivo de texto. 

Image.c, este arquivo possui o código responsável por gerar as imagens .pbm, e salvá-las. 

grid.c, este arquivo possui o código que gera matriz na qual ocorre todas as interações do jogo. 

gol.h, este arquivo é responsável por fazer a conexão entre os demais arquivos. 

### Implementação da versão paralela 

A versão paralela foi desenvolvida a partir do código da versão serial através da utilização do OpenMP, as alterações foram realizadas em três ponto do código, que são: no arquivo logic.c o código foi paralelizado primeiro no momento de criação de uma grade temporária e depois no local mais importante do jogo, no qual a grade é dividida em quatro grupos de colunas e esses grupos são distribuídos de forma estática entre os threads, quando existir mais de um thread. O código também foi paralelizado no arquivo grid.c quando a grade é alocada dinamicamente com base nas dimensões informadas.  

Nesse caso a arquitetura utilizada na paralelização foi a Phase Parallel Paradigm, na qual o computo de cada pacote de colunas acontece independentemente, e ao fim todos são sincretizados antes de iniciar outro computo.  


### Como executar 

Para executar basta fazer download do código, abrir o terminal na pasta com os arquivos é necessario um compilador da linguagem C nesse caso utilizou-se o gcc, também é necessário possuir suporte para OpenMP. 

    Caso use as configurações por meio do arquivo de texto deve ser executado o comando " gcc grid.c image.c logic.c main.c -o gol” para a versão serial ou “gcc -fopenmp grid.c image.c logic.c main.c -o gol” para a versão paralelizada, com isso será criado um arquivo executável chamado “gol”, na sequência para executar o arquivo executável usa-se o comando “./gol config.txt”, esse comado já informa o arquivo de texto com as configurações. 

    Caso a execuções seja realizada através do Mekefile, basta usar o comando “make run”. 

O Processador utilizado nos testes, e coleta de dados para traçar a curva de escalabilidade foi o ITEL core i5-8250U, possui 4 núcleos. 

Nos testes realizados para versão serial as dimensões utilizadas para as matrizes foi 2000X2000. E a quantidade de interações foi variada nos seguintes valores: 100, 500, 1000, 5000 e 10000. A granularidade definida no código é quatro, ou seja, a grade é divididade em quatro blocos de colunas. 

Na versão paralela também foi utilizada as dimensões de matrizes 2000X2000, e a carga de trabalho foi aumentada da mesma forma que na versão serial, como o processador utilizado nos testes possuía quatro núcleos físicos a quantidade de threads foi variada em: 1,2, 4 e 6.  

Os dados de configurações estão disponíveis junto ao código no arquivo config.txt para que os testes possam ser realizados. Também estão disponíveis as imagens .pbm geradas e o arquivo de texto contendo o tempo de cada execução.

  

 