template <typename T> struct ClangVector {
	T* start;
	T* end;
	T* capacity;
};
struct Hash40 {
	u32 crc;
	u32 len;
	
	Hash40() : crc(0), len(0) {};
	
	Hash40(u32 _crc, u32 _len) : crc(_crc), len(_len) {};
	
	Hash40(const std::string& str) {
		crc = crc32(str.c_str(), str.size());
		len = (u32)str.size();
	}
	
	static Hash40 From(const std::string& str) {
		return { crc32(str.c_str(), str.size()), (u32)str.size() };
	}
	
	uint64_t as_u64() const {
		return *(u64*)this;
	}
	
	bool operator == (const Hash40& other) const {
		return other.crc == crc && other.len == len;
	}
};
struct FileSystemHeader {
	uint32_t table_filesize;
	uint32_t file_info_path_count;
	uint32_t file_info_index_count;
	uint32_t folder_count;

	uint32_t folder_offset_count_1;

	uint32_t hash_folder_count;
	uint32_t file_info_count;
	uint32_t file_info_sub_index_count;
	uint32_t file_data_count;

	uint32_t folder_offset_count_2;
	uint32_t file_data_count_2;
	uint32_t padding;

	uint32_t unk1_10; // always 0x10
	uint32_t unk2_10; // always 0x10

	uint8_t regional_count_1;
	uint8_t regional_count_2;
	uint16_t padding2;

	uint32_t version;
	uint32_t extra_folder;
	uint32_t extra_count;

	uint32_t unk[2];

	uint32_t extra_count_2;
	uint32_t extra_sub_count;
};
struct RegionalStruct {
	uint32_t unk;
	uint32_t unk1;
	uint32_t index;
};
struct StreamHeader {
	uint32_t quick_dir_count;
	uint32_t stream_hash_count;
	uint32_t stream_file_index_count;
	uint32_t stream_offset_entry_count;
};
struct QuickDir {
	uint32_t hash;
	uint32_t name_length : 8;
	uint32_t count : 24;
	uint32_t index;
};
struct StreamEntry {
	uint32_t hash;
	uint32_t name_length : 8;
	uint32_t index : 24;
	uint32_t flags;
};
struct HashToIndex {
	uint32_t hash;
	uint32_t length : 8;
	uint32_t index : 24;
  
  HashToIndex() : hash(0), length(0), index(0) {};
  
  HashToIndex(Hash40 _hash, uint32_t _index) {
    hash = _hash;
    index = _index;
	}
  
	Hash40 GetHash() const {
		return { hash, length };
	}
  
	static HashToIndex From(Hash40 _hash, uint32_t _index) {
		return { hash.crc, hash.len, index };
	}
  
	void SetHash(Hash40 _hash) {
		hash = _hash.crc;
		length = _hash.len;
	}
};
struct FileInfoBucket {
	uint32_t start;
	uint32_t count;
};
struct FilePath {
	HashToIndex path;
	HashToIndex ext;
	HashToIndex parent;
	HashToIndex file_name;
};
struct FileInfoIndex {
	uint32_t dir_offset_index;
	uint32_t file_info_index;
};
struct DirInfoFlags {
	uint32_t unk1 : 26;
	uint32_t redirected : 1;
	uint32_t unk2 : 1;
	uint32_t is_symlink : 1;
	uint32_t unk3 : 3;
};
struct DirInfo {
	HashToIndex path;
	Hash40 name;
	Hash40 parent;
	uint32_t extra_dis_re;
	uint32_t extra_dis_re_length;
	uint32_t file_info_start_index;
	uint32_t file_count;
	uint32_t child_dir_start_index;
	uint32_t child_dir_count;
	DirInfoFlags flags;
};
struct StreamData {
	uint64_t size;
	uint64_t offset;
};
struct DirectoryOffset {
	uint64_t offset;
	uint32_t decomp_size;
	uint32_t size;
	uint32_t file_start_index;
	uint32_t file_count;
	uint32_t directory_index;
};
struct FileInfoFlags {
	uint32_t unused : 4;
	uint32_t is_redirect : 1;
	uint32_t unused2 : 7;
	uint32_t unknown1 : 1;
	uint32_t padding3 : 2;
	uint32_t is_regional : 1;
	uint32_t is_localized : 1;
	uint32_t unused3 : 3;
	uint32_t unknown2 : 1;
	uint32_t unknown3 : 1;
	uint32_t unused4 : 10;
};
struct FileInfo {
	uint32_t file_path_index;
	uint32_t file_info_indice_index;
	uint32_t info_to_data_index;
	FileInfoFlags flags;
};
struct FileInfoToFileData {
	uint32_t folder_offset_index;
	uint32_t file_data_index;
	uint32_t file_info_idx : 24;
	uint32_t load_type : 8;
};
struct FileDataFlags {
	uint32_t compressed : 1;
	uint32_t use_zstd : 1;
	uint32_t unk : 30;
};
struct FileData {
	uint32_t offset_in_folder;
	uint32_t comp_size;
	uint32_t decomp_size;
	FileDataFlags flags;
};
struct LoadedArc {
	u64 magic;
	u64 stream_offset;
	u64 file_data_offset;
	u64 shared_file_data_offset;
	u64 file_system_offset;
	u64 file_system_search_offset;
	u64 patch_section_offset;
	FileSystemHeader* uncompressed_fs;
	FileSystemHeader* fs_header;
	u64 region_entry;
	FileInfoBucket* file_info_buckets;
	HashToIndex* file_hash_to_path_index;
	FilePath* file_paths;
	FileInfoIndex* file_info_indices;
	HashToIndex* dir_hash_to_info_index;
	DirInfo* dir_infos;
	DirectoryOffset* folder_offsets;
	HashToIndex* folder_child_hashes;
	FileInfo* file_infos;
	FileInfoToFileData* file_info_to_datas;
	FileData* file_datas;
	void* unk_section;
	StreamHeader stream_header;
	QuickDir* quick_dirs;
	HashToIndex* stream_hash_to_entries;
	StreamEntry* stream_entries;
	u32* stream_file_indices;
	StreamData* stream_datas;
	FileInfoBucket* extra_buckets;
	void* extra_entries;
	DirectoryOffset* extra_folder_offsets;
	ClangVector<unsigned char> extra_entry_vector;
	u32 version;
	u32 extra_count;
	void* loaded_file_system_search;
	void* loaded_patch_section;
};
