Action()
{
	lr_start_transaction("UC4_SearchTickets");
	
	

		lr_start_transaction("go_to_welcome_page");
		
			web_add_auto_header("Sec-Fetch-Dest", "frame");
		
			web_add_auto_header("Sec-Fetch-Mode", "navigate");
		
			web_add_auto_header("Sec-Fetch-Site", "same-origin");
		
			web_add_auto_header("Upgrade-Insecure-Requests", "1");	
			
			/*Correlation comment - Do not change!  Original value='138250.081895504HVVVcDipfiHftczzHptDVfcf' Name ='userSession' Type ='ResponseBased'*/
			web_reg_save_param_regexp(
				"ParamName=userSession",
				"RegExp=userSession\\ value=(.*?)>",
				"Ordinal=3",
				SEARCH_FILTERS,
				"Scope=Body",
				"RequestUrl=*/nav.pl*",
				LAST);
				
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
		
			web_add_cookie("MSO=SID&{SID}&MSO_Comments&on&MSO_ServerErrorsProb&50&MSO_ServerLoadProb&50; DOMAIN=127.0.0.1");
		
			web_set_sockets_option("SSL_VERSION", "AUTO");
		
		lr_end_transaction("go_to_welcome_page", LR_AUTO);
		
		
		lr_think_time(5);

	
		lr_start_transaction("login");
	
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", "http://127.0.0.1:8090");
		
			web_add_auto_header("Sec-Fetch-User", "?1");
		
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=Welcome, <b>{username}</b>, to the Web Tours reservation pages.", LAST);
			web_submit_data("login.pl", 
				"Action=http://127.0.0.1:8090/WebTours/login.pl", 
				"Method=POST", 
				"TargetFrame=body", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/nav.pl?in=home", 
				"Snapshot=t2.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=userSession", "Value={userSession}", ENDITEM, 
				"Name=username", "Value={username}", ENDITEM, 
				"Name=password", "Value={password}", ENDITEM, 
				"Name=login.x", "Value=36", ENDITEM, 
				"Name=login.y", "Value=9", ENDITEM, 
				"Name=JSFormSubmit", "Value=off", ENDITEM, 
				LAST);
	
		lr_end_transaction("login",LR_AUTO);
		
		
		lr_think_time(5);

	
		lr_start_transaction("go_to_flights");
	
			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_auto_header("Upgrade-Insecure-Requests", "1");
			
			web_reg_save_param_regexp("ParamName=Cities", "RegExp=>(.*?)</option>", "Ordinal=All", LAST);
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=Find Flight", LAST);
			web_url("Search Flights Button", 
				"URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=search", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("go_to_flights",LR_AUTO);
		
		
		lr_think_time(5);

	
		lr_start_transaction("input_data_to_find_tickets");
	
			web_add_header("Origin", "http://127.0.0.1:8090");
		
			web_add_header("Sec-Fetch-User", "?1");
			
			lr_save_string(lr_paramarr_random("Cities"), "depart");
			lr_save_string(lr_paramarr_random("Cities"), "arrive");
			
			lr_output_message("Depart city: %s", "depart");
			lr_output_message("Arrive city: %s", "arrive");
			
			while (strcmp(lr_eval_string("depart"), lr_eval_string("arrive")) == 0)
				lr_save_string(lr_paramarr_random("Cities"), "arrive");
			
			lr_output_message("Depart city: %s", "depart");
			lr_output_message("Arrive city: %s", "arrive");
		
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=$ 0","Fail=Found",LAST);
			web_reg_find("Text=Find Flight", LAST);
			web_reg_find("Text=Flight departing from <B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>", LAST);
			web_reg_save_param_regexp("ParamName=outboundFlight","RegExp=outboundFlight\\svalue=(.*?)[>\\s]","Ordinal=all",LAST);
			web_submit_data("reservations.pl", 
				"Action=http://127.0.0.1:8090/WebTours/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/reservations.pl?page=welcome", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=depart", "Value={depart}", ENDITEM, 
				"Name=departDate", "Value={departDate}", ENDITEM, 
				"Name=arrive", "Value={arrive}", ENDITEM, 
				"Name=returnDate", "Value={departDate}", ENDITEM, 
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=findFlights.x", "Value=61", ENDITEM, 
				"Name=findFlights.y", "Value=11", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				LAST);
	
		lr_end_transaction("input_data_to_find_tickets",LR_AUTO);
		
		
		lr_think_time(5);
		
		
		lr_start_transaction("choose_ticket");
		
			lr_save_string(lr_paramarr_random("outboundFlight"),"outboundFlightRandom");
		
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=Payment Details", LAST);
			web_submit_data("reservations.pl_2", 
				"Action=http://127.0.0.1:8090/WebTours/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/reservations.pl", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=outboundFlight", "Value={outboundFlightRandom}", ENDITEM, 
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=reserveFlights.x", "Value=62", ENDITEM, 
				"Name=reserveFlights.y", "Value=4", ENDITEM, 
				LAST);
	
		lr_end_transaction("choose_ticket",LR_AUTO);
		
		
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
	
	
	
	lr_end_transaction("UC4_SearchTickets", LR_AUTO);
	
	return 0;
}