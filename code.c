	tipoLista* auxlista= transacoes;
	tipoTransacao* auxtransacao;
	tipoLista* auxlistaoperacao;
	tipoOperacao * auxoperacao;

    while (auxlista != NULL)
	{
		auxtransacao = auxlista->item;
		auxlistaoperacao = auxtransacao->operacoes;
		auxoperacao = auxlistaoperacao->item;

		while (auxlistaoperacao != NULL)
		{
			if (auxoperacao->tipo == 'W')
			{
				printf("tipo escrita | Tempo de chegada : %d \n", auxoperacao->tempoChegada);
				//criaArestas();
				//aqui inicia a verificação

			}
			auxlistaoperacao = auxlistaoperacao->proximo;
			if (auxlistaoperacao != NULL)
			{
				auxoperacao = auxlistaoperacao->item;
			}	
		}	
		auxlista = auxlista->proximo;
	}

    		anterior = linhaTempo->anterior->item;
				if((anterior->atributo == auxop->atributo) && (anterior->tipo == 'W'||anterior->tipo == 'R')){
					printf("escrita depois de escrita ou leitura \n");
					criaArestas(verificaLista(transacoes,auxop->id),verificaLista(transacoes,anterior->id));
				}
                				proximo = linhaTempo->proximo->item;
				if (proximo->tipo == 'R' && (proximo->atributo == auxop->atributo))
				{
					printf("escrita antes de leitura \n");
					criaArestas(verificaLista(transacoes,auxop->id),verificaLista(transacoes,proximo->id));
				}


if (auxop->tipo == 'W')
		{	
			if (auxlista->anterior != NULL)
			{
				id = testeescrita(auxlista,auxop);
			
			}
			else if (auxlista->proximo != NULL)
			{
				id = testeescrita2(auxlista,auxop);
				if (id != -1)
				{
					criaArestas(verificaLista(transacoes,auxop->id),verificaLista(transacoes,id));
				}
			}	
		}
		