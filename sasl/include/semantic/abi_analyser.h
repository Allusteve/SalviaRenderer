#ifndef SASL_SEMANTIC_ABI_ANALYSER_H
#define SASL_SEMANTIC_ABI_ANALYSER_H

#include <sasl/include/semantic/semantic_forward.h>

#include <sasl/enums/builtin_type_code.h>
#include <softart/include/enums.h>

#include <eflib/include/platform/boost_begin.h>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <eflib/include/platform/boost_end.h>

#include <vector>

BEGIN_NS_SASL_SEMANTIC();

class symbol;
class module_si;

enum storage_types{
	storage_none = 0,
	stream_in,
	stream_out,
	buffer_in,
	buffer_out,
	storage_types_count
};

struct storage_info{
	storage_info();
	int index;
	int offset;
	int size;
	storage_types storage;
	builtin_type_code sv_type;
};

//////////////////////////////////////////////////////////////////////////
// Application binary interface information.
// Used by host and interpolator / rasterizer.

class abi_info{
public:
	abi_info();

	softart::languages lang;

	void module( boost::shared_ptr<module_si> const& );
	bool is_module( boost::shared_ptr<module_si> const& ) const;

	void entry( boost::shared_ptr<symbol> const& );
	bool is_entry( boost::shared_ptr<symbol> const& ) const;

	bool add_input_semantic( softart::semantic sem );
	bool add_output_semantic( softart::semantic sem );
	void add_global_var( boost::shared_ptr<symbol> const& );

	storage_info* input_storage( softart::semantic );
	storage_info* alloc_input_storage( softart::semantic );

	storage_info* input_storage( boost::shared_ptr<symbol> const& );
	storage_info* alloc_input_storage( boost::shared_ptr<symbol> const& );

	storage_info* output_storage( softart::semantic );
	storage_info* alloc_output_storage( softart::semantic );

private:
	void update_abii();

	void update_input_semantics_abii();
	void update_output_semantics_abii();
	void update_input_stream_abii();
	void update_output_stream_abii();

	module_si* mod;
	symbol* entry_point;

	std::vector< softart::semantic > sems_in;
	typedef boost::unordered_map< softart::semantic, storage_info > sem_storages_t;
	sem_storages_t semin_storages;

	std::vector< symbol* > syms_in;
	typedef boost::unordered_map< symbol*, storage_info > sym_storages_t;
	sym_storages_t symin_storages;

	std::vector< softart::semantic > sems_out;
	boost::unordered_map< softart::semantic, storage_info > semout_storages;
};

// If entry of VS and PS was set, match the ABIs to generate interpolating code.
class abi_analyser{
public:
	bool entry( boost::shared_ptr<module_si>& mod, std::string const& name, softart::languages lang );
	boost::shared_ptr<symbol> const& entry( softart::languages lang ) const;

	void reset( softart::languages lang );
	void reset_all();

	bool update_abiis();
	bool verify_abiis();

	abi_info const* abii( softart::languages lang );

private:
	bool update_vs();
	bool update_ps();
	bool update_bs();

	bool verify_vs_ps();
	bool verify_ps_bs();

	boost::shared_ptr<module_si> mods[softart::lang_count];
	boost::shared_ptr<symbol> entries[softart::lang_count];
	boost::shared_ptr<abi_info> abiis[softart::lang_count];
};

END_NS_SASL_SEMANTIC();

#endif