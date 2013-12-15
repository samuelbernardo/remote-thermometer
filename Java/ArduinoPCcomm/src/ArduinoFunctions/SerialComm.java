package ArduinoFunctions;

import gnu.io.CommPortIdentifier;
import java.util.Enumeration;

public class SerialComm {
	
	protected String[] portas;
	protected Enumeration listaDePortas;
	
	/* Construtor da Classe SerialComm*/
	public SerialComm()
	{
		listaDePortas = CommPortIdentifier.getPortIdentifiers();
	}
	/* Função para obter as portas disponíveis*/
	public String[] ObterPortas()
	{
		return portas;
	}
	/* Função para armazenar uma lista das portas seriais do seu sistema disponíveis para a comunicação*/
	protected void ListarPortas()
	{
		int i = 0;
		portas = new String[10];
		
		while(listaDePortas.hasMoreElements())
		{
			CommPortIdentifier ips = (CommPortIdentifier)listaDePortas.nextElement();
			portas[i]=ips.getName();
		}
	}
	/* Função para identificar se a porta seleciona existe e está tudo em funcionamento*/
	public boolean PortaExiste(String COMp)
	{
		String temp;
		boolean e = false;
		
		while(listaDePortas.hasMoreElements())
		{
			CommPortIdentifier ips= (CommPortIdentifier)listaDePortas.nextElement();
			temp = ips.getName();
			
			if(temp.equals(COMp)==true)
			{
				e = true;
				
			}
		}
		return e;
	}


}
