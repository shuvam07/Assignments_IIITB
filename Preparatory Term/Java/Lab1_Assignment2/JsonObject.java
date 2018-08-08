import java.util.*;
public class JsonObject{

	private String key;
	private ArrayList<Object> value;

	public JsonObject(){}

	public JsonObject(String key){
		this.key = key;
		this.value = new ArrayList<Object>();
	}

	public JsonObject(String key, ArrayList<Object> value){
		this.key = key;
		this.value = new ArrayList<Object>();
		this.value.addAll(value);
	}
	
	public ArrayList<Object> getValue(){
		return this.value;
	}

	public String getKeyValue(){
		return this.key;
	}

	public String getPair(){
		return "[" + this.key + ":" + this.value.get(0) + "]";
	}

	public void addValue(Object value){
		this.value.add(value);
	}
}
