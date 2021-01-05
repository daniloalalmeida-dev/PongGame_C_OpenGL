Informações do Jogo Pong, desenvolvido por Danilo Almeida, Milena Miyoshi e Reynold Pereira, 
como parte integrante da média final do semestre, do componente Computação Gráfica.

Utilizando a linguagem C++, com OpenGL (Open Graphics Library), o jogo traz duas raquetes que rebatem uma 
primitiva criada via OpenGL.

As raquetes são manipuladas via as teclas UP / DOWN (raquete esquerda) e F1 / F2 (raquete direita).

A primitiva, assim como as raquetes estão coloridas utilizando um mix de cores com base RGB, que se alteram
ao tocar a parte superior e inferior da tela ou as laterias, como determinado na descrição da atividade.

O tamanho da janela do jogo pode ser alterada ou maximizada.

Ao rebater a primitiva, há uma aceleração da mesma em seus eixos X e Y, a fim de tornar o jogo mais difícil.

Ao se atingir 10 pontos, a acelaração em X é cancelada, impossibilitando o jogo e determinando o final da partida.

O player vencedor será apresentado na tela, assim como o resultado da partida.

Para demonstração de iluminação, foram aplicadas duas posições de luz, sendo:
posicaoLuz1[4]={x = 100.0, y = 150.0, z = 100.0, 1.0}; Esta luz especular na cor branca;
posicaoLuz2[4]={x = 100.0, y = 70.0, z = 100.0, 1.0}; Esta luz especular na cor azul;

Alguns "bugs" podem sugir devido a variação numerica da posição da primitiva x1.

