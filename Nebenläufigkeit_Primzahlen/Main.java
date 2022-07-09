package de.eva.Nebenläufigkeit_Primzahlen;

public class Main {
	
	public static void main(String[] args) throws InterruptedException {
		// Erstelle Tasks fuer Intervalle
		PrimeCalculator pc1 = new PrimeCalculator(0, 25000);
		PrimeCalculator pc2 = new PrimeCalculator(25000, 50000);
		PrimeCalculator pc3 = new PrimeCalculator(50000, 75000);
		PrimeCalculator pc4 = new PrimeCalculator(75000, 100000);
		// Erstelle Threads mit Tasks
		Thread prim1 = new Thread(pc1);
		Thread prim2 = new Thread(pc2);
		Thread prim3 = new Thread(pc3);
		Thread prim4 = new Thread(pc4);
		
		// Starten der Threads
		long startTime = System.currentTimeMillis();
		prim1.start();
		prim2.start();
		prim3.start();
		prim4.start();
		// waiting state
		prim1.join();
		prim2.join();
		prim3.join();
		prim4.join();
		long endTime = System.currentTimeMillis();		
		
		// Sortierte Ausgabe der Zahlen
		for (int i : pc1.getPrimes()){
			System.out.println(i);
		}
		for (int i : pc2.getPrimes()){
			System.out.println(i);
		}
		for (int i : pc3.getPrimes()){
			System.out.println(i);
		}
		for (int i : pc4.getPrimes()){
			System.out.println(i);
		}
		
		System.out.println("Dauer: " + (endTime - startTime) + "ms");
	}
}
