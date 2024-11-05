#pragma once

#include "AssetManager.h"

namespace crepe {

template <typename asset>
std::shared_ptr<asset> AssetManager::cache(const std::string & file_path,
										   bool reload) {
	auto it = asset_cache.find(file_path);

	if (!reload && it != asset_cache.end()) {
		return std::any_cast<std::shared_ptr<asset>>(it->second);
	}

	std::shared_ptr<asset> new_asset
		= std::make_shared<asset>(file_path.c_str());

	asset_cache[file_path] = new_asset;

	return new_asset;
}

} // namespace crepe
