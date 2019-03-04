/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */

#include <eosio/chain/genesis_state.hpp>

// these are required to serialize a genesis_state
#include <fc/smart_ref_impl.hpp>   // required for gcc in release mode

namespace eosio { namespace chain {

genesis_state::genesis_state() {
   initial_timestamp = fc::time_point::from_iso_string( "2018-06-01T12:00:00" );
   initial_key = fc::variant(eosio_root_key).as<public_key_type>();

   initial_configuration.max_block_net_usage = config::default_max_block_net_usage;
   initial_configuration.target_block_net_usage_pct = config::default_target_block_net_usage_pct;
   initial_configuration.max_transaction_net_usage = config::default_max_transaction_net_usage;
   initial_configuration.base_per_transaction_net_usage = config::default_base_per_transaction_net_usage;
   initial_configuration.net_usage_leeway = config::default_net_usage_leeway;
   initial_configuration.context_free_discount_net_usage_num = config::default_context_free_discount_net_usage_num;
   initial_configuration.context_free_discount_net_usage_den = config::default_context_free_discount_net_usage_den;

   initial_configuration.max_block_cpu_usage = config::default_max_block_cpu_usage;
   initial_configuration.target_block_cpu_usage_pct = config::default_target_block_cpu_usage_pct;
   initial_configuration.max_transaction_cpu_usage = config::default_max_transaction_cpu_usage;
   initial_configuration.min_transaction_cpu_usage = config::default_min_transaction_cpu_usage;

   initial_configuration.max_transaction_lifetime = config::default_max_trx_lifetime;
   initial_configuration.deferred_trx_expiration_window = config::default_deferred_trx_expiration_window;
   initial_configuration.max_transaction_delay = config::default_max_trx_delay;
   initial_configuration.max_inline_action_size = config::default_max_inline_action_size;
   initial_configuration.max_inline_action_depth = config::default_max_inline_action_depth;
   initial_configuration.max_authority_depth = config::default_max_auth_depth;
}

chain::chain_id_type genesis_state::compute_chain_id() const {
   digest_type::encoder enc;
   fc::raw::pack( enc, *this );
   return chain_id_type{enc.result()};
}

} } // namespace eosio::chain
