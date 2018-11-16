//=================================================AJAX CALL FOR STORE A REGISTER DATA IN DATABASE=====================================//
$('#register_form').submit(function(){
		var myobj={"user_id":0,
               "user_fname":$('#text1').val(),
						   "user_lname":$('#text2').val(),
						   "user_email":$('#user_email').val(),
						   "user_password": $('#user_password').val(),
						   "user_country":"",
						   "user_address":"",
						   "user_city":"",
					     "user_state":"",
						   "user_pincode":8888,
					     "user_phone":""
							};
			   var myjson=JSON.stringify(myobj);
			   console.log(myjson);

			   $.ajax({
							  	type :"POST",
								  url: "http://localhost:5224/ebaytester/webapi/user/register",
								  data : myjson,
								  contentType: "application/json;",
								  success: function(response){
													console.log(response)
				 									if(response!=null)
														  {localStorage.clear();
														   localStorage.user_Id=response.user_id;
														   localStorage.fName=response.user_fname;
														   localStorage.lName=response.user_lname;
														   localStorage.email=response.user_email;
														   localStorage.user_PINCODE=8888;
														   window.location="http://localhost:5224/ebaytester/home.html";
														  }
													  else
														  {
														   alert("already exist");
													     window.location="http://localhost:5224/ebaytester/register.html";
														  }
											  }
			 	});

			  return false;
		  });
//=======================================================================END OF CODE==================================================//
