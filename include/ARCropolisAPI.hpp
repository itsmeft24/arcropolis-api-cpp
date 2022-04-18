
#pragma once
#include <crc32.h>
#include <ARCTypes.hpp>

namespace ARCropolisAPI {
	
	enum class Event : u32
	{
		ArcFilesystemMounted,
		ModFilesystemMounted
	};
	
	struct APIVersion {
		u32 Major;
		u32 Minor;
	};
	
	typedef bool (*CallbackFunction)(u64, u8*, u64, u64*);
	typedef bool (*StreamCallbackFunction)(u64, u8*, u64*);
	typedef bool (*ExtensionCallbackFunction)(u64, u8*, u64, u64*);
	typedef bool (*EventCallbackFunction)(Event);
	
	extern "C" {
		void arcrop_register_callback(u64, u64, CallbackFunction);
		void arcrop_register_callback_with_path(u64, u64, StreamCallbackFunction);
		bool arcrop_load_file(u64, u8*, u64, u64*);
		static APIVersion* arcrop_api_version();
		void arcrop_require_api_version(u32, u32);
		void arcrop_register_extension_callback(u64, ExtensionCallbackFunction);
		bool arcrop_get_decompressed_size(u64, u64*);
		bool arcrop_get_loaded_arc(LoadedArc**);
		void arcrop_register_event_callback(Event, EventCallbackFunction);
		bool arcrop_is_file_loaded(u64);
		bool arcrop_is_mod_enabled(u64);
		void arcrop_show_mod_manager();
		void arcrop_show_config_editor();
		void arcrop_show_main_menu();
	}
	
	void RegisterCallback(Hash40 hash, u64 max_size, CallbackFunction clbk) {
		arcrop_register_callback(hash.as_u64(), max_size, clbk);
	}
	
	void RegisterCallback(u64 hash, u64 max_size, CallbackFunction clbk) {
		arcrop_register_callback(hash, max_size, clbk);
	}
	
	void RegisterStreamCallback(Hash40 hash, u64 max_size, StreamCallbackFunction clbk) {
		arcrop_register_callback_with_path(hash.as_u64(), max_size, clbk);
	}

	void RegisterStreamCallback(u64 hash, u64 max_size, StreamCallbackFunction clbk) {
		arcrop_register_callback_with_path(hash, max_size, clbk);
	}
	
	bool LoadFile(Hash40 hash, u8* buffer, u64 len, u64* out_size) {
		return arcrop_load_file(hash.as_u64(), buffer, len, out_size);
	}
	
	bool LoadFile(u64 hash, u8* buffer, u64 len, u64* out_size) {
		return arcrop_load_file(hash, buffer, len, out_size);
	}
	
	static APIVersion* GetAPIVersion() {
		return arcrop_api_version();
	}
	
	void RequireAPIVersion(const APIVersion& version) {
		arcrop_require_api_version(version.Major, version.Minor);
	}
	
	void RegisterExtensionCallback(Hash40 hash, ExtensionCallbackFunction clbk) {
		arcrop_register_extension_callback(hash.as_u64(), clbk);
	}
	
	void RegisterExtensionCallback(u64 hash, ExtensionCallbackFunction clbk) {
		arcrop_register_extension_callback(hash, clbk);
	}
	
	u64 GetDecompressedSize(Hash40 hash) {
		u64 out_size = 0;
		arcrop_get_decompressed_size(hash.as_u64(), &out_size);
		return out_size;
	}
	
	u64 GetDecompressedSize(u64 hash) {
		u64 out_size = 0;
		arcrop_get_decompressed_size(hash, &out_size);
		return out_size;
	}
	
	LoadedArc* GetLoadedArc() {
		LoadedArc* ret;
		arcrop_get_loaded_arc(&ret);
		return ret;
	}
	
	void RegisterEventCallback(Event e, EventCallbackFunction clbk) {
		arcrop_register_event_callback(e, clbk);
	}
	
	bool IsFileLoaded(u64 hash) {
		return arcrop_is_file_loaded(hash);
	}
	
	bool IsFileLoaded(Hash40 hash) {
		return arcrop_is_file_loaded(hash.as_u64());
	}
	
	bool IsModEnabled(u64 hash) {
		return arcrop_is_mod_enabled(hash);
	}
	
	bool IsModEnabled(Hash40 hash) {
		return arcrop_is_mod_enabled(hash.as_u64());
	}
	
	void ShowModManager() {
		arcrop_show_mod_manager();
	}

	void ShowConfigEditor() {
		arcrop_show_config_editor();
	}

	void ShowMainMenu() {
		arcrop_show_main_menu();
	}
}
