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
	/* Fun��o para obter as portas dispon�veis*/
	public String[] ObterPortas()
	{
		return portas;
	}
	/* Fun��o para armazenar uma lista das portas seriais do seu sistema dispon�veis para a comunica��o*/
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
	/* Fun��o para identificar se a porta seleciona existe e est� tudo em funcionamento*/
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
