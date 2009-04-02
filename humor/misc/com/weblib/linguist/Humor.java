package com.weblib.linguist;

import java.util.*;

import java.io.*;

/**
 * A JNI wrapper for HUMOR (High-speed Unification MORphology) provided by
 * Morphologic Kft.
 * 
 * Author: Istvan Endredy
 * 
 * Modified by: Endre
 **/

public class Humor {
	private static int _stemmingId = -1;

	private static int _generateId = -1;

	private static int _generateWFormsId = -1;

	private static boolean _initialized = false;

	/**
	 * 
	 * Loads the JNI library, if available.
	 * 
	 * <br>
	 * <br>
	 **/

	public static void initialize(String directory, int languageCode)
			throws Throwable {
		System.out.println("Humor init:" + directory + " languageCode:"
				+ languageCode);
		System.loadLibrary("humor2java");
		// directory = directory.replace('/','\\');
		_stemmingId = init(directory, languageCode, 1);
		System.out.println("_stemmingId: " + _stemmingId + " " + directory);
		_generateId = init(directory, languageCode, 2);
		System.out.println("_generateId: " + _generateId);
		_generateWFormsId = init(directory, languageCode, 3);
		if (_stemmingId != -1 && _generateId != -1 && _generateWFormsId != -1) {
			_initialized = true;
			System.out.println("Initialized!");
		}
	}

	public static boolean isInitialized() {

		return _initialized;

	}

	public static int closeMorph(int ids) {
		try {
			return close(ids);
		} catch (UnsatisfiedLinkError x) {
			System.err.println("UnsatisfiedLinkError: " + x.getMessage());
			return -100;
		}
	}

	public static int closeStemming() {
		return closeMorph(_stemmingId);
	}

	public static int closeWordGenerating() {
		return closeMorph(_generateId);
	}

	public static int closeWordFormsGenerating() {
		return closeMorph(_generateWFormsId);
	}	

	public static String[] getStem(String word) {
		try {
			return stem(_stemmingId, word);
		} catch (UnsatisfiedLinkError x) {
			System.err.println("UnsatisfiedLinfkError: " + x.getMessage());
			return null;
		}
	}

	public static String[] getAnalyze(String word) {
		try {
			return analyze(_stemmingId, word);
		} catch (UnsatisfiedLinkError x) {
			System.err.println("UnsatisfiedLinkError: " + x.getMessage());
			return null;
		}
	}

	public static String[] getWordGenerate(String word) {
		try {
			return generate(_generateId, word);
		} catch (UnsatisfiedLinkError x) {
			System.err.println("UnsatisfiedLinkError: " + x.getMessage());
			return null;
		}
	}

	public static String[] getWordForms(String word, int limit) {
		try {
			return generateWordForms(_generateWFormsId, word, limit);
		} catch (UnsatisfiedLinkError x) {
			System.err.println("UnsatisfiedLinkError: " + x.getMessage());
			return null;
		}
	}

	public static String[] getSyns(String word, int context_size) {
		try {
			return getSynonims(_stemmingId, word, context_size);
		} catch (UnsatisfiedLinkError x) {
			return null;
		}
	}

	public static void TestError(String word, int limit) {
		String[] forms;
		forms = getWordForms(word, limit);
		if (forms != null) {
			System.out.println("\ngenerating " + limit + " word forms of \""
					+ word + "\"");
			for (int i = 0; i < forms.length; i++) {
				System.out.println(" " + forms[i]);
			}
		}
	}

	/**
	 * 
	 * Cant instantiate (Singleton design pattern)
	 **/

	private Humor() {

	}

	// /////////////////////////////////////////////////////////////////////////////////////

	// Private

	//

	private synchronized static native int init(String directory,
			int language_code, int mode) throws UnsatisfiedLinkError;

	private synchronized static native int close(int id)
			throws UnsatisfiedLinkError;

	private synchronized static native String[] stem(int id, String word)
			throws UnsatisfiedLinkError;

	private synchronized static native String[] analyze(int id, String word)
			throws UnsatisfiedLinkError;

	private synchronized static native String[] generate(int id, String word)
			throws UnsatisfiedLinkError;

	private synchronized static native String[] generateWordForms(int id,
			String word, int limit) throws UnsatisfiedLinkError;

	private synchronized static native String[] getSynonims(int id,
			String word, int context_size) throws UnsatisfiedLinkError;

	static public void main(String args[]) {

		List strings = new ArrayList();

		try {
			System.out.println("start reading");

			BufferedReader in = new BufferedReader(new InputStreamReader(
					new FileInputStream("in.txt"), "UTF-16"));

			while (in.ready()) {

				String str = in.readLine();
				System.out.println("reading" + str);

				strings.add(str);

			}

			System.out.println("file loaded");

		} catch (UnsupportedEncodingException e) {
			System.out.println("UnsupportedEncodingException ");

		} catch (IOException e) {
			System.out.println("io error");

		}

		// Initialize JNI extension

		String lexicon_directory = new String("."); // current dir

		int lang_code = 1038;

		// int codePage = 852;

		try {

			Humor.initialize(lexicon_directory, lang_code);

		} catch (Throwable e) {

			System.out.println("There is a problem with the Humor library: "
					+ e);

			return;

		}

		if (_stemmingId == -100) {

			System.out.println("Could not load the \"init\"!");

			return;

		} else if (_stemmingId == -1) {

			System.out
					.println("Error in \"init\"! (is lexicon path correct? timelimit?)");

			return;

		}

		System.out.println(" _stemmingId: " + _stemmingId);

		System.out.println(" _generateId: " + _generateId);

		System.out.println(" _generateWFormsId: " + _generateWFormsId);

		try {

			String[] stems;
			String[] syns;

			Iterator iter = strings.iterator();

			BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
					new FileOutputStream("out.txt"), "UTF-16"));

			while (iter.hasNext()) {

				String word = (String) iter.next();
				System.out.println("stemming " + word);

				stems = Humor.getStem(word);
				// stems = Humor.getAnalyze(word);

				if (stems != null) {

					for (int i = 0; i < stems.length; i++) {
						System.out.println(stems[i] + " (" + stems[i].length()
								+ ")");
						out.write(word + ":" + stems[i]);
						out.newLine();

					}

				} else
					System.out.println("stems == null");

				syns = Humor.getSyns(word, 0);

				if (syns != null) {

					System.out.println("\nsyns of \"" + word + "\"");

					for (int i = 0; i < syns.length; i++)

					{

						System.out.println(" " + syns[i].toString());
						out.write(" " + word + ":" + syns[i]);
						out.newLine();

					}

				}

			}

			out.close();

		} catch (UnsupportedEncodingException e) {

		} catch (IOException e) {

		}

		String word = new String("technik");
		String[] stems;

		stems = Humor.getStem(word);
		if (stems != null) {

			System.out.println("\nstems of \"" + word + "\"");

			for (int i = 0; i < stems.length; i++)

			{

				System.out.println(" " + stems[i]);

			}

		}

		word = "kehely[FN][PL][NOM]";

		String[] gens;

		gens = Humor.getWordGenerate(word);

		if (gens != null) {

			System.out.println("\ngenerating word for \"" + word + "\"");

			for (int i = 0; i < gens.length; i++)

			{

				System.out.println(" " + gens[i]);

			}

		}

		word = "kutya";

		gens = Humor.getWordForms(word, 10);

		if (gens != null) {

			System.out.println("\ngenerating word forms for \"" + word + "\"");

			for (int i = 0; i < gens.length; i++)

			{

				System.out.println(" " + gens[i]);

			}

		}

		/*
		 * String []forms; int limit = 4;
		 * 
		 * //sz�l�s ut�n hashajt�t kaptam word = "�rem";
		 * 
		 * Humor.TestError(word, limit); word = "ut�n";
		 * 
		 * word = "hashajt�t"; word = "kaptam";
		 */

		int err = Humor.closeMorph(_stemmingId);

		err = Humor.closeMorph(_generateId);

		err = Humor.closeMorph(_generateWFormsId);

		if (err == -100) {

			System.out.println("Could not load the \"close\"!");

			return;

		}

	}

}
