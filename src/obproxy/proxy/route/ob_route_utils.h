/**
 * Copyright (c) 2021 OceanBase
 * OceanBase Database Proxy(ODP) is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#ifndef OBPROXY_ROUTE_UTILS_H
#define OBPROXY_ROUTE_UTILS_H
#include "lib/ob_define.h"
#include "lib/container/ob_iarray.h"
#include "share/part/ob_part_mgr_util.h"
#include "obutils/ob_proxy_json_config_info.h"

namespace oceanbase
{
namespace common
{
class ObString;
class ObAddr;
}
namespace obproxy
{
class ObResultSetFetcher;
namespace proxy
{
class ObProxyPartInfo;
class ObRouteParam;
class ObRoutineParam;
class ObTableRouteParam;
class ObTableEntryName;
class ObTableEntry;
class ObRoutineEntry;
class ObPartitionEntry;
class ObRouteUtils
{
public:
  static int get_table_entry_sql(char *sql_buf, const int64_t buf_len, ObTableEntryName &name,
                                 bool is_need_force_flush = false);
  static int get_part_info_sql(char *sql_buf, const int64_t buf_len, const uint64_t table_id);
  static int get_first_part_sql(char *sql_buf, const int64_t buf_len, const uint64_t table_id, const bool is_hash_part);
  static int get_sub_part_sql(char *sql_buf, const int64_t buf_len, const uint64_t table_id,
                              const bool is_template_table);

  static int fetch_table_entry(obproxy::ObResultSetFetcher &rs_fetcher, ObTableEntry &entry);
  static int fetch_part_info(obproxy::ObResultSetFetcher &rs_fetcher, ObProxyPartInfo &part_info);
  static int fetch_first_part(obproxy::ObResultSetFetcher &rs_fetcher, ObProxyPartInfo &part_info);
  static int fetch_sub_part(obproxy::ObResultSetFetcher &rs_fetcher, ObProxyPartInfo &part_info);

  static int build_sys_dummy_entry(const common::ObString &cluster_name,
                                   const int64_t cluster_id,
                                   const obutils::LocationList &rs_list,
                                   const bool is_rslist,
                                   ObTableEntry *&entry);
  static int build_and_add_sys_dummy_entry(const common::ObString &cluster_name,
                                           const int64_t cluster_id,
                                           const common::ObIArray<common::ObAddr> &addr_list,
                                           const bool is_rslist);
  static int build_and_add_sys_dummy_entry(const common::ObString &cluster_name,
                                           const int64_t cluster_id,
                                           const obutils::LocationList &location_list,
                                           const bool is_rslist);
  static int convert_addrs_to_locations(const common::ObIArray<common::ObAddr> &addr_list,
                                        obutils::LocationList &location_list);

  static int convert_route_param_to_table_param(const ObRouteParam &route_param,
                                                ObTableRouteParam &table_param);

  static int convert_route_param_to_routine_param(const ObRouteParam &route_param,
                                                  ObRoutineParam &routine_param);

  static int get_partition_entry_sql(char *sql_buf, const int64_t buf_len,
                                     const ObTableEntryName &name, uint64_t partition_id,
                                     bool is_need_force_flush);

  static int fetch_one_partition_entry_info(obproxy::ObResultSetFetcher &rs_fetcher,
                                            ObTableEntry &table_entry,
                                            ObPartitionEntry *&entry);
  static int get_routine_entry_sql(char *sql_buf, const int64_t buf_len,
                                   const ObTableEntryName &name);

  static int fetch_one_routine_entry_info(obproxy::ObResultSetFetcher &rs_fetcher,
                                          const ObTableEntryName &name,
                                          const int64_t cr_version,
                                          const int64_t cr_id,
                                          ObRoutineEntry *&entry);

private:
  static int fetch_part_key(obproxy::ObResultSetFetcher &rs_fetcher, ObProxyPartInfo &part_info);
  static int add_generated_part_key(const common::ObString &func_expr,
                                    const int64_t generated_key_idx,
                                    ObProxyPartInfo &part_info);
  static int fetch_part_option(obproxy::ObResultSetFetcher &rs_fetcher, ObProxyPartInfo &part_info);
  static int build_part_desc(ObProxyPartInfo &part_info);
  static int build_part_desc(ObProxyPartInfo &part_info,
                             const share::schema::ObPartitionLevel part_level,
                             ObProxyPartOption &part_opt);

};

bool is_fake_ip_port(const char *ip_str, const int64_t port);

} // end of namespace proxy
} // end of namespace obproxy
} // end of namespace oceanbase
#endif // OBPROXY_ROUTE_UTILS_H
