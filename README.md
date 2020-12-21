# Universidade Federal de Viçosa - (UFV)
### Estrutura de Dados - Trabalho 1
---
Representação e comparação de "Ragged Array" com matrizes tradicionais.

EU LI AS REGRAS

Aluno: Erick Lima Figueiredo    
MA: 98898
Disciplina: Estrutura de Dados  
Prof: Salles Vianna
UNIVERSIDADE FEDERAL DE VIÇOSA

Analisando os resultados obtidos com o experimento podemos perceber que a matriz representada no formato Tradicional
tem um melhor desempenho de modo geral, se comparado com a matriz representada no formato Ragged. Isso já era esperado, 
pois precisamos realizar diversas operações para acessar os elementos presentes em cada uma das linhas. Sendo assim, 
concluímos que a matriz no formato Tradicional é mais rápida para se realizar operações sobre as linhas pois seu acesso
é "instantâneo", porém a criação de matrizes Ragged são mais rápidas, isso se deve ao fato de que nessa representação 
alocamos um único vetor que guardará todas as linhas da matriz. Além disso, concluímos também que a matriz Ragged tem um 
melhor desempenho em matrizes que possuem poucas linhas, pois nessas situações o programa precisa consultar em qual linha
está um menor número de vezes, o que melhora seu desempenho.
