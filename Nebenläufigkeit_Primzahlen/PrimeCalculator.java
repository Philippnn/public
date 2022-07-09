package de.eva.Nebenläufigkeit_Primzahlen;

import java.util.ArrayList;

public class PrimeCalculator implements Runnable {
	
	private int firstValue;
	private int lastValue;
	// Primzahlen in Liste speichern
	private ArrayList<Integer> primes = new ArrayList<>();
	
	public PrimeCalculator(int firstValue, int lastValue) {
		this.firstValue = firstValue;
		this.lastValue = lastValue;
	}
	
	public void getPrimesUntil(){	
		if (firstValue < 3){
			this.primes.add(2);
			firstValue = 3;
		}
		if (firstValue % 2 == 0){
			// nur ungerade Zahlen pruefen
			firstValue += 1;
		}
		int number = firstValue;
		int factor = 3;
		do {
			factor = 3;
			while (factor < number) {
				if (number % factor == 0) {
					break;
				}
				factor++;
			}			
			if (factor == number) {			
				this.primes.add(number);
			}			
			number = number + 2;
		} while (number <= lastValue);				
	}
	
	@Override
	public void run() {
		getPrimesUntil();
	}
	
	public ArrayList<Integer> getPrimes(){
		return this.primes;
	}
		
	public static void main(String args[]) {
		// Beispiel sequentielle Verarbeitung
		PrimeCalculator primcalc = new PrimeCalculator(0, 100000);
		
		long startTime = System.currentTimeMillis();
		primcalc.getPrimesUntil();
		long endTime = System.currentTimeMillis();
		
		System.out.println("Dauer: " + (endTime - startTime) + "ms");


	}
}
