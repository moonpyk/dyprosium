#include "dhenums.h"

QString dhOptionTypeToQString (int type) {
	switch(type) {
		case subnet_mask : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Subnet Mask");
		case time_offset : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Time Offset");
		case routers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Routers");
		case time_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Time Servers");
		case ien116_name_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "IEN116 Name Servers");
		case domain_name_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Domain Name Servers");
		case log_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Log Servers");
		case cookie_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Cookie Servers");
		case lpr_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "LPR Servers");
		case impress_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Impress Servers");
		case resource_location_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Resource Location Servers");
		case host_name : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Host Name");
		case boot_size : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Boot Size");
		case merit_dump : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Merit Dump");
		case domain_name : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Domain Name");
		case swap_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Swap Server");
		case root_path : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Root Path");
		case extensions_path : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Extensions Path");
		case ip_forwarding : 
			return QT_TRANSLATE_NOOP("OptionTypes", "IP Forwarding");
		case non_local_source_routing : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Non Local source routing");
		case policy_filter : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Policy Filter");
		case max_dgram_reassembly : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Max DGRAM Reassembly");
		case default_ip_ttl : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Default IP TTL");
		case path_mtu_aging_timeout : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Path MTU Aging timeout");
		case path_mtu_plateau_table : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Path MTU Plateau table");
		case interface_mtu : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Interface MTU");
		case all_subnets_local : 
			return QT_TRANSLATE_NOOP("OptionTypes", "All Subnets Local");
		case broadcast_address : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Broadcast Address");
		case perform_mask_discovery : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Perform Mask Discovery");
		case mask_supplier : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Mask Supplier");
		case router_discovery : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Router Discovery");
		case router_solicitation_address : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Router Solicitation address");
		case static_routes : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Static Routes");
		case trailer_encapsulation : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Trailer Encapsulation");
		case arp_cache_timeout : 
			return QT_TRANSLATE_NOOP("OptionTypes", "ARP Cache timeout");
		case ieee802_3_encapsulation : 
			return QT_TRANSLATE_NOOP("OptionTypes", "IEEE802.3 encapsulation");
		case default_tcp_ttl : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Default TCP TTL");
		case tcp_keepalive_interval : 
			return QT_TRANSLATE_NOOP("OptionTypes", "TCP Keep alive interval");
		case tcp_keepalive_garbage : 
			return QT_TRANSLATE_NOOP("OptionTypes", "TCP Keep alive garbage");
		case nis_domain : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NIS Domain");
		case nis_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NIS Servers");
		case ntp_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NTP Servers");
		case vendor_encapsulated_options : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Vendor encapsulated options");
		case netbios_name_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Netbios name servers");
		case netbios_dd_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Netbios DD server");
		case netbios_node_type : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Netbios Node type");
		case netbios_scope : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Netbios Scope");
		case font_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Font Servers");
		case x_display_manager : 
			return QT_TRANSLATE_NOOP("OptionTypes", "X Display manager");
		case dhcp_parameter_request_list : 
			return QT_TRANSLATE_NOOP("OptionTypes", "DHCP parameter request list");
		case dhcp_max_message_size : 
			return QT_TRANSLATE_NOOP("OptionTypes", "DHCP max message size");
		case vendor_class_identifier : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Vendor Class identifier");
		case dhcp_client_identifier : 
			return QT_TRANSLATE_NOOP("OptionTypes", "DHCP Client identifier");
		case nwip_domain : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NWIP Domain");
		case nwip_suboptions : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NWIP Sub-options");
		case nisplus_domain : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NIS+ Domain");
		case nisplus_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NIS+ Servers");
		case tftp_server_name : 
			return QT_TRANSLATE_NOOP("OptionTypes", "TFTP server name");
		case bootfile_name : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Bootfile name");
		case mobile_ip_home_agent : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Mobile IP Home agent");
		case smtp_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "SMTP Server");
		case pop_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "POP Server");
		case nntp_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NNTP Server");
		case www_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "WWW Server");
		case finger_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Finger Server");
		case irc_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "IRC Server");
		case streettalk_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Streettalk Server");
		case streettalk_directory_assistance_server : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Streettalk directory assistance server");
		case user_class : 
			return QT_TRANSLATE_NOOP("OptionTypes", "User Class");
		case slp_directory_agent : 
			return QT_TRANSLATE_NOOP("OptionTypes", "SLP directory agent");
		case slp_service_scope : 
			return QT_TRANSLATE_NOOP("OptionTypes", "SLP service scope");
		case fqdn : 
			return QT_TRANSLATE_NOOP("OptionTypes", "FQDN");
		case relay_agent_information : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Relay Agent Information");
		case nds_servers : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NDS Servers");
		case nds_tree_name : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NDS tree name");
		case nds_context : 
			return QT_TRANSLATE_NOOP("OptionTypes", "NDS context");
		case authenticate : 
			return QT_TRANSLATE_NOOP("OptionTypes", "Authenticate");

		default: return DHOPTIONTYPE_UNKNOWN_RETVAL;
	}
}

DHOptionType dhOptionTypesArray[] = {
	subnet_mask,
	time_offset,
	routers,
	time_servers,
	ien116_name_servers,
	domain_name_servers,
	log_servers,
	cookie_servers,
	lpr_servers,
	impress_servers,
	resource_location_servers,
	host_name,
	boot_size,
	merit_dump,
	domain_name,
	swap_server,
	root_path,
	extensions_path,
	ip_forwarding,
	non_local_source_routing,
	policy_filter,
	max_dgram_reassembly,
	default_ip_ttl,
	path_mtu_aging_timeout,
	path_mtu_plateau_table,
	interface_mtu,
	all_subnets_local,
	broadcast_address,
	perform_mask_discovery,
	mask_supplier,
	router_discovery,
	router_solicitation_address,
	static_routes,
	trailer_encapsulation,
	arp_cache_timeout,
	ieee802_3_encapsulation,
	default_tcp_ttl,
	tcp_keepalive_interval,
	tcp_keepalive_garbage,
	nis_domain,
	nis_servers,
	ntp_servers,
	vendor_encapsulated_options,
	netbios_name_servers,
	netbios_dd_server,
	netbios_node_type,
	netbios_scope,
	font_servers,
	x_display_manager,
	dhcp_parameter_request_list,
	dhcp_max_message_size,
	vendor_class_identifier,
	dhcp_client_identifier,
	nwip_domain,
	nwip_suboptions,
	nisplus_domain,
	nisplus_servers,
	tftp_server_name,
	bootfile_name,
	mobile_ip_home_agent,
	smtp_server,
	pop_server,
	nntp_server,
	www_server,
	finger_server,
	irc_server,
	streettalk_server,
	streettalk_directory_assistance_server,
	user_class,
	slp_directory_agent,
	slp_service_scope,
	fqdn,
	relay_agent_information,
	nds_servers,
	nds_tree_name,
	nds_context,
	authenticate
};

DHOptionEditorType dhOptionTypeEditorType(DHOptionType type) {
	switch(type) {
		case ip_forwarding:
		case non_local_source_routing:
		case all_subnets_local:
		case perform_mask_discovery:
		case mask_supplier:
		case router_discovery:
		case trailer_encapsulation:
		case ieee802_3_encapsulation:
		case tcp_keepalive_garbage:
			return FlagEdit;

		 case routers: 
		 case time_servers: 
		 case ien116_name_servers: 
		 case domain_name_servers: 
		 case log_servers: 
		 case cookie_servers: 
		 case lpr_servers: 
		 case impress_servers: 
		 case resource_location_servers: 
		 case nis_servers: 
		 case ntp_servers: 
		 case netbios_name_servers: 
		 case netbios_dd_server: 
		 case font_servers: 
		 case x_display_manager: 
		 case nisplus_servers: 
		 case mobile_ip_home_agent: 
		 case smtp_server: 
		 case pop_server: 
		 case nntp_server: 
		 case www_server: 
		 case finger_server: 
		 case irc_server: 
		 case streettalk_server: 
		 case streettalk_directory_assistance_server: 
		 case nds_servers: 
			 return AddressListEdit;

		 case subnet_mask:
		 case swap_server:
		 case broadcast_address:
		 case router_solicitation_address:
			 return AddressEdit;

		 case policy_filter:
		 case path_mtu_plateau_table:
		 case static_routes:
		 case dhcp_parameter_request_list:
			 return StringListEdit;

		 default:
			 return StringEdit;
	}
}

