//=========================================================ajax call on submit the login form=====================================================//
$('#login')
		.click(
				function() {
							$.ajax({
								type : "post",
								url : "http://localhost:5224/ebaytester/webapi/user/login",
								data : $('#login_form').serialize(),
								dataType : "JSON",
								success : function(response) {
									if (response != null) {
										//localStorage.clear();
										localStorage.user_Id = response.user_id;
										localStorage.fName = response.user_fname;
										localStorage.lName = response.user_lname;
										localStorage.email = response.user_email;
										localStorage.user_Address = response.user_address;
										localStorage.user_State = response.user_state;
										localStorage.user_PINCODE = response.user_pincode;
										localStorage.user_Phone = response.user_phone;
										localStorage.wallet_balance=response.wallet_balance;
										//alert(localStorage.product_id_buynow);
										if (localStorage.email == 'admin@gmail.com') {
											window.location = "http://localhost:5224/ebaytester/admin_category.html";
										}
										
										else if(localStorage.product_id_buynow != null)
											{if(parseInt(localStorage.user_PINCODE)==8888)
												{
													window.location = "http://localhost:5224/ebaytester/address_form_buyer.html";
												}
												else{
													window.location = "http://localhost:5224/ebaytester/orderReview.html";
												}

											}
											else if(localStorage.place_order=="place_order")
												{if(parseInt(localStorage.user_PINCODE)==8888)
													{
														window.location = "http://localhost:5224/ebaytester/address_form_buyer.html";
													}
													else{
														window.location="http://localhost:5224/ebaytester/orderReviewCart.html";
													}
												}
											else if(localStorage.deal_id!=null){
												if(parseInt(localStorage.user_PINCODE)==8888)
													{
														window.location = "http://localhost:5224/ebaytester/address_form_buyer.html";
													}
													else{
														window.location = "http://localhost:5224/ebaytester/dealByName.html";
													}
											}
						
											else
											{
												window.location = "http://localhost:5224/ebaytester/home.html";
											}
									} else {
										alert("enter correct password and username");
									}
								}
							});
					return false;
				});
//===================================================================END OF CODE==================================================================//
