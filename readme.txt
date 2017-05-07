Hamer Iboshi GRR20158555

No trabalho foi utilizado a biblioteca grafviz para a leitura do arquivo .dot, e foram utilizadas funções da biblioteca para passar para minha própria estrutura de dados.
Após isso foi feita uma DFS simples que verificava se o vértice tinha sido visitado ou não, a DFS é chamada para os vizinhos não visitados e retorna os atributos desses vértices filhos (caso já foi visitado só retorna os atributos desse filho), que são comparados com os do vértice atual para saber se é um atributo novo, ou se ele já existe no vértice para poder ser somado com a quantidade do atributo deste filho.
