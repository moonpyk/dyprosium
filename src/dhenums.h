#ifndef DHENUMS_H
#define DHENUMS_H

#include "sidebar_utils.h"

#include <QString>
#include <QList>

#define DHOPTIONTYPE_UNKNOWN_RETVAL "Unknown"

enum DHExclusionType {
	SimpleAdress,
	Range
};

enum DHOptionType {
	option_null = 0,
	subnet_mask = 1,
	time_offset = 2,
	routers = 3,
	time_servers = 4,
	ien116_name_servers = 5,
	domain_name_servers = 6,
	log_servers = 7,
	cookie_servers = 8,
	lpr_servers = 9,
	impress_servers = 10,
	resource_location_servers = 11,
	host_name = 12,
	boot_size = 13,
	merit_dump = 14,
	domain_name = 15,
	swap_server = 16,
	root_path = 17,
	extensions_path = 18,
	ip_forwarding = 19,
	non_local_source_routing = 20,
	policy_filter = 21,
	max_dgram_reassembly = 22,
	default_ip_ttl = 23,
	path_mtu_aging_timeout = 24,
	path_mtu_plateau_table = 25,
	interface_mtu = 26,
	all_subnets_local = 27,
	broadcast_address = 28,
	perform_mask_discovery = 29,
	mask_supplier = 30,
	router_discovery = 31,
	router_solicitation_address = 32,
	static_routes = 33,
	trailer_encapsulation = 34,
	arp_cache_timeout = 35,
	ieee802_3_encapsulation = 36,
	default_tcp_ttl = 37,
	tcp_keepalive_interval = 38,
	tcp_keepalive_garbage = 39,
	nis_domain = 40,
	nis_servers = 41,
	ntp_servers = 42,
	vendor_encapsulated_options = 43,
	netbios_name_servers = 44,
	netbios_dd_server = 45,
	netbios_node_type = 46,
	netbios_scope = 47,
	font_servers = 48,
	x_display_manager = 49,
	dhcp_parameter_request_list = 55,
	dhcp_max_message_size = 57,
	vendor_class_identifier = 60,
	dhcp_client_identifier = 61,
	nwip_domain = 62,
	nwip_suboptions = 63,
	nisplus_domain = 64,
	nisplus_servers = 65,
	tftp_server_name = 66,
	bootfile_name = 67,
	mobile_ip_home_agent = 68,
	smtp_server = 69,
	pop_server = 70,
	nntp_server = 71,
	www_server = 72,
	finger_server = 73,
	irc_server = 74,
	streettalk_server = 75,
	streettalk_directory_assistance_server = 76,
	user_class = 77,
	slp_directory_agent = 78,
	slp_service_scope = 79,
	fqdn = 81,
	relay_agent_information = 82,
	nds_servers = 85,
	nds_tree_name = 86,
	nds_context = 87,
	authenticate = 210,
};

enum DHOptionEditorType {
	StringEdit = 0,
	AddressEdit = 1,
	FlagEdit = 2,
	StringListEdit = 3,
	AddressListEdit = 4
};

extern DHOptionType dhOptionTypesArray[];

QString dhOptionTypeToQString(int type);
DHOptionEditorType dhOptionTypeEditorType(DHOptionType type);

#endif //DHENUMS_H
