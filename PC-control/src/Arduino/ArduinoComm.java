package Arduino;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.ObjectInputStream.GetField;

import javax.swing.plaf.basic.BasicBorders.SplitPaneBorder;

import ArduinoFunctions.*;

public class ArduinoComm extends SerialComm
{
	
	private static final int SAVE = 2;
	private static final int QUERY = 1;
	
	public ArduinoComm()
	{
		
	}
	
	public static void main(String[] args)
	{
		int paylod=0;
		String ch = "0";
		DataInputStream teclado = new DataInputStream(System.in);  
		int Mode = QUERY;
		SerialCommLeitura leitura ;
		
		while(!ch.equals("exit")){
			switch (Mode){	
				case 1:
				
					try {
						ch = teclado.readLine();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					leitura = new SerialCommLeitura("COM8", 9600, 0);
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
								//System.out.println(str[1].length());
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
						}else
						if(ch.contains("Get T1")){
							leitura.EnviarUmaString("8");	
						}else
						if(ch.contains("Get T2")){
							leitura.EnviarUmaString("9");	
						}else
						if(ch.contains("Get T3")){
							leitura.EnviarUmaString("10");	
						}else
						if(ch.contains("Get T4")){
							leitura.EnviarUmaString("11");	
						}else
							if(ch.contains("Mode = SAVE")){				/*Comando para entrar em modo SAVE*/
								//Mode = SAVE;
								leitura.EnviarUmaString("12");
								System.out.printf("SAVE MODE ON\n");
						}
			        leitura.HabilitarLeitura(); 
			        leitura.LerDados();
			        try {
			            Thread.sleep(1000);
			        } catch (InterruptedException ex) {
			            System.out.println("Erro na Thread: " + ex);
			        }
			        leitura.FecharCom();
			        break;
		       
				case 2:
					/*MODO SAVE
					 * criar ficheiros e guardar dados recebidos
					 */
					
					leitura = new SerialCommLeitura("COM8", 9600, 0);
					leitura.HabilitarLeitura(); 
			        leitura.ObterIdDaPorta();
			        leitura.AbrirPorta();
			        leitura.LerDados();
			    
			      
			        try {
			            Thread.sleep(1000);
			        } catch (InterruptedException ex) {
			            System.out.println("Erro na Thread: " + ex);
			        }
			        leitura.FecharCom();
					        break;
			}
		}	
	}
}


