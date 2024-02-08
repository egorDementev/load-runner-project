Action()
{

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("WebTours", 
		"URL=http://127.0.0.1:8090/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=images/jmeter_logo.png", "Referer=http://127.0.0.1:8090/WebTours/header.html", ENDITEM, 
		"Url=images/webtours.png", "Referer=http://127.0.0.1:8090/WebTours/header.html", ENDITEM, 
		"Url=images/in_home.gif", "Referer=http://127.0.0.1:8090/WebTours/header.html", ENDITEM, 
		LAST);

	web_add_cookie("MSO=SID&1707370084&MSO_Comments&on&MSO_ServerErrorsProb&50&MSO_ServerLoadProb&50; DOMAIN=127.0.0.1");

	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_start_transaction("login");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://127.0.0.1:8090");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	lr_think_time(4);

	web_submit_data("login.pl", 
		"Action=http://127.0.0.1:8090/WebTours/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value=138304.583556096HVVtAtcpAVzzzzzHtczitpcfcV", ENDITEM, 
		"Name=username", "Value=007", ENDITEM, 
		"Name=password", "Value=password", ENDITEM, 
		"Name=login.x", "Value=45", ENDITEM, 
		"Name=login.y", "Value=9", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("go_to_my_tickets");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(4);

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

	lr_start_transaction("go_to_flights");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	lr_think_time(10);

	web_url("Search Flights Button", 
		"URL=http://127.0.0.1:8090/WebTours/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:8090/WebTours/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_flights",LR_AUTO);

	return 0;
}