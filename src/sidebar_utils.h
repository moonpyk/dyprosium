#ifndef SIDEBAR_UTILS_H
#define SIDEBAR_UTILS_H

#define TREE_COLUMN_OPTIONS 0

#define TREE_ROLE_TYPE 999
#define TREE_ROLE_ITEM_PTR (TREE_ROLE_TYPE + 1)

#define TREE_ROLE_ROOT 0 // +DATA
#define TREE_ROLE_SUBNET 1 //+DATA
#define TREE_ROLE_SUBNET_RESERVATIONS 2
#define TREE_ROLE_SUBNET_RESERVATION_OPTION 3 //+DATA
#define TREE_ROLE_SUBNET_EXCLUSIONS 4
#define TREE_ROLE_SUBNET_OPTIONS 5
#define TREE_ROLE_GLOBAL_OPTIONS 6

#define setItemRole(VALUE) setData(TREE_COLUMN_OPTIONS, TREE_ROLE_TYPE, VALUE)
#define setDataPtr(VALUE) setData(TREE_COLUMN_OPTIONS, TREE_ROLE_ITEM_PTR, QVariant::fromValue(VALUE));

#define getItemRoleNoCheck() getItemRole(NULL)
#define getItemRole(SUCCESS_PTR) data(TREE_COLUMN_OPTIONS, TREE_ROLE_TYPE).toInt(SUCCESS_PTR) 

#define getDataPtr(TYPE) data(TREE_COLUMN_OPTIONS, TREE_ROLE_ITEM_PTR).value<TYPE>()

#define getConfiguration() getDataPtr(DHConfiguration *)
#define getSubNetwork() getDataPtr(DHSubNetwork *)
#define getSubNetworkExclusion() getDataPtr(DHSubNetworkExclusion *)
#define getSubNetworkReservation() getDataPtr(DHSubNetworkReservation *)

#endif // SIDEBAR_UTILS_H