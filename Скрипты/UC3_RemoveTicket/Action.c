Action()
{
	int i;
	int random;
	char param[100];
	char res[100];
	
	lr_start_transaction("UC3_RemoveTicket");
	
	
	
		lr_start_transaction("go_to_welcome_page");
	
			web_add_auto_header("Sec-Fetch-Dest", "frame");
		
			web_add_auto_header("Sec-Fetch-Mode", "navigate");
		
			web_add_auto_header("Sec-Fetch-Site", "same-origin");
		
			web_add_auto_header("Upgrade-Insecure-Requests", "1");
		
			/*Correlation comment - Do not change!  Original value='138251.472579992HVVVDVApVcAiDDDDtczzHpizAHcf' Name ='userSession' Type ='ResponseBased'*/
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
		
		lr_end_transaction("go_to_welcome_page", LR_AUTO);
		
		
		lr_think_time(5);

	
		lr_start_transaction("login");
	
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
				"Name=login.x", "Value=19", ENDITEM,
				"Name=login.y", "Value=2", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);
		
			web_set_sockets_option("SSL_VERSION", "AUTO");
	
		lr_end_transaction("login",LR_AUTO);
		
		
		lr_think_time(5);

	
		lr_start_transaction("go_to_my_tickets");
	
			web_revert_auto_header("Sec-Fetch-User");
			
			web_reg_find("Text=No flights have been reserved.","Fail=Found",LAST);
			
			web_reg_save_param_ex(
			    "ParamName=FlightIDs",
			    "LB=<input type=\"hidden\" name=\"flightID\" value=\"", "RB=\"",
			    "Ordinal=all", SEARCH_FILTERS, "Scope=Body", LAST);
		
			web_reg_save_param_ex(
			    "ParamName=CGIFields",
			    "LB=<input type=\"hidden\" name=\".cgifields\" value=\"", "RB=\"",
			    "Ordinal=all", SEARCH_FILTERS, "Scope=Body", LAST);
			
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=<b>Itinerary</font></b>", LAST);
			web_url("Itinerary Button", 
				"URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("go_to_my_tickets",LR_AUTO);
		
		
		lr_think_time(5);

	
		lr_start_transaction("removing_ticket");
	
			web_add_header("Origin", "http://127.0.0.1:8090");
		
			web_add_header("Sec-Fetch-User", "?1");
			
			if (atoi(lr_eval_string("{FlightIDs_count}")) >= 3)
				random = rand() % 3 + 1;
			else
				random = rand() % atoi(lr_eval_string("{FlightIDs_count}")) + 1;
			
			
			lr_output_message("Random number is: %d", random);
			
			lr_save_string("", "fullR");
			
			for (i = 1; i <= random; i++)
				lr_param_sprintf("fullR", "%s%d=on&", lr_eval_string("{fullR}"), i);
			
			
			for (i = 1; i <= lr_paramarr_len("FlightIDs"); i++) {
			    lr_param_sprintf("fullR",
		        "%sflightID=%s&",
		        lr_eval_string("{fullR}"),
		        lr_paramarr_idx("FlightIDs",
		        i));
			    
			    lr_param_sprintf("fullR",
		        "%s.cgifields=%s&",
		        lr_eval_string("{fullR}"),
		        lr_paramarr_idx("CGIFields",
		        i));
			    
			}
			
			lr_save_string(lr_eval_string("{fullR}removeFlights.x=64&removeFlights.y=5"), "fullRequest");
		
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=we could not delete your entire itinerary","Fail=Found",LAST);
			web_reg_find("Text={FlightIDs_1}","Fail=Found", LAST);
			
			if (random >= 2)
				web_reg_find("Text={FlightIDs_2}","Fail=Found", LAST);
			if (random == 3)
				web_reg_find("Text={FlightIDs_3}","Fail=Found", LAST);
			
			web_custom_request("itinerary.pl_1",
			    "URL=http://127.0.0.1:8090/WebTours/itinerary.pl",
			    "Method=POST",
			    "Resource=0",
			    "RecContentType=text/html",
			    "Referer=http://127.0.0.1:8090/WebTours/itinerary.pl",
			    "Snapshot=t4.inf",
			    "Mode=HTTP",
			    "Body={fullRequest}",
			    LAST);
		
		lr_end_transaction("removing_ticket",LR_AUTO);
		
		
		lr_think_time(5);

		
		lr_start_transaction("logout");
	
			web_add_header("Sec-Fetch-User", "?1");
		
			web_reg_find("Text=Error","Fail=Found",LAST);
			web_reg_find("Text=To make reservations,please enter your account information to the left.", LAST);
			web_url("SignOff Button", 
				"URL=http://127.0.0.1:8090/WebTours/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=itinerary", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("logout",LR_AUTO);
	
	
	
	lr_end_transaction("UC3_RemoveTicket", LR_AUTO);

	return 0;
}