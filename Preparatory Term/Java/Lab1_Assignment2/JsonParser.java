import java.util.*;
import java.io.*;

public class JsonParser{
	public static void main(String[] args){
	try{
		StringBuffer jsonString = new StringBuffer();
		FileReader fr = new FileReader(args[0]);
		int i;
	        while ((i=fr.read()) != -1)
	      	    jsonString.append((char)i);
		System.out.println("File read");
		System.out.println(jsonString.substring(0));
		ArrayList<JsonObject> objStack = new ArrayList<JsonObject>();
		ArrayList<Character> braceStack = new ArrayList<Character>();
		JsonObject marker = new JsonObject();		
		String jsonKey ;
		int slength = jsonString.length();
		System.out.println("Json Size - " + slength);
		int iter = 0;
		StringBuffer key = new StringBuffer();
		JsonObject popObject, pushObject;
		ArrayList<JsonObject> lstJsonObject = new ArrayList<JsonObject>();
		while(iter < slength){
			char c = jsonString.charAt(iter); 
			if(c=='{' || c=='['){
				braceStack.add(0,c);
				objStack.add(0, marker);
			}
			else if(c=='}' || c==']'){
				if(key.substring(0).trim() != ""){
					popObject = objStack.remove(0);
					popObject.addValue(key.substring(0).trim());
					objStack.add(0,popObject);
					key.delete(0, key.length());
				}
				while(true){
					popObject = objStack.remove(0);
					if(popObject.getValue() == null){
						break;
					}
					else{
						lstJsonObject.add(0,popObject);
					}
				}
				System.out.println("Json Size - " + lstJsonObject.size() );
				if(objStack.size() == 0){
					break;
				}
				popObject = objStack.remove(0);
				for(JsonObject jsonObject : lstJsonObject){
					popObject.addValue(jsonObject);
				}
				lstJsonObject.clear();
				objStack.add(0,popObject);
				braceStack.remove(0);
			}
			else if(c==':'){
				jsonKey = key.substring(0).trim();
				pushObject = new JsonObject(jsonKey);
				objStack.add(0,pushObject);
				key.delete(0, key.length());
			}
			else if(c==','){
				if(key.substring(0).trim() != ""){
					popObject = objStack.remove(0);
					popObject.addValue(key.substring(0).trim());
					objStack.add(0,popObject);
					key.delete(0, key.length());
				}
			}
			else{
				key.append(c);
			}
			iter++;
		}
		System.out.println("Json Parsed");
		HashMap<String,JsonObject> hashMap = new HashMap<String,JsonObject>();
		for(JsonObject jsonObject : lstJsonObject){
			hashMap.put(jsonObject.getKeyValue(),jsonObject);
		}
		System.out.println("Enter json key to query and -1 to quit:");
		while(true){
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			String line = br.readLine();
			if((line.trim().equals("-1"))){
				break;
			}
			else{
				if(hashMap.containsKey(line.trim())){
					JsonObject value = hashMap.get(line.trim());
					System.out.println(PrintValueOfKey(value));
				}
				else{
					System.out.println("Key does not exists!!!");
				}
			}
		}
		}
		catch(Exception ex){
			System.out.println("Exception");
		}
	}
	
	public static String PrintValueOfKey(JsonObject object){
		StringBuffer result = new StringBuffer();
		ArrayList<Object> lstValue = object.getValue();
		result.append("[" + object.getKeyValue() + ":");
		for(Object obj: lstValue){
			if (obj != null && (obj instanceof String)){
				result.append(obj);
			}
			else{
				result.append(PrintValueOfKey((JsonObject)obj));
			}
		}
		result.append( "]");
		return result.substring(0).trim();
	}
}
