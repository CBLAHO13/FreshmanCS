/* This program will calculate readability scores for a given text file.
  Place the text file in the working directory.
  Run the program.
  Get results. 
  
  Copyright Colleen Blaho 2013. Copyleft also Colleen Blaho 2013. 
 */
import java.util.List;
import java.util.Scanner;
import java.io.*;
import java.util.*;
import java.lang.String;


public class readabilityCalculator {
	

	public static void lineReader(List<String> linesInFile, String input){	
			Scanner fileReader = null; // have to initialize it up here or the finally block has a fit
			try { 
				File fileToRead = new File(input);
				fileReader = new Scanner(fileToRead);
				String[] parts = new String[100000];
				//unfortunately, .split() returns an array, and not a List<string> so we have to use this ugly thing for now.
				while(fileReader.hasNextLine()){
					String line = fileReader.nextLine();
					parts = line.split(" "); 
					for (String i : parts){
						linesInFile.add(i);	 //convert the half-way array into a big List<string>
							//this variable can flex as needed, since we have no idea how big this is
					}
				}
			}
			catch (FileNotFoundException e) {
				System.out.println("Your File could not be found!");
				String extension = input.substring(input.lastIndexOf(".") + 1);
				String correctExtension = "txt";
					if (!(extension.equals(correctExtension))){
						System.out.println("You have the wrong file extension on this file. Try again!");
						return;}
					else { //file is in wrong place.
						System.out.println("File not found. Ensure the file name is in this directory, and its name is spelled correctly.");
						return;}	
			}
			finally { 
				if(fileReader!=null)
					fileReader.close(); // close the data stream to prevent resource leaks.
			}
    }
	
	public static void lineAnalyzer(List<String> contents, String input){
		if (contents != null && contents.size() >= 1){ //make sure we weren't given an empty file.
			System.out.println("\nFile found.");
			System.out.println("Analyzing...");
			contents.removeAll(Arrays.asList("", null)); //remove possible empty linebreaks
			String[] contentsArray = new String[contents.size()]; 
			contentsArray = contents.toArray(contentsArray);
			int wordCount = contentsArray.length;
			for (int i = 0; i <= contentsArray.length - 1; i++){ 
				contentsArray[i] = contentsArray[i].toLowerCase(); //make sure capitalized vowels are grabbed too
				contentsArray[i] = contentsArray[i].replaceAll("e$", " ");//scrub out ending e chars
				contentsArray[i] = contentsArray[i].replaceAll("[aeiouy][aeiouy]", "a"); //scrub out "independent vowels" to count them better, replace with model syllable
				contentsArray[i] = contentsArray[i].replaceAll("[aeiouy]", "a" ); //replace all vowels with model syllable
				contentsArray[i] = contentsArray[i].replaceAll("^[^aeiouy]*$", "a"); //scrub out words with no vowels, replace with model syllable
			}
			int vowelCount = 0; //vowels determine the number of syllables
			vowelCount = vowelCounter(contentsArray, vowelCount);
			int sentenceCount = 1; //prevent a 0/0 occurrence. by default, it is one sentence since the text file is not blank.
			sentenceCount = sentenceCounter(contentsArray, sentenceCount);
			double FRES = 206.835 - 84.6 * (vowelCount) / (wordCount) - 1.015 * (wordCount) / (sentenceCount);
			double FKRA = 11.8* (vowelCount) / (wordCount) + 0.39 * (wordCount) / (sentenceCount) - 15.59;
			FlechReadingEasePrint(FRES, input); 
			FlechKincaidPrint(FKRA);
		}
		else 
		{ System.out.print("File must contain valid text.\n");} //are they trying to give us an empty file that exists?
	}
	
	public static int vowelCounter (String [] contentsArray, int vowelCount){
		for (int i = 0; i <= contentsArray.length - 1; i++){ 
			for (int j = 0; j < contentsArray[i].length(); j++) { //count important vowels by iterating through each string
			    char c = contentsArray[i].charAt(j);
			    if (c=='a') // a is the only vowel we have now!
			    	vowelCount++;    
			}	
		}
		 return vowelCount;	
	}
	
	public static int sentenceCounter (String[] contentsArray, int sentenceCount){
		for (int i = 0; i <= contentsArray.length - 1; i++){ 
			for (int j = 0; j < contentsArray[i].length(); j++) { //count important vowels by iterating through each string
			    char c = contentsArray[i].charAt(j);
			    if (c=='.')
			    	sentenceCount++; 
			    else if( c==':')
			    	sentenceCount++;
			    else if(c==';')
			    	sentenceCount++;
			    else if(c=='?')
			    	sentenceCount++;
			    else if (c=='!')
			    	sentenceCount++;    
			}	
		}
		return sentenceCount;
	}
	
	public static void FlechReadingEasePrint(double rawScore, String filename){
		String gradeLevel = "";
		//table given to us in the assignment
		if (rawScore > 91)
			gradeLevel = "a fifth grade or less";
		else if (rawScore > 81)
			gradeLevel = "a sixth grade";
		else if (rawScore > 71)
			gradeLevel = "a seventh grade";
		else if (rawScore > 66)
			gradeLevel = "an eighth grade";
		else if (rawScore > 61)
			gradeLevel = "a ninth grade";
		else if (rawScore > 51)
			gradeLevel = "a high school student";
		else if (rawScore > 31)
			gradeLevel = "a college student";
		else if (rawScore > 0)
			gradeLevel = "a college graduate";
		else
			gradeLevel = "a law school graduate";
		
		rawScore = ((int)(rawScore * 100))/100; //rounding with typecasts!
		System.out.println("\nThe file \"" + filename + "\" has Flesch Reading Ease Score index of " + rawScore + ".\n"
					 + " It requires " + gradeLevel + " education to read.");
	}
	
	public static void FlechKincaidPrint(double rawScore){
		int rawScoreInt = (int)rawScore;
		String gradeLevel;
		//table given to us in the assignment
		if (rawScoreInt > 13 || rawScoreInt == 13)
			gradeLevel = "a higher education";
		else if (rawScoreInt == 12)
			gradeLevel = "a senior";
		else if (rawScoreInt == 11)
			gradeLevel = "a junior";
		else if (rawScoreInt == 10)
			gradeLevel = "a sophmore";
		else if (rawScoreInt == 9)
			gradeLevel = "a freshman";
		else if (rawScoreInt == 8)
			gradeLevel = "an eighth grade";
		else if (rawScoreInt == 7)
			gradeLevel = "a seventh grade";
		else if (rawScoreInt == 6)
			gradeLevel = "a sixth grade";
		else if (rawScoreInt == 5)
			gradeLevel = "a fifth grade";
		else if (rawScoreInt == 4)
			gradeLevel = "a fourth grade";
		else if (rawScoreInt == 3)
			gradeLevel = "a third grade";
		else if (rawScoreInt == 2)
			gradeLevel = "a second grade";
		else if (rawScoreInt == 1)
			gradeLevel = "a first grade";
		else
			gradeLevel = "a kindergarten"; // this shouldn't print at all, mostly for error handling purposes.
		
		double rawScoreTruncated = ((int)(rawScore*100)) / 100; //round to two decimal places
		System.out.println("Its Flesch-Kincaid Grade Level Formula value is " + rawScoreTruncated + ", indicating\n it is at " + gradeLevel + " level.");
	}
	
	public static void main(String[] args) {
		Scanner mainScanner = new Scanner(System.in);
		System.out.println("Enter file name.");
		String input1 = mainScanner.nextLine();
		String sentinel = "QUIT";
		List<String> linesInFile = new ArrayList<String>();
		while (!(input1.equals(sentinel)) && input1 != null){
				lineReader(linesInFile, input1);
				lineAnalyzer(linesInFile, input1);
				System.out.println("Analysis finished. Type a new filename or QUIT.");
				linesInFile.clear(); //bit of cleanup for the next run
				System.out.println("Enter file name.");
				input1 = mainScanner.nextLine();
			}
		if (input1.equals(sentinel)) {
			if(mainScanner!=null) // close the scanner just to wrap everything in a neat bow
				mainScanner.close();
			System.out.println("QUITTING PROGRAM");
			System.exit(0);
		}
	}		
}
