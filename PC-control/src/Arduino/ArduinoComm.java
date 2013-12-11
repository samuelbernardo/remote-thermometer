package Arduino;

import java.io.DataInputStream;
import java.io.IOException;

import javax.swing.plaf.basic.BasicBorders.SplitPaneBorder;

import ArduinoFunctions.*;

public class ArduinoComm extends SerialComm
{
	
	public ArduinoComm()
	{
		
	}
	
	public static void main(String[] args)
	{
		int paylod=0;
		String ch = "0";
		DataInputStream teclado = new DataInputStream(System.in);  
		
		while(!ch.equals("exit")){
				
			try {
				ch = teclado.readLine();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			SerialCommLeitura leitura = new SerialCommLeitura("COM8", 9600, 0);
			leitura.HabilitarEscrita();
	        leitura.ObterIdDaPorta();
	        leitura.AbrirPorta();
	        
				if(ch.equals("Sensor1")){
					leitura.EnviarUmaString("1");
					System.out.print("Luminosidade:");
				}else
				if(ch.equals("Sensor2")){
					leitura.EnviarUmaString("2");
					System.out.println("Temperatura Sensor TMP36:");
				}else
				if(ch.equals("Sensor3")){
					leitura.EnviarUmaString("2");
					System.out.println("Temperatura Sensor INM-0616 (Thermistor 20K):");
				}else
				if(ch.contains("Set")){
					String str0[]=ch.split(" ");
					String str[]=str0[1].split("=");
					
					if(str[0].equals("T1"))str0[0]="4";
					if(str[0].equals("T2"))str0[0]="5";
					if(str[0].equals("T3"))str0[0]="6";
					if(str[0].equals("T4"))str0[0]="7";
					
					if(str.length>1 && str.length < 3 && (str0[0].equals("4") || str0[0].equals("5") || str0[0].equals("6") || str0[0].equals("7"))){
						System.out.println(str[1].length());
						if(str[1].length()==4) {
							leitura.EnviarUmaString(str0[0]+str[1]);	
							System.out.println(str0[0]+str[1]);
						}else
						if(str[1].length()==3) {
							leitura.EnviarUmaString(str0[0]+"0"+str[1]);	
							System.out.println(str0[0]+"0"+str[1]);
							}else
							if(str[1].length()==2) {
								leitura.EnviarUmaString(str0[0]+"00"+str[1]);	
								System.out.println(str0[0]+"00"+str[1]);
								}else
								if(str[1].length()==1) {
									leitura.EnviarUmaString(str0[0]+"000"+str[1]);	
									System.out.println(str0[0]+"000"+str[1]);
									}else{
									System.out.println("Valor introduzido fora dos limites\n");
									}
					}else{
						System.out.println("Valor introduzido fora dos limites\n");
					}	
				}else{
					leitura.EnviarUmaString(ch);
				}
	        leitura.HabilitarLeitura(); 
	        leitura.LerDados();
	        try {
	            Thread.sleep(1000);
	        } catch (InterruptedException ex) {
	            System.out.println("Erro na Thread: " + ex);
	        }
	        leitura.FecharCom();
		}
	}
}

