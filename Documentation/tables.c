/* DHCP Option names, formats and codes, from RFC1533.

   Format codes:

   I - IP address
   l - 32-bit signed integer
   L - 32-bit unsigned integer
   s - 16-bit signed integer
   S - 16-bit unsigned integer
   b - 8-bit signed integer
   B - 8-bit unsigned integer
   t - ASCII text
   T - Lease Time, 32-bit unsigned integer implying a number of seconds from
       some event.  The special all-ones value means 'infinite'.  May either
       be printed as a decimal, eg, "3600",  or as this name, eg, "infinite".
   f - flag (true or false)
   A - array of whatever precedes (e.g., IA means array of IP addresses)
   a - array of the preceding character (e.g., IIa means two or more IP
       addresses)
   U - name of an option space (universe)
   F - implicit flag - the presence of the option indicates that the
       flag is true.
   o - the preceding value is optional.
   E - encapsulation, string or colon-separated hex list (the latter
       two for parsing).   E is followed by a text string containing
       the name of the option space to encapsulate, followed by a '.'.
       If the E is immediately followed by '.', the applicable vendor
       option space is used if one is defined.
   e - If an encapsulation directive is not the first thing in the string,
       the option scanner requires an efficient way to find the encapsulation.
       This is done by placing a 'e' at the beginning of the option.   The
       'e' has no other purpose, and is not required if 'E' is the first
       thing in the option.
   X - either an ASCII string or binary data.   On output, the string is
       scanned to see if it's printable ASCII and, if so, output as a
       quoted string.   If not, it's output as colon-separated hex.   On
       input, the option can be specified either as a quoted string or as
       a colon-separated hex list.
   N - enumeration.   N is followed by a text string containing
       the name of the set of enumeration values to parse or emit,
       followed by a '.'.   The width of the data is specified in the
       named enumeration.   Named enumerations are tracked in parse.c.
   d - Domain name (i.e., FOO or FOO.BAR).
*/

struct option dhcp_options [256] = {
    { "pad",  "", 0 },
    { "subnet-mask",  "I", 1 },
    { "time-offset",  "l", 2 },
    { "routers",  "IA", 3 },
    { "time-servers",  "IA", 4 },
    { "ien116-name-servers", "IA", 5 },
    { "domain-name-servers", "IA", 6 },
    { "log-servers",  "IA", 7 },
    { "cookie-servers",  "IA", 8 },
    { "lpr-servers",  "IA", 9 },
    { "impress-servers",  "IA", 10 },
    { "resource-location-servers",  "IA", 		 11 },
    { "host-name",  "t", 12 },
    { "boot-size",  "S", 13 },
    { "merit-dump",  "t", 14 },
    { "domain-name",  "t", 15 },
    { "swap-server",  "I", 16 },
    { "root-path",  "t", 17 },
    { "extensions-path",  "t", 18 },
    { "ip-forwarding",  "f", 19 },
    { "non-local-source-routing",  "f", 20 },
    { "policy-filter",  "IIA", 21 },
    { "max-dgram-reassembly",  "S", 22 },
    { "default-ip-ttl",  "B", 23 },
    { "path-mtu-aging-timeout",  "L", 		 24 },
    { "path-mtu-plateau-table",  "SA", 		 25 },
    { "interface-mtu",  "S", 26 },
    { "all-subnets-local",  "f", 27 },
    { "broadcast-address",  "I", 28 },
    { "perform-mask-discovery",  "f", 		 29 },
    { "mask-supplier",  "f", 30 },
    { "router-discovery",  "f", 31 },
    { "router-solicitation-address",  "I", 		 32 },
    { "static-routes",  "IIA", 33 },
    { "trailer-encapsulation",  "f", 34 },
    { "arp-cache-timeout",  "L", 35 },
    { "ieee802-3-encapsulation",  "f", 		 36 },
    { "default-tcp-ttl",  "B", 37 },
    { "tcp-keepalive-interval",  "L", 		 38 },
    { "tcp-keepalive-garbage",  "f", 39 },
    { "nis-domain",  "t", 40 },
    { "nis-servers",  "IA", 41 },
    { "ntp-servers",  "IA", 42 },
    { "vendor-encapsulated-options",  "E.", 		 43 },
    { "netbios-name-servers",  "IA", 44 },
    { "netbios-dd-server",  "IA", 45 },
    { "netbios-node-type",  "B", 46 },
    { "netbios-scope",  "t", 47 },
    { "font-servers",  "IA", 48 },
    { "x-display-manager",  "IA", 49 },
    { "dhcp-requested-address",  "I", 		 50 },
    { "dhcp-lease-time",  "L", 51 },
    { "dhcp-option-overload",  "B", 52 },
    { "dhcp-message-type",  "B", 53 },
    { "dhcp-server-identifier",  "I", 		 54 },
    { "dhcp-parameter-request-list",  "BA", 		 55 },
    { "dhcp-message",  "t", 56 },
    { "dhcp-max-message-size",  "S", 57 },
    { "dhcp-renewal-time",  "L", 58 },
    { "dhcp-rebinding-time",  "L", 59 },
    { "vendor-class-identifier",  "X", 60 },
    { "dhcp-client-identifier",  "X", 61 },
    { "nwip-domain",  "t", 62 },
    { "nwip-suboptions",  "Enwip.", 63 },
    { "nisplus-domain",  "t", 64 },
    { "nisplus-servers",  "IA", 65 },
    { "tftp-server-name",  "t", 66 },
    { "bootfile-name",  "t", 67 },
    { "mobile-ip-home-agent",  "IA", 68 },
    { "smtp-server",  "IA", 69 },
    { "pop-server",  "IA", 70 },
    { "nntp-server",  "IA", 71 },
    { "www-server",  "IA", 72 },
    { "finger-server",  "IA", 73 },
    { "irc-server",  "IA", 74 },
    { "streettalk-server",  "IA", 75 },
    { "streettalk-directory-assistance-server","IA", 76 },
    { "user-class",  "t", 77 },
    { "slp-directory-agent",  "fIa", 78 },
    { "slp-service-scope",  "fto", 79 },
    { "unknown-80",  "X", 80 },
    { "fqdn",  "Efqdn.", 81 },
    { "relay-agent-information","Eagent.",82 },
    { "nds-servers",  "IA", 85 },
    { "nds-tree-name",  "t", 86 },
    { "nds-context",  "t", 87 },
    { "subnet-selection",  "I", 118 },
    { "authenticate",  "X", 210 },
    { "option-end",  "e", 255 },
};

struct option nwip_options [256] = {
    { "pad",  "", 0 },
    { "illegal-1",  "", 1 },
    { "illegal-2",  "", 2 },
    { "illegal-3",  "", 3 },
    { "illegal-4",  "", 4 },
    { "nsq-broadcast",  "f", 5 },
    { "preferred-dss",  "IA", 6 },
    { "nearest-nwip-server",  "IA", 7 },
    { "autoretries",  "B", 8 },
    { "autoretry-secs",  "B", 9 },
    { "nwip-1-1",  "f", 10 },
    { "primary-dss",  "I", 11 },
};

/* Note that the "FQDN suboption space" does not reflect the FQDN option
 * format - rather, this is a handy "virtualization" of a flat option
 * which makes manual configuration and presentation of some of its
 * contents easier (each of these suboptions is a fixed-space field within
 * the fqdn contents - domain and host names are derived from a common field,
 * and differ in the left and right hand side of the leftmost dot, fqdn is
 * the combination of the two).
 */

struct option fqdn_options [256] = {
    { "pad",  "", 0 },
    { "no-client-update",  "f", 1 },
    { "server-update",  "f", 2 },
    { "encoded",  "f", 3 },
    { "rcode1",  "B", 4 },
    { "rcode2", "B", 5 },
    { "hostname",  "t", 6 },
    { "domainname",  "t", 7 },
    { "fqdn",  "t", 8 },
};

const char *hardware_types [] = {
    "ethernet",
    "token-ring",
    "fddi",
};

