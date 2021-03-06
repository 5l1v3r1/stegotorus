/* Copyright 2011, 2012, 2013 SRI International
 * See LICENSE for other credits and copying information
 */

#ifndef _HTTP_H
#define _HTTP_H

#include "util.h"
#include "connections.h"
#include "protocol.h"
#include "steg.h"
#include "rng.h"
#include "payloads.h"
#include "modus_operandi.h"

#include <event2/buffer.h>



class http_steg_config_t : public steg_config_t
{
public:
  bool is_clientside : 1;
  payloads pl;
  const char* shared_secret;
  const char* hostname;
  modus_operandi_t* mop;

  /*
   * A useful switch for debugging a scheme. If it is true, then
   * a POST of X  will get a response of X. In other words one
   * could just do JPEG steg between the client and server by
   * turning off all the other schemes, and having post_reflection
   * be true. The default is false.
   *
   */
  bool post_reflection;



  STEG_CONFIG_DECLARE_METHODS(http);
  
  DISALLOW_COPY_AND_ASSIGN(http_steg_config_t);

};


class http_steg_t : public steg_t
{
public:
  http_steg_config_t *config;
  conn_t *conn;

  //ian says: i am replacing this with the hostname read in from the configfile.
  //char peer_dnsname[512];
  
  bool have_transmitted : 1;
  bool have_received : 1;
  bool persist_mode : 1;
  bool transmit_lock : 1;
  /* serverside will use this */
  bool accepts_gzip : 1;
  /* clientside will use this */
  bool is_gzipped : 1;

  http_content_t type;

  unsigned int bytes_recvd;

  http_steg_t(http_steg_config_t *cf, conn_t *cn);

  STEG_DECLARE_METHODS(http);

  DISALLOW_COPY_AND_ASSIGN(http_steg_t);

};



#endif

