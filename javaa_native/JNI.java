package javaa_native;

public class JNI {

	static {
		System.load("C:\\Users\\PC\\eclipse-workspace\\HelloFX3\\src\\javaa_native\\nat.dll");
	}
	
	public native String dajKomandu(String str, char dn, String str2, String str3);
	public native String citajTabele(String str2, String str3);
	
	public static void main(String[] args) {
		
	}

}
