Action()
{
	
	int length, i;
	char name[20];
	char alphabet[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	lr_start_transaction("UC1_RegisterUser");
	
	
	
		lr_start_transaction("go_to_welcome_page");
	
			web_add_auto_header("Sec-Fetch-Dest", "frame");
		
			web_add_auto_header("Sec-Fetch-Mode", "navigate");
		
			web_add_auto_header("Sec-Fetch-Site", "same-origin");
		
			web_add_auto_header("Upgrade-Insecure-Requests", "1");
			
			web_reg_save_param("SID",
				"LB=MSO=SID&",
				"RB=&MSO",
				LAST);
		
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=Welcome to the Web Tours site.", LAST);
			web_url("welcome.pl", 
				"URL=http://127.0.0.1:8090/WebTours/welcome.pl?signOff=true", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);
		
			web_set_sockets_option("SSL_VERSION", "AUTO");
		
			web_add_cookie("MSO=SID&{SID}&MSO_Comments&on&MSO_ServerErrorsProb&50&MSO_ServerLoadProb&50; DOMAIN=127.0.0.1");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_auto_header("Sec-Fetch-User", "?1");
		
		lr_end_transaction("go_to_welcome_page", LR_AUTO);
		
		
		lr_think_time(5);

		
		lr_start_transaction("go_to_registrating_menu");
	
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=First time registering? Please complete the form below.", LAST);
			web_url("login.pl", 
				"URL=http://127.0.0.1:8090/WebTours/login.pl?username=&password=&getInfo=true", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/home.html", 
				"Snapshot=t2.inf", 
				"Mode=HTML", 
				LAST);
		
			web_add_auto_header("Origin", "http://127.0.0.1:8090");
		
			web_add_auto_header("Upgrade-Insecure-Requests", "1");
		
		lr_end_transaction("go_to_registrating_menu", LR_AUTO);
	
		
		lr_think_time(5);

		
		lr_start_transaction("registrating");
		
			length = rand() % 13 + 5;
			for (i=0; i <= length; i += 1)
				strncat(name,alphabet+(rand() % 52),1);
			
			lr_save_string(name,"userdata");
			
			lr_output_message("Userdata %s", "userdata");
			
	
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=invalid","Fail=Found",LAST);
//			web_reg_find("Text=Your username is taken","Fail=Found",LAST);
//			web_reg_find("Text=Thank you, <b>{userdata}</b>, for registering and welcome to the Web Tours family.", LAST);
			web_submit_data("login.pl_2", 
				"Action=http://127.0.0.1:8090/WebTours/login.pl", 
				"Method=POST", 
				"TargetFrame=info", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/login.pl", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=username", "Value={userdata}", ENDITEM, 
				"Name=password", "Value={userdata}", ENDITEM, 
				"Name=passwordConfirm", "Value={userdata}", ENDITEM, 
				"Name=firstName", "Value={firstName}", ENDITEM, 
				"Name=lastName", "Value={lastName}", ENDITEM, 
				"Name=address1", "Value={address1}", ENDITEM, 
				"Name=address2", "Value={address2}", ENDITEM, 
				"Name=register.x", "Value=40", ENDITEM, 
				"Name=register.y", "Value=13", ENDITEM, 
				LAST);
			
			web_revert_auto_header("Origin");
		
			web_revert_auto_header("Sec-Fetch-User");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Upgrade-Insecure-Requests", "1");
		
		lr_end_transaction("registrating", LR_AUTO);
		
		
		lr_think_time(5);
		
		
		lr_start_transaction("go_to_menu");
	
			web_reg_find("Text=Error","Fail=Found",LAST);
//			web_reg_find("Text=Using the menu to the left, you can search for new flights to book", LAST);
			web_url("button_next.gif", 
				"URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=menus", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/login.pl", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("go_to_menu", LR_AUTO);
		
		
		lr_think_time(5);
		
		
		lr_start_transaction("go_to_my_tickets");
	
			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_auto_header("Upgrade-Insecure-Requests", "1");
		
			web_reg_find("Text=Error","Fail=Found",LAST);
//			web_reg_find("Text=<b>Itinerary</font></b>", LAST);
			web_url("Itinerary Button", 
				"URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
		
			web_set_sockets_option("SSL_VERSION", "AUTO");
	
		lr_end_transaction("go_to_my_tickets",LR_AUTO);
		
		
//		lr_think_time(5);

		
//		lr_start_transaction("logout");
//	
//			web_add_header("Sec-Fetch-User", "?1");
//		
//			web_reg_find("Text=Error","Fail=Found",LAST);
//			web_reg_find("Text=To make reservations,please enter your account information to the left.", LAST);
//			web_url("SignOff Button", 
//				"URL=http://127.0.0.1:8090/WebTours/welcome.pl?signOff=1", 
//				"TargetFrame=body", 
//				"Resource=0", 
//				"RecContentType=text/html", 
//				"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=itinerary", 
//				"Snapshot=t4.inf", 
//				"Mode=HTML", 
//				LAST);
//	
//		lr_end_transaction("logout",LR_AUTO);
	
	

	lr_end_transaction("UC1_RegisterUser",LR_AUTO);

	return 0;
}