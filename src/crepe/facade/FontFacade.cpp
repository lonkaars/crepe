#include <fontconfig/fontconfig.h>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include "FontFacade.h"

using namespace std;
using namespace crepe;

FontFacade::FontFacade() {
	if (!FcInit()) {
		throw runtime_error("Failed to initialize Fontconfig.");
	}
}

FontFacade::~FontFacade() { FcFini(); }

Asset FontFacade::get_font_asset(const string & font_family) {

	FcPattern * raw_pattern
		= FcNameParse(reinterpret_cast<const FcChar8 *>(font_family.c_str()));
	if (!raw_pattern) {
		throw runtime_error("Failed to create font pattern.");
	}

	std::unique_ptr<FcPattern, std::function<void(FcPattern *)>> pattern(
		raw_pattern, [](FcPattern * p) { FcPatternDestroy(p); });

	FcConfig * config = FcConfigGetCurrent();
	if (!config) {
		throw runtime_error("Failed to get current Fontconfig configuration.");
	}

	FcResult result;
	FcPattern * raw_matched_pattern = FcFontMatch(config, pattern.get(), &result);
	if (!raw_matched_pattern) {
		throw runtime_error("No matching font found.");
	}

	std::unique_ptr<FcPattern, std::function<void(FcPattern *)>> matched_pattern(
		raw_matched_pattern, [](FcPattern * p) { FcPatternDestroy(p); });

	FcChar8 * file_path = nullptr;
	if (FcPatternGetString(matched_pattern.get(), FC_FILE, 0, &file_path) != FcResultMatch
		|| !file_path) {
		throw runtime_error("Failed to get font file path.");
	}

	string font_file_path = reinterpret_cast<const char *>(file_path);
	return Asset(font_file_path);
}
