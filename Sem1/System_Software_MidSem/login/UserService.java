package org.ebay_project.ebaytester.service;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import org.ebay_project.ebaytester.model.Product;
import org.ebay_project.ebaytester.model.User;

public class UserService {

	Connection conn;

	public UserService() {

		try {
			Class.forName("com.mysql.jdbc.Driver");
			conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/ebaytest", "root", "root");
			System.out.println("connection !");
		} catch (Exception e) {
			System.out.println("Exception found" + e);
			try {
				conn.close();
			} catch (Exception ee) {
				System.out.println("Connection close error");
			}
		}
	}
// ===============================================USER LOGIN=====================================================//
	public User userLogin(String user_email, String user_password) {
		User user = null;
		PreparedStatement preparedstmnt;
		try {
			preparedstmnt = conn
					.prepareStatement("select user_email from user where user_email = ? and user_password = ?");
			preparedstmnt.setString(1, user_email);
			preparedstmnt.setString(2, user_password);
			ResultSet rs = preparedstmnt.executeQuery();
			if (rs.next())
				user = getUserDetail(rs.getString("user_email"));

		} catch (SQLException e) {
			e.printStackTrace();
		}
		return user;
	}
// ================================================USER REGISTER=================================================//
	public User userRegister(User user) {

		PreparedStatement preparedstmnt;
		if (ValidateEmailId(user.getUser_email()) == 0) {
			try {
				preparedstmnt = conn.prepareStatement(
						"INSERT INTO `user`(`user_fname`,`user_lname`,`user_email`,`user_password`,`user_country`,`user_address`,`user_city`,`user_state`,`user_pincode`,`user_phone`) VALUES (?,?,?,?,?,?,?,?,?,?)");
				preparedstmnt.setString(1, user.getUser_fname());
				preparedstmnt.setString(2, user.getUser_lname());
				preparedstmnt.setString(3, user.getUser_email());
				preparedstmnt.setString(4, user.getUser_password());
				preparedstmnt.setString(5, user.getUser_country());
				preparedstmnt.setString(6, user.getUser_address());
				preparedstmnt.setString(7, user.getUser_city());
				preparedstmnt.setString(8, user.getUser_state());
				preparedstmnt.setInt(9, user.getUser_pincode());
				preparedstmnt.setString(10, user.getUser_phone());
				int success = preparedstmnt.executeUpdate();
				if (success == 1) {
					user = getUserDetail(user.getUser_email());
					return user;
				}
			} catch (Exception e) {
				System.out.println("Exception raised!!" + e);
			}
		}
		return null;
	}
// ===================================================UPDATE ADDRESS=============================================//
	public User updateAddress(String user_email, String country, String address, String state, int pincode,
			String emailid, String mobile) {
		PreparedStatement preparedstmnt;
		ResultSet rs;
		try {
			String query = "update user set user_country=? , user_address=?, user_state=?,  user_pincode=?, user_email=?, user_phone=? where user_email=?; ";
			preparedstmnt = (PreparedStatement) conn.prepareStatement(query);
			preparedstmnt.setString(1, country);
			preparedstmnt.setString(2, address);
			preparedstmnt.setString(3, state);
			preparedstmnt.setInt(4, pincode);
			preparedstmnt.setString(5, emailid);
			preparedstmnt.setString(6, mobile);
			preparedstmnt.setString(7, user_email);

			preparedstmnt.execute();
			query = "select * from user where user_email=?";
			preparedstmnt = (PreparedStatement) conn.prepareStatement(query);
			preparedstmnt.setString(1, user_email);
			rs = preparedstmnt.executeQuery();
			if (rs.next()) {
				User user = new User(rs.getInt("user_id"), rs.getString("user_fname"), rs.getString("user_lname"), rs.getString("user_email"), rs.getString("user_password"),
						rs.getString("user_country"), rs.getString("user_address"), rs.getString("user_city"), rs.getString("user_state"), rs.getInt("user_pincode"),
						rs.getString("user_phone"), rs.getDouble("wallet_balance")); // Bhavuk changed here
				return user;
			}
		}catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
// =================================================VALIDATE EMAILID=============================================//
	public int ValidateEmailId(String user_email) {
		try {

			PreparedStatement stmt = conn.prepareStatement("Select user_email from user where user_email LIKE ?");
			stmt.setString(1, user_email);

			ResultSet rs = stmt.executeQuery();
			if (rs.next()) {
				return 1;
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return 0;
	}
// ==============================================GET USER DETAIL=================================================//
	public User getUserDetail(String user_email) {

		User user = null;
		String sql = "select * from user where user_email = ?";
		PreparedStatement preparedstatement;
		try {
			preparedstatement = conn.prepareStatement(sql);
			preparedstatement.setString(1, user_email);
			ResultSet rs = preparedstatement.executeQuery();

			if (rs.next()) {
				user = new User();
				user.setUser_id(rs.getInt(1));
				user.setUser_fname(rs.getString(2));
				user.setUser_lname(rs.getString(3));
				user.setUser_email(rs.getString(4));
				user.setUser_password(rs.getString(5));
				user.setUser_country(rs.getString(6));
				user.setUser_address(rs.getString(7));
				user.setUser_city(rs.getString(8));
				user.setUser_state(rs.getString(9));
				user.setUser_pincode(rs.getInt(10));
				user.setUser_phone(rs.getString(11));
				user.setWallet_balance(rs.getDouble("wallet_balance")); // bhavuk changed here
			}
		} catch (SQLException e) {

			e.printStackTrace();
		}
		System.out.println("GetUserProfile !");
		return user;
	}

// ==============================bhavuk changed here added method to get wallet balance==========================//

	public User getWalletBalance(int user_id) {

		User user = null;
		String sql = "select * from user where user_id = ?";
		PreparedStatement preparedstatement;

		try {
			preparedstatement = conn.prepareStatement(sql);
			preparedstatement.setInt(1, user_id);
			ResultSet rs = preparedstatement.executeQuery();

			if (rs.next()) {
				user = new User();
				user.setWallet_balance(rs.getDouble("wallet_balance")); // bhavuk changed here
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		System.out.println("GetUserWalletBalance !");
		return user;
	}
// ==============================bhavuk changed here added method toget wallet balance===========================//

	public String getUserName(int user_id) {
		String user_fname= "";
		String user_lname= "";
		
		String sql = "select * from user where user_id = ?";
		PreparedStatement preparedstatement;
		
		try {
			preparedstatement = conn.prepareStatement(sql);
			preparedstatement.setInt(1, user_id);
			ResultSet rs = preparedstatement.executeQuery();

			if (rs.next()) {
				user_fname = rs.getString("user_fname");
				user_lname = rs.getString("user_lname");				
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		//System.out.println("GetUserName!");
		return user_fname +" "+user_lname;
	}
// =======================================================TESTING============================================//
	public List<User> getalluser(){
		String sql = "select * from user";
		PreparedStatement preparedstatement;
		List<User> list = new ArrayList<>();
		//list=null;
		User u1;
		
		try {
			preparedstatement = conn.prepareStatement(sql);
			ResultSet rs = preparedstatement.executeQuery();

			while (rs.next()) {
				u1=new User();
				u1.setUser_id(rs.getInt("user_id"));
				u1.setUser_fname(rs.getString("user_fname"));
				u1.setUser_lname(rs.getString("user_lname"));
				u1.setUser_email(rs.getString("user_email"));
				u1.setUser_password(rs.getString("user_password"));
				u1.setUser_country(rs.getString("user_country"));
				u1.setUser_address(rs.getString("user_address"));
				u1.setUser_city(rs.getString("user_city"));
				u1.setUser_state(rs.getString("user_state"));
				u1.setUser_pincode(rs.getInt("user_pincode"));
				u1.setUser_phone(rs.getString("user_phone"));
				u1.setWallet_balance(rs.getDouble("wallet_balance"));
				list.add(u1);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		//System.out.println("GetUserName!");
		return list;
	}
}
// ================================================END OF CODE===================================================//