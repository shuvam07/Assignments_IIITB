package org.ebay_project.ebaytester.model;

public class User {
    private int user_id;
	private String user_fname;
	private String user_lname;
	private String user_email;
    private String user_password;
	private String user_country;
    private String user_address;
    private String user_city;
    private String user_state;
    private int user_pincode;
    private String user_phone;
    private double wallet_balance;
           
    private String user_second_country;
    private String user_second_address;
    private String user_second_city;
    private String user_second_state;
    private int user_second_pincode;
    private String user_second_phone;
    
    private float user_rating;
    private float user_rating_count;
    private float total_rating_count;
    private String card_number;
    
    public User() {
    	
    }
    
    public User(int user_id, String user_fname, String user_lname, String user_email, String user_password,
			String user_country, String user_address, String user_city, String user_state, int user_pincode,
			String user_phone, double wallet_balance) {
		super();
		this.user_id = user_id;
		this.user_fname = user_fname;
		this.user_lname = user_lname;
		this.user_email = user_email;
		this.user_password = user_password;
		this.user_country = user_country;
		this.user_address = user_address;
		this.user_city = user_city;
		this.user_state = user_state;
		this.user_pincode = user_pincode;
		this.user_phone = user_phone;
		this.wallet_balance = wallet_balance;
	}

	
	public User(int user_id, String user_fname, String user_lname, String user_email, String user_password,
			String user_country, String user_address, String user_city, String user_state, int user_pincode,
			String user_phone, double wallet_balance, String user_second_country, String user_second_address,
			String user_second_city, String user_second_state, int user_second_pincode, String user_second_phone,
			float user_rating, int user_rating_count, int total_rating_count, String card_number) {
		super();
		this.user_id = user_id;
		this.user_fname = user_fname;
		this.user_lname = user_lname;
		this.user_email = user_email;
		this.user_password = user_password;
		this.user_country = user_country;
		this.user_address = user_address;
		this.user_city = user_city;
		this.user_state = user_state;
		this.user_pincode = user_pincode;
		this.user_phone = user_phone;
		this.wallet_balance = wallet_balance;
		this.user_second_country = user_second_country;
		this.user_second_address = user_second_address;
		this.user_second_city = user_second_city;
		this.user_second_state = user_second_state;
		this.user_second_pincode = user_second_pincode;
		this.user_second_phone = user_second_phone;
		this.user_rating = user_rating;
		this.user_rating_count = user_rating_count;
		this.total_rating_count = total_rating_count;
		this.card_number = card_number;
	}


	public String getCard_number() {
		return card_number;
	}

	public void setCard_number(String card_number) {
		this.card_number = card_number;
	}

	public String getUser_second_country() {
		return user_second_country;
	}

	public void setUser_second_country(String user_second_country) {
		this.user_second_country = user_second_country;
	}

	public String getUser_second_address() {
		return user_second_address;
	}

	public void setUser_second_address(String user_second_address) {
		this.user_second_address = user_second_address;
	}

	public String getUser_second_city() {
		return user_second_city;
	}

	public void setUser_second_city(String user_second_city) {
		this.user_second_city = user_second_city;
	}

	public String getUser_second_state() {
		return user_second_state;
	}

	public void setUser_second_state(String user_second_state) {
		this.user_second_state = user_second_state;
	}

	public int getUser_second_pincode() {
		return user_second_pincode;
	}

	public void setUser_second_pincode(int user_second_pincode) {
		this.user_second_pincode = user_second_pincode;
	}

	public String getUser_second_phone() {
		return user_second_phone;
	}

	public void setUser_second_phone(String user_second_phone) {
		this.user_second_phone = user_second_phone;
	}

	public float getUser_rating() {
		return user_rating;
	}

	public void setUser_rating(float user_rating) {
		this.user_rating = user_rating;
	}

	public float getUser_rating_count() {
		return user_rating_count;
	}

	public void setUser_rating_count(int user_rating_count) {
		this.user_rating_count = user_rating_count;
	}

	public float getTotal_rating_count() {
		return total_rating_count;
	}

	public void setTotal_rating_count(int total_rating_count) {
		this.total_rating_count = total_rating_count;
	}

	public int getUser_id() {
		return user_id;
	}

	public void setUser_id(int user_id) {
		this.user_id = user_id;
	}

	public String getUser_fname() {
		return user_fname;
	}
	
	public void setUser_fname(String user_fname) {
		this.user_fname = user_fname;
	}

	public String getUser_lname() {
		return user_lname;
	}

	public void setUser_lname(String user_lname) {
		this.user_lname = user_lname;
	}

	public String getUser_email() {
		return user_email;
	}

	public void setUser_email(String user_email) {
		this.user_email = user_email;
	}

	public String getUser_password() {
		return user_password;
	}

	public void setUser_password(String user_password) {
		this.user_password = user_password;
	}

	public String getUser_country() {
		return user_country;
	}

	public void setUser_country(String user_country) {
		this.user_country = user_country;
	}

	public String getUser_address() {
		return user_address;
	}

	public void setUser_address(String user_address) {
		this.user_address = user_address;
	}

	public String getUser_city() {
		return user_city;
	}

	public void setUser_city(String user_city) {
		this.user_city = user_city;
	}

	public String getUser_state() {
		return user_state;
	}

	public void setUser_state(String user_state) {
		this.user_state = user_state;
	}

	public int getUser_pincode() {
		return user_pincode;
	}

	public void setUser_pincode(int user_pincode) {
		this.user_pincode = user_pincode;
	}

	public String getUser_phone() {
		return user_phone;
	}

	public void setUser_phone(String user_phone) {
		this.user_phone = user_phone;
	}

	public double getWallet_balance() {
		return wallet_balance;
	}

	public void setWallet_balance(double wallet_balance) {
		this.wallet_balance = wallet_balance;
	}

	public void setUser_rating_count(float user_rating_count) {
		this.user_rating_count = user_rating_count;
	}

	public void setTotal_rating_count(float total_rating_count) {
		this.total_rating_count = total_rating_count;
	}
}