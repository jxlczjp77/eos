
/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio/chain/chain_config.hpp>
#include <eosio/chain/types.hpp>

#include <fc/crypto/sha256.hpp>

#include <string>
#include <vector>

namespace eosio { namespace chain {

struct genesis_state {
   genesis_state();

   static const string eosio_root_key;

   chain_config   initial_configuration;
   
   

   time_point                               initial_timestamp;
   public_key_type                          initial_key;

   /**
    * Get the chain_id corresponding to this genesis state.
    *
    * This is the SHA256 serialization of the genesis_state.
    */
   chain_id_type compute_chain_id() const;
};

} } // namespace eosio::chain


FC_REFLECT(eosio::chain::genesis_state,
           (initial_timestamp)(initial_key)(initial_configuration))
