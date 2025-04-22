# Game of Life 

O game of life é um autônomo celular cria do pelo britânico John Conway, consiste em um jogo que funciona sem a interação com o usuário, possui a formato de matriz na qual cada célula pode estar em dois estados, vivas ou mortas. Para que o jogo possa ser executado de forma correta é necessário que seja definido um estado inicial especificando quais células devem estar vivas no início do jogo, então a partir do estado inicial são aplicadas as seguintes regras: 1- As células vivas que possuírem menos de dois vizinhos vivos morrem por subpopulação. 2- As células vivas que possuírem exatamente dois vizinhos ou três, vivem para a próxima geração. 3- As células vivas que possuírem quatro vizinhos ou mais morrem por superpopulação. 4- As células mortas com exatamente três vizinhos vivos, vivem para próxima geração. 

### Trabalho realizado 

No presente trabalho o game of life foi adaptado a partir da versão encontrada no You Tube, no canal Cobb Coding (disponivel no link: https://youtu.be/I0ndY1Y4avQ?si=83_91MV9NTf4Gh53). 



As seguintes adaptações foram realizadas: a interface gráfica exibida no terminal foi removida, foi adicionada a funcionalidade de gerar imagens .pmb com capturas dos estados do jogo, outra saída do jogo será um arquivo de texto com o tempo real de execução em segundos. Além disso, será utilizado um arquivo de texto para configurar o jogo. Estão disponíveis aqui duas versões na primeira o código foi implementado de forma serial e na segunda de forma paralela usando openMP.  

### Arquivos do projeto 

O projeto está organizado em seis arquivos: config.txt, este arquivo é responsável por passar parâmetros de entrada para a execução do software, nele são especificados quatro paramentos para a versão serial, separados por um espaço simples, os parâmetros são respectivamente, a altura da matriz, a largura da matriz, a quantidade de interações que serão realizadas, e o intervalo de interações para a capitara da imagem. Na versão paralela, além dos parâmetros mencionados para versão serial, um outro parâmetro será passado no arquivo de configuração, a quantidade de threads usadas. 

Main.c, este é o arquivo no qual está a função principal, esta função é a primeira a ser chamada ao executar o código, ela realiza a leitura do arquivo index.txt e pega as os dados contidos nele, e utiliza para fazer a comunicação com as funções que estão em outros arquivos fazendo o jogo funcionar. Além disso é na função main, é calculado o tempo real de execução e salvo em um arquivo de texto. 

Image.c, este arquivo possui o código responsável por gerar as imagens .pbm, e salvá-las. 

grid.c, este arquivo possui o código que gera matriz na qual ocorre todas as interações do jogo. 

gol.h, este arquivo é responsável por fazer a conexão entre os demais arquivos. 

### Implementação da versão paralela 

Na versão paralela o quadro foi dividido em colunas e atribuído um pacote de colunas adjacentes para cada tarefa. Como o quadro manteve uma largura fixa durante todos os testes, essa largura foi dividida de forma proporcional a quantidade de threads, para que cada thread sempre executasse um pacote de coluna com o mesmo tamanho os bem próximos. As tarefas são capazes de atualizar a placa de forma independente em qualquer lugar fora os limites da sua região de colunas. Á comunicação de bordas entre faixas de colunas realizando a comunicação entre threads isso é feito manualmente, acessando a coluna da esquerda do thread anterior e da direita do thread seguinte. 

Nesse caso a arquitetura utilizada na paralelização foi a Phase Parallel Paradigm, na qual o computo de cada pacote de colunas acontece independentemente, e ao fim todos são sincretizados antes de iniciar outro computo.  


### Como executar 

Para execução e teste foi usado a automação por meio de MekeFile, os arquivos utilizados em cada uma das versões estão disponíveis junto com o os arquivos de código. Para executar basta fazer download do código, abrir o terminal na pasta com os arquivos e usar o comando: make run.  É necessário possuir um compilador para código c na máquina e suporte para OpenMP. 

O Processador utilizado nos testes, e coleta de dados para traçar a curva de escalabilidade foi o ITEL core i5-8250U, possui 4 núcleos. 

Nos testes realizados para versão serial as dimensões utilizadas para as matrizes foi 1000X1000. E a quantidade de interações foi variada nos seguintes valores: 250, 500, 1000, 2000, 4000, 8000, 16000. 

Na versão paralela também foi utilizada as dimensões de matrizes 1000X1000, e a carga de trabalho foi aumentada da mesma forma que na versão serial, como o processador utilizado nos testes possuía quatro núcleos físicos a quantidade de threads foi variada em: 1,2, 3, 4 e 5.  

Os dados de configurações estão disponíveis junto ao código no arquivo config.txt para que os testes possam ser realizados. Também estão disponíveis as imagens .pbm geradas e o arquivo de texto contendo o tempo de cada execução. Os resultados obtidos não serão exatamente os mesmos pois o estado inicial do jogo é definido de forma aleatório no durante a execução do código. 

  

 