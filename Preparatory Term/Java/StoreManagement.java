import java.util.*;

class Store{
	
	List<Bakery> bakery;
	List<Dairy> dairy;
	int totalBakery;
	int totalDairy;
	int currBakery;
	int currDairy;
	List<String> bakeryItems;
	List<String> dairyItems;
	int orderNo;
	
	Store(int b,int d){
		this.totalBakery = b;
		this.totalDairy = d;
		bakery = new ArrayList<Bakery>(b);
		for(int i=0;i<b;i++) {
			this.bakery.add(new Bakery());
		}
		
		dairy = new ArrayList<Dairy>(d);
		for(int i=0;i<d;i++) {
			this.dairy.add(new Dairy());
		}
		this.currBakery = 0;
		this.currDairy = 0;
		this.bakeryItems = Arrays.asList("bread","cakes","muffins");
		this.dairyItems = Arrays.asList("milk","butter");
	}

	public void placeOrder(int orderNo,String item, int quan) {
		
		if(this.bakeryItems.contains(item)){
			this.bakery.get(this.currBakery).placeOrder(orderNo,item,quan);
			nextBakery();
		}
		else {
			this.dairy.get(this.currDairy).placeOrder(orderNo,item,quan);
			nextDairy();
		}
		
	}
	
	public void printAllOrders() {
		
		for(int i = 0;i < this.totalBakery; i++) {
			List<Order> od = bakery.get(i).getAllOrders();
			if(od.size()>=1) {
				System.out.println("Bakery"+(i+1));
				for(int j = od.size()-1; j >= 0; j--) {
					Order or = od.get(j);
					System.out.println(or.getOrderNo() + " "+ or.getItem() + " " + or.getQuan());
				}
			}
			System.out.println();
		}
		
		for(int i = 0;i < this.totalDairy; i++) {
			List<Order> od = dairy.get(i).getAllOrders();
			if(od.size()>=1) {
				System.out.println("Dairy"+(i+1));
				for(int j = od.size()-1; j >= 0; j--) {
					Order or = od.get(j);
					System.out.println(or.getOrderNo() + " "+ or.getItem() + " " + or.getQuan());
				}
			}
			System.out.println();
		}
	}
	
	private void nextBakery() {
		this.currBakery = (this.currBakery + 1) % this.totalBakery;
	}
	
	private void nextDairy() {
		this.currDairy = (this.currDairy + 1) % this.totalDairy;
	}
}

class Bakery{
	
	List<Order> od;
	
	Bakery(){
		od  = new ArrayList<Order>();
	}
	
	public void placeOrder(int orderNo,String item,int quan) {
		od.add(new Order(orderNo,item,quan));
	}
	
	public List<Order> getAllOrders(){
		return od;
	}
}

class Dairy{
	
	List<Order> od;
	
	Dairy(){
		od  = new ArrayList<Order>();
	}
	
	public void placeOrder(int orderNo,String item,int quan) {
		od.add(new Order(orderNo,item,quan));
	}
	
	public List<Order> getAllOrders(){
		return od;
	}
}

class Order{
	
	int orderNo;
	String item;
	int quan;
	
	Order(int orderNo,String item,int quan){
		this.orderNo = orderNo;
		this.item = item;
		this.quan = quan;
	}
	
	public int getOrderNo() {
		return this.orderNo;
	}
	
	public String getItem() {
		return this.item;
	}
	
	public int getQuan() {
		return this.quan;
	}
}

public class StoreManagement {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		int bakery = sc.nextInt();
		int dairy = sc.nextInt();
		
		int orderNo = 1;
				
		Store st =new Store(bakery,dairy);
		
		while(true) {
			
			String item = sc.next();
			if(item.equals("End"))
				break;
			
			int quan = sc.nextInt();
						
			st.placeOrder(orderNo,item.toLowerCase(),quan);
			orderNo++;
			
		}
		st.printAllOrders();
		sc.close();

	}

}
